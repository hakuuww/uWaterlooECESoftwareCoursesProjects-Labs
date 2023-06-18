#include <iostream>
#include <string>
using namespace std;

class Song
{
private:
    string song_Title;
    string song_Artist;

public:
    Song(string song_Title, string song_Artist);
    Song();
    ~Song();
    void eraseSong();
    string get_song_Title();

    string get_song_Artist();
};