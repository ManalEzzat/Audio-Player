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
  // addAndMakeVisible(loopButton);
   //loopButton.setButtonText("Loop ON");
   //loopButton.addListener(this);

   // loop off button
   //addAndMakeVisible(loopButton);
   //loopButton.setButtonText("Loop OFF");
   //loopButton.addListener(this);

   // === Go To Start Button ===
   addAndMakeVisible(goToStartButton);
   goToStartButton.setButtonText("Restart |<");
   goToStartButton.addListener(this);

   // === End Button ===
   addAndMakeVisible(endButton);
   endButton.setButtonText("End >|");
   endButton.addListener(this);
   
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
   setSize(800, 400);
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

    
    y += 70;

      
    titlelabel.setBounds(30, y, getWidth() - 60, 30);
    y += 40;

    authorlabel.setBounds(30, y, getWidth() - 60, 30);
    y += 40;

    durationlabel.setBounds(30, y, getWidth() - 60, 30);

     
    y += 50;

   
    audiolistbox.setBounds(30, y, getWidth() - 60, getHeight() - y - 30);

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

