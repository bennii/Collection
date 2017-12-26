#include "Server.h"

void timestamp()
{
	time_t rawtime;
	struct tm * timeinfo;
	
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	printf("%i:%i:%i ", timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);	
}

Server::Server(void) : mm(&gm)
{
	packet = new PACKET();
}

Server::~Server()
{
	delete packet;
}

bool Server::Tick(long sec, long usec)
{
	if (mm.Tick())
	{
		std::vector<GameLobby*> games = mm.getReadyGames();
		
		if (games.size())															// Dia: Gibt es spielbare Lobbys
		{
			std::vector<GameLobby *>::iterator iter;

			for(iter = games .begin(); iter != games .end(); iter++)
			{
				if ((*iter)->isStarted() == false) 
				{
					startgame((*iter)->getHost()->getSID(), (*iter)->getID());		// Dia: Spiel starten
					mm.removePlayer((*iter));										// Dia: Spieler entfernen
				}
			}
		}
	}
	
	return SimpleServer::Tick(sec, usec);
}

// wird von SimpleServer::Create(..) aufgerufen
bool Server::OnInitialize(void)
{
	return true;
}

// wird von SimpleServer::Destroy() aufgerufen
void Server::OnDeinitialize(void)
{
	std::vector<Player *> & plist = pm.getList();
	std::vector<Player *>::iterator it;
	
	if (plist.empty() != false)
	{
		for(it = plist.begin(); it != plist.end(); it++)
		{
			Disconnect((*it)->getSID());
		}
	}
}

bool Server::OnConnect(int _sid, const char * _actualIp, unsigned short _actualPort)
// wird von SimpleServer::Tick(...) aufgerufen, sofern ein "connect" auftritt
{
	timestamp();
	printf("DEBUG: Neuer User mit ID '%i' verbunden\n", _sid);
	
	if (pm.createPlayer(_sid, _sid, "", _actualIp, _actualPort) != NULL) 
		return true;
	
	return false;
}

// wird von SimpleServer::Disconnect(...) aufgerufen
void Server::OnDisconnect(int _sid)
{
	Player * player = pm.getPlayer(_sid);
	
	timestamp();
	printf("DEBUG: Benutzer '%s' ist disconnected.\n", player->getNick().c_str());
	
	if (player->isHost())
	{
		GameLobby * game = player->linkgedGame();

		gm.deleteGame(game->getID());
		
		player->linkGame(NULL);
		player->setHost(false);
		
		timestamp();
		printf("DEBUG: Game von Benutzer '%s' wurde geschlossen\n", player->getNick().c_str());
	}
	
	pm.deletePlayer(_sid);
}

// wird von SimpleServer::Tick(...) aufgerufen, sofern es Daten zu lesen gibt
int Server::OnData(int _sid, char * _data, size_t _size)
{
	static int c = 0;
	packet = (PACKET *)_data;
	printPacket(packet);
	
	pr.setPacket(packet);
	int size = pr.getSize();
	
	switch(packet->opcode)
	{
		// Client möchte mich spammen -_-
		case (OPCODE_SPAM):
		{
			timestamp();
			printf("DEBUG: SPAM: %i\n", c++);
			break;
		}

		// Client möchte sich einloggen
		case (CLIENT_REQUEST_LOGIN): 
		{
			timestamp();
			printf("DEBUG: Spieler mit ID '%i' hat sich eingeloggt\n", _sid);
			char 	*nick		= pr.readString();
			char 	*password 	= pr.readString();
			
			login(_sid, nick, password);
			break;
		}

		// Client möchte die Liste aller Games
		case (CLIENT_REQUEST_GAMELIST): 
		{
			timestamp();
			printf("DEBUG: Spielliste von '%i' angefordert\n", _sid);

			sendgamelist(_sid);
			break;
		}

		// Client möchte ein Game erstellen
		case (CLIENT_REQUEST_CREATEGAME): 
		{
			timestamp();
			printf("DEBUG: Spiel wird erstellt...\n");

			char  *name = pr.readString();
			char  *map	= pr.readString();
			BYTE   max  = pr.readByte();
			BYTE   mode = pr.readByte();
			
			puts(name);
			
			creategame(_sid, name, map, max, (GameMode)mode);
			break;
		}
		
		// Client möchte ein Game beitreten
		case (CLIENT_REQUEST_JOINGAME): 
		{
			timestamp();
			printf("DEBUG: Spieler mit ID '%i' möchte ein Spiel beitreten\n", _sid);

			DWORD gameid = pr.readDword();
			joingame(_sid, gameid);
			break;
		}
		
		// Client möchte ein Game starten
		case (CLIENT_REQUEST_STARTGAME):
		{
			timestamp();
			printf("DEBUG: Spieler mit ID '%i' möchte ein Spiel starten \n", _sid);

			DWORD gameid = pr.readDword();
			startgame(_sid, gameid);
			break;
		}

		// Spieler möchte ein Game schließen
		case (CLIENT_REQUEST_LEAVEGAME):
		{
			timestamp();
			printf("DEBUG: Spieler mit ID '%i' möchte ein Spiel verlassen\n", _sid);

			DWORD gameid = pr.readDword();
			leavegame(_sid, gameid);
			break;
		}

		// Client möchte ein Game schließen
		case (CLIENT_REQUEST_CLOSEGAME): 
		{
			timestamp();
			printf("DEBUG: Spieler mit ID '%i' möchte ein Spiel schliessen\n", _sid);

			DWORD gameid = pr.readDword();
			closegame(_sid, gameid);
			break;
		}
		
		// Client möchte gerne ein Spiel automatisch finden
		case (CLIENT_REQUEST_JOINQUEUE):
		{
			timestamp();
			printf("DEBUG: Spieler mit ID '%i' möchte ein Spiel suchen (Matchmaking)\n", _sid);
			
			FILTER filter;
			filter.map = "mp_dafuq";
			filter.mode = (GameMode)1;
			
			addplayertomatchmaking(_sid, filter);
			break;
		}
		
		// dem Clientem hat das Suchen wohl zu lange gedauert
		case (CLIENT_REQUEST_LEAVEQUEUE):
		{
			timestamp();
			printf("DEBUG: Spieler mit ID '%i' moechte kein Spiel mehr suchen (Matchmaking)\n", _sid);
			
			removeplayerfrommatchmaking(_sid);
			break;
		}

		// Client möchte sich ausloggen
		case (CLIENT_REQUEST_LOGOUT): 
		{
			timestamp();
			printf("DEBUG: Spieler mit ID '%i' moechte sich ausloggen.\n", _sid);
			
			logout(_sid);
			break;
		}

		// Da ist etwas beim Zusammenbauen der Pakete im Clienten falsch gelaufen
		default: 
		{
			timestamp();
			printf("DEBUG: UNBEKANNTES DATENPAKET! WAS SOLL ICH NUR MACHEN?\n");
			
			printPacket(packet);
			break;
		}
	}

	pr.cleanup();
	return size;
}

// Ein Paket an alle verbundenen User senden
int Server::SendAll(Packetbuilder * _builder)
{
	int sent = 0;
	std::vector<Player *> & list = pm.getList();
	std::vector<Player *>::iterator iter;
	
	for(iter = list.begin(); iter != list.end(); iter++)
	{
		if ((*iter)->getNick().length() != 0)
		{
			sent += Send((*iter)->getSID(), _builder->getPacket(), _builder->getSize());
		}
	}
	
	return sent;
}

// Ein Paket an alle Spieler eines Game senden
int Server::SendGame(Packetbuilder * _builder, int _gameid)
{
	int sent = 0;
	GameLobby * lobby = gm.getGame(_gameid);
	
	if (lobby == NULL)
	{
		timestamp();
		printf("SERVER: Konnte Daten nicht an Spiel versenden\n");
		return -1;	
	}
	
	std::vector<Player *> & list = lobby->getPlayers();
	std::vector<Player *>::iterator iter;
	
	for(iter = list.begin(); iter != list.end(); iter++)
	{
		sent += Send((*iter)->getSID(), _builder->getPacket(), _builder->getSize());
	}
	
	timestamp();
	printf("SERVER: Daten an Spiel '%i' versendet\n", _gameid);
	return sent;
}

// Ein Paket an gewählt user eines Spiels senden
int Server::SendGame(Packetbuilder * _builder, int _gameid, int _n, ...)
{
	int sent = 0;
	GameLobby * lobby = gm.getGame(_gameid);
	
	if (lobby == NULL) 
	{
		timestamp();
		printf("SERVER: Spiel '%i' konnte nicht gewunden werden\n", _gameid);
		return -1;	
	}
	
	std::vector<Player *> & list = lobby->getPlayers();
	std::vector<Player *>::iterator iter;
	
	if ((size_t)_n > list.size())
	{
		timestamp();
		printf("SERVER: Konnte Daten nicht an Spiel versenden\n");
		return -1;	
	}
	
	va_list vl;
	va_start(vl, _n);
	
	DWORD ignoreID = va_arg(vl, DWORD);
	
	for(iter = list.begin(); iter != list.end(); iter++)
	{
		if ((DWORD)(*iter)->getSID() == ignoreID)
		{
			ignoreID = va_arg(vl, DWORD);
		}
		else if ((DWORD)(*iter)->getSID() != ignoreID)
		{
			sent += Send((*iter)->getSID(), _builder->getPacket(), _builder->getSize());
		}
	}

	va_end(vl);
	timestamp();
	printf("SERVER: Daten an Spiel '%i' versendet\n", _gameid);
	return sent;
}

// wird aufgerufen, wenn der Server ein Login-Datenpacket empfängt
void Server::login(int _sid, char * _nick, char * _password)
{
	Player  * player = pm.getPlayer(_sid);

	if (player == NULL) 
	{
		pb.setOpcode(SERVER_ANSWER_LOGIN);
		pb.addByte(0);
		
		Send(_sid, pb.getPacket(), pb.getSize());
		
		pb.cleanup();
		timestamp();
		printf("SERVER: Spieler '%i' nicht gefunden.\n", _sid);
		return;
	}

	pb.setOpcode(SERVER_ANSWER_LOGIN);
	pb.addByte(1);
	pb.addDword(_sid);															// Login ist ok (später: Datenbank-Abfrage)
	pb.addString(_nick, strlen(_nick));

	if (Send(_sid, pb.getPacket(), pb.getSize()))
	{
		timestamp();
		printf("SERVER: Neuer Spieler mit Namen '%s' hat sich eingeloggt.\n", _nick);

		player->setNick(_nick);
		player->setPID(_sid);
	}

	pb.cleanup();
}

void Server::setready(int _sid, int _gameid)
{
	Player * player = pm.getPlayer(_sid);
	GameLobby * game = gm.getGame(_gameid);
	
	if (player == NULL || game == NULL)
	{
		//pb.setOpcode(GAME_ANSWER_PLAYERREDY);
		pb.addByte(0);
		
		SendGame(&pb, _gameid, 1, _sid);
		pb.cleanup();
		
		timestamp();
		printf("SERVER: Spieler oder Game wurde nicht gefunden\n");
		return;
	}
	
	//pb.setOpcode(GAME_ANSWER_PLAYERREDY);
	pb.addByte(1);
	
	SendGame(&pb, _gameid, 1, _sid);
	pb.cleanup();
}

// wird aufgerufen, wenn ein Client ein Game erstellt
void Server::creategame(int _sid, char * _title, char * _map, int _maxPlayer, GameMode _mode)
{
	Player * player = pm.getPlayer(_sid);
	GameLobby * lobby = gm.createGame(_maxPlayer, _title, _map, _mode);

	if (player == NULL || lobby == NULL) 
	{
		pb.setOpcode(SERVER_ANSWER_CREATEGAME);
		pb.addByte(0);
		
		Send(_sid, pb.getPacket(), pb.getSize());
		
		pb.cleanup();
		timestamp();
		printf("SERVER: nullpointer exception; Spieler nicht gefunden/Fehler beim Erstellen\n");
		return;
	}
	
	if (player->linkgedGame() != NULL) return;

	lobby->addPlayer(player);

	pb.setOpcode(SERVER_ANSWER_CREATEGAME);
	pb.addByte(1);
	pb.addDword(lobby->getID());
	
	if (Send(_sid, pb.getPacket(), pb.getSize()))
	{
		timestamp();
		printf("SERVER: Spiel mit dem Titel '%s' und ID '%i' wurde erstellt.\n", _title, lobby->getID());
		
		player->linkGame(lobby);
		player->setHost(true);
	}
	
	pb.cleanup();	
	timestamp();
	printf("SERVER: %i Spiele sind aktiv\n", gm.getGamesAmount());
}

// wird aufgerufen, wenn ein Spieler ein Spiel betretet
void Server::joingame(int _sid, int _gameid)
{
	Player 		*player	= pm.getPlayer(_sid);
	GameLobby 	*lobby 	= gm.getGame(_gameid);

	if (player == NULL || lobby == NULL) 
	{
		pb.setOpcode(SERVER_ANSWER_JOINGAME);
		pb.addByte(0);
		
		Send(_sid, pb.getPacket(), pb.getSize());
		
		pb.cleanup();
		timestamp();
		printf("SERVER: nullpointer exception; Spieler oder Lobby nicht gefunden\n");
		return;
	}
	
	if (player->linkgedGame() != NULL) return;
	
	if(lobby->isFull() == false)
	{
		lobby->addPlayer(player);
		
		std::vector<Player *>::iterator players;
		
		pb.setOpcode(SERVER_ANSWER_JOINGAME);
		pb.addByte(1);
		pb.addByte(lobby->getPlayers().size());
		
		for(players = lobby->getPlayers().begin(); players != lobby->getPlayers().end(); players++)
		{
			pb.addDword((*players)->getSID());								
			pb.addString((char*)(*players)->getNick().c_str(), (*players)->getNick().length());
		}
		
		if (Send(_sid, pb.getPacket(), pb.getSize()))
		{
			timestamp();
			printf("DEBUG: Spielerliste an '%i' versendet\n", _sid);
		}
		
		pb.cleanup();
		pb.setOpcode(SERVER_ANSWER_PLAYERJOINED);
		pb.addByte(1);
		pb.addDword(player->getSID());
		pb.addString((char *)player->getNick().c_str(), player->getNick().length());
		
		SendGame(&pb, lobby->getID(), 1, player->getSID());
		pb.cleanup();
		
		timestamp();
		printf("SERVER: Spieler '%s' ist Spiel '%i' beigetreten.\n", player->getNick().c_str(), lobby->getID());
		return;
	}
	else if (lobby->isFull() == true)	
	{
		pb.setOpcode(SERVER_ANSWER_JOINGAME);
		pb.addByte(2);
		
		Send(_sid, pb.getPacket(), pb.getSize());
		
		pb.cleanup();
		
		timestamp();
		printf("SERVER: Spieler '%s' konnte Spiel '%i' nicht beitreten.\n", player->getNick().c_str(), lobby->getID());
		return;
	}
}

// wird aufgerufen, wenn ein Client ein Game startet 
void Server::startgame(int _sid, int _gameid)
{
	GameLobby * lobby = gm.getGame(_gameid);
	
	if (lobby == NULL)
	{
		pb.setOpcode(SERVER_ANSWER_STARTGAME);
		pb.addByte(0);
		
		Send(_sid, pb.getPacket(), pb.getSize());
		
		pb.cleanup();
		timestamp();
		printf("SERVER: Spiel '%i' wurde nicht gefunden, starten nicht möglich\n", _gameid);
		return;
	}
	
	pb.setOpcode(SERVER_ANSWER_STARTGAME);
	pb.addByte(1);
	
	SendGame(&pb, _gameid, 1, _sid);
	pb.cleanup();
	
	lobby->setStarted(true);

	timestamp();
	printf("SERVER: Speieler '%i' hat das Spiel '%i' gestartet\n", _sid, _gameid);
}

// wird aufgerufen, wenn ein Gast ein Game verlassen möchte
void Server::leavegame(int _sid, int _gameID)
{
	Player * player   = pm.getPlayer(_sid);
	GameLobby * game = gm.getGame(_gameID);
	
	if (game == NULL || player == NULL)
	{
		pb.setOpcode(SERVER_ANSWER_LEAVEGAME);
		pb.addByte(0);
		
		Send(_sid, pb.getPacket(), pb.getSize());
		
		pb.cleanup();
		timestamp();
		printf("SERVER: Spieler '%i' kann Spieler '%i' nicht verlassen\n", _sid, _gameID);
		return;
	}
	
	pb.setOpcode(SERVER_ANSWER_LEAVEGAME);
	pb.addByte(1);
	
	
	std::vector<Player *> & players = game->getPlayers();
	for(int i = 0; i < game->getCurrentPlayers(); i++)
	{
		printf("%s   ", (const char*)players.at(i)->getNick().c_str());
	}
	if (Send(_sid, pb.getPacket(), pb.getSize()))
	{
		game->removePlayer(_sid);
		player->linkGame(NULL);
		
		timestamp();
		printf("SERVER: Player '%i' hat das Game '%i' verlassen\n", _sid, _gameID);
	}
	
	printf("'%i' atkive Spiele\n", gm.getGamesAmount());
	std::vector<Player *> & _players = game->getPlayers();
	for(int i = 0; i < game->getCurrentPlayers(); i++)
	{
		printf("%s", (const char*)_players.at(i)->getNick().c_str());
	}
	
	pb.cleanup();
	pb.setOpcode(SERVER_ANSWER_PLAYERLEFT);
	pb.addByte(1);
	pb.addDword(_sid);
	
	
	SendGame(&pb, game->getID(), 1, _sid);
	pb.cleanup();	
}

// wird aufgerufen, wenn ein Client ein Game schließt
void Server::closegame(int _sid, int _gameid)
{
	GameLobby * lobby = gm.getGame(_gameid);
	
	if (lobby == NULL)
	{
		pb.setOpcode(SERVER_ANSWER_CLOSEGAME);
		pb.addByte(0);

		Send(_sid, pb.getPacket(), pb.getSize());
		
		pb.cleanup();
		timestamp();
		printf("SERVER: Spiel '%i' wurde nicht gefunden, schließen nicht möglich\n", _gameid);
		return;
	}
	
	if (lobby->getHost()->getSID() == _sid)
	{
		pb.setOpcode(SERVER_ANSWER_CLOSEGAME);
		pb.addByte(1);
		
		if (Send(_sid, pb.getPacket(), pb.getSize()))
		{
			lobby->getHost()->setHost(false);
			lobby->getHost()->linkGame(NULL);

			gm.deleteGame(lobby->getID());
		}
		
		pb.cleanup();
		pb.setOpcode(SERVER_ANSWER_GAMESHUTDOWN);
		pb.addByte(1);
		
		SendGame(&pb, lobby->getID(), 1, _sid);
		pb.cleanup();
	}

	timestamp();
	printf("SERVER: %i Spiele sind aktiv\n", gm.getGamesAmount());
}

// wird aufgerufen, wenn ein Client ausloggt
void Server::logout(int _sid)
{
	Player * player = pm.getPlayer(_sid);

	if (player == NULL) 
	{
		timestamp();
		printf("SERVER: Spieler '%i' nicht gefunden\n", _sid);
		return;
	}
	
	if (player->isHost())
	{
		printf("SERVER: %i aktive Spiele\n", gm.getGamesAmount());
		GameLobby * game = player->linkgedGame();
		
		gm.deleteGame(game->getID());

		player->linkGame(NULL);
		player->setHost(false);
	}

	pb.setOpcode(SERVER_ANSWER_LOGOUT);
	pb.addByte(1);

	if(Send(_sid, pb.getPacket(), pb.getSize()))
	{
		timestamp();
		printf("SERVER: Spieler '%s' hat den Server verlassen.\n", player->getNick().c_str());
		timestamp();
		printf("SERVER: %i aktive Spiele\n", gm.getGamesAmount());
	}

	pb.cleanup();
}

// wird aufgerufen, wenn ein Client die Liste aller offenen Games abfragt
// Verbesserungen; Nur die Spiele senden, die sich verändert haben UND nur nicht gestartete Spiele zeigen
void Server::sendgamelist(int _sid)
{
	std::vector<GameLobby*>::iterator iter;
	
	pb.setOpcode(SERVER_ANSWER_GAMELIST);
	pb.addByte(1);
	pb.addDword(gm.getGamesAmount());

	for(iter = gm.getList().begin(); iter != gm.getList().end(); iter++)
	{
		if ((*iter)->isStarted() == false)
		{
			pb.addDword((*iter)->getID());				
			pb.addString((char*)(*iter)->getTitle().c_str(), (*iter)->getTitle().length());
			pb.addString((char*)(*iter)->getMap().c_str(), (*iter)->getMap().length());
			pb.addByte((*iter)->getMaxPlayers());	
			pb.addByte((*iter)->getCurrentPlayers());
		}
	}

	if (Send(_sid, pb.getPacket(), pb.getSize()))
	{
		timestamp();
		printf("SERVER: Spielliste an User %i gesendet\n", _sid);
	}
	
	timestamp();
	printf("SERVER: %i aktiv(e) Spiele\n", gm.getList().size());
	pb.cleanup();
}

void Server::addplayertomatchmaking(int _sid, FILTER _filter)
{
	Player * player = pm.getPlayer(_sid);

	if (player == NULL)
	{
		timestamp();
		printf("SERVER: Spieler mit ID '%i' konnte nicht gefunden werden.\n", _sid);

		pb.setOpcode(SERVER_ANSWER_JOINQUEUE);
		pb.addByte(0);

		Send(_sid, pb.getPacket(), pb.getSize());
		pb.cleanup();
		return;
	}
	else if (mm.addPlayer(player, _filter) == false)
	{
		timestamp();
		printf("SERVER: Spieler mit ID '%i' konnte nicht ins Matchmaking aufgenommen werden.\n", _sid);
		
		pb.setOpcode(SERVER_ANSWER_JOINQUEUE);
		pb.addByte(0);

		Send(_sid, pb.getPacket(), pb.getSize());
		pb.cleanup();
		return;
	}
	
	pb.setOpcode(SERVER_ANSWER_JOINQUEUE);
	pb.addByte(1);

	if (Send(_sid, pb.getPacket(), pb.getSize()))
	{
		printf("SERVER: Spieler mit ID '%i' wurde in die Liste aufgenommen.\n", _sid);
	}

	pb.cleanup();
}

void Server::removeplayerfrommatchmaking(int _sid)
{
	Player * player = pm.getPlayer(_sid);
	
	timestamp();
	printf("SERVER: Spieler mit ID '%i' moechte das Matchmaking verlassen.", _sid);

	if (player != NULL)
	{
		if (mm.removePlayer(player))
		{
			pb.setOpcode(SERVER_ANSWER_LEAVEQUEUE);
			pb.addByte(1);

			if (Send(_sid, pb.getPacket(), pb.getSize()))
			{
				timestamp();
				printf("SERVER: Spieler mit ID '%i' hat das Matchmaking verlassen.", _sid);
				pb.cleanup();
				return;
			}
		}
	}

	pb.setOpcode(SERVER_ANSWER_LEAVEQUEUE);
	pb.addByte(0);

	if (Send(_sid, pb.getPacket(), pb.getSize()))
	{
		timestamp();
		printf("SERVER: Spieler mit ID '%i' konnte das Matchmaking nicht verlassen.", _sid);
	}

	pb.cleanup();
}
