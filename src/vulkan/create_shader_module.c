#include "vulkan_renderer.h"
#include "vulkan_error_handle.h"
#include <vulkan/vulkan_core.h>

int vulkan_create_shader_module(VkShaderModule *module, const char *binary, unsigned length) {
    VkShaderModuleCreateInfo info = {0};
    info.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    info.pCode = (const unsigned *) binary;
    info.codeSize = length;

    if(vulkan_error_handle(vkCreateShaderModule(vulkan_data.device, &info, 0x0, module), "creating shader module"))
        return 1;

    return 0;
}
