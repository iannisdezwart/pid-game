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

#ifndef INTERCONNECT_PACKET_HPP
#define INTERCONNECT_PACKET_HPP

#include <bits/stdc++.h>

#include <sodium.h>

namespace interconnect::packet
{

// Maximum size of a packet.
constexpr const size_t max_size = 1024;

/**
 * Structure that holds a hash and an equality operator overload.
 */
struct hash_t
{
	// Holds the bytes for the hash.
	uint8_t hash[32];

	/**
	 * Checks whether this hash equals another hash.
	 * Returns true if the hashes are equal, false otherwise.
	 */
	bool
	operator==(hash_t other_hash)
	{
		return sodium_memcmp(hash, other_hash.hash, sizeof(hash)) == 0;
	}

	/**
	 * Checks whether this hash does not equal another hash.
	 * Returns true if the hashes are not equal, false otherwise.
	 */
	bool
	operator!=(hash_t other_hash)
	{
		return !operator==(other_hash);
	}
};

/**
 * Hashes `size` bytes of `data`.
 */
hash_t
hash(uint8_t *data, size_t size)
{
	hash_t res;
	crypto_generichash_blake2b(res.hash, sizeof(res), data, size, NULL, 0);
	return res;
}

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
	// TODO: don't send over the wire.
	uint32_t len;

	// MD5 checksum of the body of the message.
	hash_t checksum;
};

/**
 * Structure that holds a packet header and a packet body.
 */
struct packet_t
{
	// The header of the packet.
	header_t header;

	// The body of the packet.
	uint8_t body[max_size - sizeof(header_t)];
};

}

#endif
