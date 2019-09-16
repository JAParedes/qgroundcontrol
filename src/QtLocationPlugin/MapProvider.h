#pragma once

#include <QByteArray>
#include <QNetworkProxy>
#include <QNetworkReply>
#include <QString>
#include <QtLocation/private/qgeomaptype_p.h>

static const unsigned char pngSignature[]  = {0x89, 0x50, 0x4E, 0x47, 0x0D,
                                             0x0A, 0x1A, 0x0A, 0x00};
static const unsigned char jpegSignature[] = {0xFF, 0xD8, 0xFF, 0x00};
static const unsigned char gifSignature[]  = {0x47, 0x49, 0x46, 0x38, 0x00};

const quint32 AVERAGE_MAPBOX_SAT_MAP     = 15739;
const quint32 AVERAGE_MAPBOX_STREET_MAP  = 5648;
const quint32 AVERAGE_TILE_SIZE          = 13652;
const quint32 AVERAGE_AIRMAP_ELEV_SIZE   = 2786;

class MapProvider : public QObject {
    Q_OBJECT
  public:
    MapProvider(
        QString referrer, QString imageFormat, quint32 averageSize,
        QGeoMapType::MapStyle _mapType = QGeoMapType::CustomMap, QObject* parent = nullptr);

    QNetworkRequest getTileURL(int x, int y, int zoom,
                               QNetworkAccessManager* networkManager);

    QString getImageFormat(const QByteArray& image);

    quint32 getAverageSize(){return _averageSize;}

    QGeoMapType::MapStyle getMapStyle(){return _mapType;}

  protected:
    QString _tileXYToQuadKey(int tileX, int tileY, int levelOfDetail);
    int     _getServerNum(int x, int y, int max);

    // Define Referrer for Request RawHeader
    QString     _referrer;
    QString     _imageFormat;
    quint32     _averageSize;
    QByteArray  _userAgent;
    QString     _language;
    QGeoMapType::MapStyle _mapType;

    // Define the url to Request
    virtual QString _getURL(int x, int y, int zoom,
                            QNetworkAccessManager* networkManager) = 0;
};
