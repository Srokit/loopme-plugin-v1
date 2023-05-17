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
//    setOpaque(false);
    addAndMakeVisible(this->_loopInfoAreaComponent);
    addAndMakeVisible(this->_waveformVisComponent);
    addAndMakeVisible(this->_playButton);
    initButtons();
}

void MainAreaComponent::resized()
{
    const auto& b = getBounds();
    this->_loopInfoAreaComponent.setSize(b.getWidth(), kLoopInfoAreaHeight);
    this->_waveformVisComponent.setBounds(0, kLoopInfoAreaHeight, b.getWidth(), kWaveformCompHeight);
    this->_playButton.setBounds(b.getWidth() / 2 - kPlayButtonWidth / 2, b.getHeight() / 2 - kPlayButtonHeight / 2, kPlayButtonWidth, kPlayButtonHeight);
}

void MainAreaComponent::paint(juce::Graphics& g) {
//    g.fillAll(juce::Colours::blue);
}

void MainAreaComponent::initButtons() {
    auto img = juce::ImageCache::getFromMemory(BinaryData::play_button_100_png, BinaryData::play_button_100_pngSize);
    this->_playButton.setImages(true, true, true,
                                img, 1.0f, juce::Colours::transparentBlack, img, 1.0f,
                                juce::Colours::transparentBlack, img,
                                1.0f, juce::Colours::transparentBlack);
}

} // namespace lm::ui
