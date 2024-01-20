#include "vulkan_error_handle.h"
#include "vulkan_renderer.h"
#include <vulkan/vulkan_core.h>

int vulkan_create_render_pass() {
    VkAttachmentDescription color_attachment = {0};
    color_attachment.format = vulkan_data.image_format;
    color_attachment.samples = VK_SAMPLE_COUNT_1_BIT;
    color_attachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
    color_attachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
    color_attachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    color_attachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    color_attachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    color_attachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

    VkAttachmentReference attachment_reference = {0};
    attachment_reference.attachment = 0;
    attachment_reference.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

    VkSubpassDescription subpass = {0};
    subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
    subpass.pColorAttachments = &attachment_reference;
    subpass.colorAttachmentCount = 1;

    VkRenderPassCreateInfo info = {0};
    info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    info.attachmentCount = 1;
    info.pAttachments = &color_attachment;
    info.pSubpasses = &subpass;
    info.subpassCount = 1;

    if(vulkan_error_handle(vkCreateRenderPass(vulkan_data.device, &info, 0x0, &vulkan_data.render_pass), "creating render pass"))
        return 1;

    return 0;
}
