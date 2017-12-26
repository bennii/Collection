#include "Packets.h"

PACKET::PACKET()
{
	size = 0;
	opcode = 0;

	memset(data, 0, MAX_PACKETSIZE - 4);
}

void printPacket(PACKET * _p)
{
	printf("%.4X ", _p->opcode); printf("%.4X ", _p->size); 

	for(int i = 0; i < _p->size; i++)
		printf("%.2X", _p->data[i]);

	printf("\n");
}