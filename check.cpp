#include <iostream>
#include <string>
using namespace std;

int main(){
    float a=1,b=2.1;
    cout << (int(a) == a) << endl;
    cout << (int(b) == b) << endl;
    char c = 'A';
    cout << (c == 65) << endl;
    string s = "1", p = "s";
    cout << stoi(s) << endl;
    cout << stoi(p) << endl;

    if (chance_type == 1)
        return false;
    else if (chance_type == 0)
    {
        char choice;
        string input[3];
        float result;
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
            return true;
        }
        else
        {
            cout << "False!: Incorrect answer : Change Turn" << endl;
            sleep(2);
            system("clear");
            return false;
        }
    }
    else if (chance_type == 2)
    {
        board.print_back();
        sleep(3);
        system("clear");
    }
    else if (chance_type == 3)
    {
        char choice;
        string input[5];
        float result;
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
            return true;
        }
        else
        {
            cout << "False!: Incorrect answer : Change Turn" << endl;
            sleep(2);
            system("clear");
            return false;
        }
    }
}

switch(chance_type){
    case 1:
        return false;
    case 2:
        board.print_back();
        sleep(3);
        system("clear");
    case 0:
        char choice;
        string input[3];
        float result;
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
            return true;
        }
        else
        {
            cout << "False!: Incorrect answer : Change Turn" << endl;
            sleep(2);
            system("clear");
            return false;
        }
        break;
    case 3:
        char choice;
        string input[5];
        float result;
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
            return true;
        }
        else
        {
            cout << "False!: Incorrect answer : Change Turn" << endl;
            sleep(2);
            system("clear");
            return false;
        }
        break;
}