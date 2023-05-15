/*
  ==============================================================================

    WaveformVisualizerAggregate.h
    Created: 12 May 2023 5:44:00pm
    Author:  Stanley Rokita

  ==============================================================================
*/

#pragma once

#include "WaveformVisualizer.h"

namespace lm::wf {

struct WaveformVisualizerAggregateAttributes {
    int minHeight;
    int maxHeight;
    float initWaveFrequency;
    float movementFrequency;
    
    WaveformVisualizerAttributes toVisualizerAttributes() const;
};

class WaveformVisualizerAggregate {
public:
    WaveformVisualizerAggregate(): _numPoints(0) {}
    void setNumPoints(int);
    int getNumPoints() const;
    void addVisualizerWithAttributes(const WaveformVisualizerAggregateAttributes&);
    int getHeightAtIndex(int) const;
    void update();
    void pause();
    void resume();

private:
    int _numPoints;
    std::vector<WaveformVisualizer> _visualizers;
};

} // namespace lm::wf
