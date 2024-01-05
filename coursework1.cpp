/*Banker's Algorithm for Deadlock Avoidance

Petar Atanasov

M00916537
*/

#include <iostream>
#include <array>

using namespace std;

// number of processes
                        // wrong procesess: 4-->3
const int n_of_processes = 5;           
// number of resources
                        // wrong resourcess: 3-->5
const int n_of_resources = 3;

//get the values for allocation for safe state
int allocation[n_of_processes][n_of_resources] = { 
                        //here will be the values where deadlock occur  
    {0, 1, 0}, //P0      //3, 2, 0      //1, 1, 1       //2, 1, 0     //0, 1, 2, 1, 0
    {2, 0, 0}, //P1      //2, 0, 2      //2, 2, 2       //3, 0, 2     //1, 2, 1, 0, 0
    {3, 0, 2}, //P2      //3, 0, 2      //3, 3, 3       //2, 1, 1    //2, 1, 1, 1, 1
    {2, 1, 1}, //P3      //5, 1, 1      //4, 4, 4       //0, 0, 2
    {0, 0, 2}  //P4      //0, 10, 2     //5, 5, 5
};

// get the values for maximum for safe state
int maximum[n_of_processes][n_of_resources] = {
                        //here will be the values where deadlock occur
    {7, 5, 3}, //P0      //7, 5, 3      //6, 6, 6       //7, 5, 3   //2, 2, 2, 2, 2
    {3, 2, 2}, //P1      //13, 2, 2     //7, 7, 7       //3, 2, 2   //2, 3, 2, 1, 2  
    {9, 0, 2}, //P2      //9, 0, 2      //8, 8, 8       //9, 0, 2   //3, 2, 2, 9, 2
    {4, 2, 2}, //P3      //10, 4, 6     //8, 8, 8       //4, 2, 2
    {5, 3, 3}  //P4      //5, 3, 3      //9, 9, 9
};

// get the available values for the banker's algorithm
                        // wrong inputs: 2, 6, 2, 2, 6
int current_Available[n_of_resources] = {3, 3, 2};
// track the processes if they are finished or not 
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
                //after the remaining need, check if resources are available
                if (exProcess){
                    for (int k = 0; k < n_of_resources; k++){
                        // allocate the resources
                        work[k] += allocation[i][k];
                    }
                    // go to step 2 

                    // the process is finished
                    copyOfFinish[i] = true;
                    // set the safe sequence array with the count increment
                    //and assigning variable i to it
                    safeSeq[count++] = i;
                    found = true;
                }
            }
        }
        // if nothing is true set an error conditian 
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
// resource-request algorithm 
 bool resource_request(int request[][n_of_resources]){
    int checkNeed[n_of_processes][n_of_resources];
    need(checkNeed);

    // step 1 --> iterate between the procceses 
    for ( int i = 0; i < n_of_processes; i++){
        // check the request exceed it's maximum
        for (int j = 0; j < n_of_resources; j++){
            if (request[i][j] > checkNeed[i][j]){
                cout << "Processes reached its maximum claim" << endl;
                return false;
            }
        }
    
     //step 2 --> check if request it is within available resources 
        for(int j = 0; j < n_of_resources; j++){
            if(request[i][j] > current_Available[j]){
                cout << "Resources aren't available" << endl;
                return false;
            }
        }
    
        //step 3 --> pretend to allocate request 
        for (int j = 0; j < n_of_resources; j++){
            current_Available[j] -= request[i][j];
            allocation[i][j] += request[i][j];
            checkNeed[i][j] -= request[i][j];
        }

        // step 4 -->  based on safety algorithm 
        if(!Safe()){
            cout << "UNSAFE STATE." << endl;

            // restore the resource-allocation state
            for(int j = 0; j < n_of_resources; j++){
                current_Available[j] += request[i][j];
                allocation[i][j] -= request[i][j];
                checkNeed[i][j] += request[i][j];
            }
            return false;
        }

        cout << "Resources allocated succesfully" << endl;
    }
    return true; 
 }
int main() {

 if(!Safe()){
    cout << " SAFE SEQUENCE not found " << endl;
 }
return 0; 
};
