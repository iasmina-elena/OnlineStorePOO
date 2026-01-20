#ifndef FOOTWEAR_H
#define FOOTWEAR_H

#include "Product.h"

class Footwear : public Product {
    int size;

public:
    Footwear(const std::string& name, double price, int stock, int size);

    std::string type() const override;
    void print(std::ostream& os) const override;

    bool isReturnable() const override;
    int returnWindowDays() const override;
    double shippingSurcharge() const override;
    double discountPercent() const override;
};

#endif //FOOTWEAR_H