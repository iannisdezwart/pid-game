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