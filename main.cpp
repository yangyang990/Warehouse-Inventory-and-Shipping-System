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
#include <fstream>
#include <sstream>

using namespace std;

template <typename T>
class MyStack
{
private:
    struct Node
    {
        T data;
        Node *next;
        Node(const T &d) : data(d), next(nullptr) {}
    };
    Node *topNode;

public:
    MyStack() : topNode(nullptr) {}

    ~MyStack()
    {
        while (!empty())
            pop();
    }

    void push(const T &value)
    {
        Node *newNode = new Node(value);
        newNode->next = topNode;
        topNode = newNode;
    }

    void pop()
    {
        if (!empty())
        {
            Node *temp = topNode;
            topNode = topNode->next;
            delete temp;
        }
    }

    T &top()
    {
        return topNode->data;
    }

    bool empty() const
    {
        return topNode == nullptr;
    }

    // For iteration (copy stack without modifying original)
    Node *getTopNode() const { return topNode; }
};

template <typename T>
class MyQueue
{
private:
    struct Node
    {
        T data;
        Node *next;
        Node(const T &d) : data(d), next(nullptr) {}
    };
    Node *frontNode;
    Node *rearNode;

public:
    MyQueue() : frontNode(nullptr), rearNode(nullptr) {}

    ~MyQueue()
    {
        while (!empty())
            pop();
    }

    void push(const T &value)
    {
        Node *newNode = new Node(value);
        if (rearNode)
            rearNode->next = newNode;
        else
            frontNode = newNode;
        rearNode = newNode;
    }

    void pop()
    {
        if (!empty())
        {
            Node *temp = frontNode;
            frontNode = frontNode->next;
            if (!frontNode)
                rearNode = nullptr;
            delete temp;
        }
    }

    T &front()
    {
        return frontNode->data;
    }

    bool empty() const
    {
        return frontNode == nullptr;
    }

    // For iteration (copy queue without modifying original)
    Node *getFrontNode() const { return frontNode; }
};

class Category
{
private:
    int id;
    string name;

public:
    Category(int id = 0, const string &name = "") : id(id), name(name) {}
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
    Product(int id = 0, const string &name = "", double price = 0, const Category &category = Category())
        : id(id), name(name), price(price), category(category) {}
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

void saveInventory(MyStack<Purchase> &inventory)
{
    ofstream outFile("inventory.txt");
    if (!outFile)
    {
        cout << "Error saving inventory!\n";
        return;
    }

    // Traverse manually
    auto node = inventory.getTopNode();
    while (node)
    {
        Purchase p = node->data;
        outFile << p.product.getId() << ","
                << p.product.getName() << ","
                << p.product.getPrice() << ","
                << p.product.getCategory().getId() << ","
                << p.product.getCategory().getName() << ","
                << p.quantity << "\n";
        node = node->next;
    }
    outFile.close();
}

void saveOrders(MyQueue<Purchase> &order)
{
    ofstream outFile("orders.txt");
    if (!outFile)
    {
        cout << "Error saving orders!\n";
        return;
    }

    auto node = order.getFrontNode();
    while (node)
    {
        Purchase p = node->data;
        outFile << p.product.getId() << ","
                << p.product.getName() << ","
                << p.product.getPrice() << ","
                << p.product.getCategory().getId() << ","
                << p.product.getCategory().getName() << ","
                << p.quantity << "\n";
        node = node->next;
    }
    outFile.close();
}

void loadInventory(MyStack<Purchase> &inventory)
{
    ifstream inFile("inventory.txt");
    if (!inFile)
        return;

    string line;
    while (getline(inFile, line))
    {
        stringstream ss(line);
        string token;

        int id, catId, qty;
        string name, catName;
        double price;

        getline(ss, token, ',');
        id = stoi(token);
        getline(ss, name, ',');
        getline(ss, token, ',');
        price = stod(token);
        getline(ss, token, ',');
        catId = stoi(token);
        getline(ss, catName, ',');
        getline(ss, token, ',');
        qty = stoi(token);

        Category c(catId, catName);
        Product p(id, name, price, c);
        inventory.push(Purchase(qty, p));
    }
    inFile.close();
}

void loadOrders(MyQueue<Purchase> &order)
{
    ifstream inFile("orders.txt");
    if (!inFile)
        return;

    string line;
    while (getline(inFile, line))
    {
        stringstream ss(line);
        string token;

        int id, catId, qty;
        string name, catName;
        double price;

        getline(ss, token, ',');
        id = stoi(token);
        getline(ss, name, ',');
        getline(ss, token, ',');
        price = stod(token);
        getline(ss, token, ',');
        catId = stoi(token);
        getline(ss, catName, ',');
        getline(ss, token, ',');
        qty = stoi(token);

        Category c(catId, catName);
        Product p(id, name, price, c);
        order.push(Purchase(qty, p));
    }
    inFile.close();
}

int main()
{
    MyQueue<Purchase> order;     // FIFO
    MyStack<Purchase> inventory; // LIFO

    loadInventory(inventory);
    loadOrders(order);

    int choice;

    while (true)
    {
        cout << " ***************************************************** " << endl;
        cout << " ----Warehouse Inventory and Shipping System----" << endl;
        cout << " 1. Add incoming item " << endl;
        cout << " 2. Process incoming item " << endl;
        cout << " 3. Display all items " << endl;
        cout << " 4. Ship item " << endl;
        cout << " 5. View last incoming item " << endl;
        cout << " 6. View next shipment " << endl;
        cout << " 7. Exit " << endl;
        cout << " ***************************************************** " << endl;
        cout << "Enter your choice: ";

        cin >> choice;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Please enter a number.\n\n";
            continue;
        }
        cin.ignore();

        switch (choice)
        {
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

            // Validation (reject only numbers)
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
            saveInventory(inventory);
            saveOrders(order);

            cout << qty << "x " << name << " (RM" << price << ") added to inventory under category " << catName << ".\n\n";
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
            saveInventory(inventory);
            saveOrders(order);
            break;
        }

        case 3:
        {
            cout << "Items in Inventory:\n";
            auto node = inventory.getTopNode();
            if (!node)
                cout << "Inventory is empty.\n";
            while (node)
            {
                Purchase buy = node->data;
                cout << "- " << buy.product.getName()
                     << " (x" << buy.quantity
                     << ", RM" << buy.product.getPrice()
                     << ", Category: " << buy.product.getCategory().getName() << ")\n";
                node = node->next;
            }

            cout << "\nItems in Shipping Cart:\n";
            auto qnode = order.getFrontNode();
            if (!qnode)
                cout << "Shipping cart is empty.\n";
            while (qnode)
            {
                Purchase buy = qnode->data;
                cout << "- " << buy.product.getName()
                     << " (x" << buy.quantity
                     << ", RM" << buy.product.getPrice()
                     << ", Category: " << buy.product.getCategory().getName() << ")\n";
                qnode = qnode->next;
            }
            cout << endl;
            break;
        }

        case 4:
        {
            if (!order.empty())
            {
                Purchase buy = order.front();
                order.pop();
                cout << "Shipping item: " << buy.product.getName()
                     << " (x" << buy.quantity
                     << ", RM" << buy.product.getPrice()
                     << ", Category: " << buy.product.getCategory().getName() << ")\n\n";
            }
            else
            {
                cout << "No items to ship.\n\n";
            }
            saveInventory(inventory);
            saveOrders(order);
            break;
        }

        case 5:
        {
            if (!inventory.empty())
            {
                Purchase buy = inventory.top();
                cout << "Last incoming item: " << buy.product.getName()
                     << " (x" << buy.quantity
                     << ", RM" << buy.product.getPrice()
                     << ", Category: " << buy.product.getCategory().getName() << ")\n\n";
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
                     << " (x" << pur.quantity
                     << ", RM" << pur.product.getPrice()
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