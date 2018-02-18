#ifndef EXCEPTION_RL_SERVICEROUTER_EXCEPTION_HPP_
#define EXCEPTION_RL_SERVICEROUTER_EXCEPTION_HPP_

#include <exception>

namespace rocklike
{

class ServiceRouterException : public std::exception {
public:
	~ServiceRouterException() throw() {

	}

	virtual char const * what() const throw() {
		return "Service Router Exception";
	}
};

}

#endif /* EXCEPTION_RL_SERVICEROUTER_EXCEPTION_HPP_ */
