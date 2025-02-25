#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "int_stack.h"

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
      
    if(stack_is_empty(s))
    {
        fprintf(stderr, "Test succeded: stack_empty correctly initialized an empty stack.\n");
    }
    // Fail with error message
    fprintf(stderr, "FAIL: stack_empty() failed to create empty stack.\n");
    exit(EXIT_FAILURE);  
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


void stack_push_test(void)
{
    fprintf(stderr, "Starting stack_push_test()...");
    // Create an empty stack
    stack s = stack_empty();  
    
    // Push value on the stack
    s = stack_push(s, 4);
   
    // Check if pushed integer is correct value
    if (stack_top(s) != 4) 
    {
        // Fail with error message
        fprintf(stderr, "FAIL: stack_push added wrong value to the stack.\n");
        exit(EXIT_FAILURE);
    } 
    
    // Push one more value on the stack
    s = stack_push(s, 5);

    //check if stack_push placed value at correct position
    if(stack_top(s) == 4)
    {  
        // Fail with error message
        fprintf(stderr, "FAIL: stack_push placed value at wrong position.\n");
        exit(EXIT_FAILURE);
    }
    
    // pop values off the stack
    s = stack_pop(s);
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


void stack_pop_test(void)
{
    fprintf(stderr, "Starting stack_pop_test()...");
    // Create an empty stack
    stack s = stack_empty();

    // push an element on stack
    s = stack_push(s, 5);
    s = stack_push(s, 15);
    s = stack_push(s, 15);
   
    // pop element off stack
    s = stack_pop(s);

    if(stack_top(s) == 10)
    {
         fprintf(stderr, "Test succeeded: stack_pop correctly removed the top element\n");
    }
    else if(stack_top(s) == 15 && s.first_free_pos == 2)
    {
        // Fail with error message
        fprintf(stderr, "FAIL: stack_pop removed wrong element\n");
        exit(EXIT_FAILURE);
    }
    else if(stack_top(s) == 15 && s.first_free_pos == 3)
    {
        // Fail with error message
        fprintf(stderr, "FAIL: stack_pop removed 0 elements.\n");
        exit(EXIT_FAILURE);
    }
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
