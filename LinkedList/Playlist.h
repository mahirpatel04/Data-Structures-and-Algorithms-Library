#pragma once

#include <iostream>
using namespace std;

class PlaylistNode {
private:
  string uniqueID;
  string songName;
  string artistName;
  int songLength;
  PlaylistNode* nextNodePtr;
public:
  // Constructors
  PlaylistNode() : 
  uniqueID("none"), songName("none"), artistName("none"), songLength(0), nextNodePtr(nullptr) {}

  PlaylistNode(string id, string songName, string artistName, int length) : 
  uniqueID(id), songName(songName), artistName(artistName), songLength(length), nextNodePtr(nullptr) {}

  // Other member Functions
  const string& GetID() const { return uniqueID; }
  const string& GetArtistName() const { return artistName; }
  const string& GetSongName() const { return songName; }
  int GetSongLength() const { return songLength; }
  PlaylistNode* GetNext() { return nextNodePtr; }
  const PlaylistNode* GetNext() const { return nextNodePtr; }
  const void PrintPlaylistNode() const {
    cout << "Unique ID: " << uniqueID << endl;
    cout << "Song Name: " << songName << endl;
    cout << "Artist Name: " << artistName << endl;
    cout << "Song Length (in seconds): " << songLength << endl;
  }
  const void InsertAfter(PlaylistNode* inputNode) {
    PlaylistNode* currNext = this->nextNodePtr;
    this->SetNext(inputNode);
    inputNode->nextNodePtr = currNext;
  }
  const void SetNext(PlaylistNode* inputNode) {
    nextNodePtr = inputNode;
  }
};

class Playlist {
private:
  PlaylistNode* head;
  PlaylistNode* tail;
public:
  Playlist() : head(nullptr),tail(nullptr) {}
  void PrintMenu(const string& title) const;
  void AddSong(const string& id, const std::string& song, const std::string& artist, int length);
  void RemoveSong();
  void ChangePositionSong();
  void OutputSongsByArtist() const;
  void OutputTotalTime() const;
  void OutputFullPlaylist() const;

  // Copy Constructor
  Playlist(const Playlist&) = delete;
  // Assignment Operator
  Playlist& operator=(const Playlist&) = delete;

  // Destructor
  ~Playlist() {
    // Head node is removed until the entire list is empty
    while (head != nullptr) {
      if (head == tail) {
        delete head;
        head = tail = nullptr;
      }
      else {
        PlaylistNode *temp = head;
        this->head = temp->GetNext();
        delete temp;
      }
    }
  }
};

