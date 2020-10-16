#include <iostream>
#include <queue>
using namespace std;
struct Node{
    int info;
    struct Node* izq;
    struct Node* der;
};
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
void traversal(Node* raiz, int opcion){
    switch (opcion){
        case 1:
            preOrden(raiz);
            cout << endl;
        break;
        case 2:
            inOrden(raiz);
            cout << endl;
        break;
        case 3:
            postOrden(raiz);
            cout << endl;
        break;
        case 4:
            levelByLevel(raiz);
            cout << endl;
        break;
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
    int n;
    cin >> n;
    for (int i = 0; i < n; i++){
        int valor;
        cin >> valor;
        agregaNodo(raiz, valor);
    }
    traversal(raiz, 1);
    traversal(raiz, 2);
    traversal(raiz, 3);
    traversal(raiz, 4);
    cout << height(raiz) << endl;
    cout << whatLevelAmI(raiz, 30, 0) << endl;
    cout << whatLevelAmI(raiz, 28, 0) << endl;
    cout << whatLevelAmI(raiz, 11, 0) << endl;
    cout << whatLevelAmI(raiz, 5, 0) << endl;
    return 0;
}
