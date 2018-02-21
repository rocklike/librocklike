#include "rl_message_dispatcher.hpp"

namespace rocklike
{

void MessageDispatcher::operator()(Queue<RLNetworkMessage, RlQueue> &queue, ServiceGateway &svcGateway)
{
	bool stopped = false;
	while (!stopped)
	{
		try
		{
			NetworkMessage netMsg;
			if (queue.pop(netMsg))
			{
				try
				{
					// pass messag to ServiceGateway
					std::cout << "Dispatcher: Got 1 Processing\n";
					svcGateway.process(netMsg);
					std::cout << "Dispatcher: Got 1 Processing Done\n";
					// get and send response
					netMsg.connStubPtr_->send_data(netMsg.getResponseData(), netMsg.getResponseDataSize());
					// TODO log
				}
				catch (...)
				{
					// TODO log
					std::cout << "Unknown Service Gateway Error\n";
				}
			}
			else
			{
				queue.wait(); // waits for 1 sec
			}
		}
		catch (QueueDisabledException &e)
		{
			// TODO log as system error, can't send a response
			std::cout << "Queue Disabled\n";
			stopped = true;
		}
		catch (...)
		{
			std::cout << "System Error\n";
		}
	}
}

} //namespace rocklike
