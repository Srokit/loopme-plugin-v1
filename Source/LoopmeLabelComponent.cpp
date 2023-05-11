/*
  ==============================================================================

    LoopmeLabel.cpp
    Created: 11 May 2023 12:39:42pm
    Author:  Stanley Rokita

  ==============================================================================
*/

#include "LoopmeLabelComponent.h"

namespace loopme::ui {

LoopmeLabelComponent::LoopmeLabelComponent(const std::string& text, const juce::Point<int>& size) : _text(text), _size(size) {
    this->_label.setText(this->_text, juce::dontSendNotification);
    this->_label.setFont(juce::Font(15.0f));
    this->setColour(juce::Label::textColourId, juce::Colours::white);
    setSize(this->_size.getX(), this->_size.getY());
    addAndMakeVisible(this->_label);
}

void LoopmeLabelComponent::resized() {
    auto bounds = getBounds();
    this->_label.setBounds(getBounds());
}

juce::FlexItem LoopmeLabelComponent::makeFlexItem() {
    return juce::FlexItem(this->_size.getX(), this->_size.getY(), *this);
}

}
