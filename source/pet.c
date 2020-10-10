#include "pet.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"


int CreatePet(Pet *newPet, char *params[3]) {
    // reading pet's name
    if (!params || !newPet || !(params[0])) {
        perror("pointer error");
        return 0;
    }
    size_t bufSize = strlen(params[0]) + 1;
    if (!(newPet->name = (char*) malloc(bufSize * sizeof(char)))) {
        perror("allocation error");
        return 0;
    }
    strncpy(newPet->name, params[0], bufSize);
    // reading pet's type
    if (!(params[1])) {
        perror("pointer error");
        free(newPet->name);
        return 0;
    }
    bufSize = strlen(params[1]) + 1;
    if (!(newPet->type = (char*) malloc(bufSize * sizeof(char)))) {
        perror("allocation error");
        free(newPet->name);
        return 0;
    }
    strncpy(newPet->type, params[1], bufSize);
    // reading pet's color
    if (!(params[2])) {
        perror("pointer error");
        free(newPet->name);
        free(newPet->type);
        return 0;
    }
    bufSize = strlen(params[2]) + 1;
    if (!(newPet->color = (char*) malloc(bufSize * sizeof(char)))) {
        perror("allocation error");
        free(newPet->name);
        free(newPet->type);
        return 0;
    }
    strncpy(newPet->color, params[2], bufSize);
    return 1;
}

int SortPets(Pet *pets, const size_t petsNumber) {
    if (!pets || (int) petsNumber < 1) {
        perror("Pointer error");
        return 0;
    }
    for (size_t i = 0 ; i < petsNumber ; i++) {
        if (!pets[i].name
        || !pets[i].type
        || !pets[i].color) {
            perror("pointer error") ;
            return 0;
        }
    }
    for (size_t i = 0 ; i < petsNumber ; i++) {
        for (size_t j = 0; j < petsNumber - 1; j++) {
            if (strcmp(pets[j].type, pets[j + 1].type) > 0) {
                Pet temp = pets[j];
                pets[j] = pets[j + 1];
                pets[j + 1] = temp;
            }
        }
    }
    return 1;
}

int DeletePet(Pet *pet) {
    if(pet->name) {
        free(pet->name);
    }
    if (pet->color) {
        free(pet->color);
    }
    if (pet->type) {
        free(pet->type);
    }
    return 1;
}

int PrintPet(const Pet *pet) {
    if (!pet
    || !pet->name
    || !pet->type
    || !pet->color) {
        perror("pointer error");
        return 0;
    }
    printf("name: %s, type: %s, color: %s\n",
           pet->name,
           pet->type,
           pet->color);
    return 1;
}