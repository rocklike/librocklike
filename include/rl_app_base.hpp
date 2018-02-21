#ifndef RL_APP_BASE_HPP_
#define RL_APP_BASE_HPP_

#include "rl_networkmessage_extractor_base.hpp"
#include "rl_service_gateway_delegate.hpp"

namespace rocklike
{

class AppBase : public ServiceGatewayDelegate
{
public:
	virtual ~AppBase();
	virtual void initialize() = 0;
	virtual void onNetworkMessageReceive(rocklike::NetworkMessage &netmsg) = 0;
	virtual void destroy() = 0;
	virtual std::shared_ptr<rocklike::MessageExtractorBase> createMessageExtractor() = 0;

protected:
	std::shared_ptr<rocklike::MessageExtractorBase> messageExtractorBase_;
};

} //namespace rocklike

#endif /* RL_APP_BASE_HPP_ */
