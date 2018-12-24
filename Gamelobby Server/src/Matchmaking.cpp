#include "Matchmaking.h"

Matchmaking::Matchmaking(GameManager *_gm)
{
    playerCap = 1000;

    if (_gm != NULL)
        gameManager = _gm;
}

Matchmaking::~Matchmaking()
{
}

bool Matchmaking::Tick(void)
{
    std::vector<Player *>::iterator pIter;
    std::vector<GameLobby *>::iterator gIter;

    try
    {
        if (playerList.size() == 0) // Dia: Gibt es suchende Spieler?
        {
            return false; // hier gibt es nichts zu tun
        }

        for (pIter = playerList.begin(); pIter != playerList.end(); pIter++)
        {
            if ((*pIter)->linkgedGame() == NULL) // Dia: Bereits in einem Spiel?
            {
                FILTER filter = (*pIter)->getFilter();

                for (gIter = gameManager->getList().begin(); gIter != gameManager->getList().end(); gIter++)
                {
                    if (filter.map == (*gIter)->getMap() && filter.mode == (*gIter)->getMode()) // Dia: Spiel gefunden
                    {
                        (*gIter)->addPlayer((*pIter)); // Dia: Spieler hinzufuegen
                        (*pIter)->linkGame((*gIter));

                        printf("MATCHMAKING: Spiel fuer Spieler '%i' gefunden.\n", (*pIter)->getSID());
                        break; // Es muss eine alternative gefunden werden, die Schleife eher zu verlassen
                    }
                }

                if ((*pIter)->linkgedGame() == NULL) // Dia: Spiel erstellen
                {
                    GameLobby *lobby = gameManager->createGame((int)filter.mode * 2, "AUTO GENERATED MATCH", filter.map, filter.mode);

                    lobby->addPlayer((*pIter));
                    (*pIter)->linkGame(lobby);

                    printf("MATCHMAKING: Spiel fuer '%i' erstellt.\n", (*pIter)->getSID());
                }
            }
        }
    }
    catch (std::exception e)
    {
        printf("MATCHMAKING: Fehler im Tick: %s\n", e.what());
        return false;
    }

    return true;
}

bool Matchmaking::addPlayer(Player *_player, FILTER _filter)
{
    try
    {
        std::vector<Player *>::iterator iter;

        iter = find(playerList.begin(), playerList.end(), _player);

        if (iter == playerList.end() && (int)playerList.size() <= playerCap) // iter == end() => Spieler is noch nicht am suchen
        {
            _player->setFilter(_filter);
            playerList.push_back(_player);
        }

        printf("MATCHMAKING: Spieler mit ID '%i' wurde hinzugefuegt.\n", _player->getSID());
    }
    catch (std::exception e)
    {
        printf("MATCHMAKING: Fehler beim Hinzufügen eines Spielers: %s\n", e.what());
        return false;
    }

    return true;
}

bool Matchmaking::removePlayer(Player *_player)
{
    try
    {
        std::vector<Player *>::iterator iter;

        iter = find(playerList.begin(), playerList.end(), _player);

        if (iter == playerList.end())
        {
            return false;
        }

        playerList.erase(iter);
        printf("MATCHMAKING: Spieler mit ID '%i' wurde entfernt.\n", _player->getSID());
    }
    catch (std::exception e)
    {
        printf("MATCHMAKING: Fehler beim Entfernen eines Spielers: %s\n", e.what());
        return false;
    }

    return true;
}

/*
 * Diese Methode brauchen wir, damit wir die Spieler aus einem gestartetem
 * Spiel löschen können, da diese kein Spiel mehr benötigen
 */
bool Matchmaking::removePlayer(GameLobby *_lobby)
{
    try
    {
        std::vector<Player *>::iterator iter;

        for (iter = _lobby->getPlayers().begin(); iter != _lobby->getPlayers().end(); iter++)
        {
            removePlayer((*iter));
        }
    }
    catch (std::exception e)
    {
        return false;
    }

    return true;
}

std::vector<GameLobby *> Matchmaking::getReadyGames(void) // In Server->Tick wird diese Methode genutzt um Spiele zu starten
{
    std::vector<GameLobby *> list;
    std::vector<GameLobby *>::iterator iter;

    try
    {
        for (iter = gameManager->getList().begin(); iter != gameManager->getList().end(); iter++)
        {
            if ((*iter)->getCurrentPlayers() == (*iter)->getMaxPlayers()) // Das Spiel ist voll => es kann gespielt werden
            {
                list.push_back((*iter));
            }
        }
    }
    catch (std::exception e)
    {
        printf("MATCHMAKING: Fehler beim finden von ReadyGames: %s\n", e.what());
    }

    return list;
}
