/**
 * @file recloserConfig.c
 * @author Sean Leana
 * @brief Allows user to interact with recloser configuration
 * @date August 14 2025
 */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

//#include <gpiod.h>

#include "recloserAuth.h"
#include "recloserConfig.h"
#include "../Common/files.h"
#include "../../env/recloserConfig.txt"

#define BUFFER_SIZE 100


/**
 * checks if config file exists
 */
static bool configFileExists() {
    FILE *fileptr;
    fileptr = fopen("../../env/recloserConfig.txt", "r");
    //check if file was found
    if(!fileptr) {
        return false;
    }
    fclose(fileptr);
    return true;
}

// void configPins(Recloser *r) {
//     //todo
// }

// void writeRecloserToFile(Recloser *r) {
//}

/**
 * Reads the current configuration from config file into a Recloser struct
 */
void loadRecloserFromFile(Recloser *r) {
    FILE *recloserFile = fopen("../../env/recloserConfig.txt", "r");
    if(!recloserFile) {
        printf("Error opening recloser file\n");
        fcloser(recloserFile);
        
    }
    //find config setting in config file
    char *line;
    char buff[BUFFER_SIZE];
    int index = 0;
    int offset = 0;
    int value = 0;

    // read from configuration file into recloser struct
    while((line = scanLine(recloserFile))) {
        if(sscanf(line, "%99[^:]%n", buff, &index) == 1) {
            if(strcmp(buff, "recloseAttempts") == 0) {
                offset += index;
                if(sscanf(line + offset, "%d", value, &index) == 1) {
                    offset += index;
                    if(getc(line + offset) != EOF) {
                        printf("Error, invalid recloser configuration file\n");
                    } else {
                        r->recloseAttempts = value;
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
                    if(getc(line + offset) != EOF) {
                        printf("Error, invalid recloser configuration file\n");
                    } else {
                        r->recloseOpenInterval1 = value;
                    }
                }
                else {
                    printf("Error, invalid recloser configuration file\n");
                }
            }
            else if(strcmp(buff, "recloseOpenInterval2") == 0) {
                offset += index;
                if(sscanf(line + offset, "%d", value, &index) == 1) {
                    offset += index;
                    if(getc(line + offset) != EOF) {
                        printf("Error, invalid recloser configuration file\n");
                    } else {
                        r->recloseOpenInterval2 = value;
                    }
                }
                else {
                    printf("Error, invalid recloser configuration file\n");
                }
            }
            else if(strcmp(buff, "recloseOpenInterval3") == 0) {
                offset += index;
                if(sscanf(line + offset, "%d", value, &index) == 1) {
                    offset += index;
                    if(getc(line + offset) != EOF) {
                        printf("Error, invalid recloser configuration file\n");
                    } else {
                        r->recloseOpenInterval3 = value;
                    }
                }
                else {
                    printf("Error, invalid recloser configuration file\n");
                }
            }
            else if(strcmp(buff, "recloseOpenInterval4") == 0) {
                offset += index;
                if(sscanf(line + offset, "%d", value, &index) == 1) {
                    offset += index;
                    if(getc(line + offset) != EOF) {
                        printf("Error, invalid recloser configuration file\n");
                    } else {
                        r->recloseOpenInterval4 = value;
                    }
                }
                else {
                    printf("Error, invalid recloser configuration file\n");
                }
            }
            else if(strcmp(buff, "subscriptions") == 0) {
                offset += index;
                int subCount = 0;
                while(sscanf(line + offset, "%99[^,]%n", buff, &index) == 1) {
                    offset += index;
                    r->subscriptions[subCount] = malloc(sizeof(char) * (strlen(buff) + 1));
                    strcpy(r->subscriptions[subCount], buff);
                    subCount++;
                }
            }
            else {
                printf("Error, invalid recloser configuration file\n");
            }
            offset = 0;
        }
        else {
            printf("Error, invalid recloser configuration file\n");
        }
    }
}



/** 
void updateFile(Recloser *r, int num) {

}
*/

/**
 * Print the existing configuration
 */
static void printExistingConfig(Recloser *r) {
    printf("Existing configuration:\n");
    printf("Reclose attempts: %d\n", r->recloseAttempts);
    printf("Open interval duration: \n");
    printf("First cycle): %d\n", r->recloseOpenInterval1);
    printf("First cycle): %d\n", r->recloseOpenInterval2);
    printf("First cycle): %d\n", r->recloseOpenInterval3);
    printf("First cycle): %d\n", r->recloseOpenInterval4);
    
    for(int i = 0; i < strlen(r->subscriptions[i]); i++) {
        for(int j = 0; j < strlen(r->subscriptions[i][j]); j++) {
            printf("%c", r->subscriptions[i][j]);
            if(j != strlen(r->subscriptions[i][j]) - 1) {
                printf(",");
            }
        }
    }
}

/**
 * load recloser with default settings
 */
void loadRecloserDefault(Recloser *r) {
    r->recloseAttempts = 4;
    r->recloseOpenInterval1 = 1;
    r->recloseOpenInterval2 = 1;
    r->recloseOpenInterval3 = 2;
    r->recloseOpenInterval4 = 4;
}

/**
 * Verify number
 */
static int retrieveNumber(const char *prompt, int min, int max, const char *retry) {
    int num;
    printf("%s", prompt);
    scanf("%d", &num);
    while(num < min || num > max) {
        printf("%s", retry);
        scanf("%d", &num);
    }
    return num;
}

/**
 * FUNCTION NOT FULLY IMPLEMENTED
 * Edits configuration file
 * @returns 1 if configuration was changed
 */
int changeConfiguration(int configNumber, Recloser *r) {
    int num = 0;
    if(configNumber == 1) {
        //updates the config data in the file
        r->recloseAttempts = retrieveNumber("Enter the number of reclosing attempts(1-4): ", 1, 4, "Please try again, enter a valid number of reclosing attempts(1-4): ");
    } else if(configNumber == 2) {
        r->recloseOpenInterval1 = retrieveNumber("Enter recloser interval for reclose attempt one (1-10s): ", 1, 10, "Please try again, enter a valid interval for reclose attempt one (1-10s): ");
    } else if(configNumber == 3) {
        // printf("Enter recloser interval for reclose attempt 2(s): ");
        // if(scanf("%d", &num) == 1) {
        //     while(num < 0 && num > 10) {
        //         printf("Please try again, enter a valid interval for reclose attempt 2 (1-10s): ");
        //         scanf("%d", &num);
        //     }
        r->recloseOpenInterval2 = retrieveNumber("Enter recloser interval for reclose attempt two (1-10s): ", 1, 10, "Please try again, enter a valid interval for reclose attempt two (1-10s): ");
    } else if (configNumber == 4) {
        // printf("Enter recloser interval for reclose attempt 3(s): ");
        // if(scanf("%d", &num) == 1) {
        //     while(num < 0 && num > 10) {
        //         printf("Please try again, enter a valid interval for reclose attempt 3 (1-10s): ");
        //         scanf("%d", &num);
        //     }
         r->recloseOpenInterval3 = retrieveNumber("Enter recloser interval for reclose attempt three (1-10s): ", 1, 10, "Please try again, enter a valid interval for reclose attempt three (1-10s): ");
    } else if (configNumber == 5) {
        r->recloseOpenInterval4 = retrieveNumber("Enter recloser interval for reclose attempt four (1-10s): ", 1, 10, "Please try again, enter a valid interval for reclose attempt four (1-10s): ");
    }
    // } else if (configNumber == 6) {
    // }
    else {
        printf("finish this function\n");
    }

}

/**
 * Checks if file exists, if it does it will pull 
 */
static void config(Recloser *r) {
    //checks if config file exists
    if(configFileExists()) {
        //loads recloser from existing configuration file
        loadRecloserFromFile(r);
    } else {
        //create file
        fopen("../../env/recloserConfig.txt", "w");
        //loads recloser with default settings
        loadRecloserDefault(r);
    }

    printExistingConfig(r);
    //or if they want to continue with existing config
    int input;
    //asks user to enter number of config to change
    while(input != 0) {
        printExistingConfig(r);
        printf("Enter configuration number to change associated configuration or enter 0 to exit: ");
        scanf("%d", &input);

        if(input == 0) {
            printf("Exiting\n");
        } else if(input > 0 && input <= 10) {
            if(changeConfiguration(input, r)) {
                printf("\nConfiguration changed successfully.\n\n");                    
            }
        } else {
            printf("Invalid input\n");
        }
    }
   //configPins();
}