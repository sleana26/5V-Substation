/**
 * @file recloserConfig.h
 * @author Sean Leana
 * @brief Allows user to change configuration files for the recloser.
 * Can add reclosers to subscribe to, change reclose interval, reclose 
 * attempts, etc.
 * @date August 14 2025
 */

#include <gpiod.h>

#ifndef CONFIG_H
#define CONFIG_H

/** 
 * Reads the configuration of the existing configuration file stored locally.
 * Prints the existing configuration to the user and prompts them to either
 * change settings or to continue with existing settings
 */
void config();

/**
 * Edits the configuration file configuration file
 * @returns 1 if configuration was changed
 */
int changeConfiguration(int configNumber);


#endif


