//runfree.h
#ifndef   __RUNFREE_H__
# define  __RUNFREE_H__

#define APPNAME "run-free"

#ifndef VERSION  // runfree
#define VERSION "1.0.0"
#endif

#define RF_MAX_COMMAND_LEN 1023		// 1024 with '\0'
#define RF_MAX_COMBO_ELEM 5		// maximum # of items in the command
				// combo list

/* WINDOW DEFS */
/*** main window */
#define RF_MWINDOW_TITLE	"Run Program"
#define RF_MWINDOW_BORDERWIDTH	5

/* FILE DEFS */
#define RF_DEFAULT_FILE_DIR	"HOME/.run-free"
#define RF_DEFAULT_EXEC_DIR	"HOME/.run-free"
#define RF_RUN_IN_TERM_NAME	"./.run-free.tmp"
#define RF_HISTORY_FILE_NAME	"./.run-free.hst"
#define RF_CONFIG_FILE_NAME	"./.run-free.cfg"

/* configurables -defaults */
#define TERM			"xterm"			// assumed to be within path
#define RF_KBHIT_FILE_NAME	"run-free-kbhit"	// assumed to be within path

/* proto types */
int createScript(char *s);
int cleanUpScript();


#endif // __RUNFREE_H__
