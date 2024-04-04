#include <cstring>
#include <string> 
#include <iostream>
#include <time.h>
#include <cstdlib>

using namespace std;

int main(){ 
    char ch[10];
    int count, guess, enter;
    string user;
    
    cout << "Think of a number between 0 - 20 and press enter when you have your number!\n'";
    cin.get();

    while(1){
        srand(time(NULL));
        guess = rand() % 21;

        cout << "Is the number " << guess << "? (Y/N) \n";
        getline(cin, user);

        if(user == "Y"){
            count++;
            if(count == 1){
                cout << " I guessed your number first try lol \n";
            }else
                cout << "I guessed your number in " << count << "steps \n";
            break;
        }else if(user == "N"){
            count ++;
            continue;
        }else 
            cout << "Only use Y or N as an input";
    }

}
