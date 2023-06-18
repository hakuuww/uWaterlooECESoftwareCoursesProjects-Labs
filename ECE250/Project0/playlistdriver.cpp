#include <iostream>
#include <cmath>
#include <string>

#include "Playlist.hpp"

using namespace std;

int main()
{

    if (cin.eof())
    {
        return 0;
    }

    char userInput;
    cin >> userInput;

    if (userInput != 'm')
    {
        return 0;
    }

    int songListSize;
    cin >> songListSize;

    if (songListSize <= 0)
    {
        return 0;
    }

    Playlist p1(songListSize);

    bool exit = false;

    while (exit == false || (!std::cin.eof()))
    {

        char userInput2;
        cin >> userInput2;
        switch (userInput2)
        {
        case 'i':
        {
            cin.ignore();
            std::string songTitleAndArtistName;
            std::getline(std::cin, songTitleAndArtistName);

            // Used the method at here https://stackoverflow.com/questions/10553597/cin-and-getline-skipping-input
            // https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c

            // call the playlistaddsong function
            string delimiter = ";";
            size_t pos = 0;
            string songTitle;
            string artistName;

            if ((pos = songTitleAndArtistName.find(delimiter)) != string::npos)
            {

                songTitle = songTitleAndArtistName.substr(0, pos);

                artistName = songTitleAndArtistName.substr(pos + 1, songTitleAndArtistName.length());

                if ((songTitleAndArtistName != "Muskrat Love;Captain and Tennille") &&
                    ((songTitle != "My Heart Will Go On")))
                {
                    p1.playlistAddSong(songTitle, artistName); // should output success
                }
                else
                {
                    cout << "can not insert " << songTitleAndArtistName << endl;
                }
            }
            else
            {
                if (cin.eof())
                {
                    exit = true;
                    break;
                }
                cout << "can not insert " << songTitleAndArtistName << endl;
            }
            if (cin.eof())
            {
                return 0;
            }

            break;
        }
            // Adds a song at the end of the playlist if it is not already in the list, the list is not full, and it is not a restricted entry
        case 'p':
        {
            cin.ignore();
            int songPosition;

            cin >> songPosition;

            p1.playlistPlaySong(songPosition);
            if (cin.eof())
            {
                return 0;
            }

            // Plays song at position n
            break;
        }
        case 'e':
        {
            cin.ignore();
            int songPosition;

            cin >> songPosition;

            p1.playlistEraseSong(songPosition);
            // Erases song at position n, moves any songs after position n up by 1
            if (cin.eof())
            {
                return 0;
            }
            break;
        }
        default:
            exit = true;
            if (cin.eof())
            {
                return 0;
            }
            break;
            // code block
        }
    }

    if (cin.eof())
    {
        return 0;
    }

    return 0;
}