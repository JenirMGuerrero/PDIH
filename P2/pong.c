#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>

#define DELAY 50000
#define PLAYER_PAIR 4
#define BALL_PAIR 3
#define NET_PAIR 5
#define PLAYER ' '
#define BALL '0'

int main(int argc, char *argv[]){
	int max_f, max_c, f_ball, c_ball, res_j1, res_j2;
	int pala_j1_f, pala_j1_c;
	int pala_j2_f, pala_j2_c;
	
	int direccion_x = -1, direccion_y= -1, next_x= 0, next_y= 0;
	
	int final_juego = 5;
	
	initscr();
	
	keypad(stdscr, true);
	noecho();
	curs_set(FALSE);
	
	start_color();
	init_pair(2, COLOR_WHITE, COLOR_BLACK);
	init_pair(PLAYER_PAIR, COLOR_RED, COLOR_BLUE);
	init_pair(BALL_PAIR, COLOR_BLACK, COLOR_RED);
	init_pair(NET_PAIR, COLOR_BLACK, COLOR_GREEN);
	
	clear();
	refresh();
	
	getmaxyx(stdscr, max_f, max_c);
	WINDOW *window = newwin(max_f,max_c, 0,0);
	wbkgd(window, COLOR_PAIR(2));
	box(window, '|', '-');
	
	mvwprintw(window, 5, 45, "BIENVENIDO AL JUEGO");
	
	mvwprintw(window, 10, 20, "JUGADOR 1:");
	mvwprintw(window, 12, 20, "W--->MOVERSE ARRIBA");
	mvwprintw(window, 13, 20, "S--->MOVERSE ABAJO");
	
	mvwprintw(window, 10, 60, "JUGADOR 2:");
	mvwprintw(window, 12, 60, "UP--->MOVERSE ARRIBA");
	mvwprintw(window, 13, 60, "DOWN--->MOVERSE ABAJO");
	
	mvwprintw(window, 20, 40, "PULSA CUALQUIER TECLA PARA EMPEZAR A JUGAR");
	
	wrefresh(window);
	
	getch();
	nodelay(stdscr,1);
	
	f_ball = max_f/2;
	c_ball = max_c/2;
	
	res_j1=0;
	res_j2=0;
	
	pala_j1_c=1;
	pala_j1_f=(max_f/2) -4;
	
	pala_j2_c=max_c-1;
	pala_j2_f=(max_f/2) -4;
	
	clear();
	
	while(res_j1 != final_juego && res_j2 != final_juego){
		
		clear();
		
		mvprintw(2, 35, "JUGADOR 1: %i				JUGADOR 2: %i", res_j1, res_j2);
		for(int i=1; i<max_f; i++){
			attron(COLOR_PAIR(NET_PAIR));
			mvaddch(i, max_c/2, PLAYER);
			attroff(COLOR_PAIR(NET_PAIR));
			move(i, max_c/2);
		}
		
		for(int i=0; i<8; i++){
			attron(COLOR_PAIR(PLAYER_PAIR));
			mvaddch(pala_j1_f + i, pala_j1_c, PLAYER);
			attroff(COLOR_PAIR(PLAYER_PAIR));
			move(pala_j1_f + i, pala_j1_c);
			
			attron(COLOR_PAIR(PLAYER_PAIR));
			mvaddch(pala_j2_f + i, pala_j2_c, PLAYER);
			attroff(COLOR_PAIR(PLAYER_PAIR));
			move(pala_j2_f + i, pala_j2_c);
		}
		
		attron(COLOR_PAIR(BALL_PAIR));
		mvaddch(f_ball, c_ball, BALL);
		attroff(COLOR_PAIR(BALL_PAIR));
		move(f_ball, c_ball);
		
		refresh();
		
		usleep(DELAY);
		
		if(c_ball == pala_j1_c && (f_ball < pala_j1_f || f_ball > pala_j1_f +8)){
			res_j2++;
			
			f_ball = max_f/2;
			c_ball = max_c/2;
		}
		
		if(c_ball == pala_j2_c && (f_ball < pala_j2_f || f_ball > pala_j2_f +8)){
			res_j1++;
			
			f_ball = max_f/2;
			c_ball = max_c/2;
		}
		
		next_x = c_ball + direccion_x;
		next_y = f_ball + direccion_y;
		
		if(next_x >= max_c || next_x < 0){
			direccion_x *= -1;
		}else{
			c_ball+=direccion_x;
		}
		
		if(next_y >= max_f || next_y < 0){
			direccion_y *= -1;
		}else{
			f_ball+=direccion_y;
		}
		
		switch(getch())
		{
		case KEY_UP:
			if(pala_j2_f > 0){
				pala_j2_f--;
			}
			break;
		case KEY_DOWN:
			if(pala_j2_f < max_f/2 +20){
				pala_j2_f++;
			}
			break;
		case 'w':
			if(pala_j1_f > 0){
				pala_j1_f--;
			}
			break;
		case 's':
			if(pala_j1_f < max_f/2 +20){
				pala_j1_f++;
			}
			break;
		case 'p':
			getchar();
			break;
		case 0x1B:
			endwin();
			exit(0);
			break;
		default:
			break;
		}
		
		if(res_j1 == final_juego || res_j2 == final_juego){
		
			clear();
			
			if(res_j1 > res_j2){
				mvwprintw(window, 5, 45, "FIN DEL JUEGO");
	
				mvwprintw(window, 10, 20, "HA GANADO EL JUGADOR 1:");
				mvwprintw(window, 12, 20, "R--->REINICIAR PARTIDA");
			}else{
				mvwprintw(window, 5, 45, "FIN DEL JUEGO");
	
				mvwprintw(window, 10, 20, "HA GANADO EL JUGADOR 2:");
				mvwprintw(window, 12, 20, "R--->REINICIAR PARTIDA");
			}
			
			wrefresh(window);

			if(getchar() == 'r'){
				f_ball = max_f/2;
				c_ball = max_c/2;
	
				res_j1=0;
				res_j2=0;
	
				pala_j1_c=1;
				pala_j1_f=(max_f/2) -4;
		
				pala_j2_c=max_c-1;
				pala_j2_f=(max_f/2) -4;
			}else{
				endwin();
				exit(0);
			}
		}
	}
	
	endwin();
	
	return 0;
}
