#include <iostream>
#include <string>
#include <queue>

using namespace std;

//The min head will be built of patient nodes with a name, priority, and treatment.
//This struct has one constructor that initializes all 3.
struct patientNode{
    string name;
    int priority;
    int treatment;

    patientNode(string inName, int inPriority, int inTreatment){
        name = inName;
        priority = inPriority;
        treatment = inTreatment;
    }
};

//STL arranges heap as a max heap, which we want to change to a min heap
struct compare{
    //Override 'operator'
    bool operator()(const patientNode &Patient1, const patientNode &Patient2){

        //If the priorities are equal, the treatments must be compared
        if(Patient1.priority == Patient2.priority){
            return Patient1.treatment > Patient2.treatment;

        }

        //Otherwise, we can just check the priorities against one another
        else{
            return Patient1.priority > Patient2.priority;
        }

    }
};
