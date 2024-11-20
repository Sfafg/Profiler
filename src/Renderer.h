#pragma once
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <GLFW/glfw3.h>
#include <iostream>
#include <chrono>
#include <thread>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <math.h>
#include "vulkan/vulkan.hpp"
#include "VG/VG.h"

#include "imgui/imconfig.h"
#include "imgui/imgui_internal.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_vulkan.h"

#include "implot/implot.h"
#include "implot/implot_internal.h"

using namespace std::chrono_literals;
using namespace vg;

namespace Renderer
{
    inline bool recreateFramebuffer = false;
    inline GLFWwindow* window;
    inline uint32_t currentFrame = 0;
    inline uint32_t imageIndex = 0;
    inline int w = 1920;
    inline int h = 1080;
    inline int x = INT_MAX;
    inline int y = INT_MAX;
    inline int prevW = 1920;
    inline int prevH = 1080;
    inline int prevX = 0;
    inline int prevY = 0;
    inline bool isMaximized = false;
    inline SurfaceHandle windowSurface;
    inline Queue generalQueue;
    inline Device rendererDevice;
    inline Surface surface;
    inline Swapchain swapchain;
    inline RenderPassHandle renderPass;
    inline std::vector<Framebuffer> swapChainFramebuffers;
    inline DescriptorPool descriptorPool;
    inline std::vector<CmdBuffer> commandBuffer;
    inline std::vector<Semaphore> renderFinishedSemaphore;
    inline std::vector<Semaphore> imageAvailableSemaphore;
    inline std::vector<Fence> inFlightFence;

    inline void Init()
    {
        glfwInit();
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        window = glfwCreateWindow(w, h, "Profiler", nullptr, nullptr);
        if (x != INT_MAX && y != INT_MAX)
            glfwSetWindowPos(window, x, y);

        if (isMaximized)
        {
            int x, y;
            glfwGetWindowPos(window, &x, &y);
            GLFWmonitor* closest = nullptr;
            int count;
            GLFWmonitor** monitors = glfwGetMonitors(&count);
            int minDist = INT_MAX;
            for (int i = 0; i < count; i++)
            {
                int xPos, yPos;
                glfwGetMonitorPos(monitors[i], &xPos, &yPos);
                int dist = INT_MAX;
                if (x >= xPos)
                    dist = x - xPos;

                if (dist <= minDist)
                {
                    closest = monitors[i];
                    minDist = dist;
                }
            }
            const GLFWvidmode* mode = glfwGetVideoMode(closest);

            glfwSetWindowAttrib(window, GLFW_DECORATED, GLFW_FALSE);
            glfwSetWindowAttrib(window, GLFW_RESIZABLE, GLFW_FALSE);
            glfwSetWindowSize(window, mode->width, mode->height);
            glfwGetMonitorPos(closest, &x, &y);
            glfwSetWindowPos(window, x, y);
        }
        glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int w, int h) {recreateFramebuffer = true; });
        int w, h; glfwGetFramebufferSize(window, &w, &h);

        vg::instance = Instance({ "VK_KHR_surface", "VK_KHR_win32_surface" },
            [](MessageSeverity severity, const char* message) {
                if (severity < MessageSeverity::Warning) return;
                std::cout << message << '\n' << '\n';
            }, true);

        windowSurface = Window::CreateWindowSurface(vg::instance, window);
        DeviceFeatures deviceFeatures({ Feature::WideLines,Feature::LogicOp,Feature::SamplerAnisotropy,Feature::SampleRateShading });
        generalQueue = Queue({ QueueType::General }, 1.0f);
        rendererDevice = Device({ &generalQueue }, { "VK_KHR_swapchain" }, deviceFeatures, windowSurface,
            [](auto id, auto supportedQueues, auto supportedExtensions, auto type, DeviceLimits limits, DeviceFeatures features) {
                return (type == DeviceType::Integrated);
            });
        vg::currentDevice = &rendererDevice;

        surface = Surface(windowSurface, { Format::BGRA8UNORM, ColorSpace::SRGBNL });
        swapchain = Swapchain(surface, 2, w, h);

        Attachment a(surface.GetFormat(), ImageLayout::PresentSrc);
        vk::AttachmentDescription attachment = *(vk::AttachmentDescription*) &a;
        std::vector<vk::AttachmentDescription> colorAttachments = { attachment };
        std::vector<vk::AttachmentReference> refs = { vk::AttachmentReference(0, vk::ImageLayout::eColorAttachmentOptimal) };
        std::vector <vk::SubpassDescription> subpassDescriptions{
            vk::SubpassDescription({},vk::PipelineBindPoint::eGraphics, {},
                refs,{}, nullptr, {}
            )
        };
        std::vector<SubpassDependency> dependencies = { SubpassDependency(-1, 0, PipelineStage::ColorAttachmentOutput, PipelineStage::ColorAttachmentOutput, 0, Access::ColorAttachmentWrite, {}) };

        vk::RenderPassCreateInfo renderPassInfo({}, colorAttachments, subpassDescriptions, *(std::vector<vk::SubpassDependency>*) & dependencies);
        vg::DeviceHandle handle = *currentDevice;
        vk::Device device = *(vk::Device*) &handle;
        vk::RenderPass temp = device.createRenderPass(renderPassInfo);
        renderPass = *(RenderPassHandle*) &temp;

        swapChainFramebuffers.resize(swapchain.GetImageCount());
        for (int i = 0; i < swapchain.GetImageCount(); i++)
            swapChainFramebuffers[i] = Framebuffer(renderPass, { swapchain.GetImageViews()[i] }, swapchain.GetWidth(), swapchain.GetHeight());

        descriptorPool = DescriptorPool(swapchain.GetImageCount(), { {DescriptorType::CombinedImageSampler, swapchain.GetImageCount()} });

        commandBuffer = std::vector<CmdBuffer>(swapchain.GetImageCount());
        renderFinishedSemaphore = std::vector<Semaphore>(swapchain.GetImageCount());
        imageAvailableSemaphore = std::vector<Semaphore>(swapchain.GetImageCount());
        inFlightFence = std::vector<Fence>(swapchain.GetImageCount());
        for (int i = 0; i < swapchain.GetImageCount(); i++)
        {
            commandBuffer[i] = CmdBuffer(generalQueue);
            renderFinishedSemaphore[i] = Semaphore();
            imageAvailableSemaphore[i] = Semaphore();
            inFlightFence[i] = Fence(true);
        }

        // Init ImGUI
        ImGui::CreateContext();
        ImPlot::CreateContext();
        ImGui::GetIO().IniFilename = nullptr;
        ImGui::GetIO().LogFilename = nullptr;
        ImGui_ImplGlfw_InitForVulkan(window, true);
        ImGui_ImplVulkan_InitInfo info{};
        PhysicalDeviceHandle physicalDevice = *currentDevice;
        info.DescriptorPool = *(VkDescriptorPool*) &(DescriptorPoolHandle&) descriptorPool;
        info.RenderPass = *(VkRenderPass*) &(RenderPassHandle&) renderPass;
        info.Device = *(VkDevice*) &(DeviceHandle&) *currentDevice;
        info.PhysicalDevice = *(VkPhysicalDevice*) &physicalDevice;
        info.Instance = *(VkInstance*) &(InstanceHandle&) vg::instance;
        info.Queue = *(VkQueue*) &(QueueHandle&) generalQueue;
        info.MinImageCount = 2;
        info.ImageCount = swapchain.GetImageCount();
        info.MSAASamples = (VkSampleCountFlagBits) 1;

        ImGui_ImplVulkan_Init(&info);
        ImGui_ImplVulkan_CreateFontsTexture();
    }
    inline void StartFrame()
    {
        glfwPollEvents();
        if (glfwGetKey(window, GLFW_KEY_ESCAPE)) glfwSetWindowShouldClose(window, true);

        static bool released = true;
        if (glfwGetKey(window, GLFW_KEY_F11))
        {
            if (released)
            {
                released = false;
                isMaximized = !isMaximized;
                if (isMaximized)
                {
                    int x, y;
                    glfwGetWindowPos(window, &x, &y);
                    GLFWmonitor* closest = nullptr;
                    int count;
                    GLFWmonitor** monitors = glfwGetMonitors(&count);
                    int minDist = INT_MAX;
                    for (int i = 0; i < count; i++)
                    {
                        int xPos, yPos;
                        glfwGetMonitorPos(monitors[i], &xPos, &yPos);
                        int dist = INT_MAX;
                        if (x >= xPos)
                            dist = x - xPos;

                        if (dist <= minDist)
                        {
                            closest = monitors[i];
                            minDist = dist;
                        }
                    }
                    const GLFWvidmode* mode = glfwGetVideoMode(closest);

                    glfwGetWindowSize(window, &prevW, &prevH);
                    glfwGetWindowPos(window, &prevX, &prevY);
                    glfwSetWindowAttrib(window, GLFW_DECORATED, GLFW_FALSE);
                    glfwSetWindowAttrib(window, GLFW_RESIZABLE, GLFW_FALSE);
                    glfwSetWindowSize(window, mode->width, mode->height);
                    glfwGetMonitorPos(closest, &x, &y);
                    glfwSetWindowPos(window, x, y);
                }
                else
                {
                    glfwSetWindowAttrib(window, GLFW_DECORATED, GLFW_TRUE);
                    glfwSetWindowAttrib(window, GLFW_RESIZABLE, GLFW_TRUE);
                    glfwSetWindowSize(window, prevW, prevH);
                    glfwSetWindowPos(window, prevX, prevY);
                }
            }
        }
        else released = true;
        glfwGetWindowPos(window, &x, &y);
        glfwGetWindowSize(window, &w, &h);

        while (!inFlightFence[currentFrame].IsSignaled())
            std::this_thread::sleep_for(1ms);
        inFlightFence[currentFrame].Reset();

        Swapchain oldSwapchain;
        if (recreateFramebuffer)
        {
            currentDevice->WaitUntilIdle();
            recreateFramebuffer = false;
            glfwGetFramebufferSize(window, &w, &h);
            while (w == 0 || h == 0)
            {
                glfwGetFramebufferSize(window, &w, &h);
                glfwWaitEvents();
            }
            std::swap(oldSwapchain, swapchain);
            swapchain = Swapchain(surface, 2, w, h, oldSwapchain);
            for (int i = 0; i < swapchain.GetImageCount(); i++)
                swapChainFramebuffers[i] = Framebuffer(renderPass, { swapchain.GetImageViews()[i] }, swapchain.GetWidth(), swapchain.GetHeight());
        }
        auto [imageIndex_, result] = swapchain.GetNextImageIndex(imageAvailableSemaphore[currentFrame]);
        imageIndex = imageIndex_;

        RenderPass temp;
        cmd::BeginRenderpass beginRenderPass(temp, swapChainFramebuffers[imageIndex], { 0, 0 }, { swapchain.GetWidth(), swapchain.GetHeight() }, { ClearColor{ 0,0,0,255 } }, SubpassContents::Inline);
        beginRenderPass.renderpass = renderPass;
        commandBuffer[currentFrame].Clear().Begin().Append(
            std::move(beginRenderPass)
        );

        ImGui_ImplVulkan_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    inline void EndFrame()
    {
        ImGui::Render();
        ImGui_ImplVulkan_RenderDrawData(ImGui::GetDrawData(), *(VkCommandBuffer*) &(CmdBufferHandle&) commandBuffer[currentFrame], 0);

        commandBuffer[currentFrame].Append(
            cmd::EndRenderpass()
        ).End().Submit({ {PipelineStage::ColorAttachmentOutput, imageAvailableSemaphore[currentFrame]} }, { renderFinishedSemaphore[currentFrame] }, inFlightFence[currentFrame]);
        generalQueue.Present({ renderFinishedSemaphore[currentFrame] }, { swapchain }, { imageIndex });

        currentFrame = (currentFrame + 1) % swapchain.GetImageCount();
    }

    inline void Quit()
    {
        Fence::AwaitAll(inFlightFence);
        ImGui_ImplVulkan_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImPlot::DestroyContext();
        ImGui::DestroyContext();
        vg::DeviceHandle handle = *currentDevice;
        vk::Device device = *(vk::Device*) &handle;
        device.destroyRenderPass(*(vk::RenderPass*) &renderPass);
        glfwTerminate();
    }
};