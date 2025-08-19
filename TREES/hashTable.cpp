#include <iostream>
using namespace std;

template <typename T>
struct LEncadeada{
  int key ;
  T data;
  LEncadeada *next;
};

template <typename T>
void insert(LEncadeada<T>* table[], int key, int m, T data){
  int hash = key % m;
  if(table[hash] == NULL){
      table[hash]->key = key;
      table[hash]->data = data;
      table[hash]->next = NULL;
  }
  else{
      LEncadeada<T> *nav = table[hash];
      while(nav != NULL)
        nav = nav->next;
      nav->key = key;
      nav->data = data;
      nav->next = NULL;
  }
}

int hashing(int n, int m){
  return n % m;
}

template <typename T>
void show_table (LEncadeada<T>* table[], int m){
  for(int i = 0; i < m; i++){
    LEncadeada<T> *nav = *table;
    if(nav==NULL)
      //cout<<"posicao vazia";
      cout << "[" << i << "]" << " [" << table[i]->key << "]";
    else
      // cout<<dado;
      cout << "[" << i << "]" << " [ NULL ]";
    
    while(nav->next != NULL){
      nav = nav->next;
      cout << " -> [" << nav->key << "]";
    }
    cout << "\n";
  }
}

template<typename T>
void boot_table(LEncadeada<T> * table[], int m){
    for(int i = 0; i < m; i++)
      table[i] = NULL;
}

template<typename T>
T search (LEncadeada<T>* table[], int key, int m){
  int hash = key % m;

  if(table[hash] != NULL){
    if(table[hash]->key == key)
      return table[hash]->data;
    else{
      LEncadeada<T> *aux =  table[hash];
        while(aux->next!=NULL)
          aux=aux->next;
      return aux->data;
    }
  
  }
  cout<<endl;
  cout<<"Chave não encontrada "<<endl;
  return 0;
}

template<typename T>
void remove(LEncadeada<T>* table[],int key, int m){
  int hash = key % m;
  LEncadeada<T> * aux;
  if(table[hash] != NULL){
    if(table[hash]->key==key){
      aux = table[hash];
      table[hash]=table[hash]->next;
      delete aux;
    }
    else{
      aux = table[hash]->next;
      LEncadeada<T> * ant = table[hash];
      while(aux != NULL && aux->key != key){
        ant=aux;
        aux= aux->next;
      }
      if(aux!=NULL){
        ant->next = aux->next;
        delete aux;
      }
      else
        cout<<"Chave not found "<<endl;
    }
  }
}


int main(){
  int resp;
  int key;
  int data;
  bool loop = true;

  int m = 0;
  cout << "insira M\n";
  cin >> m;

  LEncadeada<int>* table[m];
  boot_table(table, m);
  
  while(loop){
    cout << "╔══════════════════HASH══════════════════╗" << endl;
    cout << "║ |=| 1  -  INSERT                       ║" << endl;
    cout << "║ |=| 2  -  REMOVE                       ║" << endl;
    cout << "║ -------------------------------------- ║" << endl;
    cout << "║ |=| 3  -  SHOW TABLE                   ║" << endl;
    cout << "║ |=| 4  -  SEARCH                       ║" << endl;
    cout << "║ -------------------------------------- ║" << endl;
    cout << "║ |=| 5  -                               ║" << endl;
    cout << "║ |=| 6  -                               ║" << endl;
    cout << "║ |=| 7  -  RESET                        ║" << endl;
    cout << "║ -------------------------------------- ║" << endl;
    cout << "║ |=| 8  -  QUIT                         ║" << endl;
    cout << "╚══════════════════MENU══════════════════╝" << endl;
    cin >> resp;

    switch(resp){
      case 1:
        cout <<"insira a chave\n";
        cin >> key;
        cout<<"Insira o dado\n";
        cin >> data;
        insert(table, key , m , data);
        break;
      case 2:
        cout <<"insira a chave\n";
        cin >> key;
        remove(table, key, m);
        break;
      case 3:
        show_table(table, m);
        break;
      case 4:
        cout <<"insira a chave  \n";
        cin >> key;
        search(table, key, m);
        break;
      case 5:
        break;
      case 6:
        break;
      case 7:
        
        boot_table(table, m);
        break;
      case 8:
        return 0;
        break;
      default:
        cout<<"Resposta inválida"<<endl;
    }
  }
}
