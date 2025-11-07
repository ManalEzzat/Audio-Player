# include <JuceHeader.h>
# include "PlayerGUI.h"

PlayerGUI::PlayerGUI()
    : thumbnailCache(5),
    audioThumbnail(512, formatManager, thumbnailCache)
{



    //===volume slider===
    volumeSlider.setRange(0.0, 1.0, 0.01);
    volumeSlider.setValue(0.5);
    volumeSlider.addListener(this);
    addAndMakeVisible(volumeSlider);


    //===speed slider===
    speedSlider.setRange(0.5, 2.0, 0.1);
    speedSlider.setValue(1.0);
    speedSlider.addListener(this);
    addAndMakeVisible(speedSlider);

    //===position slider===
    positionSlider.setRange(0.0, 1.0, 0.001);
    positionSlider.setValue(0.0);
    positionSlider.addListener(this);
    positionSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    addAndMakeVisible(positionSlider);



    // ===load Button===
    addAndMakeVisible(loadButton);
    loadButton.setButtonText("Load");
    loadButton.addListener(this);



    // === Play Button ===
    addAndMakeVisible(playButton);
    playButton.setButtonText("Play >");
    playButton.addListener(this);

    // ==== pause Button ===
    addAndMakeVisible(pauseButton);
    pauseButton.setButtonText("Pause >");
    pauseButton.addListener(this);


    //=== fullLoop Button ===
    addAndMakeVisible(fullLoopButton);
    fullLoopButton.setButtonText("FullLoop");
    fullLoopButton.addListener(this);

    //==sectionloop button==
    addAndMakeVisible(sectionLoopButton);
    sectionLoopButton.setButtonText("SectionLoop");
    sectionLoopButton.addListener(this);

    //== StartLoopButton==
    addAndMakeVisible(StartLoopButton);
    StartLoopButton.setButtonText(" StartLoop");
    StartLoopButton.addListener(this);

    //== EndLoopButton==
    addAndMakeVisible(EndLoopButton);
    EndLoopButton.setButtonText(" EndLoop");
    EndLoopButton.addListener(this);

    // === Go To Start Button ===
    addAndMakeVisible(goToStartButton);
    goToStartButton.setButtonText("Restart |<");
    goToStartButton.addListener(this);

    // === End Button ===
    addAndMakeVisible(endButton);
    endButton.setButtonText("End >|");
    endButton.addListener(this);

    // === Mute Button ===
    addAndMakeVisible(muteButton);
    muteButton.setButtonText("Mute");
    muteButton.addListener(this);

    // === Time Label ===
    addAndMakeVisible(timeLabel);
    timeLabel.setText("00:00 / 00:00", juce::dontSendNotification);
    timeLabel.setJustificationType(juce::Justification::centred);



    // === add labels ===
    addAndMakeVisible(titlelabel);
    addAndMakeVisible(authorlabel);
    addAndMakeVisible(durationlabel);
    titlelabel.setText("Title: ", juce::dontSendNotification);
    authorlabel.setText("Author: ", juce::dontSendNotification);
    durationlabel.setText("Duration: ", juce::dontSendNotification);

    // add playlist 
    addAndMakeVisible(audiolistbox);
    audiolistbox.setModel(this);
    audiolistbox.setRowHeight(30);

    formatManager.registerBasicFormats();

    setSize(800, 400);
    startTimer(100);

    // ” 10s forward” and  ” 10s backward” 
    addAndMakeVisible(addtenforward);
    addtenforward.setButtonText("Forward 10s");
    addtenforward.addListener(this);
    addAndMakeVisible(addtenbackward);
    addtenbackward.setButtonText("Backward 10s");
    addtenbackward.addListener(this);


    auto setupButtonColors = [](juce::TextButton& button) {
        button.setColour(juce::TextButton::buttonColourId, juce::Colours::lightgrey);
        button.setColour(juce::TextButton::buttonOnColourId, juce::Colours::darkgrey);
        button.setColour(juce::TextButton::textColourOffId, juce::Colours::black);  
        button.setColour(juce::TextButton::textColourOnId, juce::Colours::black);   
        };

    setupButtonColors(loadButton);
    setupButtonColors(playButton);
    setupButtonColors(pauseButton);
    setupButtonColors(fullLoopButton);
    setupButtonColors(sectionLoopButton);
    setupButtonColors(StartLoopButton);
    setupButtonColors(EndLoopButton);
    setupButtonColors(goToStartButton);
    setupButtonColors(endButton);
    setupButtonColors(muteButton);
    setupButtonColors(addtenforward);
    setupButtonColors(addtenbackward);

}
PlayerGUI:: ~PlayerGUI() {}

void PlayerGUI::paint(juce::Graphics& g) {
    g.fillAll(juce::Colours::black); 

    juce::Rectangle<int> waveformArea(560, 10, 420, 165);

    g.setColour(juce::Colours::black);
    g.fillRect(waveformArea);

    g.setColour(juce::Colour(0xff555555));
    g.drawRect(waveformArea, 2);

    if (audioThumbnail.getTotalLength() > 0.0)
    {
        g.setColour(juce::Colour(0xff4DA6FF));
        audioThumbnail.drawChannels(g, waveformArea.reduced(3),
            0.0, audioThumbnail.getTotalLength(),
            0.9f);
    }

    
    if (player.getLength() > 0.0)
    {
        double currentPos = player.getPosition();
        double totalLength = player.getLength();
        double ratio = currentPos / totalLength;

        int pointerX = waveformArea.getX() + (int)(ratio * waveformArea.getWidth());

        g.setColour(juce::Colours::white);  
        g.drawLine(pointerX, waveformArea.getY(),
            pointerX, waveformArea.getBottom(), 3.0f);
    }


}



void PlayerGUI::resized() {
    int margin = 10;
    
    audiolistbox.setBounds(10, 10, 540, 230);

    
    int waveX = 560;  
    int waveY = 10;
  

    int posSliderY = waveY + 175;
    positionSlider.setBounds(waveX, posSliderY, 420, 30);

   
    int timeerY = posSliderY + 30 + 5;
    timeLabel.setBounds(waveX, timeerY, 420, 20);

   
    int metadataX = 10;
    titlelabel.setBounds(metadataX, 260, 980, 30);
    authorlabel.setBounds(metadataX, 310, 980, 30);
    durationlabel.setBounds(metadataX, 360, 980, 30);

 
    volumeSlider.setBounds(10, 410, 470, 30);
    speedSlider.setBounds(520, 410, 470, 30);


    int btnWidth = 110;
    int btnHeight = 40;

   
    loadButton.setBounds(10, 460, btnWidth, btnHeight);
    playButton.setBounds(184, 460, btnWidth, btnHeight);
    pauseButton.setBounds(358, 460, btnWidth, btnHeight);
    goToStartButton.setBounds(532, 460, btnWidth, btnHeight);
    endButton.setBounds(706, 460, btnWidth, btnHeight);
    muteButton.setBounds(880, 460, btnWidth, btnHeight);


    
    addtenbackward.setBounds(10, 530, btnWidth, btnHeight);
    addtenforward.setBounds(184, 530, btnWidth, btnHeight);
    fullLoopButton.setBounds(358, 530, btnWidth, btnHeight);
    sectionLoopButton.setBounds(532, 530, btnWidth, btnHeight);
    StartLoopButton.setBounds(706, 530, btnWidth, btnHeight);
    EndLoopButton.setBounds(880, 530, btnWidth, btnHeight);
}



void PlayerGUI::buttonClicked(juce::Button* button) {

    if (button == &loadButton)
    {

        fileChooser = std::make_unique<juce::FileChooser>("Select audio files...", juce::File{}, "*.wav;*.mp3");

        fileChooser->launchAsync(
            juce::FileBrowserComponent::openMode
            | juce::FileBrowserComponent::canSelectFiles
            | juce::FileBrowserComponent::canSelectMultipleItems,
            [this](const juce::FileChooser& chooser)
            {
                auto results = chooser.getResults();

                if (!results.isEmpty())
                {
                    audiolist = results;
                    audiolistbox.updateContent();
                    audiolistbox.repaint();
                }
            });
    }
    else if (button == &playButton) {
        player.play();
    }
    else if (button == &pauseButton) {
        player.pause();
    }
    else if (button == &goToStartButton) {
        player.restart();
    }
    else if (button == &endButton) {
        player.end();
    }

    else if (button == &fullLoopButton)
    {
        fullLoopEnabled = !fullLoopEnabled;
        player.FullLoop(fullLoopEnabled);
        fullLoopButton.setButtonText(fullLoopEnabled ? "Full Loop ON" : "Full Loop OFF");
    }
    else if (button == &sectionLoopButton)
    {
        sectionLoopEnabled = !sectionLoopEnabled;
        player.SectionLoop(sectionLoopEnabled, loopStart, loopEnd);
        sectionLoopButton.setButtonText(sectionLoopEnabled ? "Section Loop ON" : "Section Loop OFF");
    }
    else if (button == &StartLoopButton)
    {

        loopStart = player.getPosition();
        juce::Logger::outputDebugString("Section loop START set to: " + juce::String(loopStart));
    }
    else if (button == &EndLoopButton)
    {

        loopEnd = player.getPosition();
        juce::Logger::outputDebugString("Section loop END set to: " + juce::String(loopEnd));
    }


    else if (button == &muteButton) {
        isMuted = !isMuted;
        if (isMuted) {
            previousVolume = (float)volumeSlider.getValue();
            player.setGain(0.0f);
            muteButton.setButtonText("Unmute");
        }
        else {
            player.setGain(previousVolume);
            volumeSlider.setValue(previousVolume, juce::dontSendNotification);
            muteButton.setButtonText("Mute");
        }
    }
    else if (button == &addtenforward) {
        player.tenforward();
    }
    else if (button == &addtenbackward) {
        player.tenbackward();
    }


}
//volume and speed
void PlayerGUI::sliderValueChanged(juce::Slider* slider)
{
    if (slider == &volumeSlider) {
        if (!isMuted) {
            player.setGain((float)slider->getValue());
        }
    }
    else if (slider == &speedSlider) {
        double speed = slider->getValue();
        player.setSpeed(speed);

    }
    else if (slider == &positionSlider) {
        if (!isUpdatingPosition)
        {
            double newPos = slider->getValue() * player.getLength();
            player.setPosition(newPos);
        }
    }
}


void PlayerGUI::timerCallback()
{
    player.checkloop();
    if (player.getLength() > 0.0)
    {
        double currentPos = player.getPosition();
        double totalLength = player.getLength();

        double ratio = currentPos / totalLength;

        isUpdatingPosition = true;
        positionSlider.setValue(ratio, juce::dontSendNotification);
        isUpdatingPosition = false;


        int currentMinutes = (int)currentPos / 60;
        int currentSeconds = (int)currentPos % 60;
        int totalMinutes = (int)totalLength / 60;
        int totalSeconds = (int)totalLength % 60;

        juce::String timeText = juce::String::formatted("%02d:%02d / %02d:%02d",
            currentMinutes, currentSeconds, totalMinutes, totalSeconds);

        timeLabel.setText(timeText, juce::dontSendNotification);
        repaint();
    }
}



// audio playlist
int PlayerGUI::getNumRows() {
    return audiolist.size();
}

void PlayerGUI::paintListBoxItem(int row, juce::Graphics& g, int width, int height, bool selected) {
    if (selected)
        g.fillAll(juce::Colour(0xff4DA6FF));
    else
        g.fillAll(juce::Colours::lightgrey);

    if (row < audiolist.size()) {
        g.drawText(audiolist[row].getFileName(),
            10, 0, width - 10, height,
            juce::Justification::centredLeft);
    }
}
void PlayerGUI::selectedRowsChanged(int lastRowSelected)
{
    if (lastRowSelected >= 0 && lastRowSelected < audiolist.size())
    {
        auto file = audiolist[lastRowSelected];
        player.loadFile(file);

        audioThumbnail.clear();
        audioThumbnail.setSource(new juce::FileInputSource(file));

        juce::String title = file.getFileName();
        juce::String author = "Unknown";
        juce::AudioFormatReader* reader = player.readerSource->getAudioFormatReader();
        juce::String duration = "0 sec";

        if (reader != nullptr)
        {
            duration = juce::String(reader->lengthInSamples / reader->sampleRate) + " sec";
        }


        titlelabel.setText("Title: " + title, juce::dontSendNotification);
        authorlabel.setText("Author: " + author, juce::dontSendNotification);
        durationlabel.setText("Duration: " + duration, juce::dontSendNotification);

        repaint();
    }
}
