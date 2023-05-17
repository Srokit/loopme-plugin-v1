/*
  ==============================================================================

    curl.cpp
    Created: 17 May 2023 2:04:00pm
    Author:  Stanley Rokita

  ==============================================================================
*/

#include "requests.h"

#include <fstream>

#include <JuceHeader.h>

#include "httplib.h"
#include "json.h"

#include "configvals.h"

namespace lm::data {

void curlLoopFromUrl(const std::string& url) {
    std::string cmd = "curl " + url + " -o /Users/srok/audio.mp3";
    DBG(cmd);
    system(cmd.c_str());
}

std::string getLoopInfoFromBackend() {
    std::string url = config::kBackendUrlBase + "loop";
    std::string cmd = "curl " + url + " -o /Users/srok/json.txt";
    system(cmd.c_str());
    
    std::ifstream f("/Users/srok/json.txt");
    nlohmann::json j = nlohmann::json::parse(f);
    return j["url"].get<std::string>();
}

} // namespace lm::data
