## Process this file with automake to produce Makefile.in

INCLUDES = \
	@GTK_CFLAGS@
		

bin_PROGRAMS = run-free

run_free_SOURCES = \
	debug.h commonDefs.h help.h \
	main.c  main.h \
	support.c support.h \
	interface.c interface.h \
	callbacks.c callbacks.h \
	kbhit.c	kbhit.h \
	comboBox.c comboBox.h \
	comboHandlers.c comboHandlers.h


run_free_LDADD = @GTK_LIBS@

