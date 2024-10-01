#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "Stringovi.h"
#include "Lista.h"
#include "Torka.h"
#include "Stringovi.h"
#include <iostream>
#include <string>
#include <unordered_map>
#include <cstring>
#include <sstream>

class Interpreter {
public:
    Interpreter();  // Dodat konstruktor

    void run();

private:
    std::unordered_map<std::string, std::string> variables; //mapa za cuvanje stringove
    std::unordered_map<std::string, Lista> lists; //mapa cuvanje liste
    std::unordered_map<std::string, Torka> tuples; //mapa cuvanje torke
    Stringovi s;
    void add_list(const std::string& listName, const std::vector<std::string>& elements); //dodaje listu u mapu
    void add_tuple(const std::string& tupleName, const std::vector<std::string>& elements); //dodaje torku u mapu
    int countWords(const std::string& line); //broji reci sa terminala
	
};

#endif  // INTERPRETER_H
