/**
 * @file periodicTable.h
 * @brief Header file for handling operations related to the periodic table of elements.
 * 
 * This file contains definitions and function declarations for working with elements
 * of the periodic table. The periodic table is represented by an array of Element structs, 
 * where each struct stores the chemical symbol and atomic number of an element.
 * 
 * The file includes functions to load elements from a file, sort them, and retrieve 
 * an atomic number based on a chemical symbol.
 * 
 * @author  Panagiotis Tsembekis
 * @bug     No known bugs.
 */

#ifndef PERIODIC_TABLE_H
#define PERIODIC_TABLE_H

#define MAX_ELEMENTS 118 /**< Maximum number of elements in the periodic table */


/**
 * @struct Element
 * @brief A structure representing an element in the periodic table.
 * 
 * This structure holds information about an element from the periodic table,
 * including its chemical symbol and atomic number.
 * 
 * @var Element::chemSymbol
 * The chemical symbol of the element, represented as a string of up to 3 characters + 1 for '\0'
 * 
 * @var Element::atomicNumber
 * The atomic number of the element.
 */
typedef struct {
    char chemSymbol[4];
    int atomicNumber;
} Element;


/**
 * @brief Loads the periodic table from a file.
 * 
 * This function reads element data (chemical symbol and atomic number) from a specified file
 * and loads it into an array of Element structs.
 * 
 * @param[in] filename The name of the file containing element data.
 * @param[out] elements An array to store the loaded elements.
 * @return int The number of elements successfully loaded, or 'EXIT_FAILURE' if the file could not be opened.
 */
int loadPeriodicTable(const char *filename, Element elements[]);


/**
 * @brief Sorts the periodic table by atomic number.
 * 
 * This function sorts an array of Element structs in ascending order based on their atomic numbers,
 * using the bubble sort algorithm.
 * 
 * @param[in,out] elements An array of elements to be sorted.
 * @param[in] numElements The number of elements in the array.
 */
void sortPeriodicTable(Element elements[], int numElements);


/**
 * @brief Retrieves the atomic number of an element based on its chemical symbol.
 * 
 * This function searches an array of Element structs for an element with the specified chemical symbol
 * and returns its atomic number.
 * 
 * @param[in] elements The array of elements to search through.
 * @param[in] n The number of elements in the array.
 * @param[in] symbol The chemical symbol to search for.
 * @return int The atomic number of the element, or -1 if the symbol was not found.
 */
int getAtomicNumber(Element elements[], int n, const char *symbol);

#endif // PERIODIC_TABLE_H