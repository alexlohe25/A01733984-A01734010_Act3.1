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

void ancestors(Node* raiz, Node* nodo, int valor){
    if (nodo != NULL){
        if (nodo -> info == valor){
            int flag = 0;
            while (raiz -> info != valor){
                flag = 1;
                cout << raiz -> info << " ";
                if (valor < raiz -> info)
                    raiz = raiz -> izq;
                if (valor > raiz -> info)
                    raiz = raiz -> der;
            }
            if(flag != 0)cout << endl;
        }
        if (valor < nodo -> info)
            ancestors(raiz, nodo -> izq, valor);
        if (valor > nodo -> info)
            ancestors(raiz, nodo -> der, valor);  
    }
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

Node* elimina(Node* r, int valor){
    if (r == NULL)
        return r;
    if (valor < r -> info)
        r -> izq = elimina(r -> izq, valor);
    else if (valor > r -> info)
        r -> der = elimina(r->der, valor);
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
        elimina(raiz, valorDelete);
    }
    for (int i = 1; i <= 4; i++)
        traversal(raiz,i);
    cout << height(raiz) << endl;
    cin >> q;
    for (int i = 0; i < q; i++){
        int valorAncestro;
        cin >> valorAncestro;
        ancestors(raiz, raiz, valorAncestro);
    }
    cin >> r;
    for (int i = 0; i < r; i++){
        int valorNivel;
        cin >> valorNivel;
        cout << whatLevelAmI(raiz, valorNivel, 0) << endl;
    }
    return 0;
}