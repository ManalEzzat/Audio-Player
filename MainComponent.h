#pragma once
#include <JuceHeader.h>
#include "PlayerAudio.h"
class MainComponent : public juce::AudioAppComponent,
    public juce::Button::Listener,
    public juce::Slider::Listener
{
public:
    MainComponent();
    ~MainComponent() override;

    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    void paint(juce::Graphics& g) override;
    void resized() override;

    void buttonClicked(juce::Button* button) override;
    void sliderValueChanged(juce::Slider* slider) override;

private:
    // === Audio ===
    juce::AudioFormatManager formatManager;
    juce::AudioTransportSource transportSource;
    std::unique_ptr<juce::AudioFormatReaderSource> readerSource;

    juce::TextButton loadButton;
    juce::TextButton playPauseButton;
    juce::TextButton loopButton;
    juce::TextButton goToStartButton;
    juce::TextButton endButton;

    juce::TextButton muteButton;   
    bool isMuted = false;          
    float previousVolume = 0.5f;   

    // === Slider ===
    juce::Slider volumeSlider;

    // === States ===
    bool isPlaying = false;
    bool isLooping = false;

    std::unique_ptr<juce::FileChooser> fileChooser;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};
