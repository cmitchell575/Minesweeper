#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
int main() {
  const int boardSize = 3; 
  const int numBombs = 2; 
  char displayBoard[boardSize][boardSize]; 
  bool isBomb[boardSize][boardSize] = {false}; 
  int adjacentBombs[boardSize][boardSize] = {0};

  for (int i = 0; i < boardSize; i++){
    for (int j = 0; j < boardSize; j++) {
      displayBoard[i][j] = 'X' ;
    }
  }
  srand(static_cast<unsigned int>(time(0)));
  for (int i = 0; i < numBombs;) {
    int x = rand() % boardSize;
    int y = rand() % boardSize;
    if (!isBomb[x][y]){
        isBomb[x][y] = true;
        i++;
    }
  }
  for (int i = 0; i < boardSize; i++) {
    for (int j = 0; j < boardSize; j++) {
      if (!isBomb[i][j]);
        for (int dx = -1; dx <= 1; dx++) {
          for (int dy = -1; dy <= 1; dy++) {
            int nx = i + dx;
            int ny = j + dy;
            if (dx!= 0 || dy != 0){
              if (nx >= 0 && nx < boardSize && ny >= 0 && ny < boardSize && isBomb[nx][ny]){
                adjacentBombs[i][j]++;
                 }
              }
            }
        }
      }
    }
  bool gameOver = false;
  bool gameWon = false;
  while (!gameOver && !gameWon) {
    for (int i = 0; i < boardSize; i++) {
      for (int j = 0; j < boardSize; j++) {
        cout << "| " << displayBoard[i][j] << " ";
      }
      cout << "|\n";
    }
  int x, y;
  cout << "Enter row and column to reveal (0 = " << boardSize - 1<< "): ";
  cin >> x >> y;
  if (x < 0 || x >= boardSize || y < 0 || y >= boardSize) {
    cout << "Invalid input. Try again.\n";
  }else if (isBomb[x][y]){
    gameOver = true;
  }else{
  displayBoard[x][y] = '0' + adjacentBombs[x][y];
  gameWon = true;
  for (int i = 0; i < boardSize; i++) {
    for (int j = 0; j < boardSize; j++) {
      if (displayBoard[i][j] == 'X' && !isBomb[i][j]){
        gameWon = false;
      }
    }
  }
  }
}
for (int i = 0; i < boardSize; i++) {
  for (int j = 0; j < boardSize; j++) {
    if (isBomb[i][j]){
      displayBoard[i][j] = '*';
    }
    cout << "| " << displayBoard[i][j] << " ";
  }
  cout << "|\n";
}
if (gameOver) {
  cout <<"Game Over! You hit a bomb!\n";
}else if(gameWon){
  cout << "Congratulations! You've revealed all non-bomb spaces!\n";
}
}
