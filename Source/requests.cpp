/*
  ==============================================================================

    curl.cpp
    Created: 17 May 2023 2:04:00pm
    Author:  Stanley Rokita

  ==============================================================================
*/

#include "requests.h"

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
    httplib::Client cli(config::kBackendUrlBase);
    auto res = cli.Get("/loop");
    if (res && res->status == 200) {
        nlohmann::json j = nlohmann::json::parse(res->body);
        return j["url"].get<std::string>();
    } else {
        return "https://loopme-comb-loops.s3.us-west-1.amazonaws.com/LonelyTrkSymphony_142_Gm.mp3";
    }
}

} // namespace lm::data
