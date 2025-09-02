// Project 02 for Data Structures - 2024/1
// Authors: Daniel Henrique, Gabriel Laurentino, Pedro Henrique e Victor Menezes

#include <iostream>
#include <stdlib.h>
#include <locale.h>
#include <unistd.h>
#include "fila.h"
using namespace std;

// Cheerer struct
struct cheerer {
    int id;
    bool cheerer_level; // false = regular cheerer, true = member of the club
    int waiting_time;
};

// Define o level do cheerer mantendo a proproção
bool cheerer_level(float total[], float proportion[]) {
    bool level;
    if (proportion[0] < 95) { // Se a proporção do cheerer normal for smaller que 95%, cria um novo cheerer normal
        level = false; // 0 = normal
        total[0]++; // Incrementa o número de cheereres normais
    } else { // Caso contrário, cria um sócio-cheerer
        level = true; // 1 = sócio
        total[1]++; // Incrementa o número de sócio-cheereres
    }
    for (int i = 0; i < 2; i++) // Atualiza as novas proporções
        proportion[i] = (total[i] / (total[0] + total[1])) * 100; // índice/total * 100
    return level;
}

// Define o waiting_time do cheerer normal mantendo a proproção
int create_waiting_time_regular(float total[], float proportion[]) {
    int waiting_time;
    if (proportion[2] < 45) { // Se a proporção do waiting_time=3 for smaller que 45%, cria um novo waiting_time=3
        waiting_time = 3;
        total[2]++;
    } else if (proportion[1] < 30) { // Se a proporção do waiting_time=2 for smaller que 30%, cria um novo waiting_time=2
        waiting_time = 2;
        total[1]++;
    } else { // Caso contrário, cria um novo waiting_time=1
      waiting_time = 1;
      total[0]++;
    }
    for (int i = 0; i < 3; i++) // Atualiza as novas proporções
        proportion[i] = (total[i] / (total[0]+total[2]+total[1])) * 100; // índice/total * 100
    return waiting_time;
}

// Define o waiting_time do sócio-cheerer mantendo a proproção
int create_waiting_time_member(float total[], float proportion[]) {
    int  waiting_time;
    if (proportion[0] < 85) { // Se a proporção do waiting_time=1 for smaller que 85%, cria um novo waiting_time=1
        waiting_time = 1;
        total[0]++;
    } else { // Caso contrário, cria um novo waiting_time=2
        waiting_time = 2;
        total[1]++;
    }
    for (int i = 0; i < 2; i++) // Atualiza as novas proporções
        proportion[i] = (total[i] / (total[0] + total[1])) * 100; // índice/total * 100
    return waiting_time;
}

// Cria novo cheerer/sócio
cheerer *new_cheerer(bool cheerer_level, int &IDcounter, float total_n[], float proportion_n[], float total_s[], float proportion_s[]) {
    cheerer *e = new cheerer;
    if (cheerer_level == 1) { // If club member
        e->waiting_time = create_waiting_time_member(total_s, proportion_s);
        e->cheerer_level = cheerer_level;
        e->id = ++IDcounter;
    } else { // Se normal
        e->waiting_time = create_waiting_time_regular(total_n, proportion_n);
        e->cheerer_level = cheerer_level;
        e->id = ++IDcounter;
    }
      return e;
}

// Compara as filas e retorna a posição da fila com smaller elemento
int smaller_queue(TListQ<cheerer> ticket[], int qtd) {
    int k = 0; // Retorna o índice do vetor que contém a smaller fila
    TListQ<cheerer> smaller = ticket[0]; // Contém a smaller fila
    for (int i = 0; i < qtd; i++) {
        if (ticket[i].size < smaller.size) { // Verifica se a fila do índice atual é smaller do que a smaller fila
            smaller = ticket[i];
            k = i;
        }
    }
    return k;
}

// Imprime a fila
void print_queue(TListQ<cheerer> list) {
    TElementQ<cheerer> *nav = list.first;
    if (nav == NULL)
        cout << "\n Fila Vazia.";
    while (nav != NULL) {
        cout << "ID: " <<nav->data.id << " | ";
        cout << "Level: " << nav->data.cheerer_level << " | ";
        cout << "Waiting time: " <<nav->data.waiting_time << " | ";
        cout << "\n";
        nav = nav->next;
    }
}

int main() {
    setlocale(LC_ALL, "Portuguese");

    int ID = 0;
    int t = 0;
    int qtd_m = -1, qtd_r = -1, all_people_on_queue = -1, all_people_on_ticket = -1, all_waiting_time = -1;
    float total_regular[3] = {0.00}; // Total de cheereres, qtd cheereres com 1un de waiting_time, qtd cheereres com 2un de waiting_time, qtd cheereres com 3un de waiting_time
    float proportion_regular[3] = {0.00}; // Proporção de waiting_time dos cheereres normais: 1un, 2un, 3un,
    float total_member[2] = {0.00}; // Total de socios, qtd socios com 2un de waiting_time, qtd socios com 1un de waiting_time
    float proportion_member[2] = {0.00}; // Proporção de waiting_time dos sócio-cheereres: 1un, 2un
    float total_people[2] = {0.00}; // Qtd cheereres, qtd sócios
    float proportion_people[2] = {0.00}; // Proporção cheereres, proporção sócios
    cheerer newMember;
    float average_regular = 0.00;
    float average_member = 0.00;
    float aux;
    TListQ<cheerer> regular_waiting_list; // Lista de espera de cheereres normais, caso não haja tickets apropriados
    bootLinkedQueue(regular_waiting_list);
    TListQ<cheerer> member_waiting_list;  // Lista de espera de sócio-cheereres, caso não haja tickets apropriados
    bootLinkedQueue(member_waiting_list);

    while (qtd_m < 0) {
        cout << "1. Digite a quantidade de tickets sócio-cheerer: \n";
        cin >> qtd_m;
    }
    while (qtd_r < 0) {
        cout << "2. Digite a quantidade de tickets normal: \n";
        cin >> qtd_r;
    }
    while (all_people_on_queue < 0) {
        cout << "3. Digite a quantidade de pessoas para serem inicializadas na fila (carga inicial):\n";
        cin >> all_people_on_queue;
    }
    while (all_people_on_ticket < 0) {
        cout << "4. Digite a quantidade de pessoas que procuram o ticket a cada unidade de waiting_time: \n";
        cin >> all_people_on_ticket;
    }
    while (all_waiting_time < 0) {
        cout << "5. Digite a quantidade de waiting_time que será simulado: \n";
        cin >> all_waiting_time;
    }

    // Inicializa todos os tickets de sócio-cheerer
    TListQ<cheerer> ticket_socio[qtd_m];
    for(int i = 0; i < qtd_m; i++) {
        bootLinkedQueue(ticket_socio[i]);
    }

    // Inicializa todos os tickets de cheerer normal
    TListQ<cheerer> ticket_normal[qtd_r];
    for(int i = 0; i < qtd_r; i++) {
        bootLinkedQueue(ticket_normal[i]);
    }

    // Inicializa os cheereres em suas respectivas filas
    for (int i = 0; i < all_people_on_queue; i++) {
        newMember = *new_cheerer(cheerer_level(total_people, proportion_people), ID, total_regular, proportion_regular, total_member, proportion_member);
        if (newMember.cheerer_level == false) { // Se for cheerer normal
            if (qtd_r != 0)
                queue(ticket_normal[smaller_queue(ticket_normal, qtd_r)], newMember);
            else
                queue(regular_waiting_list, newMember);
        } else { // Se for sócio-cheerer
            if (qtd_m != 0)
                queue(ticket_socio[smaller_queue(ticket_socio, qtd_m)], newMember);
            else
                queue(member_waiting_list, newMember);
        }
    }

    // Imprime todas as filas
    cout << "waiting_time: " << t << endl;
    if (qtd_m == 0) {
        cout << "\nFILA DE ESPERA SÓCIO-cheererES | Pessoas na fila: " << member_waiting_list.size << "\n";
        print_queue(member_waiting_list);
        cout << "\n";
    } else {
        for(int i = 0; i < qtd_m; i++) {
            cout << "\nFILA SOCIO = " << i+1 << " | Pessoas na fila: " << ticket_socio[i].size << "\n";
            if (ticket_socio[i].first != NULL) {
                print_queue(ticket_socio[i]);
                cout << "\n";
            }
        }
    }
    if (qtd_r == 0) {
        cout << "\nFILA DE ESPERA cheererES NORMAIS | Pessoas na fila: " << regular_waiting_list.size << "\n";
        print_queue(regular_waiting_list);
        cout << "\n";
    } else {
        for(int i = 0; i < qtd_r; i++) {
            cout << "\nFILA NORMAL = " << i+1 << " | Pessoas na fila: " << ticket_normal[i].size << "\n";
            if (ticket_normal[i].first != NULL){
                print_queue(ticket_normal[i]);
                cout << "\n";
            }
        }
    }

    for (t = 0; t < all_waiting_time; t++) {
        system("pause");
        system("cls");

        // Adiciona os novos cheereres por unidade de waiting_time
        for (int i = 0; i < all_people_on_ticket; i++) {
            newMember = *new_cheerer(cheerer_level(total_people, proportion_people), ID, total_regular, proportion_regular, total_member, proportion_member);
            if (newMember.cheerer_level == false) { // Se for cheerer normal
                if (qtd_r != 0)
                    queue(ticket_normal[smaller_queue(ticket_normal, qtd_r)], newMember);
                else
                    queue(regular_waiting_list, newMember);
            } else { // Se for sócio-cheerer
                if (qtd_m != 0)
                    queue(ticket_socio[smaller_queue(ticket_socio, qtd_m)], newMember);
                else
                    queue(member_waiting_list, newMember);
            }
        }

        for (int i = 0; i < qtd_r; i++) { // Passando por todos os primeiros da fila
            if (ticket_normal[i].first != NULL) {
                ticket_normal[i].first->data.waiting_time--; // Decrementa waiting_time do cheerer em atendimento
                if (ticket_normal[i].first->data.waiting_time == 0) { // Se waiting_time = 0, passa pro próximo da fila
                    dequeue(ticket_normal[i]);
                }
            }
        }
        for (int i = 0; i < qtd_m; i++) { // Passando por todos os primeiros da fila
            if (ticket_socio[i].first != NULL) {
                ticket_socio[i].first->data.waiting_time--; // Decrementa waiting_time do cheerer em atendimento
                if (ticket_socio[i].first->data.waiting_time == 0) { // Se waiting_time = 0, passa pro próximo da fila
                    dequeue(ticket_socio[i]);
                }
            }
        }
    
        // Imprime todas as filas
        cout << "waiting_time: " << t+1 << endl; // Imprime na tela o waiting_time atual de reprodução da simulação
        if (qtd_m == 0) {  // Verifica se a quantidade de tickets sócio-cheerer é =0
            cout << "\nFILA DE ESPERA SÓCIO-cheererES | Pessoas na fila: " << member_waiting_list.size << "\n";
            print_queue(member_waiting_list);  // Imprime na tela a fila de espera de sócio-cheereres
            cout << "\n";
        } else { // Se a quantidade de tickets sócio-cheerer é !=0
            for(int i = 0; i < qtd_m; i++) {
                cout << "\nFILA SOCIO = " << i+1 << " | Pessoas na fila: " << ticket_socio[i].size << "\n";
                if (ticket_socio[i].first != NULL) {
                    print_queue(ticket_socio[i]); // Imprime na tela a fila sócios-cheereres
                    cout << "\n";
                }
            }
        }
        if (qtd_r == 0) { // Verifica se a quantidade de tickets cheerer-normal é = 0
            cout << "\nFILA DE ESPERA cheererES NORMAIS | Pessoas na fila: " << regular_waiting_list.size << "\n";
            print_queue(regular_waiting_list); // Imprime na tela a fila de espera de cheereres-normais
            cout << "\n";
        } else { // Se a quantidade de tickets cheerer-normal é !=0
            for(int i = 0; i < qtd_r; i++) {
                cout << "\nFILA NORMAL = " << i+1 << " | Pessoas na fila: " << ticket_normal[i].size << "\n";
                if (ticket_normal[i].first != NULL){
                    print_queue(ticket_normal[i]); // Imprime na tela a fila cheereres-normais
                    cout << "\n";
                }
            }
        }

        aux = 0;
        for (int i = 0; i< qtd_r; i++) // Calcula a quantidade média de cheerer normal
            aux += ticket_normal[i].size;
        aux = aux / qtd_r; // Aux = aux % número de filas
        average_regular += aux;
    
        aux = 0;
        for (int i = 0; i< qtd_m; i++) // Calcula a quantidade média de sócio-cheereres
            aux += ticket_socio[i].size;
        aux = aux / qtd_m; // Aux = aux % número de filas
        average_member += aux;

  } // Encerra a simulação

  if (all_waiting_time != 0) {  // Verifica se o waiting_time é diferente de zero
      average_regular = average_regular / all_waiting_time; // Calcula a média de cheereres normais que esperam nas filas dos tickets
      average_member = average_member / all_waiting_time; // Calcula a média de sócio-cheereres que esperam nas filas dos tickets
  }

  if (qtd_r == 0) // Verifica se existe ticket para cheereres normais
      cout << " \n Não há tickets para cheereres normais ";
  else
      cout << " \n Quantidade média de cheereres normais que esperam por ticket a cada unidade de waiting_time: " << average_regular;

  if (qtd_m == 0) // Verifica se existe ticket para sócio-cheereres
      cout << " \n Não há tickets para ´socio-cheereres ";
  else
      cout << " \n Quantidade média de sócio-cheereres que esperam por ticket a cada unidade de waiting_time: " << average_member;

  return 0;
}
