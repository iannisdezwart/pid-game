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

	uint8_t payload[] = "Response!!!!!";

	interconnect::server_socket_t socket(1337);

	while (true)
	{
		interconnect::packet::packet_t packet;
		sockaddr_in client_addr;

		if (socket.receive(packet, client_addr) < 0)
		{
			if (errno != EAGAIN)
			{
				printf("receive() failed: %s\n",
					strerror(errno));
			}

			continue;
		}

		packet.print();
		socket.send(payload, sizeof(payload), client_addr);
	}


	return 0;
}