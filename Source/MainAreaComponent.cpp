/*
  ==============================================================================

    PluginContainerComponent.cpp
    Created: 11 May 2023 2:19:56pm
    Author:  Stanley Rokita

  ==============================================================================
*/

#include <JuceHeader.h>
#include "MainAreaComponent.h"

#include "configvals.h"

namespace lm::ui {

MainAreaComponent::MainAreaComponent()
{
    addAndMakeVisible(this->_loopInfoAreaComponent);
    addAndMakeVisible(this->_waveformVisComponent);
}

void MainAreaComponent::resized()
{
    const auto& b = getBounds();
    this->_loopInfoAreaComponent.setSize(b.getWidth(), b.getHeight() / 5);
    this->_waveformVisComponent.setBounds(0, b.getHeight() / 5, b.getWidth(), b.getHeight() * 4 / 5);
}

void MainAreaComponent::paint(juce::Graphics& g) {
    g.fillAll(juce::Colours::blue);
}

} // namespace lm::ui
