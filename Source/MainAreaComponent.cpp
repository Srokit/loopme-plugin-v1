/*
  ==============================================================================

    PluginContainerComponent.cpp
    Created: 11 May 2023 2:19:56pm
    Author:  Stanley Rokita

  ==============================================================================
*/

#include <JuceHeader.h>
#include "MainAreaComponent.h"

#include "actions.h"
#include "AppState.h"
#include "configvals.h"

namespace lm::ui {

MainAreaComponent::MainAreaComponent()
{
    addAndMakeVisible(this->_loopInfoAreaComponent);
    addAndMakeVisible(this->_waveformVisComponent);
    addAndMakeVisible(this->_playButton);
    initImages();
    initButtons();
    addAndMakeVisible(this->_nextButton);
}

void MainAreaComponent::resized()
{
    const auto& b = getBounds();
    this->_loopInfoAreaComponent.setSize(b.getWidth(), kLoopInfoAreaHeight);
    this->_waveformVisComponent.setBounds(0, kLoopInfoAreaHeight, b.getWidth(), kWaveformCompHeight);
    this->_playButton.setBounds(b.getWidth() / 2 - kPlayButtonWidth / 2, b.getHeight() / 2 - kPlayButtonHeight / 2, kPlayButtonWidth, kPlayButtonHeight);
    this->_nextButton.setBounds(b.getWidth() / 2 - kNextButtonWidth / 2, kNextButtonY, kNextButtonWidth, kNextButtonHeight);
}

void MainAreaComponent::paint(juce::Graphics& g) {
//    g.fillAll(juce::Colours::blue);
}

void MainAreaComponent::valueChanged(juce::Value&) {
    setImageIsPlaying(data::AppState::get().isPlaying());
}

void MainAreaComponent::initImages() {
    _playingImg = std::make_unique<juce::Image>(juce::ImageCache::getFromMemory(BinaryData::pause_button_100_png, BinaryData::pause_button_100_pngSize));
    _pausedImg = std::make_unique<juce::Image>(juce::ImageCache::getFromMemory(BinaryData::play_button_100_png, BinaryData::play_button_100_pngSize));
}

void MainAreaComponent::initButtons() {
    this->_playButton.setImages(true, true, true,
                                *_playingImg, 1.0f, juce::Colours::transparentBlack, *_playingImg, 1.0f,
                                juce::Colours::transparentBlack, *_playingImg,
                                1.0f, juce::Colours::transparentBlack);
    this->_playButton.addListener(this);
    data::AppState::get().addListenerIsPlaying(this);
    this->_nextButton.addListener(this);
    this->_nextButton.setButtonText("Next");
    this->_nextButton.setColour(juce::TextButton::buttonColourId, juce::Colours::black);
}

void MainAreaComponent::setImageIsPlaying(bool isPlaying) {
    juce::Image &img = (isPlaying) ? *_playingImg : *_pausedImg;
    this->_playButton.setImages(true, true, true,
                                img, 1.0f, juce::Colours::transparentBlack, img, 1.0f,
                                juce::Colours::transparentBlack, img,
                                1.0f, juce::Colours::transparentBlack);
}

} // namespace lm::ui
