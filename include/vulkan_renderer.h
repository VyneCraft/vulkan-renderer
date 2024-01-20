#ifndef VULKAN_RENDERER_HEADER
#define VULKAN_RENDERER_HEADER

#include <vulkan/vulkan.h>
#include <vulkan/vulkan_core.h>

struct VulkanData {
    VkInstance instance;

    VkSurfaceKHR surface;

    VkPhysicalDevice driver;
    VkQueue graphic_queue;
    VkQueue present_queue;

    VkDevice device;

    VkExtent2D image_extent;
    unsigned minimum_image_count;
    unsigned maximum_image_count;

    VkFormat image_format;
    VkColorSpaceKHR image_color_space;
    VkPresentModeKHR image_present_mode;

    VkSwapchainKHR swapchain;

    VkImage *images;
    VkImageView *image_views;

    VkPipeline pipeline;
    VkPipelineLayout pipeline_layout;

    VkRenderPass render_pass;

    VkFramebuffer *framebuffers;

    VkViewport viewport;

    unsigned image_count;

    int graphic_queue_index;
    int present_queue_index;
};

extern struct VulkanData vulkan_data;

int vulkan_create_instance(const char **required_extensions, unsigned extension_count);
int vulkan_get_surface_data();
int vulkan_select_driver();
int vulkan_create_device();
int vulkan_get_queues();
int vulkan_create_swapchain();
int vulkan_prepare_image_views();
int vulkan_create_render_pass();
int vulkan_create_pipeline();

int vulkan_create_shader_module(VkShaderModule *module, const char *binary, unsigned length);

#endif
