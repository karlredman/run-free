/*!\file callbacks.h
  \brief callback functions for the application
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
#ifndef _CALLBACKS_H_
#define _CALLBACKS_H_


void
on_mainWindow_destroy                  (GtkObject       *object,
                                        gpointer         user_data);

void
on_combo_entry1_changed                (GtkEditable     *editable,
                                        gpointer         user_data);

gboolean
on_combo_entry1_key_press_event        (GtkWidget       *widget,
                                        GdkEventKey     *event,
                                        gpointer         user_data);

gboolean
on_combo_key_press_event        (GtkWidget       *widget,
                                        GdkEventKey     *event,
                                        gpointer         user_data);

void
on_browseButton_clicked                (GtkButton       *button,
                                        gpointer         user_data);

void
on_checkbutton_toggled                 (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_ok_button1_clicked                  (GtkButton       *button,
                                        gpointer         user_data);

void
on_cancel_button1_clicked              (GtkButton       *button,
                                        gpointer         user_data);

gboolean
on_fileselection_key_press_event       (GtkWidget       *widget,
                                        GdkEventKey     *event,
                                        gpointer         user_data);

gboolean
on_mainWindow_key_press_event          (GtkWidget       *widget,
                                        GdkEventKey     *event,
                                        gpointer         user_data);
void
on_runButton_clicked			(GtkButton       *button,
					 gpointer         user_data);

void
on_optionsButton_clicked               (GtkButton       *button,
                                        gpointer         user_data);

void
on_whoEntry_activate                   (GtkEditable     *editable,
                                        gpointer         user_data);

void
on_passwordEntry_activate              (GtkEditable     *editable,
                                        gpointer         user_data);

void
on_whoEntry_grab_focus                 (GtkWidget       *widget,
                                        gpointer         user_data);

void
on_passwordEntry_grab_focus            (GtkWidget       *widget,
                                        gpointer         user_data);

void handle_options_display();

gboolean
on_fileselection_delete_event          (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data);

///calculate the combo box positions
static void //MOVE THIS
gtk_combo_get_pos (GtkCombo * combo,
                   gint * x,
                   gint * y,
                   gint * height,
                   gint * width);

///handle a dialog ok button click
void
dialog_ok_clicked	                (GtkButton       *button,
                                        gpointer         user_data);
#endif //_CALLBACKS_H_
