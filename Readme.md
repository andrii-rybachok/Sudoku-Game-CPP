# Sudoku console game C++

## How to Play  
### Starting the Game  
1. **Compile the Program:**  
   Use the provided Makefile to compile the game:  
   ```sh
   make
   ```  
2. **Run the Game:**  
   ```sh
   ./sudoku
   ```  
   By default, this starts a **9x9 interactive Sudoku game**.  

### Gameplay Instructions  
- **Filling a Cell:**  
  Enter the column number, row number, and the value you want to place (all 1-based).  
  Example inputs:  
  ```
  3 5 7
  4,2,9
  ```  
  (Any non-integer separator can be used.)  

- **Solving the Puzzle:**  
  At any time, type:  
  ```
  Solve
  ```  

---

## Command-Line Options  
The game can be customized using the following flags:  

| Flag | Description | Example |
|------|------------|---------|
| `-s, --seed` | Set a random seed to replicate results | `./sudoku -s 123` |
| `-u, --unittest` | Run unit tests (speed test with both solvers). Specify the number of iterations. | `./sudoku -u 1000` |
| `-g, --gamesize` | Set the board size (e.g., 9 for 9x9, 16 for 16x16) | `./sudoku -g 16` |
| `-n, --nobs` | Specify the number of pre-filled (immutable) values in the board | `./sudoku -n 30` |
| `-v, --verbose` | Enable verbose output after each unit test (not applicable in interactive mode) | `./sudoku -v` |
