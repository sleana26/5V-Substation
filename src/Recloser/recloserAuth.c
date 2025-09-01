/**
 * @file recloserAuth.c
 * @brief handles local Recloser authentication once logged in the user can access configuration.
 * @author Sean Leana
 * @date 8/14/25
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <openssl/rand.h>
#include <inttypes.h>

//hash library
#include "argon2.h"
#include "../Common/files.h"

#define MAX_PASS_LEN = 16
#define MAX_USER_LEN = 16
#define HASH_LEN = 32
#define SALT_LEN = 16
#define BUFFER_SIZE = 100

/**
 * Generates random salt for hash, prints error if there is an error
 */
static uint8_t *generateSalt(uint8_t *salt) {

    memset(salt, 0x00, SALT_LEN);

    if(RAND_bytes(salt, saltLength)) {
        return salt;
    } else {
        printf(stderr, "Error generating random salt.");
        exit(EXIT_FAILURE);
    }
}

/**
* hashes the password
*/
static uint8_t *hashPass(char *enteredPass, uint8_t *salt, uint8_t *hash) {

    //duplicates password entered by user
    uint8_t *enteredPassDup = (uint8_t *)strdup(enteredPass);

    //gets length of paaword
    uint32_t enteredPassLen = strlen((char *)enteredPassDup);

    //two passes
    uint32_t t_cost = 2;
    uint32_t m_cost = (1 << 16);

    //number of threads
    uint32_t parallelism = 1;

    //hash
    argon2i_hash_raw(t_cost, m_cost, parallelism, enteredPassDup, enteredPassLen, saltPtr, SALT_LEN, hash, HASH_LEN);

    return hash;
}

/**
* compares username from login to file. if theres a match for username then password gets checkdreturns 1 if they are equal
* @
*/
static bool compareCredentials(char *passAttempt, char *user) {
    FILE *passfile = openPasswordFile('../../files/passwords.txt', 'r');
    
    //find user in pass file
    char *line;
    char buff[BUFFER_SIZE];
    int index = 0;
    // read users from password file until EOF or user match is found
    while(line = scanLine(passfile)) {
        if(sscanf(line, "%99[^:]%n", buff, &index) == 1) {
            if(strcmp(buff, user) == 0) {
                offset++;
                break;
            }
        }
    }
    // if line returned is NULL the user was not found
    if(line == NULL) {
        return false;
    }
    //get salt from password file
    uint_t salt[SALT_LEN];
    int i = 0;
    while(line[index] != ':') {
        if(line[index] == '\n' || line[index] == EOF || i > SALT_LEN) {
            printf("password file error1");
        }
        salt[i] = (uint_t *)line[index];
        index++;
        i++;
    }
    index++;

    //hash the password entered by user
    size_t hashAttempt[HASH_LEN];
    hashPass(passAttempt, salt, hashAttempt);
    int j = 0;

    //compare hash from entered password to stored hash
    while(line[j] != '\0' && line[j] != EOF ) {
        if(hashAttempt[j] != (uint_t *)line[index]) {
            printf("hashes dont match\n");
            fclose(passfile);
            return false;
        }
        index++;
        j++;
    }
    if(j == HASH_LEN - 1) {
        fclose(passfile);
        return true;
    } else {
        fclose(passfile);
        return false;
    }
}

/**
* Stores the authentication info in password file and returns 1 if successful
*/
static int storeAuth(char * username, uint8_t *salt, uint8_t *hash) {
    //open password file in write mode
    FILE *passfile = openPasswordFile('w');

    fprintf(passfile, "%u", )

    fclose(passfile);
}

/**
 * Checks if a password has been set for the admin account, if not the user will be prompted to set a password.
 * If a password has been set, the user will be prompted to enter the password to login.
 * @returns 1 if user was successfully signed in
 */
int login() {
    // I think I need to check if user and pass file exists, if not creates one, and then I can go through a setup process where
    // user sets pass for admin if the file didnt exist "first startup, set password for admin: ", otherwise user is prompted for
    // username "enter username(default is admin)" and then password "enter pass":
    if(passFileExists()) {
        //prompts user and checks if hash matches
        if(loginAttempt()) {
            loggedIn = 1;
            return 1;
        } else {
            printf("Error logging in\n");
            return 0;
        }
    } else {
        if(passwordSet()) {
            loggedIn = 1;
            return 1;
        } else {
            printf("Error setting password\n");
            return 0;
        }
    }
}

/**
 * Logs user out of session
 */
void logOut() {
    loggedIn = 0;
}

/**
 * Checks if a password exists
 * @returns 1 if password exists, 0 if no password
 */
static bool passFileExists() {
     //open password file to see if admin account already has a password set
     //Maybe setjmp longjmp to catch errors, or handle an error from openFile someother way
    FILE *passfile = fopen('../../files/passwords.txt');
    if(!passfile) {
        return false;
    } else {
         return true;
    }
}

/**
 *
 * 
 */
static int loginAttempt(char *username) {
    int i = 0;
    char username[MAX_USER_LEN] = {};
    printf(stdout, "Enter username(default: 'admin'): ");
    while((ch = getchar()) != NULL) && ch != EOF) {
        if((ch > 0 && ch <  33) || (ch > 57 && ch < 65) || (ch > 90 && ch < 97) || (ch > 122)) {
            printf("No special characters allowed, please try again: ");
        } else if (i >= MAX_USER_LEN){
            
        }
        else {
            username[i++] = ch;
        }
        
    }
    //stores entered pass
    char passAttempt[BUFFER_SIZE] = {};
    int passwordMatched = 0;
    int attemptCount = 0;
    printf(stdout, "Password: ");

    while(!passwordMatched) {
        while((ch = getchar()) != NULL) && ch != EOF) {
            username[i++] = ch;
        }
        attemptCount++;
        if(comparePass(passAttempt, user)) {
            printf("Welcome.\n");
            return 1;
        }
        else if(attemptCount == 3) {
            printf("Three attempts failed, please wait 30s before trying again.\n");
            time.sleep(10);
        }
    }
}

       // uint8_t salt[SALT_LEN];
       // for another function
       // generateSalt(salt);
       // hashedPassAttempt = hashPass(passAttempt, salt, hash);

/**
 * User sets the password
 * @returns 1 if password is set
 */
static bool passwordSet() {
    char username[MAX_USER_LEN + 1] = {};
    char passSet[MAX_PASS_LEN + 1] = {};
    printf(stdout, "Initial startup.\n");
    printf(stdout, "Set a password between 8 and 16 characters long for 'admin': ");
    int j = 0;
    ch = getchar();
    int passwordAccepted = 0;
    while(!passwordAccepted) {
        while(ch != EOF && ch != '\0') {
            passSet[j] = ch;
            ch = getchar();
            j++;
        }
        passSet[j + 1] = '\0';
        if(j < 9 || j > 17) {
            printf(stdout, "Password must be between 8 and 16 characters long. Try again: ");
            ch = getchar();
            j = 0;
        } else {
            passwordAccepted = 1;
            uint8_t salt[SALT_LEN];
            salt = generateSalt(salt);
            uint8_t hash[HASH_LEN];
            hash = hashpass(passSet, salt, hash);
            if(storeAuth(username, salt, hash)) {
                return true;
            }
        }
    }
}