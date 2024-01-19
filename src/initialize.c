#include "vulkan_renderer.h"
#include "renderer/renderer.h"
#include <vulkan/vulkan.h>
#include <vulkan/vulkan_core.h>

struct VulkanData vulkan_data;

int initialize_renderer() {
    if(vulkan_create_instance())
        return 1;

    return 0;
}
