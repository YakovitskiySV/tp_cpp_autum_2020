#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "pet.h"

int main() {
    size_t petsNumber = 0;
    while (!(scanf("%zu", &petsNumber)) || ((int) petsNumber < 0)) {
        printf("%s", "Please enter a valid pets number\n");
    }
    Pet *pets;
    if (!(pets = (Pet*) malloc(petsNumber * sizeof(Pet)))) {
        perror("allocation error");
        return 0;
    }
    char *params[3];

    for (size_t i = 0 ; i < 3 ; i++) {
        params[i] = (char*) malloc(64 * sizeof(char));
    }

    for (size_t i = 0 ; i < petsNumber ; i++) {
        for (size_t j = 0 ; j < 3 ; j++) {
            scanf("%2s", params[j]);
        }
        if (!(CreatePet(&pets[i], params))) {
            for (size_t j = 0 ; j < i ; j++) {
                FreePet(&pets[j]);
                free(params[j]);
            }
            free(pets);
            return 0;
        }
    }
    for (size_t i = 0 ; i < 3 ; i++) {
        free(params[i]);
    }
    if (!(SortPets(pets, petsNumber))) {
        for (size_t i = 0 ; i < petsNumber ; i++) {
            FreePet(&pets[i]);
        }
        free(pets);
        return 0;
    }
    for (size_t i = 0 ; i < petsNumber ; i++) {
        if (!(PrintPet(&pets[i]))) {
            for (size_t j = 0 ; j < i ; j++) {
                FreePet(&pets[j]);
            }
            free(pets);
            return 0;
        }
        FreePet(&pets[i]);
    }
    free(pets);
    return 1;
}
