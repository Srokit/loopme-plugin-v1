/*
  ==============================================================================

    LoopInfo.h
    Created: 10 May 2023 7:38:29pm
    Author:  Stanley Rokita

  ==============================================================================
*/

#pragma once

#include <string>

namespace loopme {

struct LoopInfo {
    std::string name;
    std::string tempo;
    std::string key;

    LoopInfo() {
        // Default values
        name = "Spontaneous";
        tempo = "105";
        key = "Cm";
    }

    LoopInfo(std::string name, std::string tempo, std::string key): name(name), tempo(tempo), key(key) {}
};

}
