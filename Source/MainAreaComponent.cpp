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
}

void MainAreaComponent::resized()
{
    const auto& b = getBounds();
    this->_loopInfoAreaComponent.setSize(b.getWidth(), b.getHeight());
}

void MainAreaComponent::paint(juce::Graphics& g) {
    g.fillAll(juce::Colours::blue);
}

} // namespace lm::ui
