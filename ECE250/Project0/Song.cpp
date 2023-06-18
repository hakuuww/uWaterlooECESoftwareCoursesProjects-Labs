#include <iostream>
#include <string>
#include <cmath>
using namespace std;

#include "Song.hpp"

Song::Song(string song_Title_p, string song_Artist_p)
{
    song_Title = song_Title_p;
    song_Artist = song_Artist_p;
}

string Song::get_song_Title()
{
    return this->song_Title;
}

string Song::get_song_Artist()
{
    return this->song_Artist;
}

void Song::eraseSong()
{
    song_Title = "";
    song_Artist = "";
    song_Title.clear();
    song_Artist.clear();
}

Song::Song()
{
    song_Title = "";
    song_Artist = "";
    song_Title.clear();
    song_Artist.clear();
}


Song::~Song()
{
}
 
