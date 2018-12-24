#ifndef HASHMANAGER_H
#define HASHMANAGER_H

#include "MD5Hash.h"
#include <vector>
#include <algorithm>

typedef struct HASH
{
    int gameLen;
    int hashNumber;
    std::string gameHash;
    std::string completeHash;

    HASH(void);
    ~HASH(void);
} tagHASH;

class Hashmanager
{
  public:
    Hashmanager();
    ~Hashmanager();

    int contains(HASH *_hash);
    int contains(std::string _hash);
    void removeHash(HASH *_hash);
    HASH createHash(std::string _string);

  private:
    int hashLen;
    std::vector<HASH> hashTable;
};

#endif // HASHMANAGER_H
