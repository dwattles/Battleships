# include "header.h"

int main()
{
    int mode;          // INPUT - 1 for vs player or 0 for vs comp
    int turn;            // OUTPUT - 1 turn is 1 player move
    char temp[10][10];   // temporary grid for displaying board w/ hidden ships
    int playAgain;     // INPUT - 1 to play again

    PlayerBoard player1; // INPUT,OUTPUT - contains player1 info
    PlayerBoard player2; // INPUT,OUTPUT - contains player2 info

    // initialize ship sizes and names
    initFleet(player1);
    initFleet(player2);

    // seed rand function with time
    srand(time(NULL));

    // loop to keep playing new games until player quits
    while(true)
    {
        mode=2;
        turn=1;

        // menu to select mode
        startMenu(mode);

        // player vs player mode
        if(mode==1)
        {
            // initialize boards pvp mode
            initBoard(player1,player2);

            // loop while game is not won
            while(true)
            {
                // player1 turn
                if(turn%2==1)
                {
                    cout << endl << endl << endl;
                    cout << "Player 1: \n";

                    // get player1 to fire shot at player2 board
                    // hide opposing ships in display
                    // display boards player 1 perspective
                    fire(player2);
                    hideShips(player2,temp);
                    cout << setw(26) << "Player 1" << setw(52) << "Player 2\n";
                    displayBoards(player1.board,temp);
                }
                // player2 turn
                else
                {
                    cout << endl << endl << endl;
                    cout << "Player 2: \n";

                    // get player2 to fire shot at player1 board
                    // hide opposing ships in display
                    // display boards player2 perspective
                    fire(player1);
                    hideShips(player1,temp);
                    cout << setw(26) << "Player 2" << setw(52) << "Player 1\n";
                    displayBoards(player2.board,temp);
                }

                // condition to end game
                if(gameWon(player1)==true||gameWon(player2)==true)
                    break;

                turn++;
            }

            // ending display
            if(turn%2==1)
                cout << "Congratulations Player 1!!!\n";
            else
                cout << "Congratulations Player 2!!!\n";
            cout << "Turns taken " << (turn+1)/2 << endl;
        }

        // vs comp
        if(mode==0)
        {
            // initialize ship positions player vs comp
            initBoard2(player1,player2);

            // loop while game isn't won
            while(true)
            {
                // player1 turn
                if(turn%2==1)
                {
                    cout << endl << endl << endl;
                    cout << "Player 1: \n";

                    // get player1 to fire shot at comp's board
                    // hide opposing ships in display
                    // display boards player1 perspective
                    fire(player2);
                    hideShips(player2,temp);
                    cout << setw(26) << "Player 1" << setw(53) << "Computer\n";
                    displayBoards(player1.board,temp);
                }
                // comp's turn
                else
                {
                    cout << endl << endl << endl;
                    cout <<"Player 1: \n";

                    // computer fires shot
                    // hide opposing ships in display
                    // display boards player1 perspective
                    compFire(player1);
                    hideShips(player2,temp);
                    cout << setw(26) << "Player 1" << setw(53) << "Computer\n";
                    displayBoards(player1.board,temp);
                }
//                displayBoards(player1.board,player2.board); // test!!

                // exit condition for game loop
                if(gameWon(player1)==true||gameWon(player2)==true)
                    break;

                turn++;
            }

            // ending display
            if(turn%2==1)
                cout << "Congratulations Player 1!!!\n";
            else
                cout << "Computer Wins!!!\n";
            cout << "Turns taken " << (turn+1)/2 << endl << endl;
        }

        // if player wants to play again
        // player info might not be updating properly, check vectors w/ship info
        // reset info that will not be reset in functions
        cout << "Enter 1 to play again or 0 to quit\n";
        cin >> playAgain;
        if(!playAgain)
            break;
        else
        {
            for(int i=0;i<Fleet_Size;i++)
            {
                player1.ships[i].hitcount=0;
                player2.ships[i].hitcount=0;
            }
        }
    }
    cout << "****************************************\n";
    cout << " Programmed by : Dylan Wattles\n";
    cout << " Student ID    : 10245608\n";
    cout << " CS2           : MTWR - 7:30a-12:30p\n";
    cout << " Final Project : Battleship\n";
    cout << "****************************************\n";

    return 0;
}
