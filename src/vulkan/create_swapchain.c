#include "vulkan_error_handle.h"
#include "vulkan_renderer.h"
#include <vulkan/vulkan_core.h>

int vulkan_create_swapchain() {
    VkSwapchainCreateInfoKHR info = {0};
    info.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    info.surface = vulkan_data.surface;
    info.clipped = VK_TRUE;
    info.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
    info.imageExtent = vulkan_data.image_extent;
    info.imageFormat = vulkan_data.image_format;
    info.imageColorSpace = vulkan_data.image_color_space;
    info.presentMode = vulkan_data.image_present_mode;
    info.preTransform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;
    info.minImageCount = vulkan_data.minimum_image_count;
    info.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
    info.imageArrayLayers = 1;
    
    if(vulkan_data.graphic_queue_index == vulkan_data.present_queue_index)
        info.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
    else {
        info.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
        info.queueFamilyIndexCount = 2;
        info.pQueueFamilyIndices = (const unsigned[]) { vulkan_data.graphic_queue_index, vulkan_data.present_queue_index };
    }

    if(vulkan_error_handle(vkCreateSwapchainKHR(vulkan_data.device, &info, 0x0, &vulkan_data.swapchain), "creating swapchain"))
        return 1;

    return 0;
}
