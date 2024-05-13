#include <iostream>
#include <random>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>
#include <ctime>

using namespace std;


class Board
{
    private:
        int shape; // velikost hracího pole
        int number_of_mines; // pocet min
        char **board; // hrací pole
        bool game_over = false; // konec hry
        int move=0; // tah

    public:
        Board(); // Konstruktor
        Board(int s,int n); // konstruktor s parametry
        //Destruktor
        ~Board();

        void print_Board(); //tisk hracího pole

        void set_mines(); // inicializace min

        void play_game(); // Hlavní metoda na spuštění hry

        bool check_move(string move);   //kontrola tahu uzivatel
        void make_move(int x, int y); // provede tah na hrací plose
        void count_mines_around(int x, int y,int depth); // ukaze kolik kde min po tahu uzivatele

        int count_mines_in_position(int x, int y); // vypocita kolik je min kolem daného x,y
        bool anyunreveald_left(); // kontroluje konec hry - jestli uz vsechna pole odhalena
        void replace_mine(int x, int y); // pokud prvni tah a uzivatel odhali minu, funkce minu da jinam
        void get_users_move(int &x, int &y);    // zisk uzivatelskeho tahu
        char get_value(int x, int y);
        bool get_game_state();
        void restart();
};