/*
  ==============================================================================

    WaveformVisualizerComponent.h
    Created: 12 May 2023 5:29:15pm
    Author:  Stanley Rokita

  ==============================================================================
*/

#pragma once

#include <memory>

#include <JuceHeader.h>

#include "WaveformVisualizer.h"

namespace lm::ui {

class WaveformVisualizerComponent : public juce::AnimatedAppComponent {
public:
    WaveformVisualizerComponent();
    void paint(juce::Graphics&) override;
    void update() override;
private:
    static constexpr int FPS = 30;
    static constexpr float MOVE_FREQ = 1;
    static constexpr float RADIUS = 50;
    
    int _numWfPoints;
    
    std::unique_ptr<wf::WaveformVisualizer> _oscilator;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(WaveformVisualizerComponent)
};

} // namespace lm::ui
