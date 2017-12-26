#include "Gamemanager.h"

GameManager::GameManager(void)
{
	counter = 10000;
}

GameManager::GameManager(int _startID)
{
	counter = _startID;
}

GameManager::~GameManager(void)
{
	std::vector<GameLobby *>::iterator iter;

	for(iter = list.begin(); iter != list.end(); iter++)
	{
		delete *iter;
		list.erase(iter);
	}
}

GameLobby * GameManager::createGame(int _maxplayer, std::string _title, std::string _map, GameMode _mode)
{
	GameLobby * lobby = new GameLobby(_maxplayer, counter++);
	
	lobby->setTitle(_title);
	lobby->setMode(_mode);
	lobby->setStarted(false);
	lobby->setMap(_map);
	//lobby->setHash(hm.createHash( (itoa(lobby->getID(), hash, 10)) ));
    //lobby->setHash(hm.createHash(std::to_string(lobby->getID()));
	
	list.push_back(lobby);

	return lobby;
}


void GameManager::deleteGame(int _gameid)
{
	std::vector<GameLobby *>::iterator iter;

	for(iter = list.begin(); iter != list.end(); iter++)
	{
		if ((*iter)->getID() == _gameid) 
		{
			// Wurde das Spiel gestartet? Sollte abgefangen werden.
			GameLobby * lobby = *iter;
			delete lobby;
			lobby = NULL;
			list.erase(iter);
			return;
		}
	}
}

GameLobby * GameManager::getGame(int _gameid)
{
	std::vector<GameLobby *>::iterator iter;

	for(iter = list.begin(); iter != list.end(); iter++)
		if ((*iter)->getID() == _gameid) 
			return *iter;

	return NULL;
}

int GameManager::getGamesAmount(void)
{
	return list.size();
}

std::vector<GameLobby *> & GameManager::getList(void)
{
	return list;
}
