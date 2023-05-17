/*
  ==============================================================================

    actions.cpp
    Created: 17 May 2023 11:27:39am
    Author:  Stanley Rokita

  ==============================================================================
*/

#include "actions.h"

#include "AppState.h"

namespace lm::data::actions {
    void toggleIsPlaying() {
        AppState::get().setIsPlaying(!AppState::get().isPlaying());
    }

    void nextLoop() {
        AppState::get().nextLoop();
    }
}