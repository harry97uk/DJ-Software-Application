/*
  ==============================================================================

    FilePlayerGui.cpp
    Created: 22 Jan 2013 2:49:07pm
    Author:  tj3-mitchell

  ==============================================================================
*/

#include "FilePlayerGui.h"

FilePlayerGui::FilePlayerGui (FilePlayer& filePlayer_) : filePlayer (filePlayer_), waveform(1)

{
    playButton.setButtonText (">");
    playButton.addListener(this);
    addAndMakeVisible(&playButton);
    
    addAndMakeVisible(&waveform);

    
    playbackPosition.setRange(0, 1);
    playbackPosition.addListener(this);
    addAndMakeVisible(&playbackPosition);
    
    fileGain.setRange(0, 1);
    fileGain.addListener(this);
    addAndMakeVisible(&fileGain);
    
    LFreq.setSliderStyle(juce::Slider::Rotary);
    LFreq.setRange(0, 1);
    LFreq.addListener(this);
    addAndMakeVisible(&LFreq);
    
    AudioFormatManager formatManager;
    formatManager.registerBasicFormats();
    fileChooser = new FilenameComponent ("audiofile",
                                         File::nonexistent,
                                         true, false, false,
                                         formatManager.getWildcardForAllFormats(),
                                         String::empty,
                                         "(choose a WAV or AIFF file)");
    fileChooser->addListener(this);
    addAndMakeVisible(fileChooser);
    
    
    
}

FilePlayerGui::~FilePlayerGui()
{
    
}

//Component
void FilePlayerGui::resized()
{
    playButton.setBounds (0, 0, 20, 20);
    fileChooser->setBounds (20, 0, getWidth()-20, 20);
    playbackPosition.setBounds(0, 20, getWidth(), 20);
    fileGain.setBounds(0, 40, getWidth(), 20);
    LFreq.setBounds(0, 60, getWidth(), 60);
    
}

//Button Listener
void FilePlayerGui::buttonClicked(Button* button)
{
    if (button == &playButton)
    {
        
        filePlayer.setPlaying(!filePlayer.isPlaying());
        timerCallback();
        
    }
}

//FilenameComponentListener
void FilePlayerGui::filenameComponentChanged (FilenameComponent* fileComponentThatHasChanged)
{
    if (fileComponentThatHasChanged == fileChooser)
    {
        File audioFile (fileChooser->getCurrentFile().getFullPathName());
        
        if(audioFile.existsAsFile())
        {
                filePlayer.loadFile(audioFile);
        }
        else
        {
            AlertWindow::showMessageBox (AlertWindow::WarningIcon,
                                         "sdaTransport",
                                         "Couldn't open file!\n\n");
        }
    }
}

void FilePlayerGui::sliderValueChanged(Slider* slider)
{
    if (slider == &playbackPosition)
    {
        filePlayer.setPosition(playbackPosition.getValue());
    }
    else if (slider == &fileGain)
    {
        filePlayer.setGain(fileGain.getValue());
    }

}

void FilePlayerGui::timerCallback()
{
    if (filePlayer.isPlaying() == true)
    {
        startTimer(250);
        playbackPosition.setValue(filePlayer.getPosition());
    }
    else if (filePlayer.isPlaying() == false)
    {
        stopTimer();
    }
}


