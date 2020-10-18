/*
    TC1031.500 Actividad 3.1 Operaciones avanzadas en un BST 
    Código elaborado por: 
    Alejandro López Hernández A01733984
    Juan Pablo Armendáriz Salas A01734010
    Fecha: 18/Oct/2020
    Programa dedicado al uso de operaciones en un Arbol Binario de Busqueda (BST), incluyendo inserciones y eliminaciones de nodos
    Impresión del arbol en PreOrden , InOrden, PsotOrden y por niveles; así como la altura del árbol, obtener los ancestros de un nodo
    y el nivel en que se encuentra el nodo en el arbol
*/
#include <iostream>
#include <queue>
using namespace std;
//estructura del nodo
struct Node{
    int info;
    struct Node* izq;
    struct Node* der;
};
// impresiones recursivas del arbol, todos se ejecutan en un orden O(n), puesto que se ejecuta n veces según los nodos del arbol
void preOrden(Node* r){
    if (r != NULL){
        cout << r -> info << " ";
        preOrden(r -> izq);
        preOrden(r -> der);
    }
}
void inOrden(Node* r){
    if (r != NULL){
        inOrden(r -> izq);
        cout << r-> info << " ";
        inOrden(r -> der);
    }
}

void postOrden(Node *r){
    if (r != NULL){
        postOrden(r -> izq);
        postOrden(r -> der);
        cout << r-> info << " ";
    }
}
//levelByLevel, que hace uso de una pila para guardar los nodos de tal manera que se impriman los nodos según en el nivel del árbol 
//en el que se encuentran,  es de Orden O(n) puesto que se ejecuta n veces según la cantidad de nodos
void levelByLevel(Node* r){
    queue <Node*> niveles;
    if (r != NULL){
        niveles.push(r);
        while (!niveles.empty()){
            Node * temp = niveles.front();
            niveles.pop();
            cout << temp -> info << " ";
            if (temp -> izq != NULL)
            niveles.push(temp -> izq);
            if (temp -> der != NULL)
            niveles.push(temp->der);
        }
    }
}
//height, determina la altura del BST comparando la altura de ambos lados y tomando la que sea mayor, es de orden O(n log n) 
int height(Node* r){
    if (r == NULL)
        return 0;
    int ladoIzq = height(r -> izq);
    int ladoDer = height(r -> der);
    if (ladoIzq > ladoDer)
        return ladoIzq + 1;
    else
        return ladoDer + 1;
}
//funcion ancestors, que imprime una lista de los ancestros de determinado nodo, es de orden O(n)
void ancestors(Node* nodo, int valor, queue <int> & ancestros){
    if (nodo != NULL){
        if (valor == nodo -> info){
            while (!ancestros.empty()){
                cout << ancestros.front() << " ";
                ancestros.pop();
            }
            cout << endl;
        }
        else{
            ancestros.push(nodo-> info);
            if (valor < nodo -> info)
                ancestors(nodo -> izq, valor, ancestros);
            if (valor > nodo -> info)
                ancestors(nodo -> der, valor, ancestros);            
        }
    }
}
//generaNodo, que guarda dinamicamente un nuevo ndo, orden O(1)
Node* generarNodo(int valor){
  Node* tmp = new Node;
  tmp -> info = valor;
  tmp -> der = NULL;
  tmp -> izq = NULL;
  return tmp;
}
//agregaNodo, agregar un nuevo nodo al BST según su valor. Orden(log n)
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
//cambio, obtiene el valor más pequeño de la derecha de un nodo. O(n)
Node* cambio(Node* raiz){
  if(raiz == NULL){
    return NULL;
  }
  if(raiz -> izq){
    return cambio(raiz -> izq);
  }
  else{
    return raiz;
  }
}
//elimina, elimina un nodo con determindao valor. O (log n)
Node* elimina(Node* r, int valor){
    if (r == NULL){
        return r;
    }
    if (valor < r -> info){
        r -> izq = elimina(r -> izq, valor);
        return r;
    }
    else if (valor > r -> info){
        r -> der = elimina(r->der, valor);
        return r;
    }
    else{
        if (r -> izq == NULL){
            Node* temp = r -> der;
            delete r;
            return temp;
        }
        else if (r -> der == NULL){
            Node * temp = r -> izq;
            delete r;
            return temp;
        }
        Node* temp2Hijos = cambio(r -> der);
        r -> info = temp2Hijos -> info;
        r -> der = elimina(r -> der, temp2Hijos -> info);
    }
    return r;
}
//funcion traversal, imprime el arbol en un orden determinado por una opcion. O(1)
void traversal(Node* raiz, int opcion){
    switch (opcion){
        case 1:
        if (raiz != NULL){
            preOrden(raiz);
            cout << endl;
        }
        break;
        case 2:
            if (raiz != NULL){
                inOrden(raiz);
                cout << endl;
            }
        break;
        case 3:
            if (raiz != NULL){
                postOrden(raiz);
                cout << endl;
            }
        break;
        case 4:
            if (raiz != NULL){
                levelByLevel(raiz);
                cout << endl;
            }
        break;
    }
}
//whatLevelAmI, obtiene el nivel del BST en el que está un determinado nodo, si no lo encuentra retorna -1. O(log n)
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
//main, ejecuta todo
int main(){
    Node* raiz = NULL;
    int n, m , q, r;
    cin >> n;
    for (int i = 0; i < n; i++){
        int valorAdd;
        cin >> valorAdd;
        agregaNodo(raiz, valorAdd);
    }
    cin >> m;
    for (int i = 0; i < m; i++){
        int valorDelete;
        cin >> valorDelete;
        if (raiz != NULL)
            raiz = elimina(raiz, valorDelete);
    }
    for (int i = 1; i <= 4; i++)
        traversal(raiz,i);
    cout << height(raiz) << endl;
    cin >> q;
    for (int i = 0; i < q; i++){
        queue <int> ancestros;
        int valorAncestro;
        cin >> valorAncestro;
        ancestors(raiz, valorAncestro, ancestros);
    }
    cin >> r;
    for (int i = 0; i < r; i++){
        int valorNivel;
        cin >> valorNivel;
        cout << whatLevelAmI(raiz, valorNivel, 0) << endl;
    }
    return 0;
}