#include "HashTable.h"
#include "WordEntry.h"

HashTable::HashTable (int s) : size(s) {
  // Pointer to array of lists containing WordEntry objects
	hashTable = new list<WordEntry>[s];
}

int HashTable::computeHash(const string &s) const {
  // WRITTEN BY CHAT-GPT NOT BY ME

  int hash_value = 0;
  // Iterate through each character in the sentence
  for (char c : s) {
    // Add the ASCII value of each character to the hash value
    hash_value += static_cast<int>(c);
  }  
  // Return the final hash value
  return hash_value % size;
}

void HashTable::put(const string &s, int score) {
  if (contains(s) == true) {
    int index = computeHash(s);
    // Iterate through list at the computed index
    for (auto i = hashTable[index].begin(); i != hashTable[index].end(); i++) {
      // Check if the word already exists in the linked list in which case add a new appearance with the new score
      if (i->getWord() == s) {
        i->addNewAppearance(score);
        return;
      }
    }
  }
  else {
    // Create a new hash and insert a new WordEntry object to the linked list at the index
    int index = computeHash(s);
    WordEntry* insertWord = new WordEntry(s, score);
    hashTable[index].push_back(*insertWord);
  }

}

double HashTable::getAverage(const string &s) const {
  if (contains(s) == true) {
    int index = computeHash(s);
    // Iterate through the hastable
    for (auto i = hashTable[index].begin(); i != hashTable[index].end(); i++) {
      // See if word exists in the list in which case return the average
      if (i->getWord() == s) {
        return i->getAverage();
      }
    }
  }
  // Default value is 2.0
  return 2.0;
}

bool HashTable::contains(const string &s) const {
  int index = computeHash(s);
  // Same logic of iterating through the table
  for (auto i = hashTable[index].begin(); i != hashTable[index].end(); i++) {
    // If there is a match then return true
    if (i->getWord() == s) {
      return true;
      }
  }
  // After the for loop no match has been found so just return false
  return false;
}

HashTable::~HashTable() {
  // Deletes the entire array that was dynamically allocated
  delete[] hashTable;
}



int main() {
  return 0;
}