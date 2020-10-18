#include <iostream>
#include <queue>
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

void deleteMemoria(Node* node){
  node -> izq = NULL;
  node -> der = NULL;
  delete node;
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

void reemplaza(Node* raiz, Node* nuevaR){
  if(raiz -> padre){
    if(raiz -> info == raiz -> padre -> izq -> info){
      raiz -> padre -> izq = nuevaR;
    }
    else if(raiz -> info == raiz -> padre -> der -> info){
      raiz -> padre -> der = nuevaR;
    }
  }
  if(nuevaR){
    nuevaR -> padre = raiz -> padre;
  }
}

void eliminaNodo(Node* eRaiz){
  if(eRaiz -> izq && eRaiz -> der){
    Node* tmp = cambio(eRaiz -> der);
    eRaiz -> info = tmp -> info;
    eliminaNodo(tmp);
  }
  else if(eRaiz -> izq){
    reemplaza(eRaiz, eRaiz -> izq);
    deleteMemoria(eRaiz);
  }
  else if(eRaiz -> der){
    Node * tempDer = eRaiz -> der;
    reemplaza(eRaiz, tempDer);
    deleteMemoria(eRaiz);
  }
  else if(eRaiz -> izq == NULL && eRaiz -> der == NULL){
    if(eRaiz -> padre -> izq == eRaiz){
        eRaiz -> padre -> izq = NULL;
    }
    else if(eRaiz -> padre -> der == eRaiz){
        eRaiz -> padre -> der = NULL;
    }
    deleteMemoria(eRaiz);
  }
}

void elimina(Node* raiz, int valor){
    if(raiz != NULL){
        if(valor < raiz -> info){
            elimina(raiz -> izq, valor);
        }
        else if(valor > raiz -> info){
            elimina(raiz -> der, valor);
        }
        else if (valor == raiz -> info)
            eliminaNodo(raiz);
    }
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
        agregaNodo(raiz, valorAdd, NULL);
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