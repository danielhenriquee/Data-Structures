// // Trabalho T2 - Estrutura de dados
// // Autores: Daniel Henrique, Gabriel Laurentino, Pedro Henrique e Victor Menezes

// #include <iostream>
// #include <locale.h>
// #include <unistd.h>
// #include "fila.h"
// using namespace std;

// // Struct de torcedor
// struct torcedor {
//   int id;
//   bool tipo_torcedor; // false = normal, true = socio
//   int tempo;
// };

// // Define o tipo do torcedor mantendo a proproção
// bool tipo_torcedor(float total[], float proporcao[]) {
//   bool tipo;
//   if (proporcao[0] < 95) { // Se a proporção do torcedor normal for menor que 95%, cria um novo torcedor normal
//     tipo = false; // 0 = normal
//     total[0]++; // Incrementa o número de torcedores normais

//   } else { // Caso contrário, cria um sócio-torcedor
//     tipo = true; // 1 = sócio
//     total[1]++; // Incrementa o número de sócio-torcedores

//   }
//   for (int i = 0; i < 2; i++) // Atualiza as novas proporções
//     proporcao[i] = (total[i] / (total[0] + total[1])) * 100; // índice/total * 100
//   return tipo;
// }

// // Define o tempo do torcedor normal mantendo a proproção
// int criar_tempo_normal(float total[], float proporcao[]) {
//   int tempo;
//   if (proporcao[2] < 45) { // Se a proporção do tempo=3 for menor que 45%, cria um novo tempo=3
//     tempo = 3;
//     total[2]++;
//   } else if (proporcao[1] < 30) { // Se a proporção do tempo=2 for menor que 30%, cria um novo tempo=2
//     tempo = 2;
//     total[1]++;
//   } else { // Caso contrário, cria um novo tempo=1
//     tempo = 1;
//     total[0]++;
//   }
//   for (int i = 0; i < 3; i++) // Atualiza as novas proporções
//     proporcao[i] = (total[i] / (total[0]+total[2]+total[1])) * 100; // índice/total * 100
//   return tempo;
// }

// // Define o tempo do sócio-torcedor mantendo a proproção
// int criar_tempo_socio(float total[], float proporcao[]) {
//   int  tempo;
//   if (proporcao[0] < 85) { // Se a proporção do tempo=1 for menor que 85%, cria um novo tempo=1
//     tempo = 1;
//     total[0]++;
//   } else { // Caso contrário, cria um novo tempo=2
//     tempo = 2;
//     total[1]++;
//   }
//   for (int i = 0; i < 2; i++) // Atualiza as novas proporções
//     proporcao[i] = (total[i] / (total[0] + total[1])) * 100; // índice/total * 100
//   return tempo;
// }

// // Cria novo torcedor/sócio
// torcedor *novo_torcedor(bool tipo_torcedor, int &IDcounter, float total_n[], float proporcao_n[], float total_s[], float proporcao_s[]) {
//   torcedor *newElement = new torcedor;
//   if (tipo_torcedor == 1) { // Se socio
//     newElement->tempo = criar_tempo_socio(total_s, proporcao_s);
//     newElement->tipo_torcedor = tipo_torcedor;
//     newElement->id = ++IDcounter;
//   } else { // Se normal
//     newElement->tempo = criar_tempo_normal(total_n, proporcao_n);
//     newElement->tipo_torcedor = tipo_torcedor;
//     newElement->id = ++IDcounter;
//   }
//   return newElement;
// }

// // Compara as filas e retorna a posição da fila com menor elemento
// int menor_fila(TListQ<torcedor> guiche[], int qtd) {
//   int k = 0; // Retorna o índice do vetor que contém a menor fila
//   TListQ<torcedor> menor = guiche[0]; // Contém a menor fila
//   for (int i = 0; i < qtd; i++) {
//     if (guiche[i].size < menor.size) { // Verifica se a fila do índice atual é menor do que a menor fila
//       menor = guiche[i];
//       k = i;
//     }
//   }
//   return k;
// }

// // Imprime a fila
// void print_queue(TListQ<torcedor> list) {
//   TElementQ<torcedor> *nav = list.first;
//   if (nav == NULL)
//     cout << "\n Fila Vazia.";
//   while (nav != NULL) {
//     cout << "ID: " <<nav->data.id << " | ";
//     cout << "Tipo: " << nav->data.tipo_torcedor << " | ";
//     cout << "Tempo: " <<nav->data.tempo << " | ";
//     cout << "\n";
//     nav = nav->next;
//   }
// }

// int main() {
//   setlocale(LC_ALL, "Portuguese");
    
//   int ID = 0;
//   int t = 0;
//   int qtd_s = -1, qtd_n = -1, qtd_pessoas_fila = -1, qtd_pessoas_guiche = -1, qtd_tempo = -1;
//   float total_normal[3] = {0.00}; // Total de torcedores, qtd torcedores com 1un de tempo, qtd torcedores com 2un de tempo, qtd torcedores com 3un de tempo
//   float proporcao_normal[3] = {0.00}; // Proporção de tempo dos torcedores normais: 1un, 2un, 3un,
//   float total_socio[2] = {0.00}; // Total de socios, qtd socios com 2un de tempo, qtd socios com 1un de tempo
//   float proporcao_socio[2] = {0.00}; // Proporção de tempo dos sócio-torcedores: 1un, 2un
//   float total_pessoa[2] = {0.00}; // Qtd torcedores, qtd sócios
//   float proporcao_pessoa[2] = {0.00}; // Proporção torcedores, proporção sócios
//   torcedor membroNovo;
//   float qtd_media_n = 0.00;
//   float qtd_media_s = 0.00;
//   float aux;
//   TListQ<torcedor> lista_espera_normal; // Lista de espera de torcedores normais, caso não haja guichês apropriados
//   bootLinkedQueue(lista_espera_normal);
//   TListQ<torcedor> lista_espera_socio;  // Lista de espera de sócio-torcedores, caso não haja guichês apropriados
//   bootLinkedQueue(lista_espera_socio);

//   while (qtd_s < 0) {
//     cout << "1. Digite a quantidade de guichês sócio-torcedor: \n";
//     cin >> qtd_s;
//   }
//   while (qtd_n < 0) {
//     cout << "2. Digite a quantidade de guichês normal: \n";
//     cin >> qtd_n;
//   }
//   while (qtd_pessoas_fila < 0) {
//     cout << "3. Digite a quantidade de pessoas para serem inicializadas na fila (carga inicial):\n";
//     cin >> qtd_pessoas_fila;
//   }
//   while (qtd_pessoas_guiche < 0) {
//     cout << "4. Digite a quantidade de pessoas que procuram o guichê a cada unidade de tempo: \n";
//     cin >> qtd_pessoas_guiche;
//   }
//   while (qtd_tempo < 0) {
//     cout << "5. Digite a quantidade de tempo que será simulado: \n";
//     cin >> qtd_tempo;
//   }

//   // Inicializa todos os guichês de sócio-torcedor
//   TListQ<torcedor> guiche_socio[qtd_s];
//   for(int i = 0; i < qtd_s; i++) {
//     bootLinkedQueue(guiche_socio[i]);
//   }

//   // Inicializa todos os guichês de torcedor normal
//   TListQ<torcedor> guiche_normal[qtd_n];
//   for(int i = 0; i < qtd_n; i++) {
//     bootLinkedQueue(guiche_normal[i]);
//   }

//   // Inicializa os torcedores em suas respectivas filas
//   for (int i = 0; i < qtd_pessoas_fila; i++) {
//     membroNovo = *novo_torcedor(tipo_torcedor(total_pessoa, proporcao_pessoa), ID, total_normal, proporcao_normal, total_socio, proporcao_socio);
//     if (membroNovo.tipo_torcedor == false) { // Se for torcedor normal
//       if (qtd_n != 0)
//         queue(guiche_normal[menor_fila(guiche_normal, qtd_n)], membroNovo);
//       else
//         queue(lista_espera_normal, membroNovo);
//     } else { // Se for sócio-torcedor
//       if (qtd_s != 0)
//         queue(guiche_socio[menor_fila(guiche_socio, qtd_s)], membroNovo);
//       else
//         queue(lista_espera_socio, membroNovo);
//     }
//   }

//   // Imprime todas as filas
//   cout << "Tempo: " << t << endl;
//   if (qtd_s == 0) {
//     cout << "\nFILA DE ESPERA SÓCIO-TORCEDORES | Pessoas na fila: " << lista_espera_socio.size << "\n";
//     print_queue(lista_espera_socio);
//     cout << "\n";
//   } else {
//     for(int i = 0; i < qtd_s; i++) {
//       cout << "\nFILA SOCIO = " << i+1 << " | Pessoas na fila: " << guiche_socio[i].size << "\n";
//       if (guiche_socio[i].first != NULL) {
//         print_queue(guiche_socio[i]);
//         cout << "\n";
//       }
//     }
//   }
//   if (qtd_n == 0) {
//     cout << "\nFILA DE ESPERA TORCEDORES NORMAIS | Pessoas na fila: " << lista_espera_normal.size << "\n";
//     print_queue(lista_espera_normal);
//     cout << "\n";
//   } else {
//     for(int i = 0; i < qtd_n; i++) {
//       cout << "\nFILA NORMAL = " << i+1 << " | Pessoas na fila: " << guiche_normal[i].size << "\n";
//       if (guiche_normal[i].first != NULL){
//         print_queue(guiche_normal[i]);
//         cout << "\n";
//       }
//     }
//   }

//   for (t = 0; t < qtd_tempo; t++) {
//     system("PAUSE");
//     system("cls");

//     // Adiciona os novos torcedores por unidade de tempo
//     for (int i = 0; i < qtd_pessoas_guiche; i++) {
//       membroNovo = *novo_torcedor(tipo_torcedor(total_pessoa, proporcao_pessoa), ID, total_normal, proporcao_normal, total_socio, proporcao_socio);
//       if (membroNovo.tipo_torcedor == false) { // Se for torcedor normal
//         if (qtd_n != 0)
//           queue(guiche_normal[menor_fila(guiche_normal, qtd_n)], membroNovo);
//         else
//           queue(lista_espera_normal, membroNovo);
//       } else { // Se for sócio-torcedor
//         if (qtd_s != 0)
//           queue(guiche_socio[menor_fila(guiche_socio, qtd_s)], membroNovo);
//         else
//           queue(lista_espera_socio, membroNovo);
//       }
//     }

//     for (int i = 0; i < qtd_n; i++) { // Passando por todos os primeiros da fila
//       if (guiche_normal[i].first != NULL) {
//         guiche_normal[i].first->data.tempo--; // Decrementa tempo do torcedor em atendimento
//         if (guiche_normal[i].first->data.tempo == 0) { // Se tempo = 0, passa pro próximo da fila
//           dequeue(guiche_normal[i]);
//         }
//       }
//     }
//     for (int i = 0; i < qtd_s; i++) { // Passando por todos os primeiros da fila
//       if (guiche_socio[i].first != NULL) {
//         guiche_socio[i].first->data.tempo--; // Decrementa tempo do torcedor em atendimento
//         if (guiche_socio[i].first->data.tempo == 0) { // Se tempo = 0, passa pro próximo da fila
//           dequeue(guiche_socio[i]);
//         }
//       }
//     }

//     // Imprime todas as filas
//     cout << "Tempo: " << t+1 << endl; // Imprime na tela o tempo atual de reprodução da simulação
//     if (qtd_s == 0) {  // Verifica se a quantidade de guichês sócio-torcedor é =0
//       cout << "\nFILA DE ESPERA SÓCIO-TORCEDORES | Pessoas na fila: " << lista_espera_socio.size << "\n";
//       print_queue(lista_espera_socio);  // Imprime na tela a fila de espera de sócio-torcedores
//       cout << "\n";
//     } else { // Se a quantidade de guichês sócio-torcedor é !=0
//       for(int i = 0; i < qtd_s; i++) {
//         cout << "\nFILA SOCIO = " << i+1 << " | Pessoas na fila: " << guiche_socio[i].size << "\n";
//         if (guiche_socio[i].first != NULL) { 
//           print_queue(guiche_socio[i]); // Imprime na tela a fila sócios-torcedores
//           cout << "\n";
//         }
//       }
//     }
//     if (qtd_n == 0) { // Verifica se a quantidade de guichês torcedor-normal é = 0
//       cout << "\nFILA DE ESPERA TORCEDORES NORMAIS | Pessoas na fila: " << lista_espera_normal.size << "\n";
//       print_queue(lista_espera_normal); // Imprime na tela a fila de espera de torcedores-normais
//       cout << "\n";
//     } else { // Se a quantidade de guichês torcedor-normal é !=0
//       for(int i = 0; i < qtd_n; i++) {
//         cout << "\nFILA NORMAL = " << i+1 << " | Pessoas na fila: " << guiche_normal[i].size << "\n";
//         if (guiche_normal[i].first != NULL){
//           print_queue(guiche_normal[i]); // Imprime na tela a fila torcedores-normais
//           cout << "\n";
//         }
//       }
//     }

//     aux = 0;
//     for (int i = 0; i< qtd_n; i++) // Calcula a quantidade média de torcedor normal
//       aux += guiche_normal[i].size;
//     aux = aux / qtd_n; // Aux = aux % número de filas
//     qtd_media_n += aux;

//     aux = 0;
//     for (int i = 0; i< qtd_s; i++) // Calcula a quantidade média de sócio-torcedores
//       aux += guiche_socio[i].size;
//     aux = aux / qtd_s; // Aux = aux % número de filas
//     qtd_media_s += aux;

//   } // Encerra a simulação

//   if (qtd_tempo != 0) {  // Verifica se o tempo é diferente de zero
//     qtd_media_n = qtd_media_n / qtd_tempo; // Calcula a média de torcedores normais que esperam nas filas dos guichês
//     qtd_media_s = qtd_media_s / qtd_tempo; // Calcula a média de sócio-torcedores que esperam nas filas dos guichês
//   }

//   if (qtd_n == 0) // Verifica se existe guichê para torcedores normais
//     cout << " \n Não há guichês para torcedores normais ";
//   else
//     cout << " \n Quantidade média de torcedores normais que esperam por guichê a cada unidade de tempo: " << qtd_media_n;
  
//   if (qtd_s == 0) // Verifica se existe guichê para sócio-torcedores
//     cout << " \n Não há guichês para ´socio-torcedores ";
//   else
//     cout << " \n Quantidade média de sócio-torcedores que esperam por guichê a cada unidade de tempo: " << qtd_media_s;
  
//   return 0;
// }
// Trabalho T2 - Estrutura de dados
// Autores: Daniel Henrique, Gabriel Laurentino, Pedro Henrique e Victor Menezes

#include <iostream>
#include <stdlib.h>
#include <locale.h>
#include <unistd.h>
#include "fila.h"
using namespace std;

// Struct de torcedor
struct torcedor {
  int id;
  bool tipo_torcedor; // false = normal, true = socio
  int tempo;
};

// Define o tipo do torcedor mantendo a proproção
bool tipo_torcedor(float total[], float proporcao[]) {
  bool tipo;
  if (proporcao[0] < 95) { // Se a proporção do torcedor normal for menor que 95%, cria um novo torcedor normal
    tipo = false; // 0 = normal
    total[0]++; // Incrementa o número de torcedores normais

  } else { // Caso contrário, cria um sócio-torcedor
    tipo = true; // 1 = sócio
    total[1]++; // Incrementa o número de sócio-torcedores

  }
  for (int i = 0; i < 2; i++) // Atualiza as novas proporções
    proporcao[i] = (total[i] / (total[0] + total[1])) * 100; // índice/total * 100
  return tipo;
}

// Define o tempo do torcedor normal mantendo a proproção
int criar_tempo_normal(float total[], float proporcao[]) {
  int tempo;
  if (proporcao[2] < 45) { // Se a proporção do tempo=3 for menor que 45%, cria um novo tempo=3
    tempo = 3;
    total[2]++;
  } else if (proporcao[1] < 30) { // Se a proporção do tempo=2 for menor que 30%, cria um novo tempo=2
    tempo = 2;
    total[1]++;
  } else { // Caso contrário, cria um novo tempo=1
    tempo = 1;
    total[0]++;
  }
  for (int i = 0; i < 3; i++) // Atualiza as novas proporções
    proporcao[i] = (total[i] / (total[0]+total[2]+total[1])) * 100; // índice/total * 100
  return tempo;
}

// Define o tempo do sócio-torcedor mantendo a proproção
int criar_tempo_socio(float total[], float proporcao[]) {
  int  tempo;
  if (proporcao[0] < 85) { // Se a proporção do tempo=1 for menor que 85%, cria um novo tempo=1
    tempo = 1;
    total[0]++;
  } else { // Caso contrário, cria um novo tempo=2
    tempo = 2;
    total[1]++;
  }
  for (int i = 0; i < 2; i++) // Atualiza as novas proporções
    proporcao[i] = (total[i] / (total[0] + total[1])) * 100; // índice/total * 100
  return tempo;
}

// Cria novo torcedor/sócio
torcedor *novo_torcedor(bool tipo_torcedor, int &IDcounter, float total_n[], float proporcao_n[], float total_s[], float proporcao_s[]) {
  torcedor *newElement = new torcedor;
  if (tipo_torcedor == 1) { // Se socio
    newElement->tempo = criar_tempo_socio(total_s, proporcao_s);
    newElement->tipo_torcedor = tipo_torcedor;
    newElement->id = ++IDcounter;
  } else { // Se normal
    newElement->tempo = criar_tempo_normal(total_n, proporcao_n);
    newElement->tipo_torcedor = tipo_torcedor;
    newElement->id = ++IDcounter;
  }
  return newElement;
}

// Compara as filas e retorna a posição da fila com menor elemento
int menor_fila(TListQ<torcedor> guiche[], int qtd) {
  int k = 0; // Retorna o índice do vetor que contém a menor fila
  TListQ<torcedor> menor = guiche[0]; // Contém a menor fila
  for (int i = 0; i < qtd; i++) {
    if (guiche[i].size < menor.size) { // Verifica se a fila do índice atual é menor do que a menor fila
      menor = guiche[i];
      k = i;
    }
  }
  return k;
}

// Imprime a fila
void print_queue(TListQ<torcedor> list) {
  TElementQ<torcedor> *nav = list.first;
  if (nav == NULL)
    cout << "\n Fila Vazia.";
  while (nav != NULL) {
    cout << "ID: " <<nav->data.id << " | ";
    cout << "Tipo: " << nav->data.tipo_torcedor << " | ";
    cout << "Tempo: " <<nav->data.tempo << " | ";
    cout << "\n";
    nav = nav->next;
  }
}

int main() {
  setlocale(LC_ALL, "Portuguese");

  int ID = 0;
  int t = 0;
  int qtd_s = -1, qtd_n = -1, qtd_pessoas_fila = -1, qtd_pessoas_guiche = -1, qtd_tempo = -1;
  float total_normal[3] = {0.00}; // Total de torcedores, qtd torcedores com 1un de tempo, qtd torcedores com 2un de tempo, qtd torcedores com 3un de tempo
  float proporcao_normal[3] = {0.00}; // Proporção de tempo dos torcedores normais: 1un, 2un, 3un,
  float total_socio[2] = {0.00}; // Total de socios, qtd socios com 2un de tempo, qtd socios com 1un de tempo
  float proporcao_socio[2] = {0.00}; // Proporção de tempo dos sócio-torcedores: 1un, 2un
  float total_pessoa[2] = {0.00}; // Qtd torcedores, qtd sócios
  float proporcao_pessoa[2] = {0.00}; // Proporção torcedores, proporção sócios
  torcedor membroNovo;
  float qtd_media_n = 0.00;
  float qtd_media_s = 0.00;
  float aux;
  TListQ<torcedor> lista_espera_normal; // Lista de espera de torcedores normais, caso não haja guichês apropriados
  bootLinkedQueue(lista_espera_normal);
  TListQ<torcedor> lista_espera_socio;  // Lista de espera de sócio-torcedores, caso não haja guichês apropriados
  bootLinkedQueue(lista_espera_socio);

  while (qtd_s < 0) {
    cout << "1. Digite a quantidade de guichês sócio-torcedor: \n";
    cin >> qtd_s;
  }
  while (qtd_n < 0) {
    cout << "2. Digite a quantidade de guichês normal: \n";
    cin >> qtd_n;
  }
  while (qtd_pessoas_fila < 0) {
    cout << "3. Digite a quantidade de pessoas para serem inicializadas na fila (carga inicial):\n";
    cin >> qtd_pessoas_fila;
  }
  while (qtd_pessoas_guiche < 0) {
    cout << "4. Digite a quantidade de pessoas que procuram o guichê a cada unidade de tempo: \n";
    cin >> qtd_pessoas_guiche;
  }
  while (qtd_tempo < 0) {
    cout << "5. Digite a quantidade de tempo que será simulado: \n";
    cin >> qtd_tempo;
  }

  // Inicializa todos os guichês de sócio-torcedor
  TListQ<torcedor> guiche_socio[qtd_s];
  for(int i = 0; i < qtd_s; i++) {
    bootLinkedQueue(guiche_socio[i]);
  }

  // Inicializa todos os guichês de torcedor normal
  TListQ<torcedor> guiche_normal[qtd_n];
  for(int i = 0; i < qtd_n; i++) {
    bootLinkedQueue(guiche_normal[i]);
  }

  // Inicializa os torcedores em suas respectivas filas
  for (int i = 0; i < qtd_pessoas_fila; i++) {
    membroNovo = *novo_torcedor(tipo_torcedor(total_pessoa, proporcao_pessoa), ID, total_normal, proporcao_normal, total_socio, proporcao_socio);
    if (membroNovo.tipo_torcedor == false) { // Se for torcedor normal
      if (qtd_n != 0)
        queue(guiche_normal[menor_fila(guiche_normal, qtd_n)], membroNovo);
      else
        queue(lista_espera_normal, membroNovo);
    } else { // Se for sócio-torcedor
      if (qtd_s != 0)
        queue(guiche_socio[menor_fila(guiche_socio, qtd_s)], membroNovo);
      else
        queue(lista_espera_socio, membroNovo);
    }
  }

  // Imprime todas as filas
  cout << "Tempo: " << t << endl;
  if (qtd_s == 0) {
    cout << "\nFILA DE ESPERA SÓCIO-TORCEDORES | Pessoas na fila: " << lista_espera_socio.size << "\n";
    print_queue(lista_espera_socio);
    cout << "\n";
  } else {
    for(int i = 0; i < qtd_s; i++) {
      cout << "\nFILA SOCIO = " << i+1 << " | Pessoas na fila: " << guiche_socio[i].size << "\n";
      if (guiche_socio[i].first != NULL) {
        print_queue(guiche_socio[i]);
        cout << "\n";
      }
    }
  }
  if (qtd_n == 0) {
    cout << "\nFILA DE ESPERA TORCEDORES NORMAIS | Pessoas na fila: " << lista_espera_normal.size << "\n";
    print_queue(lista_espera_normal);
    cout << "\n";
  } else {
    for(int i = 0; i < qtd_n; i++) {
      cout << "\nFILA NORMAL = " << i+1 << " | Pessoas na fila: " << guiche_normal[i].size << "\n";
      if (guiche_normal[i].first != NULL){
        print_queue(guiche_normal[i]);
        cout << "\n";
      }
    }
  }

  for (t = 0; t < qtd_tempo; t++) {
    system("pause");
    system("cls");

    // Adiciona os novos torcedores por unidade de tempo
    for (int i = 0; i < qtd_pessoas_guiche; i++) {
      membroNovo = *novo_torcedor(tipo_torcedor(total_pessoa, proporcao_pessoa), ID, total_normal, proporcao_normal, total_socio, proporcao_socio);
      if (membroNovo.tipo_torcedor == false) { // Se for torcedor normal
        if (qtd_n != 0)
          queue(guiche_normal[menor_fila(guiche_normal, qtd_n)], membroNovo);
        else
          queue(lista_espera_normal, membroNovo);
      } else { // Se for sócio-torcedor
        if (qtd_s != 0)
          queue(guiche_socio[menor_fila(guiche_socio, qtd_s)], membroNovo);
        else
          queue(lista_espera_socio, membroNovo);
      }
    }

    for (int i = 0; i < qtd_n; i++) { // Passando por todos os primeiros da fila
      if (guiche_normal[i].first != NULL) {
        guiche_normal[i].first->data.tempo--; // Decrementa tempo do torcedor em atendimento
        if (guiche_normal[i].first->data.tempo == 0) { // Se tempo = 0, passa pro próximo da fila
          dequeue(guiche_normal[i]);
        }
      }
    }
    for (int i = 0; i < qtd_s; i++) { // Passando por todos os primeiros da fila
      if (guiche_socio[i].first != NULL) {
        guiche_socio[i].first->data.tempo--; // Decrementa tempo do torcedor em atendimento
        if (guiche_socio[i].first->data.tempo == 0) { // Se tempo = 0, passa pro próximo da fila
          dequeue(guiche_socio[i]);
        }
      }
    }

    // Imprime todas as filas
    cout << "Tempo: " << t+1 << endl; // Imprime na tela o tempo atual de reprodução da simulação
    if (qtd_s == 0) {  // Verifica se a quantidade de guichês sócio-torcedor é =0
      cout << "\nFILA DE ESPERA SÓCIO-TORCEDORES | Pessoas na fila: " << lista_espera_socio.size << "\n";
      print_queue(lista_espera_socio);  // Imprime na tela a fila de espera de sócio-torcedores
      cout << "\n";
    } else { // Se a quantidade de guichês sócio-torcedor é !=0
      for(int i = 0; i < qtd_s; i++) {
        cout << "\nFILA SOCIO = " << i+1 << " | Pessoas na fila: " << guiche_socio[i].size << "\n";
        if (guiche_socio[i].first != NULL) {
          print_queue(guiche_socio[i]); // Imprime na tela a fila sócios-torcedores
          cout << "\n";
        }
      }
    }
    if (qtd_n == 0) { // Verifica se a quantidade de guichês torcedor-normal é = 0
      cout << "\nFILA DE ESPERA TORCEDORES NORMAIS | Pessoas na fila: " << lista_espera_normal.size << "\n";
      print_queue(lista_espera_normal); // Imprime na tela a fila de espera de torcedores-normais
      cout << "\n";
    } else { // Se a quantidade de guichês torcedor-normal é !=0
      for(int i = 0; i < qtd_n; i++) {
        cout << "\nFILA NORMAL = " << i+1 << " | Pessoas na fila: " << guiche_normal[i].size << "\n";
        if (guiche_normal[i].first != NULL){
          print_queue(guiche_normal[i]); // Imprime na tela a fila torcedores-normais
          cout << "\n";
        }
      }
    }

    aux = 0;
    for (int i = 0; i< qtd_n; i++) // Calcula a quantidade média de torcedor normal
      aux += guiche_normal[i].size;
    aux = aux / qtd_n; // Aux = aux % número de filas
    qtd_media_n += aux;

    aux = 0;
    for (int i = 0; i< qtd_s; i++) // Calcula a quantidade média de sócio-torcedores
      aux += guiche_socio[i].size;
    aux = aux / qtd_s; // Aux = aux % número de filas
    qtd_media_s += aux;

  } // Encerra a simulação

  if (qtd_tempo != 0) {  // Verifica se o tempo é diferente de zero
    qtd_media_n = qtd_media_n / qtd_tempo; // Calcula a média de torcedores normais que esperam nas filas dos guichês
    qtd_media_s = qtd_media_s / qtd_tempo; // Calcula a média de sócio-torcedores que esperam nas filas dos guichês
  }

  if (qtd_n == 0) // Verifica se existe guichê para torcedores normais
    cout << " \n Não há guichês para torcedores normais ";
  else
    cout << " \n Quantidade média de torcedores normais que esperam por guichê a cada unidade de tempo: " << qtd_media_n;

  if (qtd_s == 0) // Verifica se existe guichê para sócio-torcedores
    cout << " \n Não há guichês para ´socio-torcedores ";
  else
    cout << " \n Quantidade média de sócio-torcedores que esperam por guichê a cada unidade de tempo: " << qtd_media_s;

  return 0;
}
