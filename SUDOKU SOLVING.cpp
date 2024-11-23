#include <iostream>
using namespace std;

void printGrid(int grid[9][9])
{
    for (int row = 0; row < 9; row++)
    {
        for (int col = 0; col < 9; col++)
        {
            cout << grid[row][col] << " ";
        }
        cout << endl;
    }
}
bool isSafe(int grid[9][9], int row, int col, int num)
{

    for (int x = 0; x < 9; x++)
        if (grid[row][x] == num)
            return false;
    for (int x = 0; x < 9; x++)
        if (grid[x][col] == num)
            return false;
    int startRow = row - row % 3, startCol = col - col % 3;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (grid[i + startRow][j + startCol] == num)
                return false;
        return true;
}
bool solveSudoku(int grid[9][9]) {
    int row, col;
    bool isEmpty = false;

    for (row = 0; row < 9; row++)
    {
        for (col = 0; col < 9; col++)
        {
            if (grid[row][col] == 0)
            {
                isEmpty = true;
                break;
            }
        }
        if (isEmpty)
            break;
    }
    if (!isEmpty)
        return true;
    for (int num = 1; num <= 9; num++)
    {
        if (isSafe(grid, row, col, num))
        {
            grid[row][col] = num;
            if (solveSudoku(grid))
                return true;
            grid[row][col] = 0;
        }
    }
    return false;
}
int main() 
{
    int grid[9][9];
    cout << "Enter the Sudoku puzzle (use 0 for empty cells):" << endl;
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            cin >> grid[row][col];
        }
    }
    if (solveSudoku(grid))
    {
        cout << "Solved Sudoku grid:" << endl;
        printGrid(grid);
    }
    else 
    {
        cout << "No solution exists!" << endl;
    }
    return 0;
}

