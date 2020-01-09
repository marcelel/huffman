#include <iostream>
#include <string>

using namespace std;

// Definicja węzła drzewa kodu bezprzystankowego
struct HTNode
{
    HTNode * next;
    HTNode * left;
    HTNode * right;
    char value;
    int count;
};

// Tworzy listę wierzchołków
void makeList (HTNode * & root, string s) {
    HTNode * p;
    root = nullptr;                    // Tworzymy pustą listę
    for (char i : s) { // Tworzymy węzły i zliczamy znaki
        p = root;                     // Szukamy na liście znaku s [ i ]

        while (p && (p->value != i)) {
            p = p->next;
        }

        if (!p) {                       // Jeśli go nie ma, to
            p = new HTNode;             // tworzymy dla niego nowy węzełFASF
            p->next = root;            // Węzeł trafi na początek listy
            p->left = nullptr;            // Ustawiamy pola węzła
            p->right = nullptr;
            p->value = i;
            p->count = 0;
            root = p;               // Wstawiamy węzeł na początek listy
        }

        p->count++;                   // Zwiększamy licznik wystąpień znaku
    }

    int tmp_count;
    char tmp_value;
    bool sorted;

    do {                             // Listę sortujemy rosnąco względem count
        sorted = true;                     // Zakładamy posortowanie listy
        p = root;                     // Sortujemy od pierwszego elementu

        while (p->next) {
            if (p->count > p->next->count) {
                tmp_value = p->value;               // Wymieniamy zawartość dwóch kolejnych elementów
                p->value = p->next->value;
                p->next->value = tmp_value;
                tmp_count = p->count;
                p->count = p->next->count;
                p->next->count = tmp_count;
                sorted = false;                // Sygnalizujemy nieposortowanie listy
            }

            p = p->next;                // Przechodzimy do następnego elementu
        }
    } while (!sorted);
}

// Tworzy z listy drzewo Huffmana
void makeTree (HTNode * & root ) {
    HTNoode *p, *r, *v1, *v2;

    while (true) {
        v1 = root;                    // Pobieramy z listy dwa pierwsze węzły
        v2 = v1->next;

        if (!v2) {
            break;                // Jeśli tylko jeden element, zakończ
        }

        root = v2->next;              // Lista bez v1 i v2

        p = new HTNode;               // Tworzymy nowy węzeł
        p->left = v1;                 // Dołączamy do niego v1 i v2
        p->right = v2;                // i wyliczamy nową częstość
        p->count = v1->count + v2->count;

        // Węzeł wstawiamy z powrotem na listę tak, aby była uporządkowana

        if (!root || (p->count <= root->count)) {
            p->next = root;
            root = p;
            continue;
        }

        r = root;

        while (r->next && (p->count > r->next->count)) {
            r = r->next;
        }

        p->next = r->next;
        r->next = p;
    }
}

// Drukuje zawartość drzewa Huffmana
void printCoding (HTNode * p, string b) {
    if (!p->left) {
        cout << p->value << " " << b << endl;
    } else {
        printCoding(p->left, b + "0");
        printCoding(p->right, b + "1");
    }
}

// Koduje znak
bool codeValue (char c, HTNode * p, string b) {
    if (!p->left) {
        if (c != p->value) {
            return false;
        } else {
            cout << b;
            return true;
        }
    } else {
        return codeValue(c, p->left, b + "0") || codeValue(c, p->right, b + "1");
    }
}

// Koduje tekst kodem Huffmana
void codeHuffman ( HTNode * root, string s )
{

    for (char i : s) { // Kodujemy poszczególne znaki
        codeValue(i, root, "");
    }
}


int main( )
{
    HTNode * root;                   // Początek listy / korzeń drzewa
    string s = "AABBACBCCDDDDBAAAAAAAAAABAAAABDCCCCABADDA";                        // Przetwarzany łańcuch
//    getline ( cin, s );                 // Czytamy łańcuch wejściowy

    makeList(root, s);               // Tworzymy listę wierzchołków
    makeTree(root);                  // Tworzymy drzewo kodu Huffmana
    printCoding(root, "");             // Wyświetlamy kody znaków
    codeHuffman ( root, s );            // Kodujemy i wyświetlamy wynik

    return 0;
}
