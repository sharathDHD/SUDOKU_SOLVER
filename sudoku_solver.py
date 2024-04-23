def is_valid_grid(grid):
    """
    Check if the Sudoku grid is valid.
    """
    if len(grid) != 9:
        return False
    for row in grid:
        if len(row) != 9:
            return False
        for cell in row:
            if not isinstance(cell, int) or not 0 <= cell <= 9:
                return False
    return True

def is_safe(grid, row, col, num):
    """
    Check if it's safe to place 'num' in the given position (row, col) of the Sudoku grid.
    """
    for x in range(9):
        if grid[row][x] == num or grid[x][col] == num:
            return False
    
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
    if not is_valid_grid(grid):
        raise ValueError("Invalid Sudoku grid")
    
    if row == 8 and col == 9:
        return True
    
    if col == 9:
        row += 1
        col = 0
    
    if grid[row][col] > 0:
        return solve_sudoku(grid, row, col + 1)
    
    for num in range(1, 10):
        if is_safe(grid, row, col, num):
            grid[row][col] = num
            if solve_sudoku(grid, row, col + 1):
                return True
        grid[row][col] = 0
    return False

def print_solution(grid):
    """
    Print the solved Sudoku grid.
    """
    for row in grid:
        print(*row)

def main():
    grid = [[5, 3, 0, 0, 0, 0, 0, 0, 0],
            [6, 0, 0, 1, 9, 5, 0, 0, 0],
            [0, 9, 8, 0, 0, 0, 0, 6, 0],
            [8, 0, 0, 0, 6, 0, 0, 0, 3],
            [4, 0, 0, 8, 0, 3, 0, 0, 1],
            [7, 0, 0, 0, 2, 0, 0, 0, 6],
            [0, 6, 0, 0, 0, 0, 2, 8, 0],
            [0, 0, 0, 4, 1, 9, 0, 0, 5],
            [0, 0, 0, 0, 8, 0, 0, 0, 0]]
    
    try:
        if solve_sudoku(grid):
            print_solution(grid)
        else:
            print("No solution exists.")
    except ValueError as e:
        print("Error:", e)

if __name__ == "__main__":
    main()
