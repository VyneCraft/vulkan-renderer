#include "vulkan_renderer.h"
#include "vulkan_error_handle.h"
#include <vulkan/vulkan_core.h>

static unsigned evaluate_points(VkPhysicalDevice driver);

int vulkan_select_driver() {
    unsigned driver_count = 0;
    if(vulkan_error_handle(vkEnumeratePhysicalDevices(vulkan_data.instance, &driver_count, 0x0), "enumerating physical devices"))
        return 1;

    VkPhysicalDevice drivers[driver_count];

    if(vulkan_error_handle(vkEnumeratePhysicalDevices(vulkan_data.instance, &driver_count, drivers), "enumerating physical devices"))
        return 1;
    
    unsigned highest_driver_points = 0;
    unsigned driver_points;

    for(unsigned driver_index = 0; driver_index < driver_count; ++driver_index) {
        driver_points = evaluate_points(drivers[driver_index]);

        if(driver_points > highest_driver_points) {
            highest_driver_points = driver_points;

            vulkan_data.driver = drivers[driver_index];
        }
    }

    return 0;
}

static unsigned evaluate_points(VkPhysicalDevice driver) {
    // Get Device Properties/Features and evaluate all points

    return 0;
}
