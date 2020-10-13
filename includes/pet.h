#ifndef INCLUDES_PET_H_
#define INCLUDES_PET_H_

#include <stdlib.h>

typedef struct pet {
    char *name;
    char *type;
    char *color;
} pet;

 //  Init/release operations
pet *allocate_pets(size_t *pets_number);
int create_pet(pet *new_pet,
                char *expected_name,
                char *expected_type,
                char *expected_color);
int free_pet(pet *single_pet);
int free_pets(pet *pets, size_t *pets_number);

 // set operations
int set_pets_name(pet *single_pet, char *name);
int set_pets_type(pet *single_pet, char *type);
int set_pets_color(pet *single_pet, char *color);


 //  Extra operations
int print_pet(pet *single_pet);
int print_pets_by_type(pet *pets, size_t *pets_number, char *requested_pets_type);
int sort_pets(pet *pets, const size_t *petsNumber);

#endif  // INCLUDES_PET_H_
