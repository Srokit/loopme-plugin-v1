/*
  ==============================================================================

    WaveformVisualizer.cpp
    Created: 12 May 2023 5:24:52pm
    Author:  Stanley Rokita

  ==============================================================================
*/

#include "WaveformVisualizer.h"

#include <chrono>
#include <cmath>

using namespace std::chrono;

namespace {

long long getTs() {
    return duration_cast<milliseconds>(
        system_clock::now().time_since_epoch()
    ).count();
}

}

namespace lm::wf {

WaveformVisualizer::WaveformVisualizer(const WaveformVisualizerAttributes& attributes) {
    _minHeight = attributes.minHeight;
    _maxHeight = attributes.maxHeight;
    _initWaveFrequency = attributes.initWaveFrequency;
    _movementFrequency = attributes.movementFrequency;
    _numPoints = attributes.numPoints;
    _initTs = getTs();
    _isPaused = true;
    _pausedElapsed = 0;
    initHeights();
}

void WaveformVisualizer::update() {
    long long newTs = getTs();
    long long elapsed = newTs - _initTs;
    if (_isPaused) {
        elapsed = _pausedElapsed;
        return;
    }
    float elapsedS = static_cast<float>(elapsed) / 1000.0f;
    for (int i = 0; i < _numPoints; i++) {
        float initPhase = static_cast<float>(i) / static_cast<float>(_numPoints) * 2.0f * M_PI * _initWaveFrequency;
        float sinVal = std::sin(2.0f * M_PI * _movementFrequency * elapsedS + initPhase);
        float sinValShifted = (sinVal + 1.0f) / 2.0f;
        int height = _minHeight + static_cast<int>(static_cast<float>(heightAmp()) * sinValShifted);
        _heights[i] = height;
    }
}

int WaveformVisualizer::getHeight(int index) const {
    return _heights[index];
}

void WaveformVisualizer::pause() {
    _isPaused = true;
    _pausedElapsed = getTs() - _initTs;
}

void WaveformVisualizer::resume() {
    _isPaused = false;
    _initTs = getTs() - _pausedElapsed;
}

void WaveformVisualizer::initHeights() {
    _heights.reserve(_numPoints);
    for (int i = 0; i < _numPoints; i++) {
        float sinVal = std::sin(static_cast<float>(i) / _numPoints * 2.0f * M_PI * _initWaveFrequency);
        float sinValShifted = (sinVal + 1.0f) / 2.0f;
        _heights.push_back(_minHeight + heightAmp() * sinValShifted);
    }
}

} // namespace lm::wf
