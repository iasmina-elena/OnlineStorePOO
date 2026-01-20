#include <iostream>
#include <vector>
#include <limits>

#include "Store.h"
#include "Clothing.h"
#include "Footwear.h"
#include "PremiumClothing.h"
#include "Customer.h"
#include "CardPayment.h"
#include "CashOnDelivery.h"
#include "Box.h"

template <typename T>
bool read(T& x) {
    if (std::cin >> x) return true;
    if (!std::cin.eof()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    return false;
}

int main() {
    Store store;
    Customer client("Alex", "StradaX", 1000);

    Box<int> boxInt(10);
    Box<std::string> boxString("Hello!");

    boxInt.print();
    boxString.print();

    boxInt.setValue(20);
    std::cout << "get value(int): " << boxInt.getValue() << "\n";
    boxString.setValue("Hello again!");
    std::cout << "get value (string): " << boxString.getValue() << "\n";

    std::cout << "Client ID: " << client.getId()
              << " | Adresa: " << client.getAddress() << "\n";

    store.addProduct(new Clothing("Tricou", 50, 10, "M"));
    store.addProduct(new Clothing("Bluza", 120, 8, "L"));
    store.addProduct(new Clothing("Geaca", 300, 5, "XL"));
    store.addProduct(new Clothing("Pantaloni", 150, 7, "M"));

    store.addProduct(new PremiumClothing("HanoracPremium", 260, 4, "L", "Bumbac organic", 24));
    store.addProduct(new PremiumClothing("PaltonPremium", 700, 2, "XL", "Lana", 12));

    store.addProduct(new Footwear("Adidasi", 200, 6, 42));
    store.addProduct(new Footwear("Pantofi", 250, 4, 41));
    store.addProduct(new Footwear("Ghete", 350, 3, 43));
    store.addProduct(new Footwear("Sandale", 100, 10, 40));

    try {
        const Product* p1 = store.getProductByIdPublic(1);
        std::cout << "Produs #1 type: " << p1->type()
                  << " stock: " << p1->getStock() << "\n";
        std::cout << "Pret: " << p1->getPrice() << "\n";

        const Product* p10 = store.getProductByIdPublic(10);
        if (const auto* prem = dynamic_cast<const PremiumClothing*>(p10)) {
            std::cout << "Premium material: " << prem->getMaterial()
                      << " warranty: " << prem->getWarrantyMonths() << "\n";
        }

        Clothing tmp("tmp", 0.0, 1, "M");
        std::cout << tmp.returnWindowDays() << " ignora\n";
    } catch (...) {}

    while (true) {
        try {
            std::cout << "============================================\n";
            std::cout << "Client: " << client << "\n";
            std::cout << "============================================\n";

            std::cout << "\n--- MENIU ---\n";
            std::cout << "1. Afiseaza produse\n";
            std::cout << "2. Plaseaza comanda\n";
            std::cout << "3. Afiseaza comenzi\n";
            std::cout << "4. Returneaza comanda\n";
            std::cout << "5. Afiseaza doar PremiumClothing\n";
            std::cout << "0. Iesire\n";
            std::cout << "\nCe optiune alegi? \n";
            std::cout << "============================================\n";

            int opt;
            if (!read(opt)) break;

            if (opt == 1) {
                store.listProducts();
            }
            else if (opt == 2) {
                std::cout << "Metoda de plata -> 0 = ramburs, 1 = card : ";
                int payOpt;
                if (!read(payOpt)) break;

                PaymentMethod* pay = nullptr;

                if (payOpt == 1) {
                    std::string last4;
                    std::cout << "Ultimele 4 cifre card: ";
                    if (!read(last4)) break;

                    pay = new CardPayment(last4);
                } else {
                    pay = new CashOnDelivery();
                }

                std::vector<OrderItem> cart;

                while (true) {
                    int id, A;
                    std::cout << "ID produs: ";
                    if (!read(id)) { delete pay; return 0; }

                    std::cout << "Cantitate: ";
                    if (!read(A)) { delete pay; return 0; }

                    Product* p = store.getProductByIdPublic(id);

                    bool merged = false;
                    for (auto& it : cart) {
                        if (it.product->getID() == p->getID()) {
                            it.quantity += A;
                            merged = true;
                            break;
                        }
                    }
                    if (!merged) {
                        cart.push_back({p, A});
                    }

                    std::cout << "Mai adaugi produse? (y/n): ";
                    char ans;
                    if (!read(ans)) { delete pay; return 0; }
                    if (ans == 'n' || ans == 'N') break;
                }

                std::cout << "Adresa livrare: ";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::string address;
                if (!std::getline(std::cin, address)) { delete pay; break; }

                double total = store.previewOrderCost(cart, *pay);

                if (total > client.getBudget()) {
                    std::cout << "Buget insuficient! Cost comanda: " << total << " lei\n";
                    delete pay;
                }
                else {
                    int idComanda = store.placeOrder(cart, address, pay);
                    client.setBudget(client.getBudget() - total);

                    std::cout << "Comanda plasata cu succes!\n";
                    std::cout << "ID comanda: " << idComanda << "\n";
                    std::cout << "Buget ramas: " << client.getBudget() << " lei\n";
                }
            }
            else if (opt == 3) {
                store.listOrders();
            }
            else if (opt == 4) {
                int orderId;
                std::cout << "ID comanda: ";
                if (!read(orderId)) break;

                double refund = store.returnOrderById(orderId);
                client += refund;

                std::cout << "Ai primit inapoi: " << refund << " lei\n";
                std::cout << "Buget acum: " << client.getBudget() << " lei\n";
            }
            else if (opt == 5) {
                store.listPremiumClothingOnly();
            }
            else if (opt == 0) {
                break;
            }
            else {
                std::cout << "Optiune invalida!\n";
            }
        }
        catch (const std::exception& e) {
            std::cout << "Eroare: " << e.what() << "\n";
            return 0;
        }
    }

    return 0;
}

