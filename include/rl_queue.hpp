#ifndef FRAMEWORK_RL_QUEUE_HPP_
#define FRAMEWORK_RL_QUEUE_HPP_

#include <thread>
#include <queue>
#include "rl_queue_disabled_exception.hpp"
#include "rl_network_message.hpp"

namespace rocklike
{

using RLNetworkMessage = rocklike::NetworkMessage;
using RlQueue = std::queue<rocklike::NetworkMessage>;

template <typename T, class Cont>
class Queue
{
  public:
	bool pop(T &element);
	bool push(T &element);
	//	bool empty() const;
	int size() const;
};

template <>
class Queue<RLNetworkMessage, RlQueue>
{
  public:
	Queue(int maxSize) : maxSize_(maxSize), stopped(false) {}

	bool pop(RLNetworkMessage &element) throw(QueueDisabledException);
	// bool push(RLNetworkMessage &element) throw(QueueDisabledException) = 0;
	bool push(RLNetworkMessage && element) throw(QueueDisabledException, std::invalid_argument);
	//	bool empty() const;
	int size();
	void wait();
	void notify();
	void notifyAll();
	void stop();

  private:
	RlQueue queue_;
	int maxSize_ = 100;
	std::mutex mutex_;
	std::mutex waitMutex_;
	std::condition_variable condVar_;

	bool stopped;
};

} //namespace rocklike

#endif /* FRAMEWORK_RL_QUEUE_HPP_ */
