# 🛒 Online Store 

## Descrierea proiectului

Acest proiect implementează o aplicație tip **magazin online** în C++, construită pe baza principiilor Programării Orientate pe Obiecte (POO). Aplicația oferă funcționalități de gestionare a produselor, plasare și returnare de comenzi, calcularea costului total pe baza unor reguli comerciale și interacțiune cu utilizatorul printr-un meniu simplu în consolă.

---

## 🚀 Funcționalități End User

Prin intermediul meniului din consolă, utilizatorul poate:

- Vizualiza lista completă de produse disponibile
- Plasa o comandă selectând produsele și cantitățile dorite
- Alege metoda de plată (Card sau Ramburs)
- Introduce adresa de livrare
- Vizualiza comenzile deja plasate
- Returna comenzi acceptate, cu restabilirea automată a bugetului și a stocului
- Primi mesaje de eroare în caz de acțiuni invalide

---

## 🧠 Concepte și Structură

Aplicația include următoarele componente:

### 🏷️ Modele de produs
- **Product** — clasă abstractă de bază pentru toate produsele
- **Clothing** — produs de tip „haină”
- **PremiumClothing** — derivat din Clothing cu funcții extinse
- **Footwear** — încălțăminte

### 🧾 Comenzi și stocuri
- **OrderItem** — o poziție dintr-o comandă
- **Order** — comandă plasată de client, cu reguli comerciale aplicate
- **Store** — manager al produselor și comenzilor

### 💳 Metode de plată
- **PaymentMethod** — clasă abstractă pentru plata unei comenzi
- **CardPayment** — plata cu cardul
- **CashOnDelivery** — plata ramburs

---

## 📦 Tehnologii și unelte folosite

- **Programare Orientată pe Obiecte**  
  (moștenire, polimorfism, clase abstracte, tratarea excepțiilor)
---

## 🧠 Diagrama de moștenire (simplificată)

```mermaid
classDiagram
direction TB

class Product {
  <<abstract>>
}
class Clothing
class PremiumClothing
class Footwear

Product <|-- Clothing
Clothing <|-- PremiumClothing
Product <|-- Footwear

class PaymentMethod {
  <<abstract>>
}
class CardPayment
class CashOnDelivery

PaymentMethod <|-- CardPayment
PaymentMethod <|-- CashOnDelivery


