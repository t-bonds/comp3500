// #0#BEGIN# DO NOT MODIFIE THIS COMMENT LINE!
// Tanner
// Bonds
// #0#END# DO NOT MODIFIE THIS COMMENT LINE!

#include "stdio.h"
#include "string.h"
#include <iostream>
using namespace std;
#define num 5 // 5 processes

struct PCB {
    char ID; // process ID
    int runtime; //runtime
    int pri; //priority
    char state; //status，R-Ready，F-Terminated, r-running
};

struct PCB pcblist[num]; //PCB array


void init() // initialize PCB
{
    int i;
    for (i = 0; i < num; i++) {

        // Print the prompt excatly syntax like this:
        // "ID PRIORITY RUNTIME--->PCB[0]"
        // to require users to input ID, priority, and runtime.
        // The "0" is the index of each PCB, counting start from 0
        // Return new line after prompt information
        // #1#BEGIN# DO NOT MODIFY THIS COMMENT LINE!

        cout << "ID PRIORITY RUNTIME--->PCB[" << i << "]\n";

        // #1#END# DO NOT MODIFY THIS COMMENT LINE!
        scanf(
                "%10s%10d%10d",
                & pcblist[i].ID,
                & pcblist[i].pri,
                & pcblist[i].runtime
        );
        pcblist[i].state = 'R'; // initialize all processes "R"
        getchar(); // carriage from an "enter" key
    }
}

int max_pri_process() // determine a process with max priority
{
    int max = -1000; // initialize max priority with smallest value
    int i;
    int key;
    for (i = 0; i < num; i++) {
        if (pcblist[i].state == 'r') // r denotes a running status
            return -1;
        else if(max < pcblist[i].pri && pcblist[i].state == 'R')
        //select a process with max priority
        {
            max = pcblist[i].pri;
            // max stores a process with max priority each loop

            key = i; // assign ID to key
        }
    }
    if (pcblist[key].state == 'F') // if a process with max priority is done
        return -1;
    else
        return key;
}

void show() // display info in each loop
{
    int i;
    printf("\nID PRIORITY RUNTIME STATUS \n");
    printf("-------------------------------------------------\n");
    for (i = 0; i < num; i++) 
    {
        // for each process, display ID PRIORITY RUNTIME STATUS
        // Must contains those informations and seperated properly
        // (No strict syntax rules for seperators)
        // #2#BEGIN# DO NOT MODIFY THIS COMMENT LINE!

        cout << pcblist[i].ID << "  ";

            if (pcblist[i].pri >= 0) {

             cout << pcblist[i].pri << "        ";

            }

            else {

            cout << pcblist[i].pri << "       ";

            }

            cout << pcblist[i].runtime << "       "
                 << pcblist[i].state << "\n";

        // #2#END# DO NOT MODIFY THIS COMMENT LINE!
    }

    printf("press any key to continue...\n");
}

void run() // calculate value for each process in each loop
{
    int i, j;
    int t = 0; // t: how many time has a process been ran
    for (j = 0; j < num; j++) {
        // sum of runtime from all processes into t
        // #3#BEGIN# DO NOT MODIFY THIS COMMENT LINE!

        t = t + pcblist[j].runtime;

        // #3#END# DO NOT MODIFY THIS COMMENT LINE!
    }
    printf("\nBefore run, the condition is:\n");
    show();
    getchar();
    for (j = 0; j < t; j++) {
        while (max_pri_process() != -1)
        // a process with max priority is still running
        {
            // assign "r" to a running process
            // #4#BEGIN# DO NOT MODIFY THIS COMMENT LINE!

            pcblist[max_pri_process()].state = 'r';

            // #4#END# DO NOT MODIFY THIS COMMENT LINE!
        }
        for (i = 0; i < num; i++) {
            if (pcblist[i].state == 'r') {
                // priority of a process is decrease by 1
                // #5#BEGIN# DO NOT MODIFY THIS COMMENT LINE!

                pcblist[i].pri -= 1;

                // #5#END# DO NOT MODIFY THIS COMMENT LINE!

                // runtime is decrease by 1
                // #6#BEGIN# DO NOT MODIFY THIS COMMENT LINE!

                pcblist[i].runtime -= 1;

                // #6#END# DO NOT MODIFY THIS COMMENT LINE!
                {
                    if (pcblist[i].runtime == 0)
                        // F: a process is done
                        // #7#BEGIN# DO NOT MODIFY THIS COMMENT LINE!

                        pcblist[i].state = 'F';

                        // #7#END# DO NOT MODIFY THIS COMMENT LINE!
                    else
                        // R: a process is not done
                        // #8#BEGIN# DO NOT MODIFY THIS COMMENT LINE!

                        pcblist[i].state = 'R';

                        // #8#END# DO NOT MODIFY THIS COMMENT LINE!
                }
                show();
                getchar();
            }
        }

    }
}

int main() {
    int banner_id;
    // #9#BEGIN# DO NOT MODIFY THIS COMMENT LINE!
    banner_id = 903466288;
    // #9#END# DO NOT MODIFY THIS COMMENT LINE!
    printf("banner_id: %d\n", banner_id);
    init(); // initialize each PCB
    run();
}

