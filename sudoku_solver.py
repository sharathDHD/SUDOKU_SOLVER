def is_safe(grid, row, col, num):
    """
    Check if it's safe to place 'num' in the given position (row, col) of the Sudoku grid.
    """
    # Check if 'num' is not already placed in the current row
    for x in range(9):
        if grid[row][x] == num:
            return False
    
    # Check if 'num' is not already placed in the current column
    for x in range(9):
        if grid[x][col] == num:
            return False
    
    # Check if 'num' is not already placed in the current 3x3 box
    start_row = row - row % 3
    start_col = col - col % 3
    for i in range(3):
        for j in range(3):
            if grid[i + start_row][j + start_col] == num:
                return False
    return True

def solve_sudoku(grid, row=0, col=0):
    """
    Recursively solve the Sudoku puzzle using backtracking.
    """
    # If we have reached the end of the grid, the puzzle is solved
    if row == 8 and col == 9:
        return True
    
    # Move to the next row if we have reached the end of the current row
    if col == 9:
        row += 1
        col = 0
    
    # If the current cell is already filled, move to the next cell
    if grid[row][col] > 0:
        return solve_sudoku(grid, row, col + 1)
    
    # Try placing numbers from 1 to 9 in the current cell
    for num in range(1, 10):
        if is_safe(grid, row, col, num):
            grid[row][col] = num
            if solve_sudoku(grid, row, col + 1):
                return True
        grid[row][col] = 0  # Backtrack if the current placement is not valid
    return False

def print_solution(grid):
    """
    Print the solved Sudoku grid.
    """
    for row in grid:
        print(*row)

def main():
    # Example Sudoku puzzle
    grid = [[5, 3, 0, 0, 7, 0, 0, 0, 0],
            [6, 0, 0, 1, 9, 5, 0, 0, 0],
            [0, 9, 8, 0, 0, 0, 0, 6, 0],
            [8, 0, 0, 0, 6, 0, 0, 0, 3],
            [4, 0, 0, 8, 0, 3, 0, 0, 1],
            [7, 0, 0, 0, 2, 0, 0, 0, 6],
            [0, 6, 0, 0, 0, 0, 2, 8, 0],
            [0, 0, 0, 4, 1, 9, 0, 0, 5],
            [0, 0, 0, 0, 8, 0, 0, 7, 9]]
    
    # Solve the Sudoku puzzle
    if solve_sudoku(grid):
        print_solution(grid)
    else:
        print("No solution exists.")

if __name__ == "__main__":
    main()
