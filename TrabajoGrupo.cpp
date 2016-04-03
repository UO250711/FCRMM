#include <iostream>
#include <stdlib.h>
#include <cstdlib>
#include <time.h>
#include <string>

using namespace std;

const int N_MAX_INTENTOS = 5;
const int N_COLORES = 6;
const int N_COLORES_CLAVE = 4;
const int CARACTER_INICIAL = 'A';
const string LICENCIA = "Trabajo grupo FCyR";
const int CARACTER_FINAL = CARACTER_INICIAL + N_COLORES;
char Clave[N_COLORES_CLAVE + 1] = "ABCD";

extern "C" int calculaNMuertosASM(char propuesta[], char clave[], int nElementos);

/*
* Lee la licencia del programa y comprueba q sea valida. 
* La licencia debe ser como máximo de 20 caracteres. 
*
*/
bool leeLicencia(){
	char licencia[20]; 
	cout << "Introduce la licencia]: " << endl;
	cin.getline(licencia,20);	
	return (strlen(licencia) <= 20 && licencia == LICENCIA);
}

/*
* Función pseudo-aleatoria para generar la clave a partir de valor[]
*
*/
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
* Comprueba que los datos introducidos sean entre el rango ASCII CARACTER_INICIAL y CARACTER_FINAL
*
*/
bool compruebaRangoCaraceteres(char propuesta[], int nElementos)
{	
	for (int i = 0; i < nElementos; i++)
		if (!(propuesta[i] >= CARACTER_INICIAL && propuesta[i] < CARACTER_FINAL))
			return false;
			return true;
}
/*
* Comprueba que los datos introducidos no contengan ningun caracter repetido. 
*
*/
bool compruebaCaracteresRepetidos(char propuesta[], int nElementos)
{
	int i, j;
	for (i = 0; i < nElementos; i++)
		for (j = i + 1; j < nElementos; j++)
			if (propuesta[i] == propuesta[j])
				return false;
				return true;
}
/*
* Calcula y devuelve el numero de muertos o posiciones exactas acertadas
*
*/
int calculaNMuertos(char propuesta[], char solucion[], int nElementos)
{
	int nMuertos = 0;
	for (int i = 0; i < nElementos; i++){
		if (propuesta[i] == solucion[i])
			nMuertos++;
	}
	return nMuertos;
}
/*
* Calcula y devuelve el numero de heridos o posiciones no exactas acertadas
*
*/

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

/*
* Aplicación principal main(). 
* Comprueba licencia y condiciones. Permite hasta un numero maximo de N_MAX_INTENTOS intentos. 
*/

int main()
{
	// leemos los datos de la licencia y si son incorrectos , salimos del programa. 
	if (leeLicencia() == false){
		printf("Error en licencia\n");
		exit(EXIT_FAILURE);
	}
	
	// declaración de variables locales 
	int nMuertos = 0;
	int nHeridos = 0;
	int nIntentos = 0;
	char intento[N_COLORES_CLAVE + 1];
	int contador_intentos = 0;
	// semilla y generación pseudo-aleatoria de clave. 
	srand((unsigned int)time(NULL));
	generaClave(Clave, N_COLORES_CLAVE, CARACTER_INICIAL, CARACTER_FINAL);
	
	// empieza el juego hasta agotar N_MAX_INTENTOS
	while (contador_intentos != N_MAX_INTENTOS)
	{
		//cout << Clave << endl; // quitar para la version final 
		// incrementamos intentos 
		contador_intentos++;
		// preguntamos al jugador y leemos
		cout << "Introduce intento: ";
		cin >> intento;
		// Si se introducen valores repetidoso valores fuera del rango, avisa pero cuenta como un intento. 
		cout << "Este es tu intento numero " << contador_intentos << endl;
		if (compruebaCaracteresRepetidos(intento, N_COLORES_CLAVE) == false)
		{
			cout << "No se permiten valores repetidos en la jugada" << endl;
		}
		else if (compruebaRangoCaraceteres(intento, N_COLORES_CLAVE) == false)
		{
			cout << "No se permiten valores fueran del rango en la jugada" << endl;
		}
		else
		{

			// calculamos muertos (ASM) y heridos. 
			nMuertos = calculaNMuertosASM(intento, Clave, N_COLORES_CLAVE);
			nHeridos = calculaNHeridos(intento, Clave, N_COLORES_CLAVE);
			cout << "Hay " << nHeridos << " Heridos " << " y " << nMuertos << " Muertos" << endl;

			// si tenemos 4 muertos, juego ganado. 
			if (nMuertos == 4)
			{
				cout << "Correcto ! Has ganado en el intento numero " << contador_intentos << endl;
				exit(EXIT_FAILURE);
			}
		}
	}

	// Juego perdido
	if (contador_intentos == N_MAX_INTENTOS){
		cout << "Has perdido :(" << endl;
		cout << "La clave era:  " << Clave << endl;
	}
	return 0;
}