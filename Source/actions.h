/*
  ==============================================================================

    actions.h
    Created: 17 May 2023 11:27:39am
    Author:  Stanley Rokita

  ==============================================================================
*/

#pragma once

namespace lm::data::actions {

void toggleIsPlaying();

void nextLoop();

void updateHostSampleRate(double);

void updateHostBpm(double);

} // namespace lm::data::actions
