/*
  ==============================================================================

    FilePlayerGui.cpp
    Created: 22 Jan 2013 2:49:07pm
    Author:  tj3-mitchell

  ==============================================================================
*/

#include "FilePlayerGui.h"

FilePlayerGui::FilePlayerGui (FilePlayer& filePlayer_) : filePlayer (filePlayer_)

{
    playButton.setButtonText (">");
    playButton.addListener(this);
    addAndMakeVisible(&playButton);
    
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
    playButton.setBounds (0, 0, getHeight(), getHeight());
    fileChooser->setBounds (getHeight(), 0, getWidth()-getHeight(), getHeight());
    
    
}

//Button Listener
void FilePlayerGui::buttonClicked (Button* button)
{
    if (button == &playButton)
    {
        filePlayer.setPlaying(!filePlayer.isPlaying());
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
