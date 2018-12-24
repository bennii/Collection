#ifndef _PLAYER_H
#define _PLAYER_H

#include <string>
#include <cstring>
#include "GameLobby.h"

typedef struct FILTER
{
    GameMode mode;
    std::string map;

    FILTER()
    {
        map = "";
        mode = (GameMode)1;
    }

    bool operator=(FILTER &filter)
    {
        if (map == filter.map && mode == filter.mode)
            return true;
        else
            return false;
    }
} tagFILTER;

class Player
{
  public:
    Player(int _pid, int _sid, const char *_nick, const char *_ip, unsigned short _port);
    ~Player();

    int getPID(void);
    void setPID(int _pid);

    int getSID(void);
    std::string &getIP(void);
    unsigned short getPort(void);

    std::string &getNick(void);
    void setNick(char *_nickname);

    GameLobby *linkgedGame(void);
    void linkGame(GameLobby *_lobby);

    void setHost(bool _val);
    bool isHost(void);

    void setReady(bool _val);
    bool getReady(void);
    void setFilter(FILTER _filter);
    FILTER getFilter();

  private:
    std::string nickname;
    std::string ip;
    unsigned short port;

    bool ready;

    int pid; // unique id aus der Datenbank
    int sid; // id vom Server zugewiesen => zum Senden genutzt

    bool host;
    GameLobby *game;
    FILTER filter;
};

#endif
