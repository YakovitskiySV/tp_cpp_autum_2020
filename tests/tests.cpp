#include <gtest/gtest.h>

extern "C" {
#include "pet.h"
}

TEST(wrong_paramerts, CreatePet_nullptr) {
    Pet *newPet = NULL;
    char **params = NULL;
    EXPECT_EQ(0, CreatePet(newPet, params));
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}