#pragma once
#include <JuceHeader.h>
#include "PlayerAudio.h"

class PlayerGUI : public juce::Component,
    public juce::Button::Listener
{
public:
    PlayerGUI();
    ~PlayerGUI() override;

    void paint(juce::Graphics&) override;
    void resized() override;
    void buttonClicked(juce::Button* button) override;

private:
    PlayerAudio player;

    juce::TextButton playButton;
    juce::TextButton pauseButton;
    juce::TextButton gotoStartButton;
    juce::TextButton endButton;
    juce::TextButton loopButton;

    bool isLooping = false;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PlayerGUI)
};
