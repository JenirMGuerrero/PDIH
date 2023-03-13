#include <stdio.h>
#include <string.h>
#include <math.h>
#include <dos.h>

#define BYTE unsigned char

//Definimos las constantes para el cambio de modo
BYTE MODOTEXTO=3;
BYTE MODOVIDEO=4;

unsigned char colorfondo=0;
unsigned char colortexto=1;

void pausa(){				//Espera pulsación de tecla
	union REGS inregs, outregs;
	inregs.h.ah=0x00;
	int86(0x16, &inregs, &outregs);
}

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

//Función que establece el modo de video 3-Texto 4-Grafico
void setvideomode(BYTE modo){
	union REGS inregs, outregs;
	inregs.h.ah=0x00;
	inregs.h.al=modo;
	int86(0x10, &inregs, &outregs);
}

//Función que devuelve el modo de vídeo actual
BYTE getvideomode(){
	BYTE modo;
	union REGS inregs, outregs;
	inregs.h.ah=0x0F;
	int86(0x10, &inregs, &outregs);
	
	modo=outregs.h.al;
	
	if(modo == 3)
		return outregs.h.ah;
	else
		return modo;
}

//Funcion para cambiar el color del texto
void printcaracter(char c){		//Esta función imprime un caracter por pantalla
	union REGS inregs, outregs;
	inregs.h.ah=0x09;
	inregs.h.al=c;
	inregs.h.bl=colorfondo << 4 | colortexto;
	inregs.h.bh=0x00;
	inregs.x.cx=1;
	int86(0x10, &inregs, &outregs);
}

void textcolor(int color){	//Cambiaremos el color de texto global
	colortexto=color;
}

void textbackground(int color){ //Cambiaremos el color de fondo global
	colorfondo=color;
}


//Funcion que limpia la pantalla, para ello escribiremos saltos de linea hasta que la pantalla quede "limpia"
void clrscr(){
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
}

//Funcion que escribe un caracter en pantalla con el color indicado actualmente
void cputchar(char caracter){
	union REGS inregs, outregs;
	inregs.h.ah=0x09;
	inregs.h.al=caracter;
	int86(0x10, &inregs, &outregs);
}

//Funcion que obtiene un caracter por teclado y lo muestra en pantalla
void getche(){
	union REGS inregs, outregs;
	inregs.h.ah=1;
	int86(0x21, &inregs, &outregs);

}

int main(){
	int i;

	printf("\nCursor invisible");
	setcursortype(0);
	pausa();
	
	printf("\nCursor normal");
	setcursortype(1);
	pausa();
	
	printf("\nCursor grueso");
	setcursortype(2);
	pausa();
	printf("\n");
	
	textcolor(2);
	printcaracter('c');
	printf("\n");
	
	textcolor(1);
	textbackground(2);
	printcarater('c');
	
	printf("\n");
	
	printf("Esperando lectura de caracter...");
	getche();
	
	return 0;
}
