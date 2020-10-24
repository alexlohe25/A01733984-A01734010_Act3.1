#ifndef PRIORITY_QUEUE_H_INCLUDED
#define PRIORITY_QUEUE_H_INCLUDED
#include <vector>
//clase priority queue, que se encarga de representar un max heap en un vector
class priority_queue{
	private:
		//vector del heap
		std::vector <int> filaPriorizada;
		//tamanio del heap
		int tamanio;
	public:
		priority_queue();
		void push(int);
		void heapifyPadre(int);
		void heapifyIzqDer(int);
		int pop();
		void print();
		int top();
		bool empty();
		int size();
		int getIzq(int);
		int getDer(int);
		int getPadre(int);
};
//constructor de la clase
priority_queue::priority_queue(){
	tamanio = 0;
}
//metodo push, que agrega un nodo al vector y verifica su orden con un heapify del fondo hacia la raíz.
//Recibe un valor entero y no retorna nada, pero modifica los atributos del objeto
//Orden O(n) 
void priority_queue::push(int valor){
	if (tamanio == 0){
		filaPriorizada.push_back(valor);
		tamanio++;
	}
	else{
		bool flagEqual = false;
		for (int i = 0; i < tamanio; i++)
			if (filaPriorizada[i] == valor)
				flagEqual = true;
		if (flagEqual == false){
			tamanio++;
			filaPriorizada[tamanio - 1] = valor;
			heapifyPadre(tamanio - 1);
		}
	}
}
//metodo heapifyPadre, que verifica el ordenamiento del heap obteniendo el padre de un nodo y comparándose
//con el. Si el nodo resulta mayor que su padre, se intercambia
//orden O(log n)
void priority_queue::heapifyPadre(int i){
	int padre = getPadre(i);
	if (filaPriorizada[padre] > 0){
		if (filaPriorizada[i] > filaPriorizada[padre]){
			int temp = filaPriorizada[i];
			filaPriorizada[i] = filaPriorizada[padre];
			filaPriorizada[padre] = temp;
			heapifyPadre(padre);
		} 
	}
}
//metodo pop, que elimina la raiz, pone el ultimo valor como raiz temporal
// y verifica su orden con un heapify de la raiz hasta el fondo
//Recibe un valor entero y retorna la raiz a eliminar, pero modifica los atributos del objeto
//Orden O(1) 
int priority_queue::pop(){
	int raiz;
	if (tamanio == 0)
		raiz = -1;
	else{
		raiz = filaPriorizada[0];
		int final = filaPriorizada[tamanio - 1];
		filaPriorizada[0] = final;
		filaPriorizada.pop_back();
		tamanio--;
		heapifyIzqDer(0);
	}
	return raiz;
}
//metodo heapifyPadre, que verifica el ordenamiento del heap obteniendo los nodos hijo y comparandose cada uno
//con el. Si el nodo resulta menor que su hijo, se intercambia
//Orden O(log n)
void priority_queue::heapifyIzqDer(int i){
	int indexRaiz = i;
	int izq = getIzq(i);
	int der = getDer(i);
	if (izq < tamanio && filaPriorizada[izq] > filaPriorizada[indexRaiz])
		indexRaiz = izq;
	if (der < tamanio && filaPriorizada[der] > filaPriorizada[indexRaiz])
		indexRaiz = der;
	if(indexRaiz != i){

		int temp = filaPriorizada[i];
		filaPriorizada[i] = filaPriorizada[indexRaiz];
		filaPriorizada[indexRaiz] = temp;
		heapifyIzqDer(indexRaiz);
	}
}
//metodo print, que imprime el contenido de la fila
//no recibe nada pero imprime el atributo del vector
//Orden O(1), puesto que recorre todo el vector
void priority_queue::print(){
	for (int i = 0; i < tamanio; i++)
		std::cout << filaPriorizada[i] << " ";
	std::cout << std::endl;
}
//metodo top, que retorna el primer valor del vector
//no recibe nada pero retorna el primer valor
//Orden O(1)
int priority_queue::top(){
	if (!filaPriorizada.empty())
		return filaPriorizada[0];
	return -1;
}
//metodo empty, que determina si el vector está vacío
//no recibe nada, pero retorna un bool
//OrdenO(1)
bool priority_queue::empty(){
	return filaPriorizada.empty();
}
//metodo size, obtiene el tamaño del arbol
//no recibe nada, pero retorna un entero
//Orden O(1)
int priority_queue::size(){
	return tamanio;
}
//getters con orden O(1)
int priority_queue::getIzq(int k){
	return (2*k) + 1;
}
int priority_queue::getDer(int k){
	return (2*k) + 2;
}
int priority_queue::getPadre(int k){
	return k/2;//2 + 1;
}
#endif