#ifndef EXCEPTION_RL_SERVICENOTFOUND_EXCEPTION_HPP_
#define EXCEPTION_RL_SERVICENOTFOUND_EXCEPTION_HPP_

#include <exception>

namespace rocklike
{

class ServiceNotFoundException : public std::exception {
public:
	~ServiceNotFoundException() throw() {

	}

	virtual char const * what() const throw() {
		return "Service Not Found.";
	}
};


}



#endif /* EXCEPTION_RL_SERVICENOTFOUND_EXCEPTION_HPP_ */
