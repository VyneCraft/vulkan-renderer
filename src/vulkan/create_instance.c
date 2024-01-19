#include "memory_alias.h"
#include "vulkan_renderer.h"
#include "renderer/renderer.h"
#include "vulkan_error_handle.h"
#include <vulkan/vulkan.h>
#include <vulkan/vulkan_core.h>

static void destroy_instance(void *pointer);

int vulkan_create_instance() {
    VkApplicationInfo app_info = {0};
    app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    app_info.apiVersion = VK_API_VERSION_1_3;
    app_info.pApplicationName = "vulkan";
    app_info.applicationVersion = 1;

    VkInstanceCreateInfo info = {0};
    info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    info.pApplicationInfo = &app_info;
    info.enabledExtensionCount = renderer_context.extension_count;
    info.ppEnabledExtensionNames = renderer_context.extensions;

    if(vulkan_error_handle(vkCreateInstance(&info, 0x0, (VkInstance *) &renderer_context.instance), "creating vulkan instance"))
        return 1;

    memory_push_alias(renderer_context.instance, destroy_instance);

    return 0;
}

static void destroy_instance(void *pointer) {
    vkDestroyInstance(pointer, 0x0);
}
