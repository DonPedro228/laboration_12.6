#include <iostream>
#include <fstream>
using namespace std;

struct Elem
{
	Elem* link;
	int info;
};

int FindElem(Elem* L, int value)
{
    while (L != nullptr)
    {
        if (L->info == value) {
            return value;
        }
        L = L->link;
    }

    return -1;
}

void enqueue(Elem*& front, Elem*& rear, int value)
{
    Elem* temp = new Elem;
    temp->info = value;
    temp->link = nullptr;
    if (rear == nullptr) {
        front = rear = temp;
    }
    else {
        rear->link = temp;
        rear = temp;
    }
}

int dequeue(Elem*& front, Elem*& rear)
{
    if (front == nullptr) {
        cerr << "Queue is empty." << endl;
        return -1; 
    }
    else {
        int value = front->info;
        Elem* temp = front;
        front = front->link;
        if (front == nullptr) {
            rear = nullptr;
        }
        delete temp;
        return value;
    }
}

bool isEmpty(Elem* front)
{
    return front == nullptr;
}

void splitQueue(Elem*& front1, Elem*& rear1, Elem*& front2, Elem*& rear2, int value)
{
    Elem* current = front1;
    Elem* prev = nullptr;


    while (current != nullptr && current->info != value)
    {
        prev = current;
        current = current->link;
    }

    if (current == nullptr)
        return;

   
    if (prev == nullptr) 
    {
        front2 = front1;
        rear2 = rear1;
        front1 = current->link;
        if (front1 == nullptr)
            rear1 = nullptr;
    }
    else
    {
        front2 = current;
        rear2 = rear1;
        prev->link = nullptr; 
    }
}


int main() {
    Elem* front1 = nullptr;
    Elem* rear1 = nullptr;
    Elem* front2 = nullptr;
    Elem* rear2 = nullptr;

    int elem;
    cout << "Find number: "; cin >> elem;

    ifstream file("12.txt");
    if (!file.is_open()) {
        cerr << "Unable to open file." << endl;
        return 1;
    }

    int number;
    while (file >> number) {
        enqueue(front1, rear1, number);
    }
    file.close();

    if (FindElem(front1, elem) != -1) {
        cout << "Element found: " << elem << endl;
        splitQueue(front1, rear1, front2, rear2, elem);
    }
    else {
        cout << "Element not found!" << endl;
    }

    cout << "First queue: ";
    while (!isEmpty(front1)) {
        cout << dequeue(front1, rear1) << " ";
    }
    cout << endl;

    cout << "Second queue: ";
    while (!isEmpty(front2)) {
        cout << dequeue(front2, rear2) << " ";
    }
    cout << endl;

    

    return 0;
}

