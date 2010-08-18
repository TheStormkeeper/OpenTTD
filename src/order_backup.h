/* $Id$ */

/*
 * This file is part of OpenTTD.
 * OpenTTD is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, version 2.
 * OpenTTD is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with OpenTTD. If not, see <http://www.gnu.org/licenses/>.
 */

/** @file order_backup.h Functions related to order backups. */

#ifndef ORDER_BACKUP_H
#define ORDER_BACKUP_H

#include "core/pool_type.hpp"
#include "order_type.h"
#include "vehicle_type.h"
#include "tile_type.h"
#include "group_type.h"
#include "company_type.h"

/** Unique identifier for an order backup. */
typedef uint8 OrderBackupID;
struct OrderBackup;

/** The pool type for order backups. */
typedef Pool<OrderBackup, OrderBackupID, 1, 256> OrderBackupPool;
/** The pool with order backups. */
extern OrderBackupPool _order_backup_pool;

/**
 * Data for backing up an order of a vehicle so it can be
 * restored after a vehicle is rebuilt in the same depot.
 */
struct OrderBackup : OrderBackupPool::PoolItem<&_order_backup_pool> {
private:
	TileIndex tile;            ///< Tile of the depot where the order was changed.
	GroupID group;             ///< The group the vehicle was part of.
	uint16 service_interval;   ///< The service interval of the vehicle.
	char *name;                ///< The custom name of the vehicle.

	const Vehicle *clone;      ///< Vehicle this vehicle was a clone of.
	VehicleOrderID orderindex; ///< The order-index the vehicle had.
	Order *orders;             ///< The actual orders if the vehicle was not a clone.

	/**
	 * Create an order backup for the given vehicle.
	 * @param v The vehicle to make a backup of.
	 */
	OrderBackup(const Vehicle *v);

	/**
	 * Restore the data of this order to the given vehicle.
	 * @param v The vehicle to restore to.
	 */
	void DoRestore(const Vehicle *v);

public:
	/** Free everything that is allocated. */
	~OrderBackup();

	/**
	 * Create an order backup for the given vehicle.
	 * @param v The vehicle to make a backup of.
	 * @note Will automatically remove any previous backups of this user.
	 */
	static void Backup(const Vehicle *v);

	/**
	 * Restore the data of this order to the given vehicle.
	 * @param v The vehicle to restore to.
	 * @note After restoration the backup will automatically be removed.
	 */
	static void Restore(const Vehicle *v);

	/**
	 * Reset the OrderBackups.
	 * @param tile The tile of the order backup.
	 */
	static void Reset(TileIndex tile = INVALID_TILE);

	/**
	 * Clear the group of all backups having this group ID.
	 * @param group The group to clear.
	 */
	static void ClearGroup(GroupID group);

	/**
	 * Clear/update the (clone) vehicle from an order backup.
	 * @param v The vehicle to clear.
	 * @pre v != NULL
	 * @note If it is not possible to set another vehicle as clone
	 *       "example", then this backed up order will be removed.
	 */
	static void ClearVehicle(const Vehicle *v);
};

#define FOR_ALL_ORDER_BACKUPS_FROM(var, start) FOR_ALL_ITEMS_FROM(OrderBackup, order_backup_index, var, start)
#define FOR_ALL_ORDER_BACKUPS(var) FOR_ALL_ORDER_BACKUPS_FROM(var, 0)

#endif /* ORDER_BACKUP_H */
