#include "vulkan_error_handle.h"
#include "vulkan_renderer.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vulkan/vulkan_core.h>

int vulkan_prepare_image_views() {
    if(vulkan_error_handle(vkGetSwapchainImagesKHR(vulkan_data.device, vulkan_data.swapchain, &vulkan_data.image_count, 0x0), "getting swapchain images"))
        return 1;

    vulkan_data.images = malloc(vulkan_data.image_count * sizeof(VkImage));

    if(!vulkan_data.images) {
        (void) fprintf(stderr, "error allocating swapchain images buffer: %s\n", strerror(errno));

        return 1;
    }

    if(vulkan_error_handle(vkGetSwapchainImagesKHR(vulkan_data.device, vulkan_data.swapchain, &vulkan_data.image_count, vulkan_data.images), "getting swapchain images"))
        return 1;

    vulkan_data.image_views = malloc(vulkan_data.image_count * sizeof(VkImage));

    if(!vulkan_data.image_views) {
        (void) fprintf(stderr, "error allocating image views buffer: %s\n", strerror(errno));

        return 1;
    }

    VkImageViewCreateInfo info = {0};
    info.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    info.format = vulkan_data.image_format;
    info.viewType = VK_IMAGE_VIEW_TYPE_2D;
    info.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
    info.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
    info.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
    info.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
    info.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    info.subresourceRange.levelCount = 1;
    info.subresourceRange.layerCount = 1;

    for(unsigned image_index = 0; image_index < vulkan_data.image_count; ++image_index) {
        info.image = vulkan_data.images[image_index];

        if(vulkan_error_handle(vkCreateImageView(vulkan_data.device, &info, 0x0, vulkan_data.image_views + image_index), "creating image view"))
            return 1;
    }

    return 0;
}
