#ifndef ONLINESTORE_BOX_H
#define ONLINESTORE_BOX_H

#include <iostream>

template <typename T>
class Box {
    T value;

public:
    explicit Box(const T& value) : value(value) {}

    const T& getValue() const {return value;}

    void setValue(const T& v) {value=v;}

    void print() const {
        std::cout << "Box value: " << value << "\n";
    }
};

#endif //ONLINESTORE_BOX_H