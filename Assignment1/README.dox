/**

@mainpage Latin Square Game Project

@brief A console-based implementation of a Latin Square puzzle game.

@author Panagiotis Tsembekis

This program implements a Latin Square puzzle game where players can input values into a pre-populated square, trying to fill in the remaining cells while adhering to the Latin Square rules. 
The Latin Square rules require that each row and each column contain unique numbers between 1 and `size` (where `size` is the dimension of the square). 

### General Overview
- The Latin Square is read from a text file provided as a command-line argument.
- The input file specifies the size of the square and the initial values for some of its cells.
- Pre-given cells are displayed in parentheses and cannot be modified by the user.
- The user enters number in the tableau until the game is finished or when he wishes to exit the game.

### How to Play
- Run the code by entering `./latinsquare {filename}`.
  - `{filename}` should be a file that should have the following structure:
    - **First Line:** integer number [1, 9] that indicates the size of the tableau (n * n tableau)
    - **Second Line and Below:** Tableau contents represented by `size` negative numbers, separated by a whitespace character (one row). Enter multiple rows by repeating the same procedure on the next line. 
- The user is prompted to enter commands in the format: `i,j=val` where `i` is the row number, `j` is the column number, and `val` is the value to be placed at position `(i, j)`.
  - To clear a cell, the command `i,j=0` can be used.
  - To exit the game and save the current state, the command `0,0=0` should be used.
- The game validates the input values to ensure they do not violate the Latin Square rules:
  - No value should appear more than once in a row or column.
  - Each value should be between 1 and `size`.
  - Each value should appear maximum `size` times on the whole tableau.
  - Pre-given values cannot be modified.

### Program Structure
The program consists of the following main functions:
1. **readLatinSquare**: Reads the Latin Square values from the input file and checks for invalid configurations.
2. **writeLatinSquare**: Writes the current state of the Latin Square to an output file.
3. **displayLatinSquare**: Displays the current state of the Latin Square on the console with visual formatting.
4. **checkUserInput**: Checks the validity of the user’s input (i.e., whether the value placement is allowed).
5. **getUserInput**: Prompts the user to enter a move and handles any formatting issues.
6. **play**: The main game loop that repeatedly accepts and executes user input until the game is completed.

### Key Design Decisions
- **Data Structure**: The Latin Square is represented as a 2D array of shorts (`short square[N][N]`), where each element stores a number from `1` to `size` or `0` for empty cells. Negative values represent pre-given cells that cannot be modified.
- **Input Validation**: The program validates every input to ensure no rules are violated before allowing a move. This includes checking for duplicate values in rows/columns and bounds checking.
- **File Handling**: When the game ends, the state of the Latin Square is saved to a new file named `out-<filename>` to prevent overwriting the original input file.

### Stability and Bugs
- **Stability**: The program is generally stable with proper user input handling and checks for boundary conditions. The game loop continues to run until the user completes the puzzle or exits manually.
- **Known Limitations**: 
  - The program does not check if the initial Latin Square provided in the input file adheres to the Latin Square rules. Specifically, it does not validate:
    - That all values in the tableau are between 0 and `size`.
    - That no number appears more than once in any row or column.
    - That each number appears no more than `size` times across the entire tableau.
- **Bugs**: 
  - No known bugs. (6/10/24)
  

**/