#include "Packetbuilder.h"

Packetbuilder::Packetbuilder(void)
{
	packet = new PACKET();
	index = 0;
}

Packetbuilder::~Packetbuilder(void)
{
}

void Packetbuilder::copyPacket(PACKET * p)
{
	cleanup();
	memcpy(packet, p, p->size + 4);
}

unsigned int Packetbuilder::getIndex()
{
	return index;
}

unsigned short Packetbuilder::getSize()
{
	return packet->size + 4;
}

void Packetbuilder::setOpcode(unsigned short opcode)
{
	packet->opcode = opcode;
}

void Packetbuilder::cleanup()
{
	memset(packet, 0, sizeof(*packet));
	index = 0;
}

void Packetbuilder::addByte(unsigned char val)
{
	unsigned char * pointer = packet->data + index;

	*pointer = val;

	index += sizeof(unsigned char);
	packet->size += sizeof(unsigned char);
}

void Packetbuilder::addWord(unsigned short val)
{
	unsigned char * pointer = packet->data + index;
	*((unsigned short *)pointer) = val;

	index += sizeof(unsigned short);
	packet->size += sizeof(unsigned short);
}

void Packetbuilder::addDword(unsigned long val)
{
	unsigned char * pointer = packet->data + index;
	*((unsigned long *)pointer) = val;

	index += sizeof(unsigned long);
	packet->size += sizeof(unsigned long);
}

void Packetbuilder::addFloat(float val)
{
	unsigned char * pointer = packet->data + index;
	*((float *)pointer) = val;

	index += sizeof(float);
	packet->size += sizeof(float);
}

void Packetbuilder::addDouble(double val)
{
	unsigned char * pointer = packet->data + index;
	*((double *)pointer) = val;

	index += sizeof(double);
	packet->size += sizeof(double);
}

void Packetbuilder::addString(char * string, int length)
{
	addWord((unsigned short)length);

	unsigned char * pointer = packet->data + index;

	for(int i = 0; i < length; i++)
		*(pointer + i) = string[i];

	index += sizeof(char) * length;
	packet->size += sizeof(char) * length;
}

PACKET * Packetbuilder::getPacket()
{
	return packet;
}
