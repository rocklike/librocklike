#######################################
# The list of libraries we are building seperated by spaces.
# The 'lib_' indicates that these build products will be installed
# in the $(libdir) directory. For example /usr/lib
check_LTLIBRARIES = libgtest.la

#######################################
# Build information for each library

# Sources for librocklikecore
libgtest_la_SOURCES = gtest/gtest-all.cc
			
libgtest_la_LDFLAGS = -lpthread

# Compiler options. Here we are adding the include directory
# to be searched for headers included in the source code.
#libgtest_la_CPPFLAGS = -I$(top_srcdir)/include -I${BOOST_ROOT}/include

AM_CXXFLAGS=-std=c++11
