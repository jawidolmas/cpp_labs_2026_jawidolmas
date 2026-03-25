#include <iostream>
#include <string>
using namespace std;

struct Song {
    string title;
    string artist;
    int ratings[3];
    Song* next;
    Song* prev;

    Song(string t, string a, int r1, int r2, int r3)
        : title(t), artist(a), ratings{r1, r2, r3}, next(nullptr), prev(nullptr) {}
};

class Playlist {
private:
    Song* head = nullptr;
    Song* tail = nullptr;
    Song* curr = nullptr;

public:
    void addSong(string title, string artist, int r1, int r2, int r3) {
        Song* newSong = new Song(title, artist, r1, r2, r3);
        if (head == nullptr) {
            head = tail = curr = newSong;
        } else {
            newSong->prev = tail;
            tail->next = newSong;
            tail = newSong;
        }
    }

    void nextSong() {
        if (curr && curr->next) {
            curr = curr->next;
        }
    }

    void prevSong() {
        if (curr && curr->prev) {
            curr = curr->prev;
        }
    }

    void removeCurrent() {
        if (curr == nullptr) return;

        Song* toDelete = curr;

        if (toDelete->prev) {
            toDelete->prev->next = toDelete->next;
        } else {
            head = toDelete->next;
        }

        if (toDelete->next) {
            toDelete->next->prev = toDelete->prev;
            curr = toDelete->next;
        } else {
            tail = toDelete->prev;
            curr = tail;
        }

        delete toDelete;

        if (head == nullptr) {
            curr = nullptr;
        }
    }

    void displayPlaylist() {
        if (head == nullptr) {
            cout << "Playlist is empty!\n";
            return;
        }

        Song* temp = head;
        while (temp != nullptr) {
            if (temp == curr) {
                cout << "-> ";
            } else {
                cout << "   ";
            }
            cout << temp->title << " by " << temp->artist << endl;
            cout << "Ratings: ";
            for (int i = 0; i < 3; i++) {
                cout << temp->ratings[i];
                if (i < 2) cout << ", ";
            }
            cout << endl << endl;
            temp = temp->next;
        }
    }

    ~Playlist() {
        Song* temp = head;
        while (temp) {
            Song* next = temp->next;
            delete temp;
            temp = next;
        }
    }
};

int main() {
    Playlist playlist;

    playlist.addSong("Unuttun mu?", "Sezen Aksu", 5, 4, 5);
    playlist.addSong("Hosca kal", "Emre Aydin", 3, 2, 4);
    playlist.addSong("Unutulacak Dunler", "Gazapizm", 1, 2, 5);

    int choice = 0;

    while (choice != 5) {
        playlist.displayPlaylist();
        cout << "1. Next Song\n";
        cout << "2. Previous Song\n";
        cout << "3. Remove Current\n";
        cout << "4. Add New Song\n";
        cout << "5. Exit\n";
        cout << "Choose: ";
        cin >> choice;
        cin.ignore();

        switch(choice) {
            case 1: playlist.nextSong(); break;
            case 2: playlist.prevSong(); break;
            case 3: playlist.removeCurrent(); break;
            case 4: {
                string title, artist;
                int r1, r2, r3;
                cout << "Enter song title: ";
                getline(cin, title);
                cout << "Enter artist name: ";
                getline(cin, artist);
                cout << "Enter 3 ratings: ";
                cin >> r1 >> r2 >> r3;
                cin.ignore();
                playlist.addSong(title, artist, r1, r2, r3);
                break;
            }
            case 5: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice!\n";
        }
    }
    return 0;
}
