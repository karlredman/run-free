/*!\file interface.c
  \brief Interface function definitions.
  This file was originally created by glade
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

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

#include <gdk/gdkkeysyms.h>
#include <gtk/gtk.h>

#include "callbacks.h"
#include "interface.h"
#include "support.h"
#include "main.h"
#include "debug.h"
#include "help.h"

GtkWidget*
create_mainWindow (void)
{
  GtkWidget *mainWindow;
  GtkWidget *vbox1;
  GtkWidget *hbox1;
  //GtkWidget *combo1;
  GtkWidget *combo_entry1;
  guint browseButton_key;
  GtkWidget *browseButton;
  GtkWidget *hbox2;
  guint checkbutton_key;
  //GtkWidget *checkbutton;
  guint optionsButton_key;
  GtkWidget *optionsButton;
  guint runButton_key;
  GtkWidget *runButton;
  //GtkWidget *vbox2;
  GtkWidget *hbox3;
  guint label1_key;
  GtkWidget *label1;
  GtkWidget *whoEntry;
  GtkWidget *hbox4;
  guint label2_key;
  GtkWidget *label2;
  GtkWidget *passwordEntry;
  GtkAccelGroup *accel_group;

  accel_group = gtk_accel_group_new ();

  mainWindow = gtk_window_new (GTK_WINDOW_TOPLEVEL);

  //set the policy for resizeing
  //gtk_window_set_policy (GTK_WINDOW (mainWindow), FALSE, FALSE, FALSE);

  gtk_object_set_data (GTK_OBJECT (mainWindow), "mainWindow", mainWindow);
  gtk_window_set_title (GTK_WINDOW (mainWindow), "run-free");

  vbox1 = gtk_vbox_new (FALSE, 0);
  gtk_widget_ref (vbox1);
  gtk_object_set_data_full (GTK_OBJECT (mainWindow), "vbox1", vbox1,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (vbox1);
  gtk_container_add (GTK_CONTAINER (mainWindow), vbox1);

  hbox1 = gtk_hbox_new (FALSE, 0);
  gtk_widget_ref (hbox1);
  gtk_object_set_data_full (GTK_OBJECT (mainWindow), "hbox1", hbox1,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (hbox1);
  gtk_box_pack_start (GTK_BOX (vbox1), hbox1, TRUE, TRUE, 0);

  combo1 = gtk_combo_new ();
  gtk_widget_ref (combo1);
  gtk_object_set_data_full (GTK_OBJECT (mainWindow), "combo1", combo1,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (combo1);
  gtk_box_pack_start (GTK_BOX (hbox1), combo1, TRUE, TRUE, 0);

  combo_entry1 = GTK_COMBO (combo1)->entry;
  gtk_widget_ref (combo_entry1);
  gtk_object_set_data_full (GTK_OBJECT (mainWindow), "combo_entry1", combo_entry1,
                            (GtkDestroyNotify) gtk_widget_unref);

  gtk_widget_show (combo_entry1);

  gtk_combo_set_use_arrows_always(GTK_COMBO(combo1), 1);

  browseButton = gtk_button_new_with_label ("");
  browseButton_key = gtk_label_parse_uline (GTK_LABEL (GTK_BIN (browseButton)->child),
                                   "Bro_wse");
  gtk_widget_add_accelerator (browseButton, "clicked", accel_group,
                              browseButton_key, GDK_MOD1_MASK, (GtkAccelFlags) 0);
  gtk_widget_ref (browseButton);
  gtk_object_set_data_full (GTK_OBJECT (mainWindow), "browseButton", browseButton,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (browseButton);
  gtk_box_pack_start (GTK_BOX (hbox1), browseButton, FALSE, FALSE, 0);
  gtk_widget_set_usize (browseButton, 49, -2);

  hbox2 = gtk_hbox_new (FALSE, 9);
  gtk_widget_ref (hbox2);
  gtk_object_set_data_full (GTK_OBJECT (mainWindow), "hbox2", hbox2,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (hbox2);
  gtk_box_pack_start (GTK_BOX (vbox1), hbox2, TRUE, TRUE, 0);

  checkbutton = gtk_check_button_new_with_label ("");
  checkbutton_key = gtk_label_parse_uline (GTK_LABEL (GTK_BIN (checkbutton)->child),
                                   "Run in _Terminal");
  gtk_widget_add_accelerator (checkbutton, "clicked", accel_group,
                              checkbutton_key, GDK_MOD1_MASK, (GtkAccelFlags) 0);
  gtk_widget_ref (checkbutton);
  gtk_object_set_data_full (GTK_OBJECT (mainWindow), "checkbutton", checkbutton,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (checkbutton);
  gtk_box_pack_start (GTK_BOX (hbox2), checkbutton, FALSE, FALSE, 0);

  /**\note The options button and functionality is not implimented in
     this version of run-free
  */
  optionsButton = gtk_button_new_with_label ("");
  optionsButton_key = gtk_label_parse_uline (GTK_LABEL (GTK_BIN (optionsButton)->child),
                                   "_Options");
  //gtk_widget_add_accelerator (optionsButton, "clicked", accel_group,
                              //optionsButton_key, GDK_MOD1_MASK, (GtkAccelFlags) 0);
  gtk_widget_ref (optionsButton);
  gtk_object_set_data_full (GTK_OBJECT (mainWindow), "optionsButton", optionsButton,
                            (GtkDestroyNotify) gtk_widget_unref);
  //gtk_widget_show (optionsButton);
  gtk_box_pack_start (GTK_BOX (hbox2), optionsButton, FALSE, FALSE, 0);

  runButton = gtk_button_new_with_label ("");
  runButton_key = gtk_label_parse_uline (GTK_LABEL (GTK_BIN (runButton)->child),
                                   "_Run");
  gtk_widget_add_accelerator (runButton, "clicked", accel_group,
                              runButton_key, GDK_MOD1_MASK, (GtkAccelFlags) 0);
  gtk_widget_ref (runButton);
  gtk_object_set_data_full (GTK_OBJECT (mainWindow), "runButton", runButton,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (runButton);
  gtk_box_pack_start (GTK_BOX (hbox2), runButton, FALSE, FALSE, 0);

  /**\todo
     make sure that the runButton fits if the options button is
     re-added
  */
  //gtk_widget_set_usize (runButton, 49, -2);
  gtk_widget_set_usize (runButton, 103, -2);

  vbox2 = gtk_vbox_new (FALSE, 0);
  gtk_widget_ref (vbox2);
  gtk_object_set_data_full (GTK_OBJECT (mainWindow), "vbox2", vbox2,
                            (GtkDestroyNotify) gtk_widget_unref);

  //don't show the second vbox until we're ready
  //gtk_widget_show (vbox2);

  gtk_box_pack_start (GTK_BOX (vbox1), vbox2, TRUE, TRUE, 0);

  hbox3 = gtk_hbox_new (FALSE, 14);
  gtk_widget_ref (hbox3);
  gtk_object_set_data_full (GTK_OBJECT (mainWindow), "hbox3", hbox3,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (hbox3);
  gtk_box_pack_start (GTK_BOX (vbox2), hbox3, TRUE, TRUE, 0);

  label1 = gtk_label_new ("");
  label1_key = gtk_label_parse_uline (GTK_LABEL (label1),
                                   "Run _As");
  gtk_widget_ref (label1);
  gtk_object_set_data_full (GTK_OBJECT (mainWindow), "label1", label1,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (label1);
  gtk_box_pack_start (GTK_BOX (hbox3), label1, FALSE, FALSE, 0);

  whoEntry = gtk_entry_new ();
  gtk_widget_ref (whoEntry);
  gtk_object_set_data_full (GTK_OBJECT (mainWindow), "whoEntry", whoEntry,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (whoEntry);
  gtk_box_pack_start (GTK_BOX (hbox3), whoEntry, TRUE, TRUE, 0);

  hbox4 = gtk_hbox_new (FALSE, 0);
  gtk_widget_ref (hbox4);
  gtk_object_set_data_full (GTK_OBJECT (mainWindow), "hbox4", hbox4,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (hbox4);
  gtk_box_pack_start (GTK_BOX (vbox2), hbox4, TRUE, TRUE, 0);

  label2 = gtk_label_new ("");
  label2_key = gtk_label_parse_uline (GTK_LABEL (label2),
                                   "Pa_ssword");
  gtk_widget_ref (label2);
  gtk_object_set_data_full (GTK_OBJECT (mainWindow), "label2", label2,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (label2);
  gtk_box_pack_start (GTK_BOX (hbox4), label2, FALSE, FALSE, 0);

  passwordEntry = gtk_entry_new ();
  gtk_widget_ref (passwordEntry);
  gtk_object_set_data_full (GTK_OBJECT (mainWindow), "passwordEntry", passwordEntry,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (passwordEntry);
  gtk_box_pack_start (GTK_BOX (hbox4), passwordEntry, TRUE, TRUE, 0);
  gtk_entry_set_visibility (GTK_ENTRY (passwordEntry), FALSE);

  gtk_signal_connect (GTK_OBJECT (mainWindow), "destroy",
                      GTK_SIGNAL_FUNC (on_mainWindow_destroy),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (mainWindow), "key_press_event",
                      GTK_SIGNAL_FUNC (on_mainWindow_key_press_event),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (combo_entry1), "changed",
                      GTK_SIGNAL_FUNC (on_combo_entry1_changed),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (combo1), "key_press_event",
                      GTK_SIGNAL_FUNC (on_combo_key_press_event),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (combo_entry1), "key_press_event",
                      GTK_SIGNAL_FUNC (on_combo_entry1_key_press_event),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (browseButton), "clicked",
                      GTK_SIGNAL_FUNC (on_browseButton_clicked),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (checkbutton), "toggled",
                      GTK_SIGNAL_FUNC (on_checkbutton_toggled),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (optionsButton), "clicked",
                      GTK_SIGNAL_FUNC (on_optionsButton_clicked),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (runButton), "clicked",
                      GTK_SIGNAL_FUNC (on_runButton_clicked),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (whoEntry), "grab_focus",
                      GTK_SIGNAL_FUNC (on_whoEntry_grab_focus),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (passwordEntry), "grab_focus",
                      GTK_SIGNAL_FUNC (on_passwordEntry_grab_focus),
                      NULL);

  gtk_widget_add_accelerator (whoEntry, "grab_focus", accel_group,
                              label1_key, GDK_MOD1_MASK, (GtkAccelFlags) 0);
  gtk_widget_add_accelerator (passwordEntry, "grab_focus", accel_group,
                              label2_key, GDK_MOD1_MASK, (GtkAccelFlags) 0);

  gtk_combo_disable_activate(GTK_COMBO(combo1));
  gtk_widget_grab_focus (combo_entry1);


  gtk_window_add_accel_group (GTK_WINDOW (mainWindow), accel_group);

  return mainWindow;
}

GtkWidget*
create_fileselection (void)
{
  GtkWidget *fileselection;
  GtkWidget *ok_button1;
  GtkWidget *cancel_button1;

  fileselection = gtk_file_selection_new ("Select File");
  gtk_object_set_data (GTK_OBJECT (fileselection), "fileselection", fileselection);
  gtk_container_set_border_width (GTK_CONTAINER (fileselection), 10);

  ok_button1 = GTK_FILE_SELECTION (fileselection)->ok_button;
  gtk_object_set_data (GTK_OBJECT (fileselection), "ok_button1", ok_button1);
  gtk_widget_show (ok_button1);
  GTK_WIDGET_SET_FLAGS (ok_button1, GTK_CAN_DEFAULT);

  cancel_button1 = GTK_FILE_SELECTION (fileselection)->cancel_button;
  gtk_object_set_data (GTK_OBJECT (fileselection), "cancel_button1", cancel_button1);
  gtk_widget_show (cancel_button1);
  GTK_WIDGET_SET_FLAGS (cancel_button1, GTK_CAN_DEFAULT);

  //gtk_signal_connect (GTK_OBJECT (fileselection), "destroy",
                      //GTK_SIGNAL_FUNC (on_fileselection_destroy),
                      //NULL);
  gtk_signal_connect (GTK_OBJECT (fileselection), "delete_event",
                      GTK_SIGNAL_FUNC (on_fileselection_delete_event),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (fileselection), "key_press_event",
                      GTK_SIGNAL_FUNC (on_fileselection_key_press_event),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (ok_button1), "clicked",
                      GTK_SIGNAL_FUNC (on_ok_button1_clicked),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (cancel_button1), "clicked",
                      GTK_SIGNAL_FUNC (on_cancel_button1_clicked),
                      NULL);

  return fileselection;
}

/** 
    \brief quickie/cheezy dialog for help

    \author Karl N. Redman

    \par Purpose: display a dialog box of keystrokes
*/
void keystrokes_dialog(void)
{
  GtkWidget *dialog;
  GtkWidget *scrollwin;
  GtkWidget *help;
  GtkWidget *ok;

  dialog = gtk_dialog_new();

  gtk_window_set_title(GTK_WINDOW(dialog), "run-free Keystroke Help");
  gtk_container_border_width(GTK_CONTAINER(dialog), 5);
  gtk_widget_set_usize(dialog, 300, 300);

  scrollwin = gtk_scrolled_window_new(NULL, NULL);
  gtk_container_border_width(GTK_CONTAINER(scrollwin), 10);

  gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrollwin), GTK_POLICY_AUTOMATIC, GTK_POLICY_ALWAYS);
  gtk_box_pack_start (GTK_BOX (GTK_DIALOG(dialog)->vbox), scrollwin, TRUE, TRUE, 0);
  gtk_widget_show(scrollwin);

  help = gtk_label_new(KEYSTROKES);
  gtk_label_set_justify(help, GTK_JUSTIFY_LEFT);
  gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(scrollwin), help);
  gtk_widget_show(help);

  ok = gtk_button_new_with_label("OK");
  gtk_signal_connect(GTK_OBJECT(ok), "clicked",GTK_SIGNAL_FUNC(dialog_ok_clicked), dialog);
  GTK_WIDGET_SET_FLAGS(ok, GTK_CAN_DEFAULT);
  gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog)->action_area), ok, TRUE, TRUE, 0);
  gtk_widget_grab_default(ok);
  gtk_widget_show(ok);

  //show dialog
  gtk_widget_show(dialog);
}



