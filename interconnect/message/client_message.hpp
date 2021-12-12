#ifndef PID_GAME_CLIENT_MESSAGE_HPP
#define PID_GAME_CLIENT_MESSAGE_HPP

#include <bits/stdc++.h>
#include "model/component.hpp"

using namespace interconnect::model;

namespace interconnect::message
{

struct client_message_t
{
};

struct client_message_player_movement_t : public client_message_t
{
	uint64_t player_uuid;
	component_transform_t transform;
};

}

#endif //PID_GAME_CLIENT_MESSAGE_HPP
