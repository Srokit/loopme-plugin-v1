/*
  ==============================================================================

    DataDownloader.cpp
    Created: 18 May 2023 9:28:19am
    Author:  Stanley Rokita

  ==============================================================================
*/

#include "DataDownloader.h"

#include <fstream>

#include "configvals.h"
#include "json.h"

namespace lm::data {

bool DataDownloader::dlNextLoopInfoAndUrl(LoopInfo& loopInfo, std::string& url) {
    // Download loop info from backend as json using system curl command
    std::string curlCommand = "curl " + config::kBackendUrlBase + "loop -o " + config::kLoopInfoJsonFilePath;
    int curlCommandResult = system(curlCommand.c_str());
    if (curlCommandResult != 0) {
        return false;
    }

    // Parse json using nlohmann json library
    std::ifstream loopInfoJsonFile(config::kLoopInfoJsonFilePath);
    nlohmann::json loopInfoJson;
    loopInfoJsonFile >> loopInfoJson;

    // Get loop info from json
    try {
        loopInfo = LoopInfo(loopInfoJson["info"]["name"].get<std::string>(),
                            loopInfoJson["info"]["tempo"].get<std::string>(),
                            loopInfoJson["info"]["key"].get<std::string>());
    } catch (nlohmann::json::exception& e) {
        return false;
    }

    url = loopInfoJson["url"].get<std::string>();
    return true;
}

bool DataDownloader::dlNextLoopData(const std::string& url) {
    // Download loop data from backend using system curl command
    std::string curlCommand = "curl " + url + " -o " + config::kLoopDataFilePath;
    int curlCommandResult = system(curlCommand.c_str());
    if (curlCommandResult != 0) {
        return false;
    }
    return true;
}

} // namespace lm::data