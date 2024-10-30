@mainpage

# 🧬 Managing Chemical Formulas with Dynamic Structures

## 📝 Overview
This project processes chemical formulas, expanding them into full molecular representations, validating parentheses, and calculating the total number of protons for each formula based on atomic numbers from the periodic table. Dynamic stacks are used to efficiently manage elements and parentheses while parsing the formulas.

**Author:** Panagiotis Tsembekis


## Introduction
As part of the EPL232 course, Assignment 2 focuses on:
- Expanding chemical formulas into their full molecular form.
- Validating the correctness of parentheses in these formulas.
- Calculating the total number of protons for each expanded formula.

The program supports:
- Nested parentheses.
- Multi-digit multipliers.
- Both single- and multi-letter chemical element symbols.

## Project Structure
The project is organized into the following files:

- **formulaExpander.c**: Expands formulas, validates parentheses, and calculates protons.
- **formulaExpander.h**: Header file for `formulaExpander.c`.
- **parseFormula.c**: Main driver program for formula processing.
- **periodicTable.c**: Manages loading the periodic table and retrieving atomic numbers.
- **periodicTable.h**: Header file for `periodicTable.c`.
- **unionStack.c**: Implements a union stack structure to handle element symbols and characters.
- **unionStack.h**: Header file for `unionStack.c`.

## Usage Instructions
### Compilation
Use the provided makefile to compile all source files:
```bash
make
```

### Execution
The program supports three modes of operation based on command-line arguments:

- **Parentheses Validation** (`-v`):
  Validates if all parentheses are correctly balanced.
  ```bash
  ./parseFormula periodicTable.txt -v input.txt
  ```

- **Formula Expansion** (`-ext`):
  Expands formulas from the input file and writes to the output file.
  ```bash
  ./parseFormula periodicTable.txt -ext input.txt expanded_output.txt
  ```

- **Proton Calculation** (`-pn`):
  Calculates the total protons for each formula and writes results to the output file.
  ```bash
  ./parseFormula periodicTable.txt -pn input.txt proton_output.txt
  ```

## Debugging
Each `.c` file includes a `DEBUG` block for component testing:

### Debugging formulaExpander.c
```bash
gcc -DDEBUG_FEXPANDER -o formulaExpanderTest formulaExpander.c unionStack.c periodicTable.c
./formulaExpanderTest
```

### Debugging periodicTable.c
```bash
gcc -DDEBUG_PERIODICTABLE -o periodicTableTest periodicTable.c
./periodicTableTest
```

### Debugging unionStack.c
```bash
gcc -DDEBUG_USTACK -o unionStackTest unionStack.c
./unionStackTest
```

## Dependencies
The program requires the following files:
- **periodicTable.txt**: Contains periodic table data with element symbols and atomic numbers.
  ```text
  Eu	63
  Cs	55
  Cn	112
  ```
- **input.txt**: A file with chemical formulas for processing.
- **output.txt**: A file where expanded formulas or proton calculations are stored.

## Examples
Suppose `input.txt` contains:
```text
H2O
KBr
Co3(Fe(CN)6)2
```

- **Parentheses Validation**:
  ```bash
  ./parseFormula periodicTable.txt -v input.txt
  ```
  Output:
  ```text
  Parentheses are balanced for all chemical formulas.
  ```

- **Formula Expansion**:
  ```bash
  ./parseFormula periodicTable.txt -ext input.txt expanded_output.txt
  ```
  Output in `expanded_output.txt`:
  ```text
  H H O
  Co Co Co Fe C N C N C N C N C N C N Fe C N C N C N C N C N C N
  K Br
  ```

- **Proton Calculation**:
  ```bash
  ./parseFormula periodicTable.txt -pn input.txt proton_output.txt
  ```
  Output in `proton_output.txt`:
  ```text
  10
  289
  54
  ```

## Memory Management
The program is designed for efficient memory use, with no memory leaks or undefined behavior. Use Valgrind to check for memory issues:
```bash
valgrind ./parseFormula periodicTable.txt -v input.txt
valgrind ./parseFormula periodicTable.txt -ext input.txt expanded_output.txt
valgrind ./parseFormula periodicTable.txt -pn input.txt proton_output.txt
```

## Conclusion
This project showcases efficient use of dynamic data structures to handle complex nested expressions like chemical formulas, supporting parentheses balancing, formula expansion, and proton calculations based on periodic table data. Memory management is ensured through dynamic allocation and deallocation.
