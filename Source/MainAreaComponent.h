/*
  ==============================================================================

    PluginContainerComponent.h
    Created: 11 May 2023 2:19:56pm
    Author:  Stanley Rokita

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

#include "LoopInfoAreaComponent.h"
#include "WaveformVisualizerComponent.h"

//==============================================================================
/*
*/

namespace lm::ui {

class MainAreaComponent  : public juce::Component {
public:
    MainAreaComponent();

    void resized() override;
    
    // Debug
    void paint(juce::Graphics&) override;

private:

    void initButtons();
    
    LoopInfoAreaComponent _loopInfoAreaComponent;
    WaveformVisualizerComponent _waveformVisComponent;
    
    static constexpr int kLoopInfoAreaHeight = 125;
    static constexpr int kWaveformCompHeight = 250;
    static constexpr int kPlayButtonWidth = 100;
    static constexpr int kPlayButtonHeight = 100;
    
    juce::ImageButton _playButton;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainAreaComponent)
};

} // namespace lm::ui
