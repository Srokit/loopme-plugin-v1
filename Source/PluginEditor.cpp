/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

#include "AppState.h"
#include "configvals.h"

//==============================================================================
LoopMe_Plugin_V1AudioProcessorEditor::LoopMe_Plugin_V1AudioProcessorEditor (LoopMe_Plugin_V1AudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (lm::config::kPluginWidth, lm::config::kPluginHeight);
    
    addAndMakeVisible(this->_mainAreaComponent);

    lm::data::AppState::get().addListenerNextLoop(this);
}

LoopMe_Plugin_V1AudioProcessorEditor::~LoopMe_Plugin_V1AudioProcessorEditor()
{
}

//==============================================================================
void LoopMe_Plugin_V1AudioProcessorEditor::paint (juce::Graphics& g)
{
    g.drawImageAt(juce::ImageCache::getFromMemory(BinaryData::plugin_bg_png, BinaryData::plugin_bg_pngSize), 0, 0);
}

void LoopMe_Plugin_V1AudioProcessorEditor::resized()
{
    const auto& b = getBounds();
    this->_mainAreaComponent.setBounds(b.getX() + lm::config::kMarginSize, b.getY() + lm::config::kMarginSize, b.getWidth() - lm::config::kMarginSize * 2, b.getHeight() - lm::config::kMarginSize * 2);
}

void LoopMe_Plugin_V1AudioProcessorEditor::nextLoop() {
    // TODO: Change display for loop info
}
