# Round Robin Scheduling - Final Project (2022)

This program implements a **Round Robin** scheduling algorithm using **ArrayList** and **queues** to simulate process management. It takes input for processes, their arrival times, and execution times, and then executes them in a round-robin fashion with a given quantum. The program calculates key metrics such as completion time, response time, and waiting time for each process and then computes their averages.

## Features

- **Round Robin Scheduling**: Executes processes in a round-robin manner with a specified time quantum.
- **Array List and Queue**: Processes are managed using Array lists and queues.
- **Process Metrics**: Calculates completion time, response time, and waiting time for each process.
- **Averages**: Computes the average response time and waiting time for all processes.

## Program Structure

### Data Structures:
1. **Element Structure**: 
   - `tempsArrive`: Arrival time of the process.
   - `tempsExecution`: Execution time of the process.
   - `tempsReponse`: Response time of the process.
   - `tempsAttente`: Waiting time of the process.
   - `tempsComplete`: Completion time of the process.
   - `tempsExc`: Remaining execution time.
   - `alloue`: A flag indicating if the process has been allocated.
   - `suivant`: Pointer to the next element (process) in the list.

2. **Liste Structure**:
   - `premier`: Pointer to the first element in the list.

### Functions:
1. **initialisation**: Initializes an empty list.
2. **insertion**: Inserts a new process into the list.
3. **suppression**: Removes the first process from the list.
4. **afficherListe**: Displays the current list of processes.

### Main Loop:
1. Accepts input for the quantum and number of processes.
2. Inserts processes with their arrival and execution times.
3. Executes the processes using the Round Robin algorithm, and calculates completion time, response time, and waiting time for each process.
4. Displays the results in tabular format and computes average times.

---

## Compilation and Execution

To compile and run the program, follow these steps:

### Prerequisites
- C Compiler (e.g., GCC)

### Compilation:
1. Save the code in a file, for example `round_robin.c`.
2. Open a terminal and navigate to the directory containing `round_robin.c`.
3. Run the following command to compile the program:

   ```bash
   gcc -o round_robin round_robin.c
   ```

### Execution:
Once the code is compiled, run the program with the following command:

```bash
./round_robin
```

### Example Input and Output:

#### Input:
```plaintext
Enter your quantum: 3
Enter the number of processes: 3
Enter the arrival time of process 1: 0
Enter the execution time of process 1: 5
Enter the arrival time of process 2: 1
Enter the execution time of process 2: 3
Enter the arrival time of process 3: 2
Enter the execution time of process 3: 6
```

#### Output:
```plaintext
------------------------------------------------------------------------------
Process   Arrival Time   Execution Time   Completion Time   Response Time   Waiting Time 
------------------------------------------------------------------------------
Process 1   0             5                10               10              5
Process 2   1             3                 6                5              2
Process 3   2             6                15               13              7
------------------------------------------------------------------------------

Average Response Time: 9
Average Waiting Time: 4
------------------------------------------------------------------------------
```

---

## Author

**Houssam Bouagal (2022)**  
This project is part of the final year assignment for computer science.  
For any questions or suggestions, feel free to contact me at **[mouhamedhoussem813@gmail.com]**.

---

## License

This project is open source you can reuse
