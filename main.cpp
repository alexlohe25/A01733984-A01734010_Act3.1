/*
	TC1031.500 Actividad 3.2 Árbol Heap: Implementando una fila priorizada
	Código por: 
		Juan Pablo Armendáriz Salas A01734010
		Alejandro López Hernández A01733984
	Fecha: 24/Oct/2020
	Código que accede a la clase priority queue que, dependiendo de la opcion de un menú
	realiza operaciones un árbol Max Heap representado en un vector
	Las operacion: Agregar, Eliminar raíz, imprimir, mostrar la raíz, verificar si es vacío
	y determinar el tamaño del heap
*/
#include <iostream>
#include <vector>
#include "priority_queue.h"
using namespace std;
// main del codigo que contiene el menu
int main(){
	//instancia del objeto
	priority_queue listaPriorizada;
	int opcion, valor;
	bool isEmpty;
	cin >> opcion;
	while (opcion > 0 && opcion <7){
		switch(opcion){
			case 1:
				cin >> valor;
				listaPriorizada.push(valor);
			break;
			case 2:
				cout << listaPriorizada.pop() << endl;
			break;
			case 3:
				listaPriorizada.print();
			break;
			case 4:
				cout << listaPriorizada.top() << endl;
			break;
			case 5:
				isEmpty = listaPriorizada.empty();
				cout << (isEmpty ? "true" : "false") << endl;
			break;
			case 6:
				cout << listaPriorizada.size() << endl;
			break;
		}
		cin >> opcion;
	}	
	return 0;
}