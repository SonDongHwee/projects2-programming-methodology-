#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
#include <vector>
#include <algorithm>
using namespace std;
const int TILE_SIZE = 16;
const int TILE_BOARD_LENGTH = 4;
const int NUM_CHANCE_TYPE = 2;
const int NUM_CHANCE_1 = 2;
const int NUM_CHANCE_2 = 2;
const int ROUNDS = 5;
const char BOARD_FRONT[TILE_BOARD_LENGTH][TILE_BOARD_LENGTH] = {{'A', 'B', 'C', 'D'}, {'E', 'F', 'G', 'H'}, {'I', 'J', 'K', 'L'}, {'M', 'N', 'O', 'P'}};

const int NUM_POSSIBLE_NUM = 12;
const int NUM_POSSIBLE_OP = 4;
const string POSSIBLE_NUM[NUM_POSSIBLE_NUM] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12"};
const string POSSIBLE_OP[NUM_POSSIBLE_OP] = {"+", "-", "x", "/"};

class Board
{
public:
    // A Constructor of the Board class.
    // Initialze class with pair<char, string> tiles
    // @param board_front:  The front-side of the board (Use global variable BOARD_FRONT)
    // @param board_back:  The back-side of the board (2D string array, read from Tiles.txt )
    Board(const char board_front[][TILE_BOARD_LENGTH], string board_back[][TILE_BOARD_LENGTH]);

    // Fuction for getting number or operation corresponding the input alphabet
    // @param alphabet: Player's input alphabet
    // @return (string type) number or operation corresponding to alphabet
    string get_num_from_back(char alphabet) const;

    // Function for printing front-side of the board.
    void print_front() const;

    // Function for printing front-side of the board except one tile.
    // @param alphabet: Player's input alphabet
    void print_one_flipped(char alphabet) const;

    // Function for printing back-side of the board
    void print_back() const;

    // Function for advanced version, this function changes the board corresponding to input_alphabets array
    // Using POSSIBLE_NUM / POSSIBLE_OP  array, change the board.
    // @param input_alphabets: (char type) array which saves input alphabets [correct equation]
    // @param arr_size: (int type) size for input_alphabets array
    // Do not fix it
    void change_board(char input_alphabets[], int arr_size);

private:
    pair<char, string> tiles[TILE_BOARD_LENGTH][TILE_BOARD_LENGTH];
};

Board::Board(const char board_front[][TILE_BOARD_LENGTH], string board_back[][TILE_BOARD_LENGTH]){
    for(int i=0;i<TILE_BOARD_LENGTH;i++){
        for(int j=0;j<TILE_BOARD_LENGTH;j++){
            tiles[i][j].first = board_front[i][j];
            tiles[i][j].second = board_back[i][j];
        }
    }
}
void Board::change_board(char input_alphabets[], int input_size)
{
    for (int k = 0; k < input_size; k++)
    {
        for (int i = 0; i < TILE_BOARD_LENGTH; i++)
        {
            for (int j = 0; j < TILE_BOARD_LENGTH; j++)
            {
                if (input_alphabets[k] == tiles[i][j].first)
                {
                    if ((tiles[i][j].second == "+") || (tiles[i][j].second == "-") || (tiles[i][j].second == "x") || (tiles[i][j].second == "/"))
                    {
                        tiles[i][j].second = POSSIBLE_OP[rand() % NUM_POSSIBLE_OP];
                    }
                    else
                    {
                        tiles[i][j].second = POSSIBLE_NUM[rand() % NUM_POSSIBLE_NUM];
                    }
                }
            }
        }
    }
}
string Board::get_num_from_back(char alphabet) const{
    for(int i=0;i<TILE_BOARD_LENGTH;i++){
        for(int j=0;j<TILE_BOARD_LENGTH;j++){
            if(tiles[i][j].first == alphabet)
                return tiles[i][j].second;
        }
    }
    return " ";
}
void Board::print_front() const{
    for (int i = 0; i < TILE_BOARD_LENGTH; i++)
    {
        cout << "| ";
        for (int j = 0; j < TILE_BOARD_LENGTH; j++)
        {
            
            cout << BOARD_FRONT[i][j] << "  | ";
            
        }
        cout << endl;
    }
}
void Board::print_back() const{
    for (int i = 0; i < TILE_BOARD_LENGTH; i++)
    {
        cout << "| ";
        for (int j = 0; j < TILE_BOARD_LENGTH; j++)
        {
            if (tiles[i][j].second.size() == 1)
            {
                cout << tiles[i][j].second << "  | ";
            }
            else
            {
                cout << tiles[i][j].second << " | ";
            }
        }
        cout << endl;
    }
}
void Board::print_one_flipped(char alphabet) const{
    for (int i = 0; i < TILE_BOARD_LENGTH; i++)
    {
        cout << "| ";
        for (int j = 0; j < TILE_BOARD_LENGTH; j++)
        {
            if(BOARD_FRONT[i][j] == alphabet){
                if (tiles[i][j].second.size() == 1)
                {
                    cout << tiles[i][j].second << "  | ";
                }
                else
                {
                    cout << tiles[i][j].second << " | ";
                }
            }else{
                cout << BOARD_FRONT[i][j] << "  | ";
            }
        }
        cout << endl;
    }
}

class Player
{
public:
    // A Constructor of the Player class.
    // Initialze chance_count array and score=0.
    Player();

    // Function for adding player's score.
    // @param chance_type: (int type) type of chance (1,2,3).
    void add_score(int chance_type);

    // Function for reducing the remaining number of specific chance type.
    // If chance is used, reduce the remaining chance count.
    // @param chance_type: (int type) type of chance (1,2,3).
    void reduce_chance_count(int chance_type);

    // Function for getting score.
    int get_score() const;

    // Function for printing remaining chance list.
    void print_remaining_chance_list() const;

    // Function for checking the specific chance is remained.
    // @param chance_type: (int type) type of chance (1,2,3).
    bool has_remaining_chance(int chance_type) const;

private:
    int chance_count[NUM_CHANCE_TYPE];
    int score;
};
Player::Player() : score(0){
    chance_count[0] = NUM_CHANCE_1;
    chance_count[1] = NUM_CHANCE_2;
}
void Player::add_score(int chance_type){
    if(chance_type==3)
        score += 2;
    else 
        score += 1;
}
int Player::get_score() const{
    return score;
}
void Player::print_remaining_chance_list() const{
    cout << "Chance 1:" << chance_count[0] << ",  " << "Chance 2:" << chance_count[1] <<  ",  " << "Chance 3:" << " unlimited" << endl;
}
bool Player::has_remaining_chance(int chance_type) const{
    if(chance_type == 3)
        return true;
    if(chance_count[chance_type-1]>0)
        return true;
    else   
        return false;
}

class Simple_Calculator
{
public:
    // Function that converts the operands from string to number
    //  and handles either input formula of length 3 or 5
    // Implement the length 3/5 formula calculation utilizing the arithmetic_op function
    // @param input[] : (string type) the player's given input
    // @param input_size : (int type) the length of the input
    // @return : The calculation outcome for either input of size 3 or 5.
    float calculate(string input[], int input_size) const;

    // Function that executes the arithmetic operation with the given inputs
    // @param operand : (float type) operand number
    // @param op : (string type) operator (+,-,*,/)
    // @return : The calculation outcome of the "operand1 op operand2 "
    float arithmetic_op(float operand1, float operand2, string op) const;

    // Function that verifies if the input number is integer.
    // @param number : (float type) number to verify if it is integer
    // @return : true if the number is integer, false if it is not.
    bool is_integer(float number) const;
};

class Game
{
public:
    // A Constructor of the Game class.
    // Initialze board class object and current_player_idx=0
    // @param board_front:  The front-side of the board (Use global variable BOARD_FRONT)
    // @param board_back:  The back-side of the board (2D string array, Read from Tiles.txt )
    Game(const char board_front[][TILE_BOARD_LENGTH], string board_back[][TILE_BOARD_LENGTH]);

    // Function for running the game.
    // 1) Choosing the game type [1,2]
    // 2) Start round
    //   2-1) Generate target number and verify whether it is valid or not. Only valid target
    //   number can be used in the game.
    //   2-2) Print the back-side of the board for 5 seconds.
    //   2-3) Loop play_turn until round is done.
    // 3) print final results and game is done.
    void run();

    // Function for playing each turn.
    // @return true if round is done.
    // 1) Chance-selecting step [0: no use chance, 1: skip this turn, 2: show back, 3: Double chance]
    // 2) Tile-selecting step
    // 3) Result evaluation step
    bool play_turn();

    // Function for printing the final results.
    void print_final_result() const;

    // Function for generating the target number.
    // Do not fix it
    void generate_target_num();

    // Function that finds all possible natural numbers  using numbers and operators in the current board
    // and compares with the target number.
    // @param target_num: (int type) target number generated from generate_target_num()
    // @return true if target number is valid
    bool verify_target_num(int target_num) const;

private:
    int game_type;
    int current_player_idx;
    Player players[2];
    Board board;
    Simple_Calculator calculator;
    int round;
    int target_num;
};

void Game::generate_target_num()
{
    int min = 1;
    int max = 100;
    static const double fraction = 1.0 / (RAND_MAX + 1.0);
    target_num = min + static_cast<int>((max - min + 1) * (rand() * fraction));
}

int main(void)
{
    ifstream ifs("Tile.txt");
    if (ifs.fail())
    {
        cout << "Input tile text not found! Quitting..." << endl;
        exit(1);
    }
    //      IMPLEMENT FROM HERE (Read Tile.txt)
    string board_back[TILE_BOARD_LENGTH][TILE_BOARD_LENGTH];
    for (int i = 0; i < 16; i++)
    {
        ifs >> board_back[i / 4][i % 4];
    }
    ifs.close();
    //Game game=Game(BOARD_FRONT,board_back);
    //      game.run();
    //	cout << "Thanks for playing the game!" << endl;
    return 0;
}
