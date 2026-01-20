#ifndef ORDER_H
#define ORDER_H

#include <vector>
#include <string>
#include "PaymentMethod.h"

class Product;

struct OrderItem {
    Product* product;
    int quantity;
};

class Order {
    int id;
    static int nextID;
    bool returned;

    std::string address;
    std::vector<OrderItem> items;

    PaymentMethod* payment;

public:
    Order(const std::vector<OrderItem>& items, const std::string& address, PaymentMethod* payment);
    Order(const std::vector<OrderItem>& items, const std::string& address);

    Order(const Order& other);
    Order& operator=(const Order& other);
    ~Order();

    int getID() const;
    bool isReturned() const;

    double totalBeforeRules() const;
    double totalFinal() const;

    const PaymentMethod& getPayment() const;

    double refundAmount() const;

    void returnOrder();
    void print() const;

    Order& operator+=(const OrderItem& it);
};

bool operator<(const Order& a, const Order& b);

#endif // ORDER_H