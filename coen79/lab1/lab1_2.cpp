#include <string>
#include <cstring>
#include <iostream>
#include <iomanip>

using namespace std;

int main(){
    int i, j = 0;
    string input;
    cout << "Please type 10 numbers: \n";
    
    getline(cin, input); //asks user for an input
    if(input.length() != 10){
        cout << "Please input only 10 numbers";
        return 0;
    }

    string output = input; //copies the input to another string

    for(i = 0; i < 5; i++){
        swap(output[i], output[9 - i]); //swaps the array
    }

    for(i = 0; i < 10; i+=2){ //formats the printing
        j = i + 15;
        cout << setw(j) << input << setw(15) << output << "\n";
    }
    return 0;
}


