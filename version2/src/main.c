/*! \file main.c
  \brief run-free main file

  run-free is a command line launching program written in gtk. This
  version of run-free is written is C for gtk+1.2
*/

/*! \mainpage 
 * \htmlinclude mainpage.html
 * 
 * \htmlinclude maingraph.html
 * 
 * <b>Here is the README file for this project:</b>
 * \verbinclude README
 *
 * <b>Please note the License for this project:</b>
 * \verbinclude COPYING
 */

/* NOTICE:
    Copyright (C) 2004  Karl N. Redman (SleepingStill.com)

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

    For further information contact: parasyte@sleepingstill.com
*/


#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>

#include "interface.h"
#include "support.h"
#include "main.h"
#include "comboBox.h"
#include "kbhit.h"
#include "commonDefs.h"
#include "debug.h"
#include "comboHandlers.h"
#include "help.h"

#include <getopt.h>
/** @name getopt externs
 *  externs from getopt functionality
 */
//@{ 
///command line options
extern char *optarg;			
///option arguments
extern int optind, opterr, optopt;
///the environment
extern char **environ;			
//@}

/// The Main
/** Long mian function that is intended to be split up some day
 */
int
main (int argc, char *argv[], char *env[])
{
  gboolean gui =TRUE, history_set =FALSE, listops = FALSE;
  

  int opt =0;


  /*Global_Initialization -Items initialized for runtime
   */
  history_file = NULL;		
  command = NULL;
  terminal_path = NULL;
  die = TRUE;			
  run_in_term = FALSE;		
  no_kbhit = FALSE;
  combo_mode = RF_HISTORY_MODE;	
  keep_open = FALSE;

  //init gtk stuff
  gtk_set_locale ();
  gtk_init (&argc, &argv);

  char *home_directory = getenv("HOME"); /*! get the user's home directory */

  //show debug mode message
  dprint("run-free: debug mode enabled");

  //loop through the argument options
  while(1)
    {
      int option_index = 0;
      static struct option long_options[] = {
	{"bash", 0, 0, 'b'},
	{"command", 1, 0, 'c'},
	{"die", 0, 0, 'd'},
	{"help", 0, 0, 'h'},
	{"histlen", 1, 0, 0},
	{"history", 1, 0, 0},
	{"kbhit", 0, 0, 'k'},
	{"nokbhit", 0, 0, 'i'},
	{"keystrokes", 0, 0, 'y'},
	{"listops", 0, 0, 'l'},
	{"termstay", 0, 0, 'o'},
	{"runterm", 0, 0, 'r'},
	{"terminal", 1, 0, 't'},
	{"version", 0, 0, 'V'},
	//{"smart", 0, 0, 's'},
	{0, 0, 0, 0}
      };

      /**\todo cleanup getopt stuff -it's messy! */

      //do command line processing
      opt = getopt_long(argc, argv, "bc:dhiklort:yV", long_options, &option_index);

      if(opt == -1)
	break;
      
      switch(opt)
	{
	case 0:		//long arguments
	  if(strcmp(long_options[option_index].name, OPTARG_HISTORY) ==0)
	    {
	      //handle history file
	      if(strcmp(optarg, OPTARG_HISTORY_FILETYPE_RF)==0) //run-free
		{
		  history_file = g_malloc(strlen(home_directory)+strlen(RF_HISTORY_FILENAME)+2);
		  sprintf(history_file, "%s/%s", home_directory, RF_HISTORY_FILENAME);
		}
	      else if(strcmp(optarg, OPTARG_HISTORY_FILETYPE_BASH)==0) //bash
		{
		  history_file = g_malloc(strlen(home_directory)+strlen(BASH_HISTORY_FILENAME)+2);
		  sprintf(history_file, "%s/%s", home_directory, BASH_HISTORY_FILENAME);
		}
	      else
		{
		  history_file = g_malloc(strlen(optarg)+1);
		  sprintf(history_file,"%s", optarg); //xxx
		}
	      history_set++;
	    }
	  else if(strcmp(long_options[option_index].name, OPTARG_HISTORY_LEN) ==0)
	    {
	      history_len = atol(optarg);
	    }
	  break;
	case 'b':
	  bash_shell_mode = TRUE;
	  break;
	case 'c':
	  //copy command from command line
	  if(optarg)
	    {
	      command = g_malloc(strlen(optarg)+1);
	      sprintf(command, "%s", optarg);		/* copy the string */
	    }
	  break;
	case 'd':
	  die = FALSE;
	  break;
	case 'h':
	  g_print("%s: version %s.\n%s\n", PACKAGE, VERSION, COPYRIGHT);
	  g_print("%s\n\n", LICENSE);
	  g_print("\nHELP:\n");
	  char *help = 
	    "-b, --bash\t\tRun in Bash mode (reads ~/.bashrc before execution)"
	    "\n"
	    "-c, --command=COMMAND\tSet COMMAND in entry box on startup"
	    "\n"
	    "-d, --die\t\tDo NOT die after executing a command"
	    "\n"
	    "-h, --help\t\tThis help list"
	    "\n"
	    "    --histlen=NUM\tShow NUM items from history in history list"
	    "\n"
	    "    --history=FILEPATH\tUse history file from FILEPATH"
	    "\n"
	    "-i, --nokbhit\t\tDo NOT allow keyboard hit mode (DON'T show \"HIT ANY KEY\" on exit)"
	    "\n"
	    "-k, --kbhit\t\tRun in keyboard hit mode (show \"HIT ANY KEY\" and exit)"
	    "\n"
	    "-l, --listops\t\tList default (compiled in) options and exit"
	    "\n"
	    "-o, --termstay\t\tKeep the terminal open after command exec"
	    "\n"
	    "-r, --runterm\t\tSet run_in_term mode on startup"
	    "\n"
	    "-t, --terminal=TERMPATH\tUse TERMPATH program for run_in_terminal mode"
	    "\n"
	    "-y, --keystrokes\tDisplay the keystrokes for run-free"
	    "\n"
	    "-V, --version\t\tShow version and copyright information"
	    "\n";
	  g_print("%s", help);
	  exit(0);
	  break;
	case 'i':
	  no_kbhit = TRUE;
	  break;
	case 'k':
	  gui = FALSE;
	  break;
	case 'l':
	  listops = TRUE;
	  break;
	case 'o':
	  keep_open = TRUE;
	  break;
	case 'r':
	  run_in_term = TRUE;
	  break;
	case 't':
	  if(optarg)
	    {
	      terminal_path = g_malloc(strlen(optarg)+1);
	      sprintf(terminal_path, "%s", optarg);
	    }
	  break;
	case 'y':
	  g_print("%s: version %s.\n%s\n", PACKAGE, VERSION, COPYRIGHT);
	  g_print("%s\n\n", LICENSE);
	  g_print("\nKEYSTROKES:\n");
	  g_print("%s\n",KEYSTROKES);

	  /**\todo add cleanup routines */

	  //cleanup
	  freeList(cbitems);
	  g_free(history_file);
	  g_free(home_directory);
	  g_free(command);
	  g_free(terminal_path);
	  exit(0);
	  break;
	case 'V':
	  g_print("%s: version %s.\n%s\n", PACKAGE, VERSION, COPYRIGHT);
	  g_print("%s\n\n", LICENSE);
	  exit(0);
	  break;
	default:
	  dprint("an argument is not being delt with");
	  break;
	}
    }
  

  //handle options not set
  if(!history_set)
    {
      //string terminators are accounted for
#ifdef USE_USER_HISTORY_FILENAME 
      dprint_s2("user history compile option",USER_HISTORY_FILENAME);
      history_file = g_malloc(strlen(USER_HISTORY_FILENAME)+1);
      sprintf(history_file, "%s", USER_HISTORY_FILENAME);
#else 
      dprint_s2("bash history compile option",BASH_HISTORY_FILENAME);
      history_file = g_malloc(strlen(home_directory)+strlen(BASH_HISTORY_FILENAME)+2);
      sprintf(history_file, "%s/%s", home_directory, BASH_HISTORY_FILENAME);
#endif
    }

  if(!history_len)
    history_len = DEFAULT_HISTORY_LEN;

  if(terminal_path == NULL)
    {
      terminal_path = g_malloc(strlen(DEFAULT_TERMINAL_PATH)+1);
      sprintf(terminal_path, "%s", DEFAULT_TERMINAL_PATH);
    }

  if(listops)
    {
      g_print("%s: version %s.\n%s\n", PACKAGE, VERSION, COPYRIGHT);
      g_print("%s\n\n", LICENSE);
      g_print("\n");

#ifdef USE_USER_HISTORY_FILENAME
      char *use_user_history_filename = "yes";
#else
      char *use_user_history_filename = "no";
#endif
      //list the default run-time options and exit
      g_print("debug mode \t\t\t\t=%s\n", DEBUG_MODE?"yes":"no");
      g_print("default history display length\t\t=%d\n", history_len);
      g_print("use user history file by default\t=%s\n",use_user_history_filename);
      g_print("name of default user history file: %s\n", USER_HISTORY_FILENAME);
      g_print("name of default bash history file:%s/%s\n", home_directory, BASH_HISTORY_FILENAME);
      g_print("run_in_term mode terminal path:%s\n", terminal_path);
      exit(0);
    }


  //post handle command line options 
  if(!gui)
    {
	do_kbhit();
      
      //cleanup
      freeList(cbitems);
      g_free(history_file);
      g_free(home_directory);
      g_free(command);
      g_free(terminal_path);
    }
  else
    {
      //already did this
      //gtk_set_locale ();
      //gtk_init (&argc, &argv);
    
      //create the main window
      mainWindow = create_mainWindow ();
      gtk_widget_show (mainWindow);

      //we create it but don't show it until it's needed
      fileselection = create_fileselection ();

      //set the state of the run_in_term button
      if(run_in_term)
	{
	  run_in_term = FALSE;	/* cheezy */
	  gtk_button_clicked(GTK_BUTTON(checkbutton)); 
	}

      //initialize the combo box in history mode
      //combo_init(RF_HISTORY_MODE);
      combo_init(RF_EXAMPLE_MODE);
      combo_init(RF_HISTORY_MODE);

      if(command !=NULL)
	{
	  //gtk_entry_set_text(combo_entry1, command);
	  gtk_entry_set_text(GTK_ENTRY(GTK_COMBO(combo1)->entry), command);
	  dprint_s2("startup command", command);
	}
      
      //run the program
      gtk_main ();
    }

  return 0;
}


#include <sys/types.h>
#include <unistd.h>

/** 
    \brief Internal custom "system" call

    \author Karl N. Redman

    \param command The command we want to run

    <b>
    Purpose:</b> 
    Execute the command in a way that is consistant with the
    design of run-free.
    
    \note
    This is a custom system() type call in order to handle
    environment settings properly (in the future) if this program is
    to be a setuid application (which is in the works) 
*/
void run_command(char *command)
{

  char pre[64], post[64], *buffer;

  //anything except NULL is allowed.
  if(!command)
    return;

  //populate parts of the command
  if(run_in_term)
    {
      //we want to run this in a terminal so act accordingly
      if(bash_shell_mode == TRUE)
	{
	  //endable user alias settings (i.e. ls --color)
	  strcpy(pre," -e bash -i -c \'");
	}
      else
	{
	  strcpy(pre," -e sh -c \'");
	}

      if(!no_kbhit)
	{
	  //alsways show "HIT ANY KEY"
	  if(keep_open)
	    if(bash_shell_mode == TRUE)
	      strcpy(post, ";  bash -i \'&");
	    else
	      strcpy(post, ";  sh \'&");
	  else
	    strcpy(post, "; run-free -k \'&");
	}
      else
	if(keep_open)
	    if(bash_shell_mode == TRUE)
	      strcpy(post, ";  bash -i \'&");
	    else
	      strcpy(post, ";  sh \'&");
	else
	  strcpy(post, "; \'&");
	

      //allocate a buffer
      buffer = g_malloc(strlen(terminal_path)
		      +strlen(pre)
		      +strlen(command)
		      +strlen(post)
		      +1);
      
      //populate the buffer with the command
      sprintf(buffer, "%s%s%s%s", terminal_path, pre, command, post);
    }
  else
    {
      //no terminal, we must want to just execute something in the
      //background
      strcpy(pre, "");
      strcpy(post, " &");

      //allocate a buffer
      buffer = g_malloc( +strlen(pre)
		      +strlen(command)
		      +strlen(post)
		      +1);
      
      //populate the buffer with the command
      sprintf(buffer, "%s%s%s", pre, command, post);
    }
      


  //fork the program to execute the command
  int pid = fork();

  //if we are the child...
  if(pid == 0)
    {
      //update the history file
      writeHistory(command, history_file);

      //populate the command to execute 
      char * argv[4];
      argv[0] = "sh";
      argv[1] = "-c";
      argv[2] = (char *)buffer;
      argv[3] = 0;

      /**\warning
	 NOTE: this function is a potential security problem because we are not
	 replacing the environment. if this is ever going to be a SUID
	 application then I need to handle this. I'll work on this in the
	 future -parasyte
      */
      //execute the program
      execve("/bin/sh", argv, environ);
      
      //free memory
      g_free(buffer);

      //exit properly
      exit(0);
    }
  else
    {
      g_free(buffer);

      if(die)
	{
	  //kill the main program
	  gtk_main_quit();
	}
      else
	{
	  //update the history list
	  combo_init(combo_mode);
	}
    }
}

