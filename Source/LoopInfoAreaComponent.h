/*
  ==============================================================================

    LoopInfoArea.h
    Created: 11 May 2023 12:20:58pm
    Author:  Stanley Rokita

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

#include "LoopInfo.h"
#include "LoopmeLabelComponent.h"

namespace loopme::ui {

class LoopInfoAreaComponent: public juce::Component {
public:
    LoopInfoAreaComponent();

    void resized() override;
    
    void setInfo(const LoopInfo& i) { _loopInfo = i; }

private:
    void attachChildren();
    void layoutChildren();
    
    LoopInfo _loopInfo;
    LoopmeLabelComponent _nameLabelComponent;
    LoopmeLabelComponent _tempoLabelComponent;
    LoopmeLabelComponent _keyLabelComponent;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LoopInfoAreaComponent)
};

}
