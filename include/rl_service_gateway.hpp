#ifndef FRAMEWORK_RL_SERVICE_GATEWAY_HPP_
#define FRAMEWORK_RL_SERVICE_GATEWAY_HPP_

#include <memory>

#include "rl_network_networkmessage.hpp"
#include "rl_service_gateway_delegate.hpp"

namespace rocklike {


class ServiceGateway {
public:
	ServiceGateway(std::shared_ptr<ServiceGatewayDelegate> svcGwDelBasePtr);
	void process(NetworkMessage &netMsg);
private:
	std::shared_ptr<ServiceGatewayDelegate> svcGwDelBasePtr_;
};



}

#endif /* FRAMEWORK_RL_SERVICE_GATEWAY_HPP_ */
