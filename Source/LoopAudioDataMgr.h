/*
  ==============================================================================

    LoopAudioDataMgr.h
    Created: 17 May 2023 1:05:55pm
    Author:  Stanley Rokita

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

#include <mutex>

namespace lm::data {

class LoopAudioDataMgr {
public:
    static LoopAudioDataMgr &get() {
        static LoopAudioDataMgr instance;
        return instance;
    }
    void loadFileFromDisk();
    void setOrigBpm(double origBpm) { _origBpm = origBpm; }
    void setHostBpm(double hostBpm) { _hostBpm = hostBpm; _isHostBpmSet = true; }
    void setHostSampleRate(double sampleRate) { _hostSampleRate = sampleRate; }
    void incIndex();
    float getSample(int channel);
    bool isHostBpmSet() const { return _isHostBpmSet; }
    void resampleBufferAndResetIndex();
    std::unique_lock<std::mutex>&& getScopedResamplingLock() { std::unique_lock<std::mutex> l(_resampledBufferMut); return std::move(l); }
private:

    void convertMp3FileToWavFile();
    void timeStretchFile();
    
    void resampleBuffer();
    void resetIndex();
    
    std::mutex _resampledBufferMut;
    
    juce::AudioBuffer<float> _origSRBuffer;
    juce::AudioBuffer<float> _resampledBuffer;

    double _origSampleRate;
    double _hostSampleRate;
    double _origBpm;
    double _hostBpm;
    
    bool _isHostBpmSet = false;

    int _readIndex = 0;
};

} // namespace lm::data
