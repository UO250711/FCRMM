#include <iostream>
#include <stdlib.h>
#include <cstdlib>
#include <time.h>
#include <string>

using namespace std;

const int N_MAX_INTENTOS = 15;
const int N_COLORES = 6;
const int N_COLORES_CLAVE = 4;
const int CARACTER_INICIAL = 'A';
const string LICENCIA = "Trabajo Grupo FCyR";
const int CARACTER_FINAL = CARACTER_INICIAL + N_COLORES;

char Clave[N_COLORES_CLAVE + 1] = "ABCD";

extern "C" int calculaNMuertosASM(char propuesta[], char clave[], int nElementos);

bool leeLicencia(string licencia){
	if (licencia == LICENCIA)
	{
		return true;
	}
	return false;
}

void generaClave(char valor[], int nValores, int minimo, int maximo)
{
	int aleatorio = 0;
	int generados = 0;
	int i = 0;
	bool repetido = false;

	while (generados != nValores)
	{
		// Genera un número aleatorio entre máximo y mínimo
		// minimo = codigo ASCII del primer caracter valido
		// maximo = codigo ASCII del ultimo caracter valido

		aleatorio = (int)(((double)rand() / (RAND_MAX + 1)) * (maximo - minimo) + minimo);

		// Se comprueba que el caracter no ha sido generado antes
		repetido = false;
		i = 0;
		while ((!repetido) && (i < generados))
		{
			repetido = (aleatorio == valor[i]);
			i++;
		}

		// Si el caracter no está repetido, se añade como válido a la clave
		if (!repetido)
		{
			valor[generados] = (char)aleatorio;
			generados++;
		}
	}
	// Hay que añadir el terminador de cadenas a la clave generada. Tiene que estar en la última posición del array 
	valor[nValores] = '\0';
}

/*
* Revisa si en la entrada de datos hay caracteres fuera del rango.  
*
*/
bool revisaRango(char propuesta[], int nElementos)
{
	int i;
	for (i = 0; i < nElementos; i++)
		if (propuesta[i] >= CARACTER_INICIAL && propuesta[i] < CARACTER_FINAL)
		{
		}
		else{
			return false;
		}		
}

/*
* Encuentra repetidos en la propuesta
* Si algun caracter introducido está repetido da error.
*
*/
bool revisaRepetidos(char propuesta[], int nElementos)
{
	int i, j;
	for (i = 0; i < nElementos; i++)
		for (j = i + 1; j < nElementos; j++)
			if (propuesta[i] == propuesta[j])
				return false;
				return true;
}

int calculaNMuertos(char propuesta[], char solucion[], int nElementos)
{
	int nMuertos = 0;
	for (int i = 0; i < nElementos; i++){

		if (propuesta[i] == solucion[i])
			nMuertos++;
	}
	return nMuertos;


}
int calculaNHeridos(char propuesta[], char solucion[], int nElementos)
{
	int nHeridos = 0;
	for (int i = 0; i < nElementos; i++)
	{
		if (propuesta[0] == solucion[i] || propuesta[1] == solucion[i] || propuesta[2] == solucion[i] || propuesta[3] == solucion[i])
		{
			if (propuesta[i] != solucion[i])
			{
				nHeridos++;
			}
		}
	}
	return nHeridos;
}

int main()
{
	// leemos los datos de la licencia
	string licencia;
	cout << "Para poder jugar, introduce la licencia: " << endl;
	getline(cin, licencia);
	if (leeLicencia(licencia) == false){
		printf("Error en licencia\n");
		//exit(EXIT_FAILURE);
	}

	// comienza el juego 
	int nMuertos = 0;
	int nHeridos = 0;
	int nIntentos = 0;
	char intento[N_COLORES_CLAVE + 1];
	srand((unsigned int)time(NULL));
	generaClave(Clave, N_COLORES_CLAVE, CARACTER_INICIAL, CARACTER_FINAL);
	int contador_intentos = 0;

	while (contador_intentos != N_MAX_INTENTOS)
	{
		cout << Clave << endl;
		contador_intentos++;
		cout << "Introduce intento: ";
		cin >> intento;
		// Si se introducen valores repetidos se avisa. 
		// Cuenta como un intento 
		cout << "Este es tu intento numero " << contador_intentos << endl;
		if (revisaRepetidos(intento, N_COLORES_CLAVE) == false)
		{
			cout << "No se permiten valores repetidos en la jugada" << endl;
		}
		else if (revisaRango(intento, N_COLORES_CLAVE) == false)
		{
			cout << "No se permiten valores fueran del rango en la jugada" << endl;
		}
		else
		{

			// calculamos muertos y heridos. 
			nMuertos = calculaNMuertos(intento, Clave, N_COLORES_CLAVE);
			nHeridos = calculaNHeridos(intento, Clave, N_COLORES_CLAVE);
			cout << "Hay " << nHeridos << " Heridos " << " y " << nMuertos << " Muertos" << endl;

			// Juego ganado 
			if (nMuertos == 4)
			{
				cout << "Has ganado en el intento numero " << contador_intentos << endl;
				exit(EXIT_FAILURE);
			}
		}
	}

	// Juego perdido
	if (contador_intentos == N_MAX_INTENTOS){
		cout << "Has perdido :(" << endl;
	}
	return 0;
}