/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

#include <chrono>
#include <thread>

#include "requests.h"

//==============================================================================
LoopMe_Plugin_V1AudioProcessor::LoopMe_Plugin_V1AudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
}

LoopMe_Plugin_V1AudioProcessor::~LoopMe_Plugin_V1AudioProcessor()
{
}

//==============================================================================
const juce::String LoopMe_Plugin_V1AudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool LoopMe_Plugin_V1AudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool LoopMe_Plugin_V1AudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool LoopMe_Plugin_V1AudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double LoopMe_Plugin_V1AudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int LoopMe_Plugin_V1AudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int LoopMe_Plugin_V1AudioProcessor::getCurrentProgram()
{
    return 0;
}

void LoopMe_Plugin_V1AudioProcessor::setCurrentProgram (int index)
{
}

const juce::String LoopMe_Plugin_V1AudioProcessor::getProgramName (int index)
{
    return {};
}

void LoopMe_Plugin_V1AudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void LoopMe_Plugin_V1AudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    this->_sampleRate = sampleRate;
    nextLoop();
}

void LoopMe_Plugin_V1AudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool LoopMe_Plugin_V1AudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void LoopMe_Plugin_V1AudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    if (!this->_isPlaying) {
        buffer.clear();
        return;
    }

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    for (int sample = 0; sample < buffer.getNumSamples(); ++sample) {

        for (int channel = 0; channel < totalNumOutputChannels; ++channel)
        {
            auto* channelData = buffer.getWritePointer (channel);
            channelData[sample] = _loopAudioDataMgr.getSample(channel);
        }
        _loopAudioDataMgr.incIndex();
    }
}

//==============================================================================
bool LoopMe_Plugin_V1AudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* LoopMe_Plugin_V1AudioProcessor::createEditor()
{
    return new LoopMe_Plugin_V1AudioProcessorEditor (*this);
}

//==============================================================================
void LoopMe_Plugin_V1AudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void LoopMe_Plugin_V1AudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

void LoopMe_Plugin_V1AudioProcessor::nextLoop() {
    std::string url = lm::data::getLoopInfoFromBackend();
    lm::data::curlLoopFromUrl(url);
    
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    _loopAudioDataMgr.loadFileFromDisk("/Users/srok/audio.mp3");
    _loopAudioDataMgr.resampleBuffer(this->_sampleRate);
    _loopAudioDataMgr.resetIndex();
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new LoopMe_Plugin_V1AudioProcessor();
}
