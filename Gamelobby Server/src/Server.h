#ifndef _SERVER_H
#define _SERVER_H

#include <cstdarg>
#include <ctime>
#include "SimpleServer.h"
#include "Packets.h"
#include "Playermanager.h"
#include "Gamemanager.h"
#include "Packetreader.h"
#include "Packetbuilder.h"
#include "Matchmaking.h"
#include "/usr/include/PCSC/wintypes.h"

/*
 * Zeitstempel für Debugausgaben.
 */
void timestamp();

/*
 *	Dieser Server ist komplett unabhängig von Winsocket. SimpleServer implementiert die dazu
 *	notwendigen Methoden. Hier wird ausschließlich das abarbeiten der Pakete und das Management von
 * 	Spielern/Spiele geregelt. Wenn der Server auf Linux portiert werden sollte, reicht das Ändern/Ersetzen von
 * 	SimpleServer mit dem jetzt bestehendem "Template" vollkommen aus.
 */
class Server : public SimpleServer
{
public:
					Server(void);
					~Server(void);
	
	bool			Tick(long sec, long usec);										// Update (Daten senden/Empfangen etc.)

protected:
	virtual bool 	OnInitialize();
	virtual void 	OnDeinitialize();
	virtual bool 	OnConnect(int _sid, const char * _actualIp, unsigned short _actualPort);
	virtual void 	OnDisconnect(int _sid);											// Verbindung des Users _sid beendet
	virtual int 	OnData(int _sid, char * _data, size_t _size);					// Datenpaket vom User _sid empfangen
	
	int				SendAll(Packetbuilder * _builder);								// Diese Methode sendet allen eingelogten Usern das Datenpaket
	int				SendGame(Packetbuilder * _builder, int _gameid);				// Diese Methode wird genutzt, wenn allen Spielern eines Games ein Packet gesendet werden soll.
	int				SendGame(Packetbuilder * _builder, int _gameid, int _n, ...);	// Diese Methode wird genutzt, wenn Spieler ausgelassen werden sollen (ID übergeben).

private:
	GameManager 	gm;
	Packetreader  	pr;
	Packetbuilder 	pb;
	PlayerManager 	pm;
	Matchmaking		mm;

	PACKET * packet;

private:
	void login(int _sid, char * _nickname, char * _password);								// wird aufgerufen, wenn ein User sich einloggen möchte
	void creategame(int _sid, char * _title, char * _map, int _maxPlayer, GameMode _mode);	// wird aufgerufen, wenn ein User ein Game erstellt
	void setready(int _sid, int _gameid);													// wird aufgerufen, wenn ein Spieler ready ist
	void joingame(int _sid, int _gameid);													// wird aufgerufen, wenn ein User ein Game beitreten möchte
	void startgame(int _sid, int _gameid);													// ein Erstelltes Game wird gestartet
	void leavegame(int _sid, int _gameid);													// wird aufgerufen, wenn ein Spieler ein Game verlässt
	void closegame(int _sid, int _gameid);													// Ein Host/Spieler beendet eine Lobby/Game
	void logout(int _sid);																	// wird aufgerufen, wenn ein User sich abmeldet
	void sendgamelist(int _sid);															// wird augerufen, wenn ein User "Refresh GameList" ausführt
	void addplayertomatchmaking(int _sid, FILTER _filter);									// wird aufgerufen, wenn ein Spieler ein Spiel suchen lassen möchte
	void removeplayerfrommatchmaking(int _sid);												// wird aufgerufen, wenn ein Sppieler die automatische Suche beenden möchte
};

#endif
