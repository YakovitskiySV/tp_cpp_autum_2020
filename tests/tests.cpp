#include <gtest/gtest.h>
#include <pthread.h>
#include <string>
#include <fcntl.h>

extern "C" {
#include "pet.h"
}

char *AllocateString(const char *src);
int DeletePet(Pet *pet);

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
    char *params[3];
    params[0] = NULL;
    params[1] = AllocateString("cat");
    params[2] = AllocateString("orange");
    ASSERT_EQ(0, CreatePet(pets, params));
    delete[] params[1];
    delete[] params[2];
    delete[] pets;
}

TEST(wrongParametrs, CreatePet_secondParam1Invalid2) {
    Pet *pets = new Pet[1];
    char **params = new char *[3];
    params[0] = AllocateString("deniska");
    params[1] = NULL;
    params[2] = AllocateString("orange");
    ASSERT_EQ(0, CreatePet(pets, params));
    delete[] params[0];
    delete[] params[2];
    delete[] params;
    delete[] pets;
}

TEST(wrongParametrs, CreatePet_secondParam2Invalid) {
    Pet *pets = new Pet[1];
    char **params = new char *[3];
    params[0] = AllocateString("deniska");
    params[1] = AllocateString("cat");
    params[2] = NULL;
    ASSERT_EQ(0, CreatePet(pets, params));
    delete[] params[0];
    delete[] params[1];
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
    pets->name = NULL;
    pets->type = AllocateString("cat");
    pets->color = AllocateString("orange");
    size_t petsNumber = 1;
    ASSERT_EQ(0, SortPets(pets, petsNumber));
    DeletePet(pets);
    delete[] pets;
}

TEST(wrongParametrs, SortPets_petsTypeNULL) {
    Pet *pets = new Pet[1];
    pets[0].name = AllocateString("deniska");
    pets[0].type = NULL;
    pets[0].color = AllocateString("orange");
    size_t petsNumber = 1;
    ASSERT_EQ(0, SortPets(pets, petsNumber));
    DeletePet(pets);
    delete[] pets;
}

TEST(wrongParametrs, SortPets_petsColorNULL) {
    Pet *pets = new Pet[1];
    pets[0].name = AllocateString("deninska");
    pets[0].type = AllocateString("cat");
    pets[0].color = NULL;
    size_t petsNumber = 1;
    ASSERT_EQ(0, SortPets(pets, petsNumber));
    DeletePet(pets);
    delete[] pets;
}

TEST(wrongParametrs, PrintPet_petsNULL) {
    Pet *pets = NULL;
    ASSERT_EQ(0, PrintPet(pets));
}

TEST(wrongParametrs, PrintPet_petsNameNULL) {
    Pet *pets = new Pet[1];
    pets[0].name = NULL;
    pets[0].type = AllocateString("cat");
    pets[0].color = AllocateString("orange");
    ASSERT_EQ(0, PrintPet(pets));
    DeletePet(pets);
    delete[] pets;
}

TEST(wrongParametrs, PrintPet_petsTypeNULL) {
    Pet *pets = new Pet[1];
    pets[0].name = AllocateString("deniska");
    pets[0].type = NULL;
    pets[0].color = AllocateString("orange");
    ASSERT_EQ(0, PrintPet(pets));
    DeletePet(pets);
    delete[] pets;
}

TEST(wrongParametrs, PrintPet_petsColorNULL) {
    Pet *pets = new Pet[1];
    pets[0].name = AllocateString("deniska");
    pets[0].type = AllocateString("cat");
    pets[0].color = NULL;
    ASSERT_EQ(0, PrintPet(pets));
    DeletePet(pets);
    delete[] pets;
}

TEST(correctParametrs, CreatePet) {
    Pet newPet;
    Pet expectedPet;
    char **params = new char*[3];
    params[0] = AllocateString("deniska");
    params[1] = AllocateString("cat");
    params[2] = AllocateString("orange");
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
    char *params[5][3];
    params[0][0] = AllocateString("deniska");
    params[0][1] = AllocateString("cat");
    params[0][2] = AllocateString("orange");
    params[1][0] = AllocateString("andruha");
    params[1][1] = AllocateString("dog");
    params[1][2] = AllocateString("brown");
    params[2][0] = AllocateString("marvin");
    params[2][1] = AllocateString("zebruh");
    params[2][2] = AllocateString("black and white");
    params[3][0] = AllocateString("vasiok");
    params[3][1] = AllocateString("cat");
    params[3][2] = AllocateString("yellow");
    params[4][0] = AllocateString("bukva");
    params[4][1] = AllocateString("a");
    params[4][2] = AllocateString("pervaya");
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
    params[0] = AllocateString("deniska");
    params[1] = AllocateString("cat");
    params[2] = AllocateString("orange");
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
    char fileString[40];
    fgets(fileString, 40, testFile);
    fclose(testFile);
    system("rm -rf PrintPetTest.txt");
    char *expectedString = AllocateString("name: deniska, type: cat, color: orange");
    EXPECT_EQ(strcmp(expectedString, fileString),0);
    DeletePet(pet);
    delete[] pet;
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

char *AllocateString(const char *src) {
    char *param = new char[strlen(src) + 1];
    strncpy(param, src, strlen(src) + 1);
    return param;
}

int DeletePet(Pet *pet) {
    delete[] pet->name;
    delete[] pet->color;
    delete[] pet->type;
    return 1;
}