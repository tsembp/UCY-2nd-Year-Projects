/**
 * @file periodicTable.c
 * @brief Provides implementations for managing and accessing periodic table data.
 *
 * Implements functions to load a periodic table from a file, sort it by atomic number,
 * and retrieve the atomic number of an element given its chemical symbol.
 * 
 * @author  Panagiotis Tsembekis
 * @bug     No known bugs.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "periodicTable.h"


// Load the periodic table's elements from specified file
int loadPeriodicTable(const char *filename, Element elements[]) {
    FILE *file = fopen(filename, "r"); // open file to read elements
    if (file == NULL) {
        perror("Unable to open file to read periodic table elements.");
        return EXIT_FAILURE;
    }

    char symbol[4];
    int atomicNumber, index = 0;

    while (index < MAX_ELEMENTS && fscanf(file, "%3s %d", symbol, &atomicNumber) == 2) { // read element symbol & atomic number
        symbol[sizeof(symbol) - 1] = '\0';  // termination character
        if (strlen(symbol) > 3) { // handle invalid elements
            fprintf(stderr, "Error: Chemical symbol '%s' exceeds maximum length.\n", symbol);
            continue;  // skip this
        }

        // Construct element that will be stored in elements[index]
        strncpy(elements[index].chemSymbol, symbol, sizeof(elements[index].chemSymbol) - 1); // element name = symbol read
        elements[index].chemSymbol[sizeof(elements[index].chemSymbol) - 1] = '\0';  // termination character
        elements[index].atomicNumber = atomicNumber; // assign atomic number
        index++;
    }

    fclose(file);
    return index; // return index to keep track in parseFormula.c of how many elements we've read
}


// Sort the periodic table in ascending order based on atomic number
void sortPeriodicTable(Element elements[], int numElements) {
    int i, j;
    Element temp;

    for (i = 0; i < numElements - 1; i++) {
        for (j = 0; j < numElements - i - 1; j++) {
            if (elements[j].atomicNumber > elements[j + 1].atomicNumber) { // sort in ascending order
                // Swap element[i] with element[i + 1]
                temp = elements[j];
                elements[j] = elements[j + 1];
                elements[j + 1] = temp;
            }
        }
    }
}


// Retrieve the atomic number of given symbol
int getAtomicNumber(Element elements[], int n, const char *symbol) {
    for (int i = 0; i < n; i++) { // iterate elements table to find the requested symbol
        if (strcmp(elements[i].chemSymbol, symbol) == 0) { // if a match is found return its atomic number
            return elements[i].atomicNumber;
        }
    }

    return -1;  // return -1 if element not found
}


#ifdef DEBUG_PERIODICTABLE

int main() {
    Element elements[MAX_ELEMENTS];
    int numElements;

    // Load the periodic table from the given "periodicTable.txt" file
    numElements = loadPeriodicTable("periodicTable.txt", elements);
    if (numElements == -1) {
        printf("Failed to load periodic table.\n");
        return EXIT_FAILURE;
    }

    printf("Loaded %d elements.\n", numElements);

    // Sort the periodic table
    sortPeriodicTable(elements, numElements);
    printf("Elements sorted by atomic number.\n");

    // Print sorted elements
    printf("%-5s | %-15s\n", "Symbol", "Atomic Number");  // Header
    printf("------------------------------\n");
    for (int i = 0; i < numElements; i++) {
        printf("%-6s | %15d\n", elements[i].chemSymbol, elements[i].atomicNumber);
    }

    // Test retrieval of atomic numbers
    const char* testSymbols[] = {"H", "Db", "Uus", "None"};
    for (int i = 0; i < sizeof(testSymbols)/sizeof(testSymbols[0]); i++) {
        int atomicNumber = getAtomicNumber(elements, numElements, testSymbols[i]);
        if (atomicNumber != -1) {
            printf("Atomic number of %s: %d\n", testSymbols[i], atomicNumber);
        } else {
            printf("'%s' not found in the periodic table.\n", testSymbols[i]);
        }
    }

    return 0;
}
#endif // DEBUG_PERIODICTABLE