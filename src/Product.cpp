#include "Product.h"
#include <stdexcept>

int Product::nextID = 1;

Product::Product(const std::string& name, double price, int stock)
    : id(nextID++), name(name), price(price), stock(stock) {}

Product::~Product() = default;

int Product::getID() const {return id;}
double Product::getPrice() const {return price;}
int Product::getStock() const {return stock;}

void Product::decreaseStock(int A) {
    if (A <= 0) throw std::runtime_error("Cantitate ibvalida!");
    if (A > stock) throw std::runtime_error("Stoc insuficient!");

    stock -= A;
}

void Product::increaseStock(int A) {
    if (A > 0) stock += A;
}

std::ostream& operator<<(std::ostream& os, const Product& p) {
    p.print(os);
    return os;
}