#ifndef _PACKETS_H
#define _PACKETS_H

#include <cstdio>
#include <cstring>

#include "opcodes.h"

const int MAX_PACKETSIZE = 8192;

typedef struct PACKET
{
    unsigned short opcode;                  // wie das Packet verarbeitet werden soll	(2 Byte)
    unsigned short size;                    // die anzahl an Bytes in data				(2 Byte)
    unsigned char data[MAX_PACKETSIZE - 4]; // Datenarray							(8188 Bytes)

    PACKET();
} typPACKET;

void printPacket(PACKET *p); // benötigt einen Ausgabe-Stream, z.B. eine debug-console

#endif
