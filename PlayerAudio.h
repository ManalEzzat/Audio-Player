#pragma once
#include <JuceHeader.h>

class PlayerAudio
{
public:
    PlayerAudio();
    ~PlayerAudio();

    bool loadFile(const juce::File& file);
    void play();
    void pause();
    void gotostart();
    void end();
    void setLooping(bool loop);

private:
    juce::AudioFormatManager formatAudio;
    juce::AudioTransportSource transportSource;
    std::unique_ptr<juce::AudioFormatReaderSource> readerSource;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PlayerAudio)
};
