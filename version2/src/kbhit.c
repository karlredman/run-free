/*!\file kbhit.c
  \brief Handle console keyboard functionality
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
#include <termios.h>
#include <term.h>
#include <curses.h>
#include <unistd.h>

#include "kbhit.h"

///console termio settings (pre and post operation)
static struct termios initial_settings, new_settings;

/** 
    \brief Handle a keybaord keypress

    \author Karl N. Redman, various.
*/
int do_kbhit()
{
	int ch = 0;

	printf("PRESS ANY KEY TO CONTINUE");
	fflush((FILE *)0);

	//set keyboard state - no echo, single char input
	init_keyboard();

	//get charecter
	read(STDIN_FILENO, &ch, 1); /* getchar() works here too */
	printf("%c",ch);

	//set keyboard back to initial state
	close_keyboard();

	return(0);
}

/** 
    \brief Initialize the keyboard for console keyboard handling

    \author Karl N. Redman, various
*/
void init_keyboard()
{
  //	struct termios new_settings;

	//save attribures for close
	tcgetattr(0, &initial_settings);

	//set no echo, one char input,
	new_settings = initial_settings;
	new_settings.c_lflag &= ~ICANON;
	new_settings.c_lflag &= ~ECHO;
	new_settings.c_lflag &= ~ISIG;
	new_settings.c_cc[VMIN] = 1;
	new_settings.c_cc[VTIME] = 0;

	tcsetattr(0, TCSANOW, &new_settings);
}

/** 
    \brief Reset keyboard to initial settins

    \author Karl N. Redman, various
*/
void close_keyboard()
{
	//reset terminal to initial settings
	tcsetattr(0, TCSANOW, &initial_settings);
}
