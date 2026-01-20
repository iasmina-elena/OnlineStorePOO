#include "PremiumClothing.h"

PremiumClothing::PremiumClothing(const std::string& name, double price, int stock, const std::string& size, const std::string& material, int warrantyMonths)
    : Clothing(name, price, stock, size), material(material), warrantyMonths(warrantyMonths) {}

std::string PremiumClothing::type() const { return "Haina Premium";}

void PremiumClothing::print(std::ostream& os) const {
    Clothing::print(os);
    os << " | Material: " << material
       << " | Garantie: " << warrantyMonths << " luni";
}

int PremiumClothing::getWarrantyMonths() const { return warrantyMonths;}
const std::string& PremiumClothing::getMaterial() const { return material;}

bool PremiumClothing::isReturnable() const { return true;}
int PremiumClothing::returnWindowDays() const { return 60;}
double PremiumClothing::shippingSurcharge() const { return 15.0; }

double PremiumClothing::discountPercent() const {
    if (warrantyMonths >= 24) return 0.10;
    if (warrantyMonths >= 12) return 0.05;
    return 0.0;
}