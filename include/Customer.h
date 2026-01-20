#ifndef ONLINESTORE_CUSTOMER_H
#define ONLINESTORE_CUSTOMER_H

#include <string>
#include <iostream>
#include <stdexcept>

class Customer {
    std::string name;
    std::string address;
    double budget;
    static int nextCustomerId;
    int id;

public:
    Customer();
    Customer(const std::string& name, double budget);
    Customer(const std::string& name, const std::string& address, double budget);

    Customer(const Customer& other);
    Customer& operator=(const Customer& other);
    ~Customer();

    int getId() const;
    double getBudget() const;
    void setBudget(double b);
    const std::string& getAddress() const;

    friend std::ostream& operator<<(std::ostream& os, const Customer& c);
    friend std::istream& operator>>(std::istream& is, Customer& c);

    Customer& operator+=(double amount);

    static bool isValidBudget(double b);
};

bool operator<(const Customer& a, const Customer& b);

#endif //ONLINESTORE_CUSTOMER_H