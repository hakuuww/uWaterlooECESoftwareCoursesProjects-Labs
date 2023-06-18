#include <iostream>
#include <string>
#include "Song.hpp"
using namespace std;

class Playlist
{
private:
    int listSize;
    Song *playlistArr;
    int listEnd;

public:
    Playlist(int listSize_p);
    Playlist();
    ~Playlist();
    void playlistAddSong(string song_Title_p, string song_Artist_p);
    void playlistPlaySong(int n_p);
    void playlistEraseSong(int n_p);

};