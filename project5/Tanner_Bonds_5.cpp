// Please change the following into your name
// #0#BEGIN# DO NOT MODIFIE THIS COMMENT LINE!
// Tanner
// Bonds
// #0#END# DO NOT MODIFIE THIS COMMENT LINE!
#include<iostream>
using namespace std;
#define MAXPROCESS 50                       // max number of processes
#define MAXRESOURCE 100                     // max number of types of resources
int Available[MAXRESOURCE];                 // vector indicates the number of available resources of each type
int Max[MAXPROCESS][MAXRESOURCE];           // matrix defines the maximum demand of each process
int Allocation[MAXPROCESS][MAXRESOURCE];    // matrix defines the number of resources of each type currently allocated to each process
int Need[MAXPROCESS][MAXRESOURCE];          // matrix indicates the remaining resource need by each process
int Request[MAXPROCESS][MAXRESOURCE];       // matrix indicates the resources of each type requested by each process
bool Finish[MAXPROCESS];                    // vector indicates finish checking of each process
int p[MAXPROCESS];                          // record safe sequence of processes
int m, n;                                   // m processes, n units of resources

void Init(){
    int i, j;
    cout<<"m: input the number of processes"<<endl;
    cin>>m;
    cout<<"n: input the number of types of resources"<<endl;
    cin>>n;
    cout<<"Max Matrix: input the value of each element left to right, top to bottom"<<endl;
    for(i=0;i<m;i++){
        for(j=0;j<n;j++){
            cin>>Max[i][j];
        }
    }
    cout<<"Allocation Matrix: input the value of each element left to right, top to bottom"<<endl;
    for(i=0;i<m;i++){
        // check the resources request reasonable or not
        for(j=0;j<n;j++){
            cin>>Allocation[i][j];
            // remaining need of each process
            Need[i][j]=Max[i][j]-Allocation[i][j];
            if(Need[i][j]<0){
                cout<<"The "<<i+1<<"-th process request "<<j+1<<" resources, which is beyond the maximum resources, please retry"<<endl;
                j--;
                continue;
            }
        }
    }
    cout<<"Available Vector: input the value of each element left to right"<<endl;
    for(i=0;i<n;i++){
        cin>>Available[i];
    }
}

bool Safe(){
    int i,j,k,l=0;
    int Work[MAXRESOURCE];
    // work on providing different types of resources to each process

    for(i=0;i<n;i++) Work[i]=Available[i];
    for(i=0;i<m;i++){
        Finish[i]=false;
    }
    for(i=0;i<m;i++){
        if(Finish[i]==true){
            continue;
        }else{
            // Looping through all different types of resources
            // to check all types of available resources meet need
            // use varible j and write a "for" loop statment
            // #1#BEGIN# DO NOT MODIFIE THIS COMMENT LINE!

            for (j=0; j < m; j++)

            // #1#END# DO NOT MODIFIE THIS COMMENT LINE!
            {
                if(Need[i][j]>Work[j]){
                    break;
                }
            }

            // If all types of resources are enough for the
            // process, then the resources can be truly
            // assigned to this process i. 
            // What is the value of j if all types of resources
            // meet the need? (Need[i][j] no great than Work[j] for all j)
            // Write an "if" condition statement of j
            // #2#BEGIN# DO NOT MODIFIE THIS COMMENT LINE!

            if (j == m)            

            // #2#END# DO NOT MODIFIE THIS COMMENT LINE! 
            { 
                Finish[i]=true;
                for(k=0;k<n;k++){
                    Work[k]+=Allocation[i][k];
                }

                // After successfully assigment of resources to process i
                // Record the number of process i into safe sequence p[l]
                // l is the index of array p. l should increase 1 and pointing
                // to next postition of p after that (l++)
                // #3#BEGIN# DO NOT MODIFIE THIS COMMENT LINE!

                p[l++] = i;

                // #3#END# DO NOT MODIFIE THIS COMMENT LINE! 

                // reset the i into -1 to start loop again
                i=-1;
            }else{
                continue;
            }
        }
        // What is the value of l if we finish recording
        // all process number of the safe sequence
        // write a "if" statement
        // #4#BEGIN# DO NOT MODIFIE THIS COMMENT LINE!

        if (l == m) {

        // #4#END# DO NOT MODIFIE THIS COMMENT LINE!
            // if the system is safe, the resource will be assigned to the processes
            cout<<"The system is safe"<<endl;
            cout<<"The safe sequence is:"<<endl;
            for(i=0;i<l;i++){
                cout<<p[i];
                if(i!=l-1){
                    cout<<"-->";
                }
            }
            cout<<" "<<endl;
            return true;
        }
    }
    cout<<"The system is not safe"<<endl;
    return false;
}

void Bank() // banker's algorithm
{
    int i,cusneed;
    char again;
    while(1)
    {
        cout<<"A process start to request resources. The process number is: "<<endl;
        cin>>cusneed;
        cout<<"Each type resource requested by this proess"<<endl;
        for(i=0;i<n;i++)
        {
            cin>>Request[cusneed][i];
        }
        for(i=0;i<n;i++)
        {
            if(Request[cusneed][i]>Need[cusneed][i])
            {
                cout<<"Requested more than needed, please re-try!"<<endl;
                continue;
            }
            if(Request[cusneed][i]>Available[i])
            {
                cout<<"Requested more than available, please re-try!"<<endl;
                continue;
            }
        }
        for(i=0;i<n;i++)
        {
            Available[i]-=Request[cusneed][i];
            // Provide resources to the process cusneed
            // What is the value Allocation[cusneed][i]
            // after that? Write a statement to update the
            // new value of Allocation matrix
            // #5#BEGIN# DO NOT MODIFIE THIS COMMENT LINE!

            Allocation[cusneed][i] += Request[cusneed][i];

            // #5#END# DO NOT MODIFIE THIS COMMENT LINE!
            Need[cusneed][i]-=Request[cusneed][i];
        }

        // Request will only approved when the system is safe
        // Write a if statement to check whether it is safe
        // hint: what is the return value of function Safe()?
        // #6#BEGIN# DO NOT MODIFIE THIS COMMENT LINE!

        if (Safe())

        // #6#END# DO NOT MODIFIE THIS COMMENT LINE!
        {
            cout<<"Request approved!"<<endl;
        }else{
            cout<<"Your request is declined!"<<endl;
            // if not safe, we return back to the 
            // previous state
            for(i=0;i<n;i++)
            {
                Available[i]+=Request[cusneed][i];
                // Write a sentence to recover the prevoius value
                // of Allocation[cusneed][i]
                // #7#BEGIN# DO NOT MODIFIE THIS COMMENT LINE!

                Allocation[cusneed][i] -= Request[cusneed][i];

                // #7#END# DO NOT MODIFIE THIS COMMENT LINE!
                Need[cusneed][i]+=Request[cusneed][i]; 
            }
        }
        for(i=0;i<m;i++)
        {
            Finish[i]=false;
        }
        cout<<"Do you want to try again? Yes press y/Y, otherwise press any other key to quit"<<endl;
        cin>>again;
        if(again=='y'||again=='Y')
        {
            continue;
        }
        break;
    }
}

int main()
{
    // change your the following id into your banner id
    // #8#BEGIN# DO NOT MODIFIE THIS COMMENT LINE!
    int banner_id = 903466288;
    // #8#END# DO NOT MODIFIE THIS COMMENT LINE!
    Init();
    Safe();
    Bank();
}

