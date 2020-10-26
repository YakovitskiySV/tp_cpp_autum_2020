#include <stdio.h>
#include <string.h>
#include "pet.h" // NOLINT

#define STD_BUF_STRING_SIZE 64

int main() {
    size_t pets_number = 0;
    if (!scanf("%zu", &pets_number)) {
        perror("scanf() error");
        return 1;
    }
    pet *pets = NULL;
    pets = allocate_pets(&pets_number);
    if (!pets) {
        perror("allocation error");
        return 1;
    }
    for (size_t i = 0; i < pets_number; ++i) {
        char expected_name[STD_BUF_STRING_SIZE] = "";
        char expected_type[STD_BUF_STRING_SIZE] = "";
        char expected_color[STD_BUF_STRING_SIZE] = "";
        if (!scanf("%s %s %s", expected_name, expected_type, expected_color)) {
            perror("scanf() error");
            return 1;
        }
        if (create_pet(&pets[i],
                       expected_name,
                       expected_type,
                       expected_color) != 0) {
            if (free_pets(pets, &pets_number)) {
                perror("pointer error");
                return 1;
            }
            perror("allocation error");
            return 1;
        }
    }
    char requested_pets_type[STD_BUF_STRING_SIZE] = "";
    if (!scanf("%s", requested_pets_type)) {
        perror("scanf() error");
        return 1;
    }
    print_pets_by_type(pets, &pets_number, requested_pets_type);
    free_pets(pets, &pets_number);
    return 0;
}
