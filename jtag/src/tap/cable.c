/*
 * $Id$
 *
 * Copyright (C) 2003 ETC s.r.o.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
 * 02111-1307, USA.
 *
 * Written by Marcel Telka <marcel@telka.sk>, 2003.
 *
 */

#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>

#include "cable.h"

extern cable_driver_t arcom_cable_driver;
extern cable_driver_t byteblaster_cable_driver;
extern cable_driver_t dlc5_cable_driver;
extern cable_driver_t ea253_cable_driver;
extern cable_driver_t ei012_cable_driver;
extern cable_driver_t mpcbdm_cable_driver;
extern cable_driver_t wiggler_cable_driver;

uint32_t frequency = 0;

cable_driver_t *cable_drivers[] = {
	&arcom_cable_driver,
	&byteblaster_cable_driver,
	&dlc5_cable_driver,
	&ea253_cable_driver,
	&ei012_cable_driver,
	&mpcbdm_cable_driver,
	&wiggler_cable_driver,
	NULL				/* last must be NULL */
};

void
cable_wait( void )
{
	useconds_t s;

	if (!frequency)
		return;

	s = 1000000 / frequency / 2;
	if (s == 0)
		s = 1;

	usleep( s );
}