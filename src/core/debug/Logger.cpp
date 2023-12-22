//
// Created by Damon Tregear on 11/19/23.
//

#include "Logger.h"

namespace UmbraEngine::Core::Debug {
/******************************
 * @section Constructors
 *****************************/
Logger::Logger(LogLevel logLevel, PrefixLevel prefixLevel, const std::string& file, bool enableConsole,
               bool enableColors) {
    logLevel_ = logLevel;
    prefixLevel_ = prefixLevel;
    file_ = file;
    enableConsole_ = enableConsole;
    enableColors_ = enableColors;
    stop_ = false;

    std::ofstream ofs(file_);

    consumer_ = std::thread([&, this]() {
        while (!stop_.load()) {
            for (auto& messageQueue : messageQueues_) {
                if (!messageQueue.second->Empty()) {
                    std::string message = messageQueue.second->Front();
                    messageQueue.second->Pop();

                    // TODO: Continue here
                    // Add message to file and print to console if enabled
                    if (ofs.is_open()) {
                        ofs << message;
                    }

                    if (enableConsole_) {
                        std::cout << message;
                    }
                }
            }
        }

        ofs.close();
    });
}

Logger::~Logger() noexcept {
    stop_ = true;
    if (consumer_.joinable()) {
        consumer_.join();
    }

    // TODO: Modify memory freeing implementation?
    for (auto& messageQueue : messageQueues_) {
        delete messageQueue.second;
    }
}

/******************************
 * @section Methods
 * @subsection Public methods
 *****************************/
void Logger::Log(LogLevel level, const std::string& message, const std::string& file, uint32_t line) noexcept {
    std::chrono::system_clock::time_point timestamp = std::chrono::system_clock::now();

    std::thread::id threadId = std::this_thread::get_id();
    auto it = messageQueues_.find(threadId);
    if (it == messageQueues_.end()) {
        // TODO: Use built in memory allocator?
        auto* queue = new DataStructures::MpscQueue<std::string>(100);
        it = messageQueues_.insert({threadId, queue}).first;
    }

    std::string formattedPrefix = FormatPrefix(level, prefixLevel_, timestamp, threadId, file, line);
    std::string formattedLog = FormatLog(message, formattedPrefix);
    it->second->Push(formattedLog);
}

Logger::LogLevel Logger::GetLogLevel() noexcept {
    return logLevel_;
}

void Logger::SetLogLevel(LogLevel level) noexcept {
    logLevel_ = level;
}

Logger::PrefixLevel Logger::GetPrefixLevel() noexcept {
    return prefixLevel_;
}

void Logger::SetPrefixLevel(PrefixLevel level) noexcept {
    prefixLevel_ = level;
}

std::string Logger::GetColor(LogLevel level) noexcept {
    switch (level) {
        case LogLevel::kFatal:
            return "\033[41m";  // Red
        case LogLevel::kError:
            return "\033[33m";  // Orange
        case LogLevel::kAlert:
            return "\033[45m";  // Purple
        case LogLevel::kWarn:
            return "\033[43m";  // Yellow
        case LogLevel::kInfo:
            return "\033[42m";  // Green
        case LogLevel::kDebug:
            return "\033[44m";  // Blue
        case LogLevel::kTrace:
            return "\033[46m";  // Grey
        default:
            return "\033[0m";   // Reset
    }
}

/******************************
 * @section Methods
 * @subsection Private methods
 *****************************/
std::string Logger::FormatPrefix(LogLevel level, PrefixLevel prefixLevel,
                                 const std::chrono::system_clock::time_point& timestamp,
                                 const std::thread::id& threadId, const std::string& file, uint32_t line) noexcept {
    std::string time;
    std::stringstream ss;
    switch (prefixLevel) {
        case PrefixLevel::kNone:
            break;
        case PrefixLevel::kMinimalPrefix:
            if (enableConsole_ && enableColors_) {
                std::string color = GetColor(level);
                ss << color << level << "\033[0m" << ": ";
                break;
            }

            ss << level << ": ";
            break;
        case PrefixLevel::kProductionPrefix:
            time = FormatTimestamp(timestamp);

            if (enableConsole_ && enableColors_) {
                std::string color = GetColor(level);
                ss << "[" << time << "] " << color << level << "\033[0m" << ": ";
                break;
            }

            ss << "[" << time << "] " << level << ": ";
            break;
        case PrefixLevel::kDebugPrefix:
            time = FormatTimestamp(timestamp, Precision::kMilliseconds);

            if (enableConsole_ && enableColors_) {
                std::string color = GetColor(level);
                ss << "[" << time << "] " << color << level << "\033[0m" << file << ":" << line << ": ";
                break;
            }

            ss << "[" << time << "] " << level << file << ":" << line << ": ";
            break;
        case PrefixLevel::kFullPrefix:
            time = FormatTimestamp(timestamp, Precision::kNanoseconds);

            if (enableConsole_ && enableColors_) {
                std::string color = GetColor(level);
                ss << "[" << time << "] " << color << level << "\033[0m" << file << ":" << line << " (" <<
                    threadId << "): ";
                break;
            }

            ss << "[" << time << "] " << level << file << ":" << line << " (" << threadId << "): ";
            break;
        default:
            break;
    }

    return ss.str();
}

std::string Logger::FormatTimestamp(const std::chrono::system_clock::time_point& timestamp,
                                    Precision precision) noexcept {
    auto duration = timestamp.time_since_epoch();

    std::stringstream ss;
    std::time_t time = std::chrono::system_clock::to_time_t(timestamp);
    ss << std::put_time(std::localtime(&time), "%H:%M:%S");

    switch (precision) {
        case Precision::kSeconds:
            break;  // Already formatted to seconds
        case Precision::kMilliseconds:
            ss << '.' << std::setfill('0') << std::setw(3)
               << std::chrono::duration_cast<std::chrono::milliseconds>(duration).count() % 1000;
            break;
        case Precision::kMicroseconds:
            ss << '.' << std::setfill('0') << std::setw(6)
               << std::chrono::duration_cast<std::chrono::microseconds>(duration).count() % 1000000;
            break;
        case Precision::kNanoseconds:
            ss << '.' << std::setfill('0') << std::setw(9)
               << std::chrono::duration_cast<std::chrono::nanoseconds>(duration).count() % 1000000000;
            break;
        default:
            break;
    }

    return ss.str();
}

std::string Logger::FormatLog(const std::string& message, const std::string& prefix) noexcept {
    std::stringstream ss;
    ss << prefix << message << "\n";

    return ss.str();
}
}