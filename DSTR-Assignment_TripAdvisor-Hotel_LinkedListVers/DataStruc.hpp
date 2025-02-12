#ifndef DATASTUC_HPP
#define DATASTUC_HPP
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct ReviewAndRating {
    string review;
    string rating;
    ReviewAndRating* prev;
    ReviewAndRating* next;

    // Constructor
    ReviewAndRating(const string& rev, const string& rate) {
        review = rev;
        rating = rate;
        prev = nullptr;
        next = nullptr;
    }
};

struct PowWord {
    string word;
    int frequency;
    PowWord* prev;
    PowWord* next;

    // Default constructor
    PowWord() {
        word = "";
        frequency = 0;
        prev = nullptr;
        next = nullptr;
    }

    // Parameterized constructor to simplify node creation
    PowWord(const string& Word) {
        word = Word;
        frequency = 0;
        prev = nullptr;
        next = nullptr;
    }
};

struct NegWord {
    string word;
    int frequency;
    NegWord* prev;
    NegWord* next;

    // Default constructor
    NegWord() {
        word = "";
        frequency = 0;
        prev = nullptr;
        next = nullptr;
    }

    // Parameterized constructor to simplify node creation
    NegWord(const string& Word) {
        word = Word;
        frequency = 0;
        prev = nullptr;
        next = nullptr;
    }
};




// Define a Linked List Node for Min/Max Used Words
struct WordNode {
    string word;
    WordNode* next;

    WordNode(const string& w) : word(w), next(nullptr) {}
};

class DataIO {
public:
    // Insert review & rating function
    void Insert_RevRat(ReviewAndRating*& head, ReviewAndRating*& tail, const string& rev, const string& rate) {
        ReviewAndRating* newnode = new ReviewAndRating(rev, rate);

        if (head == nullptr) {    // Empty list
            head = newnode;
            tail = newnode;
        }
        else {                    // No empty list
            tail->next = newnode;
            newnode->prev = tail;
            tail = newnode;
        }
        newnode = nullptr;
    }

    // Insert positive word function
    void Insert_PosWord(PowWord*& head, PowWord*& tail, const string& Word) {
        PowWord* newnode = new PowWord(Word);

        if (head == nullptr) {    // Empty list
            head = newnode;
            tail = newnode;
        }
        else {                    // No empty list
            tail->next = newnode;
            newnode->prev = tail;
            tail = newnode;
        }
        newnode = nullptr;
    }

    // Insert negative word function
    void Insert_NegWord(NegWord*& head, NegWord*& tail, const string& Word) {
        NegWord* newnode = new NegWord(Word);

        if (head == nullptr) {    // Empty list
            head = newnode;
            tail = newnode;
        }
        else {                    // No empty list
            tail->next = newnode;
            newnode->prev = tail;
            tail = newnode;
        }
        newnode = nullptr;
    }

    // Select review & rating function
    ReviewAndRating* selectRevRat(ReviewAndRating* head, ReviewAndRating* tail, int index) {
        int curIndex = 0;

        if (head == nullptr) {    // Empty List
            return nullptr;
        }
        else {                    // Not Empty List
            ReviewAndRating* trav = head;

            while (trav != nullptr) {
                if (curIndex == index) {
                    return trav;
                }
                else {
                    trav = trav->next;
                    curIndex++;
                }
            }
        }
        return nullptr;
    }
};

#endif
