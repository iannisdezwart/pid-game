#ifndef PID_GAME_SERVER_MESSAGE_HPP
#define PID_GAME_SERVER_MESSAGE_HPP

namespace interconnect::message
{

/**
 * Enum for types of messages that can be sent from server to client
 */
enum server_message_type_t
{

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
