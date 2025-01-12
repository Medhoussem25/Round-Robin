#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("Final Round Robin TP 2022\n Using linked lists\n and queues\n\n");

    int loop = 1;
    while (loop == 1) {
        // Define the structure for an Element
        typedef struct Element Element;
        struct Element {
            int arrivalTime, executionTime, responseTime, waitingTime, num, completionTime, executedTime, allocated;
            Element *next;
        };

        // Define the structure for a List
        typedef struct List List;
        struct List {
            Element *first;
        };

        // Function to initialize a list
        List *initialize() {
            List *list = malloc(sizeof(*list));
            if (list == NULL) {
                exit(EXIT_FAILURE);
            }
            list->first = NULL;
            return list;
        }

        // Function to insert an element into the list
        void insert(List *list, int number, int arrival, int execution) {
            Element *newElem = malloc(sizeof(*newElem));
            if (list == NULL || newElem == NULL) {
                exit(EXIT_FAILURE);
            }
            newElem->num = number;
            newElem->arrivalTime = arrival;
            newElem->executionTime = execution;
            newElem->responseTime = 0;
            newElem->waitingTime = 0;
            newElem->completionTime = 0;
            newElem->executedTime = 0;
            newElem->allocated = 0;
            newElem->next = NULL;

            if (list->first == NULL) {
                list->first = newElem;
            } else {
                Element *current = list->first;
                while (current->next != NULL) {
                    current = current->next;
                }
                current->next = newElem;
            }
        }

        // Function to remove the first element of the list
        void delete(List *list) {
            if (list == NULL) {
                exit(EXIT_FAILURE);
            }
            if (list->first != NULL) {
                Element *toDelete = list->first;
                list->first = list->first->next;
                free(toDelete);
            }
        }

        // Function to display the list
        void display(List *list) {
            if (list == NULL) {
                exit(EXIT_FAILURE);
            }
            Element *current = list->first;
            while (current != NULL) {
                printf("Process %d -> ", current->num);
                current = current->next;
            }
        }

        // Initialize three lists
        List *mainList = initialize();
        List *queueList = initialize();
        List *timeList = initialize();

        // Input quantum
        int quantum, arrival, execution;
        printf("\nEnter your quantum: ");
        scanf("%d", &quantum);
        while (quantum < 0) {
            printf("Invalid input. Enter your quantum: ");
            scanf("%d", &quantum);
        }

        // Input the number of processes
        int processCount;
        printf("Enter the number of processes: ");
        scanf("%d", &processCount);
        while (processCount < 0) {
            printf("Invalid input. Enter the number of processes: ");
            scanf("%d", &processCount);
        }

        // Input details for each process
        for (int i = 0; i < processCount; i++) {
            printf("Enter arrival time for process %d: ", i + 1);
            scanf("%d", &arrival);
            while (arrival < 0) {
                printf("Invalid input. Enter arrival time for process %d: ", i + 1);
                scanf("%d", &arrival);
            }

            printf("Enter execution time for process %d: ", i + 1);
            scanf("%d", &execution);
            while (execution < 0) {
                printf("Invalid input. Enter execution time for process %d: ", i + 1);
                scanf("%d", &execution);
            }

            insert(mainList, i + 1, arrival, execution);
        }

        int clock = 0;
        printf("--------------------------------------------------------------\n");
        printf("Process   Arrival Time   Execution Time   Completion   Response   Waiting\n");
        printf("--------------------------------------------------------------\n");

        while (clock <= 1000) {
            int timeStep = 0, completed = 0;
            Element *current = mainList->first;

            // Allocate processes that have arrived
            while (current != NULL) {
                if (current->arrivalTime <= clock && current->allocated == 0) {
                    insert(queueList, current->num, current->arrivalTime, current->executionTime);
                    current->allocated = 1;
                }
                current = current->next;
            }

            Element *candidate = queueList->first;
            if (candidate != NULL) {
                if (candidate->executionTime - quantum <= 0) {
                    timeStep = candidate->executionTime;
                    completed = 1;
                    candidate->executionTime = 0;
                } else {
                    candidate->executionTime -= quantum;
                    timeStep = quantum;
                    completed = 0;
                }

                // Allocate arriving processes during execution
                for (int t = clock; t <= clock + timeStep; t++) {
                    current = mainList->first;
                    while (current != NULL) {
                        if (current->arrivalTime <= t && current->allocated == 0) {
                            insert(queueList, current->num, current->arrivalTime, current->executionTime);
                            current->allocated = 1;
                        }
                        current = current->next;
                    }
                }

                if (completed) {
                    Element *finished = queueList->first;
                    current = mainList->first;
                    while (current != NULL) {
                        if (current->num == finished->num) {
                            current->completionTime = clock + timeStep;
                            current->responseTime = current->completionTime - current->arrivalTime;
                            current->waitingTime = current->responseTime - current->executionTime;
                        }
                        current = current->next;
                    }
                    delete(queueList);
                } else {
                    Element *temp = queueList->first;
                    insert(queueList, temp->num, temp->arrivalTime, temp->executionTime);
                    delete(queueList);
                }
            } else {
                break;
            }
            clock += timeStep;
        }

        Element *node = mainList->first;
        float avgResponseTime = 0, avgWaitTime = 0;

        while (node != NULL) {
            printf("P%d              %d             %d             %d             %d             %d\n",
                   node->num, node->arrivalTime, node->executionTime, node->completionTime, node->responseTime, node->waitingTime);
            avgResponseTime += node->responseTime;
            avgWaitTime += node->waitingTime;
            node = node->next;
        }

        printf("--------------------------------------------------------------\n");
        printf("\nAverage Response Time: %.2f\n", avgResponseTime / processCount);
        printf("Average Waiting Time: %.2f\n", avgWaitTime / processCount);
        printf("--------------------------------------------------------------\n");

        printf("\nPress 1 for another iteration, 0 to exit: ");
        scanf("%d", &loop);
    }

    return 0;
}
