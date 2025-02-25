#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "int_stack.h"

/**
 * int_stack_test.c - Unit tests for integer stack operations.
 *
 * This file contains unit tests for verifying the correctness of the integer stack 
 * operations defined in int_stack.h. The tests cover creating an empty stack, pushing 
 * and popping integers, checking if the stack is empty, and retrieving the top element. 
 * Each test validates the expected behavior and terminates with an error message if 
 * any test fails.
 *
 * Author: Alexander Eriksson (alexander.eriksson@outlook.com)
 *
 * Version information:
 * 2025-02-13 v1.0: Initial version with tests for stack_empty, stack_is_empty, 
 *                  stack_top, stack_push, and stack_pop.
 * 2025-02-19 v2.0: Updated every function except stack_empty_test.
 */

/*
 * stack_empty_test() - Test the stack_empty function.
 *
 * Creates an empty stack and verifies that stack_is_empty()
 * Prints a success message if the test passes;
 * otherwise, it prints an error message and exits.
 */


void stack_empty_test(void)
{
    // Print a starting message
    fprintf(stderr,"Starting stack_empty_test()...");
    
    // creating an empty stack
    stack s = stack_empty();
      
    if(!stack_is_empty(s))
    {
        // Fail with error message
        fprintf(stderr, "FAIL: stack_empty() failed to create empty stack.\n");
        exit(EXIT_FAILURE); 
        
    }
    
    fprintf(stderr, "Test succeded: stack_empty correctly initialized an empty stack.\n");
}

/**
 * stack_is_empty_test() - Test the stack_is_empty function.
 *
 * Creates an empty stack, pushes an element onto it, and checks that
 * stack_is_empty() correctly identifies the stack as non-empty.
 * Prints a success message if the test passes; otherwise, it prints
 * an error message and exits.
 */
void stack_is_empty_test(void)
{
    // Print a starting message
    fprintf(stderr,"Starting stack_is_empty_test()...");

    // Creating empty stack
    stack s = stack_empty();

    //push 5 on the stack
    s = stack_push(s,5);

    //check if stack_is_empty() returns false when stack is not empty
    if(!stack_is_empty(s))
    {
        fprintf(stderr, "Test succeeded: stack_is_empty correctly identified a non empty stack.\n");
    }
    else
    {
        // Fail with error message
        fprintf(stderr, "FAIL: stack_is_empty failed to identify the non empty stack.\n");
        exit(EXIT_FAILURE);
    }
    
}

/**
 * stack_top_test() - Test the stack_top function.
 *
 * This test verifies that stack_top() correctly returns the top element 
 * of the stack after multiple push operations. 
 *
 * The test fails and exits if stack_top() does not return the expected values.
 */
void stack_top_test(void)
{
    fprintf(stderr, "Starting stack_top_test()...");

    // Create an empty stack and push a value on the stack
    stack s = stack_empty();
    s = stack_push(s, 5);  

    // Check if the top element is 5
    if (stack_top(s) != 5)
    {
        // Fail with error message
        fprintf(stderr, "FAIL: stack_top did not return the correct top element.\n");
        exit(EXIT_FAILURE);
    } 
    
    // Push another value on the stack
    s = stack_push(s, 4);

    // Check if stack_top() always return same value
    if (stack_top(s) == 5) 
    {
        // Fail with error message
        fprintf(stderr, "FAIL: stack_top always returns same element\n");
        exit(EXIT_FAILURE);
       
    } 
    
    fprintf(stderr, "Test succeeded: stack_top correctly returned the top element.\n");  
}

/**
 * stack_push_test() - Test the stack_push function.
 *
 * This test verifies that stack_push() correctly adds elements to the stack 
 * and that no extra elements are added. 
 *
 * The test fails and exits if stack_push() adds more elements than expected.
 */
void stack_push_test(void)
{
    fprintf(stderr, "Starting stack_push_test()...");
    // Create an empty stack
    stack s = stack_empty();  
    
    // Push values on the stack
    s = stack_push(s, 4);
    
    // pop values off the stack
    s = stack_pop(s);

    // check if stack_push added to many elements
    if(!stack_is_empty(s))
    {
         // Fail with error message
        fprintf(stderr, "FAIL: stack_push placed too many values.\n");
        exit(EXIT_FAILURE);
    }

    fprintf(stderr, "Test succeeded: stack_push correctly added elements to the stack.\n");
}

/**
 * stack_pop_test() - Test the stack_pop function.
 *
 * This test verifies that stack_pop() correctly removes the top element 
 * from the stack. It pushes two values onto the stack, pops one off, 
 * and checks if the remaining top element is correct.
 *
 * The test fails and exits if stack_pop() does not remove the expected value.
 */
void stack_pop_test(void)
{
    fprintf(stderr, "Starting stack_pop_test()...");
    // Create an empty stack
    stack s = stack_empty();

    // pushes 2 values then pops one off stack
    s = stack_push(s,5);
    s = stack_push(s,4);
    s = stack_pop(s);

    if(stack_top(s) == 4)
    {
        // Fail with error message
        fprintf(stderr, "FAIL: stack_pop removed wrong value.\n");
        exit(EXIT_FAILURE);
    }
    
    fprintf(stderr, "Test succeeded: stack_pop correctly removed the top element\n");
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
