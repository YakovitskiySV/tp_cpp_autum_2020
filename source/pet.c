#include <stdio.h>  // NOLINT
#include <stdlib.h>  // NOLINT
#include <string.h>  // NOLINT
#include "pet.h"  // NOLINT

pet *allocate_pets(size_t *pets_number) {
    if (!pets_number || pets_number == 0) {
        return NULL;
    }
    pet *pets = malloc(*pets_number * sizeof(pet));
    if (!pets) {
        return NULL;
    }
    return pets;
}

int set_pets_name(pet *single_pet, char *const name) {
    if (!single_pet || !name) {
        return 1;
    }
    size_t name_size = strlen(name) + 1;
    single_pet->name = (char *)malloc(name_size * sizeof(char));
    if (!single_pet->name) {
        return 1;
    }
    strncpy(single_pet->name, name, name_size);
    return 0;
}

int set_pets_type(pet *single_pet, char *const type) {
    if (!single_pet || !type) {
        return 1;
    }
    size_t type_size = strlen(type) + 1;
    single_pet->type = (char *)malloc(type_size * sizeof(char));
    if (!single_pet->type) {
        return 1;
    }
    strncpy(single_pet->type, type, type_size);
    return 0;
}

int set_pets_color(pet *single_pet, char *const color) {
    if (!single_pet || !color) {
        return 1;
    }
    size_t color_size = strlen(color) + 1;
    single_pet->color = (char *)malloc(color_size * sizeof(char));
    if (!single_pet->color) {
        return 1;
    }
    strncpy(single_pet->color, color, color_size);
    return 0;
}

int create_pet(pet *new_pet, char *expected_name, char *expected_type,
               char *expected_color) {
    if (!new_pet || !expected_name || !expected_type || !expected_color) {
        return 1;
    }
    if (set_pets_name(new_pet, expected_name) != 0) {
        return 1;
    }
    if (set_pets_type(new_pet, expected_type) != 0) {
        free(new_pet->name);
        return 1;
    }
    if (set_pets_color(new_pet, expected_color) != 0) {
        free(new_pet->name);
        free(new_pet->type);
        return 1;
    }
    return 0;
}

int free_pet(pet *single_pet) {
    if (!single_pet) {
        return 1;
    }
    if (single_pet->name) {
        free(single_pet->name);
    }
    if (single_pet->color) {
        free(single_pet->color);
    }
    if (single_pet->type) {
        free(single_pet->type);
    }
    return 0;
}

int free_pets(pet *pets, size_t *pets_number) {
    if (!pets || *pets_number == 0) {
        return 1;
    }
    for (size_t i = 0; i < *pets_number; ++i) {
        free_pet(&pets[i]);
    }
    free(pets);
    return 0;
}

int print_pet(pet *pet) {
    if (!pet || !pet->name || !pet->type || !pet->color) {
        return 0;
    }
    printf("name: %s, type: %s, color: %s\n", pet->name, pet->type, pet->color);
    return 1;
}

int print_pets_by_type(pet *pets, size_t *pets_number,
                       char *requested_pets_type) {
    if (!pets || !requested_pets_type) {
        return 1;
    }
    int counter = 0;
    for (size_t i = 0; i < *pets_number; ++i) {
        if (!pets->type) {
            return 1;
        }
        if (strcmp(pets[i].type, requested_pets_type) == 0) {
            print_pet(&pets[i]);
            ++counter;
        }
    }
    if (counter == 0) {
        printf("there are no animal with type %s :-(", requested_pets_type);
    }
    return 0;
}
