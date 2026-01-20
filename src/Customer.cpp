#include "Customer.h"

int Customer::nextCustomerId = 56238;

Customer::Customer()
    : name("Anonim"), address("Nimic"), budget(0), id(nextCustomerId++) {}

Customer::Customer(const std::string& name, double budget)
    : name(name), address("Nimic"), budget(budget), id(nextCustomerId++) {
    if (!isValidBudget(budget)) throw std::runtime_error("Buget invalid!");
}

Customer::Customer(const std::string& name, const std::string& address, double budget)
    : name(name), address(address), budget(budget), id(nextCustomerId++) {
    if (!isValidBudget(budget)) throw std::runtime_error("Buget invalid!");
}

Customer::Customer(const Customer& other)
    : name(other.name), address(other.address), budget(other.budget), id(other.id) {}

Customer& Customer::operator=(const Customer& other) {
    if (this == &other) return *this;

    name = other.name;
    address = other.address;
    budget = other.budget;
    id = other.id;

    return *this;
}

Customer::~Customer() = default;

int Customer::getId() const { return id;}
double Customer::getBudget() const { return budget;}

void Customer::setBudget(double b) {
    if (!isValidBudget(b)) throw std::runtime_error("Buget invalid!");
    budget = b;
}

const std::string& Customer::getAddress() const { return address;}

bool Customer::isValidBudget(double b) {
    return b >= 0 && b <= 1000000;
}

Customer& Customer::operator+=(double amount) {
    if (amount < 0) throw std::runtime_error("Suma trebuie sa fie pozitiva!");
    budget += amount;

    return *this;
}

std::ostream& operator<<(std::ostream& os, const Customer& c) {
    os << "Customer:  #" << c.id
       << " | Nume: " << c.name
       << " | Adresa: " << c.address
       << " | Buget: " << c.budget;

    return os;
}

std::istream& operator>>(std::istream& is, Customer& c) {
    is >> c.name >> c.address >> c.budget;
    if (!Customer::isValidBudget(c.budget)) throw std::runtime_error("Buget invalid");
    return is;
}

bool operator<(const Customer& a, const Customer& b) {
    return a.getBudget() < b.getBudget();
}