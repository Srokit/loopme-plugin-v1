/*
  ==============================================================================

    LoopInfoArea.cpp
    Created: 11 May 2023 12:20:58pm
    Author:  Stanley Rokita

  ==============================================================================
*/

#include "LoopInfoAreaComponent.h"

namespace loopme {

namespace ui {

LoopInfoAreaComponent::LoopInfoAreaComponent()
: _loopInfo(),
  _nameLabelComponent(this->_loopInfo.name, {100, 50}),
  _tempoLabelComponent(this->_loopInfo.tempo, {50, 50}),
  _keyLabelComponent(this->_loopInfo.key, {50, 50})
{
    setSize(700, 150);
    attachChildren();
}

void LoopInfoAreaComponent::resized() {
    layoutChildren();
}

void LoopInfoAreaComponent::attachChildren() {
    addAndMakeVisible(this->_nameLabelComponent);
    addAndMakeVisible(this->_tempoLabelComponent);
    addAndMakeVisible(this->_keyLabelComponent);
}

void LoopInfoAreaComponent::layoutChildren() {
    juce::FlexBox fb;
    fb.items.add(this->_nameLabelComponent.makeFlexItem());
    fb.items.add(this->_tempoLabelComponent.makeFlexItem());
    fb.items.add(this->_keyLabelComponent.makeFlexItem());
    fb.alignItems = juce::FlexBox::AlignItems::flexStart;
    fb.alignContent = juce::FlexBox::AlignContent::flexStart;
    fb.flexWrap = juce::FlexBox::Wrap::wrap;
    fb.flexDirection = juce::FlexBox::Direction::row;
    fb.justifyContent = juce::FlexBox::JustifyContent::spaceAround;
    fb.performLayout(getBounds());
}

}

}
