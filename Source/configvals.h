/*
  ==============================================================================

    configvals.h
    Created: 11 May 2023 2:12:48pm
    Author:  Stanley Rokita

  ==============================================================================
*/

#pragma once

#include <string>

// Easily configurable values for the whole plugin

namespace lm::config {

constexpr int kMarginSize = 50;
constexpr int kPluginWidth = 800;
constexpr int kPluginHeight = 600;

const std::string kBackendUrlBase = "http://loopme-backend.herokuapp.com/";
const std::string kLoopInfoJsonFilePath = "/Users/srok/loop_info.json";
const std::string kLoopDataFilePath = "/Users/srok/loop_data.mp3";
const std::string kLoopDataWavFilePath = "/Users/srok/loop_data.wav";
const std::string kSoundStretchExecPath = "/Users/srok/Dev/soundstretch/soundstretch_mac_os_v2.1.2/SoundStretch";
const std::string kStretchedFilePath = "/Users/srok/loop_data_stretched.wav";

constexpr double kWavSampleRate = 44100;
constexpr int kWavBitsPerSample = 16;

} // namespace lm::config
