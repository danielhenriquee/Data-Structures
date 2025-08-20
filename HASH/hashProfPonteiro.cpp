#include <iostream>

using namespace std;

const int tam =  8;

struct Thash{
  int chave;
  Thash *prox;
};

int funcao_hashing(int num){
  return num % tam;
}

void inicializa(Thash* tabela[]){
  for (int i = 0; i < tam; i++){
    tabela[i] = NULL;
  }
}

void inserir (Thash* tabela[], int num){
  Thash *novo
  novo = new Thash();
  novo->chave = num;
  int pos = funcao_hashing(num);
  novo->prox = tabela[pos];
  tabela[pos] = novo;
}

void remover (Thash* tabela[], int num){
  int pos = funcao_hashing(num);
  Thash *aux;
  if(tabela[pos] != NULL){
    if(tabela[pos]->chave == num){
      aux = tabela[pos];
      tabela[pos] = tabela[pos]->prox;
      delete aux;
    }else{
      aux = tabela[pos]->prox;
      Thash* ant = tabela[pos];
      while(aux != NULL && aux->chave != num){
        ant = aux;
        aux = aux->prox;
      }
      if(aux != NULL){
        ant->prox = aux->prox;
        delete aux;
      }
      else{
        cout << "\nNúmero não encontrado";
      }
    }
  }
  else{
    cout << "\nNúmero não encontrado";
  }
}

void mostrar_hash_completo(Thash* tabela[]){
  Thash *aux;
  for(int i=0; i < tam; i++){
    aux=tabela[i];
    if(aux == NULL){
      cout << "\nEntrada " << i << " : NULL";
    }
    else{
      cout << "\nEntrada " << i << ": ";
      while(aux != NULL){
      cout << " --> " << aux->chave;
      aux = aux->prox;
      }
    }
  }
}

void buscar(Thash* tabela[], int num){
  int pos = funcao_hashing(num);
  return pos;
}
