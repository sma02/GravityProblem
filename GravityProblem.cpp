#include <iostream>
#include <windows.h>
using namespace std;

bool gravity = false;
bool isBlackHole = false;
char maze[20][71] = {
    "######################################################################",
    "#                                                                    #",
    "#                                                                    #",
    "#                                                                    #",
    "#                                                                    #",
    "#                                                                    #",
    "#                                                                    #",
    "#                                                                    #",
    "#                                                                    #",
    "#                                                                    #",
    "#                                                                    #",
    "#                                                                    #",
    "#                                                                    #",
    "#                                                                    #",
    "#                                                                    #",
    "#                                                                    #",
    "#                                                                    #",
    "#                                                                    #",
    "#                                                                    #",
    "######################################################################",
};

void gotoxy(int x, int y);
void consoleCursor(bool visibility);
void render(char array[][71], int mazeSize, int offsetX, int offsetY);
void setGravity(bool value);
void toggleBlackHole();
void shiftArray(char array[][71], int mazeSize);
void copyArray(char array1[], char array2[], int size);
void printMaze(char array[][71], int mazeSize, int offsetX, int offsetY);
void fillObjectsRandomly(char array[][71], int mazeSize, int objectCount);

int main()
{
    system("cls");
    consoleCursor(false);
    setGravity(true);
    fillObjectsRandomly(maze, 20, 80);
    printMaze(maze, 20, 20, 5);
    while (1)
    {
        Sleep(50);
        render(maze, 20, 20, 5);
        if (GetAsyncKeyState(VK_UP))
        {
            setGravity(0);
        }
        else if (GetAsyncKeyState(VK_DOWN))
        {
            setGravity(1);
        }
        else if (GetAsyncKeyState(VK_SPACE))
        {
            toggleBlackHole();
        }
    }
}
void fillObjectsRandomly(char array[][71], int mazeSize, int objectCount)
{
    int x, y;
    x = rand() % 68 + 2;
    y = rand() % (mazeSize - 2) + 2;
    for (int i = 0; i < objectCount; i++)
    {
        x = rand() % 68 + 2;
        y = rand() % (mazeSize - 2) + 2;
        if (array[y][x] != ' ')
        {
            i--;
        }
        else
        {
            array[y][x] = '*';
        }
    }
}
void printMaze(char array[][71], int mazeSize, int offsetX, int offsetY)
{
    for (int i = 0; i < mazeSize; i++)
    {
        gotoxy(offsetX, offsetY + i);
        cout << array[i] << endl;
    }
}
void setGravity(bool value)
{
    gravity = value;
}
void toggleBlackHole()
{
    isBlackHole = !isBlackHole;
}
void render(char array[][71], int mazeSize, int offsetX, int offsetY)
{
    if (gravity)
    {
        if (isBlackHole)
        {
            shiftArray(array, mazeSize);
            printMaze(array, mazeSize, offsetX, offsetY);
        }
        else
        {
            for (int i = mazeSize - 2; i > 0; i--)
            {

                for (int j = 1; j < 69; j++)
                {
                    if (array[i][j] != ' ' && array[i + 1][j] == ' ')
                    {
                        array[i + 1][j] = array[i][j];
                        array[i][j] = ' ';
                        gotoxy(offsetX + j, offsetY + i);
                        cout << array[i][j];
                        gotoxy(offsetX + j, offsetY + i + 1);
                        cout << array[i + 1][j];
                    }
                }
            }
        }
    }
}
void copyArray(char array1[], char array2[], int size)
{
    for (int i = 1; i < size - 1; i++)
    {
        array1[i] = array2[i];
    }
}
void shiftArray(char array[][71], int mazeSize)
{
    char firstLine[71];
    copyArray(firstLine, array[mazeSize - 2], 71);
    for (int i = mazeSize - 2; i > 0; i--)
    {
        copyArray(array[i], array[i - 1], 71);
    }
    copyArray(array[1], firstLine, 71);
}
void gotoxy(int x, int y)
{
    COORD coordinates;
    coordinates.X = x;
    coordinates.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);
}
void consoleCursor(bool visibility)
{
    CONSOLE_CURSOR_INFO ci;
    HANDLE stdHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleCursorInfo(stdHandle, &ci);
    ci.bVisible = visibility;
    SetConsoleCursorInfo(stdHandle, &ci);
}
