
# Latin Square Game Project

**Author**: Panagiotis Tsembekis  
**Description**: A console-based Latin Square puzzle game.

---

## Overview

This program allows players to solve a Latin Square puzzle, adhering to the rules that each row and column must contain unique numbers from 1 to `size`, where `size` is the square's dimension.

### Features
- **Input File**: The Latin Square is loaded from a text file specified as a command-line argument.
- **Initial Values**: Some cells may contain pre-defined values (displayed in parentheses) that cannot be modified.
- **Game Controls**: Players fill in the remaining cells while following Latin Square rules.

---

## How to Play

1. **Run the Program**:  
   ```bash
   ./latinsquare {filename}
   ```
   - `{filename}` should be a structured text file:
     - **First Line**: Integer from 1 to 9 representing the square size.
     - **Subsequent Lines**: Rows of numbers (one row per line) separated by spaces. Negative values represent pre-set cells.

2. **Enter Moves**:  
   Use the format `i,j=val`:
   - `i`: Row number
   - `j`: Column number
   - `val`: Value to place
   - To clear a cell: `i,j=0`
   - To exit and save: `0,0=0`

3. **Rules**:
   - No duplicate values in any row or column.
   - Values must be between 1 and `size`.
   - Pre-set values cannot be changed.

---

## Program Structure

- **`readLatinSquare`**: Loads the Latin Square from the input file and checks validity.
- **`writeLatinSquare`**: Saves the game state to an output file.
- **`displayLatinSquare`**: Visually formats and displays the square in the console.
- **`checkUserInput`**: Validates player input.
- **`getUserInput`**: Prompts for moves and manages formatting.
- **`play`**: Main loop that processes moves until completion or exit.

---

## Design Decisions

- **Data Structure**: The Latin Square is a 2D array `short square[N][N]`, where:
  - Positive values (1 to `size`) are modifiable.
  - Negative values indicate fixed cells.
- **Validation**: Each move is checked for compliance with game rules.
- **File Handling**: Saves the game to `out-<filename>` on exit.

---

## Known Limitations and Bugs

- **Initial File Validations**:
  - The program does not validate if the input file initially follows Latin Square rules.
- **Known Bugs**:
  - No known bugs as of 10/06/2024.
