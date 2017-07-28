#include <iostream>
#include <fstream>
#include<sstream>
#include "include/libpq-fe.h"
#include "Conexion.h"

using namespace std;

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

Conexion::Conexion()
{
	char *db = "DataJuegos";
	char *dbserver = "127.0.0.1";
	char *uname = "postgres";
	char *pass = "admin";

	printf("Attempting to Connect to Database Server:\n");
	printf("Database: %s\n", db);
	printf("Server  : %s\n", dbserver);

	sprintf_s(buff, "dbname=%s host=%s port=5432 user=%s password=%s",
		db, dbserver, uname, pass);

	dbconn = PQconnectdb(buff);

	if (PQstatus(dbconn) != CONNECTION_OK)
	{
		conectado = false;
	}
		
	else
	{
		conectado = true;
	}
		
}

Conexion:: ~Conexion()
{
	/*
	res = PQexec(dbconn, "COMMIT");
	PQclear(res);
	PQfinish(dbconn);
	*/
}

//-------------------------------------------------
//-------------------------------------------------

void Conexion::cargarEstructura()
{
	ifstream archivo;
	string linea;
	string query;

	archivo.open("queries.txt", ios::in);
	if (!archivo.is_open())
		return;
	while (!archivo.eof())
	{
		getline(archivo, linea);

		query += linea + "\n";
	}

	const char* SQL = query.c_str();

	PQclear(res);

	res = PQexec(dbconn, SQL);

	if (PQresultStatus(res) != PGRES_COMMAND_OK)
	{
		printf("Error executing SQL!: %s\n", PQerrorMessage(dbconn));
		PQclear(res);
	}

	res = PQexec(dbconn, "END");
	PQclear(res);
}

//-------------------------------------------------
//-------------------------------------------------

void Conexion::cargarDatos()
{
	//string cadena = "psql -h localhost -p 5432 -U postgres -d \"DataJuegos\" -f respaldo.sql";

	//system(cadena.c_str());

	ShellExecute(NULL,NULL, "C:\\Program Files\\PostgreSQL\\9.5\\bin\\psql.exe", "-h localhost -p 5432 -U postgres -d \"DataJuegos\" -f respaldo.sql", NULL, SW_SHOW);
}

void Conexion::guardarDatos()
{
	//string cadena = "pg_dump -h localhost -p 5432 -U postgres -d \"DataJuegos\" -f respaldo.sql -F p -b";

	//system(cadena.c_str());

	ShellExecute(NULL,NULL,"C:\\Program Files\\PostgreSQL\\9.5\\bin\\pg_dump.exe", "-h localhost -p 5432 -U postgres -d \"DataJuegos\" -f respaldo.sql -F p -b", NULL, SW_SHOW);
}

//-------------------------------------------------
//-------------------------------------------------

void Conexion::agregarJugador(std::string nombreJugador, std::string contrasenia)
{/*
	if (nombreJugador != "" && contrasenia != "")
	{
		if (!conectado)
			printf("Connection Failed: %s\n", PQerrorMessage(dbconn));
		else
		{
			printf("Connected Successfully!\n");

			string query = "select \"Username\" from public.\"Jugadores\"";

			const char* SQL = query.c_str();

			sprintf_s(buff, "BEGIN; DECLARE my_portal CURSOR FOR %s", SQL);

			res = PQexec(dbconn, buff);
			if (PQresultStatus(res) != PGRES_COMMAND_OK)
			{
				printf("Error executing SQL!: %s\n", PQerrorMessage(dbconn));
				PQclear(res);
			}
			else
			{
				PQclear(res);
				res = PQexec(dbconn, SQL);

				if (PQresultStatus(res) != PGRES_TUPLES_OK)
				{
					printf("ERROR, Fetch All Failed: %s", PQerrorMessage(dbconn));
					PQclear(res);
				}
				else
				{
					for (i = 0; i < PQntuples(res); i++)
					{
						for (j = 0; j < nFields; j++)
						{
							if (nombreJugador == PQgetvalue(res, i, j))
								return;
						}
					}

					query = "insert into public.\"Jugadores\" (\"Username\", \"Password\") values ('" + nombreJugador + "', '" + contrasenia + "')";
					
					const char* SQL = query.c_str();

					PQclear(res);
					res = PQexec(dbconn, SQL);

					if (PQresultStatus(res) != PGRES_COMMAND_OK)
					{
						printf("ERROR, Fetch All Failed: %s", PQerrorMessage(dbconn));
						PQclear(res);
					}
				}
			}
		}
	}

	res = PQexec(dbconn, "CLOSE my_portal");
	PQclear(res);

	res = PQexec(dbconn, "END");
	PQclear(res);
	*/

	if (nombreJugador != "" && contrasenia != ""){

		string query = "select \"Username\" from public.\"Jugadores\"";
		const char * SQL = query.c_str();
		res = PQexec(dbconn, SQL);

		if (PQresultStatus(res) != PGRES_TUPLES_OK){
			cout << "Error al ejecutar la consulta" << endl;
			return;
		}

		nFields = PQntuples(res);

		for (i = 0; i<nFields; i++) {
			for (j = 0; j<1; j++) {
				if (nombreJugador == PQgetvalue(res, i, j)){
					cout << "El Jugador ya existe" << endl;
					return;
				}
			}
		}

		query = "insert into public.\"Jugadores\" (\"Username\", \"Password\") values ('" + nombreJugador + "', '" + contrasenia + "')";
		SQL = query.c_str();
		res = PQexec(dbconn, SQL);

		if (PQresultStatus(res) != PGRES_COMMAND_OK)	{
			cout << "ERROR al intentar insertar el Jugador en la Tabla" << endl;
			return;
		}
		cout << "La operacion de Agregar Jugador se realizo con exito" << endl;
	}
	else
		cout << "ERROR. El nombre del jugador no puede ser vacio; la contrasenia tampoco" << endl;
}

std::string Conexion::listarJugadores()
{/*
	char *SQL = "select * from public.\"Jugadores\"";

	if (!conectado)
		printf("Connection Failed: %s\n", PQerrorMessage(dbconn));
	else
	{
		printf("Connected Successfully!\n");

		sprintf_s(buff, "BEGIN; DECLARE my_portal CURSOR FOR %s", SQL);

		res = PQexec(dbconn, buff);
		if (PQresultStatus(res) != PGRES_COMMAND_OK)
		{
			printf("Error executing SQL!: %s\n", PQerrorMessage(dbconn));
			PQclear(res);
		}
		else
		{
			PQclear(res);
			res = PQexec(dbconn, "FETCH ALL in my_portal");

			if (PQresultStatus(res) != PGRES_TUPLES_OK)
			{
				printf("ERROR, Fetch All Failed: %s", PQerrorMessage(dbconn));
				PQclear(res);
			}
			else
			{
				nFields = PQnfields(res);

				// Print out the field names
				for (i = 0; i < nFields; i++)
					printf("%-25s", PQfname(res, i));

				printf("\n");

				// Print out the rows
				for (i = 0; i < PQntuples(res); i++)
				{
					for (j = 0; j < nFields; j++)
						printf("%-25s", PQgetvalue(res, i, j));

					printf("\n");
				}
			}
		}
	}

	res = PQexec(dbconn, "CLOSE my_portal");
	PQclear(res);

	res = PQexec(dbconn, "END");
	PQclear(res);
	*/
	/*
	res = PQexec(dbconn, "select * from public.\"Jugadores\"");

	if (PQresultStatus(res) != PGRES_TUPLES_OK){
		cout << "Error al ejecutar la consulta" << endl;
		return;
	}

	nFields = PQntuples(res);
	_itoa_s(nFields, buff, 10);

	string cuenta = buff;
	string input;
	string output = "Se recibieron " + cuenta + " resultados.\n\n" + "\tID\tUsername Password\n";

	for (i = 0; i<nFields; i++) {
		for (j = 0; j<3; j++) {
			input.assign(PQgetvalue(res, i, j));
			output += "\t " + input;
		}
		output += " \n";
	}
	cout << output << endl;
	*/
	res = PQexec(dbconn, "select * from public.\"Jugadores\"");
	if (PQresultStatus(res) != PGRES_TUPLES_OK){
		return "No se recibieron datos.";
	}
	nFields = PQntuples(res);
	char resultCount[10];
	_itoa_s(nFields, resultCount, 10);
	string recount = resultCount;
	string returnValue = "Se recibieron " + recount + " resultados.\n\n" + "\tID\tUsername Password\n";
	string getvalue;
	for (i = 0; i < nFields; i++) {
		for (j = 0; j < 3; j++) {
			getvalue.assign(PQgetvalue(res, i, j));
			returnValue += "\t " + getvalue;
		}
		returnValue += " \n";
	}
	return returnValue;
}

void Conexion::borrarJugador(std::string nombreJugador)
{
	if (!conectado)
		printf("Connection Failed: %s\n", PQerrorMessage(dbconn));
	else
	{
		printf("Connected Successfully!\n\n");

		string query = "delete from public.\"Jugadores\" where \"Username\"='" + nombreJugador + "'";

		const char *SQL = query.c_str();

		PQclear(res);

		res = PQexec(dbconn, SQL);
	}
}

void Conexion::borrarJuagdor(int idJugador)
{
	if (!conectado)
		printf("Connection Failed: %s\n", PQerrorMessage(dbconn));
	else
	{
		printf("Connected Successfully!\n\n");

		stringstream query;

		query << "delete from public.\"Jugadores\" where \"ID_Jugador\"='" << idJugador << "'";

		string intermediario = query.str();

		const char *SQL = intermediario.c_str();

		PQclear(res);

		res = PQexec(dbconn, SQL);
	}
}

//-------------------------------------------------
//-------------------------------------------------

void Conexion::agregarJuego(std::string nombreJuego, std::string descripcion)
{
	/*
	if (nombreJuego != "" && descripcion != "")
	{
		if (!conectado)
			printf("Connection Failed: %s\n", PQerrorMessage(dbconn));
		else
		{
			printf("Connected Successfully!\n");

			string query = "select \"Nombre_Juego\" from public.\"Juegos\"";

			const char* SQL = query.c_str();

			sprintf_s(buff, "BEGIN; DECLARE my_portal CURSOR FOR %s", SQL);

			res = PQexec(dbconn, buff);
			if (PQresultStatus(res) != PGRES_COMMAND_OK)
			{
				printf("Error executing SQL!: %s\n", PQerrorMessage(dbconn));
				PQclear(res);
			}
			else
			{
				PQclear(res);
				res = PQexec(dbconn, SQL);

				if (PQresultStatus(res) != PGRES_TUPLES_OK)
				{
					printf("ERROR, Fetch All Failed: %s", PQerrorMessage(dbconn));
					PQclear(res);
				}
				else
				{
					for (i = 0; i < PQntuples(res); i++)
					{
						for (j = 0; j < nFields; j++)
						{
							if (nombreJuego == PQgetvalue(res, i, j))
								return;
						}
					}

					query = "insert into public.\"Juegos\" (\"Nombre_Juego\", \"Descripcion_Juego\") values ('" + nombreJuego + "', '" + descripcion + "')";

					const char* SQL = query.c_str();

					PQclear(res);
					res = PQexec(dbconn, SQL);

					if (PQresultStatus(res) != PGRES_COMMAND_OK)
					{
						printf("ERROR, Fetch All Failed: %s", PQerrorMessage(dbconn));
						PQclear(res);
					}
				}
			}
		}
	}

	res = PQexec(dbconn, "CLOSE my_portal");
	PQclear(res);
	
	res = PQexec(dbconn, "COMMIT");
	PQclear(res);
	PQfinish(dbconn);
	*/
	if (nombreJuego != "" && descripcion != ""){

		string query = "select \"Nombre_Juego\" from public.\"Juegos\"";
		const char * SQL = query.c_str();
		res = PQexec(dbconn, SQL);

		if (PQresultStatus(res) != PGRES_TUPLES_OK){
			cout << "Error al ejecutar la consulta" << endl;
			return;
		}

		nFields = PQntuples(res);

		for (i = 0; i<nFields; i++) {
			for (j = 0; j<1; j++) {
				if (nombreJuego == PQgetvalue(res, i, j)){
					cout << "El Juego ya existe" << endl;
					return;
				}
			}
		}

		query = "insert into public.\"Juegos\" (\"Nombre_Juego\", \"Descripcion_Juego\") values ('" + nombreJuego + "', '" + descripcion + "')";
		SQL = query.c_str();
		res = PQexec(dbconn, SQL);

		if (PQresultStatus(res) != PGRES_COMMAND_OK)	{
			cout << "ERROR al intentar insertar el Juego en la Tabla" << endl;
			return;
		}
		cout << "La operacion de Agregar Juego se realizo con exito" << endl;
	}
	else
		cout << "ERROR. El nombre del Juego no puede ser vacio; la descripcion tampoco" << endl;
}

std::string Conexion::listarJuegos()
{/*
	char *SQL = "select * from public.\"Juegos\"";

	if (!conectado)
		printf("Connection Failed: %s\n", PQerrorMessage(dbconn));
	else
	{
		printf("Connected Successfully!\n");

		sprintf_s(buff, "BEGIN; DECLARE my_portal CURSOR FOR %s", SQL);

		res = PQexec(dbconn, buff);
		if (PQresultStatus(res) != PGRES_COMMAND_OK)
		{
			printf("Error executing SQL!: %s\n", PQerrorMessage(dbconn));
			PQclear(res);
		}
		else
		{
			PQclear(res);
			res = PQexec(dbconn, "FETCH ALL in my_portal");

			if (PQresultStatus(res) != PGRES_TUPLES_OK)
			{
				printf("ERROR, Fetch All Failed: %s", PQerrorMessage(dbconn));
				PQclear(res);
			}
			else
			{
				nFields = PQnfields(res);

				// Print out the field names
				for (i = 0; i < nFields; i++)
					printf("%-15s", PQfname(res, i));

				printf("\n");

				// Print out the rows
				for (i = 0; i < PQntuples(res); i++)
				{
					for (j = 0; j < nFields; j++)
						printf("%-15s", PQgetvalue(res, i, j));

					printf("\n");
				}
			}
		}
	}

	res = PQexec(dbconn, "CLOSE my_portal");
	PQclear(res);
	*/
	/*
	res = PQexec(dbconn, "END");
	PQclear(res);
	PQfinish(dbconn);
	*/
	res = PQexec(dbconn, "select * from public.\"Juegos\"");
	if (PQresultStatus(res) != PGRES_TUPLES_OK){
		return "No se recibieron datos.";
	}
	nFields = PQntuples(res);
	char resultCount[10];
	_itoa_s(nFields, resultCount, 10);
	string recount = resultCount;
	string returnValue = "Se recibieron " + recount + " resultados.\n\n" + "\tID\tJuego\t\tDescripcion\n";
	string getvalue;
	for (i = 0; i < nFields; i++) {
		for (j = 0; j < 3; j++) {
			getvalue.assign(PQgetvalue(res, i, j));
			returnValue += "\t" + getvalue;
		}
		returnValue += " \n";
	}
	return returnValue;
}

void Conexion::borrarJuego(std::string nombreJuego)
{
	if (!conectado)
		printf("Connection Failed: %s\n", PQerrorMessage(dbconn));
	else
	{
		printf("Connected Successfully!\n\n");

		string query = "delete from public.\"Juegos\" where \"Nombre_Juego\"='" + nombreJuego + "'";

		const char *SQL = query.c_str();

		PQclear(res);

		res = PQexec(dbconn, SQL);

		if (PQresultStatus(res) != PGRES_COMMAND_OK)
		{
			printf("Error executing SQL!: %s\n", PQerrorMessage(dbconn));
			PQclear(res);
		}
	}
}

void Conexion::borrarJuego(int idJuego)
{
	if (!conectado)
		printf("Connection Failed: %s\n", PQerrorMessage(dbconn));
	else
	{
		printf("Connected Successfully!\n\n");

		stringstream query;

		query << "delete from public.\"Juegos\" where \"ID_Juego\"='" << idJuego << "'";

		string intermediario = query.str();

		const char *SQL = intermediario.c_str();

		PQclear(res);

		res = PQexec(dbconn, SQL);
	}
}

//-------------------------------------------------
//-------------------------------------------------

std::string Conexion::listarHighScores(Filtro filtro, std::string especificacion)
{
	/*
	if (!conectado)
		printf("Connection Failed: %s\n", PQerrorMessage(dbconn));
	else
	{
		printf("Connected Successfully!\n\n");

		string query = "select * from public.\"HighScores\"";
			
		if (filtro == Filtro::Todo)
			printf("En pantalla se muestran todas las tuplas de la tabala. Si desea restringir la busqueda debe especificar un criterio\n\n");

		else if (filtro == Filtro::Juego)
		{
			if (especificacion != "" )
				query += " where \"Juego\" = (select \"ID_Juego\" from public.\"Juegos\" where \"Nombre_Juego\" = '" + especificacion + "')";
			else
				printf("Debe especificar el criterio de busqueda. ERROR\n");
		}

		else if (filtro == Filtro::Jugador)
		{
			if (especificacion != "")
			{
				query += " where \"Jugador\" = (select \"ID_Jugador\" from public.\"Jugadores\" where \"Username\" = '" + especificacion + "')";
			}
			else
				printf("Debe especificar el criterio de busqueda. ERROR\n");
		}

		const char *SQL = query.c_str();

		sprintf_s(buff, "BEGIN; DECLARE my_portal_HS CURSOR FOR %s", SQL);

		res = PQexec(dbconn, buff);
		if (PQresultStatus(res) != PGRES_COMMAND_OK)
		{
			printf("Error executing SQL!: %s\n", PQerrorMessage(dbconn));
			PQclear(res);
		}
		else
		{
			PQclear(res);
			res = PQexec(dbconn, "FETCH ALL in my_portal_HS");

			if (PQresultStatus(res) != PGRES_TUPLES_OK)
			{
				printf("ERROR, Fetch All Failed: %s", PQerrorMessage(dbconn));
				PQclear(res);
			}
			else
			{
				nFields = PQnfields(res);

				// Print out the field names
				for (i = 0; i < nFields; i++)
					printf("%-10s", PQfname(res, i));

				printf("\n");

				// Print out the rows
				for (i = 0; i < PQntuples(res); i++)
				{
					for (j = 0; j < nFields; j++)
						printf("%-10s", PQgetvalue(res, i, j));

					printf("\n");
				}
			}
		}
	}
	
	res = PQexec(dbconn, "CLOSE my_portal_HS");
	PQclear(res);
	
	res = PQexec(dbconn, "COMMIT");
	PQclear(res);
	*/
	if (!conectado)
		printf("Connection Failed: %s\n", PQerrorMessage(dbconn));
	else
	{
		printf("Connected Successfully!\n\n");

		string query = "select * from public.\"HighScores\"";

		if (filtro == Filtro::Todo)
			printf("En pantalla se muestran todas las tuplas de la tabala. Si desea restringir la busqueda debe especificar un criterio\n\n");

		else if (filtro == Filtro::Juego)
		{
			if (especificacion != "")
				query += " where \"Juego\" = (select \"ID_Juego\" from public.\"Juegos\" where \"Nombre_Juego\" = '" + especificacion + "')";
			else
				printf("Debe especificar el criterio de busqueda. ERROR\n");
		}

		else if (filtro == Filtro::Jugador)
		{
			if (especificacion != "")
			{
				query += " where \"Jugador\" = (select \"ID_Jugador\" from public.\"Jugadores\" where \"Username\" = '" + especificacion + "')";
			}
			else
				printf("Debe especificar el criterio de busqueda. ERROR\n");
		}

		const char * q = query.c_str();

		res = PQexec(dbconn, q);

		if (PQresultStatus(res) != PGRES_TUPLES_OK){
			return "No se recibieron datos.";
		}

		nFields = PQntuples(res);
		char resultCount[10];
		_itoa_s(nFields, resultCount, 10);
		string recount = resultCount;
		string returnValue = "Se recibieron " + recount + " resultados.\n\n" + "\tID_HS\tJuego\tJugador\tPuntuacion\n";
		string getvalue;

		for (i = 0; i < nFields; i++) {

			for (j = 0; j < 4; j++) {

				getvalue.assign(PQgetvalue(res, i, j));
				returnValue += "\t" + getvalue;
			}

			returnValue += " \n";
		}

		return returnValue;
	}
}

void Conexion::borrarHighScores(std::string nombreJugador, std::string nombreJuego, int puntaje)
{
	char puntajeArray[100];

	_itoa_s(puntaje, puntajeArray, 10);

	if (!conectado)
		printf("Connection Failed: %s\n", PQerrorMessage(dbconn));
	else
	{
		printf("Connected Successfully!\n\n");

		string query = "delete from public.\"HighScores\" where \"Jugador\" = (select \"ID_Jugador\" from public.\"Jugadores\" where \"Username\" = '" + nombreJugador + "') and \"Juego\" = (select \"ID_Juego\" from public.\"Juegos\" where \"Nombre_Juego\" = '" + nombreJuego + "') and \"Puntuacion\" = " + puntajeArray;

		const char *SQL = query.c_str();

		PQclear(res);

		res = PQexec(dbconn, SQL);
	}
}

//-------------------------------------------------
//-------------------------------------------------

std::string Conexion::listarSavedGames(Filtro filtro, std::string especificacion)
{
	if (!conectado)
		printf("Connection Failed: %s\n", PQerrorMessage(dbconn));
	else
	{
		printf("Connected Successfully!\n\n");

		string query = "select * from public.\"SavedGames\"";

		if (filtro == Filtro::Todo)
			printf("En pantalla se muestran todas las tuplas de la tabala. Si desea restringir las busqueda debe especificar un criterio\n\n");

		else if (filtro == Filtro::Juego)
		{
			if (especificacion != "")
				query += " where \"Juego\" = (select \"ID_Juego\" from public.\"Juegos\" where \"Nombre_Juego\" = '" + especificacion + "')";
			else
				printf("Debe especificar el criterio de busqueda. ERROR\n");
		}

		else if (filtro == Filtro::Jugador)
		{
			if (especificacion != "")
			{
				query += " where \"Jugador\" = (select \"ID_Jugador\" from public.\"Jugadores\" where \"Username\" = '" + especificacion + "')";
			}
			else
				printf("Debe especificar el criterio de busqueda. ERROR\n");
		}

		const char * q = query.c_str();

		res = PQexec(dbconn, q);

		if (PQresultStatus(res) != PGRES_TUPLES_OK){
			return "No se recibieron datos.";
		}

		nFields = PQntuples(res);
		char resultCount[10];
		_itoa_s(nFields, resultCount, 10);
		string recount = resultCount;
		string returnValue = "Se recibieron " + recount + " resultados.\n\n" + "\tID_Saved_Game\tFecha/Hora\t\Nombre_partida\tData\tJuego\tJugador\n";
		string getvalue;

		for (i = 0; i < nFields; i++) {

			for (j = 0; j < 6; j++) {

				getvalue.assign(PQgetvalue(res, i, j));
				returnValue += "\t" + getvalue;
			}

			returnValue += " \n";
		}

		return returnValue;
	}
}

void Conexion::borrarSavedGame(std::string nombreJugador, std::string nombreJuego)
{
	if (!conectado)
		printf("Connection Failed: %s\n", PQerrorMessage(dbconn));
	else
	{
		printf("Connected Successfully!\n\n");

		string query = "delete from public.\"SavedGames\" where \"Jugador\" = (select \"ID_Jugador\" from public.\"Jugadores\" where \"Username\" = '" + nombreJugador + "') and \"Juego\" = (select \"ID_Juego\" from public.\"Juegos\" where \"Nombre_Juego\" = '" + nombreJuego + "')";

		const char *SQL = query.c_str();

		PQclear(res);

		res = PQexec(dbconn, SQL);
	}
}

//--------------------------------------------------
//--------------------------------------------------

std::string Conexion::listarRegistros(Filtro filtro, std::string especificacion)
{
	if (!conectado)
		printf("Connection Failed: %s\n", PQerrorMessage(dbconn));
	else
	{
		printf("Connected Successfully!\n\n");

		string query = "select * from public.\"RegistroDeUso\"";

		if (filtro == Filtro::Todo)
			printf("En pantalla se muestran todas las tuplas de la tabala. Si desea restringir las busqueda debe especificar un criterio\n\n");

		else if (filtro == Filtro::Juego)
		{
			if (especificacion != "")
				query += " where \"Juego\" = (select \"ID_Juego\" from public.\"Juegos\" where \"Nombre_Juego\" = '" + especificacion + "')";
			else
				printf("Debe especificar el criterio de busqueda. ERROR\n");
		}

		else if (filtro == Filtro::Jugador)
		{
			if (especificacion != "")
			{
				query += " where \"Jugador\" = (select \"ID_Jugador\" from public.\"Jugadores\" where \"Username\" = '" + especificacion + "')";
			}
			else
				printf("Debe especificar el criterio de busqueda. ERROR\n");
		}

		const char * q = query.c_str();

		res = PQexec(dbconn, q);
		
		if (PQresultStatus(res) != PGRES_TUPLES_OK){
			return "No se recibieron datos.";
		}
		
		nFields = PQntuples(res);
		char resultCount[10];
		_itoa_s(nFields, resultCount, 10);
		string recount = resultCount;
		string returnValue = "Se recibieron " + recount + " resultados.\n\n" + "\tID_Reg\tJuego\tJugador\tFecha/Hora\n";
		string getvalue;
		
		for (i = 0; i < nFields; i++) {
		
			for (j = 0; j < 4; j++) {

				getvalue.assign(PQgetvalue(res, i, j));
				returnValue += "\t" + getvalue;
			}
			
			returnValue += " \n";
		}
		
		return returnValue;
	}
}

void Conexion::borrarRegistros(std::string nombreJugador, std::string nombreJuego)
{
	if (!conectado)
		printf("Connection Failed: %s\n", PQerrorMessage(dbconn));
	else
	{
		printf("Connected Successfully!\n\n");

		string query = "delete from public.\"RegistroDeUso\" where \"Jugador\" = (select \"ID_Jugador\" from public.\"Jugadores\" where \"Username\" = '" + nombreJugador + "') and \"Juego\" = (select \"ID_Juego\" from public.\"Juegos\" where \"Nombre_Juego\" = '" + nombreJuego + "')";

		const char *SQL = query.c_str();

		PQclear(res);

		res = PQexec(dbconn, SQL);
	}
}

/*void main()
{
	char *db = "DataJuegos";
	char *dbserver = "127.0.0.1";
	char *uname = "postgre";
	char *pass = "admin";

	char *SQL = "select * from public.Juegos;";
	// char *SQL      = "select userid, stationid from public.auditlog";

	char     buff[200];
	PGconn   *dbconn;
	PGresult *res;

	int nFields, i, j;

	printf("Attempting to Connect to Database Server:\n");
	printf("Database: %s\n", db);
	printf("Server  : %s\n", dbserver);

	sprintf_s(buff, "dbname=%s host=%s port=5432 user=%s password=%s",
		db, dbserver, uname, pass);

	dbconn = PQconnectdb(buff);

	if (PQstatus(dbconn) != CONNECTION_OK)
		printf("Connection Failed: %s\n", PQerrorMessage(dbconn));
	else
	{
		printf("Connected Successfully!\n");

		sprintf_s(buff, "BEGIN; DECLARE my_portal CURSOR FOR %s", SQL);

		res = PQexec(dbconn, buff);
		if (PQresultStatus(res) != PGRES_COMMAND_OK)
		{
			printf("Error executing SQL!: %s\n", PQerrorMessage(dbconn));
			PQclear(res);
		}
		else
		{
			PQclear(res);
			res = PQexec(dbconn, "FETCH ALL in my_portal");

			if (PQresultStatus(res) != PGRES_TUPLES_OK)
			{
				printf("ERROR, Fetch All Failed: %s", PQerrorMessage(dbconn));
				PQclear(res);
			}
			else
			{
				nFields = PQnfields(res);

				// Print out the field names
				for (i = 0; i<nFields; i++)
					printf("%-15s", PQfname(res, i));

				printf("\n");

				// Print out the rows
				for (i = 0; i<PQntuples(res); i++)
				{
					for (j = 0; j<nFields; j++)
						printf("%-15s", PQgetvalue(res, i, j));

					printf("\n");
				}

				res = PQexec(dbconn, "END");
				PQclear(res);
			}
		}

	}


	PQfinish(dbconn);
}*/