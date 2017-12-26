#ifndef _SIMPLESERVER_H
#define _SIMPLESERVER_H

#ifdef _WIN32
#define _WIN32_WINNT 0x0601

#include <winsock2.h>
#include <ws2tcpip.h>
#endif
#ifdef __linux__
#include <netdb.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <sys/select.h>
#include <arpa/inet.h>
#include <netinet/in.h>

const int SOCKET_ERROR   = -1;
const int INVALID_SOCKET = -1;
typedef int SOCKET;
#endif

#include <exception>
#include <memory>
#include <cstdio>
#include <string.h>
	
const int MAX_BUFFER_SIZE		 = 8192;									// maximale Menge an Daten, die ein send/recv-call nutzen kann
const int MAX_CONNECTION_OBJECTS = 64;

#ifdef _WIN32                                                               // Nur unter Windows
bool InitializeWinsock();													// Netzwerk initialisieren
void DeinitializeWinsock();													// Netzwerk bereinigen
#endif

struct SimpleServerData;													// Vorausdekleration der Serverdaten
class SimpleServer
{
private:
	bool isRunning;
	SimpleServerData * simpleServerData;
	
protected:																	// Methoden unten müssen bei Vererbung implementiert werden
	virtual bool 	OnInitialize() = 0;										// wird bei Destroy() aufgerufen
	virtual void 	OnDeinitialize() = 0;									// wird bei Create(...) aufgerufen, muss true zurückgeben, damit Server startet
	virtual bool 	OnConnect(int uid, const char * actualIp, unsigned short actualPort) = 0;	// ein neuer Client ist verbunden; muss true zurückgeben, damit Verbindung besteht
	virtual void 	OnDisconnect(int uid) = 0;								// wird beim Trennen einer Verbindung aufgerufen
	virtual int 	OnData(int uid, char * data, size_t size) = 0;			// wird bei vorhandenen Daten aufgerufen

public:
	SimpleServer();
	virtual ~SimpleServer();
	
	bool Create(short port);												// Server erstellen
	void Destroy();															// Server beenden
	bool Send(int uid, void * data, size_t size);							// Daten an einen Clienten senden
	void Disconnect(int uid);												// Clienten (Socket) disconnecten
	bool IsRunning();														// ist der Server aktiv und listening

	short int GetPort() const;												// aktiver Port	

	virtual bool Tick(long sec, long usec);									// Server Tick, abfrage ob Daten gesendet oder empfangen werden sollen/neue Verbindungen (Clienten) existieren
};

#endif
