/*
  ==============================================================================

    FlexBoxComponent.cpp
    Created: 12 May 2023 1:21:16pm
    Author:  Stanley Rokita

  ==============================================================================
*/

#include "FlexBoxComponent.h"

namespace lm::ui {

FlexBoxComponent::FlexBoxComponent() {
    _flexBox.flexDirection = juce::FlexBox::Direction::row;
    _flexBox.alignContent = juce::FlexBox::AlignContent::flexStart;
    _flexBox.alignItems = juce::FlexBox::AlignItems::flexStart;
    _flexBox.justifyContent = juce::FlexBox::JustifyContent::flexStart;
    _flexBox.flexWrap = juce::FlexBox::Wrap::noWrap;
}

void FlexBoxComponent::layout() {
    // For each child add a flex item
    _flexBox.items.clear();
    for (auto* child : getChildren()) {
        _flexBox.items.add(juce::FlexItem(*child).withWidth(child->getWidth()).withHeight(child->getHeight()));
        // Layout child flexbox components in cascading fashion
        if (childIsAFlexBox(child)) {
            childToFB(child)->layout();
        }
    }
    _flexBox.performLayout(getLocalBounds());
}

bool FlexBoxComponent::childIsAFlexBox(juce::Component* child) {
    return dynamic_cast<FlexBoxComponent*>(child) != nullptr;
}
FlexBoxComponent* FlexBoxComponent::childToFB(juce::Component* child) {
    return dynamic_cast<FlexBoxComponent*>(child);
}

} // namespace lm::ui
