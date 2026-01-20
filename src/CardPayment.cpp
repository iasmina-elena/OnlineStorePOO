#include "CardPayment.h"

CardPayment::CardPayment(const std::string& last4) : last4(last4) {}

std::string CardPayment::name() const {
    return "Card **** **** **** " + last4;
}

double CardPayment::fee(double amount) const {
    return amount * 0.02;
}

void CardPayment::validate(double amount) const {
    if (amount <= 0) throw std::runtime_error("Suma invalida!");
    if (last4.size() != 4) throw std::runtime_error("Card invalid: trebuie sa introduci ultimele 4 cifre!");
}

bool CardPayment::supportsRefund() const {
    return true;
}

double CardPayment::refundFee(double amount) const {
    (void)amount;
    return 0.0;
}

const std::string& CardPayment::getLast4() const {
    return last4;
}