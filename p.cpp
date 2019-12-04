#include <sys/shm.h> 
#include <unistd.h>
#include <sys/sem.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <fstream>
#include <iostream>
#include <chrono>


using namespace std;
/*
    args {filename, read pipe, write pipe, sem_id, shmid, _p1 or _p2 or ... _pn}
*/

int main(int argc, char *argv[]){
    int result = 0;
    char character;
    struct sembuf *operations = (struct sembuf *)calloc(sizeof(sembuf), 1);
    operations->sem_num = 0;
	operations->sem_op = 1;
    operations->sem_flg = IPC_NOWAIT;

    struct sembuf *sub = (struct sembuf *)calloc(sizeof(sembuf), 1);
    sub->sem_num = 0;
	sub->sem_op = -1;
    sub->sem_flg = IPC_NOWAIT;

    //for(int i = 0; i < 6; i++){
        //cout << argv[i] << " ";
    //}
    //cout << endl;

    // Close read
    close(atoi(argv[1]));

    // While the file is not complete
    while(1){

        // Wait until semaphore is available
        while(1){
            //result = semctl(atoi(argv[3]), 0, GETVAL, 0);
            if(semctl(atoi(argv[3]), 0, GETVAL, 0) < 0){
                cout << "Error getting semaphore value: " << strerror(errno) << endl;
                exit(1);
            } else if(semctl(atoi(argv[3]), 0, GETVAL, 0) == 0){
                if(semctl(atoi(argv[3]), 0, GETVAL, 0) != 0){
                    continue;
                }
                if(semop(atoi(argv[3]), operations, 1) != 0){
                    cout << "Failed to set value to 1: " << strerror(errno) << endl;
                    exit(1);
                }
                //cout << argv[5] << " incremented to " << semctl(atoi(argv[3]), 0, GETVAL, 0) << endl;
                break;
            }
            
            //cout << result;
            // If file is completely read
            if(semctl(atoi(argv[3]), 0, GETVAL, 0) == 3){
                // Close write & free
                close(atoi(argv[2]));
                free(operations);
                //cout << argv[5] << " exiting" << endl;
                exit(0);
            }
            //usleep(1000);
        }

        // Check if two grabbed the semaphore, then decrement
        if(semctl(atoi(argv[3]), 0, GETVAL, 0) == 2){
            if(semop(atoi(argv[3]), sub, 1) != 0){
                cout << "Failed to set value to 1: " << strerror(errno) << endl;
                exit(1);
            }
            //cout << argv[5] << " decremented to " << semctl(atoi(argv[3]), 0, GETVAL, 0) << endl;
            close(atoi(argv[2]));
            free(operations);
            //cout << argv[5] << " exiting" << endl;
            exit(0);
        }

        /*
            Semaphore value meanings:
                0 = available semaphore
                1 = unaviable semaphore
                2 = buffer for if two grab semaphore
                3 = no more data available
                4 = most recent program to use semaphore
                    has written back to Santa Claus
        */

        ifstream file;
        file.open(argv[0]);
        int random = rand() % 11;

        // If 0, generate new number
        while(random == 0){
            random = rand() % 11;
        }

        // Get file position
        string shm_data = (char *)shmat(atoi(argv[4]), (void *)0, 0);
        int position = atoi(shm_data.substr(3, shm_data.size() - 1).c_str());
        cout << position << endl;
        char *waste = (char *)calloc(sizeof(char), position + 1);
        file.read(waste, position);
        free(waste);

        // Read until i equals random
        int i = 0;
        string data = argv[5];
        while(file.get(character)){
            i++;
            data += character;
            if(i == random) break;
        }

        // If done, append the number of characters
        if(random != i){
            data += "\nCharacters read: " + to_string(position + i);
        }
        
        // String pipe terminator
        data += '^';
        file.close();

        // Write random to shared memory
        shm_data = argv[5] + to_string(i + position);
        char *data_pointer = (char *)shmat(atoi(argv[4]), (void *)0, 0);
        strcpy(data_pointer, shm_data.c_str());
        //cout << data_pointer << endl;
        shmdt(data_pointer);

        // Write data to Santa Claus
        int write_val = write(atoi(argv[2]), data.c_str(), data.length());
        if(write_val < 0){
            cout << "Error writing to pipe: " << strerror(errno) << endl;
        }

        // Means EOF was hit
        bool done = false;
        if(random != i){
            // Increment to 3 to let everyone know data is empty
            operations->sem_op = 2;
            if(semop(atoi(argv[3]), operations, 1) != 0){
                cout << "Failed to set value to 3: " << strerror(errno) << endl;
                exit(1);
            }
            //cout << argv[5] << " incremented to " << semctl(atoi(argv[3]), 0, GETVAL, 0) << endl;
            done = true;

            // Put the number of characters read into pipe
        }

        // For last iteration to not set to 2
        if(!done){
            // Increment to 4 for Santa Claus program
            operations->sem_op = 3;
            if(semop(atoi(argv[3]), operations, 1) != 0){
                cout << "Failed to set value to 3: " << strerror(errno) << endl;
                exit(1);
            }
            operations->sem_op = 1;
            //cout << argv[5] << " incremented to " << semctl(atoi(argv[3]), 0, GETVAL, 0) << endl;
        }
    }

    // Close write
    close(atoi(argv[2]));
    free(operations);
    free(sub);
}
