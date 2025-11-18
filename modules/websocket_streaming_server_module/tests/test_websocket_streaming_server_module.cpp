#include <websocket_streaming_server_module/module_dll.h>
#include <websocket_streaming_server_module/version.h>
#include <opendaq/context_factory.h>
#include <opendaq/instance_factory.h>
#include <opendaq/instance_ptr.h>
#include <opendaq/module_manager_factory.h>
#include <opendaq/module_ptr.h>
#include <coretypes/common.h>
#include <testutils/testutils.h>

class WebsocketStreamingServerModuleTest : public testing::Test
{
public:
    void TearDown() override
    {
    }
};

using namespace daq;

static ModulePtr CreateModule(ContextPtr context = NullContext())
{
    ModulePtr module;
    createWebsocketStreamingServerModule(&module, context);
    return module;
}

static PropertyObjectPtr CreateServerConfig(const InstancePtr& instance)
{
    auto config = instance.getAvailableServerTypes().get("OpenDAQLTStreaming").createDefaultConfig();
    config.setPropertyValue("WebsocketStreamingPort", 0);
    config.setPropertyValue("WebsocketControlPort", 0);
    return config;
}

TEST_F(WebsocketStreamingServerModuleTest, CreateModule)
{
    IModule* module = nullptr;
    ErrCode errCode = createModule(&module, NullContext());
    ASSERT_TRUE(OPENDAQ_SUCCEEDED(errCode));

    ASSERT_NE(module, nullptr);
    module->releaseRef();
}

TEST_F(WebsocketStreamingServerModuleTest, ModuleName)
{
    auto module = CreateModule();
    ASSERT_EQ(module.getModuleInfo().getName(), "OpenDAQWebsocketStreamingServerModule");
}

TEST_F(WebsocketStreamingServerModuleTest, VersionAvailable)
{
    auto module = CreateModule();
    ASSERT_TRUE(module.getModuleInfo().getVersionInfo().assigned());
}

TEST_F(WebsocketStreamingServerModuleTest, VersionCorrect)
{
    auto module = CreateModule();
    auto version = module.getModuleInfo().getVersionInfo();

    ASSERT_EQ(version.getMajor(), WS_STREAM_SRV_MODULE_MAJOR_VERSION);
    ASSERT_EQ(version.getMinor(), WS_STREAM_SRV_MODULE_MINOR_VERSION);
    ASSERT_EQ(version.getPatch(), WS_STREAM_SRV_MODULE_PATCH_VERSION);
}

TEST_F(WebsocketStreamingServerModuleTest, GetAvailableComponentTypes)
{
    const auto module = CreateModule();

    DictPtr<IString, IFunctionBlockType> functionBlockTypes;
    ASSERT_NO_THROW(functionBlockTypes = module.getAvailableFunctionBlockTypes());
    ASSERT_EQ(functionBlockTypes.getCount(), 0u);

    DictPtr<IString, IDeviceType> deviceTypes;
    ASSERT_NO_THROW(deviceTypes = module.getAvailableDeviceTypes());
    ASSERT_EQ(deviceTypes.getCount(), 0u);

    DictPtr<IString, IServerType> serverTypes;
    ASSERT_NO_THROW(serverTypes = module.getAvailableServerTypes());
    ASSERT_EQ(serverTypes.getCount(), 1u);
    ASSERT_TRUE(serverTypes.hasKey("OpenDAQLTStreaming"));
    ASSERT_EQ(serverTypes.get("OpenDAQLTStreaming").getId(), "OpenDAQLTStreaming");
}

TEST_F(WebsocketStreamingServerModuleTest, ServerConfig)
{
    auto module = CreateModule();

    DictPtr<IString, IServerType> serverTypes = module.getAvailableServerTypes();
    ASSERT_TRUE(serverTypes.hasKey("OpenDAQLTStreaming"));
    auto config = serverTypes.get("OpenDAQLTStreaming").createDefaultConfig();
    ASSERT_TRUE(config.assigned());

    ASSERT_TRUE(config.hasProperty("WebsocketStreamingPort"));
    ASSERT_EQ(config.getPropertyValue("WebsocketStreamingPort"), 7414);

    ASSERT_TRUE(config.hasProperty("WebsocketControlPort"));
    ASSERT_EQ(config.getPropertyValue("WebsocketControlPort"), 7438);
}

TEST_F(WebsocketStreamingServerModuleTest, CreateServer)
{
    auto device = Instance();
    auto module = CreateModule(device.getContext());
    auto config = CreateServerConfig(device);

    ASSERT_NO_THROW(module.createServer("OpenDAQLTStreaming", device.getRootDevice(), config));
}

TEST_F(WebsocketStreamingServerModuleTest, CreateServerFromInstance)
{
    auto device = Instance();
    auto config = CreateServerConfig(device);

    ASSERT_NO_THROW(device.addServer("OpenDAQLTStreaming", config));
}
