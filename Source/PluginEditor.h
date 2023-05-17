/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

#include "AppState.h"

#include "MainAreaComponent.h"

//==============================================================================
/**
*/
class LoopMe_Plugin_V1AudioProcessorEditor  : public juce::AudioProcessorEditor,
                                              public juce::Value::Listener,
                                              public lm::data::INextLoopCallback
{
public:
    LoopMe_Plugin_V1AudioProcessorEditor (LoopMe_Plugin_V1AudioProcessor&);
    ~LoopMe_Plugin_V1AudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

    void valueChanged(juce::Value& value) override;

    void nextLoop() override;

private:

    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    LoopMe_Plugin_V1AudioProcessor& audioProcessor;

    lm::ui::MainAreaComponent _mainAreaComponent;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LoopMe_Plugin_V1AudioProcessorEditor)
};
