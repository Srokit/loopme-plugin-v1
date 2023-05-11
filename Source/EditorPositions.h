/*
  ==============================================================================

    EditorPositions.h
    Created: 10 May 2023 7:52:39pm
    Author:  Stanley Rokita

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

// Constants which determine the positions that things are drawn in the editor

namespace loopme {
namespace positions {

constexpr int kPluginWidth = 800;
constexpr int kPluginHeight = 600;

const juce::Point<int> kNameLabelSize {150, 50};
const juce::Point<int> kTempoLabelSize {50, 50};
const juce::Point<int> kKeyLabelSize {50, 50};

const juce::Rectangle<int> kLoopInfoAreaBounds {50, 50, 700, 200};
}
}
