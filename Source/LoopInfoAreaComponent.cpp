/*
  ==============================================================================

    LoopInfoArea.cpp
    Created: 11 May 2023 12:20:58pm
    Author:  Stanley Rokita

  ==============================================================================
*/

#include "LoopInfoAreaComponent.h"

namespace lm::ui {

LoopInfoAreaComponent::LoopInfoAreaComponent()
: _loopInfo(),
  _nameLabelComponent(this->_loopInfo.name, 40, {kVertFbWidth, kLoopNameHeight}),
  _tempoAndKeyLabelComponent(calcTempoAndKeyLabelStr(this->_loopInfo.tempo, this->_loopInfo.key), 20, {kVertFbWidth, kTempoAndKeyH})
{
    attachChildren();
}

void LoopInfoAreaComponent::resized() {
    layoutChildren();
}

void LoopInfoAreaComponent::attachChildren() {
    
    this->_vertFlexBoxComponent.addAndMakeVisible(this->_nameLabelComponent);
    this->_vertFlexBoxComponent.addAndMakeVisible(this->_spacerComp);
    this->_vertFlexBoxComponent.addAndMakeVisible(this->_tempoAndKeyLabelComponent);
    this->_containerFlexBoxComponent.addAndMakeVisible(this->_vertFlexBoxComponent);
    addAndMakeVisible(this->_containerFlexBoxComponent);
}

void LoopInfoAreaComponent::layoutChildren() {
    // Set sizes of all components
    this->_containerFlexBoxComponent.setSize(getWidth(), getHeight());
    this->_vertFlexBoxComponent.setSize(kVertFbWidth, kVertFbHeight);
    this->_tempoAndKeyLabelComponent.setSize(kVertFbWidth, kTempoAndKeyH);
    this->_nameLabelComponent.setSize(kVertFbWidth, kLoopNameHeight);
    this->_spacerComp.setSize(kVertFbWidth, kSpacerHeight);

    // Set flexbox properties
    this->_containerFlexBoxComponent.setFlexDirection(juce::FlexBox::Direction::row);
    this->_containerFlexBoxComponent.setJustifyContent(juce::FlexBox::JustifyContent::flexStart);
    this->_vertFlexBoxComponent.setFlexDirection(juce::FlexBox::Direction::column);
    this->_vertFlexBoxComponent.setJustifyContent(juce::FlexBox::JustifyContent::flexStart);
    
    // Perform recursive layout
    this->_containerFlexBoxComponent.layout();
}

void LoopInfoAreaComponent::paint(juce::Graphics& g) {
//    g.fillAll(juce::Colours::yellow);
}

} // namespace lm::ui
