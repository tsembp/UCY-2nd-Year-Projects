/**
 * @file unionStack.c
 * @brief Implementation of union stack functions for storing generic data.
 *
 * This source file provides detailed implementations of functions for managing a union stack,
 * which is capable of storing different types of data (e.g., char and Element). Functions include
 * stack initialization, check if stack is empty, push operations for different data types,
 * pop, and peek operations.
 * 
 * @author  Panagiotis Tsembekis
 * @bug     No known bugs.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "unionStack.h"

// Initialize the union stack
int initUnionStack(UnionStack **stack) {
    *stack = (UnionStack *) malloc(sizeof(UnionStack)); // allocate memory for a union stack
    if (*stack == NULL) { // check if the required memory can we allocated
        perror("Unable to allocate memory for union stack initialization.");
        return EXIT_FAILURE;
    }

    // Initialize top of stack as NULL and its size to 0
    (*stack)->top = NULL;
    (*stack)->size = 0;

    return EXIT_SUCCESS;
}


// Check if the union stack is empty
bool isEmptyUnion(UnionStack *stack) {
    return (stack->top == NULL); // if the stack's top is NULL -> return false, true otherwise
}


// Push a character onto the union stack
int pushCharUnion(UnionStack *stack, char c) {
    if (stack == NULL) {
        perror("Union stack is NULL.");
        return EXIT_FAILURE;
    }

    StackNode *newNode = (StackNode *) malloc(sizeof(StackNode)); // allocate memory for a Node pointer
    if (newNode == NULL) { // check if required memory can be allocated
        perror("Unable to allocate memory for new node.");
        return EXIT_FAILURE;
    }

    newNode->data.charData = c; // assigne the pushed character to the new node's data
    newNode->dataType = CHAR_TYPE; // mark the data type as CHAR_TYPE
    newNode->next = stack->top; // new node is our new top, update top and top->next accordingly
    stack->top = newNode;
    (stack->size)++; // increment stack's size

    return EXIT_SUCCESS;
}


// Push an Element onto the union stack
int pushElementUnion(UnionStack *stack, Element element) {
    if (stack == NULL) {
        perror("Union stack is NULL.");
        return EXIT_FAILURE;
    }

    StackNode *newNode = (StackNode *) malloc(sizeof(StackNode)); // alocate memory space for a Node pointer
    if (newNode == NULL) { // if required memory can't be allocated print according message
        perror("Unable to allocate memory for new node.");
        return EXIT_FAILURE;
    }

    newNode->data.elementData = element; // assign pushed Element to newNode's data
    newNode->dataType = ELEMENT_TYPE; // mark the data type as ELEMENT_TYPE
    newNode->next = stack->top; // new node is our new stack top
    stack->top = newNode;
    (stack->size)++; // increment stack's size

    return EXIT_SUCCESS;
}


// Pop from the union stack
int popUnion(UnionStack *stack, StackData *returnValue, StackDataType *returnType) {
    if (stack == NULL || stack->top == NULL) {
        perror("Can't pop from empty/null union stack.");
        return EXIT_FAILURE;
    }

    StackNode *temp = stack->top; // get stack's top node
    *returnValue = temp->data; // return the popped value
    *returnType = temp->dataType; // return the type of the data
    stack->top = stack->top->next; // new top is the next node after top

    free(temp); // free space that previous top was taking up
    (stack->size)--; // decrease stack's size

    if(stack->size == 0){
        stack->top = NULL;
    }

    return EXIT_SUCCESS;
}


// Peek at the top of the union stack
StackDataType topUnionType(UnionStack *stack) {
    if (stack == NULL || stack->top == NULL) {
        perror("Unable to retrieve top of empty/null union stack.");
        return -1;
    }
    return stack->top->dataType;  // return the type of the top element
}


// Print the stack
void printUnionStack(UnionStack *stack) {
    if (stack == NULL || stack->top == NULL) {
        printf("Stack is empty.\n");
        return;
    }

    StackNode *current = stack->top;
    while (current != NULL) {
        if (current->dataType == CHAR_TYPE) { // print char data
            printf("%c ", current->data.charData);
        } else if (current->dataType == ELEMENT_TYPE) { // print element data
            printf("%s(%d) ", current->data.elementData.chemSymbol, current->data.elementData.atomicNumber);
        }
        current = current->next;
    }
    printf("\n");
}


#ifdef DEBUG_USTACK

int main() {
    UnionStack *stack = NULL;

    // Test stack initialization
    printf("Testing stack initialization...\n");
    if (initUnionStack(&stack) == EXIT_SUCCESS && stack != NULL) {
        printf("Stack initialized successfully.\n");
    } else {
        printf("Failed to initialize stack.\n");
        return EXIT_FAILURE;
    }

    // Test pop on empty stack
    printf("Attempting to pop from an empty stack...\n");
    StackData data;
    StackDataType type;
    int popResult = popUnion(stack, &data, &type);
    if (popResult == EXIT_FAILURE) {
        printf("Correct behavior: Cannot pop from an empty stack.\n");
    } else {
        printf("Error: Popping from an empty stack should fail.\n");
    }

    // Test pushing and popping operations
    printf("Testing push operations...\n");
    pushCharUnion(stack, 'a');
    pushElementUnion(stack, (Element){.chemSymbol = "He", .atomicNumber = 2});

    printf("Testing pop operations...\n");
    popUnion(stack, &data, &type);
    if (type == ELEMENT_TYPE) {
        printf("Popped Element: %s, Atomic Number: %d\n", data.elementData.chemSymbol, data.elementData.atomicNumber);
    } else if (type == CHAR_TYPE) {
        printf("Popped Character: %c\n", data.charData);
    }

    printf("Stack after 1st pop operation: ");
    printUnionStack(stack);

    popUnion(stack, &data, &type);
    if (type == ELEMENT_TYPE) {
        printf("Popped Element: %s, Atomic Number: %d\n", data.elementData.chemSymbol, data.elementData.atomicNumber);
    } else if (type == CHAR_TYPE) {
        printf("Popped Character: %c\n", data.charData);
    }

    printf("Stack after 2nd pop operation: ");
    printUnionStack(stack);

    // Test again popping on empty stack after pop operations
    printf("Re-attempting to pop on empty stack after clear...\n");
    popResult = popUnion(stack, &data, &type);
    if (popResult == EXIT_FAILURE) {
        printf("Correct behavior after clear: Cannot pop from an empty stack.\n");
    } else {
        printf("Error after clear: Popping from an empty stack should fail.\n");
    }

    printf("Stack operations test completed.\n");
    
    return 0;
}
#endif // DEBUG_USTACK
