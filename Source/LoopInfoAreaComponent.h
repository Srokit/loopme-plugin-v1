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
#include "FlexBoxComponent.h"

namespace lm::ui {

class LoopInfoAreaComponent: public juce::Component {
public:
    LoopInfoAreaComponent();

    void resized() override;
    
    void setInfo(const data::LoopInfo& i) { _loopInfo = i; }
    
    // Debug
    void paint(juce::Graphics&) override;

private:
    void attachChildren();
    void layoutChildren();
    
    static constexpr int kVertFbWidth = 300;
    static constexpr int kVertFbHeight = 125;

    static constexpr int kLoopNameHeight = 70;
    
    static constexpr int kSpacerHeight = 0;
    
    static constexpr int kTempoAndKeyWidth = 50;
    
    static constexpr int kTempoAndKeyH = 30;
    
    static std::string calcTempoAndKeyLabelStr(const std::string& tempo, const std::string& key) {
        return tempo + '|' + key;
    }
    
    data::LoopInfo _loopInfo;
    LoopmeLabelComponent _nameLabelComponent;
    LoopmeLabelComponent _tempoAndKeyLabelComponent;
    
    juce::Component _spacerComp;

    FlexBoxComponent _containerFlexBoxComponent;
    FlexBoxComponent _vertFlexBoxComponent;

    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LoopInfoAreaComponent)
};

} // namespace lm::ui
