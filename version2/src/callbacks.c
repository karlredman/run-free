/*!\file callbacks.c
  \brief callback function deffinitions
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

#include <gtk/gtk.h>
#include <gtk/gtkcombo.h>
#include <gdk/gdkkeysyms.h>

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

#include "callbacks.h"
#include "interface.h"
#include "support.h"

#include "comboHandlers.h"
#include "comboBox.h"
#include "main.h"

/// whether the "options" box is up (disabled)
gboolean vbox2Up = FALSE;

/** 
    \brief called when the main window is destroyed

    \author Karl N. Redman

    \par Purpose: 
    	cleans up before exiting
*/
void
on_mainWindow_destroy                  (GtkObject       *object,
                                        gpointer         user_data)
{
  //cleanup
  freeList(cbitems);
  g_free(history_file);
  g_free(home_directory);
  g_free(command);
  g_free(terminal_path);

  //die
  gtk_main_quit();
}


void
on_combo_entry1_changed                (GtkEditable     *editable,
                                        gpointer         user_data)
{

}

gboolean 
on_combo_key_press_event		(GtkWidget       *widget,
                                        GdkEventKey     *event,
                                        gpointer         user_data)
{
  return TRUE;
}

/** 
    \brief handle when a keypress event occures in the combo box.

    \author Karl N. Redman

    \note
    This is a lengthy function for now. run-free 3.0 will handle this
    better in the futue. For now we just handle the common
    functionality of the application from here
*/
gboolean
on_combo_entry1_key_press_event        (GtkWidget       *widget,
                                        GdkEventKey     *event,
                                        gpointer         user_data)
{
  //save the previous key press (for control chars)
  static unsigned int prevKey =0;

  if(event->keyval == GDK_Return ||
     event->keyval == GDK_KP_Enter) // run command
    {
      if(strcmp(gtk_entry_get_text(GTK_ENTRY( GTK_COMBO(combo1)->entry)), "") !=0 &&
	 gtk_entry_get_text(GTK_ENTRY( GTK_COMBO(combo1)->entry)) != NULL)
	{
	  writeHistory(gtk_entry_get_text(GTK_ENTRY( GTK_COMBO(combo1)->entry)), history_file);
	  run_command(gtk_entry_get_text(GTK_ENTRY( GTK_COMBO(combo1)->entry)));

	  gtk_widget_grab_focus(GTK_WIDGET(GTK_COMBO (combo1)->entry));
	}
      return TRUE;
    }
  else if(event->keyval == GDK_u)
    {
      if(prevKey == GDK_Alt_L || prevKey == GDK_Alt_R)
	{
	  if(die)
	    die=FALSE;
	  else
	    die=TRUE;
	}
      }
  else if(event->keyval == GDK_y)
    {
      if(prevKey == GDK_Alt_L || prevKey == GDK_Alt_R)
	{
	  if(keep_open)
	    keep_open=FALSE;
	  else
	    keep_open=TRUE;
	}
      }
  else if(event->keyval == GDK_h)
    {
      if(prevKey == GDK_Alt_L || prevKey == GDK_Alt_R)
	{
	  keystrokes_dialog();
	}
      }
  if(event->keyval == GDK_space)
  {
      if(prevKey == GDK_Control_L || prevKey == GDK_Control_R ||
	prevKey == GDK_Alt_L || prevKey == GDK_Alt_R)
	{
	  gint x =0, y =0, 
	    height =0, width =0, 
	    old_height =0, old_width =0; 

	  //we have to grab the combo position
	  gtk_combo_get_pos(GTK_COMBO(combo1), &x, &y, &height, &width);

	  //see if we have the focus
	  if (!GTK_WIDGET_HAS_FOCUS (GTK_COMBO(combo1)->entry))
	    gtk_widget_grab_focus (GTK_COMBO(combo1)->entry);
	  
	  //deliver all events to the popwin
	  gtk_grab_add (GTK_COMBO(combo1)->popwin);

	  //grab ponter (mouse) and all other events
	  gdk_pointer_grab (GTK_COMBO(combo1)->popwin->window, TRUE,
			    GDK_BUTTON_PRESS_MASK | 
			    GDK_BUTTON_RELEASE_MASK |
			    GDK_POINTER_MOTION_MASK, 
			    NULL, NULL, GDK_CURRENT_TIME);

	  /* I don't know why this is being evil but the widget needs
	     to be resized...
	   */
	  if (width != old_width || height != old_height)
	    {
	      gtk_widget_hide (GTK_SCROLLED_WINDOW
			       (GTK_COMBO(combo1)->popup)->hscrollbar);

	      gtk_widget_hide (GTK_SCROLLED_WINDOW
			       (GTK_COMBO(combo1)->popup)->vscrollbar);
	    }
	  
	  //set the position of the listbox
	  gtk_widget_set_uposition (GTK_COMBO(combo1)->popwin, x, y);
	  gtk_widget_set_usize (GTK_COMBO(combo1)->popwin, width, height);
	  gtk_widget_realize (GTK_COMBO(combo1)->popwin);
	  gdk_window_resize (GTK_COMBO(combo1)->popwin->window, width, height);
	  
	  gtk_widget_show(GTK_COMBO(combo1)->popwin);
	}
      return FALSE;
  } 
  else
    if(event->keyval == GDK_Control_L || event->keyval == GDK_Control_R ||
       event->keyval == GDK_Alt_L || event->keyval ==GDK_Alt_R)
      prevKey = event->keyval;
    else
      prevKey = 0;
    
  return FALSE;
}


void
on_browseButton_clicked                (GtkButton       *button,
                                        gpointer         user_data)
{
  gtk_widget_show (fileselection);
}


/** 
    \brief handle setting the run_in_term mode

    \author Karl N. Redman

    \par Purpose: 
    	Toggle between run_in_term and normal (exit) modes of
    operation
*/
void
on_checkbutton_toggled                 (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
  if(!run_in_term)
    run_in_term = TRUE;
  else
    run_in_term = FALSE;
}


/** 
    \brief Handle the OK button clicked in the fileselection dialog.

    \author Karl N. Redman

    \par Purpose: 
    	Sets the combo box entry and hides the fileselection
    dialog.
*/
void
on_ok_button1_clicked                  (GtkButton       *button,
                                        gpointer         user_data)
{
  //space and null are the +1's
  char s[strlen(gtk_entry_get_text(GTK_ENTRY( GTK_COMBO(combo1)->entry)))
	 +1 
	 + strlen( gtk_file_selection_get_filename(GTK_FILE_SELECTION(fileselection)))
	 +1]; 
  
  //set the combo box string
  sprintf(s, "%s %s", gtk_entry_get_text(GTK_ENTRY( GTK_COMBO(combo1)->entry)), gtk_file_selection_get_filename(GTK_FILE_SELECTION(fileselection)));

  //set the entry
  gtk_entry_set_text(GTK_ENTRY( GTK_COMBO(combo1)->entry), s);

  //hide the file dialog
  gtk_widget_hide (fileselection);

  /**\todo 
     clear the file selection by stripping off the file name ?
   */
  
}


void
on_cancel_button1_clicked              (GtkButton       *button,
                                        gpointer         user_data)
{
  gtk_widget_hide (fileselection);
}


gboolean
on_fileselection_key_press_event       (GtkWidget       *widget,
                                        GdkEventKey     *event,
                                        gpointer         user_data)
{
  if(event->keyval == GDK_Escape) // quit
    {
      //cancel operations
      gtk_button_clicked(GTK_BUTTON(GTK_FILE_SELECTION(widget)->cancel_button));
    }
  return FALSE;
}


/** 
    \brief Handle a keypress event at the toplevel window level

    \author Karl N. Redman

    \par Purpose: 
    	Takes care of default keystrokes (closing the App. etc.).
*/
gboolean
on_mainWindow_key_press_event          (GtkWidget       *widget,
                                        GdkEventKey     *event,
                                        gpointer         user_data)
{
  static unsigned int prevKey =0;

  //return on_combo_entry1_key_press_event(widget, event, user_data);
  if(event->keyval == GDK_Escape) // quit
    {
      //cancel operations -"destroy"
      gtk_main_quit();
    }
  else if(event->keyval ==GDK_c)
    {
      gtk_widget_grab_focus(GTK_WIDGET(GTK_COMBO (combo1)->entry));
    }
  else if(event->keyval == GDK_m) // history mode -should be anaccelerator
    {
      if(prevKey == GDK_Control_L || prevKey == GDK_Control_R)
	{
	  if(combo_mode < RF_MAX_MODE)
	    combo_mode++;
	  else if(combo_mode >= RF_MAX_MODE)
	    combo_mode = RF_HISTORY_MODE;
	
	  combo_init(combo_mode);
	}
    }
  else if(event->keyval == GDK_h)
    {
      if(prevKey == GDK_Alt_L || prevKey == GDK_Alt_R)
	{
	  keystrokes_dialog();
	}
      }
  else
    if(event->keyval == GDK_Control_L || event->keyval == GDK_Control_R)
      prevKey = event->keyval;
    else
      prevKey = 0;
  return FALSE;
}

/** 
    \brief Execute the command in the combo entry box.

    \author Karl N. Redman

    \par Purpose: 
    	Write to the history file and execute the command in the
    entry box.
*/
void
on_runButton_clicked			(GtkButton       *button,
					 gpointer         user_data)
{
  if(strcmp(gtk_entry_get_text(GTK_ENTRY( GTK_COMBO(combo1)->entry)), "") !=0 &&
     gtk_entry_get_text(GTK_ENTRY( GTK_COMBO(combo1)->entry)) != NULL)
    {
      writeHistory(gtk_entry_get_text(GTK_ENTRY( GTK_COMBO(combo1)->entry)), history_file);
      run_command(gtk_entry_get_text(GTK_ENTRY( GTK_COMBO(combo1)->entry)));
    }
}

/** 
    \brief Handle the options mode selection

    \author Karl N. Redman

    \par Purpose: 
    	Resize the main window and display the options allowed by
    the options mode of operation.
*/
void
on_optionsButton_clicked               (GtkButton       *button,
                                        gpointer         user_data)
{
  //TODO (this needs to be made more intuitive!!!)
  static gboolean up = TRUE;

  /*! \note in order to resize the window we have to mess with the
    window policy of the mainWindow. This is pretty clumbsy here.
  */
  if(up)
    gtk_window_set_policy (GTK_WINDOW (mainWindow), FALSE, FALSE, FALSE);
  else
    gtk_window_set_policy (GTK_WINDOW (mainWindow), FALSE, FALSE, TRUE);

  handle_options_display();
  gtk_window_set_policy (GTK_WINDOW (mainWindow), TRUE, TRUE, TRUE);

  if(up)
    up=TRUE;
  else
    up=FALSE;
}
/** 
    \brief Handle options display

    \author Karl N. Redman

    \par Purpose: 
    	Handle mainWindow resizing when Options are desired
*/
void handle_options_display()
{
  if(vbox2Up)
    {
      int x;
      int y;

      ///set the focus to the combo box
      gtk_widget_grab_focus(GTK_WIDGET(GTK_COMBO (combo1)->entry));
      
      ///hide the vbox
      gtk_widget_hide (vbox2);

      /// resize the main window
      gdk_window_get_origin(mainWindow->window, &x, &y);
      gdk_window_move (mainWindow->window, x, y);
      
      //set the flag
      vbox2Up = FALSE;
    }
  else
    {
      //show the vbox
      gtk_widget_show (vbox2);
      vbox2Up = TRUE;
    }
}


void
on_whoEntry_grab_focus                 (GtkWidget       *widget,
                                        gpointer         user_data)
{
  if(!vbox2Up)
    handle_options_display();
}


void
on_passwordEntry_grab_focus            (GtkWidget       *widget,
                                        gpointer         user_data)
{
  if(!vbox2Up)
    handle_options_display();
}

gboolean
on_fileselection_delete_event          (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data)
{
  gtk_widget_hide (fileselection);
  return TRUE;
}




#define EMPTY_LIST_HEIGHT   (15)
/** 
    \brief figure out the combo box positions

    \author NOT ME! whoever wrote gtkhacks...
    
    \warning This function is "borrowed" from gtkhacks of glade (i think)
    
    
    \par Purpose: 
    grab the position of the combo box
    
    \todo 
    REDO THIS FUNCTION! This function is not mine! (see gtkhacks)
	
*/

static void
gtk_combo_get_pos (GtkCombo * combo,
                   gint * x,
                   gint * y,
                   gint * height,
                   gint * width)
{
        GtkBin *popwin;
        GtkWidget *widget;
        GtkScrolledWindow *popup;

        gint real_height;
        GtkRequisition list_requisition;
        gboolean show_hscroll = FALSE;
        gboolean show_vscroll = FALSE;
        gint avail_height;
        gint min_height;
        gint alloc_width;
        gint work_height;
        gint old_height;
        gint old_width;

        widget = GTK_WIDGET(combo);
        popup  = GTK_SCROLLED_WINDOW (combo->popup);
        popwin = GTK_BIN (combo->popwin);

        gtk_widget_realize(GTK_WIDGET(combo->entry));
        gdk_window_get_origin (combo->entry->window, x, y);
        real_height = MIN (combo->entry->requisition.height,
                           combo->entry->allocation.height);
        *y += real_height;
        avail_height = gdk_screen_height () - *y;

        gtk_widget_size_request (combo->list, &list_requisition);
        min_height = MIN (list_requisition.height,
                          popup->vscrollbar->requisition.height);
        if (!GTK_LIST (combo->list)->children)
                list_requisition.height += EMPTY_LIST_HEIGHT;

        alloc_width = (widget->allocation.width -
             2 * popwin->child->style->klass->xthickness -
             2 * GTK_CONTAINER (popwin->child)->border_width -
             2 * GTK_CONTAINER (combo->popup)->border_width -
             2 * GTK_CONTAINER (GTK_BIN (popup)->child)->border_width -
             2 * GTK_BIN (popup)->child->style->klass->xthickness);

        work_height = (2 * popwin->child->style->klass->ythickness +
             2 * GTK_CONTAINER (popwin->child)->border_width +
             2 * GTK_CONTAINER (combo->popup)->border_width +
             2 * GTK_CONTAINER (GTK_BIN (popup)->child)->border_width +
             2 * GTK_BIN (popup)->child->style->klass->xthickness);

        do {
                old_width = alloc_width;
                old_height = work_height;

                if (!show_hscroll &&
                    alloc_width < list_requisition.width) {
                          work_height += popup->hscrollbar->requisition.height
                                         + GTK_SCROLLED_WINDOW_CLASS
                                           (GTK_OBJECT (combo->popup)->klass)->scrollbar_spacing;
                          show_hscroll = TRUE;
                }
            if (!show_vscroll &&
                work_height + list_requisition.height > avail_height) {
                    if (work_height + min_height > avail_height &&
                        *y - real_height > avail_height) {
                                *y -= (work_height +
                                       list_requisition.height +
                                       real_height);
                                break;
                    }
                    alloc_width -= popup->vscrollbar->requisition.width +
                                   GTK_SCROLLED_WINDOW_CLASS
                                  (GTK_OBJECT (combo->popup)->klass)->scrollbar_spacing;
                    show_vscroll = TRUE;
            }
        } while (old_width != alloc_width || old_height != work_height);

        *width = widget->allocation.width;
        if (show_vscroll)
                *height = avail_height;
        else
                *height = work_height + list_requisition.height;

        if (*x < 0)
                *x = 0;
}

void
dialog_ok_clicked	                (GtkButton       *button,
                                        gpointer         user_data)
{
  gtk_widget_destroy(GTK_WIDGET(user_data));
}
