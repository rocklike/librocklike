#ifndef EXCEPTION_RL_SENDIO_EXCEPTION_HPP_
#define EXCEPTION_RL_SENDIO_EXCEPTION_HPP_

#include <exception>

namespace rocklike
{

class SendIOException : public std::exception
{
  public:
	~SendIOException() throw()
	{
	}

	virtual char const *what() const throw()
	{
		return "Error sending";
	}
};

} //namespace rocklike

#endif /* EXCEPTION_RL_SENDIO_EXCEPTION_HPP_ */
