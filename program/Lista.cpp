#include "Lista.h"
#include <algorithm>

//definisanje svih funkcija

Lista::Lista(const std::vector<std::string>& initialElements) : elements(initialElements) {}

void Lista::append(const std::string& element) {
    elements.push_back(element);
}

void Lista::extend(const Lista& otherList) {
    elements.insert(elements.end(), otherList.elements.begin(), otherList.elements.end());
}

void Lista::insert(int index, const std::string& element) {
    if (index >= 0 && index <= static_cast<int>(elements.size())) {
        elements.insert(elements.begin() + index, element);
    } else {
        std::cout << "Index out of range!" << std::endl;
    }
}

void Lista::remove(const std::string& element) {
    elements.erase(std::remove(elements.begin(), elements.end(), element), elements.end());
}

int Lista::count(const std::string& element) const {
    return std::count(elements.begin(), elements.end(), element);
}

int Lista::index(const std::string& element, int start) const {
    auto it = std::find(elements.begin() + start, elements.end(), element);
    if (it != elements.end()) {
        return std::distance(elements.begin(), it);
    }
    return -1; // Element not found
}

void Lista::reverse() {
    std::reverse(elements.begin(), elements.end());
}

void Lista::sort() {
    std::sort(elements.begin(), elements.end());
}

void Lista::clear() {
    elements.clear();
}

int Lista::size() const {
    return static_cast<int>(elements.size());
}

void Lista::print() const {
    std::cout << "[";
    for (std::size_t i = 0; i < elements.size(); ++i) {
        std::cout << elements[i];
        if (i < elements.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << "]" << std::endl;
}
// U klasi Lista

Lista Lista::operator+(const Lista& other) const {
    Lista result = *this;  // Kreiraj kopiju trenutne liste

    // Dodaj elemente iz druge liste u rezultujuću listu
    for (const auto& element : other.elements) {
        result.elements.push_back(element);
    }

    return result;
}

Lista Lista::operator*(int multiplier) const {
    Lista result;  // Kreiraj praznu rezultujuću listu

    // Pomnoži trenutnu listu sa brojem i dodaj rezultat u rezultujuću listu
    for (int i = 0; i < multiplier; i++) {
        for (const auto& element : elements) {
            result.elements.push_back(element);
        }
    }

    return result;
}





