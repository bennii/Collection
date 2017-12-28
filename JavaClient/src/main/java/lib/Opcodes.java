package lib;

/*
    This are the opcodes that are used during the server / client
    communication. They define different operations. Different operations
    contain different data. Hence they have to be parsed differently.

    ONLY CHANGE IF YOU ARE AWARE OF THE CONSEQUENCES.

	|short->opcode|short->size| are part of every data packet  and contain two unsigned short each.
*/

public class Opcodes {
    // Misc.  - I do not remember why this was created.
    public final int OPCODE_SPAM					= 8888;

    // SERVER OPCODES
    public final int SERVER_ANSWER_GAMELIST			= 2000;			//
    public final int SERVER_ANSWER_CREATEGAME		= 2001;			//
    public final int SERVER_ANSWER_LOGIN			= 2002;			//
    public final int SERVER_ANSWER_LOGOUT			= 2003;			//
    public final int SERVER_ANSWER_JOINGAME			= 2004;			//
    public final int SERVER_ANSWER_CLOSEGAME		= 2005;			//
    public final int SERVER_ANSWER_STARTGAME		= 2006;			//
    public final int SERVER_ANSWER_PLAYERJOINED		= 2007;			//
    public final int SERVER_ANSWER_PLAYERLEFT		= 2008;			//
    public final int SERVER_ANSWER_LEAVEGAME		= 2009;			//
    public final int SERVER_ANSWER_MAPLIST			= 2010;			//
    public final int SERVER_ANSWER_GAMESHUTDOWN		= 2011;			//
    public final int SERVER_ANSWER_JOINQUEUE		= 2012;			//
    public final int SERVER_ANSWER_LEAVEQUEUE       = 2013;	        //
    public final int SERVER_ANSWER_GAMEFOUND		= 2014;			//
    public final int SERVER_ANSWER_QUEUEKICK		= 2015;			//

    // CLIENT OPCODES
    public final int CLIENT_REQUEST_GAMELIST		= 1000;			//
    public final int CLIENT_REQUEST_CREATEGAME		= 1001;			//
    public final int CLIENT_REQUEST_LOGIN			= 1002;			//
    public final int CLIENT_REQUEST_LOGOUT			= 1003;			//
    public final int CLIENT_REQUEST_JOINGAME		= 1004;			//
    public final int CLIENT_REQUEST_CLOSEGAME		= 1005;			//
    public final int CLIENT_REQUEST_STARTGAME		= 1006;			//
    public final int CLIENT_REQUEST_PLAYERLEFT		= 1008;			//
    public final int CLIENT_REQUEST_LEAVEGAME		= 1009;			//
    public final int CLIENT_REQUEST_MAPLIST			= 1010;			//
    public final int CLIENT_REQUEST_GAMESHUTTDOWN	= 1011;			//
    public final int CLIENT_REQUEST_JOINQUEUE		= 1012;			//
    public final int CLIENT_REQUEST_LEAVEQUEUE      = 1013;         //

    // ADMIN OPCODES
    public final int ADMIN_REQUEST_GAMES			= 10000;        //
    public final int ADMIN_REQUEST_PLAYER			= 10001;        //
    public final int ADMIN_REQUEST_KICK				= 10002;        //
    public final int ADMIN_REQUEST_CLOSE			= 10003;        //
}
