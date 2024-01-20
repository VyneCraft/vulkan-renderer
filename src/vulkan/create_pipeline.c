#include "vulkan_error_handle.h"
#include "vulkan_renderer.h"
#include <vulkan/vulkan_core.h>

extern const char *__block_vert_spv;
extern const unsigned __block_vert_spv_length;

extern const char *__block_frag_spv;
extern const unsigned __block_frag_spv_length;

int vulkan_create_pipeline() {
    VkPipelineDynamicStateCreateInfo dynamic_state_info = {0};
    dynamic_state_info.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;

    VkPipelineShaderStageCreateInfo vertex_shader = {0};
    vertex_shader.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    vertex_shader.stage = VK_SHADER_STAGE_VERTEX_BIT;
    vertex_shader.pName = "main";

    if(vulkan_create_shader_module(&vertex_shader.module, __block_vert_spv, __block_vert_spv_length))
        return 1;

    VkPipelineShaderStageCreateInfo fragment_shader = {0};
    fragment_shader.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    fragment_shader.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
    fragment_shader.pName = "main";

    if(vulkan_create_shader_module(&fragment_shader.module, __block_frag_spv, __block_frag_spv_length))
        return 1;

    // No Dynamic State

    VkPipelineInputAssemblyStateCreateInfo assembly_stage_info = {0};
    assembly_stage_info.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
    assembly_stage_info.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;

    VkPipelineVertexInputStateCreateInfo vertex_stage_info = {0};
    vertex_stage_info.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;

    vulkan_data.viewport.width = vulkan_data.image_extent.width;
    vulkan_data.viewport.height = vulkan_data.image_extent.height;
    vulkan_data.viewport.maxDepth = 1;

    VkPipelineViewportStateCreateInfo viewport_info = {0};
    viewport_info.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
    viewport_info.viewportCount = 1;
    viewport_info.pViewports = &vulkan_data.viewport;

    VkPipelineRasterizationStateCreateInfo rasterization_stage_info = {0};
    rasterization_stage_info.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
    rasterization_stage_info.cullMode = VK_CULL_MODE_BACK_BIT;
    rasterization_stage_info.frontFace = VK_FRONT_FACE_CLOCKWISE;
    rasterization_stage_info.lineWidth = 1;
    rasterization_stage_info.polygonMode = VK_POLYGON_MODE_FILL;
    
    VkPipelineMultisampleStateCreateInfo multisample_info = {0};
    multisample_info.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
    multisample_info.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;

    VkPipelineColorBlendAttachmentState color_blend_attachment = {0};
    color_blend_attachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;

    VkPipelineColorBlendStateCreateInfo color_blend_info = {0};
    color_blend_info.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
    color_blend_info.attachmentCount = 1;
    color_blend_info.pAttachments = &color_blend_attachment;

    VkPipelineLayoutCreateInfo pipeline_layout_info = {0};
    pipeline_layout_info.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    
    if(vulkan_error_handle(vkCreatePipelineLayout(vulkan_data.device, &pipeline_layout_info, 0x0, &vulkan_data.pipeline_layout), "creating pipeline layout"))
        return 1;

    VkGraphicsPipelineCreateInfo info = {0};
    info.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
    info.layout = vulkan_data.pipeline_layout;
    info.pStages = (VkPipelineShaderStageCreateInfo[]) { vertex_shader, fragment_shader };
    info.stageCount = 2;
    info.renderPass = vulkan_data.render_pass;
    info.pDynamicState = &dynamic_state_info;
    info.pViewportState = &viewport_info;
    info.pInputAssemblyState = &assembly_stage_info;
    info.pVertexInputState = &vertex_stage_info;
    info.pRasterizationState = &rasterization_stage_info;
    info.pMultisampleState = &multisample_info;
    info.pColorBlendState = &color_blend_info;

    if(vulkan_error_handle(vkCreateGraphicsPipelines(vulkan_data.device, 0x0, 1, &info, 0x0, &vulkan_data.pipeline), "creating pipeline"))
        return 1;

    return 0;
}
