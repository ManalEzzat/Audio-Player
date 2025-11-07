#pragma once
#include <JuceHeader.h>
#include "PlayerAudio.h"

class PlayerGUI : public juce::Component,
    public juce::Button::Listener,
    public juce::ListBoxModel,
    public juce::Slider::Listener,
    public juce::Timer
   
{
public:
    PlayerGUI();
    ~PlayerGUI() override;

    void resized() override;
    void paint(juce::Graphics& g) override;


    void prepareToPlay(int samplesPerBlockExpected, double sampleRate);
    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill);
    void releaseResources();

    PlayerAudio& getPlayer() { return player; }

    // ListBoxModel overrides
    int getNumRows() override;
    void paintListBoxItem(int row, juce::Graphics& g, int width, int height, bool rowIsSelected) override;
    void selectedRowsChanged(int lastRowSelected) override;

private:
    std::unique_ptr<juce::FileChooser> fileChooser;

    juce::TextButton loadButton;
    juce::TextButton playButton;
    juce::TextButton pauseButton;

    juce::TextButton goToStartButton;
    juce::TextButton endButton;
    juce::TextButton muteButton;
    juce::TextButton fullLoopButton{ "Full Loop" };
    juce::TextButton sectionLoopButton{ "Section Loop" };
    juce::TextButton StartLoopButton{ "Set Start" };
    juce::TextButton EndLoopButton{ "Set End" };
    juce::TextButton addtenforward;
    juce::TextButton addtenbackward;


    juce::AudioThumbnailCache thumbnailCache;
    juce::AudioThumbnail audioThumbnail;

    juce::AudioFormatManager formatManager;


    double loopStart = 0.0;
    double loopEnd = 0.0;
    bool fullLoopEnabled = false;
    bool sectionLoopEnabled = false;


    bool isMuted = false;
    float previousVolume = 0.5f;

    juce::ListBox audiolistbox; // to add playlist gui


    juce::Label titlelabel; // to add title in gui title
    juce::Label authorlabel; // to add the text in gui author 
    juce::Label durationlabel; // to add duration in gui duration
    juce::Label timeLabel;

    juce::Slider volumeSlider;
    juce::Slider speedSlider;
    juce::Slider positionSlider;




    juce::Array<juce::File> audiolist;
    PlayerAudio player;
    int audioindex = -1;

    // listeners
    void buttonClicked(juce::Button* button) override;
    void sliderValueChanged(juce::Slider* slider) override;
    void timerCallback() override;
    bool isUpdatingPosition = false;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PlayerGUI)
};
