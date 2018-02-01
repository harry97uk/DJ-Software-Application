/*
  ==============================================================================

    FilePlayer.h
    Created: 22 Jan 2013 2:49:14pm
    Author:  tj3-mitchell

  ==============================================================================
*/

#ifndef H_FILEPLAYER
#define H_FILEPLAYER

#include "../JuceLibraryCode/JuceHeader.h"
#include "EQ.hpp"

/**
 Simple FilePlayer class - streams audio from a file.
 */
class FilePlayer : public AudioSource
{
public:
    /**
     Constructor
     */
    FilePlayer();
    
    /**
     Destructor
     */
    ~FilePlayer();
    
    /**
     Starts or stops playback of the looper
     */
    void setPlaying (const bool newState);
    
    /**
     Gets the current playback state of the looper
     */
    bool isPlaying () const;
    
    EQ& getEQ() { return eq; }
    
    /**
     Loads the specified file into the transport source
     @param newFile The file loaded in the FilePlayerGui FileBrowserComponent
     @see FilePlayerGui
     */
    void loadFile (const File& newFile);
    
    /** sets the position as a percentage of the total song in seconds
     @param newPosition a value of 0 to 1 that is available on a slider at the top*/
    void setPosition (float newPosition);
    
    /** @return the position of the song as a percentage of the total song in seconds */
    float getPosition();
    
    /** sets the amplitude of the audio coming from the file player
     @param sliderValue the value of a slider with the range 0 to 1*/
    void setGain (float sliderValue);
    
    /** @return the value of the amplitude in a range from 0 o 1*/
    float getGain();
    
    void setLooping(bool newState, float startPos);
    
    AudioSampleBuffer getBuffer();
    
    //AudioSource
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    void releaseResources() override;
    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override;
    
private:
    AudioFormatReaderSource* currentAudioFileSource;    //reads audio from the file
    AudioTransportSource audioTransportSource;	// this controls the playback of a positionable audio stream, handling the
                                            // starting/stopping and sample-rate conversion
    TimeSliceThread thread;//thread for the transport source
    EQ eq;
    AudioSampleBuffer waveform;
    CriticalSection loopLock;
    
};

#endif  // H_FILEPLAYER
