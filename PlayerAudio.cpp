# include "PlayerAudio.h"
# include <JuceHeader.h>

PlayerAudio::PlayerAudio() {
    formatManager.registerBasicFormats();
}

PlayerAudio::~PlayerAudio() {
    transportSource.setSource(nullptr);
    readerSource.reset();
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

bool PlayerAudio::loadFile(const juce::File& file)
{
    if (auto* reader = formatManager.createReaderFor(file))
    {
        transportSource.stop();
        transportSource.setSource(nullptr);
        readerSource.reset();

        readerSource = std::make_unique<juce::AudioFormatReaderSource>(reader, true);
        transportSource.setSource(readerSource.get(), 0, nullptr, reader->sampleRate);
        transportSource.start();

        return true;
    }
    return false;
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

void PlayerAudio::setGain(float gain)
{
    transportSource.setGain(gain);
}



void PlayerAudio::setPosition(double pos)
{
    transportSource.setPosition(pos);
}

double PlayerAudio::getPosition() const
{
    return transportSource.getCurrentPosition();
}

double PlayerAudio::getLength() const
{
    return transportSource.getLengthInSeconds();
}


void PlayerAudio::setSpeed(double speed)
{
    currentSpeed = speed;
    if (readerSource != nullptr && readerSource->getAudioFormatReader() != nullptr)
    {
         
        double currentPosition = transportSource.getCurrentPosition();
        bool wasPlaying = transportSource.isPlaying();

        auto* reader = readerSource->getAudioFormatReader();
        double newSampleRate = reader->sampleRate * speed;

        transportSource.setSource(readerSource.get(), 0, nullptr, newSampleRate);

        transportSource.setPosition(currentPosition);

        if (wasPlaying)
            transportSource.start();
    }

    }

