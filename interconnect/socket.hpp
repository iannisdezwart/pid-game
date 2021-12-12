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
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <netdb.h>
#include <errno.h>

namespace interconnect
{

/**
 * @brief Puts a socket into non-blocking mode.
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
 * Structure that represents a socket.
 * Will be inherited by the server and client socket classes.
 */
struct Socket
{
	// The socket file descriptor.
	int fd;
};

/**
 * Structure that represents a client socket.
 * This socket will connect to a server socket when initialised.
 */
struct ClientSocket : public Socket
{
	/**
	 * Creates a new client socket and connects to the server.
	 * @param ip The IP address of the server.
	 * @param port The port of the server.
	 */
	ClientSocket(char *ip, uint16_t port)
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
};

/**
 * Structure that represents a server socket.
 * This socket will listen for incoming connections.
 * @param port The port to listen on.
 */
struct ServerSocket : public Socket
{
	/**
	 * Creates a new server socket and listens for incoming connections.
	 * @param port The port to listen on.
	 */
	ServerSocket(uint16_t port)
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
};

}

#endif