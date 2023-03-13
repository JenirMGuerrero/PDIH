#include <stdio.h>
#include <string.h>
#include <math.h>
#include <dos.h>

#define BYTE unsigned char

//Definimos las constantes para el cambio de modo
BYTE MODOTEXTO=3;
BYTE MODOVIDEO=4;

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
void color_first(int color, const char c){		//Esta función cambia el color de un caracter
	union REGS inregs, outregs;
	inregs.h.ah=0x09;
	inregs.h.al=(int) c;
	inregs.h.bl=color;
	inregs.h.bh=0x00;
	inregs.x.cx=1;
	int86(0x10, &inregs, &outregs);
}

void textcolor(int color, const char *cadena){	//Cambiaremos el color de cada caracter de la cadena e imprimimos el resultado por pantalla
	int i;
	for(i=0; i < strlen(cadena); i++){
		color_first(color,cadena[i]);
		printf("%c", cadena[i]);
	}
	printf("\n");
}

//Funcion para cambiar el fondo del texto (background)
void color_background(int color, const char c){
	union REGS inregs, outregs;
	inregs.h.ah=0x0B;
	inregs.h.al=(int) c;
	inregs.h.bl=0x00;
	inregs.h.bh=color;
	inregs.x.cx=1;
	int86(0x10, &inregs, &outregs);
	
}

void textbackground(int color, const char *cadena){
	int i;
	for(i=0; i < strlen(cadena); i++){
		color_background(color,cadena[i]);
		printf("%c", cadena[i]);
	}
	printf("\n");
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
	int caracter;
	
	//primero leemos el caracter
	inregs.h.ah=1;
	int86(0x21, &inregs, &outregs);
	caracter= outregs.h.al;
	
	//luego mostramos por pantalla el caracter
	inregs.h.ah=2;
	inregs.h.dl=caracter;
	int86(0x21, &inregs, &outregs);
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
	textcolor(2,"Texto de primer plano");
	textbackground(4,"Texto de fondo");
	
	return 0;
}
