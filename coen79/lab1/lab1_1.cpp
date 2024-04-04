#include <string>
#include <cstring>
#include <iostream>

using namespace std;

int main(){
    int alpha = 0, non = 0, i;
    string input;
    char inputArray[50];
    char *p;
    char in;

    cout << "Please type something: \n";
    getline(cin, input);

    strcpy(inputArray, input.c_str());

    p = inputArray; 

    while(*p != '\0'){
        in = *p;
        p++;
        if(isalpha(in))
            alpha++;
        else if (in == ' ')
            continue;
        else
            non++;
    }

    cout << "\n Number of alpha characters: " << alpha;
    cout << "\n Number of non-alpha characters: " << non;

    return 0;
}
