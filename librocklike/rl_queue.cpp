#include "rl_queue.hpp"

namespace rocklike
{

bool Queue<RLNetworkMessage, RlQueue>::pop(RLNetworkMessage &element) throw(QueueDisabledException)
{
	std::lock_guard<std::mutex> lockGuard(this->mutex_);

	if (this->stopped)
			throw QueueDisabledException();

	if (!this->queue_.empty())
	{
		element = this->queue_.front();
		this->queue_.pop();
		return true;
	}
	else
	{
		return false;
	}
}

/*
bool Queue<RLNetworkMessage, RlQueue>::push(RLNetworkMessage &element) throw(QueueDisabledException)
{
	std::lock_guard<std::mutex> lockGuard(this->mutex_);

	if (this->stopped)
	{
		throw QueueDisabledException();
	}

	if (this->queue_.size() < this->maxSize_)
	{
		this->queue_.push(element);
		return true;
	}
	else
	{
		return false;
	}
}
*/
bool Queue<RLNetworkMessage, RlQueue>::push(RLNetworkMessage && element) throw(QueueDisabledException, std::invalid_argument) 
{
	std::lock_guard<std::mutex> lockGuard(this->mutex_);

	if (this->stopped)
	{
		throw QueueDisabledException();
	}

	if (element.getRequestData() == nullptr ||  element.getRequestDataSize() == 0 || element.connStubPtr_ == nullptr) 
	{
		throw std::invalid_argument("RLQueue push failed.  Empty element");
	}

	if (this->queue_.size() < this->maxSize_)
	{
		this->queue_.push(std::move(element));
		return true;
	}
	else
	{
		return false;
	}
}

int Queue<RLNetworkMessage, RlQueue>::size()
{
	std::lock_guard<std::mutex> lockGuard(this->mutex_);
	return this->queue_.size();
}

//bool Queue<RLMessage, RlQueue>::empty() const {
//	return this->empty()
//}

void Queue<RLNetworkMessage, RlQueue>::wait()
{
	std::unique_lock<std::mutex> mlock(waitMutex_);
	this->condVar_.wait_for(mlock, std::chrono::seconds(1));
}

void Queue<RLNetworkMessage, RlQueue>::notify()
{
	this->condVar_.notify_one();
}

void Queue<RLNetworkMessage, RlQueue>::notifyAll()
{
	this->condVar_.notify_all();
}

void Queue<RLNetworkMessage, RlQueue>::stop()
{
	std::lock_guard<std::mutex> lockGuard(this->mutex_);
	this->stopped = true;
}

} //namespace rocklike
