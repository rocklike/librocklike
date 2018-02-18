#ifndef FRAMEWORK_RL_MESSAGE_DISPATCHER_HPP_
#define FRAMEWORK_RL_MESSAGE_DISPATCHER_HPP_

#include "rl_queue.hpp"
#include "rl_service_gateway.hpp"

namespace rocklike {


class MessageDispatcher {
public:
	void operator()(Queue<RLNetworkMessage, RlQueue> & queue, ServiceGateway & svcGateway);
};





} //end namespace

#endif /* FRAMEWORK_RL_MESSAGE_DISPATCHER_HPP_ */
