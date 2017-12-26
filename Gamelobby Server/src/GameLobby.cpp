#include "GameLobby.h"
#include "Player.h"

GameLobby::GameLobby(int _playerCount, int _id)
{
	gid = _id;
	maxPlayer = _playerCount;

	started = false;
	joined 	= true;
}

GameLobby::~GameLobby(void)
{
	playerList.clear();
}

void GameLobby::addPlayer(Player * _player)
{
	if (isFull() == false && isStarted() == false)
	{
		std::vector<Player *>::iterator iter = find(playerList.begin(), playerList.end(), _player);
		
		if (iter == playerList.end()) 							// sicherstellen, dass es diesen Spieler noch nicht gibt
		{
			playerList.push_back(_player);
		}
	}
}

void GameLobby::removePlayer(int _sid)
{
	std::vector<Player *>::iterator iter;
	
	for(iter = playerList.begin(); iter != playerList.end(); iter++)
	{
		if ((*iter)->getSID() == _sid)
		{
			playerList.erase(iter);
			return;
		}
	}
}

int GameLobby::getID(void)
{
	return gid;
}

int GameLobby::getMaxPlayers(void)
{
	return maxPlayer;
}

int GameLobby::getCurrentPlayers(void)
{
	return playerList.size();
}

bool GameLobby::isFull(void)
{
	if (playerList.size() < (size_t)maxPlayer) return false;
	return true;
}

bool GameLobby::isStarted(void)
{
	return started;
}

void GameLobby::setHash(HASH _hash)
{
	hash = _hash;
}

HASH GameLobby::getHash(void)
{
	return hash;
}

void GameLobby::setMode(GameMode _mode)
{
	mode = _mode;
}

GameMode GameLobby::getMode(void)
{
	return mode;
}

void GameLobby::setStarted(bool _value)
{
	started = _value;
}

std::vector<Player *> & GameLobby::getPlayers(void)
{
	return playerList;
}

void GameLobby::setTitle(std::string _title)
{
	title.clear();
	title = _title;
}

std::string & GameLobby::getTitle(void)
{
	return title;
}

void GameLobby::setMap(std::string _map)
{
	map.clear();
	map = _map;
}

std::string & GameLobby::getMap(void)
{
	return map;
}

Player * GameLobby::getHost(void)
{
	return playerList[0];
}

bool GameLobby::playerJoined(void)
{
	return joined;
}

void GameLobby::setJoined(bool _val)
{
	joined = _val;
}