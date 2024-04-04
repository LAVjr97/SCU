// FILE: mystring.cpp
// Name: Luis Villalta


#include "mystring.h"

using namespace std;
using namespace coen79_lab5;

namespace coen79_lab5{

    // CONSTRUCTOR, COPY CONSTRUCTOR, and DESTRUCTOR
    //Post: New string has the characters from the original string
    string::string(const char str[ ]){
        current_length = strlen(str);
        allocated = current_length + 1;

        characters = new char[allocated];
        strncpy(characters, str, allocated);
    }

    //Post: New string has only the 'C' and a '\0'
    string::string(char c){
        current_length = 1;
        allocated = current_length + 1;
        characters = new char[allocated];

        characters[0] = c;
        characters[1] = '\0';
    }      

    //Post: New string copy from the original string
    string::string(const string& source){
        current_length = source.current_length;
        allocated = source.allocated;
        characters = new char[source.current_length];
        strncpy(characters, source.characters, source.current_length); 

    }

    //Post: Sets variables to 0 and deletes the character array
    string::~string( ){
        allocated = 0;
        current_length = 0;

        delete[] characters;
    }

    // MODIFICATION MEMBER FUNCTIONS
    //Post: Addend string is added to the end of the string
    void string::operator +=(const string& addend){
        current_length = current_length + addend.current_length;
        allocated = current_length + 1;
        reserve(allocated);
        strncat(characters, addend.characters, addend.current_length);
    }

    //Post: Addend characters is added to the end of the string
    void string::operator +=(const char addend[ ]){
        current_length = current_length + strlen(addend);
        allocated = current_length + 1;
        reserve(allocated);
        strncat(characters, addend, strlen(addend));
    }

    //Post: Addend character is added to the end of the string 
    //      and a null is added at the very end
    void string::operator +=(char addend){
        current_length += 1;
        allocated = current_length + 1;
        reserve(allocated);
        
        characters[current_length] = '\0';
        characters[current_length - 1] = addend;
    }

    //Post: New string is created with size n, and the old string is coppied onto the new array
    void string::reserve(size_t n){
        char *newchar = new char[n];
        
        strncpy(newchar, characters, current_length);
        delete[] characters;
        characters = newchar;
    }

    //Post: New spces is allocated if the lengths are different and then copies 
    //      the source to the original string and returns the original object
    string& string::operator =(const string& source){
        this -> dlt(0, current_length); 

        if(current_length != source.current_length){ 
            allocated = source.allocated;
            reserve(allocated);
        }

        strncpy(characters, source.characters, allocated);
        current_length = source.current_length;

        return *this;
    }

    //Pre: Position is less than length 
    //Post: Total length is checked if not more is reserved, string is inserted 
    void string::insert(const string& source, unsigned int position){
        assert(position <= length());
        size_t t = current_length + source.current_length;
        int i; 

        if(allocated < t)
            reserve(t);
        
        for(i = length(); i > position; i--)
            characters[i] = characters[i - 1];

        for(i = 0; i < source.length(); i++)
            characters[position + i] = source.characters[i];

        current_length = t;
    }

    //Pre: Position and the numbers to be added is smaller than length
    //Post: Characters array is adjusted to move the chars and currentlength is adjusted
    void string::dlt(unsigned int position, unsigned int num){
        assert(position + num <= length());
        int i;

        for(i = position; i < length(); i++)
            characters[i] = characters[i + num];

        current_length = current_length - num;
    }

    //Pre: Position is less than length
    //Post: C is added to the Characters at 'Position'
    void string::replace(char c, unsigned int position){
        assert(position < length());

        characters[position] = c;
    }

    //Pre: Position + length of the source is less than the length of the orinal string
    //Post: Original string at position given is replaced with the source string
    void string::replace(const string& source, unsigned int position){
        assert((position + source.length()) <= length());
        int i, j = 0;

        for(i = position; i < position + source.length(); i++){
            characters[i] = source[j];
            j++;
        }
    }

    // CONSTANT MEMBER FUNCTIONS

    //Pre: Position is less than length
    //Post: returns the charater at the given position
    char string::operator [](size_t position) const{
        assert(position < length());
        
        return characters[position];
    }

    //Post: Return the position of the first character found, else return -1
    int string::search(char c) const{
        int i; 

        for(i = 0; i < length() - 1; i++)
            if(characters[i] == c)
                return i;

        return -1;
    }

    //Post: return the position of the string inside of the original string
    int string::search(const string& substring) const{
        char *n = strstr(characters, substring.characters);

        if(n != NULL)
            return n[0] - characters[0];

        return -1;
    }

    //Post: return the number of times a character exists in the string
    unsigned int string::count(char c) const{
        unsigned int i, co = 0; 

        for(i = 0; i < length(); i++)
            if(characters[i] == c)
                co++;
        
        return co;
    }

    //FRIEND FUNCTIONS
    //Post: The string is written to outs 
    std::ostream& operator <<(std::ostream& outs, const string& source){
        outs << source.characters;

        return outs;
    }

    //Post: Compares the strings in s1 and s2 and returns true 
    //      if they are the same, else false 
    bool operator ==(const string& s1, const string& s2){
        if(strcmp(s1.characters, s2.characters) == 0)
            return true;
        return false;
    }

    //Post: Compares the strings in s1 and s2 and returns true 
    //      if they are different, else false 
    bool operator !=(const string& s1, const string& s2){
        if(strcmp(s1.characters, s2.characters) != 0)
            return true;
        return false;
    }

    //Post: Compares the strings in s1 and s2 and returns true if s1 is 
    //      greater than s2, else false 
    bool operator > (const string& s1, const string& s2){
        if(strcmp(s1.characters, s2.characters) > 0)
            return true;
        return false;
    }

    //Post: Compares the string in s1 and s2 and returns true if s2 is 
    //      greater than s1, else false 
    bool operator < (const string& s1, const string& s2){
        if(strcmp(s1.characters, s2.characters) < 0)
            return true;
        return false;
    }

    //Post: Compares the string in s1 and s2 and returns true if s1 is greater
    //      than or equal to s2, else false
    bool operator >=(const string& s1, const string& s2){
        if(strcmp(s1.characters, s2.characters) >= 0)
            return true;
        return false;

    }
    //Post: Compares the string in s1 and s2 and returns true if s2 is greater
    //      than or equal to s1, else false
    bool operator <=(const string& s1, const string& s2){
        if(strcmp(s1.characters, s2.characters) <= 0)
            return true;
        return false;
    }

    //Post: Creates a new string and reserves space with the length of both s1 and s2
    //      and adds s1 and s2 to n using the overloaded += and returns n
    string operator +(const string& s1, const string& s2){
        string n;

        n.reserve(s1.length() + s2.length());
        n += s1;
        n += s2;

        return n;
    }

    //Post: Creates a new string and reserves space with the length of bosth s1 and addend
    //      and adds s1 and the string to n using the overloaded =+ and return n
    string operator +(const string& s1, const char addend[ ]){
        string n;

        n.reserve(s1.length() + strlen(addend));
        n += s1;
        n += addend;

        return n;
    }

    //Post: Creates a new char array and ignores the spaces and creates a new string object
    //      using b and and writes it to target and returns the input stream.
    std::istream& operator >> (std::istream& ins, string& target){
        char *b = new char[100];

        while(ins && isspace(ins.peek()))
            ins.ignore();
        ins >> b;
        target = string(b);
        return ins;
    }
}