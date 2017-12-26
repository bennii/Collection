#include "SimpleServer.h"

// TSocket struct soll einen Clienten darstellen, eine Klasse wäre übertrieben, aber äquivalent
struct TSocket
{
#ifdef _WIN32
	SOCKET s;
#endif
#ifdef __linux__
    int s;
#endif
	
	char recvBuffer[MAX_BUFFER_SIZE];
	int recvBufferIndex;
	char sendBuffer[MAX_BUFFER_SIZE];
	int sendBufferIndex;
};

// TConnection struct zum speichern. Einem Socket (anderer PC), wird fest mit einer user id verbunden
struct TConnection
{
	int uid;
	TSocket socketObject;
};

#ifdef _WIN32
// standard c++ socket methode (google bei Fragen)
bool InitializeWinsock()
{
	WSADATA wd = {0};
	
	if(WSAStartup(MAKEWORD(2, 2), &wd) != 0)
	{
		return false;
	}
	
	if(LOBYTE(wd.wVersion) < 2)
	{
		WSACleanup();
		return false;
	}

	return true;
}

// standard c++ socket methode (google bei Fragen)
void DeinitializeWinsock()
{
	WSACleanup();
}
#endif


// die Serverdaten; alterntativ: einzeln als protected in der Klasse
struct SimpleServerData
{
	SOCKET listenSocket;
	
	addrinfo hints;
	addrinfo * addrInfo;
	sockaddr_in remoteAddr;

#ifdef _WIN32
	FD_SET readSet;
	FD_SET writeSet;
#endif
#ifdef __linux__
    fd_set readSet;
    fd_set writeSet;
#endif

	timeval selectTimeout;

	u_long blockingFlag;

	int uid;
	short int port;
	
	TConnection * pConnectionList;															// die einzelnen verbundenen(!) Clienten
#ifdef _WIN32
	CRITICAL_SECTION connectionListCS;
#endif
#ifdef __linux__
    pthread_mutex_t connectionListCS;
#endif
};

SimpleServer::SimpleServer()
{

	isRunning = false;
	simpleServerData = new SimpleServerData;
	memset(simpleServerData, 0, sizeof(SimpleServerData));
	
#ifdef _WIN32
	InitializeCriticalSection(&simpleServerData->connectionListCS);
#endif
#ifdef __linux__
    simpleServerData->connectionListCS = PTHREAD_RECURSIVE_MUTEX_INITIALIZER_NP;
#endif
}

SimpleServer::~SimpleServer()
{
#ifdef _WIN32
	DeleteCriticalSection(&simpleServerData->connectionListCS);
#endif
#ifdef __linux__
    pthread_mutex_destroy(&simpleServerData->connectionListCS);
#endif
	
	delete simpleServerData;
}

bool SimpleServer::IsRunning()
{
	return isRunning;
}

short int SimpleServer::GetPort() const
{
	return simpleServerData->port;
}

bool SimpleServer::Create(short port)
{
	int result;

	simpleServerData->uid = 1;
	simpleServerData->selectTimeout.tv_sec = 0;
	simpleServerData->selectTimeout.tv_usec = 0;
	simpleServerData->blockingFlag = 1;
	simpleServerData->addrInfo = NULL;
#ifdef _WIN32
	simpleServerData->listenSocket = INVALID_SOCKET;
#endif
#ifdef __linux__
	simpleServerData->listenSocket = -1;
#endif

	// hier werden die structs/pointer auf NULL bzw. 0 gesetzt, damit später keine Fehler wegen -2342454234 Werten auftauchen
#ifdef _WIN32
	ZeroMemory(&simpleServerData->hints, sizeof(simpleServerData->hints));
	ZeroMemory(&simpleServerData->remoteAddr, sizeof(simpleServerData->remoteAddr));
#endif
#ifdef __linux__
	memset(&simpleServerData->hints, 0, sizeof(simpleServerData->hints));
	memset(&simpleServerData->remoteAddr, 0, sizeof(simpleServerData->remoteAddr));
#endif
	simpleServerData->pConnectionList = new TConnection[MAX_CONNECTION_OBJECTS];
#ifdef _WIN32
	ZeroMemory(simpleServerData->pConnectionList, MAX_CONNECTION_OBJECTS * sizeof(TSocket));
#endif
#ifdef __linux__
	memset(simpleServerData->pConnectionList, 0, MAX_CONNECTION_OBJECTS * sizeof(TSocket));
#endif

	// Array von Clienten auf 0 setzen
	for(int ctr = 0; ctr < MAX_CONNECTION_OBJECTS; ++ctr)
	{
#ifdef _WIN32
		ZeroMemory(&simpleServerData->pConnectionList[ctr], sizeof(TConnection));
#endif
#ifdef __linux__
		memset(&simpleServerData->pConnectionList[ctr], 0, sizeof(TConnection));
#endif
		simpleServerData->pConnectionList[ctr].socketObject.s = INVALID_SOCKET;
	}

#ifdef _WIN32
	InitializeWinsock();
	InitializeCriticalSection(&simpleServerData->connectionListCS);
#endif
	
	simpleServerData->port = port;
	char sport[32] = {0};
	snprintf(sport, 31, "%i", port);

	simpleServerData->hints.ai_family = AF_INET;
	simpleServerData->hints.ai_socktype = SOCK_STREAM;
	simpleServerData->hints.ai_protocol = IPPROTO_TCP;
	simpleServerData->hints.ai_flags = AI_PASSIVE;
	
	result = getaddrinfo(NULL, sport, &simpleServerData->hints, &simpleServerData->addrInfo);
	if(result != 0)
	{
		printf("getaddrinfo failed: %d\n", result);
		delete [] simpleServerData->pConnectionList;
		simpleServerData->pConnectionList = 0;
#ifdef _WIN32
		DeleteCriticalSection(&simpleServerData->connectionListCS);
#endif
#ifdef __linux__
        pthread_mutex_destroy(&simpleServerData->connectionListCS);
#endif
		return false;
	}

	// Server-Socket erstellen
	simpleServerData->listenSocket = socket(simpleServerData->addrInfo->ai_family, simpleServerData->addrInfo->ai_socktype, simpleServerData->addrInfo->ai_protocol);
	if(simpleServerData->listenSocket == INVALID_SOCKET)
	{
#ifdef _WIN32
		printf("socket failed: %i\n", WSAGetLastError());
#endif
		delete [] simpleServerData->pConnectionList;
		simpleServerData->pConnectionList = 0;
#ifdef _WIN32
		DeleteCriticalSection(&simpleServerData->connectionListCS);
#endif 
#ifdef __linux__
        pthread_mutex_destroy(&simpleServerData->connectionListCS);
#endif
		freeaddrinfo(simpleServerData->addrInfo);
		return false;
	}

	// server "binden", damit der Server mit der lokalen Adresse verbunden ist
	result = bind(simpleServerData->listenSocket, simpleServerData->addrInfo->ai_addr, (int)simpleServerData->addrInfo->ai_addrlen);
	if(result == SOCKET_ERROR)
	{
#ifdef _WIN32
		printf("bind failed: %d\n", WSAGetLastError());
#endif
		delete [] simpleServerData->pConnectionList;
		simpleServerData->pConnectionList = 0;
		freeaddrinfo(simpleServerData->addrInfo);
#ifdef _WIN32
		DeleteCriticalSection(&simpleServerData->connectionListCS);
		closesocket(simpleServerData->listenSocket);
#endif
#ifdef __linux__
        pthread_mutex_destroy(&simpleServerData->connectionListCS);
        close(simpleServerData->listenSocket);
#endif
		return false;
	}
	
	freeaddrinfo(simpleServerData->addrInfo);

	// den Socket auf "listening" setzen, damit er Verbindungen annehmen kann
	result = listen(simpleServerData->listenSocket, MAX_CONNECTION_OBJECTS);
	if(result == SOCKET_ERROR)
	{
		delete [] simpleServerData->pConnectionList;
		simpleServerData->pConnectionList = 0;
#ifdef _WIN32
		printf("listen failed: %d\n", WSAGetLastError());
		DeleteCriticalSection(&simpleServerData->connectionListCS);
		closesocket(simpleServerData->listenSocket);
#endif
#ifdef __linux__
        pthread_mutex_destroy(&simpleServerData->connectionListCS);
        close(simpleServerData->listenSocket);
#endif
		return false;
	}

	// Input/Output-Methode festsetzen
#ifdef _WIN32
	result = ioctlsocket(simpleServerData->listenSocket, FIONBIO, &simpleServerData->blockingFlag);
#endif
#if __linux__
	result = ioctl(simpleServerData->listenSocket, FIONBIO, &simpleServerData->blockingFlag);
#endif
	if(result == SOCKET_ERROR)
	{
		delete [] simpleServerData->pConnectionList;
		simpleServerData->pConnectionList = 0;
#ifdef _WIN32
		printf("ioctlsocket failed: %d\n", WSAGetLastError());
		DeleteCriticalSection(&simpleServerData->connectionListCS);
		closesocket(simpleServerData->listenSocket);
#endif
#ifdef __linux__
        pthread_mutex_destroy(&simpleServerData->connectionListCS);
        close(simpleServerData->listenSocket);
#endif
		return false;
	}
	
	// Die User-definde Methode, welche in Vererbten Klassen genutzt wird, aufrufen.
	if(OnInitialize() == false)
	{
		printf("User's OnInitialize() function failed.\n");
		delete [] simpleServerData->pConnectionList;
		simpleServerData->pConnectionList = 0;
#ifdef _WIN32
		DeleteCriticalSection(&simpleServerData->connectionListCS);
		closesocket(simpleServerData->listenSocket);
#endif
#ifdef __linux__
        pthread_mutex_destroy(&simpleServerData->connectionListCS);
        close(simpleServerData->listenSocket);
#endif
		return false;
	}
	
	isRunning = true;
	return true;
}

bool SimpleServer::Tick(long sec, long usec)
{
	int result;

	simpleServerData->selectTimeout.tv_sec = sec;
	simpleServerData->selectTimeout.tv_usec = usec;

	FD_ZERO(&simpleServerData->readSet);
	FD_ZERO(&simpleServerData->writeSet);
	FD_SET(simpleServerData->listenSocket, &simpleServerData->readSet);

#ifdef _WIN32
	EnterCriticalSection(&simpleServerData->connectionListCS);
#endif
#ifdef __linux__
    pthread_mutex_lock(&simpleServerData->connectionListCS);
#endif
	for(int loopCtr = 0; loopCtr < MAX_CONNECTION_OBJECTS; ++loopCtr)
	{
		TConnection & connectionObject = simpleServerData->pConnectionList[loopCtr];

		if(connectionObject.uid)
		{
			TSocket & sobj = connectionObject.socketObject;
			if(sobj.s != INVALID_SOCKET)
			{
				if(sobj.sendBufferIndex)
				{
					FD_SET(sobj.s, &simpleServerData->writeSet);
				}
				if(sobj.recvBufferIndex < MAX_BUFFER_SIZE - 1)
				{
					FD_SET(sobj.s, &simpleServerData->readSet);
				}
			}
		}
	}
#ifdef _WIN32
	LeaveCriticalSection(&simpleServerData->connectionListCS);
#endif
#ifdef __linux__
    pthread_mutex_unlock(&simpleServerData->connectionListCS);
#endif
	// Checken, ob Events existieren (new connection, send, read)
	result = select(0, &simpleServerData->readSet, &simpleServerData->writeSet, NULL, &simpleServerData->selectTimeout);
	if(result == SOCKET_ERROR)
	{
#ifdef _WIN32
		printf("select failed: %d\n", WSAGetLastError());
#endif
		return false;
	}

	result = FD_ISSET(simpleServerData->listenSocket, &simpleServerData->readSet);			// testen ob select readSet gesetzt hat
	if(result)
	{
		SOCKET clientSocket = accept(simpleServerData->listenSocket, NULL, NULL);			// neuer Client
		if(clientSocket != INVALID_SOCKET)
		{
#ifdef _WIN32
			result = ioctlsocket(clientSocket, FIONBIO, &simpleServerData->blockingFlag);
#endif
#ifdef __linux__
			result = ioctl(clientSocket, FIONBIO, &simpleServerData->blockingFlag);
#endif
			if(result != SOCKET_ERROR)
			{
#ifdef _WIN32
				EnterCriticalSection(&simpleServerData->connectionListCS);
#endif
#ifdef __linux__
                pthread_mutex_lock(&simpleServerData->connectionListCS);
#endif
				for(int ctr = 0; ctr < MAX_CONNECTION_OBJECTS; ++ctr)
				{
					if(simpleServerData->pConnectionList[ctr].uid == 0)						// neuen Clienten in die Liste aufnehmen
					{
						TConnection & con = simpleServerData->pConnectionList[ctr];
#ifdef _WIN32
						ZeroMemory(&con, sizeof(TConnection));
#endif
#ifdef __linux__
                        memset(&con, 0, sizeof(TConnection));
#endif

						con.uid = simpleServerData->uid++;
						con.socketObject.s = clientSocket;
						//sockaddr_in connectAddr = {0};
                        sockaddr_in connectAddr;
                        memset(&connectAddr, 0, sizeof(sockaddr_in));
						
						socklen_t namelen = sizeof(sockaddr);
						getpeername(clientSocket, (sockaddr *)&connectAddr, &namelen);

						result = OnConnect(con.uid, inet_ntoa(connectAddr.sin_addr), connectAddr.sin_port);
						if(result == false)
						{
#ifdef _WIN32
							ZeroMemory(&con, sizeof(TConnection));
#endif
#ifdef __linux__
                            memset(&con, 0, sizeof(TConnection));
#endif
							printf("The OnConnect user function denied the connection.\n");
						}
						else
						{
							clientSocket = INVALID_SOCKET;
						}
						break;
					}
				}
#ifdef _WIN32
				LeaveCriticalSection(&simpleServerData->connectionListCS);
#endif
#ifdef __linux__
                pthread_mutex_unlock(&simpleServerData->connectionListCS);
#endif

				if(clientSocket != INVALID_SOCKET)											// Maximale Verbindungen erreicht, ServerSocket schliesen
				{
#ifdef _WIN32
					closesocket(clientSocket);
#endif
#ifdef __linux__
					close(clientSocket);
#endif
					clientSocket = INVALID_SOCKET;
				}
			}
			else
			{
#ifdef _WIN32
				printf("ioctlsocket failed: %d\n", WSAGetLastError());
#endif
			}
		}
		else
		{
#ifdef _WIN32
			int dwError = WSAGetLastError();
			if(dwError != WSAEWOULDBLOCK)
			{
				printf("accept failed: %d\n", dwError);
			}
#endif
		}
	}

#ifdef _WIN32
	EnterCriticalSection(&simpleServerData->connectionListCS);								// alle Clienten durchlaufen und nach Events suchen
#endif
#ifdef __linux__
    pthread_mutex_lock(&simpleServerData->connectionListCS);
#endif
	for(int loopCtr = 0; loopCtr < MAX_CONNECTION_OBJECTS; ++loopCtr)
	{
		TConnection & connectionObject = simpleServerData->pConnectionList[loopCtr];
		if(connectionObject.uid)
		{
			TSocket & sobj = connectionObject.socketObject;

			result = FD_ISSET(sobj.s, &simpleServerData->readSet);							// Gibt es Daten zum lesen?
			if(result)
			{
				int recvCount = recv(sobj.s, sobj.recvBuffer + sobj.recvBufferIndex, MAX_BUFFER_SIZE - sobj.recvBufferIndex, 0);
				printf("SimpleServer::tick->recv(): %i\n", recvCount);
				if(recvCount == SOCKET_ERROR)
				{
#ifdef _WIN32
					int dwError = WSAGetLastError();
					if(dwError == WSAEWOULDBLOCK)
					{
					}
#endif
#ifdef __linux__
                    int dwError = 0;
                    if(errno == EWOULDBLOCK)
                    {
                        dwError = errno;
                    }
#endif
					else
					{
						printf("recv failed: %d\n", dwError);
						if(connectionObject.uid)
						{
							//OnDisconnect(connectionObject.uid);							// Verbindung wurde vom Clienten beendet, alte Version
							Disconnect(connectionObject.uid);
						}
#ifdef _WIN32
						closesocket(connectionObject.socketObject.s);
#endif
#ifdef __linux__
                        close(connectionObject.socketObject.s);
#endif
						connectionObject.uid = 0;
					}
				}
				else if(recvCount == 0)														// Verbindung wurde vom Clienten beendet
				{
					if(connectionObject.uid)
					{
						//OnDisconnect(connectionObject.uid);								// Verbindung wurde vom Clienten beendet, alte Version
						Disconnect(connectionObject.uid);
					}
#ifdef _WIN32
                    closesocket(connectionObject.socketObject.s);
#endif
#ifdef __linux__
                    close(connectionObject.socketObject.s);
#endif
					connectionObject.uid = 0;
				}
				else																		// Daten vorhanden -> Lesen
				{
					int bytesProcesed = 0;
					sobj.recvBufferIndex += recvCount;
					
					do
					{
						bytesProcesed = OnData(connectionObject.uid, sobj.recvBuffer, sobj.recvBufferIndex);
						if(bytesProcesed == 0)
						{
						}
						else if(bytesProcesed == sobj.recvBufferIndex)
						{
							sobj.recvBufferIndex = 0;
						}
						else
						{
							sobj.recvBufferIndex -= bytesProcesed;
							memmove(sobj.recvBuffer, sobj.recvBuffer + bytesProcesed, sobj.recvBufferIndex);
						}
					}
					while(bytesProcesed && sobj.recvBufferIndex);
				}
			}

			result = FD_ISSET(sobj.s, &simpleServerData->writeSet);							// etwas zum senden?
			if(result)
			{
				int sendCount = send(sobj.s, sobj.sendBuffer, sobj.sendBufferIndex, 0);
				printf("SimpleServer::send: %i bytes wurden gesendet\n", sendCount);
				if(sendCount == SOCKET_ERROR)
				{
#ifdef _WIN32
					int dwError = WSAGetLastError();
					if(dwError == WSAEWOULDBLOCK)
					{
					}
#endif
#ifdef __linux__
                    int dwError = 0;
                    if (errno == EWOULDBLOCK)
                    {
                        dwError = errno;
                    }
#endif
					else
					{
						printf("send failed: %d\n", dwError);
						if(connectionObject.uid)
						{
							//OnDisconnect(connectionObject.uid);							// Verbindung wurde vom Clienten beendet, alte Version
							Disconnect(connectionObject.uid);
						}
#ifdef _WIN32
						closesocket(connectionObject.socketObject.s);
#endif
#ifdef __linux__
                        close(connectionObject.socketObject.s);
#endif
						connectionObject.uid = 0;
					}
				}
				else
				{
					sobj.sendBufferIndex -= sendCount;
					if(sobj.sendBufferIndex)
					{
						memmove(sobj.sendBuffer, sobj.sendBuffer + sendCount, sobj.sendBufferIndex);
					}
				}
			}
		}
	}
#ifdef _WIN32
	LeaveCriticalSection(&simpleServerData->connectionListCS);
#endif
#ifdef __linux__
    pthread_mutex_unlock(&simpleServerData->connectionListCS);
#endif

	return true;
}

void SimpleServer::Destroy()
{
	OnDeinitialize();

	if(simpleServerData->pConnectionList)
	{
		for(int x = 0; x < MAX_CONNECTION_OBJECTS; ++x)
		{
			if(simpleServerData->pConnectionList[x].uid)
			{
#ifdef _WIN32
				closesocket(simpleServerData->pConnectionList[x].socketObject.s);
#endif
#ifdef __linux__
				close(simpleServerData->pConnectionList[x].socketObject.s);
#endif
			}
		}
		delete [] simpleServerData->pConnectionList;

		simpleServerData->pConnectionList = 0;
	}
#ifdef _WIN32
	DeleteCriticalSection(&simpleServerData->connectionListCS);
	DeinitializeWinsock();
#endif
#ifdef __linux__
    pthread_mutex_destroy(&simpleServerData->connectionListCS);
#endif

	isRunning = false;
}

bool SimpleServer::Send(int uid, void * data, size_t size)
{
	bool bResult = false;

#ifdef _WIN32
	EnterCriticalSection(&simpleServerData->connectionListCS);
#endif
#ifdef __linux__
    pthread_mutex_lock(&simpleServerData->connectionListCS);
#endif

	for(int loopCtr = 0; loopCtr < MAX_CONNECTION_OBJECTS; ++loopCtr)
	{
		TConnection & connectionObject = simpleServerData->pConnectionList[loopCtr];
		if(connectionObject.uid == uid)
		{
			TSocket & sobj = connectionObject.socketObject;

			if(sobj.sendBufferIndex + size < (size_t)MAX_BUFFER_SIZE)
			{
				memcpy(sobj.sendBuffer + sobj.sendBufferIndex, data, size);
				sobj.sendBufferIndex += size;
				bResult = true;
			}

			break;
		}
	}

#ifdef _WIN32
	LeaveCriticalSection(&simpleServerData->connectionListCS);
#endif
#ifdef __linux__
    pthread_mutex_unlock(&simpleServerData->connectionListCS);
#endif

	return bResult;
}

void SimpleServer::Disconnect(int uid)
{
#ifdef _WIN32
	EnterCriticalSection(&simpleServerData->connectionListCS);
#endif
#ifdef __linux__
    pthread_mutex_lock(&simpleServerData->connectionListCS);
#endif

	for(int loopCtr = 0; loopCtr < MAX_CONNECTION_OBJECTS; ++loopCtr)
	{
		TConnection & connectionObject = simpleServerData->pConnectionList[loopCtr];
		if(connectionObject.uid == uid)
		{
			TSocket & sobj = connectionObject.socketObject;
			if(connectionObject.uid)
			{
				OnDisconnect(connectionObject.uid);
			}

#ifdef _WIN32
			closesocket(sobj.s);
#endif
#ifdef __linux__
            close(sobj.s);
#endif
			connectionObject.uid = 0;

			break;
		}
	}

#ifdef _WIN32
	LeaveCriticalSection(&simpleServerData->connectionListCS);
#endif
#ifdef __linux__
    pthread_mutex_unlock(&simpleServerData->connectionListCS);
#endif
}
