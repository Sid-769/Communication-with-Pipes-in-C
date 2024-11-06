
Two-Way Communication with Pipes
=================================

Overview
--------
This program demonstrates inter-process communication (IPC) in a UNIX-like environment using pipes. 
It takes two 4-digit integers as command-line arguments, partitions these numbers, and performs a mathematical operation 
between a parent and a child process.

Features
--------
1. **Input Validation**:
   - Ensures both command-line arguments are valid 4-digit integers.

2. **Partitioning Numbers**:
   - Splits each 4-digit number into two 2-digit components.
   - Example: `1234` becomes `12` and `34`.

3. **Inter-Process Communication (IPC)**:
   - Implements bidirectional communication between a parent and a child process using two pipes:
     - **Pipe 1**: Parent sends data to the child.
     - **Pipe 2**: Child sends processed data back to the parent.

4. **Mathematical Operations**:
   - The child process performs computations using the received values and returns results to the parent.

Compilation and Execution
-------------------------

### Compilation
Use the following command to compile the program:
```bash
gcc assignment2.c -o assignment2 -lm
```
(Note: `-lm` is required for linking math functions.)

### Execution
Run the program with two 4-digit integers as arguments:
```bash
./assignment2 1234 5678
```

Example output:
```
Your integers are 1234 5678
Partitioned values: 12, 34, 56, 78
Sum from child: <result>
```

Screenshots
-----------

### Sample Outputs
- ![Output 1](assignment-2output.png)
- ![Output 2](assignment-2output2.png)

Purpose
-------
This program is designed to:
- **Demonstrate IPC using pipes**.
- **Provide experience with process creation and communication** in C.
- **Reinforce numeric manipulations** and operations across processes.
