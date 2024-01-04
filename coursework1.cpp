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
int allocation[n_of_processes][n_of_resources] = { 
                        //here will be the values where deadlock occur  
    {0, 1, 0},//P0      //3, 2, 0
    {2, 0, 0},//P1      //2, 0, 2
    {3, 0, 2},//P2      //3, 0, 2
    {2, 1, 1},//P3      //5, 1, 1
    {0, 0, 2} //P4      //0, 0, 2
};

// get the values for maximum for safe state
int maximum[n_of_processes][n_of_resources] = {
                        //here will be the values where deadlock occur
    {7, 5, 3},//P0      //7, 5, 3
    {3, 2, 2},//P1      //13, 2, 2 
    {9, 0, 2},//P2      //9, 0, 2
    {4, 2, 2},//P3      //10, 4, 6
    {5, 3, 3} //P4      //5, 3, 3
};

// get the available values for the banker's algorithm
int current_Available[n_of_resources] = {
    3,
    3,
    2
    };

bool finish[n_of_processes] = {false};

// create a Need function to get the needed values for the algorithm
void need(int request_Need[n_of_processes][n_of_resources]){
    for(int i = 0; i < n_of_processes; i++){
        for(int j = 0; j < n_of_resources; j++){
            request_Need[i][j] = maximum[i][j] - allocation[i][j];
        }
    }
}

// create a function to check for the safety alorithm 
bool Safe() {
    int request_Need[n_of_processes][n_of_resources];
    need(request_Need);

    // step 1

    // initialize work and set it to current available 
    // then loop through the resources
    int work[n_of_resources];
    for (int i = 0; i < n_of_resources; i++){
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

    while(count < n_of_processes) {
        // set a boolean value for founded sequence 
        bool found = false;
        for (int i = 0; i < n_of_processes; i++){
            if(!copyOfFinish[i]){
                // set a boolean which allow the proceses to be executed
                bool exProcess = true;
                
                //step 2

                //check if the recources are enough to proceed further
                for (int j = 0; j < n_of_resources; j++){
                    if(request_Need[i][j] > work[j]){
                        exProcess = false;
                        break;
                    }
                }
                // step 3 
                //after the remaining need check if resources are available
                if (exProcess){
                    for (int k = 0; k < n_of_resources; k++){
                        // allocate the resources
                        work[k] += allocation[i][k];
                    }
                    // go to step 2 

                    // the process is finished
                    copyOfFinish[i] = true;
                    // set the safe sequence array with the count increment
                    //and assing variable i to it
                    safeSeq[count++] = i;
                    found = true;
                }
            }
        }
        // if nothing is true set it to 0 
        if(!found){
            return false;
        }
        
    }
    
    // step 4 
    for (int i = 0; i < n_of_processes; i++){
        if(copyOfFinish[i] == false){
            cout << "UNSAFE STATE!";
            break;
        }
    }
    // print the output
    cout << "The SAFE SEQUENCE is: "; 
    for (int i = 0; i < n_of_processes - 1; i++){
        cout << " P" << safeSeq[i] << " ->";
    }
    cout << " P" << safeSeq[n_of_processes - 1] << endl;
    return true;
} 
 bool resource_request ( int request[][n_of_resources]){
    
    // iterate between the procceses 
    for ( int k = 0; k < n_of_processes; k++){
        // check the request exceed it's maximum
        for (int i = 0; i < n_of_resources; i++){
            if (request[k][i] > need[k][i]){
                cout << "Processes reached its maximum claim" << endl;
                return false;
            }
        }
    
     // check if request it is within available resources 
        for( int f = 0; f < n_of_resources; f++){
            if(request[k][f] > current_Available[f]){
                cout << "Resources aren't available" << endl;
                return false;
            }
        }
    
        //pretend to allocate request 
        for ( int y = 0; y < n_of_resources; y++){
            current_Available[y] -= request[k][y];
            allocation[k][y] += request[k][y];
            need[k][y] -= request[k][y];
        }

        // based on safety algorithm 
        if(!Safe()){
            cout << "UNSAFE STATE." << endl;

            // restore the resource-allocation state
            for(int t = 0; t < n_of_resources; t++){
                current_Available[t] += request[k][t];
                allocation[k][t] -= request[k][t];
                need[k][t] += request[k][t];
            }
            return false;
        }

        cout << "Resources allocated succesfully " << endl;
    }
    return true; 
 }
int main() {

 if(!Safe()){
    cout << " SAFE SEQUENCE not found " << endl;
 }
return 0; 
};
