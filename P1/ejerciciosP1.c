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

//Funcion que pinta un pixel en las coordenadas x,y del color indicado
void pixel(int x, int y, BYTE c){
	union REGS inregs, outregs;
	inregs.x.cx=x;
	inregs.x.dx=y;
	inregs.h.al=c;
	inregs.h.ah=0x0C;
	int86(0x10, &inregs, &outregs);
}

//Función para pintar un cubo
void pintaCubo(int esq_sup, int tamanio){
	int i;
	
	setvideomode(MODOVIDEO);
	
	for(i=esq_sup; i<tamanio; i++){
		pixel(i, esq_sup, 1);
		pixel(i, tamanio, 1);
	}
	
	for(i=esq_sup; i <= tamanio; i++){
		pixel(esq_sup, i, 2);
		pixel(tamanio, i, 2);
	}
	
	pausa();
	setvideomode(MODOTEXTO);
}

//Funcion para cambiar el color del texto

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
	inregs.h.bl=colorfondo << 4 | colortexto;
	inregs.h.bh=0x00;
	inregs.x.cx=1;
	int86(0x10, &inregs, &outregs);
}

//Funcion que obtiene un caracter por teclado y lo muestra en pantalla
void getche(){
	union REGS inregs, outregs;
	int caracter;
	
	printf("Escribe un caracter");
	inregs.h.ah=1;
	int86(0x21, &inregs, &outregs);
	
	caracter=outregs.h.al;
	printf("\nHas pulsado:");
	cputchar(caracter);
}

int main(){

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
	
	textcolor(1);
	textbackground(2);
	cputchar('c');	
	printf("\n");
	
	getche();
	
	printf("\nRealizando limpieza de pantalla, pulse una tecla");
	pausa();
	clrscr();
	gotoxy(0,0);
	
	printf("Cambiando a modo video, pulsa una tecla\n");
	pausa();
	pintaCubo(10, 100);
	
	return 0;
}
