#pragma once
#include <JuceHeader.h>
#include "PlayerAudio.h"

class PlayerGUI : public juce::Component, public juce::Button::Listener {
public:
    PlayerGUI();
    ~PlayerGUI();

    void paint(juce::Graphics&) override;
    void resized() override;
    void buttonClicked(juce::Button* button) override;

private:
    juce::TextButton loadbutton{ "Load" };
    juce::TextButton playbutton{ "play ►" };
    juce::TextButton stopbutton{ "pause ||" };
    juce::TextButton gotostart{ "go to start|◄" };
    juce::TextButton end{ "end ►|" };

    PlayerAudio player; 
    std::unique_ptr<juce::FileChooser> fileChooser;
};
