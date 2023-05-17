/*
  ==============================================================================

    LoopAudioDataMgr.h
    Created: 17 May 2023 1:05:55pm
    Author:  Stanley Rokita

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

namespace lm::data {

class LoopAudioDataMgr {
public:
    void loadFileFromDisk(juce::String filePath);
    void resampleBuffer(double sampleRate);
    void resetIndex();
    void incIndex();
    float getSample(int channel);
private:
    juce::AudioBuffer<float> _origSRBuffer;
    juce::AudioBuffer<float> _resampledBuffer;

    double _origSampleRate;

    int _readIndex = 0;
};

} // namespace lm::data