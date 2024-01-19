#ifndef VULKAN_RENDERER_ERROR_HANDLE_HEADER
#define VULKAN_RENDERER_ERROR_HANDLE_HEADER

#include <vulkan/vulkan_core.h>

int vulkan_error_handle(VkResult result, const char *error);

#endif
