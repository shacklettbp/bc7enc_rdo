#pragma once

#include <omp.h>

enum class BlockFormat {
    BC7,
    BC5,
};

void compress(uint8_t *dst, uint8_t *src, uint32_t width, uint32_t height,
              BlockFormat fmt)
{
    rdo_bc::rdo_bc_params rp;
    rp.rdo_max_threads = std::min(std::max(1, omp_get_max_threads()), 128);
    rp.m_status_output = false;
    rp.m_use_bc7e = true;
    if (fmt == BlockFormat::BC5) {
        rp.m_dxgi_format = DXGI_FORMAT_BC5_UNORM;
    }
    if (fmt == BlockFormat::BC7) {
        rp.m_dxgi_format = DXGI_FORMAT_BC7_UNORM;
    }
    rp.m_rdo_lambda = 1.f;
    rp.m_lookback_window_size = 256;
    rp.m_custom_lookback_window_size = true;

    rdo_bc::rdo_bc_encoder encoder;
}
