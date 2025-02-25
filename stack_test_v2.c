#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdbool.h>
#include "stack.h"

/**
 * stack_test.c - Unit tests for stack operations.
 *
 * This file contains unit tests for verifying the correctness of basic stack operations, 
 * including stack creation, push, pop, checking if the stack is empty, and retrieving 
 * the top element. Each test ensures that the stack functions behave as expected and 
 * will terminate the program with an error message if any test fails.
 *
 * Author: Alexander Eriksson (alexander.eriksson@outlook.com)
 *
 * Version information:
 * 2025-02-13 v1.0: Initial version with tests for stack_empty, stack_is_empty, 
 *                  stack_top, stack_push, and stack_pop.
 * 2025-02-19 v2.0: Updated every function except stack_empty_test.
 */

/**
 * stack_empty_test() - Test the stack_empty function.
 *
 * This test verifies that stack_empty() correctly initializes an empty stack.
 * It checks if the returned stack pointer is not NULL.
 *
 * The test fails and exits if stack_empty() returns NULL.
 */
void stack_empty_test(void)
{
    // Print a starting message
    fprintf(stderr,"Starting stack_empty_test()...");
    stack *s = stack_empty(free);

    if(s == NULL)
    {
        // Fail with error message
        fprintf(stderr, "FAIL: expected stack pointer, got NULL\n");
        exit(EXIT_FAILURE);
    }
    
    fprintf(stderr, "Test succeded: stack_empty correctly initialized an empty stack.\n");

    stack_kill(s);
}

/**
 * stack_is_empty_test() - Tests the stack_is_empty function.
 *
 * This test verifies that stack_is_empty() correctly identifies whether a stack 
 * is empty or not. It first checks an empty stack, then pushes a value and checks 
 * that the stack is no longer empty.
 *
 * The test fails and exits if stack_is_empty() fails to identify the empty or 
 * non-empty state of the stack.
 */
void stack_is_empty_test(void)
{
     // Print a starting message
    fprintf(stderr,"Starting stack_is_empty_test()...");

    // Creating empty stack
    stack *s = stack_empty(free);

    if(!stack_is_empty(s))
    {
         // Fail with error message
        fprintf(stderr, "FAIL: stack_is_empty failed to identify the empty stack.\n");
        exit(EXIT_FAILURE);
    }

    // Allocate memory for element
    int *v = malloc(sizeof(int));
    *v = 4;
    // Push 4 on stack
    s = stack_push(s,v);

    if(stack_is_empty(s))
    {
        // Fail with error message
        fprintf(stderr, "FAIL: stack_is_empty failed to identify the non-empty stack.\n");
        exit(EXIT_FAILURE); 
    }
    
    fprintf(stderr, "Test succeeded: stack_is_empty correctly identified a empty stack.\n");
    // Clean up
    stack_kill(s);
}

/**
 * stack_top_test() - Test the stack_top function.
 *
 * This test verifies that stack_top() correctly returns the top element of the stack 
 * without modifying it. It pushes two elements onto the stack and checks if stack_top() 
 * returns the most recently pushed element each time.
 *
 * The test fails and exits if stack_top() returns an incorrect value or fails to update 
 * after a new element is pushed.
 */
void stack_top_test(void)
{
    fprintf(stderr, "Starting stack_top_test()...");
    // Create empty stack
    stack *s = stack_empty(free);

    // Allocate memory for element and push element on the stack
    int *v1 = malloc(sizeof(int));
    *v1 = 10;
    s = stack_push(s, v1);

    // tests that stack_top returns correct value
    if (*(int *)stack_top(s) != 10) {
        fprintf(stderr, "FAIL: stack_top() returned incorrect value\n");
        exit(EXIT_FAILURE);
    }

    // Allocate memory for another element and push element on the stack
    int *v2 = malloc(sizeof(int));
    *v2 = 20;
    s = stack_push(s, v2);

    // Test that stack_top does not return same element 
    if (*(int *)stack_top(s) == 10) {
        fprintf(stderr, "FAIL: stack_top() returned same value after second push. Expected 20, got %d\n", *(int *)stack_top(s));
        exit(EXIT_FAILURE);
    }

    fprintf(stderr, "Test succeeded: stack_top inspected elements.\n");
    //clean up
    stack_kill(s);     
}

/**
 * stack_push_test() - Test the stack_push function.
 *
 * This test verifies that stack_push() correctly adds elements to the stack.
 * It pushes an element onto the stack, pops it off, and checks if the stack
 * is empty afterward to ensure no extra elements were added.
 *
 * The test fails and exits if stack_push() adds too many elements or if the
 * stack is not empty after popping the pushed element.
 */
void stack_push_test(void)
{
    fprintf(stderr, "Starting stack_push_test()...");

    // Create an empty stack
    stack *s = stack_empty(free);

    // Allocate memory for an integer
    int *v1 = malloc(sizeof(int));
    *v1 = 10;

    // Push element on the stack
    s = stack_push(s, v1);

    // Pop element off the stack
    s = stack_pop(s);
   
    // Test if stack_push pushed too many elements
    if(!stack_is_empty(s))
    {
        fprintf(stderr, "FAIL: stack_push added to many elements.\n");
    }

    fprintf(stderr, "Test succeeded: stack_push correctly pushed elements.\n");

    // Clean up
    stack_kill(s);
}


/**
 * stack_pop_test() - Test the stack_pop function.
 *
 * This test verifies that stack_pop() correctly removes the top element 
 * from the stack. It pushes two elements onto the stack, pops one off, 
 * and checks if the new top element is correct.
 *
 * The test fails and exits if stack_pop() does not remove the expected 
 * top element or leaves the wrong element at the top.
 */
void stack_pop_test(void)
{
    fprintf(stderr, "Starting stack_pop_test()...");

    // Create stack
    stack *s = stack_empty(free);

    // // Allocate memory for integers
    int *v1 = malloc(sizeof(int));
    int *v2 = malloc(sizeof(int));
    *v1 = 10;
    *v2 = 20;

    // Push 2 elements on the stack then pop 1 off the stack
    s = stack_push(s, v1);
    s = stack_push(s, v2);
    s = stack_pop(s);

    // Test if stack_pop removes correct element
    if(*(int *)stack_top(s) == *v2)
    {
        // Fail with error message
        fprintf(stderr, "FAIL: stack_pop removed wrong element\n");
        exit(EXIT_FAILURE);
    }
    
    fprintf(stderr, "Test succeeded: stack_pop correctly removed the top element\n");
    
    // Clean up
    stack_kill(s);
}

int main(void)
{
    stack_empty_test();     // Test stack_empty
    stack_is_empty_test();  // Test stack_is_empty
    stack_top_test();       // Test stack_top
    stack_push_test();      // Test stack_push
    stack_pop_test();       // Test stack_pop
    
    fprintf(stderr, "SUCCESS: Implementation passed all tests. Normal exit.\n");
    return 0;
}