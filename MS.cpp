#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main() {
  char board[3][3] = {{'a','b','c'},{'d','e','f'},{'g','h','i'}};
  bool isBomb[3][3] = {{false,false,false},{false,false,false},{false,false,false}}; 
  int adjacentBombs[3][3] = {{0,0,0},{0,0,0},{0,0,0}};
  int bombsPlaced = 0;
  int revealedSpaces= 0;
  int totalSpaces = 9;
  int totalBombs = 2;

  srand(static_cast<unsigned int>(time(0)));
  while (bombsPlaced < totalBombs) {
    int x = rand() % 3;
    int y = rand() % 3;
    if (!isBomb[x][y]){
        isBomb[x][y] = true;
        bombsPlaced++;
    }
  }
  for (int x = 0; x < 3; x++) {
    for (int y = 0; y < 3; y++) {
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
  while (revealedSpaces < totalSpaces - totalBombs) {
    cout << "\nCurrent Board:\n";
    for (int i = 0; i < 3; i++) {
      cout << "| " << board[i][0] << " | " << board [i][1] << " | " << board[i][2] << " |\n";
    }
    char input;
    cout << "Enter a cell to reveal the sapce (a-i): ";
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
  cout << "\nCongratulations! You've revealed all safe spaces!\n";
}
