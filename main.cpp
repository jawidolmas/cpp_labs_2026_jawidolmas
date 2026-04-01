#include<iostream>

using namespace std;

struct package {

    string packageID;
    string distinationCity;
    int dimensions[3];
    package *next;

};


package* Incoming_Cargo(package *head, string City, string ID, int arr[3]){

    package *new_Node = new package;

    new_Node->distinationCity = City;
    new_Node->packageID = ID;
    new_Node->dimensions[0] = arr[0];
    new_Node->dimensions[1] = arr[1];
    new_Node->dimensions[2] = arr[2];
    new_Node->next = nullptr;

    new_Node->next = head;
    return new_Node;
}


void travers_print(package *head){

    if (head == nullptr){
        cout << "List is empty\n";
        return;
    }
    package *temp = head;
    while(temp != nullptr){
        cout << "ID: " << temp->packageID
             << ", City: " << temp->distinationCity
             << ", Dimensions: "
             << temp->dimensions[0] << " x "
             << temp->dimensions[1] << " x "
             << temp->dimensions[2]
             << endl;
        temp = temp->next;
    }
}
package* Pop(package* head) {
    if (head == nullptr) {
        cout << "No package to pop.\n";
        return nullptr;
    }

    package* temp = head;
    head = head->next;
    delete temp;
    return head;
}

struct Courier {
    string courierName;
    string vehicleType;
};

const int SIZE = 5;
Courier courierQueue[SIZE];
int front = -1, rear = -1;

void Enqueue(string name, string vehicle){
    if(front == -1){ front = 0; rear = 0; }
    else { rear = (rear + 1) % SIZE; }
    courierQueue[rear].courierName = name;
    courierQueue[rear].vehicleType = vehicle;
    cout << name << " added to queue.\n";
}

void Dequeue(){
    cout << "Courier dispatched -> " << courierQueue[front].courierName
         << ", Vehicle: " << courierQueue[front].vehicleType << "\n";
    if(front == rear){ front = -1; rear = -1; }
    else { front = (front + 1) % SIZE; }
}

void printQueue(){
    if(front == -1){ cout << "Queue is empty!\n"; return; }
    int i = front;
    while(true){
        cout << "Name: " << courierQueue[i].courierName
             << ", Vehicle: " << courierQueue[i].vehicleType << "\n";
        if(i == rear) break;
        i = (i + 1) % SIZE;
    }
}




int main(){
    package *head = nullptr;
    int choice;

    while(true){
        cout << "\n       MENU        \n";
        cout << "1. Arrival\n";
        cout << "2. Courier Register\n";
        cout << "3. Dispatch\n";
        cout << "4. Display\n";
        cout << "5. Exit\n";
        cout << "Choose: ";
        cin >> choice;

        switch(choice){

            case 1: {
                string city, id;
                int dimensions[3];
                cout << "Enter destination City: ";  cin >> city;
                cout << "Enter ID: ";                cin >> id;
                cout << "Enter dimensions (Length, Width, Height): ";
                cin >> dimensions[0] >> dimensions[1] >> dimensions[2];
                head = Incoming_Cargo(head, city, id, dimensions);
                break;
            }

            case 2: {
                string name, vehicle;
                cout << "Enter courier name: ";   cin >> name;
                cout << "Enter vehicle type: ";   cin >> vehicle;
                Enqueue(name, vehicle);
                break;
            }

            case 3: {
                cout << "\n--- DISPATCH ---\n";
                if (head == nullptr) {
                    cout << "No packages to dispatch.\n";
                } else {
                    cout << "Courier " << courierQueue[front].courierName
                         << " is picking up package " << head->packageID << ".\n";
                    head = Pop(head);
                }
                Dequeue();
                break;
            }

            case 4: {
                cout << "\n-- Packages --\n";
                travers_print(head);
                cout << "\n-- Couriers --\n";
                printQueue();
                break;
            }

            case 5: {
                package* temp;
                while(head != nullptr){
                    temp = head;
                    head = head->next;
                    delete temp;
                }
                return 0;
            default:
                cout << "Invalid Input\n";
            }
        }
    }
}
