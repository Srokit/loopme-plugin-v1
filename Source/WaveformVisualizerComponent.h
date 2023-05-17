/*
  ==============================================================================

    WaveformVisualizerComponent.h
    Created: 12 May 2023 5:29:15pm
    Author:  Stanley Rokita

  ==============================================================================
*/

#pragma once

#include <array>
#include <memory>

#include <JuceHeader.h>

#include "AppState.h"
#include "WaveformVisualizerAggregate.h"

namespace lm::ui {

class WaveformVisualizerComponent : public juce::AnimatedAppComponent,
                                    public juce::Value::Listener {
public:
    WaveformVisualizerComponent();
    void paint(juce::Graphics&) override;
    void update() override;

    void valueChanged(juce::Value&) override;
private:
    /*
     * Configure these constants to change compoenent
     */
    static constexpr int kFPS = 60;
    static constexpr int kNumPoints = 100;
    static constexpr int kRectGapSize = 4;
    static constexpr int kRectWidth = 3;
    static constexpr int kWfHeight = 200;
    // Space left above and below where actual rects are drawn
    static constexpr int kWfYBorderSize = 2;
    // Size of the gap running horizontally down the middle of wf
    static constexpr int kWfMiddleGapSize = 4;
    static constexpr int kWfBottomHalfXShift = 2;
    
    // Colourscheme of visualizer
    juce::Colour _wfTopColor;
    juce::Colour _wfBotColor;
    /*
     * END configure these constants to change component
     */

    /*
     * Calculated from above values
     */
    static constexpr int kRectXDelta = kRectWidth + kRectGapSize;
    static constexpr int kWfWidth = kRectXDelta * kNumPoints;
    // Set the max height of tallest visualizer to this value
    static constexpr int kWfRectMaxHeightAllowed = (kWfHeight - kWfYBorderSize - kWfMiddleGapSize) / 2;
    /*
     * END calculated from above values
     */

    static constexpr std::array<wf::WaveformVisualizerAggregateAttributes, 3> kWfAtts {
        wf::WaveformVisualizerAggregateAttributes{
            .minHeight = 30,
            .maxHeight = kWfRectMaxHeightAllowed,
            .initWaveFrequency = 4,
            .movementFrequency = 2,
        },
        wf::WaveformVisualizerAggregateAttributes{
            .minHeight = 0,
            .maxHeight = 15,
            .initWaveFrequency = 30,
            .movementFrequency = 5,
        },
        wf::WaveformVisualizerAggregateAttributes{
            .minHeight = 0,
            .maxHeight = 4,
            .initWaveFrequency = 100,
            .movementFrequency = 10,
        },
    };
    
    void setColors();
    void initWfVisualizer();
    void drawWfRects(juce::Graphics&);
    void drawSingleWfRectAtIndexAndFacing(juce::Graphics&, int, bool);

    wf::WaveformVisualizerAggregate _visualizerAggregate;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(WaveformVisualizerComponent)
};

} // namespace lm::ui
