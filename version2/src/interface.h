/*!\file interface.h
  \brief interface globals and functions
  These functions were originall created by glade (gtk1.2)
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
#ifndef _INTERFACE_H_
#define _INTERFACE_H_

/** @name common global widgets
 * widgets we need to be in touch with
 *  
 */
//@{ 
GtkWidget *mainWindow;
GtkWidget *fileselection;
GtkWidget *checkbutton;
//@}

/** @name options widgets
 * convenience -for options (mainWindow resizing, etc)
 *  
 */
//@{ 
/*! originall meant to help out with suid functionallity but I'm going
  to put that functionality in run-free version 3.0 */
GtkWidget *vbox2;
/// the combo box
GtkWidget *combo1;
//@}

/// the check button for run_in_term mode
GtkWidget *checkbutton;

///create the main window
GtkWidget* create_mainWindow (void);
/// create the persistant fileselection box
GtkWidget* create_fileselection (void);

///display help for keystrokes
void keystrokes_dialog(void);

#endif //_INTERFACE_H_
