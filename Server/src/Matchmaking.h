#ifndef MATCHMAKING_H
#define MATCHMAKING_H

#include "Player.h"
#include "Gamemanager.h"

class Matchmaking
{
public:
	Matchmaking(GameManager * _gm);
	~Matchmaking();
	
	bool Tick(void);
	bool removePlayer(Player * _player);
	bool removePlayer(GameLobby * _lobby);
	bool addPlayer(Player * _player, FILTER _filter);
	
	std::vector<GameLobby*> getReadyGames(void);
	
private:
	int 						playerCap;
	GameManager 			   *gameManager;
	std::vector<Player *> 		playerList;							// vielleicht sollten wir in späteren Versionen diese Playerlist rausnehmen => Konsistenz
};

#endif // MATCHMAKING_H
