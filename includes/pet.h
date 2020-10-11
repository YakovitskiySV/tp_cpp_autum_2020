#ifndef INCLUDES_PET_H_
#define INCLUDES_PET_H_

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

#endif  // INCLUDES_PET_H_
