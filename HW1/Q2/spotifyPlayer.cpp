#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <vector>
#include "base64.cpp"
using namespace std;

/*
  *  This homework includes base64 decode and encode methods, These two methods are directly taken from René Nyffenegger.
  *   rene.nyffenegger@adp-gmbh.ch
*/

class SpotifyPlayer
{
  vector<string> musics;

  /**
   * @brief Hardcodedly add musics 
   * 
   */
  void addMusic()
  {
    std::string orig =
        "Music Stream 1";
    this->musics.push_back(base64_encode(reinterpret_cast<const unsigned char *>(orig.c_str()), orig.length()));
    orig = "Music Stream 2";
    this->musics.push_back(base64_encode(reinterpret_cast<const unsigned char *>(orig.c_str()), orig.length()));
    orig = "Music Stream 3";
    this->musics.push_back(base64_encode(reinterpret_cast<const unsigned char *>(orig.c_str()), orig.length()));
  }

public:
  SpotifyPlayer()
  {
    this->addMusic();
  }
  std::string stream(int musicId)
  {
    return this->musics.at(musicId);
  }
};

class MySuperMusicStreamer
{
  SpotifyPlayer *spotifyPlayer;

public:
  MySuperMusicStreamer()
  {
    this->spotifyPlayer = new SpotifyPlayer();
  }
  ~MySuperMusicStreamer()
  {
    delete this->spotifyPlayer;
    this->spotifyPlayer = NULL;
  }

  string play(int spotifyMusicId)
  {
    return this->spotifyPlayer->stream(spotifyMusicId);
  }
};

class MusicPlayerApp
{
public:
  MySuperMusicStreamer *musicPlayer;
  MusicPlayerApp()
  {
  }
  MusicPlayerApp(MySuperMusicStreamer *musicPlayer)
  {
    this->musicPlayer = musicPlayer;
  }
  ~MusicPlayerApp()
  {
    delete this->musicPlayer;
    this->musicPlayer = NULL;
  }

  string play(int musicId)
  {
    return this->musicPlayer->play(musicId);
  }
};

class SpotifyAdapter : public MusicPlayerApp, private SpotifyPlayer
{

public:
  SpotifyAdapter() : MusicPlayerApp(new MySuperMusicStreamer())
  {
  }

  string play(int musicId)
  {
    return this->musicPlayer->play(musicId) + " <via spotifyAdapter>";
  }
  string illegalPlay(int musicId)
  {
    return base64_decode(this->musicPlayer->play(musicId)) + " <illegal>";
  }
};

class Dummy
{

  SpotifyAdapter *spotifyAdapter;

public:
  Dummy()
  {
    this->spotifyAdapter = new SpotifyAdapter();
  }
  ~Dummy(){
    delete this->spotifyAdapter;
    this->spotifyAdapter = NULL;
  }

  void start()
  {
    cout << "Music id 1 is streaming: " << this->spotifyAdapter->play(1) << endl;
    cout << "Music id 1 is streaming illegally: " << this->spotifyAdapter->illegalPlay(1) << endl;
  }
};

int main()
{
  Dummy * app = new Dummy();
  app->start();
  delete app;
  return 0;
}