#ifndef SUMMARY_HPP
#define SUMMARY_HPP

#include <sstream>
#include <fstream>
#include <algorithm>
#include <limits.h>
#include <string>
#include <chrono>
#include <iostream>
#include "ReadInput.hpp"
using namespace std;
using namespace chrono;

// Define the Word Frequency Node structure
struct WordFreqNode {
    string word;
    int frequency;
    WordFreqNode* next;

    WordFreqNode(const string& Word, int freq = 0) {
        word = Word;
        frequency = freq;
        next = nullptr;
    }
};

// Define a Linked List Node for Min/Max Used Words
struct WordNode {
    string word;
    WordNode* next;

    WordNode(const string& w) : word(w), next(nullptr) {}
};

// Function prototypes
inline void displayWordFreq(WordFreqNode* head, const string& wordType);
inline void CheckWordOcc(string curReview, PowWord* posHead, NegWord* negHead, int& totalPosCount, int& totalNegCount);
inline void findMinMaxUsedWords(PowWord* posHead, NegWord* negHead, WordNode*& minUsedWordsHead, WordNode*& maxUsedWordsHead, int& minFreq, int& maxFreq);
inline void displayWordUsage(WordNode* wordList, int freq, const string& usageType);
void addToList(WordNode*& head, const string& word);
void deleteList(WordNode*& head);

// Main summary function
inline void summary(ReviewAndRating* reviewHead, PowWord* posHead, NegWord* negHead, const int lineNum) {
    cout << "\nProcessing the reviews... This might take some time. Please wait." << endl;
    auto start = high_resolution_clock::now();  // Start the timer

    int totalPosCount = 0;
    int totalNegCount = 0;

    // Traverse through the ReviewAndRating linked list
    ReviewAndRating* currentReview = reviewHead;
    while (currentReview != nullptr) {
        string curReview = currentReview->review;

        // Convert review to lowercase for case-insensitive matching
        transform(curReview.begin(), curReview.end(), curReview.begin(), ::tolower);

        // Check occurrences of positive and negative words
        CheckWordOcc(curReview, posHead, negHead, totalPosCount, totalNegCount);

        currentReview = currentReview->next;  // Move to the next review
    }

    // Title design
    cout << "\n \n";
    cout << "\033[0;34m"; // Set the text color to bright blue
    cout << "---------------------------------------" << endl;
    cout << "            Review Summary             " << endl;
    cout << "---------------------------------------" << endl;
    cout << "\033[0m";
    cout << "\n";

    // Display total counts of positive and negative words
    cout << "Total Reviews = " << lineNum << endl;
    cout << "Total Counts of positive words = " << totalPosCount << endl;
    cout << "Total Counts of negative words = " << totalNegCount << endl;

    // Display word frequencies
    cout << "\nFrequency of Positive Words:\n";
    PowWord* posCurrent = posHead;
    while (posCurrent != nullptr) {
        if (posCurrent->frequency > 0) {
            cout << posCurrent->word << " = " << posCurrent->frequency << " times\n";
        }
        posCurrent = posCurrent->next;
    }

    cout << "\nFrequency of Negative Words:\n";
    NegWord* negCurrent = negHead;
    while (negCurrent != nullptr) {
        if (negCurrent->frequency > 0) {
            cout << negCurrent->word << " = " << negCurrent->frequency << " times\n";
        }
        negCurrent = negCurrent->next;
    }

    // Find the minimum and maximum used words
    int minFreq = INT_MAX;
    int maxFreq = 0;
    WordNode* minUsedWordsHead = nullptr;
    WordNode* maxUsedWordsHead = nullptr;

    findMinMaxUsedWords(posHead, negHead, minUsedWordsHead, maxUsedWordsHead, minFreq, maxFreq);

    // Display max & min used words
    displayWordUsage(maxUsedWordsHead, maxFreq, "Maximum");
    displayWordUsage(minUsedWordsHead, minFreq, "Minimum");

    // Clean up dynamically allocated memory for minUsedWords and maxUsedWords
    deleteList(minUsedWordsHead);
    deleteList(maxUsedWordsHead);

    auto end = high_resolution_clock::now();  // End the timer
    auto duration = duration_cast<seconds>(end - start);

    int minutes = duration.count() / 60;
    int seconds = duration.count() % 60;

    cout << "\nTime taken: " << minutes << " minutes " << seconds << " seconds" << endl;
}

// Check word occurrences function
inline void CheckWordOcc(string curReview, PowWord* posHead, NegWord* negHead, int& totalPosCount, int& totalNegCount) {
    // Traverse positive words
    PowWord* currentPos = posHead;
    while (currentPos != nullptr) {
        if (curReview.find(currentPos->word) != string::npos) {
            currentPos->frequency++;
            totalPosCount++;
        }
        currentPos = currentPos->next;
    }

    // Traverse negative words
    NegWord* currentNeg = negHead;
    while (currentNeg != nullptr) {
        if (curReview.find(currentNeg->word) != string::npos) {
            currentNeg->frequency++;
            totalNegCount++;
        }
        currentNeg = currentNeg->next;
    }
}

// Display word usage function for linked list
inline void displayWordUsage(WordNode* wordList, int freq, const string& usageType) {
    cout << "\n" << usageType << " used words in the reviews: ";
    WordNode* current = wordList;
    while (current != nullptr) {
        cout << current->word;
        if (current->next != nullptr) {
            cout << ", ";
        }
        current = current->next;
    }
    cout << " (" << freq << " times)" << endl;
}

// Find min & max used words function using linked list
inline void findMinMaxUsedWords(PowWord* posHead, NegWord* negHead, WordNode*& minUsedWordsHead, WordNode*& maxUsedWordsHead, int& minFreq, int& maxFreq) {
    minFreq = INT_MAX;
    maxFreq = 0;

    // Traverse positive words
    PowWord* currentPos = posHead;
    while (currentPos != nullptr) {
        if (currentPos->frequency > 0) {
            if (currentPos->frequency < minFreq) {
                minFreq = currentPos->frequency;
                deleteList(minUsedWordsHead);
                minUsedWordsHead = new WordNode(currentPos->word);
            }
            else if (currentPos->frequency == minFreq) {
                addToList(minUsedWordsHead, currentPos->word);
            }

            if (currentPos->frequency > maxFreq) {
                maxFreq = currentPos->frequency;
                deleteList(maxUsedWordsHead);
                maxUsedWordsHead = new WordNode(currentPos->word);
            }
            else if (currentPos->frequency == maxFreq) {
                addToList(maxUsedWordsHead, currentPos->word);
            }
        }
        currentPos = currentPos->next;
    }

    // Traverse negative words
    NegWord* currentNeg = negHead;
    while (currentNeg != nullptr) {
        if (currentNeg->frequency > 0) {
            if (currentNeg->frequency < minFreq) {
                minFreq = currentNeg->frequency;
                deleteList(minUsedWordsHead);
                minUsedWordsHead = new WordNode(currentNeg->word);
            }
            else if (currentNeg->frequency == minFreq) {
                addToList(minUsedWordsHead, currentNeg->word);
            }

            if (currentNeg->frequency > maxFreq) {
                maxFreq = currentNeg->frequency;
                deleteList(maxUsedWordsHead);
                maxUsedWordsHead = new WordNode(currentNeg->word);
            }
            else if (currentNeg->frequency == maxFreq) {
                addToList(maxUsedWordsHead, currentNeg->word);
            }
        }
        currentNeg = currentNeg->next;
    }
}

// Add a word to the linked list
void addToList(WordNode*& head, const string& word) {
    WordNode* newNode = new WordNode(word);
    if (head == nullptr) {
        head = newNode;
    }
    else {
        WordNode* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newNode;
    }
}

// Delete the linked list
void deleteList(WordNode*& head) {
    while (head != nullptr) {
        WordNode* temp = head;
        head = head->next;
        delete temp;
    }
}

#endif

