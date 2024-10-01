#ifndef STRINGOVI_H
#define STRINGOVI_H

#include <string>

class Stringovi {
private:
    std::string str; //string
    
public:
    Stringovi(const std::string& s); //konstruktor koji postavlja vrednost str-u
    
    void upper(); //velika slova
    void lower(); //mala slova
    void strip(); //uklanjanje razmaka
    int count(const std::string& sub); //brojanje karaktera
    void replace(const std::string& old_sub, const std::string& new_sub); //zamena paterna sa odredjenim stringom
    
    std::string get() const; //getter za string
    Stringovi operator*(int n) const; //mnozenje stringa brojem
    Stringovi operator+(const Stringovi& other) const; //spajanje stringova
};

#endif  // STRINGOVI_H
