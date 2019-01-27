#include "Packets.h"

PACKET::PACKET()
{
    size = 0;
    opcode = 0;

    memset(data, 0, MAX_PACKETSIZE - 4);
}

void printPacket(PACKET *_p)
{
    printf("opcode: 0x%.4X; %u\n", _p->opcode, _p->opcode);
    printf("size: 0x%.4X; %u\ndata: \n", _p->size, _p->size);

    if (_p->size > 0)
    {
        for (int i = 0; i < _p->size; i++)
            if ((i + 1) % 16 == 0)
                printf("0x%.2X\n", _p->data[i]);
            else
                printf("0x%.2X ", _p->data[i]);
    }

    printf("\n");
}
