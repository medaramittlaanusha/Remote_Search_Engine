/***************************************************************************
*   DATE :21/10/2024
*   OWNER : Group-04
*	FILENAME : loggers.h
*	DESCRIPTION: This header file defines logging macros for different 
*                log levels, including INFO, WARN, FATAL, and DEBUG. 
*                These macros simplify logging messages throughout 
*                the application by providing a consistent format for 
*                displaying messages with their respective severity levels.
*****************************************************************************/




#ifndef LOGGERS_H
#define LOGGERS_H


// Logging macros for different severity levels

#define LOG_INFO(msg, arg) printf("[INFO] " msg "\n", arg);         // Log informational messages
#define LOG_WARN(msg, arg) printf("[WARN] " msg "\n", arg);        // Log warnings
#define LOG_FATAL(msg, arg) printf("[FATAL] " msg "\n", arg);      // Log fatal errors
#define LOG_DEBUG(msg, arg) printf("[DEBUG] " msg "\n", arg);      // Log debug messages

#endif
