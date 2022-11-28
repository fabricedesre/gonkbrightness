// Test program to drive screen brightness

#include <stdlib.h>
#include <log/log.h>

#include <android/hardware/graphics/composer/2.3/IComposer.h>

namespace V2_1 = android::hardware::graphics::composer::V2_1;
namespace V2_3 = android::hardware::graphics::composer::V2_3;

int main(int argc, char** argv) {
    if (argc != 2) {
        ALOGE("Usage: %s brightness", argv[0]);
        return -1;
    }
    float brightness = atof(argv[1]);
    ALOGI("will set brightness to %f", brightness);

    auto composer = V2_3::IComposer::getService("default");

    if (composer == nullptr) {
        ALOGE("failed to get hwcomposer service");
        return -2;
    }

    android::sp<V2_3::IComposerClient> client;

    composer->createClient_2_3([&](const auto& tmpError, const auto& tmpClient) {
        if (tmpError == V2_1::Error::NONE) {
            client = tmpClient;
        } else {
            ALOGE("Failed to create client!");
        }
    });

    if (!client) {
        ALOGE("Giving up");
        return -3;
    }

    // TODO: don't hardcode display number to 0
    auto error = client->setDisplayBrightness(0, brightness);
    if (error != V2_1::Error::NONE) {
        ALOGE("Failed to set brightness!");
    } else {
        ALOGI("Success changing brightness!");
    }
}
