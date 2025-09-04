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
Cheerer *create_cheerer(bool is_member, int &IDcounter, float total_regular[], float proportion_regular[], float total_member[], float proportion_member[]) {
    Cheerer *e = new Cheerer;
    if (is_member == 1) { // If club member
        e->wait_time = create_member_wait_time(total_member, proportion_member);
        e->is_club_member = is_member;
        e->id = ++IDcounter;
    } else { // Se normal
        e->wait_time = create_regular_wait_time(total_regular, proportion_regular);
        e->is_club_member = is_member;
        e->id = ++IDcounter;
    }
      return e;
}

// Finds the index of the queue with the smallest size
int find_smallest_queue_index(LinkedQ_TList<Cheerer> ticket[], int count) {
    int k = 0; // Returns the index of the vector containing the smaller row
    LinkedQ_TList<Cheerer> smallest = ticket[0]; // Contains the smallest queue
    for (int i = 0; i < count; i++) {
        if (ticket[i].size < smallest.size) { // Checks if the current index row is smaller than the smallest row
            smallest = ticket[i];
            k = i;
        }
    }
    return k;
}

// Print queue
void print_queue(LinkedQ_TList<Cheerer> q) {
    LinkedQ_TElement<Cheerer> *nav = q.first;
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
    float total_member[2] = {0.0}; // Counts of club members by wait_time 1,2
    float proportion_member[2] = {0.0};
    float total_people[2] = {0.0}; // Counts of regular vs members
    float proportion_people[2] = {0.0};
    
    Cheerer newCheerer;
    float average_regular = 0.0, average_member = 0.0, aux = 0.0;
    LinkedQ_TList<Cheerer> regular_waiting_list; // Waiting list for regular cheerers in case there are no appropriate tickets
    LinkedQ_TList<Cheerer> member_waiting_list; // Waiting list for member club cheerers in case there are no appropriate tickets
    LinkedQ_boot(regular_waiting_list);
    LinkedQ_boot(member_waiting_list);

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
    }

    // Initialize regular queues
    LinkedQ_TList<Cheerer> regular_queues[num_regular_tickets];
    for(int i = 0; i < num_regular_tickets; i++) {
        LinkedQ_boot(regular_queues[i]);
    }

    // Initialize member queues
    LinkedQ_TList<Cheerer> member_queues[num_member_tickets];
    for(int i = 0; i < num_member_tickets; i++) {
        LinkedQ_boot(member_queues[i]);
    }

    // Initialize initial queue population
    LinkedQ_TList<Cheerer> member_queues[num_member_tickets];
    for (int i = 0; i < num_member_tickets; i++) LinkedQ_boot(member_queues[i]);

    LinkedQ_TList<Cheerer> regular_queues[num_regular_tickets];
    for (int i = 0; i < num_regular_tickets; i++) LinkedQ_boot(regular_queues[i]);

    // Initialize initial queue population
    for (int i = 0; i < initial_queue_size; i++) {
        Cheerer new_cheerer_obj;
        new_cheerer_obj = *create_cheerer(determine_level(total_people, proportion_people), ID, total_regular, proportion_regular, total_member, proportion_member);
        if (!new_cheerer_obj.is_club_member) {
            if (num_regular_tickets != 0)
                LinkedQ_enqueue(regular_queues[find_smallest_queue_index(regular_queues, num_regular_tickets)], new_cheerer_obj);
            else
                LinkedQ_enqueue(regular_waiting_list, new_cheerer_obj);
        } else {
            if (num_member_tickets != 0)
                LinkedQ_enqueue(member_queues[find_smallest_queue_index(member_queues, num_member_tickets)], new_cheerer_obj);
            else
                LinkedQ_enqueue(member_waiting_list, new_cheerer_obj);
        }
    }

    // Imprime todas as filas
    cout << "wait_time: " << time_unit << endl;
    if (num_member_tickets == 0) {
        cout << "\nFILA DE ESPERA SÓCIO-cheererES | Pessoas na fila: " << member_waiting_list.size << "\n";
        print_queue(member_waiting_list);
        cout << "\n";
    } else {
        for(int i = 0; i < num_member_tickets; i++) {
            cout << "\nFILA SOCIO = " << i+1 << " | Pessoas na fila: " << member_queues[i].size << "\n";
            if (member_queues[i].first != nullptr) {
                print_queue(member_queues[i]);
                cout << "\n";
            }
        }
    }
    if (num_regular_tickets == 0) {
        cout << "\nFILA DE ESPERA cheererES NORMAIS | Pessoas na fila: " << regular_waiting_list.size << "\n";
        print_queue(regular_waiting_list);
        cout << "\n";
    } else {
        for(int i = 0; i < num_regular_tickets; i++) {
            cout << "\nFILA NORMAL = " << i+1 << " | Pessoas na fila: " << regular_queues[i].size << "\n";
            if (regular_queues[i].first != nullptr){
                print_queue(regular_queues[i]);
                cout << "\n";
            }
        }
    }

    for (time_unit = 0; time_unit < total_time_units; time_unit++) {
        system("pause");
        system("cls");

        // Add new cheerers by unit time
        for (int i = 0; i < people_per_time_unit; i++) {
            Cheerer new_cheerer_obj;
            new_cheerer_obj = *create_cheerer(determine_level(total_people, proportion_people), ID, total_regular, proportion_regular, total_member, proportion_member);
            if (new_cheerer_obj.is_club_member == false) { // If regular
                if (num_regular_tickets != 0)
                    LinkedQ_enqueue(regular_queues[find_smallest_queue_index(regular_queues, num_regular_tickets)], new_cheerer_obj);
                else
                    LinkedQ_enqueue(regular_waiting_list, new_cheerer_obj);
            } else { // If club member
                if (num_member_tickets != 0)
                    LinkedQ_enqueue(member_queues[find_smallest_queue_index(member_queues, num_member_tickets)], new_cheerer_obj);
                else
                    LinkedQ_enqueue(member_waiting_list, new_cheerer_obj);
            }
        }

        for (int i = 0; i < num_regular_tickets; i++) { // Navigating all the first ones in queues
            if (regular_queues[i].first != nullptr) {
                regular_queues[i].first->data.wait_time--; // Decrease wait_time of the cheerer in service
                if (regular_queues[i].first->data.wait_time == 0) { // If wait_time = 0, go to next one
                    LinkedQ_dequeue(regular_queues[i]);
                }
            }
        }
        for (int i = 0; i < num_member_tickets; i++) { // Navigating all the first ones in queues
            if (member_queues[i].first != nullptr) {
                member_queues[i].first->data.wait_time--; // Decrease wait_time of the cheerer in service
                if (member_queues[i].first->data.wait_time == 0) { // // If wait_time = 0, go to next one
                    LinkedQ_dequeue(member_queues[i]);
                }
            }
        }
    
        // Print all queues
        cout << "wait_time: " << time_unit+1 << endl; // Prints the current wait_time of simulation playback
        if (num_member_tickets == 0) { // Check if the number of club members tickets is =0
            cout << "\nCLUB MEMBERS WAIT QUEUE | On queue: " << member_waiting_list.size << "\n";
            print_queue(member_waiting_list); // Print club members waiting list
            cout << "\n";
        } else { // If the number of club members tickets is !=0
            for(int i = 0; i < num_member_tickets; i++) {
                cout << "\nCLUB MEMBERS QUEUE = " << i+1 << " | On queue: " << member_queues[i].size << "\n";
                if (member_queues[i].first != nullptr) {
                    print_queue(member_queues[i]); // Print club members queues
                    cout << "\n";
                }
            }
        }
        if (num_regular_tickets == 0) { // Check if the number of regular tickets is =0
            cout << "\nREGULARS WAIT QUEUE | On queue: " << regular_waiting_list.size << "\n";
            print_queue(regular_waiting_list); // Print regulars waiting list
            cout << "\n";
        } else { // If the number of regulars tickets is !=0
            for(int i = 0; i < num_regular_tickets; i++) {
                cout << "\nREGULARS QUEUE = " << i+1 << " | On queue: " << regular_queues[i].size << "\n";
                if (regular_queues[i].first != nullptr){
                    print_queue(regular_queues[i]); // Print regulars queues
                    cout << "\n";
                }
            }
        }

        aux = 0;
        for (int i = 0; i< num_regular_tickets; i++) // Calculate the average amount of regulars
            aux += regular_queues[i].size;
        aux = aux / num_regular_tickets; // Aux = aux % number of queues
        average_regular += aux;
    
        aux = 0;
        for (int i = 0; i< num_member_tickets; i++) // Calculate the average amount of club members
            aux += member_queues[i].size;
        aux = aux / num_member_tickets; // Aux = aux % umber of queues
        average_member += aux;

    } // Encerra a simulação

    if (total_time_units != 0) {  // Verifica se o wait_time é diferente de zero
        average_regular = average_regular / total_time_units; // Calcula a média de cheereres normais que esperam nas filas dos tickets
        average_member = average_member / total_time_units; // Calcula a média de sócio-cheereres que esperam nas filas dos tickets
    }

    if (num_regular_tickets == 0) // Verifica se existe ticket para cheereres normais
        cout << " \n Não há tickets para cheereres normais ";
    else
        cout << " \n Quantidade média de cheereres normais que esperam por ticket a cada unidade de wait_time: " << average_regular;

    if (num_member_tickets == 0) // Verifica se existe ticket para sócio-cheereres
        cout << " \n Não há tickets para ´socio-cheereres ";
    else
        cout << " \n Quantidade média de sócio-cheereres que esperam por ticket a cada unidade de wait_time: " << average_member;

    return 0;
}
