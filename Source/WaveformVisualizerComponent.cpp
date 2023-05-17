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
    setOpaque(false);
    setColors();
    initWfVisualizer();
    setFramesPerSecond(kFPS);
    data::AppState::get().addListenerIsPlaying(this);
}

void WaveformVisualizerComponent::paint(juce::Graphics& g) {
    g.fillAll(juce::Colours::transparentBlack);
    drawWfRects(g);
}

void WaveformVisualizerComponent::update() {
    _visualizerAggregate.update();
    repaint();
}

void WaveformVisualizerComponent::valueChanged(juce::Value&) {
    if (data::AppState::get().isPlaying()) {
        _visualizerAggregate.resume();
    }
    else {
        _visualizerAggregate.pause();
    }
}

void WaveformVisualizerComponent::setColors() {
    _wfTopColor = juce::Colours::white;
    _wfBotColor = juce::Colour::fromRGB(192, 192, 192);
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
        g.setColour(_wfTopColor);
        g.fillRect(rectLeftX, rectTopY, kRectWidth, rectHeight);
    }
    else {
        int startX = getWidth() / 2 - kWfWidth / 2 + kWfBottomHalfXShift;
        int startY = getHeight() / 2 - kWfHeight / 2 + kWfRectMaxHeightAllowed + kWfMiddleGapSize;
        int rectLeftX = startX + rectIndex * kRectXDelta;
        int rectTopY = startY;
        g.setColour(_wfBotColor);
        g.fillRect(rectLeftX, rectTopY, kRectWidth, rectHeight);
//        g.drawRect(rectLeftX, rectTopY, kRectWidth, rectHeight);
    }
}

} // namespace lm::ui
