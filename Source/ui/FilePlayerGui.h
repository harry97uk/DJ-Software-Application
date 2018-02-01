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
#include "../audio/EQ.hpp"
#include "../audio/Audio.h"
#include <thread>


/**
 Gui for the FilePlayer class
 */
class FilePlayerGui :   public Component,
                        public Button::Listener,
                        public FileBrowserListener,
                        public Slider::Listener,
                        public Timer
{
public:
    /**
     constructor - receives a reference to a FilePlayer object to control
     */
    FilePlayerGui(FilePlayer& filePlayer_, EQ& eq_);
    
    /**
     Destructor 
     */
    ~FilePlayerGui();
    
    /** Used to arrange objects in the FilePlayerGui */
    void resized() override;
    
    /**Button Listener - called when a button is clicked*/
     void buttonClicked(Button* button) override;
    
    /** Slider Listener - called when a slider is moved*/
    void sliderValueChanged(Slider* slider) override;
   
    /** Used to update playback slider position*/
    void timerCallback() override;
    
    /** FileBrowserListener */
    void loadFile();
    
    /** Function that does something when the slection is changed in the file browser
     @see FileBrowserListener*/
    void selectionChanged() override;
    
    /** Loads selected file if clicked once
     @see FileBrowserListener*/
    void fileClicked (const File& file, const MouseEvent& e) override;
    
    /** Loads selected file if clicked twice
     @see FileBrowserListener*/
    void fileDoubleClicked (const File& file) override;
    
    /** Called if the browser's root changes
     @see FileBrowserListener*/
    void browserRootChanged (const File& newRoot) override;
    
    /** @return the value of the gain slider for each file player for use with the overall crossfade slider*/
    float crossfadeFileGainValue();
private:
    TextButton playButton;
    TextButton startLoopButton, endLoopButton;
    Slider playbackPosition;
    Slider fileGain;
    Slider LFreq, MFreq, HFreq;
    Label gain, bass, mid, high, playback;
    AudioVisualiserComponent waveform;
    ScopedPointer<FileBrowserComponent> fileChooser;
    
    FilePlayer& filePlayer;
    EQ& eq;
    Atomic<bool> loop;
    
    
};


#endif  // H_FILEPLAYERGUI
