#include <stdio.h>
#include <dos.h>

//Función para ir a una coordenada (x,y)
void gotoxy(int x, int y){
	union REGS inregs, outregs;
	inregs.h.dh=y;			//Establecemos la posicion y correspondiente a las filas
	inregs.h.dl=x;			//Establecemos la posición x correspondiente a las columnas
	inregs.h.bh=0;
	inregs.h.ah=2;
	int86(0x10,&inregs,&outregs);
}

//Función para establecer el tipo de cursor
void setcursortype(int tipo){
	union REGS inregs, outregs;
	inregs.h.ah=0x01;
	switch(tipo){
		case 0:				//Cursor invisible
			inregs.h.ch=010;
			inregs.h.cl=000;
			break;
		case 1:				//Cursor normal
			inregs.h.ch=010;
			inregs.h.cl=010;
			break;
		case 2:				//Cursor grueso
			inregs.h.ch=000;
			inregs.h.cl=010;
			break;
	}
	int86(0x10, &inregs, &outregs);
}

int main(){

	/*gotoxy(00,00);				//Por defecto el cursor se movera a la parte superior de la consola
	printf("\nCursor en esta posicion!");*/
	
	
	/*printf("\nCursor invisible");
	setcursortype(0);
	
	printf("\nCursor normal");
	setcursortype(1);
	
	printf("\nCursor grueso");
	setcursortype(2);*/
	
	return 0;
}
