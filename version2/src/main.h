/*!\file main.h
  \brief run-free main include file

  run-free is a command line launching program written in gtk. This
  version of run-free is written is C for gtk+1.2
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

#ifndef _MAIN_H_
#define _MAIN_H_

/* GLOBALS:
   yes, they're GLOBAL -this is C not C++
*/

/** @name Global Switches
 *  Switches used throughout the program
 */
//@{ 
gboolean run_in_term;		/*!< toggle run_in_term checkbox */
gboolean die;			/*!< do not die unles killed */
gboolean no_kbhit;		/*!< do not allow kbhit */
gboolean keep_open;		/*!< keep the terminal open */
//@}

/** @name Global Parameters
 *  common GLOBAL parameters 
 */
//@{ 
char *home_directory;		/*!< the home directory */
char *history_file;		/*!< the history file */
int history_len;		/*!< the history length */
char *terminal_path;		/*!< this is the path to a terminal program*/

/*! the command line entered in the entry box */
char *command;

/*! execute bash in interactive mode  */
gboolean bash_shell_mode;
//@}

///Run a command
void run_command(char *command);

#endif // _MAIN_H_
