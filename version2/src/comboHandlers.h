/*!\file comboHandlers.h
  \brief various handlers based on comboBox data
  \note This stuff will be moved to more appropriate files in the near
  future.
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

#ifndef _COMBOHANDLERS_H_
#define _COMBOHANDLERS_H_

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif


/** @name command line lengths
 *  Figure out the maximum command line lengths for the current shell
 */
//@{ 
#ifndef RF_LINE_MAX_LEN 
#ifdef RF_BIG_VALUES
#include <unistd.h>
/// use the maximum line length available
#define RF_LINE_MAX_LEN sysconf(ARG_MAX)
#else
/// use a standard line length
//#define RF_LINE_MAX_LEN 255
#define RF_LINE_MAX_LEN 1026
#endif //RF_BIG_VALUES
#endif //RF_DEFAULT_LINE_MAX_LEN
//@}

///free a GList object and all it's members
void freeList(GList *list);
///read a history file
GList *readHistory(GList *list, char *filename);
///write to a history file (append)
int writeHistory(char *command, char *filename);

#endif //_COMBOHANDLERS_H_
