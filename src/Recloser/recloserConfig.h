/**
 * @file recloserConfig.h
 * @author Sean Leana
 * @brief Stores configuration of recloser
 * @date 10/27/25
 */

/**
 * Structure holding the Recloser configuration 
 */
struct recloser {
    
    /** Reclose attempts */
    int recloseAttempts;

    /** The duration the recloser will open for on first cycle (ms) */
    int recloseOpenInterval1;

    /** The duration the recloser will open for on second cycle (ms) */
    int recloseOpenInterval2;

    /** The duration the recloser will open for on third cycle (ms) */
    int recloseOpenInterval3;

    /** The duration the recloser will open for on fourth cycle (ms) */
    int recloseOpenInterval4;

    /** the topics that the recloser subscribes to */
    char *subcriptions[];
}