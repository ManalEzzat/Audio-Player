# include "PlayerGUI.h"

PlayerGUI::PlayerGUI() {


	addAndMakeVisible(pausebutton);
	pausebutton.setButtonText("pause||");
	addAndMakeVisible(playbutton);
	playbutton.setButtonText("play ►");


	addAndMakeVisible(gotostart);
	gotostart.setButtonText("go to start|◄");
	addAndMakeVisible(end);
	end.setButtonText("end ►|");
	pausebutton.setColour(juce::TextButton::buttonColourId, juce::Colours::gold);
	pausebutton.setColour(juce::TextButton::textColourOffId, juce::Colours::black);
	pausebutton.setColour(juce::TextButton::textColourOnId, juce::Colours::red);



	playbutton.setColour(juce::TextButton::buttonColourId, juce::Colours::gold);
	playbutton.setColour(juce::TextButton::textColourOffId, juce::Colours::black);
	playbutton.setColour(juce::TextButton::textColourOnId, juce::Colours::red);


	gotostart.setColour(juce::TextButton::buttonColourId, juce::Colours::gold);
	gotostart.setColour(juce::TextButton::textColourOffId, juce::Colours::black);
	gotostart.setColour(juce::TextButton::textColourOnId, juce::Colours::red);


	end.setColour(juce::TextButton::buttonColourId, juce::Colours::gold);
	end.setColour(juce::TextButton::textColourOffId, juce::Colours::black);
	end.setColour(juce::TextButton::textColourOnId, juce::Colours::red);

	addAndMakeVisible(loopButton);
	loopButton.setButtonText("Loop 🔁");
	loopButton.setColour(juce::TextButton::buttonColourId, juce::Colours::gold);
	loopButton.setColour(juce::TextButton::textColourOffId, juce::Colours::black);
	loopButton.setColour(juce::TextButton::textColourOnId, juce::Colours::red);
	loopButton.addListener(this);


	setSize(700, 400);


}
PlayerGUI::~PlayerGUI() {}
void PlayerGUI::paint(juce::Graphics& interface) {
	interface.fillAll(juce::Colours::black);
}

void PlayerGUI::resized() {
	pausebutton.setBounds(50, 50, 100, 60);
	playbutton.setBounds(160, 50, 100, 60);

	gotostart.setBounds(380, 50, 100, 60);
	end.setBounds(490, 50, 100, 60);
	loopButton.setBounds(600, 50, 100, 60);


}
void PlayerGUI::buttonClicked(juce::Button* button)
{
	if (button == &loadbutton) {
		fileChooser = std::make_unique<juce::FileChooser>(
			"Select an audio file...", juce::File{}, "*.wav;*.mp3");

		fileChooser->launchAsync(
			juce::FileBrowserComponent::openMode | juce::FileBrowserComponent::canSelectFiles,
			[this](const juce::FileChooser& chooser)
			{
				auto file = chooser.getResult();
				if (file.existsAsFile())
				{
					player.loadFile(file);
				}
			});
	}
	else if (button == &playbutton)
		player.play();
	else if (button == &stopbutton)
		player.pause();
	else if (button == &gotostart)
		player.gotostart();
	else if (button == &end)
		player.end();
	else if (button == &loopButton)
	{
		isLooping = !isLooping;
		player.setLooping(isLooping);
	}

}
