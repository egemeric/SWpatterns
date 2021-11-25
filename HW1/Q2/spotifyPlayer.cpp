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
        "Music Stream 1 content";
    this->musics.push_back(base64_encode(reinterpret_cast<const unsigned char *>(orig.c_str()), orig.length()));
    orig = "Music Stream 2 content";
    this->musics.push_back(base64_encode(reinterpret_cast<const unsigned char *>(orig.c_str()), orig.length()));
    orig = "Music Stream 3 content";
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

public:
  MySuperMusicStreamer()
  {
  }
  ~MySuperMusicStreamer()
  {
  }

  virtual string play(int spotifyMusicId){};
  virtual string illegalPlay(int spotifyMusicId){};
};
class SpotifyAdapter : public MySuperMusicStreamer
{
  SpotifyPlayer *spotifyPlayer;

public:
  SpotifyAdapter() : MySuperMusicStreamer()
  {
    this->spotifyPlayer = new SpotifyPlayer();
  }
  ~SpotifyAdapter()
  {
    delete this->spotifyPlayer;
  }

  virtual string play(int musicId)
  {
    return this->spotifyPlayer->stream(musicId) + " <via spotifyAdapter>\n";
  }

  virtual string illegalPlay(int musicId)
  {
    return (base64_decode(this->spotifyPlayer->stream(musicId)) + " <ILLEGAL STREAM>\n");
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
  }

  string play(int musicId)
  {
    this->musicPlayer = new SpotifyAdapter();
    return this->musicPlayer->play(musicId) + "\n" + this->musicPlayer->illegalPlay(musicId);
    delete this->musicPlayer;
    
  }
};

class Dummy
{

  MusicPlayerApp *musicApp;
  MySuperMusicStreamer *tmp;

public:
  Dummy()
  {
    this->tmp = new MySuperMusicStreamer();
    this->musicApp = new MusicPlayerApp(this->tmp);
  }
  ~Dummy()
  {
    delete this->musicApp;
    delete this->tmp;
  }

  void start()
  {
    cout << this->musicApp->play(1); //base64 stream  and decoded stream(illegal)
  }
};

int main()
{
  Dummy *app = new Dummy();
  app->start();
  delete app;
  return 0;
}
