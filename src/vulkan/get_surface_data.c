#include "renderer/renderer.h"
#include "vulkan_error_handle.h"
#include "vulkan_renderer.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <vulkan/vulkan_core.h>

int vulkan_get_surface_data() {
    VkSurfaceCapabilitiesKHR capabilities = {0};

    if(vulkan_error_handle(vkGetPhysicalDeviceSurfaceCapabilitiesKHR(vulkan_data.driver, vulkan_data.surface, &capabilities), "getting surface capabilites"))
        return 1;

    if(capabilities.currentExtent.width != UINT32_MAX)
        memcpy(&vulkan_data.image_extent, &capabilities.currentExtent, sizeof(vulkan_data.image_extent));
    else if(window_get_framebuffer_size(&vulkan_data.image_extent.width, &vulkan_data.image_extent.height))
            return 1;

    vulkan_data.minimum_image_count = capabilities.minImageCount;
    vulkan_data.maximum_image_count = capabilities.maxImageCount;

    unsigned format_count = 0;

    if(vulkan_error_handle(vkGetPhysicalDeviceSurfaceFormatsKHR(vulkan_data.driver, vulkan_data.surface, &format_count, 0x0), "getting surface formats"))
        return 1;

    if(!format_count)
        (void) fputs("error: no surface formats", stderr);

    VkSurfaceFormatKHR formats[format_count];

    if(vulkan_error_handle(vkGetPhysicalDeviceSurfaceFormatsKHR(vulkan_data.driver, vulkan_data.surface, &format_count, formats), "getting surface formats"))
        return 1;

    unsigned char is_format_selected = 0;

    for(unsigned format_index = 0; format_index < format_count; ++format_index) {
        if(formats[format_index].format == VK_FORMAT_B8G8R8A8_SRGB && formats[format_index].colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
            vulkan_data.image_format = formats[format_index].format;
            vulkan_data.image_color_space = formats[format_index].colorSpace;

            is_format_selected = 1;

            break;
        }
    }

    if(!is_format_selected && format_count) {
        vulkan_data.image_format = formats[0].format;
        vulkan_data.image_color_space = formats[0].colorSpace;
    }

    unsigned present_mode_count = 0;

    if(vulkan_error_handle(vkGetPhysicalDeviceSurfacePresentModesKHR(vulkan_data.driver, vulkan_data.surface, &present_mode_count, 0x0), "getting surface present modes"))
        return 1;

    if(!present_mode_count)
        (void) fputs("error: no surface present mode", stderr);

    VkPresentModeKHR present_modes[present_mode_count];

    if(vulkan_error_handle(vkGetPhysicalDeviceSurfacePresentModesKHR(vulkan_data.driver, vulkan_data.surface, &present_mode_count, present_modes), "getting surface present modes"))
        return 1;

    unsigned char is_present_mode_selected = 0;

    for(unsigned present_mode_index = 0; present_mode_index < present_mode_count; ++present_mode_index) {
        if(present_modes[present_mode_index] == VK_PRESENT_MODE_MAILBOX_KHR) {
            vulkan_data.image_present_mode = VK_PRESENT_MODE_MAILBOX_KHR;

            is_present_mode_selected = 1;

            break;
        }
    }

    if(!is_present_mode_selected)
        vulkan_data.image_present_mode = VK_PRESENT_MODE_FIFO_KHR; // That mode is required by the vulkan, a vulkan driver will always need to have it

    return 0;
}
