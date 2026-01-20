#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>
#include <iostream>

class Product {
protected:
    int id;
    std::string name;
    double price;
    int stock;
    static int nextID;

public:
    Product(const std::string& name, double price, int stock);
    virtual ~Product();

    int getID() const;
    double getPrice() const;
    int getStock() const;

    void decreaseStock(int A);
    void increaseStock(int A);

    virtual std::string type() const = 0;
    virtual void print(std::ostream& os) const = 0;

    //update proiect:
    virtual bool isReturnable() const = 0;
    virtual int returnWindowDays() const = 0;

    virtual double shippingSurcharge() const = 0;
    virtual double discountPercent() const = 0;

    double finalUnitPrice() const {
        return price * (1.0 - discountPercent());
    }
};

std::ostream& operator<<(std::ostream& os, const Product& p);

#endif //PRODUCT_H