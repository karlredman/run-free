AC_INIT(src)
AM_CONFIG_HEADER(include/config.h)
AM_INIT_AUTOMAKE(run-free, 1.0.2)
##
AC_PROG_CC
AC_PROG_CXX
AC_PROG_INSTALL
##
AC_STDC_HEADERS
PKG_CHECK_MODULES(GTK, glib >= 1.2.10 gtk+ >= 1.2.10)
AC_SUBST(GTK_CFLAGS)
AC_SUBST(GTK_LIBS)
AC_CHECK_HEADERS(curses.h curses/curses.h termios.h)
##
AC_OUTPUT(Makefile \
include/Makefile \
src/Makefile \
src/run_free/Makefile \
src/kbhit/Makefile )
##
##
echo ""
echo "--- Now run make, binaries will be under ./src ---"
echo "--- run make install to install under /usr/local/bin ---"
echo "--- add /usr/local/bin to your PATH ---"
echo ""
