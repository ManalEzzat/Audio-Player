# pragma once 
# include<JuceHeader.h>

class PlayerGUI : public juce::Component {  

public:
	PlayerGUI(); 
	~PlayerGUI();  

	void paint(juce::Graphics&) override;
	void resized() override;

private:
	juce::TextButton playbutton;
	juce::TextButton pausebutton;
	juce::TextButton gotostart;
	juce::TextButton end;

};
