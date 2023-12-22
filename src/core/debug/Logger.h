//
// Created by Damon Tregear on 11/19/23.
//

#ifndef UMBRAENGINE_LOGGER_H
#define UMBRAENGINE_LOGGER_H

#include <atomic>
#include <chrono>
#include <cstdint>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <thread>

#include "../../data-structures/MpscQueue.h"

namespace UmbraEngine::Core::Debug {

/**
 * @class Logger
 * @brief A logger class for logging messages to a file and/or console.
 *
 * @details This class is a logger class for logging messages to a file and/or console. It is designed to be
 * asynchronous, lock-free, and thread-safe. Each instantiation of the logger class will start a new thread to log to
 * the given file until the logger destructor is called.
 */
class Logger {
public:
/******************************
 * @section Enums
 *****************************/
    /**
     * @enum LogLevel
     * @brief An enumeration of possible log levels.
     *
     * @details This enumeration provides a list of possible log levels. It is used by the logger to determine what
     * level of logs to output. The logger will only output levels that are greater than or equal to the log level
     * (e.g., if the log level is set to kWarn, then the logger will output kWarn, kAlert, kError, and kFatal).
     */
    enum LogLevel : uint8_t {
        kFatal = 0x00,
        kError = 0x01,
        kAlert = 0x02,
        kWarn = 0x03,
        kInfo = 0x04,
        kDebug = 0x05,
        kTrace = 0x06,
        kInvalid = 0X07
    };

    /**
     * @enum PrefixLevel
     * @brief An enumeration of possible prefix levels.
     *
     * @details This enumeration provides a list of possible prefix levels. It is used by the logger to determine what
     * level of prefixes to output.
     */
    enum PrefixLevel : uint8_t {
        kNone = 0x00,
        kMinimalPrefix = 0x01,
        kProductionPrefix = 0x02,
        kDebugPrefix = 0x03,
        kFullPrefix = 0x04
    };

    /**
     * @enum Precision
     * @brief An enumeration of possible timestamp precisions.
     *
     * @details This enumeration provides a list of possible timestamp precisions. It is used by the logger to determine
     * what precision to format the timestamp to.
     */
    enum Precision : uint8_t {
        kSeconds = 0x00,
        kMilliseconds = 0x01,
        kMicroseconds = 0x02,
        kNanoseconds = 0x03
    };

/******************************
 * @section Properties
 * @subsection Public properties
 *****************************/

/******************************
 * @section Constructors
 *****************************/
    /**
     * @brief Default constructor (deleted). Creates an empty logger.
     */
    Logger() = delete;

    /**
     * @brief Fill constructor. Creates a new logger with an associated level and output file. Console output can be
     * enabled with or without colors or disabled entirely.
     * @param[in] logLevel The log level of the logger.
     * @param[in] prefixLevel The prefix level of the logger.
     * @param[optional] file The file to log to (defaults to "").
     * @param[optional] enableConsole Whether or not to enable console output (defaults to true).
     * @param[optional] enableColors Whether or not to enable colors for console output (defaults to false).
     */
    Logger(LogLevel logLevel, PrefixLevel prefixLevel, const std::string& file = "", bool enableConsole = true,
           bool enableColors = false);

    /**
     * @brief Copy constructor (deleted). Creates a copy of the given logger.
     * @param[in] other The logger to copy.
     */
    Logger(const Logger& other) = delete;

    /**
     * @brief Copy assignment operator (deleted). Copies the given logger.
     * @property[in] other The logger to copy.
     */
    Logger& operator=(const Logger& other) = delete;

    /**
     * @brief Move constructor (deleted). Moves the given logger.
     * @property[in] other The logger to move.
     */
    Logger(Logger&& other) = delete;

    /**
     * @brief Move assignment operator (deleted).
     * @property[in] other The logger to move.
     */
    Logger& operator=(Logger&& other) = delete;

    /**
     * @brief Destructor
     */
    ~Logger() noexcept;

/******************************
 * @section Methods
 * @subsection Public methods
 *****************************/
    /**
     * @brief Logs the given message to the logger.
     * @param[in] level The log level of the message.
     * @param[in] message The message to log.
     * @param[optional] file The file that the logger is being called from.
     * @param[optional] line The line that the logger is being called from.
     */
    static void Log(LogLevel level, const std::string& message, const std::string& file = __FILE__,
                    uint32_t line = __LINE__) noexcept;

    /**
     * @brief Gets the log level of the logger.
     * @return The log level of the logger.
     */
    static LogLevel GetLogLevel() noexcept;

    /**
     * @brief Sets the log level of the logger.
     * @param[in] level
     */
    static void SetLogLevel(LogLevel level) noexcept;

    /**
     * @brief Gets the prefix level of the logger.
     * @return The prefix level of the logger.
     */
    static PrefixLevel GetPrefixLevel() noexcept;

    /**
     * @brief Sets the prefix level of the logger.
     * @param level The prefix level to set.
     */
    static void SetPrefixLevel(PrefixLevel level) noexcept;

    /**
     * @brief Gets the color escape sequence for the given log level.
     * @param[in] level The log level to get the escape sequence for.
     * @return The color escape sequence for the given log level.
     */
    static std::string GetColor(LogLevel level) noexcept;

private:
/******************************
 * @section Properties
 * @subsection Private properties
 *****************************/
    /**
     * @property logLevel_
     * @brief The log level of the logger.
     */
    static LogLevel logLevel_;

    /**
     * @property prefixLevel_
     * @brief The prefix level of the logger.
     */
    static PrefixLevel prefixLevel_;

    /**
     * @property file_
     * @brief The file to log to.
     */
    std::string file_;

    /**
     * @property enableConsole_
     * @brief Whether or not to enable console output.
     */
    static bool enableConsole_;

    /**
     * @property enableColors_
     * @brief Whether or not to enable colors for console output.
     */
    static bool enableColors_;

    /**
     * @property consumer_
     * @brief The consumer thread.
     */
    std::thread consumer_;

    /**
     * @property stop_
     * @brief Whether or not to stop the consumer thread.
     */
    std::atomic<bool> stop_{};

    /**
     * @property messageQueues_
     * @brief A map of thread IDs to pointers to log message queues from different threads.
     */
    static std::map<std::thread::id, DataStructures::MpscQueue<std::string>*> messageQueues_;

/******************************
 * @section Methods
 * @subsection Private methods
 *****************************/
    /**
     * @brief Formats the prefix of the log message.
     * @param[in] level The log level of the message.
     * @param[in] prefixLevel The prefix level of the message
     * @param[optional] timestamp The timestamp of the message.
     * @param[optional] threadId The thread ID of the message.
     * @param[optional] file The file that the logger is being called from.
     * @param[optional] line The line that the logger is being called from.
     * @return A std::string of the formatted prefix.
     */
    static std::string FormatPrefix(LogLevel level, PrefixLevel prefixLevel,
                                    const std::chrono::system_clock::time_point& timestamp =
                                            std::chrono::system_clock::now(),
                                    const std::thread::id& threadId = std::this_thread::get_id(),
                                    const std::string& file = __FILE__,
                                    uint32_t line = __LINE__) noexcept;

    /**
     * @brief Formats the given timestamp to the given precision value.
     * @param[in] timestamp The timestamp to format.
     * @param[optional] precision The precision to format the timestamp to (defaults to seconds).
     * @return A std::string of the formatted timestamp.
     */
    static std::string FormatTimestamp(const std::chrono::system_clock::time_point& timestamp,
                                       Precision precision = kSeconds) noexcept;

    /**
     * @brief Formats the given log message.
     * @param[in] message The message to log.
     * @param[optional] prefix The prefix of the message.
     * @return A std::string of the formatted log message.
     */
    static std::string FormatLog(const std::string& message, const std::string& prefix = "") noexcept;
};
}

#endif //UMBRAENGINE_LOGGER_H
