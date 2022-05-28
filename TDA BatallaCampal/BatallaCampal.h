#include "Vector.h"
#include "tablero.h"
#include "jugador.h"

#define MIN_JUGADORES 2
#define MAX_JUGADORES 20
#define MIN_SOLDADOS 2
#define MAX_SOLDADOS 8
#define MIN_DIMENSION 20
#define MAX_DIMENSION 100

enum estadoJuego{JUGANDO,FINALIZADO};

class BatallaCampal{
	
	private:
		Vector <Jugador*>* jugadores;
		unsigned int turno;
		Tablero* tablero;
		int dimensionTablero;
		int cantidadJugadores;
		unsigned int cantidadSoldados;

	public:

		BatallaCampal(unsigned int cantJugadores, unsigned int cantidadSoldados, int dimensionTablero);
		virtual ~BatallaCampal();
		void siguienteTurno();
		estadoJuego estadoDelJuego();

};

