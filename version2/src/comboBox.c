/*!\file comboBox.c
  \brief Provide comboBox functionality
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

#include <gtk/gtk.h>
#include "comboBox.h"
#include "comboHandlers.h"
#include "interface.h"
#include "main.h"


/** 
    \brief Initialize the combo box.

    \author Karl N. Redman

    \param mode The mode we want to initialize to.

    \par Purpose: 
    	This function is a bit misleading right now. What we want
    to accomplish is the setting of the values of the combo box list
    based on various predefined modes of operation.
*/
int combo_init(unsigned int mode)
{
  /**
     \note We use GLists because we can easily use the convenience function,
     gtk_combo_set_popdown_strings(GTK_COMBO(combo), (GList *)aGList)
     for this kind of data (text only).
  */

  /** \warning
      The stuff in this function is a workaround for lack of gtk+1.2
      combobox functionality. The next version of gtk+ looks to have
      solved some of the problems we're working around here.
  */

  ///the persistant history list
  //static GList *hist_list = NULL;
  //static GList *exec_list = NULL;
  //static GList *file_list = NULL;

  if((unsigned int)mode == RF_EXAMPLE_MODE)
    {
      /* we're going to change the contents of the combo box list so
	 we need to delete the old contents and populate it with
	 something else. 
      */

      /**
	 \note
	 Note: This is a gtk+1.2 method and, I'm told, doesn't work
	 for gtk+2+ (I'll find out I guess)
      */

      GtkList *oldList = NULL;
      
      //get the current list
      //we could save this if we wanted to.
      oldList = (GtkList *)GTK_COMBO(combo1)->list;
      
      //remove each item in the GTK_LIST
      if (GTK_LIST(oldList)->children != NULL)
	gtk_list_remove_items (oldList, (GList *)oldList->children);

      //repopulate the list
      GList *list = NULL;
      list = g_list_append(list, "");
      list = g_list_append(list, "1");
      list = g_list_append(list, "2");
      list = g_list_append(list, "3");
      list = g_list_append(list, "4");

      //save a pointer to the list ?
      cbitems = list;

      //populate the combo box list widget
      gtk_combo_set_popdown_strings(GTK_COMBO(combo1), (GList *)cbitems);

      //a settingthat doesn't really go here
      gtk_combo_set_use_arrows_always(GTK_COMBO(combo1), 1);
    }

  
  if((unsigned int)mode == RF_HISTORY_MODE)
    {
      GtkList *oldList = NULL;

      oldList = (GtkList *)GTK_COMBO(combo1)->list;
      
      if (GTK_LIST(oldList)->children != NULL)
	gtk_list_remove_items (oldList, (GList *)oldList->children);

      cbitems = NULL;
      //cbitems = g_list_append(cbitems, "");
      //cbitems = g_list_append(cbitems, "a");
      //cbitems = g_list_append(cbitems, "b");
      //cbitems = g_list_append(cbitems, "c");
      //cbitems = g_list_append(cbitems, "d");
      //cbitems = g_list_append(cbitems, "e");
      //cbitems = g_list_append(cbitems, "f");
      
      cbitems = readHistory(cbitems, history_file);
      gtk_combo_set_popdown_strings(GTK_COMBO(combo1), (GList *)cbitems);
      gtk_combo_set_use_arrows_always(GTK_COMBO(combo1), 1);
    }

  return 0;
}
