/*
  ==============================================================================

    WaveformVisualizerComponent.cpp
    Created: 12 May 2023 5:29:15pm
    Author:  Stanley Rokita

  ==============================================================================
*/

#include "WaveformVisualizerComponent.h"

#include <cmath>

namespace lm::ui {

WaveformVisualizerComponent::WaveformVisualizerComponent() {
    wf::WaveformVisualizerAttributes atts;
    atts.minHeight = 10;
    atts.maxHeight = 100;
    atts.numPoints = 100;
    atts.initWaveFrequency = 4;
    atts.movementFrequency = 2;
    _oscilator = std::make_unique<wf::WaveformVisualizer>(atts);
    _numWfPoints = atts.numPoints;
    setFramesPerSecond(FPS);
    _oscilator->resume();
}

void WaveformVisualizerComponent::paint(juce::Graphics& g) {
    g.fillAll(juce::Colours::black);
    g.setColour(juce::Colours::white);
    int xDelta = 2;
    int startX = getWidth() / 2 - 100;
    int startY = getHeight() / 2;
    for (int i = 0; i < _numWfPoints; i++) {
        // Draw line with height determined by ocilator. Then move right by xDelta.
        int height = _oscilator->getHeight(i);
        g.drawLine(startX + i * xDelta, startY, startX + i * xDelta, startY + height);
        g.drawLine(startX + i * xDelta + 1, startY - 1, startX + i * xDelta + 1, startY - height - 1);
    }
}

void WaveformVisualizerComponent::update() {
    _oscilator->update();
    repaint();
}

} // namespace lm::ui
