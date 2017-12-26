#ifndef _GAMEMANAGER_H
#define _GAMEMANAGER_H

#include <vector>
#include "GameLobby.h"
#include "hashmanager.h"

class GameManager
{
public:
	GameManager(void);
	GameManager(int _startID);
	~GameManager(void);

	GameLobby * createGame(int _maxplayer, std::string _title, std::string _map, GameMode _mode);
	void		deleteGame(int _gameid);
	
	GameLobby * getGame(int _gameid);
	int			getGamesAmount(void);
	
	std::vector<GameLobby *> & getList(void);

private:
	int counter;
	Hashmanager hm;
	std::vector<GameLobby *> list;
};

#endif

