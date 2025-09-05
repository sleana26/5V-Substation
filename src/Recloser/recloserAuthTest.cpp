#include <gtest/gtest.h>
extern "C" {
#include "recloserAuth.h"
}

#define MAX_PASS_LEN = 16
#define MAX_USER_LEN = 16
#define HASH_LEN = 32
#define SALT_LEN = 16
#define BUFFER_SIZE = 100

TEST(generateSaltTest, handleSaltArray) {
    uint8_t salt[SALT_LEN];
    uint8_t *rv = generateSalt(salt);
    for(int i = 0; i < SALT_LEN; i++) {
        ASSERT_EQ(salt[i], rv[i]);
    }
}