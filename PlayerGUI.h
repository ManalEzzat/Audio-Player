# pragma once
# include <JuceHeader.h>
# include "PlayerAudio.h"

class PlayerGUI :public juce::Component,
    public juce::Button::Listener,
    public juce::ListBoxModel
    public juce::Timer
{
public:
    PlayerGUI();
    ~PlayerGUI();

    void resized() override;
    void paint(juce::Graphics& g);
  
    PlayerAudio& getPlayer() { return player; }

    void buttonClicked(juce::Button* button) override;
    void timerCallback() override;   

    int getNumRows() override;
    void paintListBoxItem(int numaudios, juce::Graphics& g, int width, int height, bool audioselected);
    void selectedRowsChanged(int audioselected);

private:

    std::unique_ptr<juce::FileChooser> fileChooser;

    juce::TextButton loadButton;
    juce::TextButton playButton;
    juce::TextButton pauseButton;
    juce::TextButton loopButton;
    juce::TextButton goToStartButton;
    juce::TextButton endButton;

    juce::ListBox audiolistbox; // to add playlist gui

    juce::TextButton muteButton;

    juce::Slider positionSlider;
    juce::Label positionLabel;
    bool isDragging = false;

    juce::Label titlelabel; // to add title in gui title
    juce::Label authorlabel; // to add the text in gui author 
    juce::Label durationlabel; // to add duration in gui duration

    
    juce::Array<juce::File> audiolist;
    PlayerAudio player;  
    int audioindex = -1;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PlayerGUI)

};
