#include "CSCI2270FinalLinkedList.hpp"
#include "CSCI2270FinalLinkedList.cpp"
#include "CSCI2270FinalSTL.cpp"
#include "CSCI2270FinalMinHeap.hpp"
#include "CSCI2270FinalMinHeap.cpp"
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include <ctime>

using namespace std;

//Takes a vector of time in milliseconds and calculates the mean
double findMeanTime(vector<double> timeVector){

    double sum = 0;

    for(int i = 0; i < timeVector.size(); i++){
        sum = sum + timeVector[i];
    }

    return sum/timeVector.size();
}

//Utilizes <cmath>
//Takes a vector of times in milliseconds and a mean, calculates standard deviation
double findStandardDeviationTime(vector<double> timeVector, double meanTime){

    double standDev = 0;

    for(int i = 0; i < timeVector.size(); i++){
        standDev += pow((timeVector[i] - meanTime), 2);
    }

    return sqrt(standDev / (timeVector.size() - 1));

}

int main(int argc, char * argv[]){

    //BEGIN BY READING IN ***ALL*** DATA

    //Arrays to hold the data being read in
    string nameArray[880];
    int priorityArray[880];
    int treatmentArray[880];

    ifstream readData(argv[2]);

    //Check to make sure opening the file was successful
    if(readData.is_open()){

        string name, priority, treatment;

        //Throw away the first line since it's the header
        getline(readData, name);

        //Keep track of the line number
        int index = 0;

        while(getline(readData, name, ',')){

            getline(readData, priority, ',');

            //The last column of the CSV has no comma
            getline(readData, treatment);

            //Unfortunately, it does have some white space. Must be removed for stoi to work.
            string correctTreatment = "";

            for(int i = 0; i < treatment.length(); i++){
                if(treatment[i] != ' '){
                    correctTreatment += treatment[i];
                }
            }

            nameArray[index] = name;
            priorityArray[index] = stoi(priority);
            treatmentArray[index] = stoi(correctTreatment);

            index++;
        }
    }

    //Opening the file didn't work; print to the terminal
    else{
        cout<<"There was an error opening the file!"<<endl;
        return -1;
    }

    //AFTER DATA IS READ, ENTER THE MAIN MENU

    bool continueMenu = true;
    int selectedDataSize = 0;
    int selectedTestSize = 0;

    LinkedList initLinkedList;

    //Tell the STL to use a vector of patientNodes and use my compare method.
    priority_queue<patientNode, vector<patientNode>, compare> STLPriorityQueue;

    minHeap initMinHeap;

    while(continueMenu){

        //A menu will always be displayed to the user until they quit.
        cout<<"----Main Menu----"<<endl;
        cout<<"Current Data Size: ";
        cout<<selectedDataSize<<endl;
        cout<<"Current Test Size: ";
        cout<<selectedTestSize<<endl;
        cout<<"A) Set New Data Size"<<endl;
        cout<<"B) Set New Test Size"<<endl;
        cout<<endl;
        cout<<"1) Build Linked List Priority Queue"<<endl;
        cout<<"2) Print Linked List Priority Queue"<<endl;
        cout<<"3) Delete Linked List Priority Queue"<<endl;
        cout<<"4) Test Linked List Priority Queue"<<endl;
        cout<<endl;
        cout<<"5) Build STL Priority Queue"<<endl;
        cout<<"6) Print and Delete STL Priority Queue"<<endl;
        cout<<"7) Test STL Priority Queue"<<endl;
        cout<<endl;
        cout<<"8) Build Minheap Priority Queue"<<endl;
        cout<<"9) Print Minheap Priority Queue"<<endl;
        cout<<"10) Delete Minheap Priority Queue"<<endl;
        cout<<"11) Test Minheap Priority Queue"<<endl;
        cout<<endl;
        cout<<"12) Exit Program"<<endl;

        //Get the input from the user
        string userSelection;
        cout<<"Please select an option: ";
        getline(cin, userSelection);

        //Set a new data size for the arrays filled from the CSV
        if(userSelection == "A"){
            string stringDataSize;
            cout<<"Please enter new data size: ";
            getline(cin, stringDataSize);
            selectedDataSize = stoi(stringDataSize);

        }

        //Sets a new test size; how many times priority queue will be built then deleted.
        else if(userSelection == "B"){
            string stringTestSize;
            cout<<"Please enter new test size: ";
            getline(cin, stringTestSize);
            selectedTestSize = stoi(stringTestSize);
        }

        else if(userSelection == "1"){

            //The user must select a data size before continuing.
            if(selectedDataSize == 0){
                cout<<"Please select a data size before building this priority queue. Press enter to continue."<<endl;
                cin.get();
            }

            //Build a priority queue by calling the push method for the data in the arrays
            else{

                for(int i = 0; i < selectedDataSize; i++){
                    initLinkedList.push(nameArray[i], priorityArray[i], treatmentArray[i]);
                }

            }

        }

        //Print the priority queue; if empty, nothing will be printed.
        else if(userSelection == "2"){
            initLinkedList.printAll();
            cout<<"Press enter to continue."<<endl;
            cin.get();

        }

        //Delete all data and set head to NULL
        else if(userSelection == "3"){
            for(int i = 0; i < selectedDataSize; i++){
                initLinkedList.pop();
            }
        }

        //Calculate the run times for building and deleting the linked list on different sized data sets.
        else if(userSelection == "4"){

            //Make sure a data size and test size have been selected.
            if(selectedDataSize == 0 || selectedTestSize == 0){
                cout<<"Please ensure you've selected a data size and test size. Press enter to continue."<<endl;
                cin.get();
            }
            else{

                //Vectors will store the time of each trail for building and deleting
                vector<double> buildTimes;
                vector<double> deleteTimes;
                double timeInMilliseconds;


                //Runs a specific 'Test' times
                for(int i = 0; i < selectedTestSize; i++){

                    //Every iteration times building, stores, times deleting, stores.
                    //<ctime> is used for the clock functions
                    //milliseconds are calculated by dividing time difference by CLOCKS_PEr_SEC * 1000

                    int startTimeBuild = clock();

                    for(int i = 0; i < selectedDataSize; i++){
                        initLinkedList.push(nameArray[i], priorityArray[i], treatmentArray[i]);
                    }

                    int endTimeBuild = clock();

                    timeInMilliseconds = (endTimeBuild-startTimeBuild)/double(CLOCKS_PER_SEC)*1000;
                    buildTimes.push_back(timeInMilliseconds);

                    int startTimeDelete = clock();

                    for(int i = 0; i < selectedDataSize; i++){
                        initLinkedList.pop();
                    }

                    int endTimeDelete = clock();

                    timeInMilliseconds = (endTimeDelete-startTimeDelete)/double(CLOCKS_PER_SEC)*1000;
                    deleteTimes.push_back(timeInMilliseconds);

                }

                //Find and print the means and standard deviations of building and deleting.
                double buildMeanTime = findMeanTime(buildTimes);
                double standDevBuildTime = findStandardDeviationTime(buildTimes, buildMeanTime);
                double deleteMeanTime = findMeanTime(deleteTimes);
                double standDevDeleteTime = findStandardDeviationTime(deleteTimes, deleteMeanTime);

                cout<<"BUILDING LINKED LIST PRIORITY QUEUE:"<<endl;
                cout<<"Mean: ";
                cout<<buildMeanTime;
                cout<<" Standard Deviation: ";
                cout<<standDevBuildTime<<endl;

                cout<<"DELETING LINKED LIST PRIORITY QUEUE:"<<endl;
                cout<<"Mean: ";
                cout<<deleteMeanTime;
                cout<<" Standard Deviation: ";
                cout<<standDevDeleteTime<<endl;
                cout<<"Press enter to continue."<<endl;
                cin.get();

            }

        }

        //The user has chosen to build an STL priority queue.
        else if(userSelection == "5"){

            //The user must select a data size before continuing.
            if(selectedDataSize == 0){
                cout<<"Please select a data size before building this priority queue. Press enter to continue."<<endl;
                cin.get();
            }

            else{

                //Create new nodes and push them to the priority queue
                for(int i = 0; i < selectedDataSize; i++){
                    patientNode newPatientNode = patientNode(nameArray[i], priorityArray[i], treatmentArray[i]);
                    STLPriorityQueue.push(newPatientNode);
                }
            }
        }

        //The user has chosen to print and delete the STL priority queue.
        else if(userSelection == "6"){

            //Check to make sure the priority queue has been built
            if(STLPriorityQueue.empty()){
                cout<<"This priority queue has not yet been built. Press enter to continue."<<endl;
                cin.get();
            }

            //If it's been built, print the top value.
            //Then, pop it off.
            else{
                while(!STLPriorityQueue.empty()){
                    cout<<STLPriorityQueue.top().name<<", "<<STLPriorityQueue.top().priority<<", "<<STLPriorityQueue.top().treatment<<endl;
                    STLPriorityQueue.pop();
                }

            cout<<"Press enter to continue."<<endl;
            cin.get();
            }
        }

        //Test the STL heap
        else if(userSelection == "7"){

            //Make sure a data size and test size have been selected.
            if(selectedDataSize == 0 || selectedTestSize == 0){
                cout<<"Please ensure you've selected a data size and test size. Press enter to continue."<<endl;
                cin.get();
            }
            else{

                //Vectors will store the time of each trail for building and deleting
                vector<double> buildTimes;
                vector<double> deleteTimes;
                double timeInMilliseconds;


                //Runs a specific 'Test' times
                for(int i = 0; i < selectedTestSize; i++){

                    //Every iteration times building, stores, times deleting, stores.
                    //<ctime> is used for the clock functions
                    //milliseconds are calculated by dividing time difference by CLOCKS_PEr_SEC * 1000

                    int startTimeBuild = clock();

                    for(int i = 0; i < selectedDataSize; i++){
                        patientNode newPatientNode = patientNode(nameArray[i], priorityArray[i], treatmentArray[i]);
                        STLPriorityQueue.push(newPatientNode);
                    }

                    int endTimeBuild = clock();

                    timeInMilliseconds = (endTimeBuild-startTimeBuild)/double(CLOCKS_PER_SEC)*1000;
                    buildTimes.push_back(timeInMilliseconds);

                    int startTimeDelete = clock();

                    while(!STLPriorityQueue.empty()){
                        STLPriorityQueue.pop();
                    }

                    int endTimeDelete = clock();

                    timeInMilliseconds = (endTimeDelete-startTimeDelete)/double(CLOCKS_PER_SEC)*1000;
                    deleteTimes.push_back(timeInMilliseconds);

                }

                //Find and print the means and standard deviations of building and deleting.
                double buildMeanTime = findMeanTime(buildTimes);
                double standDevBuildTime = findStandardDeviationTime(buildTimes, buildMeanTime);
                double deleteMeanTime = findMeanTime(deleteTimes);
                double standDevDeleteTime = findStandardDeviationTime(deleteTimes, deleteMeanTime);

                cout<<"BUILDING STL PRIORITY QUEUE:"<<endl;
                cout<<"Mean: ";
                cout<<buildMeanTime;
                cout<<" Standard Deviation: ";
                cout<<standDevBuildTime<<endl;

                cout<<"DELETING STL PRIORITY QUEUE:"<<endl;
                cout<<"Mean: ";
                cout<<deleteMeanTime;
                cout<<" Standard Deviation: ";
                cout<<standDevDeleteTime<<endl;
                cout<<"Press enter to continue."<<endl;
                cin.get();

            }

        }

        //build a new minHeap
        else if(userSelection == "8"){

            //The user must select a data size before continuing.
            if(selectedDataSize == 0){
                cout<<"Please select a data size before building this priority queue. Press enter to continue."<<endl;
                cin.get();
            }

            //We don't want to build if a priority queue has already been built
            else if(!initMinHeap.isEmpty()){
                cout<<"The priority queue has already been built. Press enter to continue."<<endl;
                cin.get();
            }

            else{

                //create a new patient and push onto the min heap.
                //they will be ordered correctly by the push function
                for(int i = 0; i < selectedDataSize; i++){
                    minHeapPatient * newPatient = new minHeapPatient(nameArray[i], priorityArray[i], treatmentArray[i]);
                    initMinHeap.push(newPatient);
                }

            }
        }

        //print an already built minHeap
        else if(userSelection == "9"){

            //Check to make sure a minHeap has been built
            if(initMinHeap.isEmpty()){
                cout<<"This priority queue has not yet been built. Press enter to continue."<<endl;
                cin.get();
            }

            //Use the pop function which utilizes minHeapify
            //Will be printed in the correct order
            else{
                for(int i = 0; i < selectedDataSize; i++){
                    initMinHeap.pop();
                }

                cout<<"Press enter to continue."<<endl;
                cin.get();
            }
        }

        //delete an already built minHeap
        else if(userSelection == "10"){

            //deleteHeap uses a for loop with the listOfPatients array
            //If the minHeap hasn't been built/has been previously delete, it will do nothing.
            //This is why no checks required
            initMinHeap.deleteHeap();

        }

        //perform a timing test on the min heap priority queue
        else if(userSelection == "11"){

            //Make sure a data size and test size have been selected.
            if(selectedDataSize == 0 || selectedTestSize == 0){
                cout<<"Please ensure you've selected a data size and test size. Press enter to continue."<<endl;
                cin.get();
            }
            else{

                //Vectors will store the time of each trail for building and deleting
                vector<double> buildTimes;
                vector<double> deleteTimes;
                double timeInMilliseconds;


                //Runs a specific 'Test' times
                for(int i = 0; i < selectedTestSize; i++){

                    //Every iteration times building, stores, times deleting, stores.
                    //<ctime> is used for the clock functions
                    //milliseconds are calculated by dividing time difference by CLOCKS_PEr_SEC * 1000

                    int startTimeBuild = clock();

                    for(int i = 0; i < selectedDataSize; i++){
                        minHeapPatient * newPatient = new minHeapPatient(nameArray[i], priorityArray[i], treatmentArray[i]);
                        initMinHeap.push(newPatient);
                    }

                    int endTimeBuild = clock();

                    timeInMilliseconds = (endTimeBuild-startTimeBuild)/double(CLOCKS_PER_SEC)*1000;
                    buildTimes.push_back(timeInMilliseconds);

                    int startTimeDelete = clock();

                    initMinHeap.deleteHeap();

                    int endTimeDelete = clock();


                    timeInMilliseconds = (endTimeDelete-startTimeDelete)/double(CLOCKS_PER_SEC)*1000;
                    deleteTimes.push_back(timeInMilliseconds);

                }

                //Find and print the means and standard deviations of building and deleting.
                double buildMeanTime = findMeanTime(buildTimes);
                double standDevBuildTime = findStandardDeviationTime(buildTimes, buildMeanTime);
                double deleteMeanTime = findMeanTime(deleteTimes);
                double standDevDeleteTime = findStandardDeviationTime(deleteTimes, deleteMeanTime);

                cout<<"BUILDING MINHEAP PRIORITY QUEUE:"<<endl;
                cout<<"Mean: ";
                cout<<buildMeanTime;
                cout<<" Standard Deviation: ";
                cout<<standDevBuildTime<<endl;

                cout<<"DELETING MINHEAP PRIORITY QUEUE:"<<endl;
                cout<<"Mean: ";
                cout<<deleteMeanTime;
                cout<<" Standard Deviation: ";
                cout<<standDevDeleteTime<<endl;
                cout<<"Press enter to continue."<<endl;
                cin.get();

            }
        }

        //The user has selected to quit
        else if(userSelection == "12"){
            continueMenu = false;
        }

        else{
            cout<<"Invalid selection. Please pick again. Press enter to continue."<<endl;
            cin.get();
        }

    }

}
