#pragma once

#include <vulkan_wrapper.h>
#include <vulkan/vulkan.h>

#include <cstdint>
#include <vector>

namespace dp
{
namespace vulkan
{
class Layers
{
public:
  explicit Layers(bool enableDiagnostics);

  // These method are available before initialization.
  uint32_t GetInstanceLayersCount() const;
  char const * const * GetInstanceLayers() const;
  uint32_t GetInstanceExtensionsCount() const;
  char const * const * GetInstanceExtensions() const;

  bool Initialize(VkInstance instance, VkPhysicalDevice physicalDevice);
  void Uninitialize(VkInstance instance);

  // These method are available after initialization.
  uint32_t GetDeviceLayersCount() const;
  char const * const * GetDeviceLayers() const;
  uint32_t GetDeviceExtensionsCount() const;
  char const * const * GetDeviceExtensions() const;

private:
  bool const m_enableDiagnostics;

  std::vector<char const *> m_instanceLayers;
  std::vector<char const *> m_instanceExtensions;

  std::vector<char const *> m_deviceLayers;
  std::vector<char const *> m_deviceExtensions;

  VkDebugReportCallbackEXT m_reportCallback = 0;

  PFN_vkCreateDebugReportCallbackEXT m_vkCreateDebugReportCallbackEXT = nullptr;
  PFN_vkDestroyDebugReportCallbackEXT m_vkDestroyDebugReportCallbackEXT = nullptr;
  PFN_vkDebugReportMessageEXT m_vkDebugReportMessageEXT = nullptr;
};
}  // namespace vulkan
}  // namespace dp
