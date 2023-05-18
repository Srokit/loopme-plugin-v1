/*
  ==============================================================================

    actions.cpp
    Created: 17 May 2023 11:27:39am
    Author:  Stanley Rokita

  ==============================================================================
*/

#include "actions.h"

#include <chrono>
#include <thread>

#include "AppState.h"
#include "DataDownloader.h"
#include "LoopAudioDataMgr.h"

namespace lm::data::actions {
    void toggleIsPlaying() {
        AppState::get().setIsPlaying(!AppState::get().isPlaying());
    }

    void nextLoop() {
        std::string url;
        LoopInfo loopInfo;
        if (!DataDownloader::get().dlNextLoopInfoAndUrl(loopInfo, url)) {
            DBG("Failed to download next loop info and url");
            return;
        }
        if (!DataDownloader::get().dlNextLoopData(url)) {
            DBG("Failed to download next loop data");
            return;
        }

        // Give curl time to finish writing to disk
        std::this_thread::sleep_for(std::chrono::milliseconds(500));

        LoopAudioDataMgr::get().loadFileFromDisk();
        LoopAudioDataMgr::get().resampleBuffer();
        LoopAudioDataMgr::get().resetIndex();
        AppState::get().setLoopInfo(loopInfo);
        AppState::get().nextLoop();
        AppState::get().setHasGottenFirstLoop();
    }

    void updateHostSampleRate(double sampleRate) {
        LoopAudioDataMgr::get().setHostSampleRate(sampleRate);
        LoopAudioDataMgr::get().resampleBuffer();
        LoopAudioDataMgr::get().resetIndex();
    }
}
