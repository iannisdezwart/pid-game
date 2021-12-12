/**
 * Low-level network packet manipulation.
 * 
 * This module provides a packet structure as a thin layer on top of UDP.  It
 * provides some additional information for the server-client structure of $GAME
 * such as client-server time synchronization.
 * 
 * ---
 * 
 * Copyright 2021 Iannis de Zwart, Karol Jurski, Arav K.
 * 
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option) any later
 * version.
 * 
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 * 
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef INTERCONNECT_TYPES_H
#define INTERCONNECT_TYPES_H

#include <bits/stdc++.h>

namespace interconnect::packet
{

/**
 * A structure to represent a header of a UDP packet.
 *
 * The header is composed of the time it was sent, the length of the body of
 * the message, and a checksum of the body. For now, we don't use the checksum
 * for the sent_at and the length fields, but we may in the future if this
 * leads to laggy behaviour.
 *
 * This header is laid out at the start of any message. It can be used to
 * send arbitrary data to the other side. There will be an abstraction for
 * the types of data that can be sent. These abstractions will be stored in the
 * form of an extra header in the body of the basic UDP packet.
 */
struct header_t
{
	// When the message was sent, in microseconds since UNIX epoch.
	uint64_t sent_at;

	// The length of the body in bytes.
	uint32_t len;

	// MD5 checksum of the body of the message.
	char checksum[16];
};

}

#endif
