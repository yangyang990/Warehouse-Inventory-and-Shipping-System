/**********|**********|**********|
Program: main.cpp
Course: OOPDS
Trimester: 2420
Lecture Class:
Tutorial Class:
Trimester: 2430
Member_1: |  |  |
Member_2: 242UC244PP | Nicholas Beh Zhi Yang | NICHOLAS.BEH.ZHI@student.mmu.edu.my | 011-65215166
Member_3: 242UC24551 | LOW ZHENG HAO | LOW.ZHENG.HAO@student.mmu.edu.my | 013-8888444
**********|**********|**********/

#include <iostream>
#include <string>
#include <stack>
#include <queue>
#include <limits>

using namespace std;

class Category
{
private:
    int id;
    string name;

public:
    Category(int id, const string &name) : id(id), name(name) {}
    int getId() const { return id; }
    string getName() const { return name; }
};

class Product
{
private:
    int id;
    string name;
    double price;
    Category category;

public:
    Product(int id, const string &name, double price, const Category &category) : id(id), name(name), price(price), category(category) {}
    int getId() const { return id; }
    string getName() const { return name; }
    double getPrice() const { return price; }
    Category getCategory() const { return category; }
};

struct Purchase
{
    int quantity;
    Product product;
    Purchase(int q, const Product &p) : quantity(q), product(p) {}
};

int main()
{
    queue<Purchase> order;     // First in, First Out
    stack<Purchase> inventory; // Last in, First Out

    int choice;

    while (true)
    {
        cout << " ***************************************************** " << endl;
        cout << " ----Warehouse Inventory and Shipping System----" << endl;
        cout << " 1. Add incoming item " << endl;
        cout << " 2. Process incoming item " << endl;
        cout << " 3. Display all item in the cart " << endl;
        cout << " 4. Ship item " << endl;
        cout << " 5. View last incoming item " << endl;
        cout << " 6. View next shipment " << endl;
        cout << " 7. Exit " << endl;
        cout << endl;
        cout << " ***************************************************** " << endl;
        cout << endl;
        cout << "Enter your choice: ";

        cin >> choice;
        if (cin.fail())
        {
            cin.clear();                                         // clear error state
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
            cout << "Invalid input! Please enter a number.\n\n";
            continue; // back to menu
        }

        cin.ignore(); // removes the leftover newline character abo will have error

        switch (choice)
        {
        // { } separate block scope prevent error
        case 1:
        {
            int id, catId, qty;
            string name, catName;
            double price;

            cout << "Enter product ID: ";
            cin >> id;
            cin.ignore();

            cout << "Enter product name: ";
            getline(cin, name);

            // Validation(int only are not allowed)
            bool isNumber = true;
            for (char c : name)
            {
                if (!isdigit(c))
                {
                    isNumber = false;
                    break;
                }
            }
            if (isNumber)
            {
                cout << "Product name cannot be only numbers!\n\n";
                break;
            }

            cout << "Enter product price: ";
            cin >> price;
            cin.ignore();

            cout << "Enter category ID: ";
            cin >> catId;
            cin.ignore();

            cout << "Enter category name: ";
            getline(cin, catName);

            cout << "Enter quantity: ";
            cin >> qty;
            cin.ignore();

            if (qty <= 0)
            {
                cout << "Invalid quantity!\n\n";
                break;
            }

            Category c(catId, catName);
            Product p(id, name, price, c);
            inventory.push(Purchase(qty, p));

            cout << qty << "x " << name << " (RM" << price << ") added to inventory under category "
                 << catName << ".\n\n";
            break;
        }

        case 2:
        {
            if (!inventory.empty())
            {
                Purchase buy = inventory.top();
                inventory.pop();
                order.push(buy);
                cout << "Processed \"" << buy.product.getName() << "\" (x" << buy.quantity << ") and added to shipping queue.\n\n";
            }
            else
            {
                cout << "No items in inventory to process!\n\n";
            }
            break;
        }

        case 3:
        {
            if (!order.empty())
            {
                cout << "Items in shipping cart:\n";
                queue<Purchase> temp = order;
                while (!temp.empty())
                {
                    Purchase buy = temp.front();
                    temp.pop();
                    cout << "- " << buy.product.getName() << " (x" << buy.quantity << ", RM" << buy.product.getPrice() << ", Category: " << buy.product.getCategory().getName() << ")\n";
                }
                cout << endl;
            }
            else
            {
                cout << "Shipping cart is empty.\n\n";
            }
            break;
        }

        case 4:
        {
            if (!order.empty())
            {
                Purchase buy = order.front();
                order.pop();
                cout << "Shipping item: " << buy.product.getName()
                     << " (x" << buy.quantity << ", RM" << buy.product.getPrice()
                     << ", Category: " << buy.product.getCategory().getName() << ")\n\n";
            }
            else
            {
                cout << "No items to ship.\n\n";
            }
            break;
        }

        case 5:
        {
            if (!inventory.empty())
            {
                Purchase buy = inventory.top();
                cout << "Last incoming item: " << buy.product.getName() << " (x" << buy.quantity << ", RM" << buy.product.getPrice() << ", Category: " << buy.product.getCategory().getName() << ")\n\n";
            }
            else
            {
                cout << "No incoming items available.\n\n";
            }
            break;
        }

        case 6:
        {
            if (!order.empty())
            {
                Purchase pur = order.front();
                cout << "Next item to ship: " << pur.product.getName()
                     << " (x" << pur.quantity << ", RM" << pur.product.getPrice()
                     << ", Category: " << pur.product.getCategory().getName() << ")\n\n";
            }
            else
            {
                cout << "No shipments pending.\n\n";
            }
            break;
        }

        case 7:
            cout << "Exiting program...\n\n";
            return 0;

        default:
            cout << "Invalid choice! Please try again.\n\n";
        }
    }
    return 0;
}