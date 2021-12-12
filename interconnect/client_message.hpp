#ifndef PID_GAME_CLIENT_MESSAGE_HPP
#define PID_GAME_CLIENT_MESSAGE_HPP

namespace interconnect::message
{

/**
 * Enum for types of messages that can be sent from server to client
 */
enum client_message_type_t
{

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
