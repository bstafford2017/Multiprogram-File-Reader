// Benjamin Stafford
// 11/16/19
// To compile: make

#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/shm.h> 
#include <sys/wait.h>
#include <sys/sem.h>
#include <sys/ipc.h>
//#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <string>
#include <fstream>

using namespace std;

string readFromPipe(int readId){
    int result = 0;
    char character;
    string data = "";
    while(1){
        result = read(readId, &character, 1);
        if(result < 0){
            cout << "Error reading pipe #1: " << strerror(errno) << endl;
            exit(1);
        } 
        if(character == '^'){
            break;
        }

        data += character;
    }
    //cout << endl;
    cout << data << endl;
    return data;
}

int main(int argc, char *argv[]){
    // Get value: ipcs -m -i sem_id

    // Shared segment = {"_p1 or _p2 or ... _p9"}

    // Create semaphore
    int sem_value = semget(IPC_PRIVATE, 1, IPC_CREAT | 0660);
    if(sem_value < 0){
        cout << "Error creating semaphore: " << strerror(errno) << endl;
        exit(1);
    }

    // Create second semaphore
    /*int sem_value_2 = semget(IPC_PRIVATE, 1, IPC_CREAT | 0660);
    if(sem_value_2 < 0){
        cout << "Error creating semaphore: " << strerror(errno) << endl;
        exit(1);
    }*/

    // Create shared memory segment
    int shmid = shmget(IPC_PRIVATE, 30, 0666 | IPC_CREAT); 
    if(shmid < 0){
        cout << "Error creating shared memory: " << strerror(errno)  << endl;
        exit(1);
    }

    char *inital_data = (char *)shmat(shmid, (void *)0, 0);
    strcpy(inital_data, "_p_0");
    shmdt(inital_data);

    int pipe1[2], pipe2[2], pipe3[2], pipe4[2], pipe5[2], pipe6[2], pipe7[2], pipe8[2], pipe9[2];

    if(pipe(pipe1) < 0){
        cout << "Error creating pipe 1: " << strerror(errno) << endl;
        exit(1);
    }
    if(pipe(pipe2) < 0){
        cout << "Error creating pipe 2: " << strerror(errno) << endl;
        exit(1);
    }
    if(pipe(pipe3) < 0){
        cout << "Error creating pipe 3: " << strerror(errno) << endl;
        exit(1);
    }
    if(pipe(pipe4) < 0){
        cout << "Error creating pipe 4: " << strerror(errno) << endl;
        exit(1);
    }
    if(pipe(pipe5) < 0){
        cout << "Error creating pipe 5: " << strerror(errno) << endl;
        exit(1);
    }
    if(pipe(pipe6) < 0){
        cout << "Error creating pipe 6: " << strerror(errno) << endl;
        exit(1);
    }
    if(pipe(pipe7) < 0){
        cout << "Error creating pipe 7: " << strerror(errno) << endl;
        exit(1);
    }
    if(pipe(pipe8) < 0){
        cout << "Error creating pipe 8: " << strerror(errno) << endl;
        exit(1);
    }
    if(pipe(pipe9) < 0){
        cout << "Error creating pipe 9: " << strerror(errno) << endl;
        exit(1);
    }

    pid_t _p1 = fork();
    if(_p1 < 0){
        cout << "Error forking _p1: " << strerror(errno) << endl;
        exit(1);
    } else if(_p1 == 0){
        int program1_exec = execlp("./pn", argv[1], to_string(pipe1[0]).c_str(), to_string(pipe1[1]).c_str(), to_string(sem_value).c_str(), to_string(shmid).c_str(), "_p1", NULL);
        if(program1_exec < 0){
            cout << "Failed to start child: " << strerror(errno) << endl;
            exit(1);
        }
    }

    pid_t _p2 = fork();
    if(_p2 < 0){
        cout << "Error forking _p2: " << strerror(errno) << endl;
        exit(1);
    } else if(_p2 == 0){
        int program1_exec = execlp("./pn", argv[1], to_string(pipe2[0]).c_str(), to_string(pipe2[1]).c_str(), to_string(sem_value).c_str(), to_string(shmid).c_str(), "_p2", NULL);
        if(program1_exec < 0){
            cout << "Failed to start child: " << strerror(errno) << endl;
            exit(1);
        }
    }

    pid_t _p3 = fork();
    if(_p3 < 0){
        cout << "Error forking _p3: " << strerror(errno) << endl;
        exit(1);
    } else if(_p3 == 0){
        int program1_exec = execlp("./pn", argv[1], to_string(pipe3[0]).c_str(), to_string(pipe3[1]).c_str(), to_string(sem_value).c_str(), to_string(shmid).c_str(), "_p3", NULL);
        if(program1_exec < 0){
            cout << "Failed to start child: " << strerror(errno) << endl;
            exit(1);
        }
    }

    pid_t _p4 = fork();
    if(_p4 < 0){
        cout << "Error forking _p4: " << strerror(errno) << endl;
        exit(1);
    } else if(_p4 == 0){
        int program1_exec = execlp("./pn", argv[1], to_string(pipe4[0]).c_str(), to_string(pipe4[1]).c_str(), to_string(sem_value).c_str(), to_string(shmid).c_str(), "_p4", NULL);
        if(program1_exec < 0){
            cout << "Failed to start child: " << strerror(errno) << endl;
            exit(1);
        }
    }

    pid_t _p5 = fork();
    if(_p5 < 0){
        cout << "Error forking _p5: " << strerror(errno) << endl;
        exit(1);
    } else if(_p5 == 0){
        int program1_exec = execlp("./pn", argv[1], to_string(pipe5[0]).c_str(), to_string(pipe5[1]).c_str(), to_string(sem_value).c_str(), to_string(shmid).c_str(), "_p5", NULL);
        if(program1_exec < 0){
            cout << "Failed to start child: " << strerror(errno) << endl;
            exit(1);
        }
    }

    pid_t _p6 = fork();
    if(_p6 < 0){
        cout << "Error forking _p6: " << strerror(errno) << endl;
        exit(1);
    } else if(_p6 == 0){
        int program1_exec = execlp("./pn", argv[1], to_string(pipe6[0]).c_str(), to_string(pipe6[1]).c_str(), to_string(sem_value).c_str(), to_string(shmid).c_str(), "_p6", NULL);
        if(program1_exec < 0){
            cout << "Failed to start child: " << strerror(errno) << endl;
            exit(1);
        }
    }

    pid_t _p7 = fork();
    if(_p7 < 0){
        cout << "Error forking _p7: " << strerror(errno) << endl;
        exit(1);
    } else if(_p7 == 0){
        int program1_exec = execlp("./pn", argv[1], to_string(pipe7[0]).c_str(), to_string(pipe7[1]).c_str(), to_string(sem_value).c_str(), to_string(shmid).c_str(), "_p7", NULL);
        if(program1_exec < 0){
            cout << "Failed to start child: " << strerror(errno) << endl;
            exit(1);
        }
    }
    pid_t _p8 = fork();
    if(_p8 < 0){
        cout << "Error forking _p8: " << strerror(errno) << endl;
        exit(1);
    } else if(_p8 == 0){
        int program1_exec = execlp("./pn", argv[1], to_string(pipe8[0]).c_str(), to_string(pipe8[1]).c_str(), to_string(sem_value).c_str(), to_string(shmid).c_str(), "_p8", NULL);
        if(program1_exec < 0){
            cout << "Failed to start child: " << strerror(errno) << endl;
            exit(1);
        }
    }

    pid_t _p9 = fork();
    if(_p9 < 0){
        cout << "Error forking _p9: " << strerror(errno) << endl;
        exit(1);
    } else if(_p9 == 0){
        int program1_exec = execlp("./pn", argv[1], to_string(pipe9[0]).c_str(), to_string(pipe9[1]).c_str(), to_string(sem_value).c_str(), to_string(shmid).c_str(), "_p9", NULL);
        if(program1_exec < 0){
            cout << "Failed to start child: " << strerror(errno) << endl;
            exit(1);
        }
    }

    // While the file is not complete
    bool done = false;
    while(semctl(sem_value, 0, GETVAL, 0) != 3){

        // Wait until a program has written back
        while(1){
            if(semctl(sem_value, 0, GETVAL, 0) < 0){
                cout << "Error getting semaphore value: " << strerror(errno) << endl;
                exit(1);
            }

            if(semctl(sem_value, 0, GETVAL, 0) == 4){
                if(semctl(sem_value, 0, GETVAL, 0) != 4){
                    continue;
                }
                break;
            }

            // If file is completely read
            if(semctl(sem_value, 0, GETVAL, 0) == 3){
                done = true;
                break;
            }
        }

        ofstream file;
        file.open("hw9.out", fstream::app);

        // Get shared memory segment
        string shm_data = (char *)shmat(shmid, (void *)0, 0);
        shmdt(shm_data.c_str());
        string program = shm_data.substr(0, 3);

        // Check which child returns data
        string data;
        if(program == "_p1"){
            data = readFromPipe(pipe1[0]); 
        } else if(program == "_p2"){
            data = readFromPipe(pipe2[0]); 
        } else if(program == "_p3"){
            data = readFromPipe(pipe3[0]); 
        } else if(program == "_p4"){
            data = readFromPipe(pipe4[0]); 
        } else if(program == "_p5"){
            data = readFromPipe(pipe5[0]); 
        } else if(program == "_p6"){
            data = readFromPipe(pipe6[0]); 
        } else if(program == "_p7"){
            data = readFromPipe(pipe7[0]); 
        } else if(program == "_p8"){
            data = readFromPipe(pipe8[0]); 
        } else if(program == "_p9"){
            data = readFromPipe(pipe9[0]); 
        }

        file << data;
        file.close();

        if(done){
            break;
        } else {
            struct sembuf *operations = (struct sembuf *)calloc(sizeof(sembuf), 1);
            operations->sem_num = 0;
            operations->sem_op = -4;
            operations->sem_flg = 0;
            if(semop(sem_value, operations, 1) != 0){
                cout << "Failed to set value to 0: " << strerror(errno) << endl;
                exit(1);
            }
            cout << "SC decremented to " << semctl(sem_value, 0, GETVAL, 0) << endl;
        }
        cout << "santa " << semctl(sem_value, 0, GETVAL, 0) << endl;
    }

    waitpid(_p1, 0, 0);
    waitpid(_p2, 0, 0);
    waitpid(_p3, 0, 0);
    waitpid(_p4, 0, 0);
    waitpid(_p5, 0, 0);
    waitpid(_p6, 0, 0);
    waitpid(_p7, 0, 0);
    waitpid(_p8, 0, 0);
    waitpid(_p9, 0, 0);

    // Remove semaphore
    int remove_result = semctl(sem_value, 0, IPC_RMID, 0);
    if(remove_result < 0){
        cout << "Error removing the semaphore: " << strerror(errno) << endl;
        exit(1);
    }

    // Remove shared memory segment
    remove_result = shmctl(shmid, IPC_RMID, NULL);
    if(remove_result < 0){
        cout << "Error removing the semaphore: " << strerror(errno) << endl;
        exit(1);
    }

    //cout << "SC exiting" << endl;
    close(pipe1[0]);
    close(pipe1[1]);
    close(pipe2[0]);
    close(pipe2[1]);
    close(pipe3[0]);
    close(pipe3[1]);
    close(pipe4[0]);
    close(pipe4[1]);
    close(pipe5[0]);
    close(pipe5[1]);
    close(pipe6[0]);
    close(pipe6[1]);
    close(pipe7[0]);
    close(pipe7[1]);
    close(pipe8[0]);
    close(pipe8[1]);
    close(pipe9[0]);
    close(pipe9[1]);
    exit(0);
}
