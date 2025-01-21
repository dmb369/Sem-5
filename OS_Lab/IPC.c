#include <sys/ipc.h>
#include <sys/shm.h>
#include <semaphore.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define SHM_KEY 1234          // Key for shared memory segment
#define SHM_SIZE 1024         // Size of shared memory segment
#define SEM_NAME "/sync_sem"  // Name for semaphore

// Function prototypes
void write_to_shared_memory();
void read_from_shared_memory();
void delete_shared_memory();

int main() {
    int choice;

    while (1) {
        printf("\nChoose an action:\n");
        printf("1. Write to shared memory\n");
        printf("2. Read from shared memory\n");
        printf("3. Delete shared memory and exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                write_to_shared_memory();
                break;
            case 2:
                read_from_shared_memory();
                break;
            case 3:
                delete_shared_memory();
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

// Function to write to the shared memory segment with semaphore synchronization
void write_to_shared_memory() {
    // Create or access shared memory segment
    int shmid = shmget(SHM_KEY, SHM_SIZE, IPC_CREAT | 0666);
    if (shmid < 0) {
        perror("Failed to create/access shared memory");
        exit(1);
    }

    // Attach to shared memory
    char *data = (char *)shmat(shmid, NULL, 0);
    if (data == (char *)(-1)) {
        perror("Failed to attach shared memory");
        exit(1);
    }

    // Initialize semaphore for synchronization
    sem_t *sem = sem_open(SEM_NAME, O_CREAT, 0644, 1);
    if (sem == SEM_FAILED) {
        perror("Failed to open/create semaphore");
        exit(1);
    }

    // Lock semaphore before writing
    sem_wait(sem);

    // Write data to shared memory
    printf("Enter a message to write to shared memory: ");
    scanf(" %[^\n]", data);  // Read input including spaces
    printf("Message written to shared memory.\n");

    // Unlock semaphore after writing
    sem_post(sem);

    // Detach from shared memory
    shmdt(data);
    sem_close(sem);
}

// Function to read from the shared memory segment with semaphore synchronization
void read_from_shared_memory() {
    // Access shared memory segment
    int shmid = shmget(SHM_KEY, SHM_SIZE, 0666);
    if (shmid < 0) {
        perror("Failed to access shared memory");
        exit(1);
    }

    // Attach to shared memory
    char *data = (char *)shmat(shmid, NULL, 0);
    if (data == (char *)(-1)) {
        perror("Failed to attach shared memory");
        exit(1);
    }

    // Open semaphore for synchronization
    sem_t *sem = sem_open(SEM_NAME, 0);
    if (sem == SEM_FAILED) {
        perror("Failed to open semaphore");
        exit(1);
    }

    // Lock semaphore before reading
    sem_wait(sem);

    // Read data from shared memory
    printf("Message read from shared memory: %s\n", data);

    // Unlock semaphore after reading
    sem_post(sem);

    // Detach from shared memory
    shmdt(data);
    sem_close(sem);
}

// Function to delete the shared memory segment and semaphore
void delete_shared_memory() {
    // Access the shared memory segment
    int shmid = shmget(SHM_KEY, SHM_SIZE, 0666);
    if (shmid < 0) {
        perror("Failed to access shared memory");
        exit(1);
    }

    // Delete shared memory segment
    if (shmctl(shmid, IPC_RMID, NULL) == -1) {
        perror("Failed to delete shared memory");
    } else {
        printf("Shared memory segment deleted.\n");
    }

    // Remove semaphore
    if (sem_unlink(SEM_NAME) == -1) {
        perror("Failed to unlink semaphore");
    } else {
        printf("Semaphore unlinked and deleted.\n");
    }
}