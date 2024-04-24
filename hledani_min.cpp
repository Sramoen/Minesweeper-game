#include "Board.h"

void set_difficult_level(int &shape,int &number_of_mines){
    cout << "Choose difficulty level: beginner, intermediate or expert."<<endl;
    string level;
    while(true){
        getline(cin, level);
        if (level=="beginner"){
            shape = 5;
            number_of_mines = 5;
            Board();
            break;
        }
        else if (level=="intermediate"){
            shape = 10;
            number_of_mines = 10;
            Board();

            break;
        }
        else if (level=="expert"){
            shape = 15;
            number_of_mines = 40;
                        Board();

            break;
        }
        else{
            cout << "Write one of the following level: beginner, intermediate or expert."<<endl; 
        }
    }

}


int main()
{   int shape, number_of_mines;
    set_difficult_level(shape,number_of_mines);
    Board board(shape,number_of_mines);
    board.play_game();
    return 0;
}