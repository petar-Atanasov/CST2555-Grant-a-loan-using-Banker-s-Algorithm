/*Banker's Algorithm for Deadlock Avoidance

Petar Atanasov

M00916537
*/


#include <iostream>
#include <array>

using namespace std;
// number of processes
const int n_of_processes = 5;
// number of resources
const int n_of_resources = 3;

// set the total to the bank
const int totalOfBank = 50;

//get the values for allocation for safe state
int allocation[n_of_processes][n_of_resources]={ 
    // #here will be the values where deadlock occur  
    {0, 1, 0},      //3 2 0
    {2, 0, 0},      //2 0 2
    {3, 0, 2},      //3 0 2
    {2, 1, 1},      //5 1 1
    {0, 0, 2}       //0 0 2
};

// get the values for maximum for safe state
int maximum[n_of_processes][n_of_resources]={
    {7, 5, 3},
    {3, 2, 2},
    {9, 0, 2},
    {4, 2, 2},
    {5, 3, 3}
};

// get the available values for the banker's algorithm
int current_Available[n_of_resources] = {
    totalOfBank,
    totalOfBank,
    totalOfBank
    };

bool finish[n_of_processes] = {false};

// create a Need function to get the needed values for the algorithm
void need(int request_Need[n_of_processes][n_of_resources]){
        for(int i = 0; i < n_of_processes; i++){
            for(int j = 0; j < n_of_resources; j++){
                request_Need[i][j] = maximum[i][j] - allocation[i][j];
            }
        }
};
// create a function to check for the safety alorithm 
bool Safe() {
    int request_Need[n_of_processes][n_of_resources] = {0};
    need(request_Need);


    // initialize work and set it to current available 
    // then loop through the resources
    int work[n_of_resources];
    for ( int i = 0; i < n_of_resources; i++){
        work[i] = current_Available[i];
    }

    // create a counter which will keep up with the function then 
    //initialize a copy of finish and set the finish from above to it and loop throught it   

    int count = 0;
    
    bool copyOfFinish[n_of_processes];
    for (int i = 0; i < n_of_processes; i++) {
        copyOfFinish[i] = finish[i];
    }
    
    // initialize a safe sequence value 
    int safeSeq[n_of_processes];

    while( count < n_of_processes) {
        // set a boolean value for founded sequence 
        bool found = false;
        for (int i = 0; i < n_of_processes; i++){
            if(!copyOfFinish[i]){
                // set a boolean which allow the proceses to be executed
                bool exProcess = true;
                //check if the recources are enough to proceed further
                for ( int j = 0; j < n_of_resources; j++){
                    if(request_Need[i][j] > work[j]){

                    }
                }
                
            }
        }
    }





}

int main() {


};