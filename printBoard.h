#include <iostream>
#ifndef PRINTBOARD_H // sin los define y el endif el codigo daba error de redefinir la funcion al ejecutarla
#define PRINTBOARD_H
using namespace std;

/* Esta funcion se encarga de imprimir el tablero, imprimiendo las fichas de los jugadores con su respectivo color y el resto de caracteres lo imprime sin color
R = Rojo
V = Verde
A = Amarillo 
B = Azul */
void printBoard(char board[15][15]) {
  system("clear");
    for(int i = 0; i < 15; i++) {
      for(int j = 0; j < 15; j++) {
        if (board[i][j] == 'R')
          cout << "\033[1;31m" << board[i][j] << "\033[0m" << " ";
        else if (board[i][j] == 'V')
          cout << "\033[1;32m" << board[i][j] << "\033[0m" << " ";
        else if (board[i][j] == 'A')
          cout << "\033[1;33m" << board[i][j] << "\033[0m" << " ";
        else if (board[i][j] == 'B')
          cout << "\033[1;34m" << board[i][j] << "\033[0m" << " ";
        else 
          cout << board[i][j] << " ";
      }
      cout << endl;
    }
}

#endif