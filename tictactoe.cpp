/* 
 * File:   main.cpp
 * Author: Alvin Lin
 *
 * Created on July 29, 2013, 9:40 AM
 */
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <iostream>
#include <sstream>
#include <string>
#include <ctime>

using namespace std;

class TTT {
public:
    //Checks for victory
    char victoryCheck() {
        //Rows
        for (int i = 0; i <= 6; i += 3) {
            if ((grid[i] == grid[i + 1] && grid[i] == grid[i + 2]) && grid[i] != ' ') {
                return grid[i];
            }
        }
        //Columns
        for (int i = 6; i <= 8; i++) {
            if ((grid[i] == grid[i - 3] && grid[i] == grid[i - 6]) && grid[i] != ' ') {
                return grid[i];
            }
        }
        //Diagonals
        if (((grid[0] == grid[4] && grid[0] == grid[8]) || (grid[2] == grid[4] && grid[2] == grid[6])) && grid[4] != ' ') {
            return grid[4];
        }
        return ' ';
    }
    //Check is a move is valid
    bool isValidMove(int move) {
        switch (move) {
            case 1: if (grid[0] == ' ') {
                    return true;
                }
                break;
            case 2: if (grid[1] == ' ') {
                    return true;
                }
                break;
            case 3: if (grid[2] == ' ') {
                    return true;
                }
                break;
            case 4: if (grid[3] == ' ') {
                    return true;
                }
                break;
            case 5: if (grid[4] == ' ') {
                    return true;
                }
                break;
            case 6: if (grid[5] == ' ') {
                    return true;
                }
                break;
            case 7: if (grid[6] == ' ') {
                    return true;
                }
                break;
            case 8: if (grid[7] == ' ') {
                    return true;
                }
                break;
            case 9: if (grid[8] == ' ') {
                    return true;
                }
                break;
        }
        return false;
    }
    //Assigns a value to place on the matrix
    void move(int move, char assign) {
        grid[move-1] = assign;
    }
    //Outputs the array as it is
    void output(string mode, string headmessage, string footmessage = "Enter a valid move. Type 0 to quit.") {
        cout << string(50, '\n');
        if(mode == "1") {
            cout << "Single Player - Easy Difficulty   " << endl;
        }
        else if(mode == "2") {
            cout << "Single Player - Hard Difficulty   " << endl;
        }
        else {
            cout << "Two player - Battle               " << endl;
        }
        cout << headmessage << endl << endl;
        cout << "                                 Grid numbers:" << endl;
        cout << "   |   |   " << "                       " << "   |   |   " << endl;
        cout << " " << grid[6] << " | " << grid[7] << " | " << grid[8] << " " << "                       " << " 7 | 8 | 9 " << endl;
        cout << "   |   |   " << "                       " << "   |   |   " << endl;
        cout << "___________" << "                       " << "___________" << endl;
        cout << "   |   |   " << "                       " << "   |   |   " << endl;
        cout << " " << grid[3] << " | " << grid[4] << " | " << grid[5] << " " << "                       " << " 4 | 5 | 6 " << endl;
        cout << "   |   |   " << "                       " << "   |   |   " << endl;
        cout << "___________" << "                       " << "___________" << endl;
        cout << "   |   |   " << "                       " << "   |   |   " << endl;
        cout << " " << grid[0] << " | " << grid[1] << " | " << grid[2] << " " << "                       " << " 1 | 2 | 3 " << endl;
        cout << "   |   |   " << "                       " << "   |   |   " << endl;
        cout << endl << footmessage << endl;
    }
    //Clear grid
    void resetGrid() {
        for (int i = 0; i < 9; i++) {
            grid[i] = ' ';
        }
    }
    //Easy AI
    int EasyAIMove() {
        int move = (rand() % 9) + 1;
        while (!isValidMove(move)) {
            move = (rand() % 9) + 1;
        }
        return move;
    }
    //Hard AI
    int HardAIMove(int playermove) {
        //If it can win, then it will play the move to win.
        for (int i = 1; i <= 9; i++) {
            if (isValidMove(i)) {
                move(i, 'O');
                if (victoryCheck() == 'O') {
                    move(i, ' ');
                    return i;
                }
                move(i, ' ');
            }
        }
        //If it is going to lose, then it will block the spot.
        for (int i = 1; i <= 9; i++) {
            if (isValidMove(i)) {
                move(i, 'X');
                if (victoryCheck() == 'X') {
                    move(i, ' ');
                    return i;
                }
                move(i, ' ');
            }
        }
        //Counts the moves on the board
        int movecount = 0;
        for (int i = 0; i < 9; i++) {
            if (grid[i] != ' ') {
                movecount++;
            }
        }
    //Figures out what to do depending on how many moves are on the board
        if (movecount == 1) {
            //Records the player's first move
            pmove1 = playermove;
            //Plays the center square if available and records the player's move
            if (playermove != 5) {
                return 5;
            }
            //Plays a random corner if the center square is taken
            else {
                switch (rand() % 4) {
                    case 0: return 1;
                    case 1: return 3;
                    case 2: return 7;
                    case 3: return 9;
                }
            }
        }
    else if (movecount == 3) {
            //Records the player's second move
            pmove2 = playermove;
            //Adjacent Edges - Double win situation
            //If the opposite edge is played, then a random move will be picked (center square taken)
            if (isEdge(pmove2) && isEdge(pmove1)) {
                if ((pmove1 == 2 && pmove2 == 4) || (pmove1 == 4 && pmove2 == 2)) {
                    return 1;
                }
        else if ((pmove1 == 4 && pmove2 == 8) || (pmove1 == 8 && pmove2 == 4)) {
                    return 7;
                }
        else if ((pmove1 == 8 && pmove2 == 6) || (pmove1 == 6 && pmove2 == 8)) {
                    return 9;
                }
        else if ((pmove1 == 6 && pmove2 == 2) || (pmove1 == 2 && pmove2 == 6)) {
                    return 3;
                }
        else {
                    int move = (rand() % 9) + 1;
                    while (!isValidMove(move)) {
                        move = (rand() % 9) + 1;
                    }
                    return move;
                }
            }
            //Opposite corners - Double win situation
            //Adjacent corners are automatically handled by victory precheck
            else if (isCorner(pmove1) && isCorner(pmove2)) {
                //Play any edge
                switch(rand()%4) {
                    case 0: return 2;
                    case 1: return 4;
                    case 2: return 6;
                    case 3: return 8;
                }
            }
            //Center-corner - Double win situation
            else if (isCenter(pmove1) && isCorner(pmove2)) {
                if (pmove2 == 1 || pmove2 == 9) {
                    switch(rand()%2) {
                        case 0: return 3;
                        case 1: return 7;
                    }
                }
        else if (pmove2 == 3 || pmove2 == 7) {
                    switch(rand()%2) {
                        case 0: return 1;
                        case 1: return 9;
                    }
                }
            }
      //Corner-non-adjacent-edge - Double win situation
      //Adjacent edge scenario is automatically handled by victory precheck
      else if (isCorner(pmove1) && isEdge(pmove2)) {
        if (pmove1 == 1 && (pmove2 == 6 || pmove2 == 8)) {
          switch(pmove2) {
            case 6: return 2;
            case 8: return 4;
          }
        }
        else if (pmove1 == 3 && (pmove2 == 4 || pmove2 == 8)) {
          switch(pmove2) {
            case 4: return 2;
            case 8: return 6;
          }
        }
        else if (pmove1 == 7 && (pmove2 == 2 || pmove2 == 6)) {
          switch(pmove2) {
            case 2: return 4;
            case 6: return 8;
          }
        }
        else if (pmove1 == 9 && (pmove2 == 2 || pmove2 == 4)) {
          switch(pmove2) {
            case 2: return 6;
            case 4: return 8;
          }
        }
        //Random move - Exception catch
        else {
                    int move = (rand() % 9) + 1;
                    while (!isValidMove(move)) {
                        move = (rand() % 9) + 1;
                    }
                    return move;
                }
      }
            //Plays a random move for all non-win scenarios that aren't handled by precheck
            else {
                int move = (rand() % 9) + 1;
                while (!isValidMove(move)) {
                    move = (rand() % 9) + 1;
                }
                return move;
            }
        } else {
            int move = (rand() % 9) + 1;
            while (!isValidMove(move)) {
                move = (rand() % 9) + 1;
            }
            return move;
        }
    }
    //Checks for edge
    bool isEdge(int move) {
        if (move == 2 || move == 4 || move == 6 || move == 8) {
            return true;
        } else {
            return false;
        }
    }
    //Checks for corner
    bool isCorner(int move) {
        if (move == 1 || move == 3 || move == 7 || move == 9) {
            return true;
        } else {
            return false;
        }
    }
    //Checks for center
    bool isCenter(int move) {
        if (move == 5) {
            return true;
        } else {
            return false;
        }
    }
private:
    char grid[9];
    int pmove1;
    int pmove2;
};
//Outputs 50 newlines to flush current text
void spacer() {
    cout << string(50, '\n');
}
//Waits a certain amount of time
void wait(float time) {
    clock_t temp = clock() + time * CLOCKS_PER_SEC;
    while (clock() < temp) {}
}
int main(int argc, char** argv) {
    
    TTT board;
    //Seeding the random number generator
    srand(time(NULL));
    //Blank string for pause
    string pause;
    string singleplayerheader = "You play as X and the computer plays as O.";
    string singleplayerAIthink = "Thinking...";
    //Menu to select mode of play
    spacer();
    cout << "Welcome to TicTacToe.";
    while (true) {
        board.resetGrid();
        beginning: cout << "Please select a mode of play:" << endl;
        cout << "1. Single player - Easy Difficulty" << endl;
        cout << "2. Single player - Hard Difficulty" << endl;
        cout << "3. Two player - Battle" << endl;
        cout << "4. Exit" << endl;
        string mode;
        getline(cin, mode);
        if (mode == "1") {
            //Outputs grid at beginning
            board.output(mode, singleplayerheader);
            char turn = 'X';
            int drawcounter = 0;
            //Stops turn and move loop when a player wins or there is a draw
            while (board.victoryCheck() == ' ' && drawcounter != 9) {
                //Turn rotation
                if (turn == 'X') {
                    //Input verification
                    string input;
                    int move;
                    while (true) {
                        getline(cin, input);
                        move = atoi(input.c_str());
                        if (input == "0") {
                            spacer();
                            goto beginning;
                        }
                        if (input.length() == 1 && move >= 1 && move <= 9 && board.isValidMove(move)) {
                            break;
                        } else {
                            board.output(mode, singleplayerheader, "Invalid move. Please enter a valid move or type 0 to quit.");
                        }
                    }
                    board.move(move, turn);
                    board.output(mode, singleplayerheader);
                    turn = 'O';
                } else {
                    //Easy AI Move
                    board.output(mode, singleplayerAIthink, singleplayerAIthink);
                    wait(rand()%4 + 1);
                    board.move(board.EasyAIMove(), turn);
                    board.output(mode, singleplayerheader);
                    turn = 'X';
                }
                drawcounter++;
            }
            if (board.victoryCheck() == 'X') {
                board.output(mode, "Congratulations! You won!", "You won! Enter anything to return to the main menu.");
            } else if (board.victoryCheck() == 'O') {
                board.output(mode, "Aw, you lost. Better luck next time.", "You lost to a computer playing random moves... Enter anything to return to the main menu.");
            } else {
                board.output(mode, "Draw! Good game!", "Draw! Enter anything to return to the main menu.");
            }
            getline(cin, pause);
            spacer();
        } else if (mode == "2") {
            //Outputs grid at beginning
            board.output(mode, singleplayerheader);
            char turn = 'X';
            int drawcounter = 0;
            //Stops turn and move loop when a player wins or there is a draw
            while (board.victoryCheck() == ' ' && drawcounter != 9) {
                //Input variables
                string input;
                int playermove;
                //Turn rotation
                if (turn == 'X') {
                    //Input verification
                    while (true) {
                        getline(cin, input);
                        playermove = atoi(input.c_str());
                        if (input == "0") {
                            spacer();
                            goto beginning;
                        }
                        if (input.length() == 1 && playermove >= 1 && playermove <= 9 && board.isValidMove(playermove)) {
                            break;
                        } else {
                            board.output(mode, singleplayerheader, "Invalid move. Please enter a valid move or type 0 to quit.");
                        }
                    }
                    board.move(playermove, turn);
                    board.output(mode, singleplayerheader);
                    turn = 'O';
                } else {
                    //Hard AI Move
                    board.output(mode, singleplayerAIthink, singleplayerAIthink);
                    wait(rand()%4 + 1);
                    board.move(board.HardAIMove(playermove), turn);
                    board.output(mode, singleplayerheader);
                    turn = 'X';
                }
                drawcounter++;
            }
            if (board.victoryCheck() == 'X') {
                board.output(mode, "Congratulations! You won!", "You won! Enter anything to return to the main menu.");
            } else if (board.victoryCheck() == 'O') {
                board.output(mode, "Aw, you lost. Better luck next time.", "You lost! Enter anything to return to the main menu.");
            } else {
                board.output(mode, "Draw! Good game!", "Draw! Enter anything to return to the main menu.");
            }
            getline(cin, pause);
            spacer();
        }
        else if(mode == "3") {
            //Gets player names
            spacer();
            string player1, player2;
            cout << "Player 1: Enter your name. You will move first." << endl;
            getline(cin, player1);
            cout << "Player 2: Enter your name. You will move second." << endl;
            getline(cin, player2);
            //Puts names in header and turn messages
            string twoplayerheader = player1;
            twoplayerheader.append(" is playing as X, ");
            twoplayerheader.append(player2);
            twoplayerheader.append(" is playing as O.");
            string player1turn = player1, player2turn = player2;
            player1turn.append("'s turn. Enter a valid move or type 0 to quit.");
            player2turn.append("'s turn. Enter a valid move or type 0 to quit.");
            //Establishes a player as X and O.
            cout << twoplayerheader << " Enter anything to continue." << endl;
            getline(cin, pause);
            spacer();
            //Sets up turns
            char turn = 'X';
            int drawcounter = 0;
            board.output(mode, twoplayerheader, player1turn);
            //Stops turn and move loop when a player wins or there is a draw
            while (board.victoryCheck() == ' ' && drawcounter != 9) {
                //Input verification
                string input;
                int move;
                while (true) {
                    getline(cin, input);
                    move = atoi(input.c_str());
                    if (input == "0") {spacer(); goto beginning;}
                    if (input.length() == 1 && move >= 1 && move <= 9 && board.isValidMove(move)) {
                        break;
                    } else {
                        if(turn == 'X') {
                            board.output(mode, "Invalid move. Please enter a valid move.", player1turn);
                        }
                        else {
                            board.output(mode, "Invalid move. Please enter a valid move.", player2turn);
                        }
                    }
                }
                //Turn-based moving
                board.move(move, turn);
                if(turn == 'X') {
                    board.output(mode, twoplayerheader, player2turn);
                    turn = 'O';
                } else {
                    board.output(mode, twoplayerheader, player1turn);
                    turn = 'X';
                }
                drawcounter++;
            }
            //Outputs victory message and pauses before return to the main menu.
            
            if (board.victoryCheck() == 'X') {
                player1.append(" won!");
                board.output(mode, player1, "Enter anything to return to the main menu.");
            } else if (board.victoryCheck() == 'O'){
                player2.append(" won!");
                board.output(mode, player2, "Enter anything to return to the main menu.");
            } else {
                board.output(mode, "Draw! Good game!", "Enter anything to return to the main menu.");
            }
            getline(cin, pause);
            spacer();
        } else if (mode == "4") {
            return 0;
        } else {
            spacer();
            cout << "Invalid game mode. ";
        }
    }
}
