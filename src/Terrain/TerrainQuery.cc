/****************************************************************************
 *
 *   (c) 2009-2016 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>
 *
 * QGroundControl is licensed according to the terms in the file
 * COPYING.md in the root of the source code directory.
 *
 ****************************************************************************/

#include "TerrainQuery.h"
#include "QGCMapEngine.h"
#include "QGeoMapReplyQGC.h"

#include <QUrl>
#include <QUrlQuery>
#include <QNetworkRequest>
#include <QNetworkProxy>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QTimer>
#include <QtLocation/private/qgeotilespec_p.h>

QGC_LOGGING_CATEGORY(TerrainQueryLog, "TerrainQueryLog")

Q_GLOBAL_STATIC(TerrainAtCoordinateBatchManager, _TerrainAtCoordinateBatchManager)
Q_GLOBAL_STATIC(TerrainTileManager, _terrainTileManager)

TerrainAirMapQuery::TerrainAirMapQuery(QObject* parent)
    : TerrainQueryInterface(parent)
{

}

void TerrainAirMapQuery::requestCoordinateHeights(const QList<QGeoCoordinate>& coordinates)
{
    QString points;
    foreach (const QGeoCoordinate& coord, coordinates) {
            points += QString::number(coord.latitude(), 'f', 10) + ","
                    + QString::number(coord.longitude(), 'f', 10) + ",";
    }
    points = points.mid(0, points.length() - 1); // remove the last ',' from string

    QUrlQuery query;
    query.addQueryItem(QStringLiteral("points"), points);

    _queryMode = QueryModeCoordinates;
    _sendQuery(QString() /* path */, query);
}

void TerrainAirMapQuery::requestPathHeights(const QGeoCoordinate& fromCoord, const QGeoCoordinate& toCoord)
{
    QString points;
    points += QString::number(fromCoord.latitude(), 'f', 10) + ","
            + QString::number(fromCoord.longitude(), 'f', 10) + ",";
    points += QString::number(toCoord.latitude(), 'f', 10) + ","
            + QString::number(toCoord.longitude(), 'f', 10);

    QUrlQuery query;
    query.addQueryItem(QStringLiteral("points"), points);

    _queryMode = QueryModePath;
    _sendQuery(QStringLiteral("/path"), query);
}

void TerrainAirMapQuery::requestCarpetHeights(const QGeoCoordinate& swCoord, const QGeoCoordinate& neCoord, bool statsOnly)
{
    QString points;
    points += QString::number(swCoord.latitude(), 'f', 10) + ","
            + QString::number(swCoord.longitude(), 'f', 10) + ",";
    points += QString::number(neCoord.latitude(), 'f', 10) + ","
            + QString::number(neCoord.longitude(), 'f', 10);

    QUrlQuery query;
    query.addQueryItem(QStringLiteral("points"), points);

    _queryMode = QueryModeCarpet;
    _carpetStatsOnly = statsOnly;

    _sendQuery(QStringLiteral("/carpet"), query);
}

void TerrainAirMapQuery::_sendQuery(const QString& path, const QUrlQuery& urlQuery)
{
    QUrl url(QStringLiteral("https://api.airmap.com/elevation/v1/ele") + path);
    url.setQuery(urlQuery);
    qCDebug(TerrainQueryLog) << "_sendQuery" << url;

    QNetworkRequest request(url);

    QNetworkProxy tProxy;
    tProxy.setType(QNetworkProxy::DefaultProxy);
    _networkManager.setProxy(tProxy);

    QNetworkReply* networkReply = _networkManager.get(request);
    if (!networkReply) {
        qCDebug(TerrainQueryLog) << "QNetworkManager::Get did not return QNetworkReply";
        _requestFailed();
        return;
    }

    connect(networkReply, &QNetworkReply::finished, this, &TerrainAirMapQuery::_requestFinished);
}

void TerrainAirMapQuery::_requestFinished(void)
{
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(QObject::sender());

    if (reply->error() != QNetworkReply::NoError) {
        qCDebug(TerrainQueryLog) << "_requestFinished error:" << reply->error();
        reply->deleteLater();
        _requestFailed();
        return;
    }

    QByteArray responseBytes = reply->readAll();
    reply->deleteLater();

    // Convert the response to Json
    QJsonParseError parseError;
    QJsonDocument responseJson = QJsonDocument::fromJson(responseBytes, &parseError);
    if (parseError.error != QJsonParseError::NoError) {
        qCDebug(TerrainQueryLog) << "_requestFinished unable to parse json:" << parseError.errorString();
        _requestFailed();
        return;
    }

    // Check airmap reponse status
    QJsonObject rootObject = responseJson.object();
    QString status = rootObject["status"].toString();
    if (status != "success") {
        qCDebug(TerrainQueryLog) << "_requestFinished status != success:" << status;
        _requestFailed();
        return;
    }

    // Send back data
    const QJsonValue& jsonData = rootObject["data"];
    qCDebug(TerrainQueryLog) << "_requestFinished" << jsonData;
    switch (_queryMode) {
    case QueryModeCoordinates:
        emit _parseCoordinateData(jsonData);
        break;
    case QueryModePath:
        emit _parsePathData(jsonData);
        break;
    case QueryModeCarpet:
        emit _parseCarpetData(jsonData);
        break;
    }
}

void TerrainAirMapQuery::_requestFailed(void)
{
    switch (_queryMode) {
    case QueryModeCoordinates:
        emit coordinateHeights(false /* success */, QList<double>() /* heights */);
        break;
    case QueryModePath:
        emit pathHeights(false /* success */, qQNaN() /* latStep */, qQNaN() /* lonStep */, QList<double>() /* heights */);
        break;
    case QueryModeCarpet:
        emit carpetHeights(false /* success */, qQNaN() /* minHeight */, qQNaN() /* maxHeight */, QList<QList<double>>() /* carpet */);
        break;
    }
}

void TerrainAirMapQuery::_parseCoordinateData(const QJsonValue& coordinateJson)
{
    QList<double> heights;
    const QJsonArray& dataArray = coordinateJson.toArray();
    for (int i = 0; i < dataArray.count(); i++) {
        heights.append(dataArray[i].toDouble());
    }

    emit coordinateHeights(true /* success */, heights);
}

void TerrainAirMapQuery::_parsePathData(const QJsonValue& pathJson)
{
    QJsonObject jsonObject =    pathJson.toArray()[0].toObject();
    QJsonArray stepArray =      jsonObject["step"].toArray();
    QJsonArray profileArray =   jsonObject["profile"].toArray();

    double latStep = stepArray[0].toDouble();
    double lonStep = stepArray[1].toDouble();

    QList<double> heights;
    foreach (const QJsonValue& profileValue, profileArray) {
        heights.append(profileValue.toDouble());
    }

    emit pathHeights(true /* success */, latStep, lonStep, heights);
}

void TerrainAirMapQuery::_parseCarpetData(const QJsonValue& carpetJson)
{
    QJsonObject jsonObject =    carpetJson.toArray()[0].toObject();

    QJsonObject statsObject =   jsonObject["stats"].toObject();
    double      minHeight =     statsObject["min"].toDouble();
    double      maxHeight =     statsObject["min"].toDouble();

    QList<QList<double>> carpet;
    if (!_carpetStatsOnly) {
        QJsonArray carpetArray =   jsonObject["carpet"].toArray();

        for (int i=0; i<carpetArray.count(); i++) {
            QJsonArray rowArray = carpetArray[i].toArray();
            carpet.append(QList<double>());

            for (int j=0; j<rowArray.count(); j++) {
                double height = rowArray[j].toDouble();
                carpet.last().append(height);
            }
        }
    }

    emit carpetHeights(true /*success*/, minHeight, maxHeight, carpet);
}

TerrainOfflineAirMapQuery::TerrainOfflineAirMapQuery(QObject* parent)
    : TerrainQueryInterface(parent)
{

}

void TerrainOfflineAirMapQuery::requestCoordinateHeights(const QList<QGeoCoordinate>& coordinates)
{
    if (coordinates.length() == 0) {
        return false;
    }

    _tileBatchManager->addQuery(this, coordinates);

    return false;
}

void TerrainOfflineAirMapQuery::requestPathHeights(const QGeoCoordinate& fromCoord, const QGeoCoordinate& toCoord)
{
    // TODO
}

void TerrainOfflineAirMapQuery::requestCarpetHeights(const QGeoCoordinate& swCoord, const QGeoCoordinate& neCoord, bool statsOnly)
{
    // TODO
}

void TerrainOfflineAirMapQuery::_signalCoordinateHeights(bool success, QList<double> heights)
{
    emit coordinateHeights(success, heights)
}

void TerrainOfflineAirMapQuery::_signalPathHeights(bool success, double latStep, double lonStep, const QList<double>& heights)
{
    // TODO
}

void TerrainOfflineAirMapQuery::_signalCarpetHeights(bool success, double minHeight, double maxHeight, const QList<QList<double>>& carpet)
{
    // TODO
}

TerrainTileManager::TerrainTileManager(void)
{

}

void TerrainTileManager::addQuery(TerrainOfflineAirMapQuery* terrainQueryInterface, const QList<QGeoCoordinate>& coordinates)
{
    if (coordinates.length() > 0) {
        QList<float> altitudes;

        if (!_getAltitudesForCoordinates(coordinates, altitudes)) {
            QueuedRequestInfo_t queuedRequestInfo = { terrainQueryInterface, coordinates, QueryMode::QueryModeCoordinates };
            _requestQueue.append(queuedRequestInfo);
            return;
        }

        qCDebug(TerrainQueryLog) << "All altitudes taken from cached data";
        terrainQueryInterface->_signalTerrainData(coordinates.count() == altitudes.count(), altitudes);
    }
}

bool TerrainTileManager::_getAltitudesForCoordinates(const QList<QGeoCoordinate>& coordinates, QList<float>& altitudes)
{
    foreach (const QGeoCoordinate& coordinate, coordinates) {
        QString tileHash = _getTileHash(coordinate);
        _tilesMutex.lock();
        if (!_tiles.contains(tileHash)) {
            qCDebug(TerrainQueryLog) << "Need to download tile " << tileHash;

            // Schedule the fetch task
            if (_state != State::Downloading) {
                QNetworkRequest request = getQGCMapEngine()->urlFactory()->getTileURL(UrlFactory::AirmapElevation, QGCMapEngine::long2elevationTileX(coordinate.longitude(), 1), QGCMapEngine::lat2elevationTileY(coordinate.latitude(), 1), 1, &_networkManager);
                QGeoTileSpec spec;
                spec.setX(QGCMapEngine::long2elevationTileX(coordinate.longitude(), 1));
                spec.setY(QGCMapEngine::lat2elevationTileY(coordinate.latitude(), 1));
                spec.setZoom(1);
                spec.setMapId(UrlFactory::AirmapElevation);
                QGeoTiledMapReplyQGC* reply = new QGeoTiledMapReplyQGC(&_networkManager, request, spec);
                connect(reply, &QGeoTiledMapReplyQGC::finished, this, &TerrainTileManager::_fetchedTile);
                connect(reply, &QGeoTiledMapReplyQGC::aborted, this, &TerrainTileManager::_fetchedTile);
                _state = State::Downloading;
            }
            _tilesMutex.unlock();

            return false;
        } else {
            if (_tiles[tileHash].isIn(coordinate)) {
                altitudes.push_back(_tiles[tileHash].elevation(coordinate));
            } else {
                qCDebug(TerrainQueryLog) << "Error: coordinate not in tile region";
                altitudes.push_back(-1.0);
            }
        }
        _tilesMutex.unlock();
    }
    return true;
}

void TerrainTileManager::_tileFailed(void)
{
    QList<float>    noAltitudes;

    foreach (const QueuedRequestInfo_t& requestInfo, _requestQueue) {
        if (requestInfo.queryMode == QueryMode::QueryModeCoordinates) {
            requestInfo.terrainQueryInterface->_signalCoordinateHeights(false, noAltitudes);
        }
    }
    _requestQueue.clear();
}

void TerrainTileManager::_fetchedTile()
{
    QGeoTiledMapReplyQGC* reply = qobject_cast<QGeoTiledMapReplyQGC*>(QObject::sender());
    _state = State::Idle;

    if (!reply) {
        qCDebug(TerrainQueryLog) << "Elevation tile fetched but invalid reply data type.";
        return;
    }

    // remove from download queue
    QGeoTileSpec spec = reply->tileSpec();
    QString hash = QGCMapEngine::getTileHash(UrlFactory::AirmapElevation, spec.x(), spec.y(), spec.zoom());

    // handle potential errors
    if (reply->error() != QGeoTiledMapReply::NoError) {
        if (reply->error() == QGeoTiledMapReply::CommunicationError) {
            qCDebug(TerrainQueryLog) << "Elevation tile fetching returned communication error. " << reply->errorString();
        } else {
            qCDebug(TerrainQueryLog) << "Elevation tile fetching returned error. " << reply->errorString();
        }
        _tileFailed();
        reply->deleteLater();
        return;
    }
    if (!reply->isFinished()) {
        qCDebug(TerrainQueryLog) << "Error in fetching elevation tile. Not finished. " << reply->errorString();
        _tileFailed();
        reply->deleteLater();
        return;
    }

    // parse received data and insert into hash table
    QByteArray responseBytes = reply->mapImageData();

    QJsonParseError parseError;
    QJsonDocument responseJson = QJsonDocument::fromJson(responseBytes, &parseError);
    if (parseError.error != QJsonParseError::NoError) {
        qCDebug(TerrainQueryLog) << "Could not parse terrain tile " << parseError.errorString();
        qCDebug(TerrainQueryLog) << responseBytes;
        _tileFailed();
        reply->deleteLater();
        return;
    }

    TerrainTile* terrainTile = new TerrainTile(responseJson);
    if (terrainTile->isValid()) {
        _tilesMutex.lock();
        if (!_tiles.contains(hash)) {
            _tiles.insert(hash, *terrainTile);
        } else {
            delete terrainTile;
        }
        _tilesMutex.unlock();
    } else {
        qCDebug(TerrainQueryLog) << "Received invalid tile";
    }
    reply->deleteLater();

    // now try to query the data again
    for (int i = _requestQueue.count() - 1; i >= 0; i--) {
        QList<float> altitudes;
        if (_getAltitudesForCoordinates(_requestQueue[i].coordinates, altitudes)) {
            if (_requestQueue[i].queryMode == QueryMode::QueryModeCoordinates) {
                _requestQueue[i].terrainQueryInterface->_signalCoordinateHeights(_requestQueue[i].coordinates.count() == altitudes.count(), altitudes);
            }
            _requestQueue.removeAt(i);
        }
    }
}

QString TerrainTileManager::_getTileHash(const QGeoCoordinate& coordinate)
{
    QString ret = QGCMapEngine::getTileHash(UrlFactory::AirmapElevation, QGCMapEngine::long2elevationTileX(coordinate.longitude(), 1), QGCMapEngine::lat2elevationTileY(coordinate.latitude(), 1), 1);
    qCDebug(TerrainQueryLog) << "Computing unique tile hash for " << coordinate << ret;

    return ret;
}

TerrainAtCoordinateBatchManager::TerrainAtCoordinateBatchManager(void)
{
    _batchTimer.setSingleShot(true);
    _batchTimer.setInterval(_batchTimeout);
    connect(&_batchTimer, &QTimer::timeout, this, &TerrainAtCoordinateBatchManager::_sendNextBatch);
    connect(&_terrainQuery, &TerrainQueryInterface::coordinateHeights, this, &TerrainAtCoordinateBatchManager::_coordinateHeights);
}

void TerrainAtCoordinateBatchManager::addQuery(TerrainAtCoordinateQuery* terrainAtCoordinateQuery, const QList<QGeoCoordinate>& coordinates)
{
    if (coordinates.length() > 0) {
        qCDebug(TerrainQueryLog) << "addQuery: TerrainAtCoordinateQuery:coordinates.count" << terrainAtCoordinateQuery << coordinates.count();
        connect(terrainAtCoordinateQuery, &TerrainAtCoordinateQuery::destroyed, this, &TerrainAtCoordinateBatchManager::_queryObjectDestroyed);
        QueuedRequestInfo_t queuedRequestInfo = { terrainAtCoordinateQuery, coordinates };
        _requestQueue.append(queuedRequestInfo);
        if (!_batchTimer.isActive()) {
            _batchTimer.start();
        }
    }
}

void TerrainAtCoordinateBatchManager::_sendNextBatch(void)
{
    qCDebug(TerrainQueryLog) << "_sendNextBatch _state:_requestQueue.count:_sentRequests.count" << _stateToString(_state) << _requestQueue.count() << _sentRequests.count();

    if (_state != State::Idle) {
        // Waiting for last download the complete, wait some more
        _batchTimer.start();
        return;
    }

    if (_requestQueue.count() == 0) {
        return;
    }

    _sentRequests.clear();

    // Convert coordinates to point strings for json query
    QList<QGeoCoordinate> coords;
    foreach (const QueuedRequestInfo_t& requestInfo, _requestQueue) {
        SentRequestInfo_t sentRequestInfo = { requestInfo.terrainAtCoordinateQuery, false, requestInfo.coordinates.count() };
        qCDebug(TerrainQueryLog) << "Building request: coordinate count" << requestInfo.coordinates.count();
        _sentRequests.append(sentRequestInfo);

        coords += requestInfo.coordinates;
    }
    _requestQueue.clear();

    _terrainQuery.requestCoordinateHeights(coords);
    _state = State::Downloading;
}

void TerrainAtCoordinateBatchManager::_batchFailed(void)
{
    QList<double> noHeights;

    foreach (const SentRequestInfo_t& sentRequestInfo, _sentRequests) {
        if (!sentRequestInfo.queryObjectDestroyed) {
            disconnect(sentRequestInfo.terrainAtCoordinateQuery, &TerrainAtCoordinateQuery::destroyed, this, &TerrainAtCoordinateBatchManager::_queryObjectDestroyed);
            sentRequestInfo.terrainAtCoordinateQuery->_signalTerrainData(false, noHeights);
        }
    }
    _sentRequests.clear();
}

void TerrainAtCoordinateBatchManager::_queryObjectDestroyed(QObject* terrainAtCoordinateQuery)
{
    // Remove/Mark deleted objects queries from queues

    qCDebug(TerrainQueryLog) << "_TerrainAtCoordinateQueryDestroyed TerrainAtCoordinateQuery" << terrainAtCoordinateQuery;

    int i = 0;
    while (i < _requestQueue.count()) {
        const QueuedRequestInfo_t& requestInfo = _requestQueue[i];
        if (requestInfo.terrainAtCoordinateQuery == terrainAtCoordinateQuery) {
            qCDebug(TerrainQueryLog) << "Removing deleted provider from _requestQueue index:terrainAtCoordinateQuery" << i << requestInfo.terrainAtCoordinateQuery;
            _requestQueue.removeAt(i);
        } else {
            i++;
        }
    }

    for (int i=0; i<_sentRequests.count(); i++) {
        SentRequestInfo_t& sentRequestInfo = _sentRequests[i];
        if (sentRequestInfo.terrainAtCoordinateQuery == terrainAtCoordinateQuery) {
            qCDebug(TerrainQueryLog) << "Zombieing deleted provider from _sentRequests index:terrainAtCoordinateQuery" << sentRequestInfo.terrainAtCoordinateQuery;
            sentRequestInfo.queryObjectDestroyed = true;
        }
    }
}

QString TerrainAtCoordinateBatchManager::_stateToString(State state)
{
    switch (state) {
    case State::Idle:
        return QStringLiteral("Idle");
    case State::Downloading:
        return QStringLiteral("Downloading");
    }

    return QStringLiteral("State unknown");
}

void TerrainAtCoordinateBatchManager::_coordinateHeights(bool success, QList<double> heights)
{
    _state = State::Idle;

    if (!success) {
        _batchFailed();
        return;
    }

    int currentIndex = 0;
    foreach (const SentRequestInfo_t& sentRequestInfo, _sentRequests) {
        if (!sentRequestInfo.queryObjectDestroyed) {
            disconnect(sentRequestInfo.terrainAtCoordinateQuery, &TerrainAtCoordinateQuery::destroyed, this, &TerrainAtCoordinateBatchManager::_queryObjectDestroyed);
            QList<double> requestAltitudes = heights.mid(currentIndex, sentRequestInfo.cCoord);
            sentRequestInfo.terrainAtCoordinateQuery->_signalTerrainData(true, requestAltitudes);
            currentIndex += sentRequestInfo.cCoord;
        }
    }
    _sentRequests.clear();
}

TerrainAtCoordinateQuery::TerrainAtCoordinateQuery(QObject* parent)
    : QObject(parent)
{

}
void TerrainAtCoordinateQuery::requestData(const QList<QGeoCoordinate>& coordinates)
{
    if (coordinates.length() == 0) {
        return;
    }

    _TerrainAtCoordinateBatchManager->addQuery(this, coordinates);
}

void TerrainAtCoordinateQuery::_signalTerrainData(bool success, QList<double>& heights)
{
    emit terrainData(success, heights);
}

TerrainPathQuery::TerrainPathQuery(QObject* parent)
    : QObject(parent)
{
    qRegisterMetaType<PathHeightInfo_t>();
    connect(&_terrainQuery, &TerrainQueryInterface::pathHeights, this, &TerrainPathQuery::_pathHeights);
}

void TerrainPathQuery::requestData(const QGeoCoordinate& fromCoord, const QGeoCoordinate& toCoord)
{
    _terrainQuery.requestPathHeights(fromCoord, toCoord);
}

void TerrainPathQuery::_pathHeights(bool success, double latStep, double lonStep, const QList<double>& heights)
{
    PathHeightInfo_t pathHeightInfo;
    pathHeightInfo.latStep = latStep;
    pathHeightInfo.lonStep = lonStep;
    pathHeightInfo.heights = heights;
    emit terrainData(success, pathHeightInfo);
}

TerrainPolyPathQuery::TerrainPolyPathQuery(QObject* parent)
    : QObject   (parent)
    , _curIndex (0)
{
    connect(&_pathQuery, &TerrainPathQuery::terrainData, this, &TerrainPolyPathQuery::_terrainDataReceived);
}

void TerrainPolyPathQuery::requestData(const QVariantList& polyPath)
{
    QList<QGeoCoordinate> path;

    foreach (const QVariant& geoVar, polyPath) {
        path.append(geoVar.value<QGeoCoordinate>());
    }

    requestData(path);
}

void TerrainPolyPathQuery::requestData(const QList<QGeoCoordinate>& polyPath)
{
    // Kick off first request
    _rgCoords = polyPath;
    _curIndex = 0;
    _pathQuery.requestData(_rgCoords[0], _rgCoords[1]);
}

void TerrainPolyPathQuery::_terrainDataReceived(bool success, const TerrainPathQuery::PathHeightInfo_t& pathHeightInfo)
{
    if (!success) {
        _rgPathHeightInfo.clear();
        emit terrainData(false /* success */, _rgPathHeightInfo);
        return;
    }

    _rgPathHeightInfo.append(pathHeightInfo);

    if (++_curIndex >= _rgCoords.count() - 1) {
        // We've finished all requests
        emit terrainData(true /* success */, _rgPathHeightInfo);
    } else {
        _pathQuery.requestData(_rgCoords[_curIndex], _rgCoords[_curIndex+1]);
    }
}

TerrainCarpetQuery::TerrainCarpetQuery(QObject* parent)
    : QObject(parent)
{
    connect(&_terrainQuery, &TerrainQueryInterface::carpetHeights, this, &TerrainCarpetQuery::terrainData);
}

void TerrainCarpetQuery::requestData(const QGeoCoordinate& swCoord, const QGeoCoordinate& neCoord, bool statsOnly)
{
    _terrainQuery.requestCarpetHeights(swCoord, neCoord, statsOnly);
}
