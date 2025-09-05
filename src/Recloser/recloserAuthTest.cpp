#include <gtest/gtest.h>
extern "C" {
#include "recloserAuth.h"
}

#define MAX_PASS_LEN = 16
#define MAX_USER_LEN = 16
#define HASH_LEN = 32
#define SALT_LEN = 16
#define BUFFER_SIZE = 100

TEST(addTest, twoPositive) {
    EXPECT_EQ(add(1, 2), 3);
}


TEST(generateSaltTest, handleSaltArray) {
    uint8_t salt[SALT_LEN];
    enerateSalt(salt);
    for(int i = 0; i < SALT_LEN; i++) {
        EXPECT_NE(salt[i], 0) << "INDEX: " << i << std::cout;
    }
}

TEST(hashPass, returnCorrectSize) {
    char enteredPass[] = {A,B,C};
    uint8_t salt[SALT_LEN] = {};
    salt = generateSalt(salt);
    uint8_t hash[HASH_LEN] = {};
    for(int i = 0; i < SALT_LEN; i++) {
        EXPECT_NE(salt[i], 0) << "INDEX: " << i << std::cout;
    }
    uint8_t *rv = hashPass(enteredPass, salt, hash);
    for(int i = 0; i < HASH_LEN; i++) {
        EXPECT_NE(hash[i], 0) << "INDEX: " << i << "Hash Value: " << hash[i] std::cout;
    }
}