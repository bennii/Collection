#ifndef _PACKETBUILDER_H
#define _PACKETBUILDER_H

#include "Packets.h"

class Packetbuilder
{
public:
	Packetbuilder(void);
	~Packetbuilder(void);
	
	void			copyPacket(PACKET * p);

	unsigned int	getIndex(void);
	unsigned short	getSize(void);

	void			setOpcode(unsigned short opcode);			// Verwendung des Packets festlegen
	void			addByte(unsigned char val);					// selbsterklärend
	void			addWord(unsigned short val);				// selbsterklärend
	void			addDword(unsigned long val);				// selbsterklärend
	void			addFloat(float val);						// selbsterklärend
	void 			addDouble(double val);
	void			addString(char * string, int length);		// selbsterklärend
	
	PACKET *		getPacket(void);							// Packet für sonstige Zwecke wie senden ausgeben
	void			cleanup();									// aufräumen fürs nächste Packet

private:
	PACKET * packet;											// das Datenpacket, bestehend aus: |opcode|size|daten....|
	unsigned int index;											// stelle, an der gelesen wird
};

#endif