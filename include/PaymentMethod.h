#ifndef ONLINESTORE_PAYMENTMETHOD_H
#define ONLINESTORE_PAYMENTMETHOD_H

#include <string>

class PaymentMethod {
public:
    virtual ~PaymentMethod();

    virtual std::string name() const = 0;
    virtual double fee(double amount) const = 0;

    // update: functii virtuale (nu afisare)
    virtual void validate(double amount) const = 0;
    virtual bool supportsRefund() const = 0;
    virtual double refundFee(double amount) const = 0;
};

#endif //ONLINESTORE_PAYMENTMETHOD_H