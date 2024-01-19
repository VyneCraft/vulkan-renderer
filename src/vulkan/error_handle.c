#include "vulkan_error_handle.h"
#include <stdio.h>
#include <vulkan/vulkan_core.h>

int vulkan_error_handle(VkResult result, const char *error) {
    if(result != VK_SUCCESS) {
        (void) fprintf(stderr, "error %s: %u\n", error, result);

        return 1;
    }

    return 0;
}
