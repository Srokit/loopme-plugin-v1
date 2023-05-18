/*
  ==============================================================================

    LoopmeLabel.cpp
    Created: 11 May 2023 12:39:42pm
    Author:  Stanley Rokita

  ==============================================================================
*/

#include "LoopmeLabelComponent.h"

namespace lm::ui {

LoopmeLabelComponent::LoopmeLabelComponent(const std::string& text, float fontHeight, const juce::Point<int>& size) : _text(text), _size(size) {
    this->_label.setText(this->_text, juce::dontSendNotification);
    this->_label.setFont(juce::Font(fontHeight));
    this->setColour(juce::Label::textColourId, juce::Colours::white);
    this->setColour(juce::Label::backgroundColourId, juce::Colours::red);
    setSize(this->_size.getX(), this->_size.getY());
    addAndMakeVisible(this->_label);
}

void LoopmeLabelComponent::resized() {
    const auto& b = getBounds();
    this->_label.setSize(b.getWidth(), b.getHeight());
}

void LoopmeLabelComponent::paint(juce::Graphics& g) {
    //    g.fillAll(juce::Colours::red);
}

juce::FlexItem LoopmeLabelComponent::makeFlexItem() {
    return juce::FlexItem(this->_size.getX(), this->_size.getY(), *this);
}

void LoopmeLabelComponent::setText(const std::string &newS) {
    this->_label.setText(newS, juce::dontSendNotification);
}

} // namespace lm::ui
