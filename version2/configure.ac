AC_INIT(src)
AM_INIT_AUTOMAKE(run-free, 2.0.0)
AM_CONFIG_HEADER(config.h)
##
#RPM
dnl For my rpm.m4 macros
RPM_RELEASE=1
AC_SUBST(RPM_RELEASE)

AM_RPM_INIT
dnl Enable or disable the rpm making rules in Makefile.am
AM_CONDITIONAL(MAKE_RPMS, test x$make_rpms = xtrue)

#for c++: dnl This is a little hack to make this work with rpm better (see mysql++.spec.in)
test -z "$CXXFLAGS" && CXXFLAGS="${CFLAGS}"
#
#debug mode
AC_ARG_ENABLE(debug,
	AC_HELP_STRING(--enable-debug,Output debugging information to STDOUT (default=no)),
	enable_debug=yes,enable_debug=no)

if [! test "x$enable_debug" != "xyes"]; then
	CFLAGS="$CFLAGS -DDEBUG"
	CXXFLAGS="$CXXFLAGS -DDEBUG"
fi
#bash_history
AC_ARG_WITH(bash_history,
	AC_HELP_STRING(--with-bash_history=FILENAME, Use specified Bash History file in home directory (default=~/.bash_history)))
if test "x$with_bash_history" = "x" ; then
	XBASH_HISTORY_FILENAME='".bash_history"'
else
  	XBASH_HISTORY_FILENAME=\"$with_bash_history\"
fi
#AH_TEMPLATE([BASH_HISTORY_FILENAME], [Specify the bash_history filename])
#AC_DEFINE(BASH_HISTORY_FILENAME, $XBASH_HISTORY_FILENAME)
AC_DEFINE_UNQUOTED(BASH_HISTORY_FILENAME, $XBASH_HISTORY_FILENAME,Specify the bash_history filename)
#
#
#user_history
AC_ARG_ENABLE(user_history,
	AC_HELP_STRING(--enable-user_history, Use the user history filename by default (default=no)),
	enable_user_history=yes,enable_user_history=no)

if [! test "x$enable_user_history" != "xyes"]; then
	AC_DEFINE(USE_USER_HISTORY_FILENAME,1,Use user history filename by default)
fi

AC_ARG_WITH(user_history,
	AC_HELP_STRING(--with-user_history=FILEPATH, Use specified History file from path (default=./.user_history)))
if test "x$with_user_history" = "x" ; then
	USER_HISTORY_FILENAME='".user_history"'
else
  	USER_HISTORY_FILENAME=\"$with_user_history\"
fi
	AC_DEFINE_UNQUOTED(USER_HISTORY_FILENAME, $USER_HISTORY_FILENAME,Specify the user_history filepath)
#
#history display length
AC_ARG_WITH(history_length,
	AC_HELP_STRING(--with-history_length=LENGTH, Show LENGTH entries when displaying history (default=20)))
if test "x$with_history_length" = "x" ; then
	HISTORY_LEN='20'
else
  	HISTORY_LEN=$with_history_length
fi
AC_DEFINE_UNQUOTED(DEFAULT_HISTORY_LEN, $HISTORY_LEN,Specify history display entries length)
#
#copyright statement
COPYRIGHT='"COPYRIGHT 2004, Karl N. Redman (parasyte@sleepingstill.com)"'
AC_DEFINE_UNQUOTED(COPYRIGHT,$COPYRIGHT, GNU and SleepingStill copyright statement)
LICENSE='"This application comes with ABSOLUTELY NO WARRANTY; \nfor details see the licensing agreement distributed with this application"'
AC_DEFINE_UNQUOTED(LICENSE,$LICENSE, GNU and SleepingStill license statement)
#
#terminal path
AC_ARG_WITH(terminal_path,
	AC_HELP_STRING(--with-terminal_path=FILENAME, Use specified terminal executable for run_in_term mode (default=xterm)))
if test "x$with_terminal_path" = "x" ; then
	DEFAULT_TERMINAL_PATH='"xterm"'
else
  	DEFAULT_TERMINAL_PATH=\"$with_terminal_path\"
fi
AC_DEFINE_UNQUOTED(DEFAULT_TERMINAL_PATH, $DEFAULT_TERMINAL_PATH,Specify default terminal for run_in_term mode)
##
#######################################
#######################################
#debuging output parameters (for debug.h)
DEBUG_PRINTF="g_print"
DEBUG_PRINTF_INCLUDE="<gtk/gtk.h>"
AC_DEFINE_UNQUOTED(DEBUG_PRINTF, $DEBUG_PRINTF,Specify the printf type of function call used in debug.h)
AC_DEFINE_UNQUOTED(DEBUG_PRINTF_INCLUDE, $DEBUG_PRINTF_INCLUDE, Specify the include file to support the printf statement)
##
#######################################
#######################################
AC_ISC_POSIX
AC_PROG_CC
AM_PROG_CC_STDC
AC_HEADER_STDC
AC_PROG_INSTALL
##
AC_STDC_HEADERS
AM_PATH_GTK(1.2.0, , AC_MSG_ERROR(Cannot find GTK: Is gtk-config in path?))
PKG_CHECK_MODULES(GTK, glib >= 1.2.10 gtk+ >= 1.2.10)
AC_SUBST(GTK_CFLAGS)
AC_SUBST(GTK_LIBS)
AC_CHECK_HEADERS(curses.h curses/curses.h termios.h)
##
dnl Use -Wall if we have gcc.
changequote(,)dnl
if test "x$GCC" = "xyes"; then
  case " $CFLAGS " in
  *[\ \	]-Wall[\ \	]*) ;;
  *) CFLAGS="$CFLAGS -Wall" ;;
  esac
fi
changequote([,])dnl
##
AC_OUTPUT(Makefile \
extradist/Makefile \
src/Makefile \
debian/Makefile \
docs/Makefile \
docs/def/Makefile \
docs/html/Makefile \
run-free.spec)
##
##
echo "--- Now run make ---"
echo ""
