/*!\file commonDefs.h
  \brief common deffinitions
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

#ifndef _COMMONDEFS_H_
#define _COMMONDEFS_H_

/** @name common file names
 * names of files  
 */
//@{ 
#define RF_HISTORY_FILENAME		".run-free_history"
#define RF_DEFAULT_HISTORY_FILE_NAME	"/home/parasyte/.bash_history"
//@}

/** @name command line options
 * options allowed from the command line
 */
//@{ 
#define RF_HISTORY_FILENAME		".run-free_history"
#define OPTARG_HISTORY			"history"
#define OPTARG_HISTORY_FILETYPE_RF	"run-free"
#define OPTARG_HISTORY_FILETYPE_BASH	"bash"
#define OPTARG_HISTORY_LEN		"histlen"
//@}

#endif //_COMMONDEFS_H_

