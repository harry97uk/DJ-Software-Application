/*
  ==============================================================================

    FilePlayerGui.cpp
    Created: 22 Jan 2013 2:49:07pm
    Author:  tj3-mitchell

  ==============================================================================
*/

#include "FilePlayerGui.h"

FilePlayerGui::FilePlayerGui (FilePlayer& filePlayer_, EQ& eq_) : filePlayer (filePlayer_), waveform(2), eq(eq_)

{
    playButton.setButtonText ("PLAY");
    playButton.addListener(this);
    addAndMakeVisible(&playButton);
    
    gain.setText("Gain", dontSendNotification);
    addAndMakeVisible(&gain);
    
    bass.setText("Bass", dontSendNotification);
    addAndMakeVisible(&bass);
    
    mid.setText("Mid", dontSendNotification);
    addAndMakeVisible(&mid);
    
    high.setText("High", dontSendNotification);
    addAndMakeVisible(&high);
    
    playback.setText("Playback Position", dontSendNotification);
    addAndMakeVisible(&playback);
    
    startLoopButton.setButtonText("START LOOP");
    startLoopButton.addListener(this);
    addAndMakeVisible(&startLoopButton);
    
    endLoopButton.setButtonText("END LOOP");
    endLoopButton.addListener(this);
    addAndMakeVisible(&endLoopButton);
    
    addAndMakeVisible(&waveform);
    waveform.pushBuffer(filePlayer.getBuffer());
    waveform.setColours(Colours::black, Colours::red);
    waveform.setSamplesPerBlock(256);
    waveform.setBufferSize(1024);
    
    
    playbackPosition.setRange(0, 1);
    playbackPosition.addListener(this);
    addAndMakeVisible(&playbackPosition);
    
    fileGain.setRange(0, 1);
    fileGain.setValue(1);
    fileGain.addListener(this);
    addAndMakeVisible(&fileGain);
    
    LFreq.setSliderStyle(juce::Slider::Rotary);
    LFreq.setRange(-1, 1);
    LFreq.setValue(0);
    LFreq.addListener(this);
    addAndMakeVisible(&LFreq);
    
    MFreq.setSliderStyle(juce::Slider::Rotary);
    MFreq.setRange(-1, 1);
    MFreq.setValue(0);
    MFreq.addListener(this);
    addAndMakeVisible(&MFreq);
    
    HFreq.setSliderStyle(juce::Slider::Rotary);
    HFreq.setRange(-1, 1);
    HFreq.setValue(0);
    HFreq.addListener(this);
    addAndMakeVisible(&HFreq);
    
    AudioFormatManager formatManager;
    formatManager.registerBasicFormats();
    fileChooser = new FileBrowserComponent(FileBrowserComponent::FileChooserFlags::openMode | FileBrowserComponent::FileChooserFlags::canSelectFiles | FileBrowserComponent::FileChooserFlags::canSelectDirectories, File("/Users/harrygardiner/Desktop"), nullptr, nullptr);
    fileChooser->addListener(this);
    addAndMakeVisible(fileChooser);
    
    
    
    
    
}

FilePlayerGui::~FilePlayerGui()
{
    
}

//Component
void FilePlayerGui::resized()
{
    playButton.setBounds ((getWidth()/4)*3, getHeight()-80, 60, 40);
    //startLoopButton.setBounds((getWidth()/4), getHeight()-80, 60, 40);
    //endLoopButton.setBounds((getWidth()/4)*2, getHeight()-80, 60, 40);
    fileChooser->setBounds (20, 300, getWidth()-20, 200);
    playbackPosition.setBounds(0, 20, getWidth(), 20);
    fileGain.setBounds(0, 40, getWidth(), 20);
    gain.setBounds(getWidth()/2, 30, getWidth()/2, 20);
    playback.setBounds(getWidth()/2, 10, getWidth()/2, 20);
    bass.setBounds(getWidth()/4, 50, getWidth()/2, 40);
    mid.setBounds(getWidth()/4, 110, getWidth()/2, 40);
    high.setBounds(getWidth()/4, 170, getWidth()/2, 40);
    LFreq.setBounds(0, 60, getWidth(), 60);
    MFreq.setBounds(0, 120, getWidth(), 60);
    HFreq.setBounds(0, 180, getWidth(), 60);
    waveform.setBounds(0, 240, getWidth(), 60);
}

//Button Listener
void FilePlayerGui::buttonClicked(Button* button)
{
    if (button == &playButton)
    {
        
        filePlayer.setPlaying(!filePlayer.isPlaying());
        timerCallback();
        if (filePlayer.isPlaying())
            playButton.setButtonText ("PAUSE");
        else
            playButton.setButtonText ("PLAY");
        
    }
    /**if (button == &startLoopButton)
    {
        
        loop = true;
        filePlayer.setLooping(loop.get(), filePlayer.getPosition());
        
    }
    if (button == &endLoopButton)
    {
        loop = false;
        filePlayer.setLooping(loop.get(), 0);
    }*/
}

//FilenameComponentListener
void FilePlayerGui::loadFile()
{
    

    File audioFile (fileChooser->getSelectedFile(1));
        
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

void FilePlayerGui::selectionChanged()
{
    
}

void FilePlayerGui::fileClicked(const File& file, const MouseEvent& e)
{
    File audioFile (fileChooser->getSelectedFile(1));
    
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

void FilePlayerGui::fileDoubleClicked(const File& file)
{
    File audioFile (fileChooser->getSelectedFile(1));
    
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

void FilePlayerGui::browserRootChanged(const File& newroot)
{
    
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
    else if (slider == &LFreq)
    {
        eq.setFreqGain(LFreq.getValue(), 0);
    }
    else if (slider == &MFreq)
    {
        eq.setFreqGain(MFreq.getValue(), 1);
    }
    else if (slider == &HFreq)
    {
        eq.setFreqGain(HFreq.getValue(), 2);
    }


}

float FilePlayerGui::crossfadeFileGainValue()
{
    return fileGain.getValue();
}

void FilePlayerGui::timerCallback()
{
    if (filePlayer.isPlaying() == true)
    {
        startTimer(250);
        playbackPosition.setValue(filePlayer.getPosition(),dontSendNotification);
    }
    else if (filePlayer.isPlaying() == false)
    {
        stopTimer();
    }
    
}


