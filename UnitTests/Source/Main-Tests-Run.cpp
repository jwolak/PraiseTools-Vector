/*#include "Command-Line-Parser-Tests.cpp"*/

#include <gtest/gtest.h>
#include "gmock/gmock.h"

//#include "TensionCpuTests/Cmd-Args-Parser-Tests.cpp"
//#include "TensionCpuTests/Tension-Cpu-Tests.cpp"
#include "TensionCpuTests/TimerTests.cpp"

int main(int argc, char **argv) {
    SET_LOG_LEVEL(equinox_logger::LogLevelType::LOG_LEVEL_DEBUG);

    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
