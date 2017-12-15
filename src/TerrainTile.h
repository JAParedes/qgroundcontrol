#ifndef TERRAINTILE_H
#define TERRAINTILE_H

#include "QGCLoggingCategory.h"

#include <QGeoCoordinate>

Q_DECLARE_LOGGING_CATEGORY(TerrainTileLog)

/**
 * @brief The TerrainTile class
 *
 * Implements an interface for https://developers.airmap.com/v2.0/docs/elevation-api
 */

class TerrainTile
{
public:
    TerrainTile();
    ~TerrainTile();

    /**
    * Constructor from json doc with elevation data (either from file or web)
    *
    * @param document
    */
    TerrainTile(QJsonDocument document);

    /**
    * Check for whether a coordinate lies within this tile
    *
    * @param coordinate
    * @return true if within
    */
    bool isIn(const QGeoCoordinate& coordinate) const;

    /**
    * Check whether valid data is loaded
    *
    * @return true if data is valid
    */
    bool isValid(void) const { return _isValid; }

    /**
    * Evaluates the elevation at the given coordinate
    *
    * @param coordinate
    * @return elevation
    */
    float elevation(const QGeoCoordinate& coordinate) const;

    /**
    * Accessor for the minimum elevation of the tile
    *
    * @return minimum elevation
    */
    float minElevation(void) const { return _minElevation; }

    /**
    * Accessor for the maximum elevation of the tile
    *
    * @return maximum elevation
    */
    float maxElevation(void) const { return _maxElevation; }

    /**
    * Accessor for the average elevation of the tile
    *
    * @return average elevation
    */
    float avgElevation(void) const { return _avgElevation; }

    /**
    * Accessor for the center coordinate
    *
    * @return center coordinate
    */
    QGeoCoordinate centerCoordinate(void) const;

private:
    inline int _latToDataIndex(double latitude) const;
    inline int _lonToDataIndex(double longitude) const;

    QGeoCoordinate      _southWest;                                     /// South west corner of the tile
    QGeoCoordinate      _northEast;                                     /// North east corner of the tile

    float               _minElevation;                                  /// Minimum elevation in tile
    float               _maxElevation;                                  /// Maximum elevation in tile
    float               _avgElevation;                                  /// Average elevation of the tile

    float**             _data;                                          /// 2D elevation data array
    int                 _gridSizeLat;                                   /// data grid size in latitude direction
    int                 _gridSizeLon;                                   /// data grid size in longitude direction
    bool                _isValid;                                       /// data loaded is valid

    // Json keys
    static const char*  _jsonStatusKey;
    static const char*  _jsonDataKey;
    static const char*  _jsonBoundsKey;
    static const char*  _jsonSouthWestKey;
    static const char*  _jsonNorthEastKey;
    static const char*  _jsonStatsKey;
    static const char*  _jsonMaxElevationKey;
    static const char*  _jsonMinElevationKey;
    static const char*  _jsonAvgElevationKey;
    static const char*  _jsonCarpetKey;
};

#endif // TERRAINTILE_H
