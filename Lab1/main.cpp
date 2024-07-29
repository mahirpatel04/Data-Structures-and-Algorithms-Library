#include <iostream>

#include "Playlist.h"

using namespace std;

int main() {

  // Creates the playlist and gets the title of the playlist
  string title;
  cout << "Enter playlist's title:" << endl;
  getline(cin, title);
  cout << endl;

  // Checking if cin is in bad state before using any value that was "cin"-ed
  if (not cin) throw runtime_error("Error reading input");

  Playlist P;
  
  // Executes commands until the user quits
  while(true) {
   
    P.PrintMenu(title);
    string command;

    if (!(cin >> command)) break;


    if (command == "a") {
      cout << "ADD SONG" << endl;
      string inputID;
      string inputName;
      string inputArtist;
      int inputLength;
      cout << "Enter song's unique ID:" << endl;
      cin >> inputID;
      cin.ignore();
      cout << "Enter song's name:" << endl;
      getline(cin, inputName);
      cout << "Enter artist's name:" << endl;
      getline(cin,inputArtist);
      cout << "Enter song's length (in seconds):" << endl;
      cin >> inputLength;
      cout << endl;
      // Checking if cin is in bad state before using any value that was "cin"-ed
      if (not cin) throw runtime_error("Error reading input");

      P.AddSong(inputID, inputName, inputArtist, inputLength);

    } else if (command == "d") {
      cout << "REMOVE SONG" << endl;
      P.RemoveSong();
      cout << endl;

    } else if (command == "c") {
      cout << "CHANGE POSITION OF SONG" << endl;
      P.ChangePositionSong();
      cout << endl;

    } else if (command == "s") {
      cout << "OUTPUT SONGS BY SPECIFIC ARTIST" << endl;
      P.OutputSongsByArtist();

    } else if (command == "t") {
      P.OutputTotalTime();
      cout << endl;

    } else if (command == "o") {
      cout << title << " - OUTPUT FULL PLAYLIST" << endl;
      P.OutputFullPlaylist();

    } else if (command == "q") {
      break;
    }
  }
  
  if (!cin) {
    cout << "Program did not exit cleanly" << endl;
    return 1;
  }
  
  return 0;
}

