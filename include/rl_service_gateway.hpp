#ifndef FRAMEWORK_RL_SERVICE_GATEWAY_HPP_
#define FRAMEWORK_RL_SERVICE_GATEWAY_HPP_

#include <memory>

#include "rl_network_message.hpp"
#include "rl_service_gateway_delegate.hpp"

namespace rocklike
{

class ServiceGateway
{
  public:
	ServiceGateway(std::shared_ptr<rocklike::ServiceGatewayDelegate> svcGwDelBasePtr);
	void process(rocklike::NetworkMessage &netMsg);

  private:
	std::shared_ptr<rocklike::ServiceGatewayDelegate> svcGwDelBasePtr_;
};

} //namespace rocklike

#endif /* FRAMEWORK_RL_SERVICE_GATEWAY_HPP_ */
