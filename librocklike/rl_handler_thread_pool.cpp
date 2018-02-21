#include <iostream>

#include "rl_handler_thread_pool.hpp"
#include "rl_message_dispatcher.hpp"

namespace rocklike
{

HandlerThreadPool::HandlerThreadPool(int threadPoolSize, int maxQueueSize, std::shared_ptr<ServiceGatewayDelegate> svcGwDelBasePtr) : queue_(maxQueueSize), notifyFlag_(0), threadPoolSize_(threadPoolSize), svcGateway(svcGwDelBasePtr)
{
}

void HandlerThreadPool::start()
{
	for (int i = 0; i < this->threadPoolSize_; i++)
	{
		std::thread t((MessageDispatcher()), std::ref(this->queue_), std::ref(this->svcGateway));
		this->threadPool_.push_back(std::move(t));
	}
}

void HandlerThreadPool::stop()
{
	this->queue_.stop();
}

void HandlerThreadPool::joinAll()
{
	for (int i = 0; i < this->threadPoolSize_; i++)
	{
		if (this->threadPool_[i].joinable())
		{
			this->threadPool_[i].join();
		}
	}
}

void HandlerThreadPool::post(RLNetworkMessage &m)
{
	if ( !this->queue_.push(std::move(m)) )
	{
		throw 1; // TODO
	}
	else
	{
		this->queue_.notify();
	}
}

} //namespace rocklike
