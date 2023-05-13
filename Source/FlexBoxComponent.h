/*
  ==============================================================================

    FlexBoxComponent.h
    Created: 12 May 2023 1:21:16pm
    Author:  Stanley Rokita

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

namespace lm::ui {

class FlexBoxComponent : public juce::Component {
public:
    
    FlexBoxComponent();
    void layout();
    
    void setFlexDirection(juce::FlexBox::Direction direction) {
        _flexBox.flexDirection = direction;
    }
    
    void setJustifyContent(juce::FlexBox::JustifyContent justify) {
        _flexBox.justifyContent = justify;
    }
private:

    static bool childIsAFlexBox(juce::Component* child);
    static FlexBoxComponent* childToFB(juce::Component* child);

    juce::FlexBox _flexBox;
};

} // namespace lm::ui
