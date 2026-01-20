#ifndef STORE_H
#define STORE_H

#include <vector>
#include <list>
#include <string>
#include "Order.h"

class Product;
class PaymentMethod;

class Store {
    std::vector<Product*> products;
    std::list<Order> orders;

    Product* findProductById(int id) const;

public:
    Store();
    ~Store();

    void addProduct(Product* p);
    void listProducts() const;

    Product* getProductByIdPublic(int id) const;

    int placeOrderOneItem(int productId, int A, const std::string& address);
    int placeOrderOneItem(int productId, int A, const std::string& address, PaymentMethod* payment);

    int placeOrder(const std::vector<OrderItem>& items, const std::string& address, PaymentMethod* payment);

    void listOrders() const;
    double returnOrderById(int orderId);

    double previewOrderCost(int productId, int A) const;
    double previewOrderCost(const std::vector<OrderItem>& items, const PaymentMethod& payment) const;

    void listPremiumClothingOnly() const;
};

#endif // STORE_H