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
#include "FilePlayer.h"

/**
 Gui for the FilePlayer class
 */
class FilePlayerGui :   public Component,
                        public Button::Listener,
                        public FilenameComponentListener
{
public:
    /**
     constructor - receives a reference to a FilePlayer object to control
     */
    FilePlayerGui();
    
    /**
     Destructor 
     */
    ~FilePlayerGui();
    
    /**
     Sets the FilePlayer that this FilePlayer will control
     
     @param filePlayer_ reference to the fileplayer to control
     */
    void setFilePlayer (FilePlayer* filePlayer_);
    
    //Component
    void resized();
    
    //Button Listener
    void buttonClicked (Button* button);
    
    //FilenameComponentListener
    void filenameComponentChanged (FilenameComponent* fileComponentThatHasChanged);

private:
    TextButton playButton;
    FilenameComponent* fileChooser;
    
    FilePlayer* filePlayer;
    
};


#endif  // H_FILEPLAYERGUI
