#include "MainComponent.h"
#include "PlayerAudio.h"
# include <vector>



MainComponent::MainComponent()
{
    formatManager.registerBasicFormats();

    // === Load Button ===
    addAndMakeVisible(loadButton);
    loadButton.setButtonText("Load");
    loadButton.addListener(this);

    // === Play/Pause Button ===
    addAndMakeVisible(playPauseButton);
    playPauseButton.setButtonText("Play >");
    playPauseButton.addListener(this);

    // === Loop Button ===
    addAndMakeVisible(loopButton);
    loopButton.setButtonText("Loop");
    loopButton.addListener(this);

    // === Go To Start Button ===
    addAndMakeVisible(goToStartButton);
    goToStartButton.setButtonText("Start |<");
    goToStartButton.addListener(this);

    // === End Button ===
    addAndMakeVisible(endButton);
    endButton.setButtonText("End >|");
    endButton.addListener(this);

    // === Mute Button ===
    addAndMakeVisible(muteButton);
    muteButton.setButtonText("Mute");
    muteButton.addListener(this);

    // === Volume Slider ===
    volumeSlider.setRange(0.0, 1.0, 0.01);
    volumeSlider.setValue(0.5);
    volumeSlider.addListener(this);
    addAndMakeVisible(volumeSlider);

    setSize(500, 250);
    setAudioChannels(0, 2);

    //adding labels
    addAndMakeVisible(titleLabel);
    addAndMakeVisible(authorLabel);
    addAndMakeVisible(durationLabel);

    titleLabel.setText("Title: ", juce::dontSendNotification);
    authorLabel.setText("Author: ", juce::dontSendNotification);
    durationLabel.setText("Duration: ", juce::dontSendNotification);

    // add playlist 
    addAndMakeVisible(audiolistbox);
    audiolistbox.setModel(this);
    audiolistbox.setRowHeight(30);
    setSize(800, 400);
    setAudioChannels(0, 2);

}

MainComponent::~MainComponent()
{
    shutdownAudio();
}

// ===== Audio callbacks =====
void MainComponent::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    transportSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void MainComponent::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
    transportSource.getNextAudioBlock(bufferToFill);
}

void MainComponent::releaseResources()
{
    transportSource.releaseResources();
}

// ===== GUI =====
void MainComponent::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::darkgrey);
}

void MainComponent::resized()
{
    int y = 20;

    loadButton.setBounds(20, y, 100, 40);
    playPauseButton.setBounds(140, y, 100, 40);
    goToStartButton.setBounds(260, y, 100, 40);
    endButton.setBounds(380, y, 100, 40);
    loopButton.setBounds(500, y, 100, 40);
    muteButton.setBounds(620, y, 100, 40);

    volumeSlider.setBounds(20, 80, getWidth() - 40, 30);

    titleLabel.setBounds(20, 120, 300, 30);
    authorLabel.setBounds(20, 150, 300, 30);
    durationLabel.setBounds(20, 180, 300, 30);


    audiolistbox.setBounds(20, 280, getWidth() - 40, getHeight() - 300);
}

// ===== Button actions =====
void MainComponent::buttonClicked(juce::Button* button)
{
    if (button == &loadButton)
    {
        fileChooser = std::make_unique<juce::FileChooser>(
            "Select an audio file...",
            juce::File{},
            "*.wav;*.mp3");

        fileChooser->launchAsync( // lambada function

            juce::FileBrowserComponent::openMode | juce::FileBrowserComponent::canSelectFiles | juce::FileBrowserComponent::canSelectMultipleItems,
            [this](const juce::FileChooser& audios)
            {
                juce::Array<juce::File> files = audios.getResults();
                for (auto file : files) {
                    audiolist.push_back(file);
                    audiolistbox.updateContent();


                    if (auto* reader = formatManager.createReaderFor(file))
                    {
                        transportSource.stop();
                        transportSource.setSource(nullptr);
                        readerSource.reset();

                        readerSource = std::make_unique<juce::AudioFormatReaderSource>(reader, true);
                        transportSource.setSource(readerSource.get(), 0, nullptr, reader->sampleRate);

                        // metadata 
                        auto metadata = reader->metadataValues;
                        juce::String title = metadata["Title"];
                        juce::String author = metadata["Author"];
                        juce::String year = metadata["Year"];
                        juce::String type = metadata["Type"];
                        juce::String duration = juce::String(reader->lengthInSamples / reader->sampleRate) + " sec";


                        if (title.isEmpty()) {
                            title = file.getFileName();
                            titleLabel.setText("Title: " + title, juce::dontSendNotification);


                        }
                        // show labels in GUI 
                        else {
                            titleLabel.setText("Title: " + title, juce::dontSendNotification);
                            authorLabel.setText("Author: " + author, juce::dontSendNotification);
                            durationLabel.setText("Duration: " + duration, juce::dontSendNotification);


                        }


                    }

                }

            });
    }
    else if (button == &playPauseButton)
    {
        if (isPlaying)
        {
            transportSource.stop();
            playPauseButton.setButtonText("Play >");
        }
        else
        {
            transportSource.start();
            playPauseButton.setButtonText("Pause ||");
        }
        isPlaying = !isPlaying;
    }
    else if (button == &loopButton)
    {
        isLooping = !isLooping;
        if (readerSource != nullptr)
            readerSource->setLooping(isLooping);
        loopButton.setButtonText(isLooping ? "Loop ON" : "Loop OFF");
    }


    else if (button == &goToStartButton)
    {
        transportSource.setPosition(0.0);
    }

    else if (button == &endButton)
    {
        transportSource.setPosition(transportSource.getLengthInSeconds());
    }
    else if (button == &muteButton)
    {
        if (!isMuted)
        {
            previousVolume = (float)volumeSlider.getValue(); // حفظ القيمة الحالية
            transportSource.setGain(0.0f);
            muteButton.setButtonText("Unmute");
        }
        else
        {
            transportSource.setGain(previousVolume);         // استرجاع الصوت
            muteButton.setButtonText("Mute");
        }
        isMuted = !isMuted;
    }

}


void MainComponent::sliderValueChanged(juce::Slider* slider)
{
    if (slider == &volumeSlider)
    {

        if (isMuted)
        {
            isMuted = false;
            muteButton.setButtonText("Mute");
        }

        transportSource.setGain((float)volumeSlider.getValue());
    }
}

// audiolist  gui

int MainComponent::getNumRows() {
    DBG("Number of audio files: " << audiolist.size());
    return audiolist.size();
}
void MainComponent::paintListBoxItem(int numaudios, juce::Graphics& g, int width, int height, bool audioselected) {

    if (audioselected) {
        g.fillAll(juce::Colours::yellow);
    }
    else {
        g.fillAll(juce::Colours::darkgrey);
    }
    if (numaudios < audiolist.size()) {
        g.drawText(audiolist[numaudios].getFileName(),
            10, 0, width - 10, height,
            juce::Justification::centredLeft, true);
    }
}

// audiolist player 
void MainComponent::selectedRowsChanged(int audioselected) {
    if (audioselected >= 0 && audioselected < audiolist.size()) {

        audioindex = audioselected;
        auto file = audiolist[audioindex];

        if (auto* reader = formatManager.createReaderFor(file))
        {

            transportSource.stop();
            transportSource.setSource(nullptr);
            readerSource.reset();

            readerSource = std::make_unique<juce::AudioFormatReaderSource>(reader, true);
            transportSource.setSource(readerSource.get(), 0, nullptr, reader->sampleRate);

            // metadata 
            auto metadata = reader->metadataValues;
            juce::String title = metadata["Title"];
            juce::String author = metadata["Author"];
            juce::String year = metadata["Year"];
            juce::String type = metadata["Type"];
            juce::String duration = juce::String(reader->lengthInSamples / reader->sampleRate) + " sec";



            if (title.isEmpty()) {
                title = file.getFileName();
                titleLabel.setText("Title: " + title, juce::dontSendNotification);
                authorLabel.setText("Author:--------" + author, juce::dontSendNotification);
                durationLabel.setText("Duration: " + duration, juce::dontSendNotification);

            }
            // show labels in GUI 
            else {
                titleLabel.setText("Title: " + title, juce::dontSendNotification);
                authorLabel.setText("Author: " + author, juce::dontSendNotification);
                durationLabel.setText("Duration: " + duration, juce::dontSendNotification);

            }
        }

    }


}
