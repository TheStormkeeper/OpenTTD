#ifndef MAP_H
#define MAP_H

#define TILE_X_BITS 8
#define TILE_Y_BITS 8

#define TILES_X (1 << TILE_X_BITS)
#define TILES_Y (1 << TILE_Y_BITS)

#define TILE_X_MAX (TILES_X - 1)
#define TILE_Y_MAX (TILES_Y - 1)

extern byte _map_type_and_height[];
extern byte _map5[];
extern byte _map3_lo[];
extern byte _map3_hi[];
extern byte _map_owner[];
extern byte _map2[];
extern byte _map_extra_bits[];

// binary logarithm of the map size, try to avoid using this one
static inline uint MapLogX(void)  { extern uint _map_log_x; return _map_log_x; }
static inline uint MapLogY(void)  { extern uint _map_log_y; return _map_log_y; }
/* The size of the map */
static inline uint MapSizeX(void) { return 1 << MapLogX(); }
static inline uint MapSizeY(void) { return 1 << MapLogY(); }
/* The maximum coordinates */
static inline uint MapMaxX(void) { return MapSizeX() - 1; }
static inline uint MapMaxY(void) { return MapSizeY() - 1; }
/* The number of tiles in the map */
static inline uint MapSize(void) { return MapSizeX() * MapSizeY(); }

#endif
