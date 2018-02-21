TESTS = rocklike_test
check_PROGRAMS = rocklike_test
rocklike_test_SOURCES = RLNetworkMessageTest.cpp RLQueueTest.cpp AllTests.cpp
rocklike_test_CPPFLAGS = -I$(top_srcdir)/GTestLib -I$(top_srcdir)/include -I${BOOST_ROOT}/include
rocklike_test_LDFLAGS = $(top_srcdir)/GTestLib/libgtest.la  $(top_srcdir)/librocklike/librocklike.la -lboost_system -L${BOOST_ROOT}/lib

AM_CXXFLAGS=-std=c++11
