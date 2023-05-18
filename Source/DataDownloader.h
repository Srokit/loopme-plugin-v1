/*
  ==============================================================================

    DataDownloader.h
    Created: 18 May 2023 9:28:19am
    Author:  Stanley Rokita

  ==============================================================================
*/

#pragma once

#include <string>

#include "LoopInfo.h"

namespace lm::data {

class DataDownloader {
public:
    static DataDownloader& get() {
        static DataDownloader instance;
        return instance;
    }

    bool dlNextLoopInfoAndUrl(LoopInfo& loopInfo, std::string& url);
    bool dlNextLoopData(const std::string& url);
};

} // namespace lm::data
