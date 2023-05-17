/*
  ==============================================================================

    curl.h
    Created: 17 May 2023 2:03:46pm
    Author:  Stanley Rokita

  ==============================================================================
*/

#pragma once

#include <string>

namespace lm::data {

void curlLoopFromUrl(const std::string&);

std::string getLoopInfoFromBackend();

} // namespace lm::data
