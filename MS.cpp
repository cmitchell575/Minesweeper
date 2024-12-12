#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
//This is a Minesweeper game! I have a static board that are characters a-i that users can enter and interact with a board created in the terminal.
//I am very proud of how this turned out and I have tinkered with many different versions of this.
//Final date of completion 12/12/24
//Chase Mitchell
int main() {
  //Declaring variables; the board/bomb/adjacentbomb arrays are set up all in the same fashion and are designed to be simple and flexible
  char board[3][3] = {{'a','b','c'},{'d','e','f'},{'g','h','i'}};
  bool isBomb[3][3] = {{false,false,false},{false,false,false},{false,false,false}}; 
  int adjacentBombs[3][3] = {{0,0,0},{0,0,0},{0,0,0}};
  //These variables are to set the initial values of how many bombs are in the grid and how many spaces have been revealed versus their totals so they can be referenced and
  //modified later.
  int bombsPlaced = 0;
  int revealedSpaces= 0;
  int totalSpaces = 9;
  int totalBombs = 2;
  bool gameOver = false;

  srand(static_cast<unsigned int>(time(0)));
  //This places bombs randomly using X,Y coordinates on our 3x3 grid to place our bombs. I modified this value to ensure that it is working correctly and not with just 2 bombs
  while (bombsPlaced < totalBombs) {
    int x = rand() % 3;
    int y = rand() % 3;
    if (!isBomb[x][y]){
        isBomb[x][y] = true;
        bombsPlaced++;
    }
  }
  //This is to calculate how many bombs are adjacent to a space (this is hidden from the user until they reveal the space)
  for (int x = 0; x < 3; x++) {
    for (int y = 0; y < 3; y++) {
      //This line continues to skip over bombs
      if (isBomb[x][y]) continue;
      for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
          int nx = x + dx;
          int ny = y + dy;
            if (nx >= 0 && nx < 3 && ny >= 0 && ny < 3 && isBomb[nx][ny]){
              adjacentBombs[x][y]++;
            }
          }
        }
      }
    }
    //This is changed from my initial setup and now is one consistent loop that will keep you in the loop while your revealed spaces are less than the total - total bombs
    //I had to mess with this a lot to make it work and I am glad I reached this conclusion as it allows the loop to end when you reach the goal of 7 revealed spaces in this
    //case however I did test with other values and it works this way without being complicated.
  while (revealedSpaces < totalSpaces - totalBombs && !gameOver) {
    //Display current board ; this is key to the loop as it updates as you reveal spaces
    cout << "\nCurrent Board:\n";
    for (int i = 0; i < 3; i++) {
      cout << "| " << board[i][0] << " | " << board [i][1] << " | " << board[i][2] << " |\n";
    }
    //Get input from the user; then determine if it is a usable input; then determine if the matched input is a bomb. If it is a bomb the game is over and you lose.
    char input;
    cout << "Enter a cell to reveal the space (a-i): ";
    cin >> input;
    bool matchInput = false;
    for (int x = 0; x < 3; x++) {
      for (int y = 0; y < 3; y++){
        if (board[x][y] == input){
          matchInput = true;
          if (isBomb[x][y]) {
            cout << "\nGame Over! You hit a bomb!\n";
            for (int i = 0; i < 3; i++){
              for (int j = 0; j < 3; j++){
                if (isBomb[i][j]) board[i][j] = '*';
                cout << "| " << board[i][j] << " ";
              }
              cout << "|\n";
            }
            gameOver = true;
          }else {
            board[x][y] = '0' + adjacentBombs[x][y];
            revealedSpaces++;
          }
        }
      }
    }
    if (!matchInput) {
      cout << "Invalid input. Try again.\n";
    }
  }
  if (!gameOver){
  cout << "\nCongratulations! You've revealed all safe spaces!\n";
  }
}