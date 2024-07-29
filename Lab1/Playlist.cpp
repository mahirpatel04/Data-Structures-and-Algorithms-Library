#include "Playlist.h"

void Playlist::PrintMenu(const string& title) const {
  // Simply outputs the menu using the title parameter

  cout << title << " PLAYLIST MENU" << endl;
  cout << "a - Add song" << endl;
  cout << "d - Remove song" << endl;
  cout << "c - Change position of song" << endl;
  cout << "s - Output songs by specific artist" << endl;
  cout << "t - Output total time of playlist (in seconds)" << endl;
  cout << "o - Output full playlist" << endl;
  cout << "q - Quit" << endl;
  cout << endl;
  cout << "Choose an option:" << endl;
}

void Playlist::AddSong(const string& id, const std::string& song, const std::string& artist, int length) {
  // Creates the new node
  PlaylistNode* newNode = new PlaylistNode(id, song, artist, length);

  // Checks if playlist is empty or not
  if (head == nullptr) {
    head = tail = newNode;
  }
  else {
    tail->SetNext(newNode);
    tail = newNode;
  }
}
    
void Playlist::RemoveSong() {
  // If the list is empty we can't remove anything so simply return from the function
  if (head == nullptr) {
    return;
  }

  // Gets the user's input
  cout << "Enter song's unique ID:" << endl;
  string idToRemove;
  cin >> idToRemove;

  // Checking if cin is in bad state before using any value that was "cin"-ed
  if (not cin) throw runtime_error("Error reading input");

  // Iterate through the list until node to remove is found
  PlaylistNode* curr = head;
  PlaylistNode* next = curr->GetNext();
  while (next->GetID() != idToRemove) {
    curr = curr->GetNext();
    next = curr->GetNext();
  }
  cout << "\"" << next->GetSongName() << "\" removed." << endl;

  // Node deleted and adjacent nodes "connected"
  curr->SetNext(next->GetNext());
  delete next;
}

void Playlist::ChangePositionSong() {
  if (head == nullptr) {
    cout << "List is empty" << endl;
    return;
  }
  // Gets the user's input
  int initialPos;
  int finalPos;
  cout << "Enter song's current position:" << endl;
  cin.ignore();
  cin >> initialPos;
  cout << "Enter new position for song:" << endl;
  cin.ignore();
  cin >> finalPos;
  
  // Checking if cin is in bad state before using any value that was "cin"-ed
  if (not cin) throw runtime_error("Error reading input");

  if (initialPos == finalPos) {
    return;
  }
  
  int count = 1;
  PlaylistNode* curr = head;
  PlaylistNode* initialNode = nullptr;
  PlaylistNode* initialNodePrev = nullptr;

  // Removes the node and holds on to it with initialNode
  while (curr != nullptr) {
    if (count == initialPos - 1) {
      initialNodePrev = curr;
      initialNode = curr->GetNext();
    }
    curr = curr->GetNext();
    count += 1;
  }

  if (initialPos > 1) {
    initialNodePrev->SetNext(initialNode->GetNext());
  }
  else {
    initialNode = head;
    head = initialNode->GetNext();
  }
  

  // Inserts back into the list
  PlaylistNode* leftNode = nullptr;
  PlaylistNode* rightNode = nullptr;
  count = 1;
  curr = head;

  while (curr!= nullptr) {
    if (count == finalPos-1) {
      leftNode = curr;
      rightNode = curr->GetNext();
    }
    curr = curr->GetNext();
    count += 1;
  }

  if (finalPos <= 1) {
    leftNode = head;
    rightNode = head->GetNext();
    head = initialNode;
    initialNode->SetNext(leftNode);
  }
  else {
    leftNode->SetNext(initialNode);
    initialNode->SetNext(rightNode);
  }

  // Finally lets the user know that the song has been moved
  cout << "\"" << initialNode->GetSongName() << "\" moved to position " << finalPos << endl;
}
  
void Playlist::OutputSongsByArtist() const {
  // Gets user's input
  string desiredArtist;
  cout << "Enter artist's name:" << endl;
  cin.ignore();
  getline(cin, desiredArtist);
  cout << endl;

  // Checking if cin is in bad state before using any value that was "cin"-ed
  if (not cin) throw runtime_error("Error reading input");

  // Checks if the playlist is empty
  if (this->head == nullptr) {
    cout << "Playlist is empty" << endl;
    cout << endl;
  }
  else {
    // Iterates through the entire list and if the artist matches the user's entry then
    // the current node is printed
    int i = 1;
    for(const PlaylistNode* curr = head; curr != nullptr; curr = curr->GetNext()) {
      if (curr->GetArtistName() == desiredArtist) {
        cout << i << "." << endl;
        curr->PrintPlaylistNode();
        cout << endl;
      }
      i += 1;
    }
  }
}
    
void Playlist::OutputTotalTime() const {
  // Iterates through all songs of the list and increments the sum by the length of current song
  int sum = 0;
  for(const PlaylistNode* curr = head; curr != nullptr; curr = curr->GetNext()) {
    sum += curr->GetSongLength();
  }

  cout << "OUTPUT TOTAL TIME OF PLAYLIST (IN SECONDS)" << endl;
  cout << "Total time: " << sum << " seconds" << endl;
}

void Playlist::OutputFullPlaylist() const {
  // Checks if playlist is empty
  if (this->head == nullptr) {
    cout << "Playlist is empty" << endl;
    cout << endl;
  }
  // Iterates through every song in the playlist and 
  else {
    int i = 1;
    for(const PlaylistNode* curr = head; curr != nullptr; curr = curr->GetNext()) {
      cout << i << "." << endl;
      curr->PrintPlaylistNode();
      cout << endl;
      i += 1;
    }
  }
}
