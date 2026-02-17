#include <coreobjects/util.h>
#include <testutils/daq_memcheck_listener.h>

int main(int argc, char** args)
{
    {
        ModuleManager(".");
    }
    testing::InitGoogleTest(&argc, args);

    testing::TestEventListeners& listeners = testing::UnitTest::GetInstance()->listeners();
    listeners.Append(new DaqMemCheckListener());

    auto res = RUN_ALL_TESTS();

    return res;
}
