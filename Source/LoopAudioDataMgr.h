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
    void setSampleStartIndexByBeat(double beat);
    void syncStartBeat(double beat);
    bool hasSyncedStartBeat() const { return _hasSyncedStartBeat; }
    bool isHostBpmSet() const { return _isHostBpmSet; }
    void resampleBufferAndResetIndex();
    std::unique_lock<std::mutex>&& getScopedResamplingLock() { std::unique_lock<std::mutex> l(_resampledBufferMut); return std::move(l); }
private:

    void convertMp3FileToWavFile();
    void timeStretchFile();
    
    void resampleBuffer();
    void resetIndex();
    
    // All loops from backend are 8 bars for now
    static constexpr int NUM_BEATS_IN_LOOP = 32;
    
    std::mutex _resampledBufferMut;
    
    juce::AudioBuffer<float> _origSRBuffer;
    juce::AudioBuffer<float> _resampledBuffer;

    double _origSampleRate;
    double _hostSampleRate;
    double _origBpm;
    double _hostBpm;
    
    bool _isHostBpmSet = false;

    int _readIndex = 0;
    
    double _syncedStartBeat = 0;
    
    bool _hasSyncedStartBeat = false;
};

} // namespace lm::data
