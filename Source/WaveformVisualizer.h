/*
  ==============================================================================

    WaveformVisualizer.h
    Created: 12 May 2023 5:24:52pm
    Author:  Stanley Rokita

  ==============================================================================
*/

#pragma once

#include <vector>

namespace lm::wf {

struct WaveformVisualizerAttributes {
    int minHeight;
    int maxHeight;
    int numPoints;
    float initWaveFrequency;
    float movementFrequency;
};

class WaveformVisualizer{
public:
    WaveformVisualizer(const WaveformVisualizerAttributes& attributes);
    void update();
    int getHeight(int index) const;
    void pause();
    void resume();
private:
    int _minHeight;
    int _maxHeight;
    int heightAmp() { return _maxHeight - _minHeight; }

    float _initWaveFrequency;
    float _movementFrequency;

    long long _initTs;

    bool _isPaused;
    long long _pausedElapsed;

    int _numPoints;

    std::vector<int> _heights;

    void initHeights();
};

} // namespace lm::wf
