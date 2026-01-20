#ifndef ONLINESTORE_CASHONDELIVERY_H
#define ONLINESTORE_CASHONDELIVERY_H

#include "PaymentMethod.h"

class CashOnDelivery : public PaymentMethod {
public:
    CashOnDelivery() = default;

    std::string name() const override;
    double fee(double amount) const override;

    void validate(double amount) const override;
    bool supportsRefund() const override;
    double refundFee(double amount) const override;
};

#endif //ONLINESTORE_CASHONDELIVERY_H