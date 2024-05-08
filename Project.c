#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define NUM_TASKS 100

typedef struct TaskStruct {
    time_t creationTime;
    int taskid;
    int burstTime;
    int remainingTime;
} TaskStruct;

// Function prototypes
void simulateFCFS();
void simulateSJF();
void simulateRR();
void printTaskInfo(TaskStruct task);
int compareTasks(const void* a, const void* b);

int main() {
    int choice;

    printf("Choose your simulation:\n");
    printf("1. FCFS\n");
    printf("2. SJF\n");
    printf("3. RR\n");
    printf("Enter your selection: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            simulateFCFS();
            break;
        case 2:
            simulateSJF();
            break;
        case 3:
            simulateRR();
            break;
        default:
            printf("Invalid selection.\n");
            break;
    }

    return 0;
}

void simulateFCFS() {
    TaskStruct tasks[NUM_TASKS];
    time_t start;

    for (int i = 0; i < NUM_TASKS; i++) {
        time(&start);
        tasks[i].creationTime = start;
        tasks[i].taskid = rand() % NUM_TASKS + 1;
        sleep(1);  // Delay to ensure different creation times
    }

    printf("Processing FCFS queue...\n");
    for (int i = 0; i < NUM_TASKS; i++) {
        printTaskInfo(tasks[i]);
        sleep(1);
    }
}

void simulateSJF() {
    TaskStruct tasks[NUM_TASKS];

    for (int i = 0; i < NUM_TASKS; i++) {
        tasks[i].creationTime = time(NULL);
        tasks[i].taskid = i + 1;
        tasks[i].burstTime = rand() % 6 + 1; 
    }

    qsort(tasks, NUM_TASKS, sizeof(TaskStruct), compareTasks);

    printf("Processing SJF queue...\n");
    for (int i = 0; i < NUM_TASKS; i++) {
        printTaskInfo(tasks[i]);
        sleep(1);
    }
}

void simulateRR() {
    TaskStruct tasks[NUM_TASKS];
    int quantum;

    printf("Enter the time slice or quantum: ");
    scanf("%d", &quantum);

    for (int i = 0; i < NUM_TASKS; i++) {
        tasks[i].creationTime = time(NULL);
        tasks[i].taskid = i + 1;
        tasks[i].burstTime = rand() % 6 + 1;
        tasks[i].remainingTime = tasks[i].burstTime;
    }

    int done = 0;
    while (!done) {
        done = 1;
        for (int i = 0; i < NUM_TASKS; i++) {
            if (tasks[i].remainingTime > 0) {
                printf("Working on task ID %d. ", tasks[i].taskid);
                if (tasks[i].remainingTime > quantum) {
                    tasks[i].remainingTime -= quantum;
                    printf("I will get back to it LATER.\n");
                    done = 0;
                } else {
                    printf("I am DONE.\n");
                    tasks[i].remainingTime = 0;
                }
            }
        }
    }
}

void printTaskInfo(TaskStruct task) {
    printf("Working on task ID %d received at time %ld\n", task.taskid, task.creationTime);
}

int compareTasks(const void* a, const void* b) {
    TaskStruct *taskA = (TaskStruct *)a;
    TaskStruct *taskB = (TaskStruct *)b;
    return taskA->burstTime - taskB->burstTime;
}
