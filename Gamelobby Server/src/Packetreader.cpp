#include "Packetreader.h"

Packetreader::Packetreader(void)
{
    index = 0;
    packet = NULL;
}

Packetreader::~Packetreader(void)
{
}

void Packetreader::setPacket(PACKET *p)
{
    packet = p;
}

// Diese Methode muss vielleicht entfernt werden
// oder mit einem delete packet arbeiten. Das würde
// aber in die Datenkontrolle der darüber liegenden
// Ebene eingreifen und könnte potentiell Fehler
// verursachen.
void Packetreader::cleanup(void)
{
    if (packet == NULL)
        return;

    memset(packet, 0, sizeof(PACKET));
    index = 0;
}

unsigned short Packetreader::getSize()
{
    if (packet == NULL)
        return 0;

    return packet->size + 4;
}
unsigned short Packetreader::getIndex()
{
    if (packet == NULL)
        return 0;

    return index;
}

unsigned short Packetreader::getOpcode()
{
    if (packet == NULL)
        return 0;

    return packet->opcode;
}

unsigned char Packetreader::readByte()
{
    if (packet == NULL || index + sizeof(unsigned char) > packet->size)
        return 0;

    unsigned char *pointer = (unsigned char *)packet->data + index;
    index += sizeof(unsigned char);

    return *pointer;
}

unsigned short Packetreader::readWord()
{
    if (packet == NULL || index + sizeof(unsigned short) > packet->size)
        return 0;

    unsigned char *pointer = (unsigned char *)packet->data + index;
    index += sizeof(unsigned short);

    return *((unsigned short *)pointer);
}

unsigned long Packetreader::readDword()
{
    if (packet == NULL || index + sizeof(unsigned int) > packet->size)
        return 0;

    unsigned char *pointer = (unsigned char *)packet->data + index;
    index += sizeof(unsigned long);

    return *((unsigned long *)pointer);
}

float Packetreader::readFloat()
{
    if (packet == NULL || index + sizeof(float) > packet->size)
        return 0.0;

    unsigned char *pointer = (unsigned char *)packet->data + index;
    index += sizeof(float);

    return *((float *)pointer);
}

double Packetreader::readDouble()
{
    if (packet == NULL || index + sizeof(double) > packet->size)
        return 0.0;

    unsigned char *pointer = (unsigned char *)packet->data + index;
    index += sizeof(double);

    return *((double *)pointer);
}

char *Packetreader::readString()
{
    if (packet == NULL)
        return NULL;

    unsigned short len = readWord();

    if (index + len * sizeof(unsigned char) > packet->size)
        return (char *)"empty";

    char *string = new char[len];
    char *pointer = (char *)packet->data + index;

    memset(string, 0, len + 1);

    for (int i = 0; i < len; i++)
    {
        string[i] = *(pointer + i);
    }

    index += sizeof(char) * len;
    return string;
}
