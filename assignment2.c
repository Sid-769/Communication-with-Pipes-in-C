#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h> // For getpid() and fork()

int main(int argc, char *argv[]) {

    if (argc != 3) {

        printf("Please Enter 2 4-Digit Numbers\n");
        return 1;
    }

    int a = atoi(argv[1]); // Convert command line arg to int
    int b = atoi(argv[2]);

    // Check if 'a' and 'b' are 4-digit numbers
    if (a < 1000 || a > 9999 || b < 1000 || b > 9999) {

        printf("Error: Please enter valid 4-digit numbers only.\n");

        return 1; // Exit if numbers are not 4 digits

    }

    printf("Your integers are %d %d\n", a, b);

    // Partition 'a' into a1 and a2
    int a1 = a / 100;
    int a2 = a % 100;

    // Partition 'b' into b1 and b2
    int b1 = b / 100;
    int b2 = b % 100;

    int pipe1[2]; // Pipe for Parent -> Child
    int pipe2[2]; // Pipe for Child -> Parent

    if (pipe(pipe1) == -1 || pipe(pipe2) == -1) {

        perror("pipe");

        exit(1); // Exit if pipe creation fails

    }

    // Fork the process to create a child
    pid_t pid = fork();

    if (pid < 0) {

        perror("fork");

        exit(1); // Exit if fork fails

    }

    if (pid > 0) { // Parent Process

        printf("Parent (PID %d): created child (PID %d)\n", getpid(), pid);

        // Close unused pipes
        close(pipe1[0]); // Close reading end of Parent -> Child pipe
        close(pipe2[1]); // Close writing end of Child -> Parent pipe

        // Step 4.1
        printf("\n###\n# Calculating X\n###\n");
        printf("Parent (PID %d): Sending %d to child\n", getpid(), a1);
        printf("Parent (PID %d): Sending %d to child\n", getpid(), b1);

        write(pipe1[1], &a1, sizeof(a1));
        write(pipe1[1], &b1, sizeof(b1));

        // Step 4.2
        int A, X;
        read(pipe2[0], &A, sizeof(A));
        printf("Parent (PID %d): Received %d from child\n", getpid(), A);

        X = A * 10000;

        // Step 4.3
        printf("\n###\n# Calculating Y\n###\n");
        printf("Parent (PID %d): Sending %d to child\n", getpid(), a2);
        printf("Parent (PID %d): Sending %d to child\n", getpid(), b1);

        write(pipe1[1], &a2, sizeof(a2));
        write(pipe1[1], &b1, sizeof(b1));

        // Step 4.4
        int B;
        read(pipe2[0], &B, sizeof(B));

        printf("Parent (PID %d): Received %d from child\n", getpid(), B);

        // Step 4.5
        printf("Parent (PID %d): Sending %d to child\n", getpid(), a1);
        printf("Parent (PID %d): Sending %d to child\n", getpid(), b2);

        write(pipe1[1], &a1, sizeof(a1));
        write(pipe1[1], &b2, sizeof(b2));

        // Step 4.6
        int C, Y;
        read(pipe2[0], &C, sizeof(C));
        printf("Parent (PID %d): Received %d from child\n", getpid(), C);

        Y = (B + C) * 100;

        printf("Parent calculated Y = (B + C) * 10^2: %d\n", Y);

        // Step 4.7
        printf("\n###\n# Calculating Z\n###\n");
        printf("Parent (PID %d): Sending %d to child\n", getpid(), a2);
        printf("Parent (PID %d): Sending %d to child\n", getpid(), b2);

        write(pipe1[1], &a2, sizeof(a2));
        write(pipe1[1], &b2, sizeof(b2));

        // Step 4.8
        int D, Z;
        read(pipe2[0], &D, sizeof(D));
        printf("Parent (PID %d): Received %d from child\n", getpid(), D);

        Z = D * 1;

        int result = X + Y + Z;
        printf("\n%d*%d == %d + %d + %d == %d\n", a, b, X, Y, Z, result);

        // Close pipes after use
        close(pipe1[1]);
        close(pipe2[0]);

    } else { // Child process

        // Close unused pipes
        close(pipe1[1]); // Close writing end of Parent -> Child pipe
        close(pipe2[0]); // Close reading end of Child -> Parent pipe

        int a1_c, b1_c, a2_c, b2_c;

        // Step 4.2
        int A_mult;
        read(pipe1[0], &a1_c, sizeof(a1_c));
        read(pipe1[0], &b1_c, sizeof(b1_c));

        printf("Child (PID %d): Received %d from parent\n", getpid(), a1_c);
        printf("Child (PID %d): Received %d from parent\n", getpid(), b1_c);

        A_mult = a1_c * b1_c;
        printf("Child (PID %d): Sending %d to parent\n", getpid(), A_mult);
        write(pipe2[1], &A_mult, sizeof(A_mult)); // Return A back to the parent

        // Step 4.4
        int B_mult;
        read(pipe1[0], &a2_c, sizeof(a2_c));
        read(pipe1[0], &b1_c, sizeof(b1_c));

        printf("Child (PID %d): Received %d from parent\n", getpid(), a2_c);
        printf("Child (PID %d): Received %d from parent\n", getpid(), b1_c);

        B_mult = a2_c * b1_c;
        printf("Child (PID %d): Sending %d to parent\n", getpid(), B_mult);

        write(pipe2[1], &B_mult, sizeof(B_mult)); // Return B back to the parent

        // Step 4.6
        int C_mult;
        read(pipe1[0], &a1_c, sizeof(a1_c));
        read(pipe1[0], &b2_c, sizeof(b2_c));

        printf("Child (PID %d): Received %d from parent\n", getpid(), a1_c);
        printf("Child (PID %d): Received %d from parent\n", getpid(), b2_c);

        C_mult = a1_c * b2_c;
        printf("Child (PID %d): Sending %d to parent\n", getpid(), C_mult);

        write(pipe2[1], &C_mult, sizeof(C_mult)); // Return C back to the parent

        // Step 4.8
        int D_mult;
        read(pipe1[0], &a2_c, sizeof(a2_c));
        read(pipe1[0], &b2_c, sizeof(b2_c));

        printf("Child (PID %d): Received %d from parent\n", getpid(), a2_c);
        printf("Child (PID %d): Received %d from parent\n", getpid(), b2_c);

        D_mult = a2_c * b2_c;
        printf("Child (PID %d): Sending %d to parent\n", getpid(), D_mult);
        
        write(pipe2[1], &D_mult, sizeof(D_mult)); // Return D back to the parent

        // Close pipes after use
        close(pipe1[0]);
        close(pipe2[1]);

        // Step 4.9: Child exits
        exit(0); // Child process exits successfully

    }

    return 0; // Exit successfully
}
