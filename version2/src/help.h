/*!\file help.h
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

#ifndef _HELP_H_
#define _HELP_H_

///the definition of keystroke help
#define KEYSTROKES \
"Entry Box Text Editing and Navigation:\n"\
"Ctrl-h, Backspace.............Delete previous character from cursor position\n"\
"Ctrl-w........................Delete previous word from cursor position\n"\
"Ctrl-b, arrowleft.............Move cursor back one character\n"\
"Ctrl-b, arrowleft.............Move cursor back one character\n"\
"Ctrl-b, arrowleft.............Move cursor back one character\n"\
"Ctrl-f, arrowright............Move cursor forward one character\n"\
"Ctrl-f, arrowright............Move cursor forward one character\n"\
"Ctrl-f, arrowright............Move cursor forward one character\n"\
"Alt-b, Ctrl-arrowleft.........Move cursor back one word\n"\
"Alt-f, Ctrl-arrowright........Move cursor forward one word\n"\
"Ctrl-a, Ctrl-Home.............Move cursor to begining of line\n"\
"Ctrl-e, Ctrl-End..............Move cursor to end of line\n"\
"\n"\
"List Box Navigation (from Entry box):\n"\
"Alt-n, downarrow..............Show next list item in entry box\n"\
"Alt-p, uparrow................Show previous list item in entry box\n"\
"Alt-Spacebar..................Drop down list item box\n"\
"\n"\
"List Box Navigation (once dropped down):\n"\
"arrowup.......................Go up one item\n"\
"arrowdown.....................Go down one item\n"\
"PgDown........................Page down\n"\
"PgUp..........................Page up\n"\
"Ctrl-Home.....................Goto top of list\n"\
"Ctrl-End......................Goto bottom of list\n"\
"Escape........................Close list popup box\n"\
"\n"\
"Application Focus Navigation:\n"\
"Tab...........................Focus next widget\n"\
"Alt-c.........................Focus Command entry box\n"\
"Alt-a.........................Focus Run_As entry box (N.A.)\n"\
"Alt-s.........................Focus Password entry box (N.A.)\n"\
"Alt-o.........................Show extended Options (N.A.)\n"\
"Alt-r.........................Run command in entry\n"\
"Alt-t.........................Toggle run command in terminal\n"\
"Alt-w.........................Browse/Add entry from file list\n"\
"Esc...........................Close run-free\n"\
"\n"\
"Other application options\n"\
"Ctrl-m........................Update history list from history file\n"\
"Alt-h.........................Display keystroke help dialog\n"\
"Alt-y.........................Set termstay switch\n"
"Alt-u.........................keepalive toggle (don't die)\n"\


#endif //_HELP_H_
