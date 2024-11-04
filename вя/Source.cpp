#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

using namespace std;


struct Product {
    string name;
    double price;
};


struct CartItem {
    Product product;
    int quantity;
};


void displayMenu() {
    cout << "\nМагазин \"Соки Никиты\"\n" << endl;
    cout << "1. Фруктовые соки\n";
    cout << "2. Овощные соки\n";
    cout << "3. Чаи\n";
    cout << "4. Корзина\n";
    cout << "5. Выход\n" << endl;
    cout << "Выберите категорию: ";
}


void displayCategory(const vector<Product>& products) {
    cout << "\nТовары:\n" << endl;
    for (int i = 0; i < products.size(); i++) {
        cout << i + 1 << ". " << products[i].name << " - " << products[i].price << " рублей/литр" << endl;
    }
}


Product getProduct(const
    vector<Product>& products, int choice) {
    return products[choice - 1];
}


void addToCart(vector<CartItem>& cart, Product product, int quantity) {

    bool found = false;
    for (int i = 0; i < cart.size(); i++) {
        if (cart[i].product.name == product.name) {
            cart[i].quantity += quantity;
            found = true;
            break;
        }
    }

  
    if (!found) {
        CartItem item;
        item.product = product;
        item.quantity = quantity;
        cart.push_back(item);
    }
}


double getParsleyTeaDiscount(const vector<CartItem>& cart) {
    double parsleyTeaQuantity = 0;
    for (const auto& item : cart) {
        if (item.product.name == "Петрушевый чай") {
            parsleyTeaQuantity += item.quantity;
        }
    }
    if (parsleyTeaQuantity >= 3)
    {
        return 0.05;
    }
    else {
        return 0;
    }
}


double getTotalDiscount(const vector<CartItem>& cart, double totalCost, double parsleyTeaDiscount) {
    double totalDiscount = parsleyTeaDiscount;
    if (totalCost > 1000) { 
        totalDiscount += 0.13; 
    }
    return totalDiscount;
}


void displayCart(const vector<CartItem>& cart) {
    cout << "\nВаша корзина:\n" << endl;
    double totalCost = 0;
    for (const auto& item : cart) {
        cout << item.product.name << " - " << item.quantity << " литров - " << item.quantity * item.product.price << " рублей" << endl;
        totalCost += item.quantity * item.product.price;
    }

    
    double parsleyTeaDiscount = getParsleyTeaDiscount(cart);

   
    double totalDiscount =
        getTotalDiscount(cart, totalCost, parsleyTeaDiscount);

    
    cout << "\nИтоговая стоимость: " << totalCost << " рублей" << endl;
    cout << "Скидка на петрушевый чай: " << setprecision(2) << fixed << parsleyTeaDiscount * 100 << "%" << endl;
    cout << "Общая скидка: " << setprecision(2) << fixed << totalDiscount * 100 << "%" << endl;
    cout << "Сумма к оплате: " << totalCost * (1 - totalDiscount) << " рублей" << endl;
}


void processOnionJuice(vector<CartItem>& cart) {
    int quantity = 0;
    cout << "Введите количество литров лукового сока: ";
    cin >> quantity;
    addToCart(cart, Product{ "Луковый сок", 80 }, quantity);
   
    int freeQuantity = quantity / 4;
    if (freeQuantity > 0) {
        cout << "Вам в подарок " << freeQuantity << " литров лукового сока!" << endl;
        addToCart(cart, Product{ "Луковый сок", 0 }, freeQuantity);
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    vector<Product> fruitJuices = {
        {"Яблочный сок", 60},
        {"Апельсиновый сок", 70},
        {"Абрикосовый сок", 80},
        {"Грушевый сок", 90}
    };
    vector<Product> vegetableJuices = {
        {"Томатный сок", 50},
        {"Луковый сок", 80},
        {"Огуречный сок", 65}
    };
    vector<Product> teas = {
        {"Чесночный чай", 40},
        {"Петрушевый чай", 35}
    };

    vector<CartItem> cart;

    
    while (true) {
        displayMenu();
        int choice;
        cin >> choice;

        switch (choice) {
        case 1: {
            displayCategory(fruitJuices);
            int productChoice;
            cout << "Выберите сок: ";
            cin >> productChoice;
            int quantity;
            cout << "Введите количество литров: ";
            cin >> quantity;
            addToCart(cart, getProduct(fruitJuices, productChoice), quantity);
            break;
        }
        case 2: {
            displayCategory(vegetableJuices);
            int productChoice;
            cout << "Выберите сок: ";
            cin >> productChoice;
            if (productChoice == 2) {
                processOnionJuice(cart);
            }
            else {
                int quantity;
                cout << "Введите количество литров: ";
                cin >> quantity;
                addToCart(cart, getProduct(vegetableJuices, productChoice), quantity);
            }
            break;
        }
        case 3: {
            displayCategory(teas);
            int productChoice;
            cout << "Выберите чай: ";
            cin >> productChoice;
            int quantity;
            cout << "Введите количество литров: ";
            cin >> quantity;
            addToCart(cart, getProduct(teas,
                productChoice), quantity);
            break;
        }
        case 4: {
            displayCart(cart);
            break;
        }
        case 5:
            return 0;
        default:
            cout << "Неверный выбор.\n";
        }
    }
}
