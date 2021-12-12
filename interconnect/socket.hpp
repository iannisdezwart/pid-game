/**
 * Low-level network socket implementation.
 * 
 * This module provides a low-level network socket implementation.  It includes
 * the basic socket functionality, as well as the ability to send and receive
 * data.  Both client and server sockets are defined here.
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

#ifndef INTERCONNECT_SOCKET_HPP
#define INTERCONNECT_SOCKET_HPP

#include <bits/stdc++.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <netdb.h>
#include <errno.h>

#include "packet.hpp"

namespace interconnect
{

/**
 * Returns the number of microseconds since UNIX epoch.
 */
uint64_t
now()
{
	struct timeval tv;
	gettimeofday(&tv, NULL);

	return tv.tv_sec * 1000000 + tv.tv_usec;
}

/**
 * Puts a socket into non-blocking mode.
 * When an IO operation is performed and there is no IO, the socket will
 * not wait until there is new IO, but simply skip the operation.
 * @param socket_fd The socket to put into non-blocking mode.
 */
int
set_nonblocking(int socket_fd)
{
	int flags;

	#ifdef O_NONBLOCK
	if ((flags = fcntl(fd, F_GETFL, 0)) == -1) flags = 0;
	return fcntl(fd, F_SETFL, flags | O_NONBLOCK);
	#else
	flags = 1;
	return ioctl(socket_fd, FIONBIO, &flags);
	#endif
}

/**
 * Structure that represents a client socket.
 * This socket will connect to a server socket when initialised.
 */
struct client_socket_t
{
	// The socket file descriptor.
	int fd;

	/**
	 * Creates a new client socket and connects to the server.
	 * @param ip The IP address of the server.
	 * @param port The port of the server.
	 */
	client_socket_t(const char *ip, uint16_t port)
	{
		// The address of the server to connect to.

		struct sockaddr_in server_addr;
		server_addr.sin_family = AF_INET;
		server_addr.sin_port = htons(port);

		// Open a UDP socket.

		fd = socket(AF_INET, SOCK_DGRAM, 0);

		if (fd < 0)
		{
			fprintf(stderr, "Failed to create a socket: %s\n",
				strerror(errno));
			exit(1);
		}

		// Decode the IP address string.

		if (inet_pton(AF_INET, ip, &server_addr.sin_addr) <= 0)
		{
			fprintf(stderr,
				"Failed to decode address %s to binary form\n",
				ip);
			exit(1);
		}

		// Connect to the server.

		if (connect(fd, (struct sockaddr *) &server_addr,
			sizeof(server_addr)) < 0)
		{
			fprintf(stderr, "Failed to connect to server: %s\n",
				strerror(errno));
		}

		// Set socket to non-blocking mode.

		set_nonblocking(fd);
	}


	/**
	 * Send a packet through the socket.
	 * The number of bytes which were sent is returned.
	 * If an error occurred, -1 is returned and errno is set to indicate
	 * the error.
	 */
	ssize_t
	send(uint8_t *data, size_t size)
	{
		packet::packet_t packet;

		// Set the header values.

		packet.header.checksum = packet::hash(data, size);
		packet.header.len = size;
		packet.header.sent_at = now();

		// Copy the data into the packet.

		memcpy(packet.body, data, size);

		// Send the packet through the socket.

		return write(fd, (void *) &packet,
			sizeof(packet::header_t) + size);
	}

	/**
	 * Receive a packet through the socket.
	 * Returns -1 on error. Errno is set to indicate the error.
	 */
	int
	receive(packet::packet_t &packet)
	{
		// Receive the packet.

		struct sockaddr_in client_addr;

		if (read(fd, &packet, sizeof(packet::packet_t)) == -1)
		{
			return -1;
		}

		// TODO: check for truncation.
		// Check the checksum.

		packet::hash_t checksum = packet::hash(packet.body,
			packet.header.len);

		// Check if the body was corrupted.

		if (packet.header.checksum != checksum)
		{
			errno = EBADMSG;
			return -1;
		}

		return 0;
	}
};

/**
 * Structure that represents a server socket.
 * This socket will listen for incoming connections.
 * @param port The port to listen on.
 */
struct server_socket_t
{
	// The socket file descriptor.
	int fd;

	/**
	 * Creates a new server socket and listens for incoming connections.
	 * @param port The port to listen on.
	 */
	server_socket_t(uint16_t port)
	{
		// Open a UDP socket.

		fd = socket(AF_INET, SOCK_DGRAM, 0);

		if (fd < 0)
		{
			fprintf(stderr, "Failed to create a socket: %s\n",
				strerror(errno));
			exit(1);
		}

		// Bind the socket to the port.

		struct sockaddr_in server_addr;
		server_addr.sin_family = AF_INET;
		server_addr.sin_port = htons(port);
		server_addr.sin_addr.s_addr = INADDR_ANY;

		if (bind(fd, (struct sockaddr *) &server_addr,
			sizeof(server_addr)) < 0)
		{
			fprintf(stderr, "Failed to bind to port %d: %s\n",
				port, strerror(errno));
			exit(1);
		}

		// Set socket to non-blocking mode.

		set_nonblocking(fd);
	}

	/**
	 * Send a packet through the socket.
	 * The client to send to is specified by `client_addr`.
	 * The number of bytes which were sent is returned.
	 * If an error occurred, -1 is returned and errno is set to indicate
	 * the error.
	 */
	ssize_t
	send(uint8_t *data, size_t size, struct sockaddr_in &client_addr)
	{
		packet::packet_t packet;

		// Set the header values.

		packet.header.checksum = packet::hash(data, size);
		packet.header.len = size;
		packet.header.sent_at = now();

		// Copy the data into the packet.

		memcpy(packet.body, data, size);

		// Send the packet through the socket.

		return sendto(fd, (void *) &packet,
			sizeof(packet::header_t) + size, 0,
			(struct sockaddr *) &client_addr,
			sizeof(client_addr));
	}

	/**
	 * Receive a packet through the socket.
	 * The client that sent the packet is stored in the `client_addr`
	 * passed by reference.
	 * Returns -1 on error. Errno is set to indicate the error.
	 */
	int
	receive(packet::packet_t &packet, struct sockaddr_in &client_addr)
	{
		// Receive the packet.

		socklen_t client_addr_len = sizeof(client_addr);

		if (recvfrom(fd, &packet, sizeof(packet::packet_t), 0,
			(struct sockaddr *) &client_addr, &client_addr_len)
			== -1)
		{
			return -1;
		}

		// TODO: check for truncation.
		// Check the checksum.

		packet::hash_t checksum = packet::hash(packet.body,
			packet.header.len);

		// Check if the body was corrupted.

		if (packet.header.checksum != checksum)
		{
			errno = EBADMSG;
			return -1;
		}

		return 0;
	}
};

}

#endif