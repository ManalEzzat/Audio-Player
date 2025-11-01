#pragma once
#include <JuceHeader.h>
#include "PlayerAudio.h"
#include <vector>

class MainComponent : public juce::AudioAppComponent,
    public juce::Button::Listener,
    public juce::Slider::Listener,
    public juce::ListBoxModel
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

    int getNumRows() override;
    void paintListBoxItem(int numaudios, juce::Graphics& g, int width, int height, bool audioselected);
    void selectedRowsChanged(int audioselected);
private:
    // === Audio ===
    juce::AudioFormatManager formatManager;
    juce::AudioTransportSource transportSource;

    std::unique_ptr<juce::AudioFormatReaderSource> readerSource;

    juce::Label titleLabel; // to add title in gui title
    juce::Label authorLabel; // to add the text in gui author 
    juce::Label durationLabel; // to add duration in gui duration


    juce::TextButton loadButton;
    juce::TextButton playPauseButton;
    juce::TextButton loopButton;
    juce::TextButton goToStartButton;
    juce::TextButton endButton;

    juce::ListBox audiolistbox; // to add playlist gui

    juce::TextButton muteButton;
    bool isMuted = false;
    float previousVolume = 0.5f;

    // === Slider ===
    juce::Slider volumeSlider;

    // === States ===
    bool isPlaying = false;
    bool isLooping = false;

    std::unique_ptr<juce::FileChooser> fileChooser;

    std::vector<juce::File> audiolist;
    int audioindex = -1; // current selected index
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};
