#ifndef VULKAN_RENDERER_HEADER
#define VULKAN_RENDERER_HEADER

#include <vulkan/vulkan.h>

struct VulkanData {
    VkPhysicalDevice driver;
};

extern struct VulkanData vulkan_data;

int vulkan_create_instance();
int vulkan_select_driver();

#endif
