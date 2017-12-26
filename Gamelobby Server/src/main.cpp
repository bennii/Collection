#include "Server.h"

int main(void)
{
	Server * server = new Server();

	if((server->Create(22350)))
	{
        timestamp();
		printf("MAIN: Server laeuft auf Port: %i. \n", server->GetPort());
	}
	
	
	while(server->IsRunning())
	{	
		server->Tick(1, 1);
	}

	server->Destroy();

	delete server;
	return 0;
}
