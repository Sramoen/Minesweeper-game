#include "Board.h"


//Konstruktor bez parametru
Board::Board(){
    shape = 10;
    number_of_mines = 10;
    board = new char*[shape];
    
    for (int i = 0; i < shape; ++i) {
        board[i] = new char[shape];
    }

    for (int i = 0; i < shape; ++i) {
        for (int j = 0; j < shape; ++j) {
            board[i][j] = '-';
        }
    }

    set_mines();
    };

// konstruktor s parametrem
Board::Board(int s,int n){
    shape =s;
    number_of_mines = n;

    board = new char*[shape]; 
    
    for (int i = 0; i < shape; ++i) {
        board[i] = new char[shape];
    }

    for (int i = 0; i < shape; ++i) {
        for (int j = 0; j < shape; ++j) {
            board[i][j] = '-';
        }
    }

    set_mines();
    };
//Destruktor
Board::~Board() {
        for (int i = 0; i < shape; ++i) {
            delete[] board[i];
        }

        delete[] board;
};

void Board::print_Board() {

    cout << setw(3) << " ";
    for (int j = 0; j < shape; ++j) {
        cout << setw(3) << j;
    }
    cout << endl;
    for (int i =0; i < shape;i++) {
        cout << setw(3) << i;
        for (int j =0; j < shape;j++) {
                if ((board[i][j] == '*') &&(!game_over))
                {
                    cout << setw(3)<<'-'; //Změnit na '-' při netestovní
                    continue;
                } 
                cout << setw(3)<<board[i][j];
        }
        cout << endl;
    }
};

void Board::set_mines(){
        // Nahodne rozhodi miny po plose
    random_device rd;
    mt19937 rng(time(nullptr));
    uniform_int_distribution<int> dis(0, shape-1);
    int i =0;
    while(i<number_of_mines){
        int x= dis(rng);
        int y = dis(rng);
        if (board[x][y] == '*'){
            continue;
        }
        board[x][y] = '*';
        i++;
    }
};

// hlavni loop na hrani hry
void Board::play_game(){
    while(!game_over){
        int x,y;
        print_Board(); //tiks plochy
        get_users_move(x,y);    // tah uzivatele

        make_move(x,y); //provedeni tahu uzivatele
        if (game_over){ //kontrola konce hry
            print_Board();
        }
    }
};

//zisk tahu uzivatele
void Board::get_users_move(int &x, int &y){
    while (true){
        string move;
        cout << "Write row and column of your move:" << endl;
        getline(cin, move);
        istringstream iss(move);
        if (!(iss >> x >> y)) {
            std::cout << move << std::endl;

            cout << "Invalid input. Please enter two integers separated by a space." << std::endl;
            continue;
        }
        if ((x >= shape) || (y>=shape) || (x < 0) || (y<0)){
            cout << "Invalid input. Integers are larger (smaller) than board." << std::endl;
            continue;
        }
        break;
        }
        return;
};

//Nahrazeni miny pokud na ji uzivatel odhaly v prvnim tahu
void Board::replace_mine(int x, int y){
    random_device rd;
    mt19937 rng(time(nullptr));
    uniform_int_distribution<int> dis(0, shape-1);
    int x_new_bomb,y_new_bomb;
    while (true) 
    {
        x_new_bomb= dis(rng);
        y_new_bomb = dis(rng);
        if (board[x_new_bomb][y_new_bomb] != '*'){
            board[x_new_bomb][y_new_bomb]='*';
            cout << x_new_bomb << y_new_bomb<<endl;
            board[x][y] = '-';
            break;
        }
    }
}

//Proved tah na plose a vyhodnoceni jestli konce hry
void Board::make_move(int x, int y)
{
    if ((board[x][y] == '*') & (move!=0)){
        cout << "You loose!"<<endl;
        game_over = true;
        move++;
        return;
    }
    else if((board[x][y] == '*') & (move!=0)){
        replace_mine(x,y);
    }
    int depth = 0;
    count_mines_around(x,y,depth);
    if (anyunreveald_left()){
        game_over = false;
        move++;
        return;
    }
    cout<<"You won" << endl;
    game_over = true;
    move++;
    return;
};

// vypocet rekurzivni odhalenych poli
void Board::count_mines_around(int x, int y,int depth)
{
    int dx[] = {-1,0,1,1,1,0,-1,-1};
    int dy[] = {1,1,1,0,-1,-1,-1,0};
    int sum;
    if (board[x][y] != '-')
         {   
            return;
         }
    for (int i = 0;i<sizeof(dx) / sizeof(dx[0]);i++){
        sum = count_mines_in_position(x,y);
        if(sum && !depth && move){
            return;
        }
        if ((x+dx[i] >= shape) || (y+dy[i]>=shape) || (x+dx[i] < 0) || (y+dy[i]<0)){
            continue;
        }
        if ((depth >=1)&(!sum)){
            count_mines_around(x+dx[i],y+dy[i],depth+1);
            
        }
        else if(depth==0){
            count_mines_around(x+dx[i],y+dy[i],depth+1);
        }
    }
};

// vypocet poctu min v konkretni pozici
int Board::count_mines_in_position(int x,int y){
    int dx[] = {-1,0,1,1,1,0,-1,-1};
    int dy[] = {1,1,1,0,-1,-1,-1,0};
    int sum  =0;
    for (int i = 0;i<sizeof(dx) / sizeof(dx[0]);i++) {
        if ((x+dx[i] >= shape) || (y+dy[i]>=shape) || (x+dx[i] < 0) || (y+dy[i]<0)){
            continue;
        }
            if (board[dx[i]+x][dy[i]+y] == '*'){
                sum++;
            }
        };
    board[x][y] = '0'+sum;
    return sum;
}

//Kontrola jestli uzivatel odhalil vse
bool Board::anyunreveald_left() {
    for (int i = 0; i < shape; ++i) {
        for (int j = 0; j < shape; ++j) {
            if (board[i][j] == '-') {
                return true; 
            }
        }
    }
    return false;
}

char Board::get_value(int x, int y){
    return board[x][y];
}

bool Board::get_game_state(){
    return game_over;
}

void Board::restart(){
    for (int i = 0; i < shape; ++i) {
        delete[] board[i];
    }
    delete[] board;

    // Allocate new memory for the board and initialize it
    board = new char*[shape]; 
    for (int i = 0; i < shape; ++i) {
        board[i] = new char[shape];
        for (int j = 0; j < shape; ++j) {
            board[i][j] = '-';
        }
    }

    // Set mines for the new board
    set_mines();
    move = 0;
    game_over = false;
}


