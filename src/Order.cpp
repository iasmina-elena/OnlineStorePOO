#include "Order.h"
#include "Product.h"
#include "CashOnDelivery.h"
#include "CardPayment.h"
#include <iostream>
#include <stdexcept>

int Order::nextID = 1;

static PaymentMethod* copyPayment(const PaymentMethod* p) {
    if (!p) throw std::runtime_error("Metoda de plata lipsa");

    if (auto card = dynamic_cast<const CardPayment*>(p)) {
        (void)card->getLast4(); // pentru a putea fi folosit in Cppcheck
        return new CardPayment(*card);
    }

    if (auto cod = dynamic_cast<const CashOnDelivery*>(p)) {
        return new CashOnDelivery(*cod);
    }

    throw std::runtime_error("Tip de plata necunoscut!");
}

Order::Order(const std::vector<OrderItem>& items, const std::string& address, PaymentMethod* payment)
    : id(nextID++), returned(false), address(address), items(items), payment(payment) {
    if (!this->payment) throw std::runtime_error("Metoda de plata lipsa!");
    if (this->items.empty()) throw std::runtime_error("Nu exista niciun produs in comanda!");
}

Order::Order(const std::vector<OrderItem>& items, const std::string& address)
    : Order(items, address, new CashOnDelivery()) {}

Order::Order(const Order& other)
    : id(other.id), returned(other.returned), address(other.address), items(other.items), payment(copyPayment(other.payment)) {}

Order& Order::operator=(const Order& other) {
    if ( this == & other) return *this;

    id = other.id;
    returned = other.returned;
    address = other.address;
    items = other.items;

    delete payment;
    payment = copyPayment(other.payment);

    return *this;
}

Order::~Order() {
    delete payment;
    payment = nullptr;
}

int Order::getID() const {return id;}
bool Order::isReturned() const {return returned;}

const PaymentMethod& Order::getPayment() const {
    if (!payment) throw std::runtime_error("Metoda de plata lipsa!");
    return *payment;
}

double Order::totalBeforeRules() const {
    double sum = 0.0;
    for (const auto& it : items) {
        if (!it.product) throw std::runtime_error("Produs invalid!");
        if (it.quantity <= 0) throw std::runtime_error("Cantitate invalida!");

        sum += it.product->finalUnitPrice() * it.quantity;
        sum += it.product-> shippingSurcharge() * it.quantity;
    }
    return sum;
}

double Order::totalFinal() const {
    double sum = totalBeforeRules();

    if (sum > 500) sum -=100;
    else if (sum < 100) sum +=20;

    payment->validate(sum);
    sum += payment->fee(sum);

    return sum;
}

double Order::refundAmount() const {
    if (!payment) throw std::runtime_error("Metoda de plata lipsa");
    if (!payment->supportsRefund()) throw std::runtime_error("Metoda de plata nu include refund");

    double final = totalFinal();
    double rf = payment->refundFee(final);
    if (rf<0) throw std::runtime_error("Refund fee invalid");
    if (rf > final) rf = final;

    return final - rf;
}

void Order::returnOrder() {
    if (returned) throw std::runtime_error("Comanda a fost deja returnata!");

    for (const auto& it : items) {
        if (!it.product) throw std::runtime_error("Produs incalid in comanda!");
        if (!it.product->isReturnable()) throw std::runtime_error("Comanda contine produse nereturnabile!");
    }

    for (auto& it : items) {
        it.product->increaseStock(it.quantity);
    }

    returned = true;
}

void Order::print() const {
    std::cout << "Comanda #" << id
              << " | Adresa: " << address
              << " | Plata: " << getPayment().name()
              << " | Total initial: " << totalBeforeRules()
              << " | Total final: " << totalFinal()
              << " | Status: ";
    if (isReturned()) {
        std::cout << "Returnata";
    }
    else {std::cout << "Activa";}
    std::cout << "\n";
}

Order& Order::operator+=(const OrderItem& it) {
    items.push_back(it);
    return *this;
}

bool operator<(const Order& a, const Order& b) {
    return a.totalFinal() < b.totalFinal();
}