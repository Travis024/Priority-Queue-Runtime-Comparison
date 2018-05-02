#include "CSCI2270FinalMinHeap.hpp"

using namespace std;

minHeap::minHeap(){};

void minHeap::push(minHeapPatient * newPatient){

    //Check to see if the heap is full
    if(currentSize == capacity){
        cout<<"This priority queue is full. Press enter to continue."<<endl;
        cin.get();
        return;
    }

    else{

        //Increments the size and puts the new node in at the very end.
        //Not yet ordered!
        currentSize++;
        int i = currentSize;
        listOfPatients[i] = newPatient;

        //Check to see that the current node isn't the min value
        //Also check to see if the it has a priority less than or equal to its parent.

       while(i > 1 && (listOfPatients[i/2]->priority > listOfPatients[i]->priority || listOfPatients[i/2]->priority == listOfPatients[i]->priority)){

            //if the node has a smaller priority, it needs to be moved into the correct position
            if(listOfPatients[i/2]->priority > listOfPatients[i]->priority){
                swap(listOfPatients[i], listOfPatients[i/2]);
                i = i/2;
            }

            //Now, the priorities are equal. Check the treatments
            if(listOfPatients[i/2]->priority == listOfPatients[i]->priority){

                if(listOfPatients[i/2] -> treatment > listOfPatients[i] -> treatment){
                    swap(listOfPatients[i], listOfPatients[i/2]);
                    i = i/2;
                }

                //In this case, the treatment is smaller, so the node at index i is in the correct position.
                //however, i still has to change so we move through our loop.
                //In this case, we decrement i to move towards the base case of exiting when i == 1
                else{
                    i--;
                }
            }

        }
    }

}

minHeapPatient * minHeap::pop(){

    //There's only one patient left
    if(currentSize == 1){
        currentSize--;
        return listOfPatients[1];
    }

    else{
        //The last index is put at the start
        //Make sure to decrement the current size
        minHeapPatient * popPatient = listOfPatients[1];
        listOfPatients[1] = listOfPatients[currentSize];
        currentSize--;
        //Take this patient and put it in the correct position
        minHeapify(1);

        //Print the information and return the pointer to this patient
        cout<<popPatient->name<<", "<<popPatient->priority<<", "<<popPatient->treatment<<endl;
        return popPatient;
    }
}

void minHeap::minHeapify(int indexPosition){

    //Find the left child, right child, and current patient
    int leftChild = 2 * indexPosition;
    int rightChild = (2 * indexPosition) + 1;
    int smallest = indexPosition;

    //First, check the left child. Take into the account where priorities are the same but treatments are different.
    if(leftChild <= currentSize && listOfPatients[leftChild] -> priority < listOfPatients[indexPosition] -> priority){
        smallest = leftChild;
    }
    if(leftChild <= currentSize && listOfPatients[leftChild] -> priority == listOfPatients[indexPosition] -> priority){
        if(listOfPatients[leftChild]->treatment < listOfPatients[indexPosition]->treatment){
            smallest = leftChild;
        }
    }

    //Next, check the right child. Take into the account where priorities are the same but treatments are different.
    if(rightChild <= currentSize && listOfPatients[rightChild] -> priority < listOfPatients[smallest] -> priority){
        smallest = rightChild;
    }
    if(rightChild <= currentSize && listOfPatients[rightChild] -> priority == listOfPatients[smallest] -> priority){
        if(listOfPatients[rightChild] -> treatment < listOfPatients[smallest] -> treatment){
            smallest = rightChild;
        }
    }

    //there was a child smaller than the parent
    if(smallest != indexPosition){
        //Swap and continue sorting until all sorted
        swap(listOfPatients[indexPosition] , listOfPatients[smallest]);
        minHeapify(smallest);
    }
}

void minHeap::deleteHeap(){
    //start at 1 because the first index is empty
    for(int i = 1; i < currentSize; i++){
        delete listOfPatients[i];
    }

    //Ensure the size gets reset to 0 for when the heap is built again
    currentSize = 0;
}

bool minHeap::isEmpty(){
    if(currentSize == 0){
        return true;
    }
    else{
        return false;
    }
}


