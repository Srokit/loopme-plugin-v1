/*
  ==============================================================================

    AppState.h
    Created: 17 May 2023 11:25:47am
    Author:  Stanley Rokita

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

namespace lm::data {

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
private:
    juce::Value _isPlaying;
};

} // namespace lm::data
