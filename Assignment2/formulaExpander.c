/**
 * @file formulaExpander.c
 * @brief Implementation for expanding, validating, and processing chemical formulas.
 *
 * This .c file provides implementations for expanding chemical formulas to their full
 * representations, validating the balance of parentheses in chemical formulas, and counting
 * protons based on expanded formulas using data from a periodic table. It utilizes stack operations
 * extensively to manage elements and parentheses during the parsing and expansion processes.
 * 
 * @author  Panagiotis Tsembekis
 * @bug     No known bugs.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "formulaExpander.h"

#define MAX_FORMULA_LENGTH 1024 /**< Buffer size for reading formulas */


/**
 * @brief Processes a chemical formula and returns its expanded form.
 *
 * This function takes a chemical formula in the form of a string, parses it,
 * and produces an expanded formula where elements are repeated based on
 * multipliers specified in the formula. It supports nested parentheses and
 * handles single, double, and triple-letter chemical symbols.
 *
 * @param formula A string representing the chemical formula to be processed.
 * @return A dynamically allocated string containing the expanded formula,
 *         or NULL if there is an error in allocation or processing.
 */
static char *processFormula(const char *formula) {
    UnionStack *stack = NULL;   
    if (initUnionStack(&stack) != EXIT_SUCCESS) { // initialize stack and handle error
        perror("Error initializing stack.");
        return NULL;
    }

    const char *p = formula;
    StackData poppedData;
    StackDataType poppedType;

    // Variables for building the expanded formula string
    size_t bufferSize = 256; // initial buffer size
    size_t length = 0;
    char *expandedFormula = (char *) malloc(bufferSize);
    if (!expandedFormula) { // ensure that space has been allocateed
        perror("Failed to allocate memory for expanded formula");
        free(stack);
        return NULL;
    }

    while (*p != '\0') {
        if (isalpha(*p)) {
            Element element;
            element.atomicNumber = 1;

            if (isupper(*p) && islower(*(p + 1)) && islower(*(p + 2))) { // 3-letter elements
                element.chemSymbol[0] = *p;
                element.chemSymbol[1] = *(p + 1);
                element.chemSymbol[2] = *(p + 2);
                element.chemSymbol[3] = '\0'; // ensure termination character
                p += 2; // skip next two letters since we handled them above
            } else if (isupper(*p) && islower(*(p + 1))) { // 2-letter elements
                element.chemSymbol[0] = *p;
                element.chemSymbol[1] = *(p + 1);
                element.chemSymbol[2] = '\0'; // ensure termination character
                p++; // skip next letter, we handled it above
            } else { // single letter element
                element.chemSymbol[0] = *p;
                element.chemSymbol[1] = '\0';
            }

            pushElementUnion(stack, element);
        } else if (isdigit(*p)) {
            int multiplier = 0;

            // Calculate multiplier (handles multi-digit multipliers too)
            while (isdigit(*p)) {
                multiplier = (multiplier * 10) + (*p - '0');
                p++;
            }

            // Pop the last element and add it multiplier-times
            if (popUnion(stack, &poppedData, &poppedType) == EXIT_SUCCESS && poppedType == ELEMENT_TYPE) {
                for (int i = 0; i < multiplier; i++) {
                    pushElementUnion(stack, poppedData.elementData); // push multiplier-times
                }
            }

            continue;
        } else if (*p == '(') { // begining of group
            Element dummy = { "(", 0 }; // push dummy element to mark begining of group
            pushElementUnion(stack, dummy);
        } else if (*p == ')') { // end of group
            Element tempArray[MAX_FORMULA_LENGTH];
            int tempIndex = 0;

            // Pop until we find the start of group ( '(' )
            while (popUnion(stack, &poppedData, &poppedType) == EXIT_SUCCESS && poppedType == ELEMENT_TYPE && strcmp(poppedData.elementData.chemSymbol, "(") != 0) {
                tempArray[tempIndex++] = poppedData.elementData;
            }

            // Look for multipliers after the end of group
            p++;
            int groupMultiplier = 1;
            if (isdigit(*p)) {
                groupMultiplier = 0;
                while (isdigit(*p)) {
                    groupMultiplier = (groupMultiplier * 10) + (*p - '0');
                    p++;
                }
            }

            // Push elements of the group back with applied multiplier
            for (int i = 0; i < groupMultiplier; i++) {
                for (int j = tempIndex - 1; j >= 0; j--) {
                    pushElementUnion(stack, tempArray[j]);
                }
            }
    
            continue; // continue parsing after handling group
        }

        p++; // move to next character of formula
    }

    // Use a temporary stack to inverse the elements inside the main stack
    UnionStack *tempStack = NULL;
    initUnionStack(&tempStack);

    while (!isEmptyUnion(stack)) { // pop from main and push to temp until main is empty
        if (popUnion(stack, &poppedData, &poppedType) == EXIT_SUCCESS && poppedType == ELEMENT_TYPE) {
            pushElementUnion(tempStack, poppedData.elementData);
        }
    }

    while (!isEmptyUnion(tempStack)) {
        if (popUnion(tempStack, &poppedData, &poppedType) == EXIT_SUCCESS && poppedType == ELEMENT_TYPE) { // pop elements until failure
            size_t symbolLen = strlen(poppedData.elementData.chemSymbol); // get symbol's length (1,2 or 3)
            if (length + symbolLen + 2 >= bufferSize) { // if adding symbol to extendedFormula exceeds our buffer size we need to realloc
                bufferSize *= 2;
                char *newPtr = (char *)realloc(expandedFormula, bufferSize); // attempt to reallocate (use temp pointer so we dont lose reference to our string)
                if (!newPtr) { // failed realloc attempt
                    free(expandedFormula);
                    perror("Failed to realloc memory for expanded formula");
                    free(stack);
                    free(tempStack);
                    return NULL;
                }
                expandedFormula = newPtr; // success realloc
            }
            
            strcpy(expandedFormula + length, poppedData.elementData.chemSymbol); // "append" element
            length += symbolLen; // increase length of expandedFormula by the new symbol's length
            expandedFormula[length++] = ' '; // space in between for proper output
        }
    }

    if (length > 0 && expandedFormula[length - 1] == ' ') { // 'discard' last space character
        length--;
    }
    expandedFormula[length] = '\0'; // termination character

    free(stack);
    free(tempStack);

    return expandedFormula;
}


// Reads formulas from specified file and with the helper method calculates the expanded version
void formulaProcessor(const char *inputFile, const char *outputFile) {
    FILE *fin = fopen(inputFile, "r"); // open file for read-only
    if (fin == NULL) { // ensure proper file opening
        perror("Unable to open input file for formula expansion.");
        return;
    }

    FILE *fout = fopen(outputFile, "w"); // open file for write-only
    if (fout == NULL) { // ensure proper file opening
        perror("Unable to open output file for writing.");
        fclose(fin);
        return;
    }

    char formula[MAX_FORMULA_LENGTH];
    while (fgets(formula, sizeof(formula), fin)) {
        formula[strcspn(formula, "\n")] = '\0'; // replace newline character with terminating character
        char *expandedFormula = processFormula(formula); // calculate expanded formula
        if (expandedFormula) { // check wether the formula returned is null (error) or not and print accordingly
            fprintf(fout, "%s\n", expandedFormula);
            free(expandedFormula);
        } else {
            printf("Error processing formula: %s\n", formula);
        }
    }

    fclose(fin);
    fclose(fout);
}


// Reads and calculates total protons number of each formula in the given input file
void countProtons(const char *inputFile, const char *outputFile, Element periodicTable[]){
    char tempFile[] = "expanded.txt"; // file that we will store the expanded formulas

    FILE *fp = fopen(tempFile, "w+"); // file for read&write (created if not existant)
    if(fp == NULL){
        perror("Unable to create file to store expanded formulas");
        exit(EXIT_FAILURE);
    }

    formulaProcessor(inputFile, tempFile); // expand the formulas

    FILE *fout = fopen(outputFile, "w");
    if(fout == NULL){
        perror("Unable to open output file for count protons.");
        fclose(fp);
        exit(EXIT_FAILURE);
    }

    char formula[MAX_FORMULA_LENGTH];
    while(fgets(formula, sizeof(formula), fp)){ // read each formula 1 by 1
        const char *p = formula;
        int totalAtomicNumber = 0;
        while(*p != '\0'){ // iterate up to the end
            if (isalpha(*p)) { // if is letter
                Element element;
                element.atomicNumber = 0;

                if(isupper(*p) && islower(*(p + 1)) && islower(*(p + 2))){ // three-letter elements
                    element.chemSymbol[0] = *p;
                    element.chemSymbol[1] = *(p + 1);
                    element.chemSymbol[2] = *(p + 2);
                    element.chemSymbol[3] = '\0';
                p += 2;
                } else if (isupper(*p) && islower(*(p + 1))) { // two-letter elements
                    element.chemSymbol[0] = *p;
                    element.chemSymbol[1] = *(p + 1);
                    element.chemSymbol[2] = '\0';
                    p++;  // skip 2nd letter since we handled it above
                } else {
                    // Single-letter element
                    element.chemSymbol[0] = *p;
                    element.chemSymbol[1] = '\0';
                }

                // After constructing the element, look-up its atomic number
                element.atomicNumber = getAtomicNumber(periodicTable, MAX_ELEMENTS, element.chemSymbol);
                totalAtomicNumber += element.atomicNumber;
            }
            
            p++; // move to next character of formula
        }

        fprintf(fout, "%d\n", totalAtomicNumber); // print formula's atomic number in output file
    }

    fclose(fp);
    fclose(fout);
}


/**
 * @brief Checks if the parentheses in a given formula are balanced.
 *
 * This function iterates over the provided chemical formula string and
 * verifies if the parentheses are balanced using a stack. It pushes
 * opening parentheses '(' onto the stack and pops them when encountering
 * closing parentheses ')'. The function returns true if all parentheses
 * are balanced, otherwise it returns false.
 *
 * @param formula A null-terminated string representing a chemical formula.
 * @return true if the parentheses in the formula are balanced, false otherwise.
 */
static bool checkParentheses(const char *formula){
    UnionStack *stack = NULL;
    initUnionStack(&stack);

    bool valid = true; // initially assume that the formula is valid
    const char *p = formula; // pointer to iterate through the string

    while (*p != '\0' && valid) { // check till end or until imbalance is found
        if (*p == '(') {
            pushCharUnion(stack, *p);
        } else if (*p == ')') {
            if (!isEmptyUnion(stack)) {
                StackData poppedData;
                StackDataType poppedType;
                popUnion(stack, &poppedData, &poppedType);
                if (poppedType != CHAR_TYPE || poppedData.charData != '(') {
                    valid = false; // mismatched parentheses
                }
            } else {
                valid = false; // extra closing parentheses at end
            }
        }
        p++;
    }

    // Check for any leftover opening parentheses in the stack
    if (valid && !isEmptyUnion(stack)) {
        valid = false;
    }

    // Clean up: Clear the stack
    while (!isEmptyUnion(stack)) {
        StackData tempData;
        StackDataType tempType;
        popUnion(stack, &tempData, &tempType);
    }

    free(stack);
    return valid;
}


// Validates the balance of parentheses of the formulas contained inside the given file
bool validateParentheses(const char *inputFile) {
    FILE *fp = fopen(inputFile, "r"); // open file for reading the formulas
    if (fp == NULL) {
        perror("Error opening file for parentheses validation.");
        return EXIT_FAILURE;
    }

    char formula[MAX_FORMULA_LENGTH];
    int lineIndex = 0;
    bool overallValid = true; // assume that all formulas are balanced

    while (fgets(formula, sizeof(formula), fp) != NULL) { // read line-by-line
        lineIndex++;
        if (formula[strlen(formula) - 1] == '\n') {
            formula[strlen(formula) - 1] = '\0'; // Remove the newline character, if present
        }

        bool valid = checkParentheses(formula);

        if (!valid) { // If not valid, print the error message
            printf("Parentheses NOT balanced in line: %d\n", lineIndex);
            overallValid = false;
        }
    }

    fclose(fp);
    return overallValid; // return overall parentheses balance of file
}


#ifdef DEBUG_FEXPANDER

int main(){

    Element periodicTable[MAX_ELEMENTS];
    int numElements = loadPeriodicTable("periodicTable.txt", periodicTable);
    if(numElements == -1 || numElements == EXIT_FAILURE){
        printf("Unable to load periodic table for testing.\n");
        return EXIT_FAILURE;
    }

    // Test the validation of parentheses (helper function)
    printf("Testing parentheses validation.\n");
    const char* validFormula = "H2O";
    const char* invalidFormula = "H2(O";

    printf("Validating correct formula: %s\n", validFormula);
    if (checkParentheses(validFormula)) {
        printf("Formula is correctly balanced.\n");
    } else {
        printf("Formula should be balanced but is reported as unbalanced.\n");
    }

    printf("Validating incorrect formula: %s\n", invalidFormula);
    if (!checkParentheses(invalidFormula)) {
        printf("Correctly identified unbalanced formula.\n");
    } else {
        printf("Failed to identify unbalanced formula.\n");
    }

    /*  TO RUN validateParentheses(inputFile) USE THE CODE BELOW AND PROVDE AN INPUT FILE.

        const char* fileName = "input.txt";
        if (validateParentheses(fileName)) {
            printf("All formulas in the file '%s' are balanced.\n", fileName);
        } else {
            printf("Some formulas in the file '%s' have unbalanced parentheses. See error lines above.\n", fileName);
        }

    */


    // TESTING EXPANSION AND COUNT PROTONS FROM SPECIFIED FILE. CHANGE INPUT FILE NAME IF NEEDED!
    // Formula expansion
    printf("Testing formula expansion. Results at 'expandedDEBUG.txt'.\n");
    const char* inputFile = "expandedTest.txt";
    printf("Expanding formulas from %s file\n", inputFile);
    formulaProcessor(inputFile, "expandedDEBUG.txt");

    // Counting protons
    printf("Testing protons count. Results at 'protonsDEBUG.txt'.\n");
    printf("Counting protons in file %s\n", inputFile);
    countProtons(inputFile, "protonsDEBUG.txt", periodicTable);    

}
#endif // DEBUG_FEXPANDER