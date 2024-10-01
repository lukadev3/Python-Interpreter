#include "Torka.h"
#include <algorithm>

//definisanje svih funkcija

Torka::Torka(const std::vector<std::string>& elements)
    : elements(elements) {}

std::string Torka::max() const {
    if (elements.empty()) {
        return "";
    }
    return *std::max_element(elements.begin(), elements.end());
}

std::string Torka::min() const {
    if (elements.empty()) {
        return "";
    }
    return *std::min_element(elements.begin(), elements.end());
}

int Torka::count(const std::string& element) const {
    return std::count(elements.begin(), elements.end(), element);
}

int Torka::index(const std::string& element, int start) const {
    auto it = std::find(elements.begin() + start, elements.end(), element);
    if (it != elements.end()) {
        return std::distance(elements.begin(), it);
    }
    return -1; // Element not found
}

int Torka::size() const {
    return elements.size();
}

Torka Torka::operator+(const Torka& other) const {
    Torka result;
    result.elements = elements;
    result.elements.insert(result.elements.end(), other.elements.begin(), other.elements.end());
    return result;
}

Torka Torka::operator*(int n) const {
    std::vector<std::string> multipliedElements;
    for (int i = 0; i < n; ++i) {
        multipliedElements.insert(multipliedElements.end(), elements.begin(), elements.end());
    }
    return Torka(multipliedElements);
}

void Torka::print() const {
    std::cout << "(";
    for (size_t i = 0; i < elements.size(); ++i) {
        std::cout << elements[i];
        if (i != elements.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << ")" << std::endl;
}

void Torka::sort() {
    std::sort(elements.begin(), elements.end());
    std::cout << "[";
    for (size_t i = 0; i < elements.size(); ++i) {
        std::cout << elements[i];
        if (i != elements.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << "]" << std::endl;
}

void Torka::clear() {
    elements.clear();
}
