# include "PlayerAudio.h"
# include <JuceHeader.h>

PlayerAudio::PlayerAudio() {
    formatManager.registerBasicFormats();    
}
PlayerAudio::~PlayerAudio() {
}
void PlayerAudio::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    transportSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void PlayerAudio::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
    transportSource.getNextAudioBlock(bufferToFill);
}

void PlayerAudio::releaseResources()
{
    transportSource.releaseResources();
}

void PlayerAudio::loadFile(const juce::File& file)
{
    if (auto* reader = formatManager.createReaderFor(file))
    {
        transportSource.stop();
        transportSource.setSource(nullptr);
        readerSource.reset();

        readerSource = std::make_unique<juce::AudioFormatReaderSource>(reader, true);
        transportSource.setSource(readerSource.get(), 0, nullptr, reader->sampleRate);
    }
}


void PlayerAudio::play() {
    if (readerSource != nullptr)
       transportSource.start();   
}
void PlayerAudio::pause() {
    transportSource.stop();
}

void PlayerAudio::end() {
    transportSource.setPosition(transportSource.getLengthInSeconds());
}

void PlayerAudio::restart() {
    transportSource.setPosition(0.0);
}
void PlayerAudio::setLoopStart()
{
    loopStart = transportSource.getCurrentPosition();
    isLoopActive = false; 
}

void PlayerAudio::setLoopEnd()
{
    loopEnd = transportSource.getCurrentPosition();
    isLoopActive = true; 

void PlayerAudio::clearLoop()
{
    isLoopActive = false;
    loopStart = 0.0;
    loopEnd = 0.0;
}

void PlayerAudio::checkLoop()
{
    if (isLoopActive)
    {
        double currentPos = transportSource.getCurrentPosition();
        if (currentPos >= loopEnd)
            transportSource.setPosition(loopStart);
    }
}

