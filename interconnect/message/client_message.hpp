#ifndef PID_GAME_CLIENT_MESSAGE_HPP
#define PID_GAME_CLIENT_MESSAGE_HPP

#include <bits/stdc++.h>
#include "model/component.hpp"

namespace interconnect::message
{

struct client_message_player_movement_t
{
	uint64_t player_uuid;
	model::component_transform_t transform;
};

/**
 * Enum for types of messages that can be sent from server to client
 */
enum client_message_type_t
{
	player_movement
};

/**
 * Definition of a high-level message from client to server
 */
struct client_message_t
{
	client_message_type_t type;
	void *content;
};

}

#endif //PID_GAME_CLIENT_MESSAGE_HPP
