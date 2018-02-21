#ifndef EXCEPTION_RL_QUEUE_DISABLED_EXCEPTION_HPP_
#define EXCEPTION_RL_QUEUE_DISABLED_EXCEPTION_HPP_

#include <exception>

namespace rocklike
{

class QueueDisabledException : public std::exception
{
  public:
	~QueueDisabledException() throw()
	{
	}

	virtual char const *what() const throw()
	{
		return "Queue Disabled.";
	}
};

} //namespace rocklike

#endif /* EXCEPTION_RL_QUEUE_DISABLED_EXCEPTION_HPP_ */
