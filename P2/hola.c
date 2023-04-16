#include <ncurses.h>

int main(){
	initscr();
	printw("holita");
	refresh();
	getch();
	endwin();
	
	return 0;
}
