#include "vulkan_renderer.h"
#include "vulkan_error_handle.h"
#include <stdio.h>
#include <string.h>
#include <vulkan/vulkan.h>
#include <vulkan/vulkan_core.h>

static const char *program_extensions[] = {

};

static const unsigned program_extension_count = sizeof(program_extensions) / sizeof(*program_extensions);

static int verify_instance_extensions(const char **extensions, unsigned extension_count);

int vulkan_create_instance(const char **required_extensions, unsigned required_extension_count) {
    const char *instance_extensions[program_extension_count + required_extension_count];
    memcpy(instance_extensions, program_extensions, program_extension_count * sizeof(const char *));
    memcpy(instance_extensions + program_extension_count, required_extensions, required_extension_count * sizeof(const char *));

    if(verify_instance_extensions(instance_extensions, program_extension_count + required_extension_count))
        return 1;

    VkApplicationInfo app_info = {0};
    app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    app_info.apiVersion = VK_API_VERSION_1_3;
    app_info.pApplicationName = "vulkan";
    app_info.applicationVersion = 1;

    VkInstanceCreateInfo info = {0};
    info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    info.pApplicationInfo = &app_info;
    info.enabledExtensionCount = required_extension_count;
    info.ppEnabledExtensionNames = required_extensions;

    if(vulkan_error_handle(vkCreateInstance(&info, 0x0, (VkInstance *) &vulkan_data.instance), "creating vulkan instance"))
        return 1;

    return 0;
}

static int verify_instance_extensions(const char **extensions, unsigned extension_count) {
    int return_value = 0;

    unsigned propertie_count = 0;

    if(vulkan_error_handle(vkEnumerateInstanceExtensionProperties(0x0, &propertie_count, 0x0), "enumerating instance extension properties"))
        return 1;

    VkExtensionProperties properties[propertie_count];

    if(vulkan_error_handle(vkEnumerateInstanceExtensionProperties(0x0, &propertie_count, properties), "enumerating instance extension properties"))
        return 1;

    unsigned char is_extension_valid = 0;

    for(unsigned extension_index = 0; extension_index < extension_count; ++extension_index) {
        for(unsigned propertie_index = 0; propertie_index < propertie_count; ++propertie_index) {
            if(!strcmp(properties[propertie_index].extensionName, extensions[extension_index])) {
                is_extension_valid = 1;
                break;
            }
        }

        if(!is_extension_valid) {
            (void) fprintf(stderr, "instance extension: '%s' not found\n", extensions[extension_index]);

            return_value = 1;
        }
    }

    return return_value;
}
