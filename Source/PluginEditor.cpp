/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

#include "EditorPositions.h"

//==============================================================================
LoopMe_Plugin_V1AudioProcessorEditor::LoopMe_Plugin_V1AudioProcessorEditor (LoopMe_Plugin_V1AudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (loopme::positions::kPluginWidth, loopme::positions::kPluginHeight);
    
    addAndMakeVisible(this->loopInfoAreaComponent);
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
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
