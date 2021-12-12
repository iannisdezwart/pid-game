#include <bits/stdc++.h>
#include <sodium.h>

#include "packet.hpp"
#include "socket.hpp"

int
main()
{
	if (sodium_init() < 0)
	{
		std::cerr << "sodium_init() failed" << std::endl;
		exit(1);
	}

	uint8_t payload[] = "Hello, world!";

	interconnect::client_socket_t socket("127.0.0.1", 1337);
	socket.send(payload, sizeof(payload));

	while (true)
	{
		interconnect::packet::packet_t packet;

		if (socket.receive(packet) < 0)
		{
			if (errno != EAGAIN)
			{
				printf("receive() failed: %s\n",
					strerror(errno));
			}

			continue;
		}

		packet.print();
	}

	return 0;
}