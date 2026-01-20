#include "CashOnDelivery.h"
#include <stdexcept>

std::string CashOnDelivery::name() const {
    return "Ramburs";
}

double CashOnDelivery::fee(double amount) const {
    (void)amount; // nu folosesc variabila amount
    return 5.0;
}

void CashOnDelivery::validate(double amount) const {
    if (amount <= 0) throw std::runtime_error("Suma invalida!");
    if (amount > 2000) throw std::runtime_error("Nu poti alege ramburs pentru sume peste 2000 lei");
}

bool CashOnDelivery::supportsRefund() const {
    return true;
}

double CashOnDelivery::refundFee(double amount) const {
    (void)amount; // nu folosesc variabila amount
    return 5.0;
}
