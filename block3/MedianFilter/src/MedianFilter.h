//
// Created by moonlightnvkz on 20.02.17.
//

#pragma once
#include <string>

bool median_filter(const std::string &input,
                   unsigned aperture_lin_sz,
                   unsigned threshold,
                   const std::string &output);