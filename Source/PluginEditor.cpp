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
    setSize (800, 600);
}

LoopMe_Plugin_V1AudioProcessorEditor::~LoopMe_Plugin_V1AudioProcessorEditor()
{
}

//==============================================================================
void LoopMe_Plugin_V1AudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.drawImageAt(juce::ImageCache::getFromMemory(BinaryData::plugin_bg_png, BinaryData::plugin_bg_pngSize), 0, 0);
    g.setFont(juce::Font(50.0f));
    g.setColour(juce::Colours::white);
    drawLoopInfoText(g);
}

void LoopMe_Plugin_V1AudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}

void LoopMe_Plugin_V1AudioProcessorEditor::drawLoopInfoText(juce::Graphics& g) {
    // Draw name
    g.drawText(this->loopInfo.name,
               loopme::positions::kNameTextX, loopme::positions::kNameTextY, loopme::positions::kNameTextW, loopme::positions::kNameTextH, juce::Justification(juce::Justification::centred));
}
