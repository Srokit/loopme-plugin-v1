/*
  ==============================================================================

    PluginContainerComponent.h
    Created: 11 May 2023 2:19:56pm
    Author:  Stanley Rokita

  ==============================================================================
*/

#pragma once

#include <memory>

#include <JuceHeader.h>

#include "actions.h"
#include "LoopInfoAreaComponent.h"
#include "WaveformVisualizerComponent.h"

//==============================================================================
/*
*/

namespace lm::ui {

class MainAreaComponent  : public juce::Component,
                           public juce::Button::Listener,
                           public juce::Value::Listener {
public:
    MainAreaComponent();

    void resized() override;
    
    // Debug
    void paint(juce::Graphics&) override;

    void buttonClicked(juce::Button* button) override {
        if (button == &this->_playButton) {
            data::actions::toggleIsPlaying();
        }
    }

    void valueChanged(juce::Value&) override;

private:

    void initImages();
    void initButtons();

    void setImageIsPlaying(bool isPlaying);
    
    LoopInfoAreaComponent _loopInfoAreaComponent;
    WaveformVisualizerComponent _waveformVisComponent;
                               
    std::unique_ptr<juce::Image> _playingImg;
    std::unique_ptr<juce::Image> _pausedImg;

    static constexpr int kLoopInfoAreaHeight = 125;
    static constexpr int kWaveformCompHeight = 250;
    static constexpr int kPlayButtonWidth = 100;
    static constexpr int kPlayButtonHeight = 100;
    
    juce::ImageButton _playButton;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainAreaComponent)
};

} // namespace lm::ui
