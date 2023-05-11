/*
  ==============================================================================

    LoopmeLabel.h
    Created: 11 May 2023 12:39:42pm
    Author:  Stanley Rokita

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

namespace loopme {

namespace ui {

class LoopmeLabelComponent: public juce::Component {
public:
    LoopmeLabelComponent(const std::string&, const juce::Point<int>& size);
    void resized() override;
    
    juce::FlexItem makeFlexItem();
private:
    juce::Label _label;
    std::string _text;
    juce::Point<int> _size;
};

}

}
