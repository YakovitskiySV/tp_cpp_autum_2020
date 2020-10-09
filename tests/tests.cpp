#include <gtest/gtest.h>

extern "C" {
#include "pet.h"
}

TEST(wrongParametrs, CreatePet_firstParamNull) {
    Pet *pets = NULL;
    char **params = new char *[3];
    ASSERT_EQ(0, CreatePet(pets, params));
    delete[] params;
}

TEST(wrongParametrs, CreatePet_secondParamNull) {
    Pet *pets = new Pet[1];
    char **params = NULL;
    ASSERT_EQ(0, CreatePet(pets, params));
    delete[] pets;
}

TEST(wrongParametrs, CreatePet_bothNull) {
    Pet *pets = NULL;
    char **params = NULL;
    ASSERT_EQ(0, CreatePet(pets, params));
}

TEST(wrongParametrs, CreatePet_secondParam0Invalid1) {
    Pet *pets = new Pet[1];
    char **params = new char *[3];
    params[0] = NULL;
    params[1] = "cat\0";
    params[2] = "orange\0";
    ASSERT_EQ(0, CreatePet(pets, params));
    delete[] params;
    delete[] pets;
}

TEST(wrongParametrs, CreatePet_secondParam1Invalid2) {
    Pet *pets = new Pet[1];
    char **params = new char *[3];
    params[0] = "deniska\0";
    params[1] = NULL;
    params[2] = "orange\0";
    ASSERT_EQ(0, CreatePet(pets, params));
    delete[] params;
    delete[] pets;
}

TEST(wrongParametrs, CreatePet_secondParam2Invalid) {
    Pet *pets = new Pet[1];
    char **params = new char *[3];
    params[0] = "deniska\0";
    params[1] = "cat\0";
    params[2] = NULL;
    ASSERT_EQ(0, CreatePet(pets, params));
    delete[] params;
    delete[] pets;
}

TEST(wrongParametrs, SortPets_firstParamNULL) {
    Pet *pets = NULL;
    size_t petsNumber = 1;
    ASSERT_EQ(0, SortPets(pets, petsNumber));
}

TEST(wrongParametrs, SortPets_petsNameNULL) {
    Pet *pets = new Pet[1];
    pets[0].name = NULL;
    pets[0].type = "cat\0";
    pets[0].color = "orange\0";
    size_t petsNumber = 1;
    ASSERT_EQ(0, SortPets(pets, petsNumber));
    delete[] pets;
}

TEST(wrongParametrs, SortPets_petsTypeNULL) {
    Pet *pets = new Pet[1];
    pets[0].name = "deniska\0";
    pets[0].type = NULL;
    pets[0].color = "orange\0";
    size_t petsNumber = 1;
    ASSERT_EQ(0, SortPets(pets, petsNumber));
    delete[] pets;
}

TEST(wrongParametrs, SortPets_petsColorNULL) {
    Pet *pets = new Pet[1];
    pets[0].name = "deniska\0";
    pets[0].type = "cat\0";
    pets[0].color = NULL;
    size_t petsNumber = 1;
    ASSERT_EQ(0, SortPets(pets, petsNumber));
    delete[] pets;
}

TEST(wrongParametrs, PrintPet_petsNULL) {
    Pet *pets = NULL;
    size_t petsNumber = 1;
    ASSERT_EQ(0, PrintPet(pets));
}

TEST(wrongParametrs, PrintPet_petsNameNULL) {
    Pet *pets = new Pet[1];
    pets[0].name = NULL;
    pets[0].type = "cat\0";
    pets[0].color = "orange\0";
    size_t petsNumber = 1;
    ASSERT_EQ(0, PrintPet(pets));
    delete[] pets;
}

TEST(wrongParametrs, PrintPet_petsTypeNULL) {
    Pet *pets = new Pet[1];
    pets[0].name = "densiska\0";
    pets[0].type = NULL;
    pets[0].color = "orange\0";
    size_t petsNumber = 1;
    ASSERT_EQ(0, PrintPet(pets));
    delete[] pets;
}

TEST(wrongParametrs, PrintPet_petsColorNULL) {
    Pet *pets = new Pet[1];
    pets[0].name = "deniska\0";
    pets[0].type = "cat\0";
    pets[0].color = NULL;
    size_t petsNumber = 1;
    ASSERT_EQ(0, PrintPet(pets));
    delete[] pets;
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}