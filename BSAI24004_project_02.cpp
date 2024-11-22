
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <cstdlib>
using namespace std;

#define Rows 100
#define Cols 100

void gotoRowCol(int rpos, int cpos)
{
    COORD scrn;
    HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    scrn.X = cpos;
    scrn.Y = rpos;
    SetConsoleCursorPosition(hOutput, scrn);
}
void color(int k)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, k);
}

void printBox(int sr, int sc, int er, int ec)
{
    char sym = -37;
    for (int ri = 0; ri < er; ri++)
    {
        for (int ci = 0; ci < ec; ci++)
        {
            if (ri == 0 || ri == er - 1 || ci == 0 || ci == ec - 1)
            {
                gotoRowCol(sr + ri, sc + ci);
                cout << sym;
            }
        }
    }
}
void intToCellNumber(int position, int& cri, int& cci)
{
    position = 100 - position;
    cri = position / 10;
    cci = position % 10;
    if (cri % 2 == 1)
    {
        cci = 9 - cci;
    }
}
void writeNumberInMiddle(int ri, int ci, int er, int ec, int value)
{
    gotoRowCol(ri * er + er / 2 - 1, ci * ec + ec / 2 - 1);
    cout << value;
}
void printPlayerInMiddle(int ri, int ci, int er, int ec, int player)
{
    char sym = 'P';
    gotoRowCol(ri * er + er / 2 + 1, ci * ec + ec / 2 - 1);
    cout << sym << player;
}
void removePlayerInMiddle(int ri, int ci, int er, int ec)
{
    gotoRowCol(ri * er + er / 2 + 1, ci * ec + ec / 2 - 1);
    cout << "  ";
}
bool isPresent(int A[], int Size, int value)
{
    for (int i = 0; i < Size; i++)
    {
        if (A[i] == value)
            return true;
    }
    return false;
}
int returnIndex(int A[], int Size, int value)
{
    for (int i = 0; i < Size; i++)
    {
        if (A[i] == value)
            return i;
    }
    return -1;
}
void printGrid(int er, int ec)
{
    for (int ri = 0; ri < 10; ri++)
    {
        for (int ci = 0; ci < 10; ci++)
        {
            printBox(ri * er, ci * ec, er, ec);
        }
    }
}
void printBoardWithNumbers(int er, int ec)
{
    int cri, cci;
    for (int position = 1; position <= 100; position++)
    {
        intToCellNumber(position, cri, cci);
        writeNumberInMiddle(cri, cci, er, ec, position);
    }
}
int rollDice()
{
    return (rand() % 6) + 1;
}
int main()
{
    srand((unsigned)time(0));
    int er = Rows / 10;
    int ec = Cols / 10;
    const int capacity = 1000;
    int sSize = 5;
    int lSize = 5;
    int SS[] = { 27, 21, 33, 44, 35 };  
    int SE[] = { 5, 18, 50, 22, 12 };   
    int LS[] = { 6, 28, 19, 80, 53 };   
    int LE[] = { 38, 67, 39, 97, 81 };
    int np;
    cout << "Enter the number of players: ";
    cin >> np;
    int Players[capacity] = {};
    printGrid(er, ec);
    printBoardWithNumbers(er, ec);
    while (true)
    {
        for (int i = 0; i < np; i++)
        {
            int dice = rollDice();
            int newPos = Players[i] + dice;
            if (newPos > 100)
            {
                cout << "Player " << i + 1 << " rolled " << dice << " but cannot move!" << endl;
                _getch();
                continue;
            }
            int cri, cci;
            intToCellNumber(Players[i], cri, cci);
            removePlayerInMiddle(cri, cci, er, ec);
            Players[i] = newPos;
            if (isPresent(SS, sSize, Players[i]))
            {
                int index = returnIndex(SS, sSize, Players[i]);
                Players[i] = SE[index];
                cout << "Player " << i + 1 << " hit a snake! Down to " << Players[i] << endl;
            }
            if (isPresent(LS, lSize, Players[i]))
            {
                int index = returnIndex(LS, lSize, Players[i]);
                Players[i] = LE[index];
                cout << "Player " << i + 1 << " climbed a ladder! Up to " << Players[i] << endl;
            }
            intToCellNumber(Players[i], cri, cci);
            printPlayerInMiddle(cri, cci, er, ec, i + 1);
            if (Players[i] == 100)
            {
                cout << "Player " << i + 1 << " wins the game!" << endl;
                return 0;
            }
            _getch();
        }
    }
    return 0;
}

