/**
 * @file formulaExpander.h
 * @brief Header file for formula expansion, calculating protons and validating parentheses.
 *
 * This file contains the declarations of the functions used for processing
 * chemical formulas, counting protons, and validating parentheses in input files.
 * It includes the necessary definitions from `periodicTable.h` and `unionStack.h`.
 * 
 * @author  Panagiotis Tsembekis
 * @bug     No known bugs.
 */

#ifndef FORMULA_EXPANDER
#define FORMULA_EXPANDER
#include <stdbool.h>
#include "periodicTable.h"
#include "unionStack.h"


/**
 * @brief Processes chemical formulas from a file and writes the expanded formulas to another file.
 * 
 * This function reads chemical formulas from a specified input file, expands them,
 * and writes the expanded formulas to a specified output file. The expansion process
 * involves replacing compact chemical notation with the full repeated elements.
 *
 * @param inputFile The name of the input file containing original compact formulas.
 * @param outputFile The name of the output file where expanded formulas will be written.
 */
void formulaProcessor(const char *inputFile, const char *outputFile);


/**
 * @brief Counts the total number of protons in the chemical formulas found in a file.
 * 
 * This function reads expanded chemical formulas from a file and uses the provided
 * periodic table to count the total number of protons for each formula. The result
 * is written to the output file provided.
 *
 * @param inputFile The name of the input file containing the chemical formulas (not expanded).
 * @param outputFile The name of the output file where the proton counts will be written.
 * @param periodicTable An array of `Element` structures representing the periodic table,
 *                      used to look up atomic numbers.
 */
void countProtons(const char *inputFile, const char *outputfile, Element periodicTable[]);


/**
 * @brief Validates the balance of parentheses in each formula from a file.
 *
 * This function opens a file, reads each line as a formula, and checks whether
 * the parentheses in the formula are balanced by calling `checkParentheses`.
 * If an imbalance is found, it prints an error message indicating the line number.
 * The function returns true if all formulas in the file are balanced, and false otherwise.
 *
 * @param inputFile The name of the input file.
 * @return true if all formulas in the file have balanced parentheses, false otherwise.
 */
bool validateParentheses(const char *inputFile);

#endif // FORMULA_EXPANDER