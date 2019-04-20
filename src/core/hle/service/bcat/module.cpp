// Copyright 2018 yuzu emulator team
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#include "common/logging/log.h"
#include "core/hle/ipc_helpers.h"
#include "core/hle/service/bcat/bcat.h"
#include "core/hle/service/bcat/module.h"

namespace Service::BCAT {

class IBcatService final : public ServiceFramework<IBcatService> {
public:
    IBcatService() : ServiceFramework("IBcatService") {
        static const FunctionInfo functions[] = {
            {10, &IBcatService::EnumerateDeliveryCacheDirectory, "EnumerateDeliveryCacheDirectory"},
            {10100, nullptr, "RequestSyncDeliveryCache"},
            {10101, nullptr, "RequestSyncDeliveryCacheWithDirectoryName"},
            {10200, nullptr, "CancelSyncDeliveryCacheRequest"},
            {20100, nullptr, "RequestSyncDeliveryCacheWithApplicationId"},
            {20101, nullptr, "RequestSyncDeliveryCacheWithApplicationIdAndDirectoryName"},
            {30100, nullptr, "SetPassphrase"},
            {30200, nullptr, "RegisterBackgroundDeliveryTask"},
            {30201, nullptr, "UnregisterBackgroundDeliveryTask"},
            {30202, nullptr, "BlockDeliveryTask"},
            {30203, nullptr, "UnblockDeliveryTask"},
            {90100, nullptr, "EnumerateBackgroundDeliveryTask"},
            {90200, nullptr, "GetDeliveryList"},
            {90201, nullptr, "ClearDeliveryCacheStorage"},
            {90300, nullptr, "GetPushNotificationLog"},
        };
        RegisterHandlers(functions);
    }

    private:
    void EnumerateDeliveryCacheDirectory(Kernel::HLERequestContext& ctx) {
        // Stub used by smash
        LOG_WARNING(Service_BCAT, "(STUBBED by me) called");
        //std::vector<u8> data = ctx.ReadBuffer();
        //std::array<u8, 1> test{{0}};
        //ctx.WriteBuffer(test);
        std::vector<u8> buffer(0);
        ctx.WriteBuffer(buffer.data(), buffer.size());

      IPC::ResponseBuilder rb{ctx, 3};
        rb.Push(RESULT_SUCCESS);
        rb.Push<u32>(0);
    }
};

void Module::Interface::CreateBcatService(Kernel::HLERequestContext& ctx) {
    LOG_DEBUG(Service_BCAT, "called");

    IPC::ResponseBuilder rb{ctx, 2, 0, 1};
    rb.Push(RESULT_SUCCESS);
    rb.PushIpcInterface<IBcatService>();
}

void Module::Interface::CreateDeliveryCacheStorageService(Kernel::HLERequestContext& ctx) {
    LOG_WARNING(Service_BCAT, "(STUBBED by me) called");

    IPC::ResponseBuilder rb{ctx, 2, 0, 1};
    rb.Push(RESULT_SUCCESS);
    rb.PushIpcInterface<IBcatService>();
}

Module::Interface::Interface(std::shared_ptr<Module> module, const char* name)
    : ServiceFramework(name), module(std::move(module)) {}

Module::Interface::~Interface() = default;

void InstallInterfaces(SM::ServiceManager& service_manager) {
    auto module = std::make_shared<Module>();
    std::make_shared<BCAT>(module, "bcat:a")->InstallAsService(service_manager);
    std::make_shared<BCAT>(module, "bcat:m")->InstallAsService(service_manager);
    std::make_shared<BCAT>(module, "bcat:u")->InstallAsService(service_manager);
    std::make_shared<BCAT>(module, "bcat:s")->InstallAsService(service_manager);
}

} // namespace Service::BCAT
