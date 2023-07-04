#include <iostream>
#include <array>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "initBoard.h"
#include "printBoard.h"
#include "ppt.h"
#include "swap.h"

using namespace std;

int seed = time(NULL);

char board[15][15];

//estructura para guardar informacion de cada ficha
struct token {
  int posx = -1;
  int posy = -1;
  int owner; //indice del jugador que posee la ficha
  int direction; //indice de la direccion a la que se tiene que mover la ficha
  int spaces_moved = 1;
  int lines_traveled = 1;
  int delivered = 0;
};

struct player {
  array<int,13>directions; // stackoverflow dijo que funcionaba, guarda las direcciones en las que se tiene que mover la ficha segun el jugador
  char token_identifier; //caracter a utilizar para identificar la ficha
  // posicion en la que la ficha inicia
  int start_pos_x;
  int start_pos_y;
  int tokens_count = 0;
  int tokens_delivered = 0;
  int tokens_taken = 0;
  struct token tokens[4];
};

struct player players[4];

//funcion para tirar dos dados y que los sume entre si
int dice(int seed) {
  return (rand() % 6 + 1)+ (rand() % 6 +1);
}

// funcion encargada de comer una ficha que se encuentre en la posicion de inicio del jugador
void take_token_start(int player, int posx, int posy) {
  // con el switch se revisa de que jugador es la ficha que se encuentra en la posicion de salida
      switch(board[posy][posx]) {
      // para cada caso se reinician los valores de la ficha para que ya no cuente en el juego
      case 'B':
        for(int i = 0; i < 4; i++) {
          if(players[0].tokens[i].posy == players[player].start_pos_y  && players[0].tokens[i].posx == players[player].start_pos_x) { // se comprueba que sea la ficha correcta así no se borra cualquiera
            players[0].tokens[i].posy = -1; // se reinician sus posiciones
            players[0].tokens[i].posx = -1;
            players[0].tokens[i].spaces_moved = 1; // se reinician sus espacios movidos
            players[0].tokens[i].lines_traveled = 1; // se reinician las lineas viajadas
          }
        }
        players[0].tokens_count--; // se le resta a la cantidad de fichas del jugador
        break;
      case 'R':
        for(int i = 0; i < 4; i++) {
          if(players[1].tokens[i].posy == players[player].start_pos_y  && players[1].tokens[i].posx == players[player].start_pos_x) {
            players[1].tokens[i].posy = -1;
            players[1].tokens[i].posx = -1;
            players[1].tokens[i].spaces_moved = 1;
            players[1].tokens[i].lines_traveled = 1;
          }
        }
        players[1].tokens_count--;
        break;
      case 'A':
        for(int i = 0; i < 4; i++) {
          if(players[2].tokens[i].posy == players[player].start_pos_y  && players[2].tokens[i].posx == players[player].start_pos_x) {
            players[2].tokens[i].posy = -1;
            players[2].tokens[i].posx = -1;
            players[2].tokens[i].spaces_moved = 1;
            players[2].tokens[i].lines_traveled = 1;
          }
        }
        players[2].tokens_count--;
        break;
      case 'V':
        for(int i = 0; i < 4; i++) {
          if(players[3].tokens[i].posy == players[player].start_pos_y  && players[3].tokens[i].posx == players[player].start_pos_x) {
            players[3].tokens[i].posy = -1;
            players[3].tokens[i].posx = -1;
            players[3].tokens[i].spaces_moved = 1;
            players[3].tokens[i].lines_traveled = 1;
          }
        }
        players[3].tokens_count--;
        break;
    }
    board[players[player].start_pos_y][players[player].start_pos_x] = players[player].token_identifier; // se coloca la ficha del jugador que realizo la salida
    printBoard(board); // se imprime el tablero
  }

// funcion encargada de comer una ficha en cualquier etapa del juego
void take_token(int player, int token, int tx, int ty) {
      // se comprueba de que jugador es la ficha en la posicion a mover
      switch(board[players[player].tokens[token].posy][players[player].tokens[token].posx]) {
      case 'B':
        for(int i = 0; i < 4; i++) {
          if(players[0].tokens[i].posy == players[player].tokens[token].posy  && players[0].tokens[i].posx == players[player].tokens[token].posx) { // se comprueba que sea la ficha correcta
            players[0].tokens[i].posy = -1; // se reinician sus posiciones
            players[0].tokens[i].posx = -1;
            players[0].tokens[i].spaces_moved = 1; // se reinician sus espacios movidos
            players[0].tokens[i].lines_traveled = 1; // se reinician sus lineas viajadas
          }
        }
        players[0].tokens_count--; // se le resta a la cantidad de fichas del jugador
        break;
      case 'R':
        for(int i = 0; i < 4; i++) {
          if(players[1].tokens[i].posy == players[player].tokens[token].posy  && players[1].tokens[i].posx == players[player].tokens[token].posx) {
            players[1].tokens[i].posy = -1;
            players[1].tokens[i].posx = -1;
            players[1].tokens[i].spaces_moved = 1;
            players[1].tokens[i].lines_traveled = 1;
          }
        }
        players[1].tokens_count--;
        break;
      case 'A':
        for(int i = 0; i < 4; i++) {
          if(players[2].tokens[i].posy == players[player].tokens[token].posy  && players[2].tokens[i].posx == players[player].tokens[token].posx) {
            players[2].tokens[i].posy = -1;
            players[2].tokens[i].posx = -1;
            players[2].tokens[i].spaces_moved = 1;
            players[2].tokens[i].lines_traveled = 1;
          }
        }
        players[2].tokens_count--;
        break;
      case 'V':
        for(int i = 0; i < 4; i++) {
          if(players[3].tokens[i].posy == players[player].tokens[token].posy  && players[3].tokens[i].posx == players[player].tokens[token].posx) {
            players[3].tokens[i].posy = -1;
            players[3].tokens[i].posx = -1;
            players[3].tokens[i].spaces_moved = 1;
            players[3].tokens[i].lines_traveled = 1;
          }
        }
        players[3].tokens_count--;
        break;
    }
     board[ty][tx] = '*';
    board[players[player].tokens[token].posy][players[player].tokens[token].posx] = players[player].token_identifier;
  }

// funcion encargada de iniciar los jugadores y sus movimientos
void init_players() {
  for(int i = 0; i < 4; i++){
    // almacena las posiciones iniciales de cada jugador
    players[i].start_pos_x = (i==0)?1:(i==1)?8:(i==2)?6:13;
    players[i].start_pos_y = (i==0)?6:(i==1)?1:(i==2)?13:8;
    // asinga cual sera la ficha correspondiente a cada jugador
    players[i].token_identifier = (i==0)?'B':(i==1)?'R':(i==2)?'A':'V';
    // almacena las direcciones predeterminadas de cada jugador siendo estas:   
    /*
      0 = derecha
      1 = abajo
      2 = izquierda
      3 = arriba 
    */
    //distintas direcciones que le corresponde a cada ficha de cada jugador
    switch (i) {
      case 0:
        players[i].directions = {0,3,0,1,0,1,2,1,2,3,2,3,0};
        break;
      case 1:
        players[i].directions = {1,0,1,2,1,2,3,2,3,0,3,0,1};
        break;
      case 2:
        players[i].directions = {3,2,3,0,3,0,1,0,1,2,1,2,3};
        break;
      case 3:
        players[i].directions = {2,1,2,3,2,3,0,3,0,1,0,1,2};
        break;
    }
  }
}

// inicializa la ficha
void init_token(int player) {
  // coloca la ficha en su posicion inicial
  board[players[player].start_pos_y][players[player].start_pos_x] = players[player].token_identifier;
  // guarda al jugador como dueño de la ficha
  players[player].tokens[players[player].tokens_count].owner = player;
  // almacena las posiciones iniciales como posiciones de la ficha especifica
  players[player].tokens[players[player].tokens_count].posx = players[player].start_pos_x;
  players[player].tokens[players[player].tokens_count].posy = players[player].start_pos_y;
  // suma al contador de fichas del jugador 
  players[player].tokens_count += 1;
  printBoard(board);
}

//funcion para mover la ficha
void move_token(int player, int token, int moves) {
  int tx = players[player].tokens[token].posx;
  int ty = players[player].tokens[token].posy;
  while (moves >= 1) {
    // Asigna a la variable directon en el strcut token el valor correspondiente del array directions segun la cantidad de lineas que recorrio
    players[player].tokens[token].direction = players[player].directions[players[player].tokens[token].lines_traveled-1];
    // Realiza los movimientos de la ficha del jugador dependiendo de su direccion almacenada
    switch (players[player].tokens[token].direction) {
      case 0:
        players[player].tokens[token].posx += 1;
        break;
      case 1:
        players[player].tokens[token].posy += 1;
        break;
      case 2:
          players[player].tokens[token].posx -= 1;
          break;
      case 3:
        players[player].tokens[token].posy -= 1;
        break;        
    }
    // Se le suma a la cantidad de espacios movidos
    players[player].tokens[token].spaces_moved += 1;
    // Controla si el jugador se paso del centro y hace los rebotes, o si corresponde cambiar la direccion
    if (players[player].tokens[token].posx == 7 && players[player].tokens[token].posy == 7 && moves > 1) {
      if(moves >= 7) {
        switch(player) {
          case 0:
            players[player].tokens[token].posx = 1;
            players[player].tokens[token].posy = 7;
            break;
          case 1:
            players[player].tokens[token].posx = 7;
            players[player].tokens[token].posy = 1;
            break;
          case 2:
            players[player].tokens[token].posx = 7;
            players[player].tokens[token].posy = 13;
            break;
          case 3:
            players[player].tokens[token].posx = 13;
            players[player].tokens[token].posy = 7;
            break;          
        }
      }
      else {
        switch(player) {
          case 0:
            players[player].tokens[token].posx -= moves;
            break;
          case 1:
            players[player].tokens[token].posy -= moves;
            break;
          case 2:
            players[player].tokens[token].posy += moves;
            break;
          case 3:
            players[player].tokens[token].posx += moves;
            break;
        }
      }
      players[player].tokens[token].lines_traveled = 13;
      players[player].tokens[token].spaces_moved = 0;
      swap(board,players[player].tokens[token].posx,players[player].tokens[token].posy,tx,ty);
      printBoard(board);
      return;
    } else if (((players[player].tokens[token].spaces_moved == 6 && players[player].tokens[token].lines_traveled % 3 != 0)||(players[player].tokens[token].spaces_moved == 2 && players[player].tokens[token].lines_traveled % 3 == 0 )|| (players[player].tokens[token].lines_traveled == 12 && players[player].tokens[token].spaces_moved == 1)) && players[player].tokens[token].lines_traveled != 13) {
      players[player].tokens[token].lines_traveled += 1;
      players[player].tokens[token].spaces_moved = 0;
      players[player].tokens[token].direction = players[player].directions[players[player].tokens[token].lines_traveled - 1];
    }
    // Si el jugador llego al centro se le avisa que entrego una ficha
    else if(players[player].tokens[token].posx == 7 && players[player].tokens[token].posy == 7 && moves == 1) {
     players[player].tokens_delivered++; // se le suma a la cantidad de fichas que entrego
     cout << "Entregaste una ficha" << endl;
    }
    // Le resta 1 a la variable de control del while
    moves--;
  }
  // se revisa si el jugador cayo en una ficha enemiga
  if((board[players[player].tokens[token].posy][players[player].tokens[token].posx] != ' ') && (board[players[player].tokens[token].posy][players[player].tokens[token].posx] != '*') && (board[players[player].tokens[token].posy][players[player].tokens[token].posx] != players[player].token_identifier)) {
    // se llama a la funcion de comer ficha
    take_token(player,token,tx,ty);
  }
  else 
      // se cambia la posicion de la ficha a la nueva posicion
      swap(board,players[player].tokens[token].posx,players[player].tokens[token].posy,tx,ty);
  printBoard(board); // se imprime el tablero
  board[7][7] = ' '; // se le asigna un espacio vacio al centro para en caso de que llegue alguna ficha no romper la funcionalidad del codigo
}

void save_game(int current_player){
  // se crea una variable para almacenar el nombre del archivo y se solicita dicho nombre
  char archivo[100];
  cout << "Ingrese un nombre para el archivo de guardado" << endl;
  cin >> archivo;
  // se le concatena al nombre la extension .dat
  archivo[strcspn(archivo, "\n")] = '.';
  strcat(archivo,"dat");
  // se abre el archivo en modo escritura
  FILE *fp;
  fp = fopen(archivo, "w");
  for(int i = 0; i < 4;i++){
    for(int j = 0; j < players[i].tokens_count; j++){
      // se almacenan todos los valores relevantes de las fichas, dueño, numero de ficha, posicion, lineas viajadas y espacios movidos
      fprintf(fp, "%d %d %d %d %d %d\n", i,j,players[i].tokens[j].posx,players[i].tokens[j].posy, players[i].tokens[j].lines_traveled, players[i].tokens[j].spaces_moved);
    }
  }
  // se almacena de quien es el turno
  fprintf(fp,"t%d", current_player);
  // se cierra el archivo
  fclose(fp);
}

// se asignan los valores obtenidos del archivo de guardado
void asing_values(int player,int token,int pos_x,int pos_y,int lines_travel, int spaces_move){
  players[player].tokens[token].posx = pos_x;
  players[player].tokens[token].posy = pos_y;
  board[players[player].tokens[token].posy][players[player].tokens[token].posx] = players[player].token_identifier;
  players[player].tokens[token].lines_traveled = lines_travel;
  players[player].tokens[token].spaces_moved = spaces_move;
  players[player].tokens_count++;
}

// funcion encargada de cargar una partida guardada
void load_game(int *current_player) {
  printBoard(board);
  // se declara el caracter previo
  int prev_char;
  // se declara la variable donde se almacenara el nombre del archivo y se solicita dicho nombre
  char archivo[100];
  cout << "Ingrese un nombre para elegir un archivo guardado" << endl;
  fgets(archivo,100,stdin);
  // se le concatena el formato .dat
  archivo[strcspn(archivo, "\n")] = '.';
  strcat(archivo,"dat");
  // se abre el archivo en modo lectura
  FILE *fp;
  fp = fopen(archivo, "r");
  // se declaran las variables donde se almacenara la informacion y la variable de control chars
  int player, token,pos_x,pos_y,c,chars = 1, lines_traveled, spaces_moved;
  // mientras que el archivo no haya terminado se recorre almacenando los valores
  while((c = fgetc(fp)) != EOF) {
    // se comprueba que c sea un numero
    if(c >= '0' && c <= '9') {
      if (chars % 6 == 1) {
        // se comprueba que su siguiente caracter sea un numero
        prev_char = c;
        c = fgetc(fp);
        if(c >= '0' && c <= '9'){
          prev_char = (prev_char - 48) * 10;
          c = prev_char + (c - 48);
          // si lo es se almacenan como un numero de dos digitos y se asigna el resultado a la variable
          player = c;
        } // si su caracter siguiente no es un numero simplemente se le asigna el numero unico a la variable
        else 
            player = prev_char - 48;
        
      }
      else if(chars % 6 == 2) {
        prev_char = c;
        c = fgetc(fp);
        if (c >= '0' && c <= '9') {
          prev_char = (prev_char - 48) * 10;
          c = prev_char + (c - 48);
          token = c;
        } else token = prev_char - 48;
        
      }
      else if(chars % 6 == 3) {
        prev_char = c;
        c = fgetc(fp);
        if (c >= '0' && c <= '9') {
          prev_char = (prev_char - 48) * 10;
          c = prev_char + (c - 48);
          pos_x = c;
        }else {
          pos_x = prev_char - 48;
        }
      }
      else if(chars % 6 == 4) {
        prev_char = c;
        c = fgetc(fp);
        if(c >= '0' && c <= '9') {
          prev_char = (prev_char - 48) * 10;
          c = prev_char + (c - 48);
          pos_y = c;
        } else pos_y = prev_char - 48;
      }
      else if(chars % 6 == 5) {
        prev_char = c;
        c = fgetc(fp);
        if (c >= '0' && c <= '9') {
          prev_char = (prev_char - 48) * 10;
          c = prev_char + (c - 48);
          lines_traveled = c;
        } else {
          lines_traveled = prev_char - 48;
        }
      }
      else if(chars % 6 == 0){
        prev_char = c;
        c = fgetc(fp);
        if (c >= '0' && c <= '9') {
          prev_char = (prev_char - 48) * 10;
          c = prev_char + (c - 48);
          spaces_moved = c;
        } else {
          spaces_moved = prev_char - 48;
        }
        // se asignan los valores encontrados a las variables de control del juego
        asing_values(player,token,pos_x,pos_y,lines_traveled,spaces_moved);
      }
    chars++;
    }
    // se almacena de quien es el turno
     else if (c == 't'){
      c = fgetc(fp);
      c -= 48;
      *current_player = c;
    }
  prev_char = c;
  }
  // se cierra el archivo
  fclose(fp);
}

//funcion para elegir la ficha que movera el jugador
void choice_token(int current_player, int moves) {
  int token_choice;
        cout << "Cual ficha queres mover?" << endl;
        cin >> token_choice;
        token_choice--;
  //controla que la ficha que quiere mover el jugador exista
        if(token_choice > players[current_player].tokens_count || token_choice < 0) cout << "Esa ficha no existe" << endl;
        else if(players[current_player].tokens[token_choice].delivered == 1) {
          cout << "Esa ya la entregaste" << endl;
        }
        else move_token(current_player,token_choice,moves);
}

int main(void) {
  char choice;
  srand(seed);
  // se declaran las variables que se usaran para el piedra papel o tijera
  int winner[2], supreme_winner, current_player;
  int playeres[4] = {0,1,2,3};
  // se inicia el tablero
  initBoard(board);
  // se inician los jugadores
  init_players();
  // se le pregunta al usuario si quiere iniciar una partida nueva
  cout << "Bienvenido al ludo" << endl;
  cout << "Queres iniciar una nueva partida? S/N" << endl;
  scanf("%c", &choice);
  getchar();
  // en caso de que no se llama a la funcion para cargar un juego guardado 
  if(choice == 'n' || choice == 'N') {
    load_game(&current_player);
    printBoard(board);
    cout << current_player % 4 << endl;
  }
  else {
  int j = 0;
  //declara quien es el ganador del piedra, papel y tijera para luego sacar su ficha y que inicie el juego
   for(int i = 0; i < 4; i+=2) {
     winner[j] = ppt(playeres[i],playeres[i+1]);
     j++;
   }
   supreme_winner = ppt(winner[0],winner[1]);
   init_token(supreme_winner);
   cout << endl;
   current_player = supreme_winner;
  }
  // se inicia el juego
   while(players[(current_player - 1) % 4].tokens_delivered != 4) {
      int moves = dice(seed); // se tira el dado
      cout << "Sacaste un " << moves << endl; // se le avisa al jugador cuantos movimientos tiene
      getchar();
      // se notifica de quien es el turno
      if (current_player % 4 == 0) cout << "Turno del jugador azul" << endl;
      else if (current_player % 4 == 1) cout << "Turno del jugador rojo" << endl;
      else if (current_player % 4 == 2) cout << "Turno del jugador amarillo" << endl;
      else if (current_player % 4 == 3) cout << "Turno del jugador verde" << endl;
     //muestra si los movimientos que saco el jugador es par para luego preguntarle si desea sacar una ficha o solo mover las fichas que tiene en el tablero
      if (players[current_player % 4].tokens_count != 4 && moves % 2 == 0) {
        cout << "Queres sacar una ficha? S/N" << endl;
        cin >> choice;
        if (choice == 'N' || choice == 'n') choice_token(current_player % 4,moves);
        else if (choice == 'S' || choice == 's') {
          //si el jugador ya tiene una ficha que saco en su turno anterior y no lo movio, le avisa y le pide mover una ficha de las que tiene, sino, saca la ficha
          if (board[players[current_player % 4].start_pos_y][players[current_player % 4].start_pos_x] == '*' || board[players[current_player % 4].start_pos_y][players[current_player % 4].start_pos_x] == ' ') 
            init_token(current_player % 4);
          else  if(board[players[current_player % 4].start_pos_y][players[current_player % 4].start_pos_x] != players[current_player % 4].token_identifier){
            take_token_start(current_player % 4,players[current_player % 4].start_pos_x,players[current_player % 4].start_pos_y);
            init_token(current_player % 4);
          }
          else {
            cout  << "Ya tenes una ficha en la posicion de inicio, cual queres mover?" << endl;
            choice_token(current_player % 4,moves);
          }
        }
        moves++;
      }
        //si tira un dado y el jugador no tiene una ficha y no saco un numero par, le avisa que intente la proxima vez
      else if(players[current_player % 4].tokens_count != 0) choice_token(current_player % 4,moves);
      else cout << "Mala suerte, probar en el proximo turno" << endl;
      current_player++;
      if (current_player % 4 == supreme_winner){
      cout << "Queres guardar la partida S/N" << endl;
      cin >> choice;
      if(choice == 'N' || choice == 'n') continue;
      else {
        save_game(current_player % 4);
        break;
      }
    }
  }
  // se comprueba quien gano y se notifica 
  if(players[(current_player - 1) % 4].tokens_delivered == 4) {
      if ((current_player-1) % 4 == 0) cout << "Gano el jugador azul, felicidades" << endl;
      else if ((current_player-1) % 4 == 1) cout << "Gano el jugador rojo, felicidades" << endl;
      else if ((current_player-1) % 4 == 2) cout << "Gano el jugador amarillo, felicidades" << endl;
      else if ((current_player-1) % 4 == 3) cout << "Gano el jugador verde, felicidades" << endl;
  }
}
