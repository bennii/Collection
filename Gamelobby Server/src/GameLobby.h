#ifndef _GAMELOBBY_H
#define _GAMELOBBY_H

#include <vector>
#include <string>
#include <algorithm>
#include "hashmanager.h"

typedef enum tagGameMode
{
    onevsone = 1,
    twovstwo,
    threevthree
} GameMode;

class Player;
class GameLobby
{
  public:
    GameLobby(int _playerCount, int _gid);
    ~GameLobby(void);

    void addPlayer(Player *_p);  // entspricht join eines Players in die Lobby, playerList[0] ist immer Host
    void removePlayer(int _sid); // entspricht leave eines Players
    int getMaxPlayers(void);
    int getCurrentPlayers(void);
    bool isFull(void);
    bool playerJoined(void);
    void setJoined(bool _val);

    int getID(void);
    void setHash(HASH _hash);
    HASH getHash(void);
    void setStarted(bool _value);
    bool isStarted(void);
    GameMode getMode(void);
    void setMode(GameMode mode);
    std::string &getTitle(void);
    void setTitle(std::string _string);
    std::string &getMap(void);
    void setMap(std::string _map);
    Player *getHost(void);

    std::vector<Player *> &getPlayers(void);

  private:
    int gid;
    int maxPlayer;
    bool started;
    bool joined;

    HASH hash;
    GameMode mode;

    std::string title;
    std::string map;

    std::vector<Player *> playerList;
};

#endif
