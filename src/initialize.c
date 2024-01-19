#include "vulkan_renderer.h"
#include "renderer/renderer.h"
#include <vulkan/vulkan.h>
#include <vulkan/vulkan_core.h>

struct VulkanData vulkan_data;

int initialize_renderer(const char **required_extensions, unsigned extensions_count) {
    if(
        vulkan_create_instance(required_extensions, extensions_count) ||
        get_window_surface(&vulkan_data.surface) ||
        vulkan_get_surface_data() ||
        vulkan_select_driver() ||
        vulkan_create_device() ||
        vulkan_get_queues() ||
        vulkan_create_swapchain()
    ) { return 1; }

    return 0;
}
