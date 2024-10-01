#ifndef TORKA_H
#define TORKA_H

#include <vector>
#include <string>
#include <iostream>

class Torka {
private:
    std::vector<std::string> elements;

public:
    Torka() {}
    explicit Torka(const std::vector<std::string>& elements); //eksplicitni konstruktor koji dodaje elemente u torku
    
    std::string max() const; //maksimalni clan torke
    std::string min() const; //minimalni clan torke
    int size() const; //velicina torke
    
    int count(const std::string& element) const; //broj pojava clana
    int index(const std::string& element, int start = 0) const; //indeks clana
    
    Torka operator+(const Torka& other) const; //prepisani operator sabiranja torki
    Torka operator*(int n) const; //prepisani operator mnozenja torke
    void print() const; //stampanje torke
    void sort(); //sortiranje torke
    void clear(); //brisanje torke(kada se torka izbrise ne moze ni da se odstampa jer vise ne postoji)
};

#endif // TORKA_H
