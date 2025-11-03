#include "MainComponent.h"

MainComponent::MainComponent()
{
    addAndMakeVisible(gui); 
    setSize(700, 400);
    setAudioChannels(0, 2);
}
MainComponent::~MainComponent() {}

void MainComponent::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    gui.getPlayer().prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void MainComponent::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
    gui.getPlayer().getNextAudioBlock(bufferToFill);
}

void MainComponent::releaseResources()
{
    gui.getPlayer().releaseResources();
}

void MainComponent::resized()
{
    gui.setBounds(getLocalBounds());
}

void MainComponent::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);
}
