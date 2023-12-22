//
// Created by damon on 9/10/2023.
//

#include <iostream>

#include "core/debug/Logger.h"

using UmbraEngine::Core::Debug::Logger;

int main() {
    Logger testLogger(Logger::LogLevel::kDebug, Logger::PrefixLevel::kMinimalPrefix, "test.log",
                      true, true);

    for (int i = 0; i < 16; i++) {
        std::stringstream ss;
        ss << "message # " << i;
        testLogger.Log(Logger::kDebug, ss.str());
    }

    testLogger.~Logger();

    return 0;
}