dnl Process this file with autoconf to produce a configure script.

AC_PREREQ(2.59)
AC_INIT(librocklike, 1.0)
AC_PROG_CC

AC_CANONICAL_SYSTEM

AC_CONFIG_MACRO_DIR([m4])

dnl Initialize automake
AM_INIT_AUTOMAKE

dnl this allows us specify individual liking flags for each target
AC_PROG_CXX 

dnl Initialize Libtool
LT_INIT

AC_CONFIG_FILES(Makefile
                librocklike/Makefile
                include/Makefile)
AC_OUTPUT
