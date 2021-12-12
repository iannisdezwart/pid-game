#ifndef PID_GAME_SERVER_MESSAGE_HPP
#define PID_GAME_SERVER_MESSAGE_HPP

#include "model/object.hpp"

using namespace interconnect::model;

namespace interconnect::message
{

struct server_message_t
{
};

struct server_message_object_creation_t : public server_message_t
{
	object_t object;
};
}

#endif //PID_GAME_SERVER_MESSAGE_HPP
