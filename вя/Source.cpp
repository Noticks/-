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
    cout << "\n������� \"���� ������\"\n" << endl;
    cout << "1. ��������� ����\n";
    cout << "2. ������� ����\n";
    cout << "3. ���\n";
    cout << "4. �������\n";
    cout << "5. �����\n" << endl;
    cout << "�������� ���������: ";
}


void displayCategory(const vector<Product>& products) {
    cout << "\n������:\n" << endl;
    for (int i = 0; i < products.size(); i++) {
        cout << i + 1 << ". " << products[i].name << " - " << products[i].price << " ������/����" << endl;
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
        if (item.product.name == "���������� ���") {
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
    cout << "\n���� �������:\n" << endl;
    double totalCost = 0;
    for (const auto& item : cart) {
        cout << item.product.name << " - " << item.quantity << " ������ - " << item.quantity * item.product.price << " ������" << endl;
        totalCost += item.quantity * item.product.price;
    }

    
    double parsleyTeaDiscount = getParsleyTeaDiscount(cart);

   
    double totalDiscount =
        getTotalDiscount(cart, totalCost, parsleyTeaDiscount);

    
    cout << "\n�������� ���������: " << totalCost << " ������" << endl;
    cout << "������ �� ���������� ���: " << setprecision(2) << fixed << parsleyTeaDiscount * 100 << "%" << endl;
    cout << "����� ������: " << setprecision(2) << fixed << totalDiscount * 100 << "%" << endl;
    cout << "����� � ������: " << totalCost * (1 - totalDiscount) << " ������" << endl;
}


void processOnionJuice(vector<CartItem>& cart) {
    int quantity = 0;
    cout << "������� ���������� ������ �������� ����: ";
    cin >> quantity;
    addToCart(cart, Product{ "������� ���", 80 }, quantity);
   
    int freeQuantity = quantity / 4;
    if (freeQuantity > 0) {
        cout << "��� � ������� " << freeQuantity << " ������ �������� ����!" << endl;
        addToCart(cart, Product{ "������� ���", 0 }, freeQuantity);
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    vector<Product> fruitJuices = {
        {"�������� ���", 60},
        {"������������ ���", 70},
        {"����������� ���", 80},
        {"�������� ���", 90}
    };
    vector<Product> vegetableJuices = {
        {"�������� ���", 50},
        {"������� ���", 80},
        {"��������� ���", 65}
    };
    vector<Product> teas = {
        {"��������� ���", 40},
        {"���������� ���", 35}
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
            cout << "�������� ���: ";
            cin >> productChoice;
            int quantity;
            cout << "������� ���������� ������: ";
            cin >> quantity;
            addToCart(cart, getProduct(fruitJuices, productChoice), quantity);
            break;
        }
        case 2: {
            displayCategory(vegetableJuices);
            int productChoice;
            cout << "�������� ���: ";
            cin >> productChoice;
            if (productChoice == 2) {
                processOnionJuice(cart);
            }
            else {
                int quantity;
                cout << "������� ���������� ������: ";
                cin >> quantity;
                addToCart(cart, getProduct(vegetableJuices, productChoice), quantity);
            }
            break;
        }
        case 3: {
            displayCategory(teas);
            int productChoice;
            cout << "�������� ���: ";
            cin >> productChoice;
            int quantity;
            cout << "������� ���������� ������: ";
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
            cout << "�������� �����.\n";
        }
    }
}
