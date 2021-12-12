#ifndef PID_GAME_SERVER_MESSAGE_HPP
#define PID_GAME_SERVER_MESSAGE_HPP

namespace interconnect::raw_model
{

enum server_message_type_t
{
	object_creation
};

struct server_message_header_t
{
	server_message_type_t type;
};
}

#endif //PID_GAME_SERVER_MESSAGE_HPP
