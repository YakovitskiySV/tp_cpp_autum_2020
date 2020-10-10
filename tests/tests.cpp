#include <gtest/gtest.h>
#include <string>
#include <fcntl.h>

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

TEST(correctParametrs, CreatePet) {
    Pet newPet;
    Pet expectedPet;
    char **params = new char*[3];
    params[0] = "densiska\0";
    params[1] = "cat\0";
    params[2] = "orange\0";
    expectedPet.name = params[0];
    expectedPet.type = params[1];
    expectedPet.color = params[2];
    CreatePet(&newPet, params);
    EXPECT_EQ(strcmp(newPet.name, expectedPet.name), 0);
    EXPECT_EQ(strcmp(newPet.type, expectedPet.type), 0);
    EXPECT_EQ(strcmp(newPet.color, expectedPet.color), 0);
    DeletePet(&newPet);
    delete[] params;
}

TEST(correctParametrs, SortPets) {
    size_t petsNumber = 5;
    Pet* pets = new Pet[petsNumber];
    Pet* sortedPets = new Pet[petsNumber];
    char *params[petsNumber][3];
    params[0][0] = "densika\0";
    params[0][1] = "cat\0";
    params[0][2] = "orange\0";
    params[1][0] = "andruha\0";
    params[1][1] = "dog\0";
    params[1][2] = "brown\0";
    params[2][0] = "marvin\0";
    params[2][1] = "zebruh\0";
    params[2][2] = "black and white\0";
    params[3][0] = "vasiok\0";
    params[3][1] = "cat\0";
    params[3][2] = "yellow\0";
    params[4][0] = "bukva\0";
    params[4][1] = "a\0";
    params[4][2] = "pervaya\0";
    CreatePet(&sortedPets[0], params[4]);
    CreatePet(&sortedPets[1], params[0]);
    CreatePet(&sortedPets[2], params[3]);
    CreatePet(&sortedPets[3], params[1]);
    CreatePet(&sortedPets[4], params[2]);
    for (size_t i = 0 ; i < petsNumber ; i++) {
        CreatePet(&pets[i], params[i]);
    }
    SortPets(pets, petsNumber);
    for (size_t i = 0 ; i < petsNumber ; i++) {
        EXPECT_EQ(strcmp(sortedPets[i].name, pets[i].name), 0);
        EXPECT_EQ(strcmp(sortedPets[i].type, pets[i].type), 0);
        EXPECT_EQ(strcmp(sortedPets[i].color, pets[i].color), 0);
    }
    for (size_t i = 0 ; i < petsNumber ; i++) {
        DeletePet(&pets[i]);
        DeletePet(&sortedPets[i]);
    }
    delete[] pets;
    delete[] sortedPets;
}

TEST(correctParametrs, PrintPet) {
    char *params[3];
    Pet *pet = new Pet[1];
    params[0] = "deniska\0";
    params[1] = "cat\0";
    params[2] = "orange\0";
    CreatePet(pet, params);
    int fd = open("PrintPetTest.txt",
                  O_CREAT
                  | O_WRONLY
                  | O_APPEND
                  | O_TRUNC,
                  0777);
    ASSERT_NE(fd, 0);
    int stdoutDesc = dup(1);
    close(1);
    dup(fd);
    close(fd);
    PrintPet(pet);
    fflush(stdout);
    dup2(stdoutDesc, 1);
    close(stdoutDesc);
    FILE *testFile = fopen("PrintPetTest.txt", "r");
    ASSERT_NE(testFile, nullptr);
    char fileString[40];
    fgets(fileString, 40, testFile);
    fclose(testFile);
    system("rm -rf PrintPetTest.txt");
    char *expectedString = "name: deniska, type: cat, color: orange";
    EXPECT_EQ(strcmp(expectedString, fileString),0);
    DeletePet(pet);
    delete[] pet;
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}