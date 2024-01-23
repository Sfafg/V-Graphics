#pragma once
#include <iostream>

#ifdef VULKAN_HPP
#define HANDLE(name, nativeName)\
class name : public vk::nativeName\
{\
public:\
    name() :vk::nativeName(nullptr) {}\
    name(const vk::nativeName& o) : vk::nativeName(o) {}\
    name(vk::nativeName&& o) : vk::nativeName(o) {}\
    name& operator=(void*& rhs) { ((vk::nativeName*)this)->operator=((Vk##nativeName)rhs); return *this; }\
    name& operator=(const vk::nativeName& rhs) { ((vk::nativeName*)this)->operator=(rhs); return *this; }\
    bool operator==(const vk::nativeName& rhs) const { return ((vk::nativeName*)this)->operator==(rhs); }\
    bool operator==(const void* rhs) const { return ((vk::nativeName*)this)->operator==((Vk##nativeName)rhs); }\
};
#else
#define HANDLE(name, nativeName)\
class name\
{\
    void* m_handle;\
public:\
    name() :m_handle(nullptr) {}\
    name& operator=(void*& rhs) { m_handle = rhs; return *this; }\
    bool operator==(const void* rhs) const { return  m_handle == rhs; }\
};
#endif


namespace vg
{
    HANDLE(InstanceHandle, Instance);
    HANDLE(DebugMessengerHandle, DebugUtilsMessengerEXT);
    HANDLE(DeviceHandle, Device);
    HANDLE(PhysicalDeviceHandle, PhysicalDevice);
    HANDLE(QueueHandle, Queue);
    HANDLE(SurfaceHandle, SurfaceKHR);
    HANDLE(SwapchainHandle, SwapchainKHR);
    HANDLE(ImageHandle, Image);
    HANDLE(ImageViewHandle, ImageView);
    HANDLE(ShaderHandle, ShaderModule);
    HANDLE(GraphicsPipelineHandle, Pipeline);
    HANDLE(PipelineLayoutHandle, PipelineLayout);
    HANDLE(RenderPassHandle, RenderPass);
    HANDLE(FramebufferHandle, Framebuffer);
    HANDLE(SemaphoreHandle, Semaphore);
    HANDLE(FenceHandle, Fence);
    HANDLE(CommandPoolHandle, CommandPool);
    HANDLE(CommandBufferHandle, CommandBuffer);
}
#undef HANDLE