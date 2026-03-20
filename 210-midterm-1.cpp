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

        Node* temp = head; //declare temp pointer and assign head's value to it
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
        newNode->next = temp->next; //set newNode's next pointer to temp->next
        newNode->prev = temp; //set newNode's prev pointer to temp itself
        if (temp->next) //if temp->next is not a nullptr
            temp->next->prev = newNode; //set it's prev pointer to newNode
        else
            tail = newNode; //else set tail to newNode instead
        temp->next = newNode; //set temp->next to newNode as final step
        //now pointers have been successfully adjusted
    }

    //method to delete a node based on given value
    //takes 1 parameter, value
    void delete_val(int value) {
        if (!head) return; //return if the list is empty

        Node* temp = head; //declare temp pointer and assign head's value to it
        
        //loop through list
        //checking to see that temp is valid and temp->data is not the value
        //we want to delete
        while (temp && temp->data != value)
            temp = temp->next; //go to next node if so

        if (!temp) return; //value was not found

        if (temp->prev) //if temp->prev is not null (not the head of list)
            temp->prev->next = temp->next; //reroute temp->prev->next to temp->next
        else
            head = temp->next; //else, move head over one node

        if (temp->next) //if we're not at the tail
            temp->next->prev = temp->prev; //reroute temp->next's prev pointer
        else
            tail = temp->prev; //else, adjust the tail pointer

        delete temp; //now safe to delete temp
    }

    //method to delete based on position
    //takes 1 parameter, pos
    void delete_pos(int pos) {
        if (!head) { //return if list is empty
            cout << "List is empty." << endl;
            return;
        }
        
        //if pos == 1, delete that first node and be done
        if (pos == 1) { 
            pop_front();
            return;
        }
    
        Node* temp = head; //declare temp pointer and assign head's value to it
    
        //iterate through the list pos number of times 
        for (int i = 1; i < pos; i++){
            if (!temp) { //return if temp is a nullptr
                cout << "Position doesn't exist." << endl;
                return;
            }
            else //else, move to the next node
                temp = temp->next;
        }
        if (!temp) { //if we make it through th whole list
            cout << "Position doesn't exist." << endl;
            return; //return because pos does not exist
        }
    
        if (!temp->next) { //if temp->next is null (at the end of the list)
            pop_back(); //delete it
            return;
        }
    
        //declare a tempPrev pointer and set it to temp->prev
        //to not lose your spot
        Node* tempPrev = temp->prev;
        tempPrev->next = temp->next; //set it's next pointer to temp->next
        temp->next->prev = tempPrev; //set next's prev pointer to tempPrev
        delete temp; //now safe to delete temp
    }

    //method to add a node to the tail of the list
    //takes 1 parameter, v
    void push_back(int v) {
        //dynamically allocate a new Node with data value v
        Node* newNode = new Node(v);
        if (!tail) //no tail, empty list
            head = tail = newNode; //newNode becomes both head and tail
        else {
            tail->next = newNode; //else, add newNode to end of list
            newNode->prev = tail; //set newNode's prev pointer to tail
            tail = newNode; //adjust tail to point to newNode (new end of list)
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