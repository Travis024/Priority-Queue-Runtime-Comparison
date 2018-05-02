#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <iostream>
#include <string>

using namespace std;

//Every node in the linked list will store all of the patient's data as well as a pointer to the next node.
struct Node{

    string name;
    int priority;
    int treatment;
    Node * next;

};

//The LinkedList class can add values, take values off, and print the whole list.
class LinkedList{
public:
    LinkedList();
    ~LinkedList();
    void push(string currentName, int currentPriority, int currentTreatment);//adds a new node
    void pop();//deletes the current head
    void printAll();//transverses through the list and prints all
private:
    Node * head;

};



#endif // LINKEDLIST_H

