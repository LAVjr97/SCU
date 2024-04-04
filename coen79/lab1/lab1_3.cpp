#include <string>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <fstream>


using namespace std;

int main(int argc, char *argv[]){
    string word;
    char upperCase[100];
    int length, i = 0;
    char ch;
    
    fstream file;
    file.open(argv[0]);
    if(file.is_open()){
        while(file >> word){
            while(i < word.length()){
                if((word[i] < 'A' || word[i] > 'z') || (word[i] < 'a' && word[i] > 'Z')){
                    word.erase(i, 1);
                    i--;
                    continue;
                }
                if(word.length() >= 10){
                    ch = word[i];
                    putchar(toupper(ch));
                }
                i++;
            }
            if(word.length() >= 10)
                cout << "\n";
        }
    }
    return 0;
}
