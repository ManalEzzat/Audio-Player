#pragma once
#include <JuceHeader.h>

class PlayerAudio : public juce::AudioSource
{
public:
    PlayerAudio();
    ~PlayerAudio() override;

    // AudioSource interface
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    bool loadFile(const juce::File& file);

    void play();
    void pause();
    void restart();
    void end();
    void setGain(float gain);
    void setSpeed(double speed);
    void setPosition(double pos);
    void FullLoop(bool shoudloop);
    void SectionLoop(bool shoudloop, double start, double end);
    void checkloop();
    double getPosition() const;
    double getLength() const;
    void tenforward();
    void tenbackward();


    std::unique_ptr<juce::AudioFormatReaderSource> readerSource;

private:
    juce::AudioFormatManager formatManager;
    juce::AudioTransportSource transportSource;
    std::unique_ptr<juce::ResamplingAudioSource> resamplingSource;
    std::unique_ptr<juce::FileChooser> fileChooser;
    double currentSpeed = 1.0;
    float previousVolume = 1.0f;

    bool isFullLoop = false;
    bool isSectionLoop = false;
    double loopStart = 0.0;
    double loopEnd = 0.0;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PlayerAudio)
};
