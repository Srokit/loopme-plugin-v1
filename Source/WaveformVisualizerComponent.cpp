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
    initWfVisualizer();
    setFramesPerSecond(kFPS);
}

void WaveformVisualizerComponent::paint(juce::Graphics& g) {
    g.fillAll(juce::Colours::black);
    drawWfRects(g);
}

void WaveformVisualizerComponent::update() {
    _visualizerAggregate.update();
    repaint();
}

void WaveformVisualizerComponent::initWfVisualizer() {
    _visualizerAggregate.setNumPoints(kNumPoints);
    for (const auto& att : kWfAtts) {
        _visualizerAggregate.addVisualizerWithAttributes(att);
    }
    _visualizerAggregate.resume();
}

void WaveformVisualizerComponent::drawWfRects(juce::Graphics& g) {
    g.setColour(juce::Colours::white);
    for (int rectIndex = 0; rectIndex < _visualizerAggregate.getNumPoints(); rectIndex++) {
        drawSingleWfRectAtIndexAndFacing(g, rectIndex, true);
        drawSingleWfRectAtIndexAndFacing(g, rectIndex, false);
    }
}

void WaveformVisualizerComponent::drawSingleWfRectAtIndexAndFacing(juce::Graphics& g, int rectIndex, bool facingUp) {
    int rectHeight = _visualizerAggregate.getHeightAtIndex(rectIndex);

    if (facingUp) {
        int startX = getWidth() / 2 - kWfWidth / 2;
        int startY = getHeight() / 2 - kWfHeight / 2;
        int rectLeftX = startX + rectIndex * kRectXDelta;
        int rectTopY = startY + (kWfRectMaxHeightAllowed - rectHeight);
        g.drawRect(rectLeftX, rectTopY, kRectWidth, rectHeight);
    }
    else {
        int startX = getWidth() / 2 - kWfWidth / 2;
        int startY = getHeight() / 2 - kWfHeight / 2 + kWfRectMaxHeightAllowed + kWfMiddleGapSize;
        int rectLeftX = startX + rectIndex * kRectXDelta;
        int rectTopY = startY;
        g.drawRect(rectLeftX, rectTopY, kRectWidth, rectHeight);
    }
}

} // namespace lm::ui
