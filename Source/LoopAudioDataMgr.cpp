/*
  ==============================================================================

    LoopAudioDataMgr.cpp
    Created: 17 May 2023 1:05:55pm
    Author:  Stanley Rokita

  ==============================================================================
*/

#include "LoopAudioDataMgr.h"

namespace lm::data {

void LoopAudioDataMgr::loadFileFromDisk(juce::String filePath) {
    juce::AudioFormatManager formatManager;
    formatManager.registerBasicFormats();
    std::unique_ptr<juce::AudioFormatReader> reader(formatManager.createReaderFor(filePath));
    if (reader.get() != nullptr) {
        this->_origSRBuffer.setSize(reader->numChannels, reader->lengthInSamples);
        reader->read(&this->_origSRBuffer, 0, reader->lengthInSamples, 0, true, true);
        _origSampleRate = reader->sampleRate;
    }
}

void LoopAudioDataMgr::resampleBuffer(double sampleRate) {
    juce::LagrangeInterpolator lInterpL;
    juce::LagrangeInterpolator lInterpR;
    double ratio = ((double) this->_origSampleRate) / ((double) sampleRate);
    float *inPtrL = this->_origSRBuffer.getWritePointer(0);
    float *inPtrR = this->_origSRBuffer.getWritePointer(1);
    int outNumSamples = (int) (((float)this->_origSRBuffer.getNumSamples()) / ((float)ratio));
    this->_resampledBuffer.setSize(2, outNumSamples);
    float *outPtrL = this->_resampledBuffer.getWritePointer(0);
    float *outPtrR = this->_resampledBuffer.getWritePointer(1);
    lInterpL.process(ratio, inPtrL, outPtrL, outNumSamples);
    lInterpR.process(ratio, inPtrR, outPtrR, outNumSamples);
}

void LoopAudioDataMgr::resetIndex() {
    this->_readIndex = 0;
}

void LoopAudioDataMgr::incIndex() {
    this->_readIndex = (this->_readIndex + 1) % this->_resampledBuffer.getNumSamples();
}

float LoopAudioDataMgr::getSample(int channel) {
    return this->_resampledBuffer.getSample(channel, this->_readIndex);
}

} // namespace lm::data
