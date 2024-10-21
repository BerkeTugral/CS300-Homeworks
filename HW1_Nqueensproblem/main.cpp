#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "stack.cpp"

using namespace std;

// Struct to represent the state (current row and next column to try)
struct State {
    
    int row;
    int nextCol;
};

// Function prototypes to make it more tidy
void saveSolutionsToFile(const vector<vector<int>>& solutions, int N);
void updateSafeMatrix(vector<vector<int>>& safeMatrix, int row, int col, int changer, int N);

// Main
int main() {
    
    int N;
    cout << "Enter the value of N for the N-Queens problem: ";
    cin >> N;

    if (N <= 0) {
        cout << "Invalid input. Please enter a positive integer.\n";
        return 1;
    }

    // Initialize the stack, safe matrix, and solutions
    Stack<State> stack;
    vector<vector<int>> safeMatrix(N, vector<int>(N, 0));  // Safe matrix for marking attacked cells
    vector<vector<int>> solutions;  // Store all valid solutions
    vector<int> currentSolution(N, -1);  // Track queen positions for each row (-1 indicates no queen)

    // Start with the first row, trying column 0
    stack.push({0, 0});
    
    // Backtracking algorithm
    while (!stack.isEmpty()) {
        State current = stack.topAndPop();  // Pop the top state
        int row = current.row;
        int col = current.nextCol;

        // Remove any previously placed queen in this row (if any)
        if (currentSolution[row] != -1) {
            int prevCol = currentSolution[row];
            updateSafeMatrix(safeMatrix, row, prevCol, -1, N);  // Unmark attacked cells
            currentSolution[row] = -1;  // Remove the queen from current solution
        }

        bool placed = false;
        // Try placing the queen in columns starting from 'col'
        for (int c = col; c < N; ++c) {
            if (safeMatrix[row][c] == 0) {  // If the position is safe
                currentSolution[row] = c;  // Place the queen
                updateSafeMatrix(safeMatrix, row, c, 1, N);  // Mark attacked cells

                if (row == N - 1) {

                    solutions.push_back(currentSolution);

                    // Prepare to backtrack: remove the queen and try next column
                    updateSafeMatrix(safeMatrix, row, c, -1, N);  // Unmark attacked cells
                    currentSolution[row] = -1;  // Remove the queen
                    continue;  // Continue to try next column in this row
                } else {
                    // Push the next state in this row with next column to try
                    stack.push({row, c + 1});
                    // Proceed to the next row
                    stack.push({row + 1, 0});

                    placed = true;
                    break;  // Break and move to the next row
                }
            }
        }

        if (!placed) {
            // If no queen was placed in this row, backtrack to previous row
        }
    }

    // Save all solutions to the file
    saveSolutionsToFile(solutions, N);

    return 0;
}

// Function to save solutions to a text file
void saveSolutionsToFile(const vector<vector<int>>& solutions, int N) {
    string fileName = to_string(N) + "queens_solutions.txt";
    ofstream outFile(fileName);

    outFile << "Total solutions for N=" << N << ": " << solutions.size() << "\n\n";

    for (int i = 0; i < solutions.size(); ++i) {
        outFile << "Solution " << (i + 1) << ": [";
        for (int j = 0; j < N; ++j) {
            outFile << solutions[i][j];
            if (j < N - 1) outFile << ", ";
        }
        outFile << "]\n";
    }

    outFile.close();
    cout << "Solutions saved to: " << fileName << "\n";
}

// Function to update the safe matrix when placing or removing a queen
void updateSafeMatrix(vector<vector<int>>& safeMatrix, int row, int col, int changer, int N) {
    
    // Update the rows and columns
    for (int i = 0; i < N; ++i) {
        safeMatrix[row][i] += changer;
        safeMatrix[i][col] += changer;
    }

    int r, c;

    // Top-left to bottom-right diagonal
    r = row; c = col;
    while (r >= 0 && c >= 0) {
        safeMatrix[r][c] += changer;
        r--; c--;
    }
    r = row + 1; c = col + 1;
    while (r < N && c < N) {
        safeMatrix[r][c] += changer;
        r++; c++;
    }

    // Top-right to bottom-left diagonal
    r = row; c = col;
    while (r >= 0 && c < N) {
        safeMatrix[r][c] += changer;
        r--; c++;
    }
    r = row + 1; c = col - 1;
    while (r < N && c >= 0) {
        safeMatrix[r][c] += changer;
        r++; c--;
    }

    // Subtract the overcounted positions
    safeMatrix[row][col] -= changer * 3;
}
