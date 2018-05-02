#ifndef MINHEAP_H
#define MINHEAP_H
#include <iostream>
#include <string>


using namespace std;

//Similar to patient node, but used for the min heap implementation
struct minHeapPatient{
    string name;
    int priority;
    int treatment;

    minHeapPatient();
    minHeapPatient(string inName, int inPriority, int inTreatment){
        name = inName;
        priority = inPriority;
        treatment = inTreatment;
    }
};

//A class for a minimum binary heap
//Uses the patientNode defined for the STL priority queue
class minHeap{
public:
    minHeap();
    void push(minHeapPatient * newPatient);//Adds a new node to the array of patients
    minHeapPatient * pop();//removes the first node from the array of patients
    void deleteHeap();//deletes every node in the array
    bool isEmpty();//Used to check if a min heap has already been built

private:
    minHeapPatient * listOfPatients[881];//An array to store all the patients, one extra element since index 0 is left empty
    int capacity = 881;
    int currentSize = 0;//tells us where to store the next patient
    void minHeapify(int indexPosition);//used when popping off a patient
};


#endif //MINHEAP_H
