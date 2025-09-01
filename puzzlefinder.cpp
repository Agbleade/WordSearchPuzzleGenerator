// Name: Alex Agbleade
// ID: 800812955


#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>

typedef std::vector<std::vector<char>> Grid;

// Direction for word placement
struct Direction {
    int dx, dy;
};

// Read words from the input file
std::vector<std::string> readWordsFromFile(const std::string& filename) {
    std::vector<std::string> words;
    std::ifstream file(filename);
    
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return words;
    }
    
    std::string word;
    while (std::getline(file, word) && words.size() < 10) {
        words.push_back(word);
    }
    
    file.close();
    return words;
}

// Create an empty grid filled with spaces
Grid createEmptyGrid(int size) {
    return Grid(size, std::vector<char>(size, ' '));
}

// Get all possible directions for word placement
std::vector<Direction> getDirections() {
    return {
        {0, 1},   // Right
        {1, 0},   // Down
        {0, -1},  // Left
        {-1, 0},  // Up
        {1, 1},   // Down-Right
        {-1, -1}, // Up-Left
        {1, -1},  // Down-Left
        {-1, 1}   // Up-Right
    };
}

// Check if a word fits in the grid at the given position and direction
bool wordFits(const Grid& grid, const std::string& word, 
              int row, int col, const Direction& dir) {
    int gridSize = grid.size();
    
    // Check if the word would go out of bounds
    if (row + (word.length() - 1) * dir.dx < 0 || 
        row + (word.length() - 1) * dir.dx >= gridSize ||
        col + (word.length() - 1) * dir.dy < 0 || 
        col + (word.length() - 1) * dir.dy >= gridSize) {
        return false;
    }
    
    // Check if the word would overlap with existing letters
    for (size_t i = 0; i < word.length(); i++) {
        int newRow = row + i * dir.dx;
        int newCol = col + i * dir.dy;
        
        // If cell isn't empty and doesn't match the word letter, word doesn't fit
        if (grid[newRow][newCol] != ' ' && grid[newRow][newCol] != word[i]) {
            return false;
        }
    }
    
    return true;
}

// Try to place a word in the grid
bool placeWord(Grid& grid, const std::string& word) {
    int gridSize = grid.size();
    auto directions = getDirections();
    
    // Try placing the word multiple times
    for (int attempt = 0; attempt < 100; attempt++) {
        // Pick a random starting position
        int row = rand() % gridSize;
        int col = rand() % gridSize;
        
        // Pick a random direction
        Direction dir = directions[rand() % directions.size()];
        
        // Check if the word fits at this position and direction
        if (wordFits(grid, word, row, col, dir)) {
            // Place the word
            for (size_t i = 0; i < word.length(); i++) {
                grid[row + i * dir.dx][col + i * dir.dy] = word[i];
            }
            return true;
        }
    }
    
    // If we couldn't place the word after multiple attempts
    return false;
}

// Place all words in the grid
Grid placeWordsInGrid(const std::vector<std::string>& words) {
    Grid grid = createEmptyGrid(10);
    
    for (const auto& word : words) {
        bool placed = placeWord(grid, word);
        if (!placed) {
            std::cerr << "Warning: Could not place word: " << word << std::endl;
        }
    }
    
    return grid;
}

// Fill empty spaces with random capital letters
Grid fillEmptySpaces(const Grid& wordsOnlyGrid) {
    Grid filledGrid = wordsOnlyGrid;
    int gridSize = filledGrid.size();
    
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridSize; j++) {
            if (filledGrid[i][j] == ' ') {
                // Generate a random capital letter (ASCII 65-90)
                filledGrid[i][j] = 'A' + (rand() % 26);
            }
        }
    }
    
    return filledGrid;
}

// Print the puzzle grid and word list
void printPuzzle(const Grid& grid, const std::vector<std::string>& words) {
    std::cout << "Today's Puzzle:" << std::endl;
    
    for (const auto& row : grid) {
        for (char cell : row) {
            std::cout << cell << " "; // Add an extra space as required
        }
        std::cout << std::endl;
    }
    
    std::cout << "----------" << std::endl;
    
    // Print the word list
    for (const auto& word : words) {
        std::cout << word << std::endl;
    }
}

int main() {
    // Seed the random number generator
    srand(static_cast<unsigned>(time(NULL)));
    
    // Read words from file
    std::vector<std::string> words = readWordsFromFile("PuzzleWords.txt");
    
    if (words.empty()) {
        std::cerr << "No words were read from the file." << std::endl;
        return 1;
    }
    
    // Place words in the grid
    Grid wordsOnlyGrid = placeWordsInGrid(words);
    
    // Print the puzzle with only words
    std::cout << "Puzzle with only words:" << std::endl;
    printPuzzle(wordsOnlyGrid, words);
    std::cout << std::endl;
    
    // Fill empty spaces with random letters
    Grid completePuzzle = fillEmptySpaces(wordsOnlyGrid);
    
    // Print the complete puzzle
    std::cout << "Complete puzzle:" << std::endl;
    printPuzzle(completePuzzle, words);
    
    return 0;
}