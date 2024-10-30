/**
 * @file parseFormula.c
 * @brief Main entry point for the formula processing application.
 * @author Panagiotis Tsembekis
 *
 * This program processes chemical formulas based on input arguments. It supports validating 
 * parentheses in formulas, expanding formulas, and counting protons in chemical formulas using
 * data from a periodic table.
 * 
 * Usage:
 * - ./parseFormula periodicTable.txt -v <input.txt>
 *   Validates balanced parentheses in the specified input file.
 * - ./parseFormula periodicTable.txt -ext <input.txt> <output.txt>
 *   Expands the formulas from the input file and writes them to the output file.
 * - ./parseFormula periodicTable.txt -pn <input.txt> <output.txt>
 *   Calculates and writes the total number of protons for each formula from the input file to the output file.
 */

#include "formulaExpander.h"
#include "periodicTable.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/**
 * @brief Main function which processes command line arguments and invokes appropriate functionality.
 *
 * @param argc The number of command line arguments.
 * @param argv The array of command line arguments.
 * @return int Returns 0 on successful execution and 1 on error.
 */
int main(int argc, char *argv[]) {
    
    if(argc != 4 && argc != 5){ // check for invalid arguments  
        printf("Usage:\n");
        printf("./parseFormula periodicTable.txt -v <input.txt>\n");
        printf("./parseFormula periodicTable.txt -ext <input.txt> <output.txt>\n");
        printf("./parseFormula periodicTable.txt -pn <input.txt> <output.txt>\n");
        return 1;
    }

    Element periodicTable[MAX_ELEMENTS];

    int numElements = loadPeriodicTable(argv[1], periodicTable);
    if (numElements == EXIT_FAILURE) {
        printf("Failed to load periodic table.\n");
        return 1;
    }

    sortPeriodicTable(periodicTable, numElements);

    if(strcmp(argv[2], "-v") == 0){ // Parentheses Validate
        if(argc != 4){
            printf("Usage: ./parseFormula periodicTable.txt -v <input.txt>\n");
            return 1;
        }
        
        const char *inputFile = argv[3];
        printf("Verify balanced parentheses in %s\n", inputFile);

        if(validateParentheses(inputFile)){
            printf("Parentheses are balanced for all chemical formulas.\n");
        } else{
            // function validateParentheses will print the appropriate unbalanced lines if exists
        }
   
    } else if(strcmp(argv[2], "-ext") == 0){ // Expand Formulas
        if(argc != 5){
            printf("Usage: ./parseFormula periodicTable.txt -ext <input.txt> <output.txt>\n");
            return 1;
        }

        const char *inputFile = argv[3];
        if(!validateParentheses(inputFile)){ // check parentheses before expansion
            printf("Imbalanced parentheses in file %s. Cannot proceed with formula expansion.\n", inputFile);
            return 1;
        }

        const char *outputFile = argv[4];
        printf("Compute extended version of formulas in %s\n", inputFile);
        formulaProcessor(inputFile, outputFile);
        printf("Writing formulas to %s\n", outputFile);
    } else if(strcmp(argv[2], "-pn") == 0){ // Calculate Total Protons Number
        if(argc != 5){
            printf("./parseFormula periodicTable.txt -pn <input.txt> <output.txt>\n");
            return 1;
        }

        const char *inputFile = argv[3];
        if(!validateParentheses(inputFile)){ // check parentheses before protons count
            printf("Imbalanced parentheses in file %s. Cannot proceed with calculating protons.\n", inputFile);
            return 1;
        }

        const char *outputFile = argv[4];
        printf("Compute total proton number of formulas in %s\n", inputFile);
        countProtons(inputFile, outputFile, periodicTable);
        printf("Writing formulas to %s\n", outputFile);

    } else{
        printf("Usage:\n");
        printf("./parseFormula periodicTable.txt -v <input.txt>\n");
        printf("./parseFormula periodicTable.txt -ext <input.txt> <output.txt>\n");
        printf("./parseFormula periodicTable.txt -pn <input.txt> <output.txt>\n");
        return 1;
    }

    return 0;
}
