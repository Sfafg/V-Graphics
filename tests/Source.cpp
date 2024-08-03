#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <vulkan/vulkan.hpp>
#include <GLFW/glfw3.h>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <thread>
#include <chrono>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stb_image.h>
#include <math.h>
#include "Instance.h"
#include "Device.h"
#include "Surface.h"
#include "Swapchain.h"
#include "Shader.h"
#include "Framebuffer.h"
#include "RenderPass.h"
#include "CmdBuffer.h"
#include "Synchronization.h"
#include "Flags.h"
#include "Buffer.h"
#include "Image.h"
#include "MemoryManager.h"
#include "Window.h"
#include "DescriptorPool.h"
#include "ImageView.h"
#include "Sampler.h"
#include "FormatInfo.h"
#include "CmdPool.h"
#include "PipelineCache.h"

using namespace std::chrono_literals;
namespace fs = std::filesystem;
using namespace vg;
bool recreateFramebuffer = false;

struct Vertex
{
    glm::vec3 position;
    glm::vec3 color;
    glm::vec2 texCoord;

    static VertexBinding& getBindingDescription()
    {
        static VertexBinding bindingDescription(0, sizeof(Vertex));

        return bindingDescription;
    }
    static std::vector<VertexAttribute>& getAttributeDescriptions()
    {
        static std::vector<VertexAttribute> attributeDescriptions = {
            VertexAttribute(0,0, Format::RGB32SFLOAT,offsetof(Vertex,position)),
            VertexAttribute(1,0, Format::RGB32SFLOAT,offsetof(Vertex,color)),
            VertexAttribute(2,0, Format::RG32SFLOAT,offsetof(Vertex,texCoord)),
        };

        return attributeDescriptions;
    }
};
const std::vector<Vertex> vertices = {
    {{-0.5f, -0.5f, 0.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
    {{0.5f, -0.5f, 0.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},
    {{0.5f, 0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
    {{-0.5f, 0.5f, 0.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}},

    {{-0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
    {{0.5f, -0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},
    {{0.5f, 0.5f, -0.5f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
    {{-0.5f, 0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}}
};

const std::vector<uint16_t> indices = {
    0, 1, 2, 2, 3, 0,
    4, 5, 6, 6, 7, 4,
};

struct UniformBufferObject
{
    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 proj;
};

int main()
{
    // TO DO: Queue sharing mode in Swapchain
    // TO DO: Optymize amount of code written

    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    // glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
    GLFWwindow* window = glfwCreateWindow(1600, 900, "Vulkan", nullptr, nullptr);
    glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int w, int h) {recreateFramebuffer = true; });

    vg::instance = Instance({ "VK_KHR_surface", "VK_KHR_win32_surface" },
        [](Debug::Severity severity, const char* message) {
            if (severity < Debug::Severity::Warning) return;
            std::cout << message << '\n' << '\n';
        });

    SurfaceHandle windowSurface = Window::CreateWindowSurface(vg::instance, window);

    DeviceFeatures deviceFeatures;
    deviceFeatures.wideLines = true;
    deviceFeatures.logicOp = true;
    deviceFeatures.samplerAnisotropy = true;
    deviceFeatures.sampleRateShading = true;

    Queue generalQueue({ QueueType::General }, 1.0f);
    Queue generalQueue1({ QueueType::General }, 1.0f);

    vg::currentDevice = Device({ &generalQueue,&generalQueue1 }, { "VK_KHR_swapchain" }, deviceFeatures, windowSurface,
        [&deviceFeatures](auto supportedQueues, auto supportedExtensions, auto type, DeviceLimits limits, DeviceFeatures features) {
            return (type == DeviceType::Dedicated) + 1 + (deviceFeatures == features);
        });

    uint32_t msaaSampleCount = std::max(currentDevice.GetProperties().limits.framebufferColorSampleCounts, currentDevice.GetProperties().limits.framebufferDepthSampleCounts);
    msaaSampleCount = (msaaSampleCount >> 1) ^ msaaSampleCount;
    Surface surface(windowSurface, Format::BGRA8SRGB, ColorSpace::SRGBNL);
    int w, h; glfwGetFramebufferSize(window, &w, &h);

    Swapchain swapchain(surface, 2, w, h);

    Image colorImage(swapchain.GetWidth(), swapchain.GetHeight(), surface.GetFormat(), { ImageUsage::ColorAttachment , ImageUsage::TransientAttachment }, 1, 1, ImageTiling::Optimal, ImageLayout::Undefined, msaaSampleCount);
    Image depthImage(swapchain.GetWidth(), swapchain.GetHeight(), { Format::D32SFLOAT,Format::D32SFLOATS8UINT,Format::x8D24UNORMPACK }, { FormatFeature::DepthStencilAttachment }, { ImageUsage::DepthStencilAttachment }, 1, 1, ImageTiling::Optimal, ImageLayout::Undefined, msaaSampleCount);
    Allocate({ &depthImage, &colorImage }, { MemoryProperty::DeviceLocal });
    ImageView colorImageView(colorImage, { ImageAspect::Color });
    ImageView depthImageView(depthImage, { ImageAspect::Depth });

    std::vector<char> cacheData;
    {
        std::ifstream cacheFile("pipelineCache.txt", std::ios_base::binary);
        uint32_t size;
        if (cacheFile.is_open() && (size = fs::file_size("pipelineCache.txt")) != 0)
        {
            cacheData.resize(size);
            cacheFile.read(cacheData.data(), cacheData.size());
        }
    }
    PipelineCache pipelineCache(cacheData);
    Shader vertexShader(ShaderStage::Vertex, "resources/shaders/shader.vert.spv");
    Shader fragmentShader(ShaderStage::Fragment, "resources/shaders/shader.frag.spv");
    RenderPass renderPass(
        {
            Attachment(surface.GetFormat(), ImageLayout::ColorAttachmentOptimal,ImageLayout::Undefined,LoadOp::Clear,StoreOp::Store,LoadOp::DontCare,StoreOp::DontCare,msaaSampleCount),
            Attachment(depthImage.GetFormat(), ImageLayout::DepthStencilAttachmentOptimal,ImageLayout::Undefined,LoadOp::Clear,StoreOp::Store,LoadOp::DontCare,StoreOp::DontCare,msaaSampleCount),
            Attachment(surface.GetFormat(), ImageLayout::PresentSrc)
        },
        {
            Subpass(
                GraphicsPipeline(
                    {{0, DescriptorType::UniformBuffer, 1, ShaderStage::Vertex},
                     {1, DescriptorType::CombinedImageSampler, 1, ShaderStage::Fragment}},
                    {PushConstantRange({ShaderStage::Vertex},0,sizeof(glm::vec3))},
                    {&vertexShader, &fragmentShader},
                    VertexLayout({Vertex::getBindingDescription()},Vertex::getAttributeDescriptions()),
                    InputAssembly(Primitive::Triangles),
                    Tesselation(),
                    ViewportState(Viewport(w, h), Scissor(w, h)),
                    Rasterizer(false, PolygonMode::Fill, CullMode::None),
                    Multisampling(msaaSampleCount,true),
                    DepthStencil(true,true,CompareOp::Less),
                    ColorBlending(true, LogicOp::Copy, { 0,0,0,0 }, {ColorBlend()}),
                    { DynamicState::Viewport, DynamicState::Scissor}
                ),
                {}, {AttachmentReference(0, ImageLayout::ColorAttachmentOptimal)},
                {AttachmentReference(2,ImageLayout::ColorAttachmentOptimal)},
                 AttachmentReference(1, ImageLayout::DepthStencilAttachmentOptimal)
            )
        },
        {
            SubpassDependency(~0, 0, PipelineStage::ColorAttachmentOutput, PipelineStage::ColorAttachmentOutput, 0, Access::ColorAttachmentWrite, {})
        },
        pipelineCache
    );
    std::ofstream("pipelineCache.txt", std::ios_base::binary)
        .write(pipelineCache.GetData().data(), pipelineCache.GetData().size());

    std::vector<Framebuffer> swapChainFramebuffers;
    swapChainFramebuffers.resize(swapchain.GetImageCount());
    for (int i = 0; i < swapchain.GetImageCount(); i++)
        swapChainFramebuffers[i] = Framebuffer(renderPass, { colorImageView, depthImageView,swapchain.GetImageViews()[i] }, swapchain.GetWidth(), swapchain.GetHeight());

    // Allocate buffer in DeviceLocal memory.
    Buffer vertexBuffer(sizeof(vertices[0]) * vertices.size() + sizeof(indices[0]) * indices.size(), { vg::BufferUsage::VertexBuffer,vg::BufferUsage::IndexBuffer, vg::BufferUsage::TransferDst });
    vg::Allocate({ &vertexBuffer }, { MemoryProperty::DeviceLocal });
    {
        // Allocate staging buffer in HostVisible memory.
        Buffer stagingBuffer(vertexBuffer.GetSize(), vg::BufferUsage::TransferSrc);
        vg::Allocate({ &stagingBuffer }, { MemoryProperty::HostVisible });
        char* data = (char*) stagingBuffer.MapMemory();
        memcpy(data, vertices.data(), sizeof(vertices[0]) * vertices.size());
        memcpy(data + sizeof(vertices[0]) * vertices.size(), indices.data(), sizeof(indices[0]) * indices.size());
        stagingBuffer.UnmapMemory();

        // Copy staging data to vertex buffer
        vg::CmdBuffer(generalQueue).Begin().Append(
            cmd::CopyBuffer(stagingBuffer, vertexBuffer, { BufferCopyRegion {vertexBuffer.GetSize() } })
        ).End().Submit().Await();
    }

    Buffer uniformBuffers(sizeof(UniformBufferObject) * swapchain.GetImageCount(), BufferUsage::UniformBuffer);
    vg::Allocate(&uniformBuffers, { MemoryProperty::HostVisible, MemoryProperty::HostCoherent });
    char* uniformBufferMemory = (char*) uniformBuffers.MapMemory();

    /// Load Image.
    int texWidth, texHeight, texChannels;
    unsigned char* pixels = stbi_load("resources/textures/texture.jpg", &texWidth, &texHeight, &texChannels, STBI_rgb_alpha);

    Image texImage(texWidth, texHeight, Format::RGBA8SRGB, { ImageUsage::TransferDst,ImageUsage::TransferSrc , ImageUsage::Sampled }, -1);
    vg::Allocate(&texImage, { MemoryProperty::DeviceLocal });
    {
        // Upload data to GPU memory
        Buffer texStagingBuffer(texWidth * texHeight * 4, { BufferUsage::TransferSrc });
        vg::Allocate(&texStagingBuffer, { MemoryProperty::HostVisible, MemoryProperty::HostCoherent });
        memcpy(texStagingBuffer.MapMemory(), pixels, texStagingBuffer.GetSize());
        stbi_image_free(pixels);

        vg::CmdBuffer imageCommandBuffer(generalQueue);
        imageCommandBuffer.Begin().Append(
            cmd::PipelineBarier(PipelineStage::TopOfPipe, PipelineStage::Transfer, { {texImage, ImageLayout::TransferDstOptimal, Access::None, Access::TransferWrite, {ImageAspect::Color,0,texImage.GetMipLevels()}} }),
            cmd::CopyBufferToImage(texStagingBuffer, texImage, ImageLayout::TransferDstOptimal, { {0UL,{ImageAspect::Color,0}, {texWidth,texHeight} } })
        );
        texImage.AppendMipmapGenerationCommands(&imageCommandBuffer, texImage.GetMipLevels());
        imageCommandBuffer.Append(
            cmd::PipelineBarier(PipelineStage::Transfer, PipelineStage::FragmentShader, { {texImage, ImageLayout::TransferSrcOptimal, ImageLayout::ShaderReadOnlyOptimal, Access::TransferWrite, Access::ShaderRead,{ImageAspect::Color,0,texImage.GetMipLevels()}} })
        ).End().Submit().Await();
    }
    ImageView imageView(texImage, { ImageAspect::Color ,0,texImage.GetMipLevels() });
    Sampler sampler(currentDevice.GetProperties().limits.maxSamplerAnisotropy, Filter::Linear, Filter::Linear);

    // Create descriptor pools
    DescriptorPool descriptorPool(swapchain.GetImageCount(), {
        {DescriptorType::UniformBuffer, swapchain.GetImageCount()},
        {DescriptorType::CombinedImageSampler, swapchain.GetImageCount()}
        });

    // Create and allocate descriptor set layouts.
    std::vector<vg::DescriptorSetLayoutHandle> layouts(swapchain.GetImageCount(), renderPass.GetPipelineLayouts()[0].GetDescriptorSets()[0]);
    auto descriptorSets = descriptorPool.Allocate(layouts);

    uint64_t offsetAlignment = currentDevice.GetProperties().limits.minUniformBufferOffsetAlignment;
    for (size_t i = 0; i < descriptorSets.size(); i++)
    {
        descriptorSets[i].AttachBuffer(DescriptorType::UniformBuffer, uniformBuffers, (sizeof(UniformBufferObject) * i / offsetAlignment) * offsetAlignment, sizeof(UniformBufferObject), 0, 0);
        descriptorSets[i].AttachImage(DescriptorType::CombinedImageSampler, ImageLayout::ShaderReadOnlyOptimal, imageView, sampler, 1, 0);
    }

    CmdBuffer commandBuffer(generalQueue);
    Semaphore renderFinishedSemaphore;
    Semaphore imageAvailableSemaphore;
    Fence inFlightFence(true);
    auto startTime = std::chrono::high_resolution_clock::now();
    while (!glfwWindowShouldClose(window))
    {
        // glfwFocusWindow(window);
        glfwPollEvents();
        if (glfwGetKey(window, GLFW_KEY_ESCAPE)) glfwSetWindowShouldClose(window, true);

        Fence::AwaitAll({ inFlightFence }, true);

        // Swapchain resize.
        Swapchain oldSwapchain;
        if (recreateFramebuffer)
        {
            std::swap(oldSwapchain, swapchain);
            swapchain = Swapchain(surface, 2, w, h, Usage::ColorAttachment, PresentMode::Fifo, CompositeAlpha::Opaque, oldSwapchain);
            colorImage = Image(swapchain.GetWidth(), swapchain.GetHeight(), surface.GetFormat(), { ImageUsage::ColorAttachment , ImageUsage::TransientAttachment }, 1, 1, ImageTiling::Optimal, ImageLayout::Undefined, msaaSampleCount);
            depthImage = Image(swapchain.GetWidth(), swapchain.GetHeight(), depthImage.GetFormat(), { ImageUsage::DepthStencilAttachment }, 1, 1, ImageTiling::Optimal, ImageLayout::Undefined, msaaSampleCount);
            Allocate({ &depthImage, &colorImage }, { MemoryProperty::DeviceLocal });
            colorImageView = ImageView(colorImage, { ImageAspect::Color });
            depthImageView = ImageView(depthImage, { ImageAspect::Depth });
            for (int i = 0; i < swapchain.GetImageCount(); i++)
                swapChainFramebuffers[i] = Framebuffer(renderPass, { colorImageView,depthImageView,swapchain.GetImageViews()[i] }, swapchain.GetWidth(), swapchain.GetHeight());
        }

        uint32_t imageIndex = swapchain.GetNextImageIndex(imageAvailableSemaphore);

        // Update UniformBuffer.
        auto currentTime = std::chrono::high_resolution_clock::now();
        float time = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();
        UniformBufferObject ubo{};
        ubo.model = glm::rotate(glm::mat4(1.0f), glm::radians(40.0f) * time, glm::vec3(0.0f, 0.0f, 1.0f));
        ubo.view = glm::lookAt(glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        ubo.proj = glm::perspective(glm::radians(45.0f), swapchain.GetWidth() / (float) swapchain.GetHeight(), 0.1f, 100.0f);
        ubo.proj[1][1] *= -1;
        memcpy(uniformBufferMemory + imageIndex * sizeof(ubo), &ubo, sizeof(ubo));

        glm::vec3 pos(-2, 0, 0);
        glm::vec3 pos1(0, 0, 0);

        commandBuffer.Clear().Begin().Append(
            cmd::BeginRenderpass(renderPass, swapChainFramebuffers[imageIndex], { 0, 0 }, { swapchain.GetWidth(), swapchain.GetHeight() }, { ClearColor{ 0,0,0,255 },ClearDepthStencil{1.0f,0U},ClearColor{ 0,0,0,255 } }),
            cmd::BindPipeline(renderPass.GetPipelines()[0]),
            cmd::BindDescriptorSets(renderPass.GetPipelineLayouts()[0], PipelineBindPoint::Graphics, 0, { descriptorSets[imageIndex] }),
            cmd::BindVertexBuffer(vertexBuffer, 0),
            cmd::BindIndexBuffer(vertexBuffer, sizeof(vertices[0]) * vertices.size(), IndexType::Uint16),
            cmd::SetViewport(Viewport(swapchain.GetWidth(), swapchain.GetHeight())),
            cmd::SetScissor(Scissor(swapchain.GetWidth(), swapchain.GetHeight())),
            cmd::PushConstants(renderPass.GetPipelineLayouts()[0], { ShaderStage::Vertex }, 0, sizeof(glm::vec3), &pos),
            cmd::DrawIndexed(indices.size()),
            cmd::PushConstants(renderPass.GetPipelineLayouts()[0], { ShaderStage::Vertex }, 0, sizeof(glm::vec3), &pos1),
            cmd::DrawIndexed(indices.size()),
            cmd::EndRenderpass()
        ).End().Submit({ {PipelineStage::ColorAttachmentOutput, imageAvailableSemaphore} }, { renderFinishedSemaphore }, inFlightFence);
        generalQueue.Present({ renderFinishedSemaphore }, { swapchain }, { imageIndex });
    }
    Fence::AwaitAll({ inFlightFence });
    glfwTerminate();
}