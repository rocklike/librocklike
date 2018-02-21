dnl Process this file with autoconf to produce a configure script.

AC_PREREQ([2.59])
AC_INIT([librocklike], [0.0.1], [cnaureus.dev@gmail.com])
AC_PROG_CC

#AC_CANONICAL_SYSTEM
AC_CONFIG_MACRO_DIR([m4])
#AC_CONFIG_HEADERS([config.h])
#AC_CONFIG_AUX_DIR([build-aux])

dnl Initialize automake
AM_INIT_AUTOMAKE([foreign subdir-objects])

dnl Initialize Libtool
LT_INIT

dnl this allows us specify individual liking flags for each target
AC_PROG_CXX 
AC_LANG([C++])

# Check for C++11
#AC_LANG_PUSH([C++])
#AX_CXX_COMPILE_STDCXX_11([noext])
#AC_LANG_POP([C++])

# Configure pthreads.
#ACX_PTHREAD([have_pthread=yes])

AC_CONFIG_FILES(Makefile
                librocklike/Makefile
                include/Makefile
                GTestLib/Makefile
                TestProgram/Makefile
                Application/Makefile
                MainProgram/Makefile)
AC_OUTPUT
