#include "vulkan_renderer.h"
#include "vulkan_error_handle.h"
#include <stdio.h>
#include <vulkan/vulkan_core.h>

int vulkan_get_queues() {
    unsigned queue_count = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(vulkan_data.driver, &queue_count, 0x0);
    
    VkQueueFamilyProperties queue_properties[queue_count];
    vkGetPhysicalDeviceQueueFamilyProperties(vulkan_data.driver, &queue_count, queue_properties);

    for(unsigned queue_index = 0; queue_index < queue_count; ++queue_index) {
        if(queue_properties[queue_index].queueFlags & VK_QUEUE_GRAPHICS_BIT && vulkan_data.graphic_queue_index < 0)
            vulkan_data.graphic_queue_index = queue_index;

        if(vulkan_data.present_queue_index < 0) {
            VkBool32 is_present_supported = VK_FALSE;

            if(vulkan_error_handle(vkGetPhysicalDeviceSurfaceSupportKHR(vulkan_data.driver, queue_index, vulkan_data.surface, &is_present_supported), "getting physical device surface support KHR"))
                return 1;

            vulkan_data.present_queue_index = queue_index;
        }
    }

    if(vulkan_data.graphic_queue < 0 | vulkan_data.present_queue_index < 0) {
        (void) fputs("couldn't find graphics queue or present queue\n", stderr);

        return 1;
    }

    vkGetDeviceQueue(vulkan_data.device, vulkan_data.graphic_queue_index, 0, &vulkan_data.graphic_queue);
    vkGetDeviceQueue(vulkan_data.device, vulkan_data.present_queue_index, 0, &vulkan_data.present_queue);

    return 0;
}
