#ifndef LISTA_H
#define LISTA_H

#include <vector>
#include <iostream>

class Lista {
private:
    std::vector<std::string> elements;

public:
    Lista() = default;
    explicit Lista(const std::vector<std::string>& initialElements); //eksplicitni konstruktor koji dodaje elemente u listu
    
    void append(const std::string& element); //dodavanje na kraj liste
    void extend(const Lista& otherList); //prosirivanje lista za jos jednu listu
    void insert(int index, const std::string& element); //umetanje clana u listu
    void remove(const std::string& element); //brisanje odredjenog clana iz liste
    int count(const std::string& element) const; //broj pojava clana
    int index(const std::string& element, int start = 0) const; //indeks clana
    void reverse(); //obrtanje liste
    void sort(); //sortiranje liste
    void clear(); //brisanje liste
    int size() const; //velicina liste
    void print() const; //stampanje liste
     // Sabira dve liste
    Lista operator+(const Lista& other) const;

    // Množi listu sa brojem
    Lista operator*(int multiplier) const;
};

#endif // LISTA_H

