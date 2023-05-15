/*
  ==============================================================================

    WaveformVisualizerAggregate.cpp
    Created: 12 May 2023 5:44:00pm
    Author:  Stanley Rokita

  ==============================================================================
*/

#include "WaveformVisualizerAggregate.h"

namespace lm::wf {

WaveformVisualizerAttributes WaveformVisualizerAggregateAttributes::toVisualizerAttributes() const {
    return {
        .minHeight = this->minHeight,
        .maxHeight = this->maxHeight,
        .initWaveFrequency = this->initWaveFrequency,
        .movementFrequency = this->movementFrequency,
        .numPoints = 0, // This value must be set by caller
    };
}

void WaveformVisualizerAggregate::setNumPoints(int numPoints) {
    _numPoints = numPoints;
}

int WaveformVisualizerAggregate::getNumPoints() const {
    return _numPoints;
}

void WaveformVisualizerAggregate::addVisualizerWithAttributes(const WaveformVisualizerAggregateAttributes& attributes) {
    WaveformVisualizerAttributes singleAttributes = attributes.toVisualizerAttributes();
    // The number of points is the same for all visualizers added
    singleAttributes.numPoints = _numPoints;
    _visualizers.emplace_back(singleAttributes);
}

int WaveformVisualizerAggregate::getHeightAtIndex(int index) const {
    int height = 0;
    for (const auto& v : _visualizers) {
        height += v.getHeight(index);
    }
    return height;
}

void WaveformVisualizerAggregate::update() {
    for (auto& v : _visualizers) {
        v.update();
    }
}

void WaveformVisualizerAggregate::pause() {
    for (auto& v : _visualizers) {
        v.pause();
    }
}

void WaveformVisualizerAggregate::resume() {
    for (auto& v : _visualizers) {
        v.resume();
    }
}

} // namespace lm::wf
