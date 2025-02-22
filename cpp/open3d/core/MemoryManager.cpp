// ----------------------------------------------------------------------------
// -                        Open3D: www.open3d.org                            -
// ----------------------------------------------------------------------------
// The MIT License (MIT)
//
// Copyright (c) 2018-2021 www.open3d.org
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
// ----------------------------------------------------------------------------

#include "open3d/core/MemoryManager.h"

#include <numeric>
#include <unordered_map>

#include "open3d/core/Blob.h"
#include "open3d/core/Device.h"
#include "open3d/core/MemoryManagerStatistic.h"
#include "open3d/utility/Helper.h"
#include "open3d/utility/Logging.h"

namespace open3d {
namespace core {

void* MemoryManager::Malloc(size_t byte_size, const Device& device) {
    void* ptr = GetDeviceMemoryManager(device)->Malloc(byte_size, device);
    MemoryManagerStatistic::GetInstance().IncrementCountMalloc(ptr, byte_size,
                                                               device);
    return ptr;
}

void MemoryManager::Free(void* ptr, const Device& device) {
    GetDeviceMemoryManager(device)->Free(ptr, device);
    MemoryManagerStatistic::GetInstance().IncrementCountFree(ptr, device);
}

void MemoryManager::Memcpy(void* dst_ptr,
                           const Device& dst_device,
                           const void* src_ptr,
                           const Device& src_device,
                           size_t num_bytes) {
    // 0-element Tensor's data_ptr_ is nullptr
    if (num_bytes == 0) {
        return;
    } else if (src_ptr == nullptr || dst_ptr == nullptr) {
        utility::LogError("src_ptr and dst_ptr cannot be nullptr.");
    }

    if ((dst_device.GetType() != Device::DeviceType::CPU &&
         dst_device.GetType() != Device::DeviceType::CUDA) ||
        (src_device.GetType() != Device::DeviceType::CPU &&
         src_device.GetType() != Device::DeviceType::CUDA)) {
        utility::LogError("MemoryManager::Memcpy: Unimplemented device.");
    }

    std::shared_ptr<DeviceMemoryManager> device_mm;
    if (dst_device.GetType() == Device::DeviceType::CPU &&
        src_device.GetType() == Device::DeviceType::CPU) {
        device_mm = GetDeviceMemoryManager(src_device);
    } else if (src_device.GetType() == Device::DeviceType::CUDA) {
        device_mm = GetDeviceMemoryManager(src_device);
    } else {
        device_mm = GetDeviceMemoryManager(dst_device);
    }

    device_mm->Memcpy(dst_ptr, dst_device, src_ptr, src_device, num_bytes);
}

void MemoryManager::MemcpyFromHost(void* dst_ptr,
                                   const Device& dst_device,
                                   const void* host_ptr,
                                   size_t num_bytes) {
    // Currently default host is CPU:0
    Memcpy(dst_ptr, dst_device, host_ptr, Device("CPU:0"), num_bytes);
}

void MemoryManager::MemcpyToHost(void* host_ptr,
                                 const void* src_ptr,
                                 const Device& src_device,
                                 size_t num_bytes) {
    // Currently default host is CPU:0
    Memcpy(host_ptr, Device("CPU:0"), src_ptr, src_device, num_bytes);
}

std::shared_ptr<DeviceMemoryManager> MemoryManager::GetDeviceMemoryManager(
        const Device& device) {
    static std::unordered_map<Device::DeviceType,
                              std::shared_ptr<DeviceMemoryManager>,
                              utility::hash_enum_class>
            map_device_type_to_memory_manager = {
                    {Device::DeviceType::CPU,
                     std::make_shared<CPUMemoryManager>()},
#ifdef BUILD_CUDA_MODULE
#ifdef BUILD_CACHED_CUDA_MANAGER
                    {Device::DeviceType::CUDA,
                     std::make_shared<CUDACachedMemoryManager>()},
#else
                    {Device::DeviceType::CUDA,
                     std::make_shared<CUDASimpleMemoryManager>()},
#endif  // BUILD_CACHED_CUDA_MANAGER
#endif  // BUILD_CUDA_MODULE
            };
    if (map_device_type_to_memory_manager.find(device.GetType()) ==
        map_device_type_to_memory_manager.end()) {
        utility::LogError("Unimplemented device '{}'.", device.ToString());
    }
    return map_device_type_to_memory_manager.at(device.GetType());
}

}  // namespace core
}  // namespace open3d
