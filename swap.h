// esta funcion se encarga de cambiar la posicion del token a la nueva posicion en el tablero luego de todos los movimientos
void swap(char board[15][15], int pos_tokenx, int pos_tokeny, int prevx, int prevy) {
  char temp = board[prevy][prevx];
  board[prevy][prevx] = board[pos_tokeny][pos_tokenx];
  board[pos_tokeny][pos_tokenx] = temp;
}