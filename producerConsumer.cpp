#include <stdio.h>

int mutex = 1;
int full = 0;
int empty = 3;

int item = 0;

int wait(int s){
    return (--s);
}

int signal(int s){
    return (++s);
}

void producer(){
    mutex = wait(mutex); //lock critical section
    full = signal(full); //one more item produced
    empty = wait(empty); //one less empty slot
    item++;
    printf("Producer produces item %d\n", item);
    mutex = signal(mutex);
}

void consumer(){
    mutex = wait(mutex);
    full = wait(full);
    empty = signal(empty);
    item--;
    printf("Producer consumes item %d\n", item);
    mutex = signal(mutex);
}

int main(){
    int choice;

    printf("\nPRODUCER CONSUMER PROBLEM\n");
    printf("Buffer Size = 3\n");

    while (1){
        printf("\n1. Produce\n2. Consume\n3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice){
            case 1: 
            if (mutex == 1 && empty != 0){
                producer;
            }
            else
                    printf("Buffer is full! Producer must wait.\n");
                break;

            case 2:
                if ((mutex == 1) && (full != 0))
                    consumer();
                else
                    printf("Buffer is empty! Consumer must wait.\n");
                break;

            case 3:
                printf("Exiting...\n");
                return 0;

            default:
                printf("Invalid choice!\n");
        }
    }
}