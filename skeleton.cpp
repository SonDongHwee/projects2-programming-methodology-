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
    if((chance_type == 3) || (chance_type == 0))
        return true;
    if(chance_count[chance_type-1]>0)
        return true;
    else   
        return false;
}
void Player::reduce_chance_count(int chance_type){
    if(chance_type==1||chance_type==2)
        chance_count[chance_type-1] -= 1;
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
float Simple_Calculator::calculate(string input[],int input_size) const{
    if(input_size == 3){
        return arithmetic_op(stoi(input[0]),stoi(input[2]),input[1]);
    }
    else{
        if(input[1]=="+" || input[1]=="-"){
            return arithmetic_op(stoi(input[0]),arithmetic_op(stoi(input[2]),stoi(input[4]),input[3]),input[1]);
        }
        else{
            return arithmetic_op(arithmetic_op(stoi(input[0]),stoi(input[2]),input[1]),stoi(input[4]),input[3]);
        }
    }
}
float Simple_Calculator::arithmetic_op(float operand1, float operand2, string op) const{
    if(op=="+")
        return operand1 + operand2;
    else if(op=="-")
        return operand1 - operand2;
    else if(op=="x")
        return operand1 * operand2;
    else if(op=="/")
        return operand1 / operand2;
    else    
        return 0;
}
bool Simple_Calculator::is_integer(float number) const{
    if(int(number) == number){
        return true;
    }
    return false;
}

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

Game::Game(const char board_front[][TILE_BOARD_LENGTH], string board_back[][TILE_BOARD_LENGTH]) : current_player_idx(0),board(board_front,board_back)
{
}

void Game::generate_target_num()
{
    int min = 1;
    int max = 100;
    static const double fraction = 1.0 / (RAND_MAX + 1.0);
    target_num = min + static_cast<int>((max - min + 1) * (rand() * fraction));
}
void Game::run(){
    cout << "Game start!" << endl;
    cout << "Choose Game Type!" << endl;
    cout << "Press 1 if you want to play basic game(fixed board)" << endl;
    cout << "Press 2 if you want to play an advanced game(changeable board)" << endl;
    cout << ">> ";
    cin >> game_type;
    while(!(game_type==1||game_type==2)){
        cout << "Invalid game type! Choose among 1 and 2 again" << endl;
        cout << ">> ";
        cin >> game_type;
    }
    system("clear");
    cout << "====== BACK ======" << endl;
    board.print_back();
    sleep(5);
    system("clear");
    
    for(round=1;round<=ROUNDS;round++){
        generate_target_num();
        while (!verify_target_num(target_num))
        {
            generate_target_num();
        }
        while(!play_turn()){
            system("clear");
        }
    }
    print_final_result();


}
void Game::print_final_result() const{
    cout << "FINAL RESULT" << endl;
    cout << "Score if player 1: " << players[0].get_score() << endl;
    cout << "Score if player 2: " << players[1].get_score() << endl;
    if(players[0].get_score()>players[1].get_score())
        cout << "Player 1 win!" << endl;
    else if (players[0].get_score() < players[1].get_score())
        cout << "Player 2 win!" << endl;
    else
        cout << "Draw!" << endl;
}

bool Game::play_turn(){
    cout << "Player" << current_player_idx%2+1 << "'s turn!" << endl;
    cout << endl;
    cout << "Round " << round << " / " << ROUNDS << endl;
    cout << "Current score:  [Player 1: " << players[0].get_score() << " | Player 2: " << players[1].get_score() << " ]" << endl;
    cout << "Target number:  " << target_num << endl;
    cout << endl;
    cout << "Player " << (current_player_idx%2+1) << "'s Remaining Chance List:" << endl;
    players[current_player_idx%2].print_remaining_chance_list();
    cout << endl;
    cout << "Press 0: No chance\nPress 1: Skip this turn!\nPress 2: Show back sides of all alphabet tiles!\nPress 3: Double Chance!" << endl;
    cout << ">> ";
    int chance_type;
    cin >> chance_type;
    while(0>chance_type || chance_type>3){
        cout << "Please enter appropriate number" << endl;
        cout << ">> ";
        cin >> chance_type;
    }
    if(players[current_player_idx%2].has_remaining_chance(chance_type)){
        players[current_player_idx%2].reduce_chance_count(chance_type);
    }
    else{
        while (!players[current_player_idx%2].has_remaining_chance(chance_type)){
            cout << "No remaining chance-" << chance_type << ", enter another chance please." << endl;
            cout << ">> ";
            cin >> chance_type;
            if (players[current_player_idx%2].has_remaining_chance(chance_type))
                players[current_player_idx%2].reduce_chance_count(chance_type);
        }
    }
    char choice;
    string input[5];
    float result;
    switch (chance_type)
    {
    case 1:
        current_player_idx += 1;
        return false;
    case 2:
        board.print_back();
        sleep(3);
        system("clear");
    case 0:
        for (int i = 1; i <= 3; i++)
        {
            cout << "====== BOARD ======" << endl;
            board.print_front();
            cout << "Choice-" << i << ": ";
            cin >> choice;
            while (!(choice >= 65 && choice <= 90))
            {
                cout << "Please check input type\n"
                     << ">> ";
                cin >> choice;
            }
            cout << "====== BOARD: One-Flipped ======" << endl;
            input[i - 1] = board.get_num_from_back(choice);
            board.print_one_flipped(choice);
            bool is_num = false;
            for(int j=0;j<NUM_POSSIBLE_NUM;j++){
                if(input[i-1]==POSSIBLE_NUM[j]){
                    is_num = true;
                }
            }
            //Incorrect case 1: Invalid formula
            if(i%2==1 && !is_num){
                cout << "False!: Invalid formila: Change turn" << endl;
                sleep(2);
                current_player_idx++;
                return false;
            }
            else if(i%2==0 && is_num){
                cout << "False!: Invalid formila: Change turn" << endl;
                sleep(2);
                current_player_idx++;
                return false;
            }
            //Incorrect case 2: Tile reuse
            for(int j=1;j<=i;j++){
                if(input[i-1]==input[j-1] && i!=j){
                    cout << "False!: You entered same alphabet twice: Change turn" << endl;
                    sleep(2);
                    current_player_idx++;
                    return false;
                }
            }
            sleep(2);
            system("clear");
        }
        system("clear");
        result = calculator.calculate(input, 3);
        cout << "Result: " << result << endl;
        if (result == target_num)
        {
            cout << "Correct: Round done!" << endl;
            players[current_player_idx % 2].add_score(chance_type);
            sleep(2);
            system("clear");
            if (round % 2 == 0)
                current_player_idx = 0;
            else
                current_player_idx = 1;
            return true;
        }
        //Incorrect case 3: Wrong answer
        else
        {
            cout << "False!: Incorrect answer : Change Turn" << endl;
            sleep(2);
            system("clear");
            current_player_idx += 1;
            return false;
        }
        break;
    case 3:
        for (int i = 1; i <= 5; i++)
        {
            cout << "====== BOARD ======" << endl;
            board.print_front();
            cout << "Choice-" << i << ": ";
            cin >> choice;
            while (!(choice >= 65 && choice <= 90))
            {
                cout << "Please check input type\n"
                     << ">> ";
                cin >> choice;
            }
            cout << "====== BOARD: One-Flipped ======" << endl;
            input[i - 1] = board.get_num_from_back(choice);
            board.print_one_flipped(choice);
            sleep(2);
            system("clear");
        }
        system("clear");
        result = calculator.calculate(input, 5);
        cout << "Result: " << result << endl;
        if (result == target_num)
        {
            cout << "Correct: Round done!" << endl;
            players[current_player_idx % 2].add_score(chance_type);
            sleep(2);
            system("clear");
            if(round%2 == 0)
                current_player_idx = 0;
            else   
                current_player_idx = 1;
            return true;
        }
        else
        {
            cout << "False!: Incorrect answer : Change Turn" << endl;
            sleep(2);
            system("clear");
            current_player_idx += 1;
            return false;
        }
        break;
    }
}
bool Game::verify_target_num(int target_num) const{
    return true;
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
        char c[16];
        ifs >> c;
        string tmp(c);
        board_back[i / 4][i % 4] = tmp;
    }
    ifs.close();
    Game game=Game(BOARD_FRONT,board_back);
    game.run();
    cout << "Thanks for playing the game!" << endl;
    return 0;
}
