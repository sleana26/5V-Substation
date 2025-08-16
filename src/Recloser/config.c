/**
 * @file recloserConfig.c
 * @author Sean Leana
 * @brief Allows user to interact with configuration
 */

#include "authentication.h"
#include <stdio.h>

/**
 * Reads the current configuration from config file into a Recloser struct???? idk maybe
 */
readConfigurationFromFile() {
    
}

/**
 * Prompts user to change configuration options
 * @returns 1 if configuration was changed
 */
static int changeConfiguration(int configNumber) {

}

/**
 * Print the existing configuration
 */
static void printConfig() {
    //prints configuration with numbers next to each config



}

// returns 1 when config is complete
void config() {
    // reads configuration from file
    //TODO

    // prints config 
    //or if they want to continue with existing config
    char input = '\0';
    //asks user to enter number of config to change
    while(input != 1) {
        printConfig();
        printf("Enter configuration number to change associated configuration 
                or enter 1 to exit: ");
        char input = getchar();
        
        if(input == '1') {
            return;
        } else if(input > 0 && input <= 10) {
            if(changeConfiguration(_)) {
                printf("\n");
                printf("Configuration changed successfully.\n");
                printf("\n");                    
            }
        } else {
            printf("Invalid input\n");
        }
    }
}