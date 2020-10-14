#include <cstdio>  // NOLINT
#include <fcntl.h>  // NOLINT
#include <gtest/gtest.h>  // NOLINT
#include <string>  // NOLINT
#define STD_STRING_SIZE 64
extern "C" {
#include "pet.h" // NOLINT
}

TEST(wrongParametrs, allocate_pet) {
    size_t *pets_number = nullptr;
    EXPECT_EQ(NULL, allocate_pets(pets_number));
}

TEST(wrongParametrs, set_pets_namePetNull) {
    pet *single_pet = nullptr;
    std::string name = "name";
    EXPECT_EQ(1, set_pets_name(single_pet, (char *)name.c_str()));
}

TEST(wrongParametrs, set_pet_nameNameNull) {
    pet single_pet[1];
    char *name = nullptr;
    EXPECT_EQ(1, set_pets_name(single_pet, name));
}

TEST(wrongParametrs, set_pets_typePetNull) {
    pet *single_pet = nullptr;
    std::string type = "type";
    EXPECT_EQ(1, set_pets_type(single_pet, (char *)type.c_str()));
}

TEST(wrongParametrs, set_pets_typeTypeNull) {
    pet single_pet[1];
    char *type = nullptr;
    EXPECT_EQ(1, set_pets_name(single_pet, type));
}

TEST(wrongParametrs, set_pets_colorPetNull) {
    pet *single_pet = nullptr;
    std::string color = "color";
    EXPECT_EQ(1, set_pets_name(single_pet, (char *)color.c_str()));
}

TEST(wrongParametrs, set_pets_colorColorNull) {
    pet single_pet[1];
    char *color = nullptr;
    EXPECT_EQ(1, set_pets_name(single_pet, color));
}

TEST(wrongParametrs, create_pet_firstParamNull) {
    pet *new_pet = nullptr;
    std::string expected_name = "name";
    std::string expected_type = "type";
    std::string expected_color = "color";
    EXPECT_EQ(1, create_pet(new_pet, (char *)expected_name.c_str(),
                            (char *)expected_type.c_str(),
                            (char *)expected_color.c_str()));
}

TEST(wrongParametrs, create_pet_nameNull) {
    pet single_pet;
    char *expected_name = nullptr;
    std::string expected_type = "type";
    std::string expected_color = "color";
    EXPECT_EQ(1, create_pet(&single_pet, expected_name,
                            (char *)expected_type.c_str(),
                            (char *)expected_color.c_str()));
}

TEST(wrongParametrs, create_pet_typeNull) {
    pet single_pet;
    char *expected_type = nullptr;
    std::string expected_name = "name";
    std::string expected_color = "color";
    EXPECT_EQ(1, create_pet(&single_pet, (char *)expected_name.c_str(),
                            expected_type, (char *)expected_color.c_str()));
}

TEST(wrongParametrs, create_pet_colorNull) {
    pet single_pet;
    char *expected_color = nullptr;
    std::string expected_name = "name";
    std::string expected_type = "type";
    EXPECT_EQ(1, create_pet(&single_pet, (char *)expected_name.c_str(),
                            (char *)expected_type.c_str(), expected_color));
}

TEST(wrongParametrs, print_pet_petsNULL) {
    pet *pets = nullptr;
    EXPECT_EQ(0, print_pet(pets));
}

TEST(wrongParametrs, print_pet_petsNameNULL) {
    pet single_pet;
    single_pet.name = nullptr;
    single_pet.type = new char[STD_STRING_SIZE];
    single_pet.color = new char[STD_STRING_SIZE];
    EXPECT_EQ(0, print_pet(&single_pet));
    delete[] single_pet.type;
    delete[] single_pet.color;
}

TEST(wrongParametrs, print_pet_petsTypeNULL) {
    pet single_pet;
    single_pet.name = new char[STD_STRING_SIZE];
    single_pet.type = nullptr;
    single_pet.color = new char[STD_STRING_SIZE];
    EXPECT_EQ(0, print_pet(&single_pet));
    delete[] single_pet.name;
    delete[] single_pet.color;
}

TEST(wrongParametrs, print_pet_petsColorNULL) {
    pet single_pet;
    single_pet.name = new char[STD_STRING_SIZE];
    single_pet.type = new char[STD_STRING_SIZE];
    single_pet.color = nullptr;
    EXPECT_EQ(0, print_pet(&single_pet));
    delete[] single_pet.name;
    delete[] single_pet.type;
}

TEST(wrongParametrs, free_petsPetsNull) {
    pet* pets = nullptr;
    size_t pets_number = 2;
    EXPECT_EQ(1, free_pets(pets, &pets_number));
}

TEST(wrongParametrs, free_petsPetsNumberIsZero) {
    pet pets[2];
    size_t pets_number = 0;
    EXPECT_EQ(1, free_pets(pets, &pets_number));
}

TEST(correctParametrs, create_pet) {
    pet newPet;
    pet expectedPet;
    std::string expected_name = "name";
    std::string expected_type = "type";
    std::string expected_color = "color";
    expectedPet.name = (char *)expected_name.c_str();
    expectedPet.type = (char *)expected_type.c_str();
    expectedPet.color = (char *)expected_color.c_str();
    create_pet(&newPet, (char *)expected_name.c_str(),
               (char *)expected_type.c_str(), (char *)expected_color.c_str());
    EXPECT_EQ(strcmp(newPet.name, expectedPet.name), 0);
    EXPECT_EQ(strcmp(newPet.type, expectedPet.type), 0);
    EXPECT_EQ(strcmp(newPet.color, expectedPet.color), 0);
    free_pet(&newPet);
}


TEST(correctParametrs, print_pet) {
    pet single_pet;
    std::string expected_name = "deniska";
    std::string expected_type = "cat";
    std::string expected_color = "orange";
    create_pet(&single_pet, (char *)expected_name.c_str(),
               (char *)expected_type.c_str(), (char *)expected_color.c_str());
    std::string expected_string = "name: deniska, type: cat, color: orange";
    char file_string[STD_STRING_SIZE];
    setbuf(stdout, file_string);
    putchar('\n');
    print_pet(&single_pet);
    setbuf(stdout, NULL);
    putchar('\n');
    file_string[expected_string.length()] = '\0';
    EXPECT_EQ(expected_string, file_string);
    free_pet(&single_pet);
}

TEST(correctParams, print_pets_by_type) {
    size_t pets_number = 3;
    pet pets[3];
    std::string cats_name = "cats_name";
    std::string type = "cat";
    std::string cats_color = "cats_color";
    for (size_t i = 0 ; i < 2 ; ++i) {
        create_pet(&pets[i], (char*)cats_name.c_str(),
                   (char*) type.c_str(),
                   (char*) cats_color.c_str());
    }
    type = "dog";
    create_pet(&pets[2], (char*)cats_name.c_str(),
              (char*) type.c_str(),
              (char*) cats_color.c_str());
    char file_string[STD_STRING_SIZE];
    std::string requested_pet_type = "dog";
    setbuf(stdout, file_string);
    putchar('\n');
    print_pets_by_type(pets, &pets_number, (char*) requested_pet_type.c_str());
    setbuf(stdout, NULL);
    std::string expected_string = "name: cats_name, type: dog, color: cats_color\n";
    EXPECT_EQ(expected_string, file_string);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
