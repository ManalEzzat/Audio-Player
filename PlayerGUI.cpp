# include <JuceHeader.h>
# include "PlayerGUI.h"

PlayerGUI::PlayerGUI(){

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


   // === Loop Button ===
   addAndMakeVisible(loopButton);
   loopButton.setButtonText("Loop ON");
   loopButton.addListener(this);

   // loop off button
   addAndMakeVisible(loopButton);
   loopButton.setButtonText("Loop OFF");
   loopButton.addListener(this);

   // === Go To Start Button ===
   addAndMakeVisible(goToStartButton);
   goToStartButton.setButtonText("Restart |<");
   goToStartButton.addListener(this);

   // === End Button ===
   addAndMakeVisible(endButton);
   endButton.setButtonText("End >|");
   endButton.addListener(this);
    //===setAButton===
    addAndMakeVisible(setAButton);
    setAButton.setButtonText("Set A");
    setAButton.addListener(this);
    //===setBButton===
    addAndMakeVisible(setBButton);
    setBButton.setButtonText("Set B");
    setBButton.addListener(this);
    //===clearLoopButton===
    addAndMakeVisible(clearLoopButton);
    clearLoopButton.setButtonText("Clear Loop");
    clearLoopButton.addListener(this);

    // === Position Slider ===
    addAndMakeVisible(positionSlider);
    positionSlider.setRange(0.0, 1.0, 0.001);
    positionSlider.addListener(this);
    positionSlider.setSliderStyle(juce::Slider::LinearHorizontal);
    positionSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);

   // === add labels ===
   addAndMakeVisible(titlelabel);
   addAndMakeVisible(authorlabel);
   addAndMakeVisible(durationlabel);
   addAndMakeVisible(positionLabel);
   positionLabel.setText("0:00 / 0:00", juce::dontSendNotification);
   titlelabel.setText("Title: ", juce::dontSendNotification);
   authorlabel.setText("Author: ", juce::dontSendNotification);
   durationlabel.setText("Duration: ", juce::dontSendNotification);
   
   // add playlist 
   addAndMakeVisible(audiolistbox);
   audiolistbox.setModel(this);
   audiolistbox.setRowHeight(30);
   setSize(800, 400);
   startTimer(100);

}
PlayerGUI:: ~PlayerGUI() {}

void PlayerGUI::paint(juce::Graphics& g) {

    g.fillAll(juce::Colours::darkgrey);
}

void PlayerGUI::resized() {
   
    int y = 20;

    
    loadButton.setBounds(30, y, 110, 40);
    playButton.setBounds(160, y, 110, 40);
    pauseButton.setBounds(290, y, 110, 40);
    goToStartButton.setBounds(420, y, 110, 40);
    endButton.setBounds(550, y, 110, 40);

    y += 60;
    setAButton.setBounds(30, y, 110, 40);
    setBButton.setBounds(160, y, 110, 40);
    clearLoopButton.setBounds(290, y, 110, 40);

    y += 70;

      
    titlelabel.setBounds(30, y, getWidth() - 60, 30);
    y += 40;

    authorlabel.setBounds(30, y, getWidth() - 60, 30);
    y += 40;

    durationlabel.setBounds(30, y, getWidth() - 60, 30);
    y += 50;
   positionSlider.setBounds(50, y, getWidth() - 100, 20);
    y += 25;

    positionLabel.setBounds(50, y, getWidth() - 100, 20);
    y += 40;
   
    audiolistbox.setBounds(30, y, getWidth() - 60, getHeight() - y - 30);

}

void PlayerGUI::timerCallback()
{
    if (player.transportSource.isPlaying())
    {
        double currentPosition = player.transportSource.getCurrentPosition();
        double totalLength = player.transportSource.getLengthInSeconds();

        if (totalLength > 0.0)
            positionSlider.setValue(currentPosition / totalLength, juce::dontSendNotification);

        int curMin = (int)(currentPosition / 60);
        int curSec = (int)((int)currentPosition % 60);
        int totalMin = (int)(totalLength / 60);
        int totalSec = (int)((int)totalLength % 60);

        positionLabel.setText(
            juce::String::formatted("%02d:%02d / %02d:%02d", curMin, curSec, totalMin, totalSec),
            juce::dontSendNotification);
         
        player.checkLoop();
    }
        void PlayerGUI::sliderValueChanged(juce::Slider* slider)
        {
            if (slider == &positionSlider && player.readerSource != nullptr)
            {
                double totalLength = player.transportSource.getLengthInSeconds();
                double newPosition = positionSlider.getValue() * totalLength;
                player.transportSource.setPosition(newPosition);
            }
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
    else if (button == &setAButton)
    {
        player.setLoopStart();
    }
    else if (button == &setBButton)
    {
        player.setLoopEnd();
    }
    else if (button == &clearLoopButton)
    {
        player.clearLoop();
    }

    
}

// audio playlist
int PlayerGUI::getNumRows() {
    return audiolist.size();
}

void PlayerGUI::paintListBoxItem(int row, juce::Graphics& g, int width, int height, bool selected) {
    if (selected)
        g.fillAll(juce::Colours::yellow);
    else
        g.fillAll(juce::Colours::darkgrey);

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
    }
}

