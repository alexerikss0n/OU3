#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdbool.h>
#include "stack.h"

void stack_empty_test(void)
{
    // Print a starting message
    fprintf(stderr,"Starting stack_empty_test()...");
    stack *s = stack_empty(free);

    if(s == NULL)
    {
        // Fail with error message
        fprintf(stderr, "FAIL: expected new stack pointer, got NULL\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        fprintf(stderr, "Test succeded: stack_empty correctly initialized an empty stack.\n");
    }

    stack_kill(s);
}

void stack_is_empty_test(void)
{
     // Print a starting message
    fprintf(stderr,"Starting stack_is_empty_test()...");

    // Creating empty stack
    stack *s = stack_empty(free);

    if(stack_is_empty(s) == true)
    {
        fprintf(stderr, "Test 1 succeeded: stack_is_empty correctly identified an empty stack.\n");
    }
    else
    {
        // Fail with error message
        fprintf(stderr, "FAIL: stack_is_empty failed to identify the empty stack.\n");
        exit(EXIT_FAILURE);
    }
    
    int *v = malloc(sizeof(int));
    *v = 4;
    //push 5 on stack
    s = stack_push(s,v);

    if(!stack_is_empty(s))
    {
        fprintf(stderr, "Test 2 succeeded: stack_is_empty correctly identified a non empty stack.\n");
    }
    else
    {
        // Fail with error message
        fprintf(stderr, "FAIL: stack_is_empty failed to identify the non empty stack.\n");
        exit(EXIT_FAILURE);
    }
    stack_kill(s);
}

void stack_push_test(void)
{
    fprintf(stderr, "Starting stack_push_test()...");

    // Create an empty stack
    stack *s = stack_empty(free);

    // Allocate memory for an integer and push it onto the stack
    int *v1 = malloc(sizeof(int));
    *v1 = 10;
    s = stack_push(s, v1);

    // Check that stack is not empty
    if (stack_is_empty(s)) {
        fprintf(stderr, "FAIL: stack_push failed, stack is still empty after push.\n");
        exit(EXIT_FAILURE);
    }

    // Check that stack_top returns the correct value
    if (*(int *)stack_top(s) != 10) {
        fprintf(stderr, "FAIL: stack_top() returned incorrect value after push. Expected 10, got %d\n", *(int *)stack_top(s));
        exit(EXIT_FAILURE);
    }

    fprintf(stderr, "Test 1 succeeded: stack_push correctly pushed value 10.\n");

    // Allocate another integer and push it
    int *v2 = malloc(sizeof(int));
    *v2 = 30;
    s = stack_push(s, v2);

    // Check that stack_top returns the new value
    if (*(int *)stack_top(s) != 20) {
        fprintf(stderr, "FAIL: stack_top() returned incorrect value after second push. Expected 20, got %d\n", *(int *)stack_top(s));
        exit(EXIT_FAILURE);
    }

    fprintf(stderr, "Test 2 succeeded: stack_push correctly pushed value 20.\n");

    // Clean up
    stack_kill(s);
}

void stack_top_test(void)
{
    fprintf(stderr, "Starting stack_top_test()...");

    stack *s = stack_empty(free);

    int *v2 = malloc(sizeof(int));
    int *v1 = malloc(sizeof(int));
    *v1 = 10;
    *v2 = 20;
    s = stack_push(s, v1);
    s = stack_push(s, v2);

    if (*(int *)stack_top(s) != 20) {
        fprintf(stderr, "FAIL: stack_top() returned incorrect value, Expected 20, got %d\n", *(int *)stack_top(s));
        exit(EXIT_FAILURE);
    }

    int *v3 = malloc(sizeof(int));
    *v3 = 30;
    s = stack_push(s, v3);

    if (*(int *)stack_top(s) == 20) {
        fprintf(stderr, "FAIL: stack_top() returned same value after second push. Expected 30, got %d\n", *(int *)stack_top(s));
        exit(EXIT_FAILURE);
    }

    fprintf(stderr, "Test succeeded: stack_top inspected elements.\n");
    stack_kill(s);     
}

void stack_pop_test(void)
{
    fprintf(stderr, "Starting stack_pop_test()...");

    stack *s = stack_empty(free);

    int *v1 = malloc(sizeof(int));
    int *v2 = malloc(sizeof(int));
    int *v3 = malloc(sizeof(int));
    *v1 = 10;
    *v2 = 20;
    *v3 = 30;

    s = stack_push(s, v1);
    s = stack_pop(s);
    if(!stack_is_empty(s))
    {
        // Fail with error message
        fprintf(stderr, "FAIL: stack_pop removed nothing\n");
        exit(EXIT_FAILURE);
    }

    int *v4 = malloc(sizeof(int));
    s = stack_push(s, v4);
    s = stack_push(s, v2);
    s = stack_push(s, v3);
    s = stack_pop(s);

    if(*(int *)stack_top(s) == 30)
    {
        // Fail with error message
        fprintf(stderr, "FAIL: stack_pop removed wrong element\n");
        exit(EXIT_FAILURE);
    }
    
    if(*(int *)stack_top(s) == 20)
    {
         fprintf(stderr, "Test succeeded: stack_pop correctly removed the top element\n");
    }
    
    stack_kill(s);
}

int main(void)
{
    stack_empty_test();     // Test stack_empty
    stack_is_empty_test();  // Test stack_is_empty
    stack_push_test();      // Test stack_push
    stack_top_test();       // Test stack_top
    stack_pop_test();       // Test stack_pop
    
    fprintf(stderr, "SUCCESS: Implementation passed all tests. Normal exit.\n");
    return 0;
}



















