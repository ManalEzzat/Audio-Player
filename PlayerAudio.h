#pragma once
# include <JuceHeader.h>

class PlayerAudio :public juce::Component
{
public:
	PlayerAudio();
	~PlayerAudio();

	void prepareToPlay(int samplesPerBlockExpected, double sampleRate) ;
	void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) ;
	void releaseResources() ;
	void loadFile(const juce::File& file);



	void play();
	void pause();
	void restart();
	void end();
    void setLoopStart();
    void setLoopEnd();
    void clearLoop();
    void checkLoop();


	std::unique_ptr<juce::AudioFormatReaderSource> readerSource;
	
	

private:
	juce::AudioFormatManager formatManager;
	juce::AudioTransportSource transportSource;
	
	std::unique_ptr<juce::FileChooser> fileChooser;
	

	float previousVolume = 1.0f;
	
    double loopStart = 0.0;
    double loopEnd = 0.0;
    bool isLoopActive = false;

	

	juce::Label titleLabel;
	juce::Label authorLabel;
	juce::Label durationLabel;
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PlayerAudio);

}; 
