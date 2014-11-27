/*
  ==============================================================================

    FilePlayer.cpp
    Created: 22 Jan 2013 2:49:14pm
    Author:  tj3-mitchell

  ==============================================================================
*/

#include "FilePlayer.h"

FilePlayer::FilePlayer() : thread("FilePlayThread")
{
    thread.startThread();
    currentAudioFileSource = NULL;
}

/**
 Destructor
 */
FilePlayer::~FilePlayer()
{
    audioTransportSource.setSource(0);//unload the current file
    deleteAndZero(currentAudioFileSource);//delete the current file
    
    thread.stopThread(100);
}

/**
 Starts or stops playback of the looper
 */
void FilePlayer::setPlaying (const bool newState)
{
    if(newState == true)
    {
        audioTransportSource.setPosition(0.0);
        audioTransportSource.start();
    }
    else
    {
        audioTransportSource.stop();
    }
}

/**
 Gets the current playback state of the looper
 */
bool FilePlayer::isPlaying () const
{
    return audioTransportSource.isPlaying();
}


/**
 Loads the specified file into the transport source
 */
void FilePlayer::loadFile(const File& newFile)
{
    // unload the previous file source and delete it..
    setPlaying(false);
    audioTransportSource.setSource (0);
    deleteAndZero (currentAudioFileSource);
    
    // create a new file source from the file..
    // get a format manager and set it up with the basic types (wav, ogg and aiff).
    AudioFormatManager formatManager;
    formatManager.registerBasicFormats();
    
    AudioFormatReader* reader = formatManager.createReaderFor (newFile);
    
    if (reader != 0)
    {
        //currentFile = audioFile;
        currentAudioFileSource = new AudioFormatReaderSource (reader, true);
        
        // ..and plug it into our transport source
        audioTransportSource.setSource (currentAudioFileSource,
                                   32768, // tells it to buffer this many samples ahead
                                   &thread,
                                   reader->sampleRate);
    }
}

//AudioSource
void FilePlayer::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    audioTransportSource.prepareToPlay (samplesPerBlockExpected, sampleRate);
}

void FilePlayer::releaseResources()
{
    audioTransportSource.releaseResources();
}

void FilePlayer::getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill)
{
    audioTransportSource.getNextAudioBlock (bufferToFill);
}
