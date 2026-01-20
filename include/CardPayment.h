#ifndef ONLINESTORE_CARDPAYMENT_H
#define ONLINESTORE_CARDPAYMENT_H

#include "PaymentMethod.h"
#include <string>

class CardPayment : public PaymentMethod {
    std::string last4;

public:
    explicit CardPayment(const std::string& last4);

    std::string name() const override;
    double fee(double amount) const override;

    void validate(double amount) const override;
    bool supportsRefund() const override;
    double refundFee(double amount) const override;

    const std::string& getLast4() const;
};

#endif //ONLINESTORE_CARDPAYMENT_H