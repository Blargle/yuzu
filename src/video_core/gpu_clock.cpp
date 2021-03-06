// Copyright 2019 yuzu Emulator Project
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#include "common/uint128.h"
#include "video_core/gpu_clock.h"

namespace Tegra {

GPUClock::GPUClock() = default;
GPUClock::~GPUClock() = default;

u64 GPUClock::GetTicks() const {
    constexpr u32 ns_per_second = 1000000000U;
    const u64 ns = GetNsTime().count();
    const u128 middle = Common::Multiply64Into128(ns, gpu_clock);
    return Common::Divide128On32(middle, ns_per_second).first;
}

} // namespace Tegra
