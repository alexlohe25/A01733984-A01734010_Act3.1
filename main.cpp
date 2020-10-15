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
int whatLevelAmI(Node* raiz, int valor, int nivel){
    if (raiz != NULL){
        if (valor == raiz -> info)
            return nivel;
        if (valor < raiz -> info)
            return whatLevelAmI(raiz -> izq, valor, nivel + 1);
        if (valor > raiz -> info)
            return whatLevelAmI(raiz -> der, valor, nivel + 1);
    }
    return -1;
}
int main(){
    Node* raiz = NULL;
    agregaNodo(raiz, 5);
    agregaNodo(raiz, 6);
    agregaNodo(raiz, 3);
    cout << whatLevelAmI(raiz, 5, 0) << endl;
    cout << whatLevelAmI(raiz, 6, 0) << endl;
    cout << whatLevelAmI(raiz, 3, 0) << endl;
    cout << whatLevelAmI(raiz, 4, 0) << endl;
    return 0;
}
