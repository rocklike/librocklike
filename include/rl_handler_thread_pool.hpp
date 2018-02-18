#ifndef FRAMEWORK_RL_HANDLER_THREAD_POOL_HPP_
#define FRAMEWORK_RL_HANDLER_THREAD_POOL_HPP_

#include <atomic>
#include <vector>
#include <thread>
#include <iostream>
#include <sstream>

#include "rl_queue_disabled_exception.hpp"
#include "rl_queue.hpp"
#include "rl_service_gateway.hpp"

namespace rocklike
{

class HandlerThreadPool {
public:
	HandlerThreadPool(int threadPoolSize, int maxQueueSize, std::shared_ptr<ServiceGatewayDelegate> svcGwDelBasePtr);
	void start();
	void stop();
	void joinAll();

	void post(rocklike::NetworkMessage &m);

private:
	std::vector<std::thread> threadPool_;
	ServiceGateway svcGateway;
	Queue<rocklike::NetworkMessage, RlQueue> queue_;
	std::atomic_ushort notifyFlag_;
	int threadPoolSize_;

};

}

#endif /* FRAMEWORK_RL_HANDLER_THREAD_POOL_HPP_ */
