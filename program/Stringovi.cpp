#include "Stringovi.h"
#include <algorithm>

//definicije svih funkcija, koristi se biblioteka algorith za laksu manipulaciju

Stringovi::Stringovi(const std::string& s) : str(s) {}

void Stringovi::upper() {
    std::transform(str.begin(), str.end(), str.begin(), ::toupper);
}

void Stringovi::lower() {
    std::transform(str.begin(), str.end(), str.begin(), ::tolower);
}

void Stringovi::strip() {
    str.erase(std::remove_if(str.begin(), str.end(), ::isspace), str.end());
}

int Stringovi::count(const std::string& sub) {
    int count = 0;
    size_t pos = 0;
    while ((pos = str.find(sub, pos)) != std::string::npos) {
        count++;
        pos += sub.length();
    }
    return count;
}

void Stringovi::replace(const std::string& pattern, const std::string& replacement) {
    std::size_t pos = str.find(pattern);
    while (pos != std::string::npos) {
        str.replace(pos, pattern.length(), replacement);
        pos = str.find(pattern, pos + replacement.length());
    }
}

Stringovi Stringovi::operator+(const Stringovi& other) const {
	return Stringovi(str + other.str);
}

Stringovi Stringovi::operator*(int n) const {
	std::string result;
	for (int i = 0; i < n; ++i) {
		result += str;
	}
	return Stringovi(result);
}

std::string Stringovi::get() const {
    return str;
}
