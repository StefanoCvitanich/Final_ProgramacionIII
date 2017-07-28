#ifndef CONEXION_H
#define CONEXION_H

#ifdef CONNECT_DB
#define CONNECT __declspec(dllimport)
#else
#define CONNECT __declspec(dllexport)
#endif

#include <string>
#include <Windows.h>
#include <shellapi.h>

struct pg_conn;
struct pg_result;

enum CONNECT Filtro{
	Todo,
	Jugador,
	Juego
};

class CONNECT Conexion
{
public:
	Conexion();
	~Conexion();

	void cargarEstructura();

	void cargarDatos();
	void guardarDatos();

	void agregarJuego(std::string nombreJuego, std::string descripcion);
	std:: string listarJuegos();
	void borrarJuego(std::string nombreJuego);
	void borrarJuego(int idJuego);

	void agregarJugador(std::string nombreJugador, std::string contrasenia);
	std::string listarJugadores();
	void borrarJugador(std::string nombreJugador);
	void borrarJuagdor(int idJugador);

	std::string listarHighScores(Filtro filtro, std::string especificacion);
	void borrarHighScores(std::string nombreJugador, std::string nombreJuego, int puntaje);

	std::string listarSavedGames(Filtro filtro, std::string especificacion);
	void borrarSavedGame(std::string nombreJugador, std::string nombreJuego);

	std::string listarRegistros(Filtro filtro, std::string especificacion);
	void borrarRegistros(std::string nombreJugador, std::string nombreJuego);

private:
	char     buff[200];
	pg_conn   *dbconn;
	pg_result *res;
	int nFields, i, j;
	bool conectado;
};

#endif