#ifndef PET_H
#define PET_H

#include "stdlib.h"

typedef struct Pet {
    char *name;
    char *type;
    char *color;
} Pet;

// Init/release operations
int CreatePet(Pet *newPet, char *params[3]);
int FreePet(Pet *pet);

// Extra operations
int PrintPet(const Pet *pet);
int SortPets(Pet *pets, const size_t petsNumber);

#endif  // PET_H