#ifndef _PACKETREADER_H
#define _PACKETREADER_H

#include "Packets.h"

class Packetreader
{
public:
	Packetreader(void);
	~Packetreader(void);

	void			setPacket(PACKET * p);			// Datenpacket zum lesen hinzufügen

	void			cleanup(void);					// aufrämen und fürs lesen des nächsten Packets vorbereiten.

	unsigned short	getSize(void);					// komplette Größe des Packets
	unsigned short	getIndex(void);					// aktueller Index, an dem als nächstes gelesen wird
	unsigned short	getOpcode(void);				// operation code des Packets;

	unsigned char	readByte(void);					// 1 Byte (8bit) lesen
	unsigned short	readWord(void);					// 2 Byte (16bit) lesen
	unsigned long	readDword(void);				// 4 Byte (32bit) lesen
	float			readFloat(void);				// 4 Byte (32bit, im Regelfall) lesen
	double 			readDouble(void);				// 8 Byte (64bit, im Regelfall) lesen
	char *			readString(void);				// count Bytes (count*8bits) lesen; es wird angenommen das zuvor im WORD-Format die Länge des Strings angegeben wird (einfach Builder nutzen)

private:
	PACKET * packet;								// das Datenpacket, bestehend aus: |opcode|size|daten....|
	unsigned int index;								// stelle, an der gelesen wird

};

#endif