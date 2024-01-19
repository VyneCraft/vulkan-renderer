#include "vulkan_error_handle.h"
#include "vulkan_renderer.h"
#include <vulkan/vulkan_core.h>

int vulkan_create_device() {
    VkDeviceQueueCreateInfo graphic_queue_info = {0};
    graphic_queue_info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    graphic_queue_info.queueCount = 1;
    graphic_queue_info.pQueuePriorities = &(float) { 1 };
    graphic_queue_info.queueFamilyIndex = vulkan_data.graphic_queue_index;

    VkDeviceQueueCreateInfo present_queue_info = {0};
    present_queue_info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    present_queue_info.queueCount = 1;
    present_queue_info.pQueuePriorities = &(float) { 1 };
    present_queue_info.queueFamilyIndex = vulkan_data.present_queue_index;

    VkDeviceCreateInfo info = {0};
    info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    info.pQueueCreateInfos = (VkDeviceQueueCreateInfo[]) { graphic_queue_info, present_queue_info };
    info.queueCreateInfoCount = 2;
    info.enabledExtensionCount = 1;
    info.ppEnabledExtensionNames = (const char *[]) { VK_KHR_SWAPCHAIN_EXTENSION_NAME };

    if(vulkan_error_handle(vkCreateDevice(vulkan_data.driver, &info, 0x0, &vulkan_data.device), "creating device"))
        return 1;

    return 0;
}
