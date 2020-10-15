#include <iostream>
using namespace std;
struct Node{
    int info;
    struct Node* izq;
    struct Node* der;
};

Node* generarNodo(int valor){
  Node* tmp = new Node;
  tmp -> info = valor;
  tmp -> der = NULL;
  tmp -> izq = NULL;

  return tmp;
}
void agregaNodo (Node* &raiz, int valor){
    if (raiz == NULL){
        Node* nodo = generarNodo(valor);
        raiz = nodo;
    }
    else{
        if(valor < raiz -> info)
            agregaNodo(raiz -> izq, valor);
        if(valor > raiz -> info)
            agregaNodo(raiz -> der, valor);
    }
}
int main(){
    Node* raiz = NULL;
    agregaNodo(raiz, 5);
    agregaNodo(raiz, 6);
    agregaNodo(raiz, 3);
    return 0;
}
