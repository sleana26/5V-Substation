/**
 * @file recloserConfig.c
 * @author Sean Leana
 * @brief Allows user to interact with recloser configuration
 * @date August 14 2025
 */

#include <stdio.h>
#include <stdbool.h>

//#include <gpiod.h>

#include "recloserAuth.h"
#include "../Common/files.h"
#include "../../env/recloserConfig.txt"

/**
 * checks if config file exists
 */
static bool configFileExists() {
    FILE * fileptr;
    fileptr = fopen("../../env/recloserConfig.txt", "r");
    //check if file was found
    if(!fileptr) {
        fclose("../../env/recloserConfig.txt");
        return false;
    } else {
        fclose("../../env/recloserConfig.txt");
        return true;
    }
    
}

/**
 * Reads the current configuration from config file into a Recloser struct
 */
loadRecloserFromFile() {
    FILE *recloserFile = fopen("../../env/recloserConfig.txt", "r");
    //find config setting in config file
    char *line;
    char buff[BUFFER_SIZE];
    int index = 0;
    int offset = 0;
    int value = 0;

    // read from configuration file into recloser struct
    while(line = scanLine(recloserFile)) {
        if(sscanf(line, "%99[^:]%n", buff, &index) == 1) {
            if(strcmp(buff, "recloseAttempts") == 0) {
                offset += index;
                if(sscanf(line + offset, "%d", value, &index) == 1) {
                    offset += index;
                    if(getc(line + offset) != EOF) {
                        printf("Error, invalid recloser configuration file\n");
                    } else {
                        recloser.
                    }
                }
                else {
                    printf("Error, invalid recloser configuration file\n");
                }
            }
            else if(strcmp(buff, "recloseOpenInterval1") == 0) {
                offset += index;
                if(sscanf(line + offset, "%d", value, &index) == 1) {
                    offset += index;
                    if(getc(line))
                }
                else {

                }
            }
        }
        offset = 0;
    }
}


/**
 * Edits configuration file
 * @returns 1 if configuration was changed
 */
int changeConfiguration(int configNumber, struct) {
    if(configNumber == 1) {
        pritnf("Enter the number of reclosing attempts(1-4): ");
        int num = 0;
        scanf(&num, "%d");
        while(num < 1 && num > 4) {
            printf("Please try again, enter the number of reclosing attempts(1-4): ");
            scanf(&num, "%d");
        }
        //updates the config data in the file
        updateFile()
        //we need a struct because its faster for the while loop
        
    } 
}

/**
 * Print the existing configuration
 */
static void printConfig() {
    //prints configuration with numbers next to each config

}

// returns 1 when config is complete
/**
 * Checks if file exists, if it does it will pull 
 */
void config(struct) {
    //checks if config file exists
    if(configFileExists()) {
        loadRecloserFromFile();
    } else {
        loadRecloserDefault();
    }
    configPins();

    // prints config 
    //or if they want to continue with existing config
    char input;
    //asks user to enter number of config to change
    while(true) {
        printConfig();
        printf("Enter configuration number to change associated configuration or enter 0 to exit: ");
        char input = getchar();

        if(input == '0') {
            break;
        } else if(input > 0 && input <= 10) {
            if(changeConfiguration(_)) {
                printf("\nConfiguration changed successfully.\n\n");                    
            }
        } else {
            printf("Invalid input\n");
        }
    }
    configPins();
}

/**
 * load recloser with default settings
 */
loadRecloserDefault(struct) {

}