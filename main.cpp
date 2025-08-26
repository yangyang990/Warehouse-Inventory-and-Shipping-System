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

using namespace std;

queue<string> order;     // First in, First Out
stack<string> inventory; // Last in, First Out

int main()
{
    int choice;

    while (true)
    {
        cout << " ****************************** " << endl;
        cout << " ----MENU----" << endl;
        cout << " 1. Add incoming item " << endl;
        cout << " 2. Process incoming item " << endl;
        cout << " 3. Ship item " << endl;
        cout << " 4. View last incoming item " << endl;
        cout << " 5. View next shipment " << endl;
        cout << " 6. Exit " << endl;
        cout << endl;
        cout << " ****************************** " << endl;
        cout << endl;
        cout << "Enter your choice: ";

        cin >> choice;

        switch (choice)
        {
        case 6:
            cout << "Exiting program...\n";
            cout << endl;
            return 0;
        }
    }
    return 0;
}