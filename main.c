#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the maximum stack size
#define MAX_STACK_SIZE 100

// Define a structure to represent the stack
typedef struct {
    double stack[MAX_STACK_SIZE]; // Array to hold stack elements
    int top;                      // Index of the top element
} Stack;

// Function to initialize the stack
void initStack(Stack *s) {
    s->top = 0;          // Set the initial top index to 0
    s->stack[s->top] = 0; // Initialize the stack with 0 at the bottom
}

// Function to push a value onto the stack
void push(Stack *s, double value) {
    // Check if the stack is not full
    if (s->top < MAX_STACK_SIZE - 1) {
        s->stack[++s->top] = value; // Increment top index and add the value
    } else {
        // Print error message and exit if stack is full
        printf("ERROR: STACK OVERFLOW\n");
        exit(1);
    }
}

// Function to pop a value from the stack
double pop(Stack *s) {
    // Check if the stack is not empty
    if (s->top > 0) {
        return s->stack[s->top--]; // Return the top value and decrement top index
    } else {
        // Print error message and exit if stack is empty
        printf("ERROR: STACK EMPTY\n");
        exit(1);
    }
}

// Function to read the input file and process its contents
void readFile(char *filename, Stack *s) {
    // Open the file for reading
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        // Print error message and exit if file cannot be opened
        printf("ERROR: FILE NOT FOUND\n");
        exit(1);
    }

    // Buffer to hold each line from the file
    char line[256];
    // Read lines from the file until end of file
    while (fgets(line, sizeof(line), file)) {
        // Remove newline character from the line
        line[strcspn(line, "\n")] = 0;

        // Attempt to convert the line to a double
        char *end;
        double num = strtod(line, &end);

        // Check if the line is a number
        if (end != line && *end == '\0') {
            // Push the number onto the stack
            push(s, num);
        } else {
            // Process the line as an operation
            if (strcmp(line, "add") == 0) {
                double x = pop(s);  // Pop the top value
                double y = pop(s);  // Pop the second top value
                push(s, x + y);     // Add them and push the result
            } else if (strcmp(line, "subtract") == 0) {
                double x = pop(s);  // Pop the top value
                double y = pop(s);  // Pop the second top value
                push(s, x - y);     // Subtract and push the result
            } else if (strcmp(line, "multiply") == 0) {
                double x = pop(s);  // Pop the top value
                double y = pop(s);  // Pop the second top value
                push(s, x * y);     // Multiply and push the result
            } else if (strcmp(line, "divide") == 0) {
                double x = pop(s);  // Pop the top value
                double y = pop(s);  // Pop the second top value
                if (y == 0) {
                    // Print error message and exit if division by zero
                    printf("ERROR: DIVIDE BY ZERO\n");
                    exit(1);
                }
                push(s, x / y);     // Divide and push the result
            } else if (strcmp(line, "negate") == 0) {
                double x = pop(s);  // Pop the top value
                push(s, -x);        // Negate and push the result
            } else if (strcmp(line, "square") == 0) {
                double x = pop(s);  // Pop the top value
                push(s, x * x);     // Square and push the result
            } else {
                // Print error message and exit if invalid input
                printf("ERROR: INVALID INPUT\n");
                exit(1);
            }
        }
    }

    // Close the file
    fclose(file);
}

// Main function
int main() {
    Stack s;                  // Create a stack instance
    initStack(&s);            // Initialize the stack
    readFile("sums.txt", &s); // Read and process the input file

    // Print the result (top of the stack)
    printf("%.2lf\n", s.stack[s.top]);
    return 0;                 // Exit the program
}
