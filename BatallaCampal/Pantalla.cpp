#include "Pantalla.h"
#include <iostream>

using namespace std;

Pantalla::Pantalla(){

	this->opcionUsuario = 0;
	this->cantidadJugadores = 2;
	this->cantidadSoldados = 3;
	this->dimensionDelTablero = 20;
	this->mapaOpcion = rand() % 3 + 1;
}

void Pantalla::nuevaPartida(){

	cout << "1.Partida rapida (2 jugadores)\n2.Partida personalizada (2 o mas jugadores)" <<endl;
	cout << "Modo de juego: ";
	cin >> this->opcionUsuario;
	
	cout<<"MAPA["<<mapaElegido()<<"] - ";
	
	if( this->opcionUsuario == 2){
		cout << "Elige cantidad de jugadores (2 a 20): ";
		cin >> this->cantidadJugadores;
		cout << "Elige cantidad de soldados por jugador (3 a 8): ";
		cin >> this->cantidadSoldados;
		cout << "Elige el tamanio del mapa (20 a 100): ";
		cin >> this->dimensionDelTablero;
	}
	
	
}

void Pantalla::creacionImagen(){
	RGBApixel White;
	White.Red = 255;
	White.Green = 255;
	White.Blue = 255;
	for(int j=0;j < this->Window.TellHeight();j++){
		for(int i=0 ; i < this->Window.TellWidth();i++){
			*this->Window(i,j) = White;
		}
	}

	this->Window.WriteToFile("tablero.bmp");
}

void Pantalla::pintarCirculo(int centerX, int centerY){
	if(centerX < 1 || centerY < 1){
		throw "Coordenadas inválidas";
	}
	RGBApixel FontColor;
	FontColor.Red = 255;
	FontColor.Green = 255;
	FontColor.Blue = 255;
	DrawArc(this->Window, centerY+20, centerX+20, 5, 0, 360, FontColor);

	this->Window.WriteToFile("tablero.bmp");
}

void Pantalla::pintarCirculoRojo(int centerX, int centerY){
	if(centerX < 1 || centerY < 1){
		throw "Coordenadas inválidas";
	}
	RGBApixel FontColor;
	FontColor.Red = 255;
	FontColor.Green = 0;
	FontColor.Blue = 0;
	DrawArc(this->Window, centerY+20, centerX+20, 5, 0, 360, FontColor);

	this->Window.WriteToFile("tablero.bmp");
}

void Pantalla::pintarLineas(int tamanio){
	if(tamanio < 20 || tamanio > 100){
		throw "tamaño inválido";
	}
	RGBApixel FontColor;
	FontColor.Red = 0;
	FontColor.Green = 0;
	FontColor.Blue = 0;
	for (int i = 20; i <= tamanio*tamanio; i = i+20){
		for (int j = 20; j <= tamanio*tamanio; j = j+20){
			DrawLine(this->Window, i, j, i, tamanio*tamanio, FontColor);
			DrawLine(this->Window, j, i, tamanio*tamanio, i, FontColor);
		}
	}
	this->Window.WriteToFile("tablero.bmp");
}
void Pantalla::pintarCuadrado(int xi,int yi, int xf, int yf, TipoDeCasillero tipo){
	if(xi < 1 || yi < 1 || xf < 1 || yf < 1){
		throw "Coordenadas inválidas";
	}
	RGBApixel FontColor;
	if(tipo == TIERRA){
		FontColor.Red = 78;
		FontColor.Green = 59;
		FontColor.Blue = 49;
	}
	else if(tipo == AGUA){
		FontColor.Red = 0;
		FontColor.Green = 0;
		FontColor.Blue = 255;
	}
	else if(tipo == AIRE){
		FontColor.Red = 162;
		FontColor.Green = 202;
		FontColor.Blue = 223;
	}
	else if(tipo == GENERAL){
		throw "Este tipo no es válido en el contexto de la Batalla Campal.";
	}
	else{
		throw "Tipo inválido de casillero.";
	}
	
	
	while (yi <= yf){
		DrawLine(this->Window, xi, yi, xf, yi, FontColor);
		yi++;
	}
	this->Window.WriteToFile("tablero.bmp");
}

void Pantalla::generarMapa(BatallaCampal* batalla, Pantalla* pantalla){
	if(batalla == NULL || pantalla == NULL){
		throw "Error en la carga";
	}

	RGBApixel LightGray;
	LightGray.Red = 192;
	LightGray.Green = 192;
	LightGray.Blue = 192;
	int xi,xf,yi,yf;

	this->Window.SetSize((pantalla->getDimensionDelTablero()*20)+20, (pantalla->getDimensionDelTablero()*20)+20);
	for( int j=0 ; j < this->Window.TellHeight() ; j++ ){
		for( int i=0 ; i < this->Window.TellWidth() ; i++ ){
			*this->Window(i,j) = LightGray;
		}
	}
	creacionImagen();

	for (int x = 1; x <= batalla->getDimensionDelTablero(); x++){
	        for (int y = 1; y <= batalla->getDimensionDelTablero(); y++){
	            	for (int z = 1; z <= batalla->getDimensionDelTablero(); z++){
	                		if(batalla->getTablero()->getCasilla(x,y,z)->getTipoDeCasilla() == TIERRA){
	                			xi = x*20;
	                			xf = (x*20)+20;
	                			yi = y*20;
	                			yf = (y*20)+20;
	                			pintarCuadrado(yi, xi, yf, xf, TIERRA);
	                		}else if(batalla->getTablero()->getCasilla(x,y,z)->getTipoDeCasilla() == AGUA){
	                			xi = x*20;
	                			xf = (x*20)+20;
	                			yi = y*20;
	                			yf = (y*20)+20;
	                			pintarCuadrado(yi, xi, yf, xf, AGUA);
	                		}
	            	}
	    	}
	}

	pintarLineas((batalla->getDimensionDelTablero()+20));
}

void Pantalla::solicitarSoldados(BatallaCampal* batalla, Jugador* jugador){

	if(batalla == NULL || jugador == NULL){
		throw "Error en la carga";
	}
	int coordX;
	int coordY;

	for( int j = 1; j <= batalla->getCantidadDeSoldados(); j++){
		cout << "Jugador: " << jugador->getId() << ", elija posiciones para el soldado [" << j << "]: " << endl;
		cout << "fila: ";
		cin >> coordX;
		cout << "columna: ";
		cin >> coordY;
		if( coordX <= batalla->getDimensionDelTablero() && coordY <= batalla->getDimensionDelTablero()){
			if(batalla->getTablero()->getCasilla(coordX, coordY, 1)->getTipoDeCasilla() == TIERRA){

				jugador->nuevoSoldado(coordX, coordY);
				this->pintarCirculo(((coordX*20)-10), ((coordY*20)-10));
			}
			else{
				cout << "Tu soldado se ahogó" << endl;
			}
		}
		else{
			throw "Coordenada invalida";
		}
		batalla->getTablero()->getCasilla(coordX, coordY, 1)->setEstado(LLENO);
	}

}

void Pantalla::usarUnaCarta(BatallaCampal* batalla, Jugador* jugador){
	if(batalla == NULL || jugador == NULL){
		throw "Error en la carga";
	}
	unsigned int coordX;
	unsigned int coordY;
	unsigned int coordZ;
	char filaOColumna;
	int numeroCarta;
	jugador->getCarta()->reiniciarCursor();
	cout << "Cartas disponibles: "<<endl;
	int id = 1;
	while(jugador->getCarta()->avanzarCursor()){
		cout << id <<"."<< jugador->getCarta()->getCursor()->getDescripcion() << endl;
		id++;
		}
	cout << "Elegir carta: " <<endl;
	cin >> numeroCarta;
	if(numeroCarta > jugador->getCantidadDeCartas() || numeroCarta < 1){
		throw "Numero de carta no disponible";
	}
	Carta* carta = jugador->getCarta()->get(numeroCarta);
	cout << "Ejecutando carta numero "<< numeroCarta<<", tipo " <<carta->getDescripcion() <<endl;
	if (carta->getTipoDeCarta() == SUPER){
		cout << "Elegir Columna (C) o Fila (F): "<<endl;
		cin >> filaOColumna;
	}
	cout << "Ingrese coordenadas: "<<endl;
	cout << "Fila: ";
	cin >> coordX;
	cout << "Columna: ";
	cin >> coordY;
	cout << "Altura: ";
	cin >> coordZ;
	if (carta->getTipoDeCarta() == RADAR){
		if (batalla->esCoordenadaValida(coordX, coordY, coordZ) && batalla->esCoordenadaValida(coordX+2, coordY+2, coordZ+2) && batalla->esCoordenadaValida(coordX-2, coordY-2, coordZ-2)){
		cout << "En los alrededores se encuentran "<< batalla->usarRadar(coordX, coordY, coordZ) << " cantidad de fichas"<<endl;
		}
	}else{
		batalla->usarCarta(jugador, numeroCarta, coordX, coordY, coordZ, filaOColumna);
	}
	cout << "Ejecutado carta " << carta->getDescripcion()<<endl;
	jugador->eliminarCarta(numeroCarta);
}
void Pantalla::usarHerramienta(BatallaCampal* batalla, Ficha* herramientaAux, Jugador* jugador){

	if(batalla == NULL || jugador == NULL || herramientaAux == NULL){
		throw "Error en la carga";
	}

	unsigned int coordX;
	unsigned int coordY;
	unsigned int coordZ;

	cout << "Cantidad de Armamento: "<< jugador->getCantidadDeHerramientas() << endl;

	if (herramientaAux->getTipo() == BARCO){
		cout << "Usando barco "<<endl;
		cout << "Ingrese coordenadas : "<<endl;
		cout << "Fila: ";
		cin >> coordX;
		cout << "Columna: ";
		cin >> coordY;
		cout << "Altura: ";
		cin >> coordZ;
		batalla->dispararMisil(coordX, coordY, coordZ);
	}
	if (herramientaAux->getTipo() == AVION){
		cout << "Usando avion"<<endl;
		cout << "Ingrese coordenadas de disparo adicional: "<<endl;
		cout << "fila: ";
		cin >> coordX;
		cout << "columna: ";
		cin >> coordY;
		cout << "Altura: ";
		cin >> coordZ;
		cout << "Disparando..." <<endl;
		if (batalla->soldadosCoinciden(coordX, coordY)){
			cout << "Fuego amigo!" << endl;
		}else if(batalla->eliminarEnemigo(coordX, coordY)){
				batalla->realizarDisparo(coordX, coordY, coordZ);
				cout << "Mataste a un soldado enemigo" << endl;
				this->pintarCirculoRojo(((coordX*20)-10), ((coordY*20)-10));
			}
		cout << "Ingrese coordenadas del 2do disparo adicional: "<<endl;
		cout << "fila: ";
		cin >> coordX;
		cout << "columna: ";
		cin >> coordY;
		cout << "Altura: ";
		cin >> coordZ;
		cout << "Disparando..." <<endl;
		if (batalla->soldadosCoinciden(coordX, coordY)){
			cout << "Fuego amigo!" << endl;
		}else if(batalla->eliminarEnemigo(coordX, coordY)){
				batalla->realizarDisparo(coordX, coordY, coordZ);
				cout << "Mataste a un soldado enemigo" << endl;
				this->pintarCirculoRojo(((coordX*20)-10), ((coordY*20)-10));
			}
	}
}
void Pantalla::solicitarCarta(BatallaCampal* batalla, Jugador* jugador){

	if(batalla == NULL || jugador == NULL){
		throw "Error en la carga";
	}

	char opcionUsuarioC;

	cout << "Generando nueva carta..." << endl;
	if(jugador->getCantidadDeCartas() == 5){
		cout << "No puedes obtener mas cartas" << endl;
	}
	int aleatorio = rand() %6 +1;
	jugador->nuevaCarta(aleatorio);
	cout << "Cartas del jugador: " << jugador->getCantidadDeCartas() <<endl;
	cout << "Desea usar una carta? (SI: S, NO: N): ";
	cin >> opcionUsuarioC;
	if(opcionUsuarioC == 'S'){
		this->usarUnaCarta(batalla, jugador);
	}
	jugador->getHerramienta()->reiniciarCursor();
	while(jugador->getHerramienta()->avanzarCursor()){
			Ficha* herramientaAux = jugador->getHerramienta()->getCursor();
			usarHerramienta(batalla, herramientaAux, jugador);
	}
}

void Pantalla::solicitarMovimiento(BatallaCampal* batalla, Jugador* jugador){

	if(batalla == NULL || jugador == NULL){
		throw "Error en la carga";
	}

	char movimiento;
	char opcionUsuarioC;
	unsigned int coordX;
	unsigned int coordY;

	cout << "Cantidad de soldados: "<< jugador->getCantidadDeSoldados() << endl;
	cout <<" Desea mover un soldado? (SI: S, NO: N): ";
	cin >> opcionUsuarioC;
	if(opcionUsuarioC == 'S'){
		cout << "elija el soldado a mover: " <<endl;

		jugador->getSoldado()->reiniciarCursor();
		while(jugador->getSoldado()->avanzarCursor()){
			cout << "Soldado: ["<< jugador->getSoldado()->getCursor()->getPosicionX() <<","<<jugador->getSoldado()->getCursor()->getPosicionY() <<"]"<<endl;
		}
		cout << "fila: ";
		cin >> coordX;
		cout << "columna: ";
		cin >> coordY;

		cout << "Elija movimiento (WASD): ";
		cin >> movimiento;
		cout << "Moviendo soldado..." << endl;

		TipoDeCasillero tipo = batalla->getTablero()->getCasilla(coordX, coordY, 1)->getTipoDeCasilla();
		int xi = coordX * 20;
		int xf = (coordX * 20) + 20;
		int yi = coordY * 20;
		int yf = (coordY * 20) + 20;
		this->pintarCuadrado(yi, xi, yf, xf, tipo);

		Ficha* soldado = batalla->moverSoldado(movimiento, coordX, coordY, jugador);

		if( soldado != NULL ) {
			int x = soldado->getPosicionX();
			int y = soldado->getPosicionY();
			this->pintarCirculo(((x*20)-10), ((y*20)-10));
			this->pintarCirculo(((x*20)-10), ((y*20)-10));
		}

		pintarLineas((batalla->getDimensionDelTablero()+20));
	}
}

void Pantalla::solicitarDisparo(BatallaCampal* batalla){

	if(batalla == NULL){
		throw "Error en la carga";
	}

	unsigned int coordX;
	unsigned int coordY;
	unsigned int coordZ;

	cout << "Ingrese coordenadas de disparo: "<<endl;

	cout << "fila: ";
	cin >> coordX;
	cout << "columna: ";
	cin >> coordY;
	cout << "Altura: ";
	cin >> coordZ;
	cout << "Disparando..." <<endl;
	if (batalla->soldadosCoinciden(coordX, coordY)){
		cout << "Fuego amigo!" << endl;
		cout << "Perdiste el turno..." << endl;
	}
	else{
		if (batalla -> eliminarEnemigo(coordX, coordY)){
			cout << "Mataste a un soldado enemigo" << endl;
			batalla -> realizarDisparo(coordX, coordY, coordZ);
			this->pintarCirculoRojo(((coordX*20)-10), ((coordY*20)-10));
		}else{
			batalla -> realizarDisparo(coordX, coordY, coordZ);
			cout << "Disparo fallido!" << endl;
			this->pintarCirculoRojo(((coordX*20)-10), ((coordY*20)-10));

		}

	}

	cout << "La casilla ahora esta: "<< batalla->getTablero()->getCasilla(coordX, coordY, coordZ)->getEstadoActual() <<endl;
}


int Pantalla::getCantidadJugadores(){
	return this->cantidadJugadores;
}

int Pantalla::getCantidadSoldados(){
	return this->cantidadSoldados;
}

int Pantalla::getDimensionDelTablero(){
	return this->dimensionDelTablero;
}

int Pantalla::mapaElegido(){
	return this->mapaOpcion;
}
