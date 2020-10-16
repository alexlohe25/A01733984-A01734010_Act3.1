#include <iostream>
using namespace std;

struct Node{
    int info;
    struct Node* izq;
    struct Node* der;
    struct Node* padre;
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

Node* generarNodo(int valor, Node* padre){
  Node* tmp = new Node;
  tmp -> info = valor;
  tmp -> der = NULL;
  tmp -> izq = NULL;
  tmp -> padre = padre;
  return tmp;
}

void agregaNodo (Node* &raiz, int valor, Node* padre){
    if (raiz == NULL){
        Node* nodo = generarNodo(valor, padre);
        raiz = nodo;
    }
    else{
        if(valor < raiz -> info)
            agregaNodo(raiz -> izq, valor, raiz);
        if(valor > raiz -> info)
            agregaNodo(raiz -> der, valor, raiz);
    }
}

void deleteMemoria(Node* raiz){
  raiz -> izq = NULL;
  raiz -> der = NULL;
  delete raiz;
}

Node* siguiente(Node* raiz){
  if(raiz == NULL){
    return NULL;
  }
  else if(raiz -> izq){
    return siguiente(raiz -> izq);
  }
  else{
    return raiz;
  }
}

void reemplazar(Node* raiz, Node* nuevaR){
  if(raiz -> padre){
    if(raiz -> info == raiz -> padre -> izq -> info){
      raiz -> padre -> izq = nuevaR;
    }
    else if(raiz -> info == raiz -> padre -> der -> info){
      raiz -> padre -> der = nuevaR;
    }
  }
  else if(nuevaR){
    nuevaR -> padre = raiz -> padre;
  }
}

void eliminaNodo(Node* raiz){
  if(raiz -> izq){
    reemplazar(raiz, raiz -> izq);
    deleteMemoria(raiz);
  }
  else if(raiz -> der){
    reemplazar(raiz, raiz -> der);
    deleteMemoria(raiz);
  }
  else if(raiz -> der && raiz -> izq){
    Node* tmp = siguiente(raiz -> der);
    raiz -> info = tmp -> info;
    eliminaNodo(tmp);
  }
  else{
    reemplazar(raiz, NULL);
    deleteMemoria(raiz);
  }
}

void elimina(Node* raiz, int valor){
    if(raiz == NULL){
      return;
    }
    else if(valor > raiz -> info){
      elimina(raiz -> der, valor);
    }
    else if(valor < raiz -> info){
      elimina(raiz -> izq, valor);
    }
    else{
      eliminaNodo(raiz);
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
        agregaNodo(raiz, valor, NULL);
    }
    traversal(raiz, 1);
    traversal(raiz, 2);
    traversal(raiz, 3);
    cout << whatLevelAmI(raiz, 30, 0) << endl;
    cout << whatLevelAmI(raiz, 28, 0) << endl;
    cout << whatLevelAmI(raiz, 11, 0) << endl;
    cout << whatLevelAmI(raiz, 5, 0) << endl;
    elimina(raiz, 10);
    traversal(raiz, 1);
    traversal(raiz, 2);
    traversal(raiz, 3);
    return 0;
}
