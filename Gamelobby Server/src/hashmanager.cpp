#include "hashmanager.h"

HASH::HASH(void)
{
    gameLen = 0;
    hashNumber = 0;
}

HASH::~HASH(void)
{
    gameHash.clear();
    completeHash.clear();
}

Hashmanager::Hashmanager()
{
    hashLen = 5; // wir einigen uns vorerst auf 5
}

Hashmanager::~Hashmanager()
{
    hashTable.clear();
}

int Hashmanager::contains(HASH *_hash)
{
    std::vector<HASH>::iterator iter;

    for (iter = hashTable.begin(); iter != hashTable.end(); iter++)
    {
        if (iter->gameHash == _hash->gameHash && iter->completeHash == _hash->completeHash)
            return iter->hashNumber;
    }

    return -1;
}

int Hashmanager::contains(std::string _hash)
{
    std::vector<HASH>::iterator iter;

    for (iter = hashTable.begin(); iter != hashTable.end(); iter++)
    {
        if (iter->gameHash == _hash || iter->completeHash == _hash)
            return iter->hashNumber;
    }

    return -1;
}

void Hashmanager::removeHash(HASH *_hash)
{
    if (contains(_hash) >= 0)
    {
        std::vector<HASH>::iterator iter;

        for (iter = hashTable.begin(); iter != hashTable.end(); iter++)
        {
            if (iter->gameHash == _hash->gameHash && iter->completeHash == _hash->completeHash)
            {
                hashTable.erase(iter);
            }
        }
    }
}

HASH Hashmanager::createHash(std::string _string)
{
    int i = 0;
    HASH hash;
    MD5Hash md5(_string);
    std::string temp;

    hash.gameLen = hashLen;
    hash.completeHash = md5.hexdigest();
    hash.hashNumber = hashTable.size() + 1;

    std::transform(hash.completeHash.begin(), hash.completeHash.end(), hash.completeHash.begin(), toupper);

    do
    {
        if (i > 27)
        {
            md5.update((char *)std::string(_string + "haha").c_str(), _string.length() + 4);
            hash.completeHash = md5.hexdigest();
            i = 0;
        }

        temp = hash.completeHash.substr(i, hashLen);
        i++;
    } while (contains(temp) >= 0);

    hash.gameHash = temp;

    hashTable.push_back(hash);
    return hash;
}
