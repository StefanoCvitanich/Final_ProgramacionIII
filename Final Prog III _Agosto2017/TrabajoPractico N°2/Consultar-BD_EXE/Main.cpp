#include <stdio.h>
#include <iostream>
#include <string>
#include "Conexion.h"

using namespace std;

void main()
{
	string jugador;
	string password;

	char tecla = 'q';
	int puntaje = 0;

	cout << "Ingrese su Nombre de Jugador" << endl;
	cin >> jugador;

	cout << "Ingrese una contrasenia" << endl;
	cin >> password;

	cout << "Presione la tecla K y luego la L sucesivamente para sumar puntos" << endl;

	for (int i = 0; i < 3; i++){
		cin >> tecla;
		if (tecla == 'k'){             // 107 es ASCII para 'k'
			//cout << "k" << endl;
			cin >> tecla;
			if (tecla == 'l'){         // 108 es ASCII para 'l'
				//cout << "l" << endl;
				puntaje++;
				cout << "puntaje: " << puntaje << endl;
			}
		}
	}

	cout << "El juego ha concluido" << endl;
	cout << "Su puntaje es: " << puntaje << endl;
	cout << "Presione la tecla Enter para continuar" << endl;

	fflush(stdin);
	cin.get();

	cout << "Comienza la comunicacion con la Base de Datos" << endl;
	
	Conexion* c = new Conexion();

	cout << "Presione Enter para Cargar la estructura de la BD" << endl;
	fflush(stdin);
	cin.get();
	//c->cargarEstructura();

	cout << "Presione Enter para cargar los datos guardados en la BD" << endl;
	fflush(stdin);
	cin.get();
	//c->cargarDatos();
	/*
	cout<<c->listarJuegos();
	c->agregarJuego("Burning Sands", "Un juego muy copado");
	cout<<c->listarJuegos();
	c->borrarJuego("Burning Sands");
	//c->borrarJuego(13);
	cout<<c->listarJuegos();

	cout << c->listarJugadores();
	c->agregarJugador(jugador, password);
	cout<<c->listarJugadores();
	c->borrarJugador("Renly");
	//c->borrarJuagdor(7);
	cout << c->listarJugadores();
	
	cout << c->listarHighScores(Todo, "");
	cout << c->listarHighScores(Juego,"Flight of the Immortals");
	cout << c->listarHighScores(Jugador, "Pedro");
	//c->borrarHighScores("Juan", "Flight of the Immortals", 3);
	cout << c->listarHighScores(Todo, "");
	
	cout << c->listarSavedGames(Todo, "");
	cout << c->listarSavedGames(Juego, "Flight of the Immortals");
	cout << c->listarSavedGames(Jugador, "Pedro");
	//c->borrarSavedGame("Juan", "Flight of the Immortals");
	cout << c->listarSavedGames(Todo, "");

	cout << c->listarRegistros(Todo, "");
	cout << c->listarRegistros(Juego, "Flight of the Immortals");
	cout << c->listarRegistros(Jugador, "Pedro");
	//c->borrarRegistros("Juan", "Flight of the Immortals");
	cout << c->listarRegistros(Todo, "");
	*/
	cout << "Presione Enter para guardar los datos de la BD" << endl;
	fflush(stdin);
	cin.get();
	//c->guardarDatos();

	cout << "Programa Finalizado. Presione Enter para terminar" << endl;
	fflush(stdin);
	cin.get();

	delete c;
}