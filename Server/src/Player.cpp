#include "Player.h"
#include "GameLobby.h"

Player::Player(int _pid, int _sid, const char * _nick, const char * _ip, unsigned short _port)
{
	nickname =  _nick;
	ip = _ip;
	pid = _pid;
	sid = _sid;
	port = _port;
	host = false;
	game = NULL;
}

Player::~Player()
{
	// Sicherstellen, dass der Spieler auch aus der Liste gelöscht wird.
	// wenn nicht in der Liste, passiert nichts.
	
	if (game != NULL)
	{
		game->removePlayer(sid);
		game = NULL;
	}
}

int Player::getPID(void)
{
	return pid;
}

void Player::setPID(int _pid)
{
	pid = _pid;
}

int Player::getSID(void)
{
	return sid;
}

std::string & Player::getIP(void)
{
	return ip;
}

unsigned short Player::getPort(void)
{
	return port;
}

std::string & Player::getNick(void)
{
	return nickname;
}

void Player::setNick(char * _nickname)
{
	nickname.clear();
	nickname = _nickname;
}


GameLobby * Player::linkgedGame(void)
{
	return game;
}

void Player::linkGame(GameLobby * _lobby)
{
	game = _lobby;
}

void Player::setHost(bool _val)
{
	host = _val;
}

bool Player::isHost(void)
{
	return host;
}

void Player::setReady(bool _val)
{
	ready = _val;
}

bool Player::getReady(void)
{
	return ready;
}

void Player::setFilter(FILTER _filter)
{
	filter = _filter;
}

FILTER Player::getFilter()
{
	return filter;
}