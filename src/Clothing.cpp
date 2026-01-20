#include "Clothing.h"

Clothing::Clothing(const std::string& name, double price, int stock, const std::string& size)
    : Product(name, price, stock), size(size) {}

std::string Clothing::type() const { return "Haina";}

void Clothing::print(std::ostream& os) const {
    os << "[HAINA] "
       << " ID: " << id
       << " | Nume: " << name
       << " | Pret: " << price
       << " | Marime: " << size
       << " | Stoc: " << stock;
}

bool Clothing::isReturnable() const { return true; }
int Clothing::returnWindowDays() const { return 30; }
double Clothing::shippingSurcharge() const { return 0.0; }
double Clothing::discountPercent() const { return 0.0; }