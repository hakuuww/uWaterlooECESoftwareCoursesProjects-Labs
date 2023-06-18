#include <iostream>

#include <cmath>
#include <string>

#include "Playlist.hpp"

using namespace std;

Playlist::Playlist(int listSize_p)
{
    listSize = listSize_p;
    playlistArr = new Song[listSize_p];
    listEnd = 0;
    std::cout << "success" << endl;
}
Playlist::Playlist()
{
    int listEnd = 0;
    int listSize = 0;
    Song *playlistArr = nullptr;
}

Playlist::~Playlist()
{

    delete[] playlistArr;
    playlistArr = nullptr;
}

void Playlist::playlistAddSong(string song_Title_p, string song_Artist_p)
{

    if (((song_Title_p == "Muskrat Love") && (song_Artist_p== "Captain and Tennille")) ||
        ((song_Title_p == "My Heart Will Go On")))
    {
        cout << "can not insert " << song_Title_p << ";" << song_Artist_p << endl;
        return;
    }

    if (listEnd > (listSize - 1))
    {
        cout << "can not insert " << song_Title_p << ";" << song_Artist_p << endl;
        return;
    }
    // Initialize an instance of song

    Song newSong = Song(song_Title_p, song_Artist_p);

    playlistArr[listEnd] = newSong;

    // add the song to the play list

    // playlist end index++

    std::cout << "success" << endl;

    listEnd++;

    return;
}

void Playlist::playlistPlaySong(int n_p)
{
    if ((n_p < 0) || (n_p > (listSize - 1)))
    {
        std::cout << "can not play " << n_p << endl;
        return;
    }

    if ((playlistArr[n_p].get_song_Artist().empty() == true) || (playlistArr[n_p].get_song_Title().empty() == true))
    {
        std::cout << "can not play " << n_p << endl;
        return;
    }
    else
    {
        std::cout << "played " << n_p << " " << playlistArr[n_p].get_song_Title() << ";" << playlistArr[n_p].get_song_Artist() << endl;
    }
    return;
}

void Playlist::playlistEraseSong(int n_p)
{
    if ((n_p < 0) || (n_p > (listSize - 1)))
    {
        std::cout << "can not erase " << n_p << endl;
        return;
    }

    if (playlistArr[n_p].get_song_Artist().empty() || playlistArr[n_p].get_song_Artist().empty())
    {
        std::cout << "can not erase " << n_p << endl;
        return;
    }

    // now [n_p] should have a song in it

    playlistArr[n_p].eraseSong();
    // deconstruct the song

    int begin{n_p};

    if (listEnd == (listSize))
    {
        while (begin < (listEnd - 1))
        {
            playlistArr[begin] = playlistArr[begin + 1];
            begin++;
        }
        playlistArr[begin].eraseSong();
    }
    else
    {
        while (begin < (listEnd))
        {
            playlistArr[begin] = playlistArr[begin + 1];
            begin++;
        }
    }

    listEnd--;

    cout << "success" << endl;
}
