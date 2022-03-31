/*******************************************************************************
*  AUTHOR        :  Dylan Wattles
*  Final Project :  BattleShips
*  CLASS         :  CS2
*  SECTION       :  MTWR: 7:30a - 12:30p
*  DUE DATE      :  2/13/19
*******************************************************************************/
#ifndef HEADER_H
#define HEADER_H
#endif

#include <iostream>
#include <vector>
#include <iomanip>
#include <stdlib.h>
#include <ctime>
using namespace std;
/*******************************************************************************
*
*  Battleship
*_______________________________________________________________________________
*
*  This program allow's players to play the board game Battleship against
*  another player or against the program's battleship algorithm. The algorithm
*  bases its decisions off of the possible arrangements for all ships in each
*  cell on the board.
*_______________________________________________________________________________
*  INPUT:
*    mode: 1 to play against player, 0 to play against computer
*    player or player's will enter the intial positions for their ships on the
*    board, and both will take shots at the other player's board until all of
*    one of the players' ships is sunk
*    additionally, the player will choose placements for ships and shots at the
*    opponents board
*    playAgain: 1 to play again, 0 to quit
*
*  OUTPUT:
*    board: the game board
*    turns: number of turns taken
*******************************************************************************/

const int Carrier=5;     // Carrier size
const int Battleship=4;  // Battleship size
const int Cruiser=3;     // Cruiser size
const int Submarine=3;   // Submarine size
const int Destroyer=2;   // Destroyer size

const int Fleet_Size=5;  // number of ships per player

/*******************************************************************************
*  struct Point
*  This contains a point's row and column coordinates
*******************************************************************************/
struct Point
{
    int row;
    int col;
};

/*******************************************************************************
*  struct Ship
*  This contains a ship's name, size and hitcount
*******************************************************************************/
struct Ship
{
    string name;
    int size;
    int hitcount;
    vector <Point> spots;
};

/*******************************************************************************
*  struct PlayerBoard
*  This contains and array of ship structures and the player board
*******************************************************************************/
struct PlayerBoard
{
    char board[10][10];
    Ship ships[Fleet_Size];
};

/*******************************************************************************
*  FUNCTION startMenu
*  This function displays the start menu, and allows user to select between
*  playing another player or the program's algorithm
*******************************************************************************/
void startMenu(int& mode);  // IN - 1 for vs player, 0 for vs computer

/*******************************************************************************
*  FUNCTION initFleet
*  This function initializes the ship sizes and names
*******************************************************************************/
void initFleet(PlayerBoard& player);  // IN,OUT - intialize ship names, sizes

/*******************************************************************************
*  FUNCTION displayBoards
*  This function displays the player boards
*******************************************************************************/
void displayBoards(char player1[][10],   // OUT - player1 board
                    char player2[][10]); // OUT - player2 board

/*******************************************************************************
*  FUNCTION spaceOccupied
*  This function returns true if a space is occupied by another ship,
*  it returns false otherwise
*******************************************************************************/
bool spaceOccupied(int row,             // IN - row coordinate to be checked
                   int col,             // IN - col coordinate to be checked
                   PlayerBoard player,  // IN - player info (need board)
                   char orientation,    // IN - horizontal or vertical ship
                   int size);           // IN - number of spaces ships takes up


/*******************************************************************************
*  FUNCTION spaceOccupied
*  This function returns true if a position is out of bounds, it returns false
*  otherwise
*******************************************************************************/
bool outBounds(int row,           // IN - row coordinate to be checked
               int col,           // IN - col coordinate to be checked
               char orientation,  // IN - horizontal or vertical ship
               int size);         // IN - size of ship to be checked

/*******************************************************************************
*  FUNCTION getValidShipInfo
*  This function returns gets a valid ship placement from a player
*******************************************************************************/
void getValidShipInfo(int& row,             // IN,OUT - row coordinate
                      int& col,             // IN,OUT - col coordinate
                      char& orientation,    // IN,OUT - horizontal or vertical
                      PlayerBoard& player,  // IN - player info (need board)
                      int index);           // IN - index for ship

/*******************************************************************************
*  FUNCTION setShip
*  This function sets an individual ship on the board
*******************************************************************************/
void setShip(PlayerBoard& player,  // IN,OUT - update player board
              int index);          // IN - ship index

/*******************************************************************************
*  FUNCTION hideShips
*  This function hides the other players ships from view
*******************************************************************************/
void hideShips(PlayerBoard player,  // IN - player board
               char temp[][10]);    // OUT - new board for opposign perspective


/*******************************************************************************
*  FUNCTION initBoard
*  This function sets up the boards for pvp
*******************************************************************************/
void initBoard(PlayerBoard& player1,   // IN,OUT - initialize board for pvp, p1
               PlayerBoard& player2);  // IN,OUT - initialize board for pvp, p2

/*******************************************************************************
*  FUNCTION initBoard
*  This function sets up the boards for pvc
*******************************************************************************/
void initBoard2(PlayerBoard& player1,  // IN,OUT - initialize board for pvc, p1
                PlayerBoard& player2); // IN,OUT - initialize board for pvc, c

/*******************************************************************************
*  FUNCTION getValidShot
*  This function gets a valid shot from a player
*******************************************************************************/
void getValidShot(PlayerBoard& otherPlayer,  // IN - player info(board)
                  int& row,                  // OUT - valid row for shot
                  int& col);                 // OUT - valid col for shot

/*******************************************************************************
*  FUNCTION fire
*  This function fires player shots
*******************************************************************************/
void fire(PlayerBoard& otherPlayer);  // OUT - update board after firing, pvp

/*******************************************************************************
*  FUNCTION setShipComp
*  This function sets up an individual ship for the computer
*******************************************************************************/
void setShipComp(PlayerBoard& computer,  // IN,OUT - uodate computer board
                 int index);             // IN - ship index

/*******************************************************************************
*  FUNCTION countShipPerms
*  This function counts arrangements of ships for a cell
*******************************************************************************/
int countShipPerms(const PlayerBoard& otherPlayer,  // IN - player board
                int index,                          // IN - ship index
                int m,                              // IN - row index
                int n);                             // IN - col index

/*******************************************************************************
*  FUNCTION compSearch
*  This function shoots for the computer when there are no unsunk hits
*******************************************************************************/
void compSearch(const PlayerBoard& otherPlayer,  // IN - player board
                int& row,                        // OUT - comp's search shot row
                int& col);                       // OUT - comp's search shot col

/*******************************************************************************
*  FUNCTION compDestroy
*  This function shoots for the computer when there are unsunk hits
*******************************************************************************/
void compDestroy(PlayerBoard& otherPlayer,  // IN - player board
                 int& row,                  // OUT - comp's destroy shot row
                 int& col);                 // OUT - comp's destroy shot col

/*******************************************************************************
*  FUNCTION getCompShot
*  This function gets a shot from either search or destroy
*******************************************************************************/
void getCompShot(PlayerBoard& otherPlayer,  // IN - player board
                 int& row,                  // OUT - row for shot
                 int& col);                 // OUT - col for shot

/*******************************************************************************
*  FUNCTION compFire
*  This function fires for the computer
*******************************************************************************/
void compFire(PlayerBoard& otherPlayer);  // IN,OUT - update other board w/shot

/*******************************************************************************
*  FUNCTION gameWin
*  This function checks if a player has won the game
*******************************************************************************/
bool gameWon(PlayerBoard player);  // IN - player board


