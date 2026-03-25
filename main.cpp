#include<iostream>
#include<string>
using namespace std;

struct song{
    string title;
    string artist;
    int ratings[3];
    song* next;
    song* prev;
};

song* head = nullptr;
song* tail = nullptr;
song* curr = nullptr;

void addSong(string title, string artist, int r1, int r2, int r3){
    song* new_node = new song();
    new_node->title = title;
    new_node->artist = artist;
    new_node->ratings[0] = r1;
    new_node->ratings[1] = r2;
    new_node->ratings[2] = r3;
    new_node->next = nullptr;
    new_node->prev = nullptr;

    if (head == nullptr){
        head = new_node;
        tail = new_node;
        curr = new_node;
    }
    else{
        new_node->prev = tail;
        tail->next = new_node;
        tail = new_node;
    }
}

void nextSong() {
    if (curr != nullptr && curr->next != nullptr) {
        curr = curr->next;
    }
}

void prevSong() {
    if (curr != nullptr && curr->prev != nullptr) {
        curr = curr->prev;
    }
}

void removeCurrent(){
    if (curr == nullptr) return;

    song *toDelete = curr;

    if (toDelete->prev != nullptr){
        toDelete->prev->next = toDelete->next;
    }
    else{
        head = toDelete->next;
    }

    if (toDelete->next != nullptr){
        toDelete->next->prev = toDelete->prev;
        curr = toDelete->next;
    }
    else {
        tail = toDelete->prev;
        curr = tail;
    }

    delete toDelete;

    if (head == nullptr) {
        curr = nullptr;
    }
}

void displayPlaylist(){
    if (head == nullptr) {
        cout << "Playlist is empty!\n";
        return;
    }

    song *temp = head;
    while(temp != nullptr){
        if (temp == curr){
            cout << "-> ";
        } else {
            cout << "   ";
        }
        cout << temp->title << " by " << temp->artist << endl;
        cout << "Ratings: ";
        for (int i = 0; i < 3; i++){
            cout << temp->ratings[i];
            if (i < 2) cout << ", ";
        }
        cout << endl << endl;
        temp = temp->next;
    }
}

int main(){
    addSong("Unuttun mu?", "Sezen Aksu", 5, 4, 5);
    addSong("Hosca kal", "Emre Aydin", 3, 2, 4);
    addSong("Unutulacak Dunler", "Gazapizm", 1, 2, 5);

    int choice = 0;
    while (choice != 5) {
        displayPlaylist();
        cout << "1.Next Song\n";
        cout << "2.Previous Song\n";
        cout << "3.Remove Current\n";
        cout << "4.Add New Song\n";
        cout << "5.Exit\n";
        cout << "Choose: ";
        cin >> choice;
        cin.ignore();

        if(choice == 1){
            nextSong();
        }
        else if(choice == 2){
            prevSong();
        }
        else if(choice == 3){
            removeCurrent();
        }
        else if(choice == 4){
            string title, artist;
            int r1, r2, r3;
            cout << "Enter song title: ";
            getline(cin, title);
            cout << "Enter artist name: ";
            getline(cin, artist);
            cout << "Enter 3 ratings: ";
            cin >> r1 >> r2 >> r3;
            cin.ignore();
            addSong(title, artist, r1, r2, r3);
        }
        else if(choice == 5){
            cout << "Exiting...\n";
        }
        else {
            cout << "Invalid choice!\n";
        }
    }
    return 0;
}
