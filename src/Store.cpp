#include "Store.h"
#include "Product.h"
#include "PremiumClothing.h"
#include "CashOnDelivery.h"
#include <iostream>
#include <stdexcept>
#include <memory>

Store::Store() = default;

Store::~Store() {
    for (Product* p : products) delete p;
}

void Store::addProduct(Product* p) {
    products.push_back(p);
}

void Store::listProducts() const {
    for (const Product* p : products) std::cout << *p << "\n";
}

Product* Store::findProductById(int id) const {
    for (Product* p  : products) {
        if (p->getID() == id) return p;
    }
    throw std::runtime_error("Produsul nu exista!");
}

Product* Store::getProductByIdPublic(int id) const {
    return findProductById(id);
}

int Store::placeOrderOneItem(int productId, int A, const std::string& address) {
    return placeOrderOneItem(productId, A, address, new CashOnDelivery());
}

int Store::placeOrderOneItem(int productId, int A, const std::string& address, PaymentMethod* payment) {
    Product* p = findProductById(productId);
    std::vector<OrderItem> items;
    items.push_back({p, A});
    return placeOrder(items, address, payment);
}

double Store::previewOrderCost(int productId, int A) const {
    Product* p = findProductById(productId);
    if (A <= 0) throw std::runtime_error("Cantitate invalida!");

    double sum = 0.0;
    sum += p->finalUnitPrice() * A;
    sum += p->shippingSurcharge() * A;

    if (sum>500) sum -=100;
    else if (sum<100) sum +=20;

    return sum;
}

double Store::previewOrderCost(const std::vector<OrderItem>& items, const PaymentMethod& payment) const {
    if (items.empty()) throw std::runtime_error("Comanda nu are niciun produs!");

    double sum = 0.0;
    for (const auto& it : items) {
        if (!it.product) throw std::runtime_error("Produs invalid in comanda!");
        if (it.quantity <= 0) throw std::runtime_error("Cantitate invalida!");

        sum += it.product->finalUnitPrice() * it.quantity;
        sum += it.product->shippingSurcharge() * it.quantity;
    }
    if (sum > 500) sum -=100;
    else if (sum < 100) sum+=20;

    payment.validate(sum);
    sum += payment.fee(sum);

    return sum;
}

int Store::placeOrder(const std::vector<OrderItem>& items, const std::string& address, PaymentMethod* payment) {
    if (items.empty()) throw std::runtime_error("Comanda nu are niciun produs");
    if (!payment) throw std::runtime_error("Metoda de plata lipsa");

    std::unique_ptr<PaymentMethod> payG(payment);

    std::vector<std::pair<Product*, int>> decreased; // imi notez la acest produs X am scazut Y bucati (in caz de eroare)
    decreased.reserve(items.size());

    try {
        for (const auto& it : items) {
            if (!it.product) throw std::runtime_error("Produs invalid in comanda!");
            it.product->decreaseStock(it.quantity);
            decreased.push_back({it.product, it.quantity});
        }

        Order newOrder(items, address, payG.release());

        (void)newOrder.totalFinal();

        orders.push_back(newOrder);
        return newOrder.getID();
    }
    catch (...) {
        for (auto& pr : decreased) {
            pr.first->increaseStock(pr.second);
        }
        throw;
    }
}

void Store::listOrders() const {
    if (orders.empty()) {
        std::cout << "Nu exista comenzi\n";
        return;
    }
    for (const Order& o : orders) o.print();
}

double Store::returnOrderById(int orderId) {
    for (Order& o : orders) {
        if (o.getID() == orderId) {
            double refund = o.refundAmount();
            o.returnOrder();
            return refund;
        }
    }
    throw std::runtime_error("Comanda nu exista");
}

void Store::listPremiumClothingOnly() const {
    bool found = false;
    for (const Product* p : products) {
        const PremiumClothing* prem = dynamic_cast<const PremiumClothing*>(p);
        if (prem) {
            found = true;
            std::cout << *prem << "\n";
        }
    }
    if (!found) std::cout << "Nu exista produse PremiumClothing\n";
}