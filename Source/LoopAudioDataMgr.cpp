/*
  ==============================================================================

    LoopAudioDataMgr.cpp
    Created: 17 May 2023 1:05:55pm
    Author:  Stanley Rokita

  ==============================================================================
*/

#include "LoopAudioDataMgr.h"

#include "configvals.h"

namespace lm::data {

void LoopAudioDataMgr::loadFileFromDisk() {
    // Convert donloaded mp3 to wav first
    convertMp3FileToWavFile();
    timeStretchFile();
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    juce::AudioFormatManager formatManager;
    formatManager.registerBasicFormats();
    std::unique_ptr<juce::AudioFormatReader> reader(formatManager.createReaderFor(juce::String(config::kStretchedFilePath)));
    if (reader.get() != nullptr) {
        this->_origSRBuffer.clear();
        this->_origSRBuffer.setSize(0, 0);
        this->_origSRBuffer.setSize(reader->numChannels, reader->lengthInSamples);
        reader->read(&this->_origSRBuffer, 0, reader->lengthInSamples, 0, true, true);
        _origSampleRate = reader->sampleRate;
    }
}

void LoopAudioDataMgr::resampleBufferAndResetIndex() {
    std::lock_guard<std::mutex> guard(_resampledBufferMut);
    resampleBuffer();
    resetIndex();
}

void LoopAudioDataMgr::resampleBuffer() {
    juce::LagrangeInterpolator lInterpL;
    juce::LagrangeInterpolator lInterpR;
    double ratio = (this->_origSampleRate / _hostSampleRate);
    float *inPtrL = this->_origSRBuffer.getWritePointer(0);
    float *inPtrR = this->_origSRBuffer.getWritePointer(1);
    int outNumSamples = (int) (((float)this->_origSRBuffer.getNumSamples()) / ((float)ratio));
    this->_resampledBuffer.clear();
    this->_resampledBuffer.setSize(0, 0);
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

void LoopAudioDataMgr::convertMp3FileToWavFile() {
    // Covert the mp3 file into a wav file using juce
    juce::File mp3File(config::kLoopDataFilePath);
    juce::File wavFile(config::kLoopDataWavFilePath);
    
    if (!wavFile.deleteFile()) {
        DBG("Wav file not deleted!");
    } else {
        DBG("Wav file deleted!");
    }
    
    std::unique_ptr<juce::FileOutputStream> wavOutputStream = wavFile.createOutputStream();
    auto *wavOutputNoDelete = wavOutputStream.release();
    
    auto *mp3InStream = mp3File.createInputStream().release();

    juce::WavAudioFormat wavFormat;
    juce::MP3AudioFormat mp3Format;
    std::unique_ptr<juce::AudioFormatReader> reader(mp3Format.createReaderFor(mp3InStream, true));
    // CRASH CAN OCCUR HERE BC Sharp Keyed loops can't download correctly from AWS.
    juce::AudioBuffer<float> tempBuff(2, reader->lengthInSamples);
    reader->read(&tempBuff, 0, reader->lengthInSamples, 0, true, true);
    int numSamples = reader->lengthInSamples;
    std::unique_ptr<juce::AudioFormatWriter> writer(wavFormat.createWriterFor(wavOutputNoDelete, reader->sampleRate, juce::AudioChannelSet::stereo(), config::kWavBitsPerSample, {}, 0));
    double sampRate = reader->sampleRate;
    int samples = reader->lengthInSamples;
    writer->writeFromAudioSampleBuffer(tempBuff, 0, reader->lengthInSamples);
    
    // FileOutputStream deleted by writer dtor
    writer.reset();
    reader.reset();
}

void LoopAudioDataMgr::timeStretchFile() {
    double speedUpFactor = _hostBpm / _origBpm;
    bool isPositive;
    if (speedUpFactor >= 1.0) {
        speedUpFactor = speedUpFactor - 1.0;
        isPositive = true;
    } else {
        speedUpFactor = 1.0 - speedUpFactor;
        isPositive = false;
    }
    std::string tempoStr = ((isPositive) ? "+" : "-") + std::to_string((int) (speedUpFactor * 100));
    // Use SoundStretch executable to stretch the wav file
    std::string command = config::kSoundStretchExecPath + " " + config::kLoopDataWavFilePath + " " + config::kStretchedFilePath + " -tempo=" + tempoStr;
    int commandResult = std::system(command.c_str());
    if (commandResult != 0) {
        DBG("Error: SoundStretch command failed");
    }
}

} // namespace lm::data
