# include "PlayerAudio.h"
# include <iostream>
using namespace std;
PlayerAudio::PlayerAudio() {

	formataudio.registerBasicFormats();

}
PlayerAudio:: ~PlayerAudio() {}

bool PlayerAudio::loadFile(const juce::File& file) {
	if (auti* reader = formatManger.creatReaderFor(file)) {
        transportSource.stop();
        transportSource.setSource(nullptr);
        readerSource.reset();

        readerSource = std::make_unique<juce::AudioFormatReaderSource>(reader, true);

        transportSource.setSource(readerSource.get(),0,nullptr, reader->sampleRate);
        return true;
    }
    return false; 
}

void PlayerAudio::play() {
	transportSource.start(); 
}
void PlayerAudio::pause() {
	transportSource.stop(); 
}
void PlayerAudio::gotostart() {
	transportSource.setPosition(0.0);
}
void PlayerAudio::end() {
	transportSource.setPosition(transportSource.getLengthInSeconds());
}
void PlayerAudio::setLooping(bool loop)
{
    if (readerSource != nullptr)
        readerSource->setLooping(loop);
}
