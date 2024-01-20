#include "renderer/renderer.h"
#include "vulkan_renderer.h"
#include <stdlib.h>
#include <vulkan/vulkan_core.h>

int close_renderer() {
    if(vulkan_data.image_views) {
        for(unsigned image_view_index = 0; image_view_index < vulkan_data.image_count; ++image_view_index) {
            vkDestroyImageView(vulkan_data.device, vulkan_data.image_views[image_view_index], 0x0);
        }

        free(vulkan_data.image_views);
    }
 
    if(vulkan_data.images)
        free(vulkan_data.images);

    if(vulkan_data.swapchain)
        vkDestroySwapchainKHR(vulkan_data.device, vulkan_data.swapchain, 0x0);
    
    if(vulkan_data.device)
        vkDestroyDevice(vulkan_data.device, 0x0);

    if(vulkan_data.surface)
        vkDestroySurfaceKHR(vulkan_data.instance, vulkan_data.surface, 0x0);

    if(vulkan_data.instance)
        vkDestroyInstance(vulkan_data.instance, 0x0);

    return 0;
}
