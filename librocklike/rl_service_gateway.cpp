#include "rl_service_gateway.hpp"

namespace rocklike
{

ServiceGateway::ServiceGateway(std::shared_ptr<ServiceGatewayDelegate> svcGwDelBasePtr) : svcGwDelBasePtr_(svcGwDelBasePtr)
{
}

void ServiceGateway::process(NetworkMessage &netMsg)
{
	std::cout << "ServiceGateway::process: Processing\n";
	this->svcGwDelBasePtr_->onNetworkMessageReceive(netMsg);
	std::cout << "ServiceGateway::process: Processing Done\n";
}

} //namespace rocklike
