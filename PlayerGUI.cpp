#include "PlayerGUI.h"

PlayerGUI::PlayerGUI()
{
   
    addAndMakeVisible(playButton);
    playButton.setButtonText("Play ►");
    playButton.setColour(juce::TextButton::buttonColourId, juce::Colours::gold);
    playButton.setColour(juce::TextButton::textColourOffId, juce::Colours::black);
    playButton.setColour(juce::TextButton::textColourOnId, juce::Colours::red);
    playButton.addListener(this);

   
    addAndMakeVisible(pauseButton);
    pauseButton.setButtonText("Pause ||");
    pauseButton.setColour(juce::TextButton::buttonColourId, juce::Colours::gold);
    pauseButton.setColour(juce::TextButton::textColourOffId, juce::Colours::black);
    pauseButton.setColour(juce::TextButton::textColourOnId, juce::Colours::red);
    pauseButton.addListener(this);

    
    addAndMakeVisible(gotoStartButton);
    gotoStartButton.setButtonText("|◄ Start");
    gotoStartButton.setColour(juce::TextButton::buttonColourId, juce::Colours::gold);
    gotoStartButton.setColour(juce::TextButton::textColourOffId, juce::Colours::black);
    gotoStartButton.setColour(juce::TextButton::textColourOnId, juce::Colours::red);
    gotoStartButton.addListener(this);

    
    addAndMakeVisible(endButton);
    endButton.setButtonText("End ►|");
    endButton.setColour(juce::TextButton::buttonColourId, juce::Colours::gold);
    endButton.setColour(juce::TextButton::textColourOffId, juce::Colours::black);
    endButton.setColour(juce::TextButton::textColourOnId, juce::Colours::red);
    endButton.addListener(this);

    
    addAndMakeVisible(loopButton);
    loopButton.setButtonText("Loop 🔁");
    loopButton.setColour(juce::TextButton::buttonColourId, juce::Colours::gold);
    loopButton.setColour(juce::TextButton::textColourOffId, juce::Colours::black);
    loopButton.setColour(juce::TextButton::textColourOnId, juce::Colours::red);
    loopButton.addListener(this);

    setSize(700, 400);
}

PlayerGUI::~PlayerGUI() {}

void PlayerGUI::paint(juce::Graphics& interface)
{
    interface.fillAll(juce::Colours::black);
}

void PlayerGUI::resized()
{
    playButton.setBounds(50, 50, 120, 60);
    pauseButton.setBounds(180, 50, 120, 60);
    gotoStartButton.setBounds(310, 50, 120, 60);
    endButton.setBounds(440, 50, 120, 60);
    loopButton.setBounds(570, 50, 120, 60);
}

void PlayerGUI::buttonClicked(juce::Button* button)
{
    if (button == &playButton)
    {
        player.play();
    }
    else if (button == &pauseButton)
    {
        player.pause();
    }
    else if (button == &gotoStartButton)
    {
        player.gotostart();
    }
    else if (button == &endButton)
    {
        player.end();
    }
    else if (button == &loopButton) {
        isLooping = !isLooping;
        player.setLooping(isLooping);
    }

}
