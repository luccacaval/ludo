#include <iostream>
using namespace std;

int ppt(int player1, int player2) {
  // inicializamos las variables para la eleccion de cada jugador y la variable del ganador
  int choice1, choice2;
  int winner = 0;
  while(1) {
    // se le pide al jugador que elija entre las opciones
	  cout << "Jugador 1. Elija piedra, papel o tijera (1,2,3): " << endl;
    cin >> choice1;
    // borramos la terminal para que no se lea su eleccion
    system("clear");
    // se le pide al jugador que elija entre las opciones  
    cout << "Jugador 2. Elija piedra, papel o tijera (1,2,3): " << endl;
	  cin >> choice2;
    // borramos la terminal para que no se lea su eleccion
    system("clear");
    // se comprueban todos los casos posibles en los que podria ganar el jugador 1
    if(choice1 > choice2 && choice1 - 1 == choice2 || choice1 == 1 && choice2 == 3) {
      // si se cumplen los casos se notifica y a winner se le asigna el valor del jugador 1 y        se sale del while
		  printf("Ganaste jugador 1\n");
      winner = player1;
      break;
	  } else if(choice1 == choice2) {
      // si no se cumplen las condiciones y si ambas elecciones son iguales es empate y se           reinicia el while
		  printf("Empate\n");
      continue;
	  } else {
      // si no se cumplen las condiciones se notifica que gano el jugador 2 y a winner se le         asigna el valor del jugador 2 y se sale del while
		  printf("Ganaste jugador 2\n");
      winner = player2;
      break;
	  }
  }
  // devolvemos el valor de winner
  return winner; 
}