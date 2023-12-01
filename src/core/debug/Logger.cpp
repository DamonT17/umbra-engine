//
// Created by Damon Tregear on 11/19/23.
//

#include "Logger.h"

namespace UmbraEngine::Core::Debug {
/******************************
 * @section Constructors
 *****************************/
// TODO: Implement Logger::Logger()

/******************************
 * @section Methods
 * @subsection Public methods
 *****************************/
void Logger::Log(const std::string& message) const {
    // TODO: Format the message

    std::cout << message << "\n";
}

void Logger::Log(LogLevel level, const std::string& message) const {
    // TODO: Implement Log function
}

}