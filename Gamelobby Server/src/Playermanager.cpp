#include "Playermanager.h"

PlayerManager::PlayerManager(void)
{
}

PlayerManager::~PlayerManager(void)
{
    std::vector<Player *>::iterator iter;

    for (iter = list.begin(); iter != list.end(); iter++)
    {
        Player *player = *iter;
        delete player;
        player = NULL;
        list.erase(iter);
    }
}

Player *PlayerManager::createPlayer(int _playerid, int _senderid, const char *_nick, const char *_ip, unsigned short _port)
{
    Player *player = new Player(_playerid, _senderid, _nick, _ip, _port);

    list.push_back(player);

    return player;
}

Player *PlayerManager::getPlayer(int _senderid)
{
    std::vector<Player *>::iterator iter;

    for (iter = list.begin(); iter != list.end(); iter++)
    {
        if ((*iter)->getSID() == _senderid)
            return (*iter);
    }

    return NULL;
}

void PlayerManager::deletePlayer(int _senderid)
{
    std::vector<Player *>::iterator iter;

    for (iter = list.begin(); iter != list.end(); iter++)
    {
        if ((*iter)->getSID() == _senderid)
        {
            Player *player = *iter;
            delete player;
            player = NULL;

            list.erase(iter);
            return;
        }
    }
}

int PlayerManager::getPlayerAmount(void)
{
    return list.size();
}

std::vector<Player *> &PlayerManager::getList(void)
{
    return list;
}
