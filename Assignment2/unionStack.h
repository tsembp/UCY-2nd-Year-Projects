/**
 * @file unionStack.h
 * @brief Header file for the implementation of a stack that can hold both characters and Elements.
 * 
 * This file contains the definitions and function declarations for a stack that supports 
 * storing either characters or elements (defined in periodicTable.h). The stack uses a union to 
 * hold different types of data, along with an enum to specify the type of data stored.
 * 
 * The stack supports standard operations such as initialization, pushing different types 
 * of data (char or Element), popping, peeking top elemnet and printing the stack contents 
 * for debugging purposes.
 * 
 * @author  Panagiotis Tsembekis
 * @bug     No known bugs.
 */

#ifndef UNIONSTACK_H
#define UNIONSTACK_H
#include <stdbool.h>
#include "periodicTable.h"


/**
 * @enum StackDataType
 * @brief Enum to specify the type of data stored in the stack.
 * 
 * This enum indicates whether the stack node holds a character or an Element.
 */
typedef enum {
    CHAR_TYPE,
    ELEMENT_TYPE
} StackDataType;


/**
 * @union StackData
 * @brief Union to store either a character or an Element.
 * 
 * This union allows a stack node to store either a single character 
 * or an Element from the periodic table.
 * 
 * @var StackData::charData
 * The character stored in the stack node, if the type is CHAR_TYPE.
 * 
 * @var StackData::elementData
 * The Element stored in the stack node, if the type is ELEMENT_TYPE.
 */
typedef union {
    char charData;
    Element elementData;
} StackData;


/**
 * @struct StackNode
 * @brief A structure representing a node in the stack.
 * 
 * Each node in the stack contains a union (to store either a char or an Element),
 * an enum (to specify the type of data), and a pointer to the next node.
 * 
 * @var StackNode::data
 * The union holding the data (char or Element).
 * 
 * @var StackNode::dataType
 * The enum indicating the type of data stored in the node.
 * 
 * @var StackNode::next
 * Pointer to the next node in the stack.
 */
typedef struct StackNode {
    StackData data; // union to hold the actual data (char or Element)
    StackDataType dataType; // enum to indicate the type of data stored
    struct StackNode *next; // pointer to next node
} StackNode;


/**
 * @struct UnionStack
 * @brief A structure representing the stack itself.
 * 
 * The stack consists of a linked list of StackNodes. Each node stores a union of either 
 * a char or an Element, and the stack keeps track of the top node and its current size.
 * 
 * @var UnionStack::top
 * Pointer to the top node of the stack.
 * 
 * @var UnionStack::size
 * The current number of elements in the stack.
 */
typedef struct {
    StackNode *top; // pointer to the top of the stack
    int size; // current size of the stack
} UnionStack;


/**
 * @brief Initializes the union stack.
 * 
 * This function allocates memory for a new stack and sets the initial size to 0.
 * The top pointer is initialized to NULL.
 * 
 * @param[in,out] stack A pointer to the pointer of the stack to be initialized.
 * @return int Returns 0 if initialization is successful, or -1 if memory allocation fails.
 */
int initUnionStack(UnionStack **stack);


/**
 * @brief Checks if the union stack is empty.
 * 
 * This function checks whether the stack contains any elements by looking at 
 * the size and top pointer.
 * 
 * @param[in] stack The stack to check.
 * @return bool Returns true if the stack is empty, false otherwise.
 */
bool isEmptyUnion(UnionStack *stack);


/**
 * @brief Pushes a character onto the union stack.
 * 
 * This function adds a new character to the top of the stack. The type of 
 * the node is set to CHAR_TYPE, and the top pointer and size are updated accordingly.
 * 
 * @param[in,out] stack The stack to which the character will be pushed.
 * @param[in] c The character to be pushed onto the stack.
 * @return int Returns 0 on success, or -1 if memory allocation fails.
 */
int pushCharUnion(UnionStack *stack, char c);


/**
 * @brief Pushes an Element onto the union stack.
 * 
 * This function adds a new Element to the top of the stack. The type of 
 * the node is set to ELEMENT_TYPE, and the top pointer and size are updated accordingly.
 * 
 * @param[in,out] stack The stack to which the Element will be pushed.
 * @param[in] element The Element to be pushed onto the stack.
 * @return int Returns 0 on success, or -1 if memory allocation fails.
 */
int pushElementUnion(UnionStack *stack, Element element);


/**
 * @brief Pops an item from the union stack.
 * 
 * This function removes the top element from the stack and stores its value in 
 * the provided returnValue. The returnType indicates whether the value was a char 
 * or an Element.
 * 
 * @param[in,out] stack The stack from which to pop the element.
 * @param[out] returnValue A pointer to store the value of the popped element.
 * @param[out] returnType A pointer to store the type (CHAR_TYPE or ELEMENT_TYPE) of the popped element.
 * @return int Returns 0 on success, or -1 if the stack is empty.
 */
int popUnion(UnionStack *stack, StackData *returnValue, StackDataType *returnType);


/**
 * @brief Peeks at the type of the top element in the union stack.
 * 
 * This function returns the type (CHAR_TYPE or ELEMENT_TYPE) of the element at 
 * the top of the stack without removing it.
 * 
 * @param[in] stack The stack to check.
 * @return StackDataType The type of the top element (CHAR_TYPE or ELEMENT_TYPE).
 */
StackDataType topUnionType(UnionStack *stack);


/**
 * @brief Prints the entire union stack (for debugging purposes).
 * 
 * This function prints each element in the stack from top to bottom, along with its type.
 * It is mainly used for debugging purposes and does not modify the stack.
 * 
 * @param[in] stack The stack to be printed.
 */
void printUnionStack(UnionStack *stack);

#endif // UNIONSTACK_H