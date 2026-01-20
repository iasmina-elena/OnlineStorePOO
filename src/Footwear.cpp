#include "Footwear.h"

Footwear::Footwear(const std::string& name, double price, int stock, int size)
    : Product(name, price, stock), size(size) {}

std::string Footwear::type() const { return "Incaltaminte";}

void Footwear::print(std::ostream& os) const {
    os << "[INCALTAMINTE] "
       << "ID: " << id
       << " | Nume: " << name
       << " | Pret: " << price
       << " | Marime: " << size
       << " | Stoc: " << stock;
}

bool Footwear::isReturnable() const { return true; }
int Footwear::returnWindowDays() const { return 14; }
double Footwear::shippingSurcharge() const { return 10.0; }
double Footwear::discountPercent() const { return 0.05; }