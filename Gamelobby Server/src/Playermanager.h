#ifndef _PLAYERMANAGER_H
#define _PLAYERMANAGER_H

#include <vector>

#include "Player.h"

class PlayerManager
{
  public:
    PlayerManager(void);
    ~PlayerManager(void);

    Player *createPlayer(int _playerid, int _senderid, const char *_nick, const char *_ip, unsigned short _port);
    Player *getPlayer(int _playerid);
    void deletePlayer(int _playerid);

    int getPlayerAmount(void);

    std::vector<Player *> &getList(void);

  private:
    std::vector<Player *> list;
};

#endif
