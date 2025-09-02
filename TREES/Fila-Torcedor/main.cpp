// Project 02 for Data Structures - 2024/1
// Authors: Daniel Henrique, Gabriel Laurentino, Pedro Henrique e Victor Menezes

#include <iostream>
#include <stdlib.h>
#include <locale.h>
#include <unistd.h>
#include "linkedQueue.h"
using namespace std;

// Cheerer struct
struct Cheerer {
    int id;
    bool is_club_member; // false = regular cheerer, true = club member
    int wait_time;
};

// Determines the level of the cheerer maintaining proportion
bool determine_level(float total[], float proportion[]) {
    bool level;
    if (proportion[0] < 95) { // If proportion of regular cheerers < 95%, create a regular cheerer
        level = false;
        total[0]++;
    } else { // Otherwise, create a club member
        level = true;
        total[1]++;
    }
    for (int i = 0; i < 2; i++) // Update proportions
        proportion[i] = (total[i] / (total[0] + total[1])) * 100;
    return level;
}

// Determines wait_time for a regular cheerer maintaining proportion
int create_regular_wait_time(float total[], float proportion[]) {
    int wait_time;
    if (proportion[2] < 45) { // If the wait_time=3 ratio is less than 45%, create a new wait_time=3
        wait_time = 3;
        total[2]++;
    } else if (proportion[1] < 30) { // If the proportion of wait_time=2 is smaller than 30%, create a new wait_time=2
        wait_time = 2;
        total[1]++;
    } else { // Otherwise, create a new wait_time=1
      wait_time = 1;
      total[0]++;
    }
    for (int i = 0; i < 3; i++) // Update new proportions
        proportion[i] = (total[i] / (total[0]+total[2]+total[1])) * 100; // ondex/total * 100
    return wait_time;
}

// Determines wait_time for a club member maintaining proportion
int create_member_wait_time(float total[], float proportion[]) {
    int wait_time;
    if (proportion[0] < 85) { // If the proportion of wait_time=1 is smaller than 85%, create a new wait_time=1
        wait_time = 1;
        total[0]++;
    } else { // Otherwise, create a new wait_time=2
        wait_time = 2;
        total[1]++;
    }
    for (int i = 0; i < 2; i++) // Update new proportions
        proportion[i] = (total[i] / (total[0] + total[1])) * 100; // index/total * 100
    return wait_time;
}

// Creates a new cheerer
cheerer *create_cheerer(bool is_member, int &IDcounter, float total_regular[], float proportion_regular[], float total_members[], float proportion_members[]) {
    cheerer *e = new cheerer;
    if (is_member == 1) { // If club member
        e->wait_time = create_member_wait_time(total_members, proportion_members);
        e->is_club_member = is_member;
        e->id = ++IDcounter;
    } else { // Se normal
        e->wait_time = create_regular_wait_time(total_regular, proportion_regular);
        e->isClubMember = is_member;
        e->id = ++IDcounter;
    }
      return e;
}

// Finds the index of the queue with the smallest size
int find_smallest_queue_index(TListQ<cheerer> ticket[], int count) {
    int k = 0; // Returns the index of the vector containing the smaller row
    TListQ<cheerer> smallest = ticket[0]; // Contains the smallest queue
    for (int i = 0; i < count; i++) {
        if (ticket[i].size < smallest.size) { // Checks if the current index row is smaller than the smallest row
            smallest = ticket[i];
            k = i;
        }
    }
    return k;
}

// Print queue
void print_queue(TListQ<cheerer> q) {
    TElementQ<cheerer> *nav = q.first;
    if (!nav)
        cout << "\nEmpty Queue.";
        return;
    while (nav) {
        cout << "ID: " << nav->data.id << " | ";
        cout << "Member: " << nav->data.is_club_member  << " | ";
        cout << "Wait time: " <<nav->data.wait_time << " | ";
        cout << "\n";
        nav = nav->next;
    }
}

int main() {
    int ID = 0;
    int time_unit = 0;
    int num_member_tickets = -1, num_regular_tickets = -1;
    int initial_queue_size = -1, people_per_time_unit = -1, total_time_units = -1;
    
    float total_regular[3] = {0.0}; // Counts of regular cheerers by wait_time 1,2,3
    float proportion_regular[3] = {0.0};
    float total_members[2] = {0.0}; // Counts of club members by wait_time 1,2
    float proportion_members[2] = {0.0};
    float total_people[2] = {0.0}; // Counts of regular vs members
    float proportion_people[2] = {0.0};
    
    cheerer newCheerer;
    float average_regular = 0.0, average_member = 0.0, aux = 0.0;
    TListQ<Cheerer> regular_waiting_list; // Waiting list for regular cheerers in case there are no appropriate tickets
    TListQ<Cheerer> member_waiting_list; // Waiting list for member club cheerers in case there are no appropriate tickets
    bootLinkedQueue(regular_waiting_list);
    bootLinkedQueue(member_waiting_list);

    // Input simulation parameters
    while (num_member_tickets < 0) {
        cout << "1. Enter number of club member tickets: ";
        cin >> num_member_tickets;
    }
    while (num_regular_tickets < 0) {
        cout << "2. Enter number of regular tickets: ";
        cin >> num_regular_tickets;
    }
    while (initial_queue_size < 0) {
        cout << "3. Enter initial number of people in queues: ";
        cin >> initial_queue_size;
    }
    while (people_per_time_unit < 0) {
        cout << "4. Enter number of new people per time unit: ";
        cin >> people_per_time_unit;
    }
    while (total_time_units < 0) {
        cout << "5. Enter total number of time units to simulate: ";
        cin >> total_time_units;

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

    // Initialize queues
    TListQ<Cheerer> member_queues[num_member_tickets];
    for (int i = 0; i < num_member_tickets; i++) bootLinkedQueue(member_queues[i]);

    TListQ<Cheerer> regular_queues[num_regular_tickets];
    for (int i = 0; i < num_regular_tickets; i++) bootLinkedQueue(regular_queues[i]);

    // Initialize initial queue population
    for (int i = 0; i < initial_queue_size; i++) {
        new_cheerer_obj = *create_cheerer(determine_level(total_people, proportion_people), ID, total_regular, proportion_regular, total_members, proportion_members);
        if (!new_cheerer_obj.is_club_member) {
            if (num_regular_tickets != 0)
                queue(regular_queues[find_smallest_queue_index(regular_queues, num_regular_tickets)], new_cheerer_obj);
            else
                queue(regular_waiting_list, new_cheerer_obj);
        } else {
            if (num_member_tickets != 0)
                queue(member_queues[find_smallest_queue_index(member_queues, num_member_tickets)], new_cheerer_obj);
            else
                queue(member_waiting_list, new_cheerer_obj);
        }
    }

    // Imprime todas as filas
    cout << "wait_time: " << t << endl;
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

    for (t = 0; t < all_wait_time; t++) {
        system("pause");
        system("cls");

        // Adiciona os novos cheereres por unidade de wait_time
        for (int i = 0; i < all_people_on_ticket; i++) {
            newMember = *create_cheerer(isClubMember(total_people, proportion_people), ID, total_regular, proportion_regular, total_member, proportion_member);
            if (newMember.isClubMember == false) { // Se for cheerer normal
                if (qtd_r != 0)
                    queue(ticket_normal[find_smallest_queue_index(ticket_normal, qtd_r)], newMember);
                else
                    queue(regular_waiting_list, newMember);
            } else { // Se for sócio-cheerer
                if (qtd_m != 0)
                    queue(ticket_socio[find_smallest_queue_index(ticket_socio, qtd_m)], newMember);
                else
                    queue(member_waiting_list, newMember);
            }
        }

        for (int i = 0; i < qtd_r; i++) { // Passando por todos os primeiros da fila
            if (ticket_normal[i].first != NULL) {
                ticket_normal[i].first->data.wait_time--; // Decrementa wait_time do cheerer em atendimento
                if (ticket_normal[i].first->data.wait_time == 0) { // Se wait_time = 0, passa pro próximo da fila
                    dequeue(ticket_normal[i]);
                }
            }
        }
        for (int i = 0; i < qtd_m; i++) { // Passando por todos os primeiros da fila
            if (ticket_socio[i].first != NULL) {
                ticket_socio[i].first->data.wait_time--; // Decrementa wait_time do cheerer em atendimento
                if (ticket_socio[i].first->data.wait_time == 0) { // Se wait_time = 0, passa pro próximo da fila
                    dequeue(ticket_socio[i]);
                }
            }
        }
    
        // Imprime todas as filas
        cout << "wait_time: " << t+1 << endl; // Imprime na tela o wait_time atual de reprodução da simulação
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

  if (all_wait_time != 0) {  // Verifica se o wait_time é diferente de zero
      average_regular = average_regular / all_wait_time; // Calcula a média de cheereres normais que esperam nas filas dos tickets
      average_member = average_member / all_wait_time; // Calcula a média de sócio-cheereres que esperam nas filas dos tickets
  }

  if (qtd_r == 0) // Verifica se existe ticket para cheereres normais
      cout << " \n Não há tickets para cheereres normais ";
  else
      cout << " \n Quantidade média de cheereres normais que esperam por ticket a cada unidade de wait_time: " << average_regular;

  if (qtd_m == 0) // Verifica se existe ticket para sócio-cheereres
      cout << " \n Não há tickets para ´socio-cheereres ";
  else
      cout << " \n Quantidade média de sócio-cheereres que esperam por ticket a cada unidade de wait_time: " << average_member;

  return 0;
}
