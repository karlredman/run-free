//comboBox.h
/*!\file comboBox.h
  \brief comboBox specific functions
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

#ifndef _COMBOBOX_H_
#define _COMBOBOX_H_


/** @name combo box mode settings
 *  Settings for various combo box modes
 */
//@{ 
#define RF_EXAMPLE_MODE 0	/*!< an example  */
#define RF_HISTORY_MODE 1	/*!< history mode  */
#define RF_MAX_MODE 1		/*!< max. modes available  */
//@}

/// the combo box list
GList *cbitems;
/// the combo box mode
unsigned int combo_mode;

/// comob box initialization
int combo_init(unsigned int mode);

#endif //_COMBOBOX_H_
