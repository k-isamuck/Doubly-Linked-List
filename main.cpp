#include <iostream>

// Muckerman_Kaylee_130526510

//Data Class: This is what goes inside your Node
class Process {
public:
    std::string processName;
    int totalTime;
    Process (std::string processName, int totalTime){
        this->processName = processName;
        this->totalTime = totalTime;
    }
    void updateRunTime() {
        totalTime--;
    }
    void print () {
        std::cout << "Process " << processName << " " << totalTime << " seconds." << std::endl;
    }
};

// Node Class: Node for the DoublyLinkedList
template <typename T> class Node {
public:
    T *data;
    Node<T> *next;
    Node<T> *prev;
    Node(T *data) {
        this->data = data;
        next = nullptr;
        prev = nullptr;
    }
    void print () {
        data->print ();
    }
};


//CircularDoublyLinkedList Class: Container for Nodes
template <typename T> class CircularDLL {
private:
    Node<T> *head;
    Node<T> *tail;
    int length;
public:
    // Constructor
    CircularDLL() {
        length = 0;
        head = nullptr;
        tail = nullptr;
    }

    CircularDLL(T *data) {
        length = 0;
        head = nullptr;
        tail = nullptr;
        insertProcess(data);
    }

    //Destructor
    ~CircularDLL() {
        Node<T> *currDelete = tail->prev;
        while (head != nullptr) {
            delete tail;
            currDelete = currDelete->prev;
            if (head->next == head) {
                head = nullptr;
            }
        }
    }

    void printList() {
        using namespace std;
        int prosNumber = 1;
        if(length == 0){
            return;
        }
        Node<T> *currN = head;
        cout << prosNumber << ". ";
        currN->print();
        currN = currN->next;
        while(currN != head){
            prosNumber++;
            cout << prosNumber << ". ";
            currN->print();
            currN = currN->next;
        }
    }

//Insert a process
    void insertProcess(T *data) {
        length++;
        Node<T> *newN = new Node<T>(data);
        if(head == nullptr){
            head = newN;
            tail = newN;
            newN->next = newN;
            newN->prev = newN;
            return;
        }
        newN->prev = tail;
        newN->next = head;
        tail->next = newN;
        head->prev = newN;
        tail = newN;
    }

//Delete a Process
    void deleteProcess(Node<T> *node) {
        if(length == 0){
            return;
        }else if(length == 1){
            head = nullptr;
        }else if(node == head){
            Node<T> *nodeInFront = node->prev;
            Node<T> *nodeAfter = node->next;
            nodeInFront->next = nodeAfter;
            nodeAfter->prev = nodeInFront;
            head = nodeAfter;
        }else{
            Node<T> *nodeInFront = node->prev;
            Node<T> *nodeAfter = node->next;
            nodeInFront->next = nodeAfter;
            nodeAfter->prev = nodeInFront;
        }
        free(node);
        length--;
    }

    void updateTime(){
        Node<T> *currUpdated = head;
        do{
            currUpdated->data->updateRunTime();
            currUpdated = currUpdated->next;
        }while(currUpdated != head);
    }

    bool isEmpty(){
        if(length == 0){
            return true;
        }
        return false;
    }

    void deleteFinishedProcess(){
        Node<T> *next = head;
        Node<T> *curr = next;
        int counter = length;
        do {
            next = curr->next;
            if(curr->data->totalTime <= 0){
                deleteProcess(curr);
            }
            curr = next;
            counter--;
        } while ( counter > 0 );
    }
};



int main() {
    using namespace std;
    int userQuantum;
    int cycleNumber = 1;
    int timePassed = 0;
    CircularDLL<Process> dll = CircularDLL<Process>();

    dll.insertProcess( new Process("A", 10));
    dll.insertProcess( new Process("B", 12));
    dll.insertProcess( new Process("C", 8));
    dll.insertProcess( new Process("D", 5));
    dll.insertProcess( new Process("E", 10));

    cout << "Enter Quantum Time";
    cin >> userQuantum;
    cout << "Repopulating with processes" << endl;
    dll.printList();
    do{
        string userAns;
        string prosName;
        int prosTime;
        timePassed += userQuantum;
        cout << "Add new process? (Enter Y/N)";
        cin >> userAns;
        cout << "\n" << endl;
        if(userAns == "Y"){
            cout << "Enter New Process Name: ";
            cin >> prosName;
            cout << "\nEnter Total Process Time: ";
            cin >> prosTime;
            cout << "\nProcess Added." << endl;
            dll.insertProcess( new Process(prosName, prosTime));
        }
        cout << "Running Cycle " << cycleNumber << endl;
        cout << "After cycle " << cycleNumber << " -" << timePassed << " second elapses - state of processes is as follows:" << endl;
        for(int i = 0; i < userQuantum; i++) {
            dll.updateTime();
        }
        dll.deleteFinishedProcess();
        dll.printList();
        cycleNumber++;
    }while(!dll.isEmpty());
    cout << "All processes are completed." << endl;

    return 0;
}
