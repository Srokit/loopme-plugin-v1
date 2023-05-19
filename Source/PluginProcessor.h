/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/**
*/
class LoopMe_Plugin_V1AudioProcessor  : public juce::AudioProcessor,
                                        public juce::Value::Listener
                            #if JucePlugin_Enable_ARA
                             , public juce::AudioProcessorARAExtension
                            #endif
{
public:
    //==============================================================================
    LoopMe_Plugin_V1AudioProcessor();
    ~LoopMe_Plugin_V1AudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    void valueChanged(juce::Value&) override;
    
    void checkIfBpmChangedAndMaybeUpdate();
    void maybeSetBufferIndexFromPlayhead();
    
    bool doesBeatDifferByAlot(double beat);

private:
    bool _isPlaying = true;
    
    // Will check against this to see if play head bpm has changed in each process block
    double _currHostBpm = -1;
    
    double lastBeat = -1;
    
    static constexpr double SIGNIFICANT_BEAT_CHANGE = 0.5;
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LoopMe_Plugin_V1AudioProcessor)
};
