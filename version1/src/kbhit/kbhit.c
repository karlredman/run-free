#include <stdio.h>
#include <termios.h>
#include <term.h>
#include <curses.h>
#include <unistd.h>

static struct termios initial_settings, new_settings;

void init_keyboard();
void close_keyboard();

int main()
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

	exit(0);
}

void init_keyboard()
{
	struct termios new_settings;

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

void close_keyboard()
{
	//reset terminal to initial settings
	tcsetattr(0, TCSANOW, &initial_settings);
}
