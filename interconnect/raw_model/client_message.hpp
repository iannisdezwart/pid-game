#ifndef PID_GAME_CLIENT_MESSAGE_HPP
#define PID_GAME_CLIENT_MESSAGE_HPP

#include <bits/stdc++.h>
#include "model/component.hpp"

namespace interconnect::raw_model
{

struct client_message_player_movement_header_t
{
	uint64_t player_uuid;
};

enum client_message_type_t
{
	player_movement
};

struct client_message_header_t
{
	client_message_type_t type;
};

}

#endif //PID_GAME_CLIENT_MESSAGE_HPP
