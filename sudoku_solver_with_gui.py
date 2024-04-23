import pygame
import sys

# Define colors
WHITE = (255, 255, 255)
BLACK = (0, 0, 0)
GRAY = (200, 200, 200)
GREEN = (0, 255, 0)
RED = (255, 0, 0)

# Define grid parameters
GRID_SIZE = 9
CELL_SIZE = 50
GRID_WIDTH = CELL_SIZE * GRID_SIZE
GRID_HEIGHT = CELL_SIZE * GRID_SIZE
SCREEN_SIZE = (GRID_WIDTH, GRID_HEIGHT + 100)

class SudokuGame:
    def __init__(self):
        pygame.init()
        self.screen = pygame.display.set_mode(SCREEN_SIZE)
        pygame.display.set_caption("Sudoku")
        self.clock = pygame.time.Clock()
        self.grid = [[0 for _ in range(GRID_SIZE)] for _ in range(GRID_SIZE)]
        self.selected = None
        self.running = True

    def solve_sudoku(self):
        if self.is_valid_grid():
            if self.solve():
                return True
            else:
                print("No solution exists.")
        else:
            print("Invalid Sudoku grid.")

    def is_valid_grid(self):
        for i in range(GRID_SIZE):
            for j in range(GRID_SIZE):
                if not self.is_valid_cell(i, j):
                    return False
        return True

    def is_valid_cell(self, row, col):
        num = self.grid[row][col]
        if num == 0:
            return True
        for x in range(GRID_SIZE):
            if self.grid[row][x] == num and x != col:
                return False
            if self.grid[x][col] == num and x != row:
                return False
        start_row = row - row % 3
        start_col = col - col % 3
        for i in range(3):
            for j in range(3):
                if self.grid[i + start_row][j + start_col] == num and (i + start_row, j + start_col) != (row, col):
                    return False
        return True

    def solve(self):
        empty_cell = self.find_empty_cell()
        if not empty_cell:
            return True
        row, col = empty_cell
        for num in range(1, 10):
            if self.is_safe(row, col, num):
                self.grid[row][col] = num
                if self.solve():
                    return True
                self.grid[row][col] = 0
        return False

    def find_empty_cell(self):
        for i in range(GRID_SIZE):
            for j in range(GRID_SIZE):
                if self.grid[i][j] == 0:
                    return (i, j)
        return None

    def is_safe(self, row, col, num):
        for x in range(GRID_SIZE):
            if self.grid[row][x] == num or self.grid[x][col] == num:
                return False
        start_row = row - row % 3
        start_col = col - col % 3
        for i in range(3):
            for j in range(3):
                if self.grid[i + start_row][j + start_col] == num:
                    return False
        return True

    def draw_grid(self):
        for i in range(GRID_SIZE + 1):
            if i % 3 == 0:
                thick = 4
            else:
                thick = 1
            pygame.draw.line(self.screen, BLACK, (0, i * CELL_SIZE), (GRID_WIDTH, i * CELL_SIZE), thick)
            pygame.draw.line(self.screen, BLACK, (i * CELL_SIZE, 0), (i * CELL_SIZE, GRID_HEIGHT), thick)

    def draw_numbers(self):
        font = pygame.font.SysFont(None, 40)
        for i in range(GRID_SIZE):
            for j in range(GRID_SIZE):
                if self.grid[i][j] != 0:
                    text = font.render(str(self.grid[i][j]), True, BLACK)
                    text_rect = text.get_rect(center=(j * CELL_SIZE + CELL_SIZE // 2, i * CELL_SIZE + CELL_SIZE // 2))
                    self.screen.blit(text, text_rect)

    def draw_buttons(self):
        font = pygame.font.SysFont(None, 30)

        solve_button = font.render("Solve", True, BLACK)
        solve_rect = solve_button.get_rect(center=(GRID_WIDTH // 4, GRID_HEIGHT + 50))
        pygame.draw.rect(self.screen, GRAY, solve_rect)
        self.screen.blit(solve_button, solve_rect)

        reset_button = font.render("Reset", True, BLACK)
        reset_rect = reset_button.get_rect(center=(3 * GRID_WIDTH // 4, GRID_HEIGHT + 50))
        pygame.draw.rect(self.screen, GRAY, reset_rect)
        self.screen.blit(reset_button, reset_rect)

    def handle_button_click(self, x, y):
        if GRID_WIDTH // 4 - 50 <= x <= GRID_WIDTH // 4 + 50 and GRID_HEIGHT + 25 <= y <= GRID_HEIGHT + 75:
            self.solve_sudoku()
        elif 3 * GRID_WIDTH // 4 - 50 <= x <= 3 * GRID_WIDTH // 4 + 50 and GRID_HEIGHT + 25 <= y <= GRID_HEIGHT + 75:
            self.grid = [[0 for _ in range(GRID_SIZE)] for _ in range(GRID_SIZE)]

    def handle_key_press(self, event):
        if self.selected:
            if event.key == pygame.K_BACKSPACE:
                self.grid[self.selected[0]][self.selected[1]] = 0
            elif event.key in range(pygame.K_1, pygame.K_9 + 1):
                num = int(pygame.key.name(event.key))
                if self.is_safe(self.selected[0], self.selected[1], num):
                    self.grid[self.selected[0]][self.selected[1]] = num
            elif event.key == pygame.K_UP and self.selected[0] > 0:
                self.selected = (self.selected[0] - 1, self.selected[1])
            elif event.key == pygame.K_DOWN and self.selected[0] < GRID_SIZE - 1:
                self.selected = (self.selected[0] + 1, self.selected[1])
            elif event.key == pygame.K_LEFT and self.selected[1] > 0:
                self.selected = (self.selected[0], self.selected[1] - 1)
            elif event.key == pygame.K_RIGHT and self.selected[1] < GRID_SIZE - 1:
                self.selected = (self.selected[0], self.selected[1] + 1)

    def run(self):
        while self.running:
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    self.running = False
                elif event.type == pygame.MOUSEBUTTONDOWN:
                    x, y = pygame.mouse.get_pos()
                    if y >= GRID_HEIGHT:
                        self.handle_button_click(x, y)
                    else:
                        row = y // CELL_SIZE
                        col = x // CELL_SIZE
                        self.selected = (row, col)
                        print("Selected cell:", self.selected)
                elif event.type == pygame.KEYDOWN:
                    self.handle_key_press(event)

            self.screen.fill(WHITE)
            self.draw_grid()
            self.draw_numbers()
            self.draw_buttons()
            if self.selected:
                pygame.draw.rect(self.screen, GREEN, (self.selected[1] * CELL_SIZE, self.selected[0] * CELL_SIZE, CELL_SIZE, CELL_SIZE), 3)
            pygame.display.flip()
            self.clock.tick(10)  # Limit screen updates to 10 frames per second
        pygame.quit()

def main():
    game = SudokuGame()
    game.run()

if __name__ == "__main__":
    main()
