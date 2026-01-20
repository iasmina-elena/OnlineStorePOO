#ifndef ONLINESTORE_PREMIUMCLOTHING_H
#define ONLINESTORE_PREMIUMCLOTHING_H

#include "Clothing.h"
#include <string>

class PremiumClothing : public Clothing {
    std::string material;
    int warrantyMonths;

public:
    PremiumClothing(const std::string& name, double price, int stock, const std::string& size, const std::string& material, int warrantyMonths);

    std::string type() const override;
    void print(std::ostream& os) const override;

    int getWarrantyMonths() const;
    const std::string& getMaterial() const;

    bool isReturnable() const override;
    int returnWindowDays() const override;
    double shippingSurcharge() const override;
    double discountPercent() const override;
};

#endif //ONLINESTORE_PREMIUMCLOTHING_H