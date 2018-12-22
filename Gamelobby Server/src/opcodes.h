#ifndef _OPCODES_H
#define _OPCODES_H

/*	Das hier sind die Opcodes, die für die Kommunikation zwischen
	Server und Clienten genutzt werden. NUR ÄNDERN WENN DU WIRKLICH
	WEIßT, WAS DU DA MACHST! ANSONSTEN KOMMST DU IN DIE HÖLLE!

	|short->opcode|short->size| sind in jedem Packet enthalten und umfassen 4 Bytes (= 2 x unsigned short)
*/

// Misc.
#define	OPCODE_SPAM						8888

// SERVER OPCODES
#define SERVER_ANSWER_GAMELIST			2000			//
#define SERVER_ANSWER_CREATEGAME		2001			//
#define SERVER_ANSWER_LOGIN				2002			//
#define SERVER_ANSWER_LOGOUT			2003			//
#define SERVER_ANSWER_JOINGAME			2004			//
#define SERVER_ANSWER_CLOSEGAME			2005			//
#define SERVER_ANSWER_STARTGAME			2006			//
#define SERVER_ANSWER_PLAYERJOINED		2007			//
#define SERVER_ANSWER_PLAYERLEFT		2008			//
#define SERVER_ANSWER_LEAVEGAME			2009			//
#define SERVER_ANSWER_MAPLIST			2010			//
#define SERVER_ANSWER_GAMESHUTDOWN		2011			//
#define SERVER_ANSWER_JOINQUEUE			2012			//
#define SERVER_ANSWER_LEAVEQUEUE        2013	        //
#define SERVER_ANSWER_GAMEFOUND			2014			//
#define SERVER_ANSWER_QUEUEKICK			2015			//


// CLIENT OPCODES
#define CLIENT_REQUEST_GAMELIST			1000			//	case vorhanden
#define CLIENT_REQUEST_CREATEGAME		1001			//	case vorhanden
#define CLIENT_REQUEST_LOGIN			1002			//	case vorhanden
#define CLIENT_REQUEST_LOGOUT			1003			//	case vorhanden
#define CLIENT_REQUEST_JOINGAME			1004			//	case vorhanden
#define CLIENT_REQUEST_CLOSEGAME		1005			//	case vorhanden
#define CLIENT_REQUEST_STARTGAME		1006			//  case vorhanden
#define CLIENT_REQUEST_PLAYERLEFT		1008			//	case vorhanden
#define CLIENT_REQUEST_LEAVEGAME		1009			//	case vorhanden
#define CLIENT_REQUEST_MAPLIST			1010			//	ist das noch notwendig?
#define CLIENT_REQUEST_GAMESHUTTDOWN	1011			//	case nicht notwendig, geplant als Reaktion auf closegame für andere Spieler
#define CLIENT_REQUEST_JOINQUEUE		1012			// 	!case notwendig
#define CLIENT_REQUEST_LEAVEQUEUE       1013            //

// ADMIN OPCODES
#define ADMIN_REQUEST_GAMES				10000           // KOMPLETT UNBEARBEITET (unwichtig)
#define ADMIN_REQUEST_PLAYER			10001           // KOMPLETT UNBEARBEITET (unwichtig)
#define ADMIN_REQUEST_KICK				10002           // KOMPLETT UNBEARBEITET (unwichtig)
#define ADMIN_REQUEST_CLOSE				10003           // KOMPLETT UNBEARBEITET (unwichtig)


#endif
