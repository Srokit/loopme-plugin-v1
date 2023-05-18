/*
  ==============================================================================

    AppState.h
    Created: 17 May 2023 11:25:47am
    Author:  Stanley Rokita

  ==============================================================================
*/

#pragma once

#include <memory>
#include <vector>

#include <JuceHeader.h>

#include "LoopInfo.h"

namespace lm::data {

class INextLoopCallback {
public:
    virtual void nextLoop() = 0;
};

class AppState {
public:
    static AppState& get() {
        static AppState instance;
        return instance;
    }
    AppState() : _isPlaying(true) {}
    void setIsPlaying(bool isPlaying) {
        this->_isPlaying = isPlaying;
    }
    bool isPlaying() const { return bool(_isPlaying.getValue()); }
    void addListenerIsPlaying(juce::Value::Listener *listener) {
        this->_isPlaying.addListener(listener);
    }

    void setLoopInfo(const LoopInfo& loopInfo) {
        _loopInfo = loopInfo;
    }
    const LoopInfo& loopInfo() const { return _loopInfo; }
    void addListenerNextLoop(INextLoopCallback *cb) {
        _nextLoopCbs.push_back(cb);
    }

    void nextLoop() {
        for (auto *cb : _nextLoopCbs) {
            cb->nextLoop();
        }
    }

    void setHasGottenFirstLoop() {
        _hasGottenFirstLoop = true;
    }
    bool hasGottenFirstLoop() const { return _hasGottenFirstLoop; }

private:
    std::vector<INextLoopCallback*> _nextLoopCbs;
    juce::Value _isPlaying;
    bool _hasGottenFirstLoop = false;
    LoopInfo _loopInfo;
};

} // namespace lm::data
