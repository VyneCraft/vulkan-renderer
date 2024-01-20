#include "vulkan_renderer.h"
#include "renderer/renderer.h"
#include <vulkan/vulkan.h>
#include <vulkan/vulkan_core.h>

struct VulkanData vulkan_data;

int initialize_renderer(void *data_share, const char **required_extensions, unsigned extensions_count) {
    if(data_share)
        *(void **) data_share = &vulkan_data;

    if(
        vulkan_create_instance(required_extensions, extensions_count) ||
        window_create_surface((void **) &vulkan_data.surface) ||
        vulkan_select_driver() ||
        vulkan_get_surface_data() ||
        vulkan_create_device() ||
        vulkan_get_queues() ||
        vulkan_create_swapchain()
    ) { return 1; }

    return 0;
}
