#ifndef PID_GAME_SERVER_MESSAGE_HPP
#define PID_GAME_SERVER_MESSAGE_HPP

#include "model/object.hpp"

namespace interconnect::message
{

struct server_message_object_creation_t
{
	model::object_t object;
};

/**
 * Enum for types of messages that can be sent from server to client
 */
enum server_message_type_t
{
	object_creation
};

/**
 * Definition of a high-level message from server to client
 */
struct server_message_t
{
	server_message_type_t type;
	void *content;
};
}

#endif //PID_GAME_SERVER_MESSAGE_HPP
