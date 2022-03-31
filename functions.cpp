#include "header.h"

/*******************************************************************************
*
*  FUNCTION startMenu
*_______________________________________________________________________________
*  This function displays the start menu and allows the user to select between
*  playing the computer and playing another player
*_______________________________________________________________________________
*  PRE-CONDITIONS
*    none
*
*  POST-CONDTIONS
*    This function will display the start menu
*******************************************************************************/
void startMenu(int& mode) // IN - 1 for pvp, 2 for pvc
{
    cout << endl;
    cout << "      888             888   888   888                888     d8b" << endl;
    cout << "      888             888   888   888                888     Y8P" << endl;
    cout << "      888             888   888   888                888" << endl;
    cout << "      88888b.  8888b. 888888888888888 .d88b. .d8888b 88888b. 88888888b." << endl;
    cout << "      888 \"88b    \"88b888   888   888d8P  Y8b88K     888 \"88b888888 \"88b" << endl;
    cout << "      888  888.d888888888   888   88888888888\"Y8888b.888  888888888  888" << endl;
    cout << "      888 d88P888  888Y88b. Y88b. 888Y8b.         X88888  888888888 d88P" << endl;
    cout << "      88888P\" \"Y888888 \"Y888 \"Y888888 \"Y8888  88888P'888  88888888888P\"" << endl;
    cout << "                                                                888" << endl;
    cout << "                                                                888" << endl;
    cout << "                                                                888" << endl;

    // by Matthew Bace
    cout << "                                        |__" << endl;
    cout << "                                        ||" << endl;
    cout << "                                        ---" << endl;
    cout << "                                        / | [" << endl;
    cout << "                                 !      | |||" << endl;
    cout << "                               _/|     _/|-++'" << endl;
    cout << "                           +  +--|    |--|--|_ |-" << endl;
    cout << "                        { /|__|  |//__|  |--- |||__" << endl;
    cout << "                       +---------------___[}-_===_.'____" << endl;
    cout << "                   ____`-' ||___-{]_| _[}-  |     |_[___|==--                 _" << endl;
    cout << "   ___..._____--==/___]_|__|_____________________________[___|==--____,------' .7" << endl;
    cout << "   <                                                                     BB-61/" << endl;
    cout << "    <_________________________________________________________________________|" << endl;
    cout << endl << endl;

    // loop to get valid mode, 1 for pvp, 0 ofr pvc
    while(mode!=1&&mode!=0)
    {
        cout << "Press 1 for player vs player.\n";
        cout << "Press 0 for player vs computer.\n";
        cin >> mode;
        cout << endl;
    }
}

/*******************************************************************************
*
*  FUNCTION displayBoards
*_______________________________________________________________________________
*  This function displays both boards
*_______________________________________________________________________________
*  PRE-CONDITIONS
*    player1[][10]: player1 board
*    player2[][10]: player2 board
*
*  POST-CONDTIONS
*    This function will display the boards
*******************************************************************************/
void displayBoards(char player1 [][10],   // OUT - p1 board
                    char player2 [][10])  // OUT - p2 board
{   
    string dashes(41,'-');

    cout << "    1   2   3   4   5   6   7   8   9  10          "
         << "    1   2   3   4   5   6   7   8   9  10            \n";

    // display boards
    for(unsigned int i=0;i<10;i++)
    {
        cout << "  " << dashes << "          " << dashes << endl;
        cout << static_cast<char>('A'+i) << " |";

        for(unsigned int j=0;j<10;j++)
            cout << setw(2) << player1[i][j] << " |";

        cout << "        ";
        cout << static_cast<char>('A'+i) << " |";

        for(unsigned int j=0;j<10;j++)
            cout << setw(2) << player2[i][j] << " |";

        cout << endl;
    }
    cout << "  " << dashes << "          " << dashes << endl;
}

/*******************************************************************************
*
*  FUNCTION initFleet
*_______________________________________________________________________________
*  This function sets up the ship names and sizes
*_______________________________________________________________________________
*  PRE-CONDITIONS
*    PlayerBoard: need structure to contain player info
*
*  POST-CONDTIONS
*    This function will set the names and sizes
*******************************************************************************/
void initFleet(PlayerBoard& player)  // OUT - player info
{
    player.ships[0].name="carrier";
    player.ships[1].name="battleship";
    player.ships[2].name="cruiser";
    player.ships[3].name="submarine";
    player.ships[4].name="destroyer";

    player.ships[0].size=Carrier;
    player.ships[1].size=Battleship;
    player.ships[2].size=Cruiser;
    player.ships[3].size=Submarine;
    player.ships[4].size=Destroyer;
}

/*******************************************************************************
*
*  FUNCTION spaceOccupied
*_______________________________________________________________________________
*  This function returns true if a space is occupied and false otherwise
*_______________________________________________________________________________
*  PRE-CONDITIONS
*    row: row coordinate for ship
*    col: col coordinate for ship
*    player: player info structure
*    orientation: horizontal or vertical orientation for ship
*    size: ship size
*
*  POST-CONDTIONS
*    This function will return true if the space is occupied and false otherwise
*******************************************************************************/
bool spaceOccupied(int row,             // IN - row coordinate
                   int col,             // IN - col coordinate
                   PlayerBoard player,  // IN - player info
                   char orientation,    // IN - ship orientation
                   int size)            // IN - ship size
{
    // loop through position + size to find other ships
    for(int i=0;i<size;i++)
    {
        if(orientation=='h')
            if(player.board[row][col+i]=='s')
                return true;
        if(orientation=='v')
            if(player.board[row+i][col]=='s')
                return true;
    }
    return false;
}

/*******************************************************************************
*
*  FUNCTION outBounds
*_______________________________________________________________________________
*  This function returns true if a given position is out of bounds
*_______________________________________________________________________________
*  PRE-CONDITIONS
*    row: row coordinate for ship
*    col: col coordinate for ship
*    orientation: horizontal or vertical orientation for ship
*    size: ship size
*
*  POST-CONDTIONS
*    This function will return true if a ship is out of bounds, false otherwise
*******************************************************************************/
bool outBounds(int row,           // IN - row coordinate
               int col,           // IN - col coordinate
               char orientation,  // IN - ship vertical or horizontal placement
               int size)          // IN - ship size
{
    // conditions for out of bounds
    if(row>9||row<0||col>9||col<0)
        return true;

    if(orientation=='h')
        if(col+size>10)
            return true;

    if(orientation=='v')
        if(row+size>10)
            return true;

    return  false;
}

/*******************************************************************************
*
*  FUNCTION getValidShipInfo
*_______________________________________________________________________________
*  This function uses the outBounds and spaceOccupied functions to get a valid
*  ship position and orientation
*_______________________________________________________________________________
*  PRE-CONDITIONS
*    row: row coordinate for ship
*    col: col coordinate for ship
*    player: player info (need board)
*    orientation: horizontal or vertical orientation for ship
*    size: ship size
*
*  POST-CONDTIONS
*    This function will return a valid ship placement
*******************************************************************************/
void getValidShipInfo(int& row,             // IN,OUT - valid row coordinate
                      int& col,             // IN,OUT - valid col coordinate
                      char& orientation,    // IN,OUT - valid orientation
                      PlayerBoard& player,  // IN - player info
                      int index)            // IN - ship index
{
    char r;  // used to convert row coordinate to a char for display

    // loop until valid placement is given
    while(true)
    {
        // Prompt for ship placement
        cout << "Enter the row and column coordinates for your "
             << player.ships[index].name << ": ";
        cin >> r >> col;
        cout << endl;

        // convert coordinates
        col-=1;
        row=r-'A';

        // Prompt for ship orientation
        cout << "Enter the orientation for your " << player.ships[index].name
             << " ((horizontal)h or (vertical)v): ";
        cin >> orientation;
        cout << endl << endl;

        // conditions for errors, no errors means input is valid
        if(outBounds(row,col,orientation,player.ships[index].size))
            cout << "Error, out of bounds.\n";
        else if(spaceOccupied(row,col,player,orientation,player.ships[index].size))
            cout << "Error, space already occupied.\n";
        else
            break;
    }
}

/*******************************************************************************
*
*  FUNCTION setShip
*_______________________________________________________________________________
*  This function will update a player's board with their ship placement
*_______________________________________________________________________________
*  PRE-CONDITIONS
*    player: player info
*    index: ship number
*
*  POST-CONDTIONS
*    This function will update a player's board with a ship placement
*******************************************************************************/
void setShip(PlayerBoard& player,  // IN,OUT - update player info w/ new ship
              int index)           // IN - index for ship to be placed
{
    int row;           // row coordinate
    int col;           // col coordinate
    char orientation;  // horizontal or vertical orientations
    Point tempPoint;   // temporary point to update ship points

    // get starting positions
    getValidShipInfo(row,col,orientation,player,index);

    // fill spots for individual ship, store points
    for(int i=0;i<player.ships[index].size;i++)
    {
        if(orientation=='h')
        {
            player.board[row][col+i]='s';
            tempPoint.col=col+i;
            tempPoint.row=row;
            player.ships[index].spots.push_back(tempPoint);
        }
        else if(orientation=='v')
        {
            player.board[row+i][col]='s';
            tempPoint.col=col;
            tempPoint.row=row+i;
            player.ships[index].spots.push_back(tempPoint);
        }
    }
}

/*******************************************************************************
*
*  FUNCTION setShipComp
*_______________________________________________________________________________
*  This function will update the computer's board with its ship placement
*_______________________________________________________________________________
*  PRE-CONDITIONS
*    row: row coordinate
*    col: col coordinate
*    orientation: ship orientation
*    tempPoint: used to store ship points
*
*  POST-CONDTIONS
*    This function will update the computer's board with a ship placement
*******************************************************************************/
void setShipComp(PlayerBoard& computer,  // IN,OUT - update computer info
                 int index)              // IN - ship index
{
    int row;           // row coordinate
    int col;           // col coordinate
    char orientation;  // ship orientation
    Point tempPoint;   // temporary ship points

    // input validation
    while(true)
    {
        // random placements
        row=rand()%10;
        col=rand()%10;
        if(rand()%2==0)
            orientation='h';
        else
            orientation='v';

        // conditions for valid ship placement
        if(!(outBounds(row,col,orientation,computer.ships[index].size)))
            if(!(spaceOccupied(row,col,computer,orientation,computer.ships[index].size)))
                break;
    }

    // update stored ship points
    for(int i=0;i<computer.ships[index].size;i++)
    {
        if(orientation=='h')
        {
            computer.board[row][col+i]='s';
            tempPoint.col=col+i;
            tempPoint.row=row;
            computer.ships[index].spots.push_back(tempPoint);
        }
        else if(orientation=='v')
        {
            computer.board[row+i][col]='s';
            tempPoint.col=col;
            tempPoint.row=row+i;
            computer.ships[index].spots.push_back(tempPoint);
        }
    }
}

/*******************************************************************************
*
*  FUNCTION hideShips
*_______________________________________________________________________________
*  This function will hide ships from other player's view
*_______________________________________________________________________________
*  PRE-CONDITIONS
*    player: player info
*    temp:matrix with hidden view
*
*  POST-CONDTIONS
*    This function hide ships from view of other player
*******************************************************************************/
void hideShips(PlayerBoard player,  // player info
               char temp[][10])     // hidden view matrix
{
    // loop through board and replace ship spaces with null
    for (int i=0;i<10;i++)
        for(int j=0;j<10;j++)
        {
            if(player.board[i][j]=='s')
                temp[i][j]='\0';
            else
                temp[i][j]=player.board[i][j];
        }
}

/*******************************************************************************
*
*  FUNCTION initBoard
*_______________________________________________________________________________
*  This function will initialize both players' boards using the setship function
*  pvp mode
*_______________________________________________________________________________
*  PRE-CONDITIONS
*    player: player info
*
*  POST-CONDTIONS
*    This function will update a player's board with all valid ship placements
*******************************************************************************/
void initBoard(PlayerBoard& player1,  // p1 info
               PlayerBoard& player2)  // p2 info
{
    char temp [10][10];  // used to display hide ships board

    // initialize all grids to 0
    for (int i=0;i<10;i++)
        for(int j=0;j<10;j++)
        {
            player1.board[i][j]='\0';
            player2.board[i][j]='\0';
            temp[i][j]='\0';
        }

    // initialize hitcounts
    for(int i=0;i<Fleet_Size;i++)
    {
        player1.ships[i].hitcount=0;
        player2.ships[i].hitcount=0;
    }

    // Prompt to place ships on board for p1
    cout << "Player 1 set your board.\n";
    cout << setw(26) << "Your Board" << setw(53) << " Enemy Board \n";
    displayBoards(player1.board,player2.board);

    // place ships for p1
    for(int i=0;i<Fleet_Size;i++)
    {
        setShip(player1,i);
        cout << setw(26) << "Your Board" << setw(53) << " Enemy Board \n";
        displayBoards(player1.board,player2.board);
    }

    hideShips(player1,temp);

    // Prompt to place ship on board p2
    cout << "Player 2 set your board.\n";
    cout << setw(26) << "Your Board" << setw(52) << "Enemy Board \n";
    displayBoards(player2.board,temp);

    // place ships for p2
    for(int i=0;i<Fleet_Size;i++)
    {
        setShip(player2,i);
        cout << setw(26) << "Your Board" << setw(52) << "Enemy Board \n";
        displayBoards(player2.board,temp);
    }
}

/*******************************************************************************
*
*  FUNCTION initBoard2
*_______________________________________________________________________________
*  This function will initialize both boards, pvc mode
*_______________________________________________________________________________
*  PRE-CONDITIONS
*    player: player info
*
*  POST-CONDTIONS
*    This function will update a player's board with all valid ship placements
*    and the computer's with random ones
*******************************************************************************/
void initBoard2(PlayerBoard& player1,  // p1 info
                PlayerBoard& player2)  // p2 info
{
    char temp [10][10];  // used to hide ships

    // initialize all grids to 0
    for (int i=0;i<10;i++)
        for(int j=0;j<10;j++)
        {
            player1.board[i][j]='\0';
            player2.board[i][j]='\0';
            temp[i][j]='\0';
        }

    // initialize hitcounts
    for(int i=0;i<Fleet_Size;i++)
    {
        player1.ships[i].hitcount=0;
        player2.ships[i].hitcount=0;
    }

    // prompt to place all ships for p1
    cout << "Player 1 set your board.\n";
    cout << setw(26) << "Your Board" << setw(53) << " Enemy Board \n";
    displayBoards(player1.board,player2.board);

    // initialize ships
    for(int i=0;i<Fleet_Size;i++)
    {
        setShip(player1,i);
        cout << setw(26) << "Your Board" << setw(53) << " Enemy Board \n";
        displayBoards(player1.board,player2.board);
    }

    // random placements from computer
    for(int i=0;i<Fleet_Size;i++)
        setShipComp(player2,i);
}

/*******************************************************************************
*
*  FUNCTION getValidShot
*_______________________________________________________________________________
*  This function will get a valid shot from players
*_______________________________________________________________________________
*  PRE-CONDITIONS
*    player: player info
*
*  POST-CONDTIONS
*    This function will return the coordinates for a valid shot
*******************************************************************************/
void getValidShot(PlayerBoard& otherPlayer, // opposing player info board shot @
                  int& row,                 // row coordinate for shot
                  int& col)                 // col coordinate for shot
{
    char r;  // used for conversion

    // loop until valid shot
    while (true)
    {
        // prompt for shot
        cout << "Fire a shot: ";
        cin >> r >> col;
        cout << endl;

        // convert coordinates
        col-=1;
        row=r-'A';

        // invalid shot entries
        if(row>9||col>9||otherPlayer.board[row][col]=='H'
                ||otherPlayer.board[row][col]=='M')
            cout << "Error, invalid shot.\n";
        else
            break;
    }
}

/*******************************************************************************
*
*  FUNCTION fire
*_______________________________________________________________________________
*  This function will iupdate the boards based on a player's shot selection
*_______________________________________________________________________________
*  PRE-CONDITIONS
*    otherplayer: opposing player info
*
*  POST-CONDTIONS
*    This function will update the boards based on a player's shot
*    It will display messages for hits, misses and when a ship is sunk
*******************************************************************************/
void fire(PlayerBoard& otherPlayer)
{
    int row;  // row coordinate
    int col;  // col coordinate

    // retrieve player shot
    getValidShot(otherPlayer,row,col);

    // detect hit, miss using points for each ship
    // hits become (H's), misses become (M's) in display
    if(otherPlayer.board[row][col]=='s')
    {
        cout << "Hit!!!\n";
        otherPlayer.board[row][col]='H';

        // loop through all ships points to update hitcount
        for(unsigned int i=0;i<Fleet_Size;i++)
        {
            for(unsigned int j=0;j<otherPlayer.ships[i].size;j++)
            {
                if(otherPlayer.ships[i].spots[j].col==col&&
                        otherPlayer.ships[i].spots[j].row==row)
                {
                    otherPlayer.ships[i].hitcount++;

                    if(otherPlayer.ships[i].hitcount==otherPlayer.ships[i].size)
                        cout << "You sunk the " << otherPlayer.ships[i].name
                             << "!!!\n";
                }
            }
        }
    }
    else
    {
        cout << "You Missed.\n";
        otherPlayer.board[row][col]='M';
    }
}

/*******************************************************************************
*
*  FUNCTION countShipPerms
*_______________________________________________________________________________
*  This function counts the number of ways a ship can be arranged onto a cell
*_______________________________________________________________________________
*  PRE-CONDITIONS
*    otherplayer: opposing player info
*    int index: ship index
*    m: row index
*    n: col index
*
*  POST-CONDTIONS
*    This function count the possible arrangements
*******************************************************************************/
int countShipPerms(const PlayerBoard& otherPlayer,  // IN - opposing player info
                int index,                          // IN - ship index
                int m,                              // IN - row index
                int n)                              // IN - col index
{
    int vertPerms=0;  // num of ways vertical ship can be arranged on element
    int horizPerms=0; // num of ways horizontal ship can be arranged on element

    // default bounds
    int topBound=m-(otherPlayer.ships[index].size-1);
    int botBound=m+(otherPlayer.ships[index].size-1);
    int rightBound=n+(otherPlayer.ships[index].size-1);
    int leftBound=n-(otherPlayer.ships[index].size-1);

    // bounds if element with ship size reaches edges
    if(m-(otherPlayer.ships[index].size-1)<0)
        topBound=0;
    if(m+(otherPlayer.ships[index].size-1)>9)
        botBound=9;
    if(n+(otherPlayer.ships[index].size-1)>9)
        rightBound=9;
    if(n-(otherPlayer.ships[index].size-1)<0)
        leftBound=0;

    // top bound given sunk ships, misses
    int i=1;
    while(m-i>=0&&i<otherPlayer.ships[index].size)
    {
        if(otherPlayer.board[m-i][n]=='Z'||otherPlayer.board[m-i][n]=='M')
        {
            topBound=m-i+1;
            break;
        }
        i++;
    }

    // bot bound given board
    i=1;
    while(m+i<=9&&i<otherPlayer.ships[index].size)
    {
//        cout << "bot loop\n";
        if(otherPlayer.board[m+i][n]=='Z'||otherPlayer.board[m+i][n]=='M')
        {
            botBound=m+i-1;
            break;
        }
        i++;
    }

    // right bound given board
    i=1;

    while(n+i<=9&&i<otherPlayer.ships[index].size)
    {
//        cout << "right loop\n"; // test
        if(otherPlayer.board[m][n+i]=='Z'||otherPlayer.board[m][n+i]=='M')
        {
            rightBound=n+i-1;
            break;
        }
        i++;
    }

    // left bound, all bounds are inclusive
    i=1;
    while(n-i>=0&&i<otherPlayer.ships[index].size)
    {
//        cout << "left loop\n"; // test
        if(otherPlayer.board[m][n-i]=='Z'||otherPlayer.board[m][n-i]=='M')
        {
            leftBound=n-i+1;
            break;
        }
        i++;
    }

    // compute vertical arrangements possible
    vertPerms=(botBound-topBound+1)-(otherPlayer.ships[index].size-1);
    if(vertPerms<0)
        vertPerms=0;

    // horizontal arrangements possible
    horizPerms=(rightBound-leftBound+1)-(otherPlayer.ships[index].size-1);
    if(horizPerms<0)
        horizPerms=0;

    // OUT all possible arrangements for a ship on one cell
    return (vertPerms+horizPerms);
}

/*******************************************************************************
*
*  FUNCTION compSearch
*_______________________________________________________________________________
*  This function determines a position to fire at base on the max ship
*  arrangements for all cells on the board. Only used when there are no unsunk
*  hits
*_______________________________________________________________________________
*  PRE-CONDITIONS
*    otherplayer: other player info
*    row: row coordinate
*    col: col coordinate
*
*  POST-CONDTIONS
*    This function will return the coordinates for a shot based on the possible
*    ways a ship can be placed on an element
*******************************************************************************/
void compSearch(const PlayerBoard& otherPlayer,  // IN - opposing player info
                int& row,                        // OUT - row coordinate
                int& col)                        // OUT - col coordinate
{
    cout << "SEARCH" << endl; // TESTING!!

    int perms[10][10]; // matrix containing the permutations
    int maxPerms;      // max permutations

    // intialize elements to 0
    for(int i=0;i<10;i++)
        for(int j=0;j<10;j++)
            perms[i][j]=0;

    // caclulate possible ship arrangements for all cells, find cell with max
    // if multiple cells have max arrangements randomly select one
    maxPerms=perms[0][0];
    for(int i=0;i<Fleet_Size;i++)
    {
        if(otherPlayer.ships[i].hitcount!=otherPlayer.ships[i].size)
        {
            for(int j=0;j<10;j++)
            {
                for(int k=0;k<10;k++)
                {
                    if(otherPlayer.board[j][k]!='M'&&otherPlayer.board[j][k]!='Z')
                    {
                        perms[j][k]+=countShipPerms(otherPlayer,i,j,k);

                        if(perms[j][k]>maxPerms)
                        {
                            maxPerms=perms[j][k];
                            row=j;
                            col=k;
                        }
                        if(perms[j][k]==maxPerms)
                        {
                            if(rand()%3==1)
                            {
                                maxPerms=perms[j][k];
                                row=j;
                                col=k;
                            }
                        }
                    }
                }
            }
        }
    }

    //test---------------------------
        for(int i=0;i<10;i++)
        {
            for(int j=0;j<10;j++)
            {
                cout << setw(3) << perms[i][j];
            }
            cout << endl;
        }
        cout << endl;
//    // test--------------------------
}

/*******************************************************************************
*
*  FUNCTION compDestroy
*_______________________________________________________________________________
*  This function will sink a ship once the search function finds a hit
*_______________________________________________________________________________
*  PRE-CONDITIONS
*    otherplayer: player info
*
*  POST-CONDTIONS
*    This function will return the coordinates for shots intended to sink a ship
*******************************************************************************/
void compDestroy(PlayerBoard& otherPlayer,  // IN - opposing player info
                 int& row,                  // OUT - row coordinate
                 int& col)                  // OUT - col coordinate
{
    cout << "DESTROY" << endl; // TEST!!!!

    int dPerms[10][10]; // matrix of permutations
    int maxDPerms=0;    // max arrangements for all elements

    // intialize elements to 0
    for(int i=0;i<10;i++)
        for(int j=0;j<10;j++)
            dPerms[i][j]=0;

    // prioritize cells in same row or col as consecutive unsunk hits
    // loop to find H's, and check if there are consecutive H's
    // if open space past consecutive H's, prioritize those spaces
    for(int i=0;i<10;i++)
    {
        for(int j=0;j<10;j++)
        {
            if(otherPlayer.board[i][j]=='H')
            {
                // consecutive row w/ h
                if(i<9&&otherPlayer.board[i+1][j]=='H')
                {
                   // below two consec
                    if(i+2<=9&&otherPlayer.board[i+2][j]!='M'
                           &&otherPlayer.board[i+2][j]!='Z'
                           &&otherPlayer.board[i+2][j]!='H')
                   {
                       row=i+2;
                       col=j;
                       return;
                   }
                   // above two consec
                   if(i>0&&otherPlayer.board[i-1][j]!='M'
                          &&otherPlayer.board[i-1][j]!='Z'
                          &&otherPlayer.board[i-1][j]!='H')
                   {
                       row=i-1;
                       col=j;
                       return;
                   }
                }
                //consecutive col w/ h
                if(j<9&&otherPlayer.board[i][j+1]=='H')
                {
                    // right of two consec
                    if(j+2<=9&&otherPlayer.board[i][j+2]!='M'
                            &&otherPlayer.board[i][j+2]!='Z'
                            &&otherPlayer.board[i][j+2]!='H')
                    {
                        row=i;
                        col=j+2;
                        return;
                    }
                    // left of two consec
                    if(j>0&&otherPlayer.board[i][j-1]!='M'
                            &&otherPlayer.board[i][j-1]!='Z'
                            &&otherPlayer.board[i][j-1]!='H')
                    {
                        row=i;
                        col=j-1;
                        return;
                    }
                }
            }
        }
    }

    // compute ship arrangements possible for every cell, store in dPerms
    for(int i=0;i<Fleet_Size;i++)
        if(otherPlayer.ships[i].hitcount!=otherPlayer.ships[i].size)
            for(int j=0;j<10;j++)
                for(int k=0;k<10;k++)
                    dPerms[j][k]+=countShipPerms(otherPlayer,i,j,k);

    // set misses and sunk spots to 0
    for(int i=0;i<10;i++)
        for(int j=0;j<10;j++)
            if(otherPlayer.board[i][j]=='M'||otherPlayer.board[i][j]=='Z'
                    ||otherPlayer.board[i][j]=='H')
                dPerms[i][j]=0;


    // loop through dPerms, find max of four adjacent cells around a hit
    // next shot is cell with max possibile ship arrangements
    for(int i=0;i<10;i++)
    {
        for(int j=0;j<10;j++)
        {
            if(otherPlayer.board[i][j]=='H')
            {
                // check down
                if(i<9&&otherPlayer.board[i+1][j]!='M'
                        &&otherPlayer.board[i+1][j]!='Z'
                        &&otherPlayer.board[i+1][j]!='H')
                {
                    if(dPerms[i+1][j]>maxDPerms)
                    {
                        maxDPerms=dPerms[i+1][j];
                        row=i+1;
                        col=j;
                    }
                }

                // check up
                if(i>0&&otherPlayer.board[i-1][j]!='M'
                        &&otherPlayer.board[i-1][j]!='Z'
                        &&otherPlayer.board[i-1][j]!='H')
                {
                    if(dPerms[i-1][j]>maxDPerms)
                    {
                        maxDPerms=dPerms[i-1][j];
                        row=i-1;
                        col=j;
                    }
                }

                // check right
                if(j<9&&otherPlayer.board[i][j+1]!='M'
                        &&otherPlayer.board[i][j+1]!='Z'
                        &&otherPlayer.board[i][j+1]!='H')
                {
                    if(dPerms[i][j+1]>maxDPerms)
                    {
                        maxDPerms=dPerms[i][j+1];
                        row=i;
                        col=j+1;
                    }
                }

                // check left
                if(j>0&&otherPlayer.board[i][j-1]!='M'
                        &&otherPlayer.board[i][j-1]!='Z'
                        &&otherPlayer.board[i][j-1]!='H')
                {
                    if(dPerms[i][j-1]>maxDPerms)
                    {
                        maxDPerms=dPerms[i][j-1];
                        row=i;
                        col=j-1;
                    }
                }
            }
        }
    }

    //test---------------------------
        for(int i=0;i<10;i++)
        {
            for(int j=0;j<10;j++)
            {
                cout << setw(3) << dPerms[i][j];
            }
            cout << endl;
        }
        cout << endl;
     //test--------------------------

}

/*******************************************************************************
*
*  FUNCTION getCompShot
*_______________________________________________________________________________
*  This function will determine whether to use search or destroy functions
*_______________________________________________________________________________
*  PRE-CONDITIONS
*    otherPlayer: opposing player info
*
*  POST-CONDTIONS
*    This function will output the coordinates for the computer's shot
*******************************************************************************/
void getCompShot(PlayerBoard& otherPlayer,  // IN - opposing player info
                 int& row,                  // OUT - row coordinate
                 int& col)                  // OUT - col coordinate
{
    bool unsunkHits=false;  // unsunk hits, hits that are not part of sunk ship

    // if unsunk hits, destroy
    // if no unsunk hits, search
    for(int i=0;i<Fleet_Size;i++)
        if(otherPlayer.ships[i].hitcount!=otherPlayer.ships[i].size
                &&otherPlayer.ships[i].hitcount!=0)
            unsunkHits=true;

    if(unsunkHits==true)
        compDestroy(otherPlayer,row,col);
    else
        compSearch(otherPlayer,row,col);
}

/*******************************************************************************
*
*  FUNCTION compFire
*_______________________________________________________________________________
*  This function will update the player info based on the computer's shot
*_______________________________________________________________________________
*  PRE-CONDITIONS
*    otherplayer: opposing player info
*
*  POST-CONDTIONS
*    This function will update the boards based on the computer's shot
*    It will display messages for hits, misses and when a ship is sunk
*******************************************************************************/
void compFire(PlayerBoard& otherPlayer)  // IN - other player's info
{
    int row;  // row coordinate
    int col;  // col coordinate
    char r;   // used to convert int coordinate to char

    // get computer's shot
    getCompShot(otherPlayer,row,col);
    r='A'+row;
    cout << "Computer fires at " << r << " " << col+1 << endl;

    // detect hit
    if(otherPlayer.board[row][col]=='s')
    {
        cout << "Computer Hit!!!\n";
        otherPlayer.board[row][col]='H';

        // loop through all ships points to update hitcount
        // hits on sunk ships become (Z's)
        for(unsigned int i=0;i<Fleet_Size;i++)
        {
            for(unsigned int j=0;j<otherPlayer.ships[i].size;j++)
            {
                if(otherPlayer.ships[i].spots[j].col==col&&
                        otherPlayer.ships[i].spots[j].row==row)
                {
                    otherPlayer.ships[i].hitcount++;

                    if(otherPlayer.ships[i].hitcount==otherPlayer.ships[i].size)
                    {
                        cout << "Computer sunk the " << otherPlayer.ships[i].name
                             << "!!!\n";
                        for(int k=0;k<otherPlayer.ships[i].size;k++)
                            otherPlayer.board[otherPlayer.ships[i].spots[k].row]
                                    [otherPlayer.ships[i].spots[k].col]='Z';
                    }
                }
            }
        }
    }
    else
    {
        cout << "Computer Missed.\n";
        otherPlayer.board[row][col]='M';
    }
}

/*******************************************************************************
*
*  FUNCTION gameWon
*_______________________________________________________________________________
*  This function determines if a game is won
*_______________________________________________________________________________
*  PRE-CONDITIONS
*    player: player info
*
*  POST-CONDTIONS
*    This function will return true if the game is won
*******************************************************************************/
bool gameWon(PlayerBoard player)
{
    int hitScore=0;  // number of current hits
    int hitAll=0;    // all ships hit

    for(int i=0;i<Fleet_Size;i++)
        hitAll+=player.ships[i].size;

    for(int i=0;i<Fleet_Size;i++)
        hitScore+=player.ships[i].hitcount;

    // conditions for win
    if(hitScore==hitAll)
    {
        cout << "Fleet has been sunk!!!\n";
        return true;
    }
    return false;
}

