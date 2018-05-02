#include "CSCI2270FinalLinkedList.hpp"

using namespace std;

//Set the head to null when initialized so the first element read in can be set to head.
LinkedList::LinkedList(){
    head = NULL;
}

LinkedList::~LinkedList(){};

void LinkedList::push(string currentName, int currentPriority, int currentTreatment){


    //Since head is NULL, we can't make any changes to it yet
    //Instead, we'll use tempHead
    Node * tempHead = new Node;

    //The first element read in becomes the head.
    if(head == NULL){
        tempHead->name = currentName;
        tempHead->priority = currentPriority;
        tempHead->treatment = currentTreatment;
        tempHead->next = NULL;
        head = tempHead;
    }

    else{
        //Create a new node with the data from the arrays
        Node * newNode = new Node;
        newNode->name = currentName;
        newNode->priority = currentPriority;
        newNode->treatment = currentTreatment;
        newNode -> next = NULL;


        Node * transverse = head;

            //First, check the new node against the head


            //If the newNode has a smaller priority, it becomes the new head.
            //The head also gets set to the newNode
            if(newNode -> priority < transverse -> priority){
                newNode -> next = transverse;
                head = newNode;
                return;
            }

            //If the newNode and the head have the same priority, check the treatment.
            if(newNode -> priority == transverse -> priority){

                //If newNode has a smaller treatment, it becomes the new head.
                //The head is set to newNode
                if(newNode -> treatment < transverse -> treatment){
                    newNode -> next = transverse;
                    head = newNode;
                    return;
                }

                //If the treatments are the same or newNode's is greater, keep the head the same and insert newNode after the head.
                else{
                    newNode -> next = transverse -> next;
                    transverse -> next = newNode;
                    return;
                }

            }

        Node * parent = new Node;

        //isEnd checks if the node being inserted has the absolute highest value
        bool isEnd = true;
        while(transverse -> next != NULL){

                //Here, parent acts as previous. Transverse gets incremented and we'll check its value.
                parent = transverse;
                transverse = transverse -> next;

                //newNode has a smaller priority than the next node.
                //It gets inserted after parent.
                if(newNode -> priority < transverse -> priority){
                    parent -> next = newNode;
                    newNode -> next = transverse;
                    isEnd = false;
                    break;
                }

                //If newNode has the same priority as the next node, check the treatments.
                if(newNode -> priority == transverse -> priority){

                    if(newNode -> treatment < transverse -> treatment){
                        parent -> next = newNode;
                        newNode -> next = transverse;
                        isEnd = false;
                        break;
                    }

                    //If newNode has the same or greater treatment, its correct place must be found among all with same priority

                    //If treatments are equal, newNode is inserted after
                    if(newNode -> treatment == transverse -> treatment){
                        newNode -> next = transverse -> next;
                        transverse -> next = newNode;
                        isEnd = false;
                        break;
                    }

                    //To find the correct placement, we search for the next node of the SAME PRIORITY with a larger treatment.
                    //If newNode has the largest treatment, it's inserted at the end.
                    if(newNode -> treatment > transverse -> treatment){

                        Node * transverseTreatment = transverse;

                        while(transverseTreatment -> next != NULL && transverseTreatment -> next -> treatment < newNode -> treatment && transverseTreatment -> next -> priority == transverseTreatment -> priority){
                            transverseTreatment = transverseTreatment -> next;
                        }

                        newNode -> next = transverseTreatment -> next;
                        transverseTreatment -> next = newNode;
                        isEnd = false;
                        break;

                    }

                }

        }

        //If newNode is the greatest priority value, it becomes the tail
        if(isEnd){
            transverse -> next = newNode;
        }

    }

}

void LinkedList::printAll(){

    //The head hasn't been set, so no LinkedList has been built.
    if(head == NULL){
        cout<<"This priority queue has yet to be built. ";
        return;
    }

    //Print every value until reaching the end
    Node * transverse = head;
    while(transverse != NULL){
        cout<<transverse -> name<<", "<<transverse -> priority<<", "<<transverse -> treatment<<endl;
        transverse = transverse -> next;
    }

}

void LinkedList::pop(){

    //The linked list hasn't been built, so don't do anything.
    if(head == NULL){
        return;
    }

    //The head is the last item, so we just want to delete it.
    //We set head to Null since that's what it is initialized as.
    if(head -> next == NULL){
        Node * tempHead = head;
        head = NULL;
        delete tempHead;
    }

    //Otherwise, move the head over one and delete the previous head.
    //Set a temporary head so the real head isn't lost.
    else{
        Node * tempHead = head;
        head = head -> next;
        delete tempHead;
    }

}
