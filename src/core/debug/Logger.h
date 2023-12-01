//
// Created by Damon Tregear on 11/19/23.
//

#ifndef UMBRAENGINE_LOGGER_H
#define UMBRAENGINE_LOGGER_H

#include <cstdint>
#include <iostream>
#include <string>

namespace UmbraEngine::Core::Debug {

class Logger {
public:
/******************************
 * @section Enums
 *****************************/
    enum LogLevel : uint8_t {
        kTRACE = 0x00,
        kDEBUG = 0x01,
        kINFO = 0x02,
        kWARNING = 0x03,
        kALERT = 0x04,
        kERROR = 0x05,
        kFATAL = 0x06,
        kINVALID = 0X07
    };

    enum ConfigLevel : uint8_t {
        kCFG_NONE = 0x00,
        kCFG_MINIMAL = 0x01,
        kCFG_PRODUCTION = 0x02,
        kCFG_DEBUG = 0x03,
        kCFG_FULL = 0x04
    };

    enum LogColor {
        kCOLOR_TRACE,
        kCOLOR_DEBUG,
        kCOLOR_INFO,
        kCOLOR_WARNING,
        kCOLOR_ALERT,
        kCOLOR_ERROR,
        kCOLOR_FATAL,
        kCOLOR_INVALID
    };

/******************************
 * @section Properties
 * @subsection Public properties
 *****************************/


/******************************
 * @section Constructors
 *****************************/
    Logger() = default;

/******************************
 * @section Methods
 * @subsection Public methods
 *****************************/
    void SetMaxLogLevel();
    void SetMaxLogLevel(const LogLevel& level);
    void SetConfigLevel(const ConfigLevel& cfgLevel);

protected:
/******************************
 * @section Methods
 * @subsection Protected methods
 *****************************/


private:
/******************************
 * @section Properties
 * @subsection Private properties
 *****************************/
    static bool enableColors;

    static LogLevel logLevel;
    static LogLevel maxLogLevel;
    static ConfigLevel configLevel;


/******************************
 * @section Methods
 * @subsection Private methods
 *****************************/
};
}

#endif //UMBRAENGINE_LOGGER_H
