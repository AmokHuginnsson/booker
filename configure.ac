dnl configure.ac is integral part of booker project.

dnl Initialization data.
AC_INIT([[booker]],[[0.0.0]],[[amok@frihet.ath.cx]])

AC_MSG_RESULT([--- Welcome to booker configurator ---                   [[0%]]])
AC_MSG_RESULT([--- Initialization ... ---                               [[6%]]])

dnl Unique file in project: bookerrc is sample configuration file.
AC_MSG_RESULT([--- Finding base directory ... ---                      [[12%]]])
AC_CONFIG_SRCDIR([[bookerrc]])
AC_CONFIG_AUX_DIR([aux])

dnl booker is not Free Software.
AC_COPYRIGHT([[booker (c) 2003 All rights reserved.]])

dnl booker is still in alpha stage.
AC_REVISION([[$ Revision: 0.0.0 $]])

dnl We select default language.
AC_LANG([C++])

dnl We will generate config.h with basic #defines.
AC_CONFIG_HEADER([config.h])

dnl Cheching for machine type.
AC_MSG_RESULT([--- Checking for machine type ... ---                   [[18%]]])
AC_CANONICAL_HOST()

dnl Testing presence of c compiler
AC_MSG_RESULT([--- Testing presence of c compiler ... ---              [[27%]]])
AC_PROG_CC
dnl and for c++ compiler
AC_MSG_RESULT([--- Testing presence of c++ compiler ... ---            [[35%]]])
AC_PROG_CXX
dnl and for c preprocesor
AC_MSG_RESULT([--- Looking for c/c++ preprocessor and egrep ... ---    [[43%]]])
AC_PROG_CPP
AC_PROG_CXXCPP
AC_PROG_EGREP

dnl Looking for main libc headers
AC_MSG_RESULT([--- Looking for main libc headers ... ---               [[51%]]])
AC_HEADER_MAJOR

dnl We need to know what operating system booker will be compiled on.
AC_MSG_RESULT([--- Guessing host operating system ... ---              [[69%]]])
AC_CHECK_HEADER(
	[[ncurses/ncurses.h]],
	[AC_DEFINE([[__PLD_HOST__]]) _HOST=['PLD. ---    ']
		_NCURSES_HEADER=[ncurses/ncurses.h]],
	[AC_CHECK_HEADER(
		[[bsd/curses.h]],
		[AC_DEFINE([[__FREEBSD_HOST__]]) _HOST=['FreeBSD. ---']
			_NCURSES_HEADER=[bsd/ncurses.h]],
		[AC_CHECK_HEADER(
			[[ncurses.h]],
			[AC_DEFINE([[__DEBIAN_HOST__]]) _HOST=['Debian. --- ']
				_NCURSES_HEADER=[ncurses.h]],
			[AC_MSG_ERROR([Can not recognize operating system!])]
		)]
	)]
)
AC_MSG_RESULT([--- Guessed host operating system is $_HOST       [[74%]]])

dnl What special compiler flags we can set?
AC_MSG_RESULT([--- Guessing specific compiler/linker features ... ---  [[75%]]])
_FLAG_____________________='none, lucky for us none. ---    '
CXXFLAGS=["$CXXFLAGS -Wl,--no-undefined -Wl,--fatal-warnings"]
AC_LINK_IFELSE([[extern int errno;int main(void){return(errno);}]],
						[],
						[AC_SUBST([SPECIAL_LINKER_FLAG],
							[[-Wl,--allow-shlib-undefined]])]
							_FLAG_____________________=[['-Wl,--allow-shlib-undefined. ---']]
							CXXFLAGS=["-Wl,--allow-shlib-undefined"]
							[AC_MSG_WARN([[We must use -Wl,--allow-shlib-undefined!]])])
AC_MSG_RESULT([--- Guessed fetures are $_FLAG_____________________[[83%]]])

dnl Now we can look for all needed libraries.
AC_MSG_RESULT([--- Looking for needed libraries ... ---                [[84%]]])
AC_CHECK_LIB([ncurses],[initscr],
							[],[AC_MSG_ERROR([Can not continue without ncurses.])])
AC_CHECK_LIB([mysqlclient],[mysql_init],
							[],[AC_MSG_ERROR([Can not continue without MySQL.])])
AC_CHECK_LIB([pq],[PQsetdbLogin],
							[],[AC_MSG_ERROR([Can not continue without PostGreSQL.])])
dnl WARNING!!! Names in c++ objects are _mangled_ so we need so use
dnl WARNING!!! this cryptic names here (I hope it is portable).
dnl UPDATE!: Now I know it is not portable across direrent versions of
dnl UPDATE!: compiler, so I used tricky hack with 'main'.
AC_CHECK_LIB([hcore],[xmalloc],
							[],[AC_MSG_ERROR([Can not continue without hcore.])])
AC_CHECK_LIB([hconsole],[main],
							[],[AC_MSG_ERROR([Can not continue without hconsole.])])
AC_CHECK_LIB([tools],[main],
							[],[AC_MSG_ERROR([Can not continue without tools.])])
AC_CHECK_LIB([dbwrapper],[main],
							[],[AC_MSG_ERROR([Can not continue without dbwrapper.])])
AC_CHECK_LIB([hdata],[main],
							[],[AC_MSG_ERROR([Can not continue without hdata.])])
AC_MSG_RESULT([--- All needed libraries found. ---                     [[92%]]])

dnl We need to check if out ncurses devel is not brain-damaged.
AC_MSG_RESULT([--- Libraries/environment sanity check ... ---          [[93%]]])
AC_MSG_CHECKING([if your ncurses-devel is brain-damaged])
CXXFLAGS=["-W -Wall -Werror -Wcast-align -Wconversion -Wwrite-strings -pedantic-errors -Wcast-qual"]
AC_COMPILE_IFELSE([#include <$_NCURSES_HEADER>
void foo(){printw("x");}],[AC_MSG_RESULT([[no :)]])],
	[AC_MSG_RESULT([[yes :(]])
		AC_MSG_ERROR([Can not continue with brain-damaged ncurses.])])

dnl We have to set up proper compiler/linker flags.
AC_OUTPUT([Makefile])
AC_MSG_RESULT([--- All ok, good luck! ---                     	       [[100%]]])
AC_MSG_RESULT([[Now you can type \`make'.]])

