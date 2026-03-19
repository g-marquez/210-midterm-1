//*****************************************************************************
// COMSC-210 | Midterm 1 | Gabriel Marquez
// Description: this program comments the starter code 210-midterm-starter-1.cpp
// file provided in Canvas and demonstrates a class method every_other_element().
//*****************************************************************************

#include <iostream>
using namespace std;

//constants that will be used in main()
const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;

class DoublyLinkedList { //class declaration for DoublyLinkedList
private: //lays out private members of the class
    struct Node { //struct declaration for the nose of a doubly linked list
        int data; //int data member of the Node
        Node* prev; //pointer that points to the previous node in the list
        Node* next; //pointer that points to the next node in the list
        //default constructor that takes a val parameter for data
        //and assigns default nullptr to prev and next
        Node(int val, Node* p = nullptr, Node* n = nullptr) {
            data = val; 
            prev = p;
            next = n;
        }
    };

    Node* head; //tracks the head of the list
    Node* tail; //tracks the tail of the list

public: //lays out public methods for the class
    //default constructor for the doubly linked list
    //assigns nullptr to head and tail by default
    DoublyLinkedList() { head = nullptr; tail = nullptr; }

    //method to insert a value after a given position in the list
    //takes 2 parameters, value & position
    void insert_after(int value, int position) {
        if (position < 0) { //validates position parameter
            cout << "Position must be >= 0." << endl;
            return;
        }

        Node* newNode = new Node(value); //dynamically allocate new Node to insert
        if (!head) { //if head == nullptr (list empty)
            head = tail = newNode; //set head & tail = the only node in the list
            return;
        }

        Node* temp = head; //declare temp node and assign head's value to it
        //iterate through the list position number of times
        //also checking that temp is valid
        for (int i = 0; i < position && temp; ++i)
            temp = temp->next; //go on to the next node

        if (!temp) { //position given was larger than the list size
            cout << "Position exceeds list size. Node not inserted.\n";
            delete newNode; //deallocate memory in this case
            return;
        }

        //arrived at correct position
        newNode->next = temp->next; //
        newNode->prev = temp;
        if (temp->next)
            temp->next->prev = newNode;
        else
            tail = newNode;
        temp->next = newNode;
    }

    void delete_val(int value) {
        if (!head) return;

        Node* temp = head;
        
        while (temp && temp->data != value)
            temp = temp->next;

        if (!temp) return; 

        if (temp->prev)
            temp->prev->next = temp->next;
        else
            head = temp->next; 

        if (temp->next)
            temp->next->prev = temp->prev;
        else
            tail = temp->prev; 

        delete temp;
    }

    void delete_pos(int pos) {
        if (!head) {
            cout << "List is empty." << endl;
            return;
        }
    
        if (pos == 1) {
            pop_front();
            return;
        }
    
        Node* temp = head;
    
        for (int i = 1; i < pos; i++){
            if (!temp) {
                cout << "Position doesn't exist." << endl;
                return;
            }
            else
                temp = temp->next;
        }
        if (!temp) {
            cout << "Position doesn't exist." << endl;
            return;
        }
    
        if (!temp->next) {
            pop_back();
            return;
        }
    
        Node* tempPrev = temp->prev;
        tempPrev->next = temp->next;
        temp->next->prev = tempPrev;
        delete temp;
    }

    void push_back(int v) {
        Node* newNode = new Node(v);
        if (!tail)
            head = tail = newNode;
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }
    
    void push_front(int v) {
        Node* newNode = new Node(v);
        if (!head)
            head = tail = newNode;
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }
    
    void pop_front() {

        if (!head) {
            cout << "List is empty." << endl;
            return;
        }

        Node * temp = head;

        if (head->next) {
            head = head->next;
            head->prev = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    void pop_back() {
        if (!tail) {
            cout << "List is empty." << endl;
            return;
        }
        Node * temp = tail;

        if (tail->prev) {
            tail = tail->prev;
            tail->next = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
    void print() {
        Node* current = head;
        if (!current) {
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    void print_reverse() {
        Node* current = tail;
        if (!current) { 
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->data << " ";
            current = current->prev;
        }
        cout << endl;
    }
};

int main() {
    cout << MIN_NR + MIN_LS + MAX_NR + MAX_LS;  // dummy statement to avoid compiler warning

    
    return 0;
}