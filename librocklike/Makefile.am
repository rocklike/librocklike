#######################################
# The list of libraries we are building seperated by spaces.
# The 'lib_' indicates that these build products will be installed
# in the $(libdir) directory. For example /usr/lib
lib_LTLIBRARIES = librocklike.la

#######################################
# Build information for each library

# Sources for librocklikecore
librocklike_la_SOURCES = rl_message_extractor_base.cpp \
                         rl_service_gateway_delegate.cpp \
                         rl_connection_stub.cpp \
                         rl_network_message.cpp \
                         rl_tcpconnection.cpp \
                         rl_handler_thread_pool.cpp \
                         rl_queue.cpp \
                         rl_tcpserver.cpp \
                         rl_message_dispatcher.cpp \
                         rl_service_gateway.cpp \
                         rl_app_base.cpp
			
# Linker options libTestProgram
librocklike_la_LDFLAGS = -lboost_system -L${BOOST_ROOT}/lib

# Compiler options. Here we are adding the include directory
# to be searched for headers included in the source code.
librocklike_la_CPPFLAGS = -I$(top_srcdir)/include -I${BOOST_ROOT}/include

AM_CXXFLAGS=-std=c++11

