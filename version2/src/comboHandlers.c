/*!\file comboHandlers.c
  \brief Handle comboBox operations

  The functions here are somewhat misplaced for now. I'll fix this in
  run-free 3.0. Basically, the idea is that we are trying to handle
  functionality that is based on the values of the combo box.
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>

#include <config.h>

#include "main.h"
#include "comboHandlers.h"
#include "debug.h"


//############## FUNCTION definition
/** 
    \brief Read the history file.

    \author Karl N. Redman

    \param list A list to populate (must be NULL) -probably
    superfluious.
    \param filename The filename of the file to read from

    \return A populated GList.

    \par Purpose:
    Read a history file and populate a GList with it's data. The list
    is populated in reverse of the file contents to accomidate for
    (only) a file that is appended to.
*/
GList *readHistory(GList *list, char *filename)
{
  FILE *fp;

  /** \warning This caused alot of headeache. In the first place, gtk
    GList operations are not intuitive at all. In the end it was
    discovered that, because the values of the glist are pointers,
    that we must use a persistant glist to populate our target
    glist. What this means is that we end up passing in and returning
    the same pointer (not the same address) in order to properly
    populate our GList.
  */

  //grab the environment $HOME directory
  //TODO
  if( (fp = fopen(filename, "a+") ) == NULL)
    {
      dprint("run-free: bash_history file not found");
      
      /**\todo
	 we are not handling file operations properly here -I was
	 probably tired and lazy at the time. This MUST be fixed in
	 the near future!
       */

      //ok, try a different file
      //TODO
      //else pop up a dialog
      g_print("could not open history file\n");
    }

  //max line length is the system max (this could be huge!)
  char line[RF_LINE_MAX_LEN+1];
  int c;
  int i =0, numItems =0;
  //char *string;

  memset(line, '\0', sizeof(line));

  do
    {
      if( (c = fgetc(fp)) == EOF)
	{
	  //dprint("end of file\n");
	  break;
	}
      if(c != '\n')
	{
	  if(i >= RF_LINE_MAX_LEN)
	    dprint("HISTORY LINE LEN TOO LONG!\n");

	  line[i] = c;
	  i++;
	  continue;
	}
      else
	{
	  i=0;
	  if(strcmp(line, "\n") == 0)
	    {
	      memset(line, '\0', sizeof(line));
	      continue;
	    }
	}

      list = g_list_prepend(list, strdup(line));
      numItems++;

      memset(line, '\0', sizeof(line));
    }while(1);

  fclose(fp);

  //list = g_list_reverse(list);

  //eliminate duplicates
  GList *newList = NULL;

  i=0;

  //this is how we set the combo box length
  //int loop_num = RF_MAX_HISTLIST_LEN-1;
  int loop_num = history_len -1;

  //weed out duplicates and only keep the first instance of a history
  //line
  for(;i < loop_num && (list != NULL); i++, 
	list = g_list_next(list))
	{

	  //see if we've seen this one before
	   if(g_list_find_custom(newList, list->data,
				 (GCompareFunc)strcmp) == NULL) 
	    {
	      //put the old command in the combo box
	      newList = g_list_append(newList, (char *)list->data);
	    }
	   else
	     {
	       //increase the number of loops we're going to try and
	       // grab the next one (unless NULL happens on next)
	       ++loop_num;
	     }
	}//end for

  newList = g_list_prepend(newList, "");
  return(newList);
}

/** 
    \brief Free up a GList and all it's members.

    \author Karl N. Redman

    \param list A pointer to a GList to be freed

    \par Purpose:
    Frees the points in the GList and then the GList pointer itself.
*/
void freeList(GList *list)
{
  int i =0;
  for(; i < (int)g_list_length(list); i++, list = list->next)
    g_free(list->data);
  
  g_list_free(list);
}


/** 
    \brief write a history file.

    \author Karl N. Redman

    \param command the command to append to the file
    \param filename the file to append the command to

    \par
    Purpose:
    Appends the command to the end of the file
*/
int writeHistory(char *command, char *filename)
{
  //always writes to the end of the file

  FILE *fp;
  int retval = 0;
  int wLen = 0;

  
  fp = fopen(filename, "a+");
  if(fp == NULL)
    {
      /**\todo FIX THIS I'm not handling file operations properly
      -probably tired at the time... -parasyte.
      */
      //display dialog
    }

  //write command line to file
  if((wLen = fputs(command, fp)) > 0)
    {
      retval = -1;
    }
  //else write a new line
   fputs("\n", fp);

  fclose(fp);			// close file

  return retval;
}
