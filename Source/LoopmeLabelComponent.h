/*
  ==============================================================================

    LoopmeLabel.h
    Created: 11 May 2023 12:39:42pm
    Author:  Stanley Rokita

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

namespace lm::ui {

class LoopmeLabelComponent: public juce::Component {
public:
    LoopmeLabelComponent(const std::string&, float fontHeight, const juce::Point<int>& size);
    void resized() override;
    void paint(juce::Graphics&) override;
    
    juce::FlexItem makeFlexItem();
    
    void setText(const std::string&);
private:
    juce::Label _label;
    std::string _text;
    juce::Point<int> _size;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LoopmeLabelComponent)
};

} // namespace lm::ui
