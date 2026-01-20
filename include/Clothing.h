#ifndef CLOTHING_H
#define CLOTHING_H

#include "Product.h"

class Clothing : public Product {
    std::string size;

public:
    Clothing(const std::string& name, double price, int stock, const std::string& size);

    std::string type() const override;
    void print(std::ostream& os) const override;

    bool isReturnable() const override;
    int returnWindowDays() const override;
    double shippingSurcharge() const override;
    double discountPercent() const override;
};

#endif //CLOTHING_H