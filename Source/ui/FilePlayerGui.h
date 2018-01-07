/*
  ==============================================================================

    FilePlayerGui.h
    Created: 22 Jan 2013 2:49:07pm
    Author:  tj3-mitchell

  ==============================================================================
*/

#ifndef H_FILEPLAYERGUI
#define H_FILEPLAYERGUI

#include "../JuceLibraryCode/JuceHeader.h"
#include "../audio/FilePlayer.h"

/**
 Gui for the FilePlayer class
 */
class FilePlayerGui :   public Component,
                        public Button::Listener,
                        public FilenameComponentListener,
                        public Slider::Listener,
                        public Timer
{
public:
    /**
     constructor - receives a reference to a FilePlayer object to control
     */
    FilePlayerGui(FilePlayer& filePlayer_);
    
    /**
     Destructor 
     */
    ~FilePlayerGui();
    
    //Component
    void resized() override;
    
    //Button Listener
    void buttonClicked(Button* button) override;
    
    void sliderValueChanged(Slider* slider) override;
    
    void timerCallback() override;
    //FilenameComponentListener
    void filenameComponentChanged (FilenameComponent* fileComponentThatHasChanged) override;
    

private:
    TextButton playButton;
    Slider playbackPosition;
    Slider fileGain;
    Slider LFreq;
    AudioVisualiserComponent waveform;
    ScopedPointer<FilenameComponent> fileChooser;
    
    FilePlayer& filePlayer;
    
};


#endif  // H_FILEPLAYERGUI
