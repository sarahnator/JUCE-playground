/*
  ==============================================================================
    This file was auto-generated!
  ==============================================================================
*/

#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    // Make sure you set the size of the component after
    // you add any child components.
    setSize (800, 600);
    setAudioChannels(0, 2); //no input, 2 output

}

MainComponent::~MainComponent()
{
    // This shuts down the audio device and clears the audio source.
    shutdownAudio();
}

//==============================================================================
void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
     String message;
    message << "Preparing to play audio..." << newLine;
    message << " samplesPerBlockExpected = " << samplesPerBlockExpected << newLine;
    message << " sampleRate = " << sampleRate;
    Logger::getCurrentLogger()->writeToLog (message);
}

void MainComponent::getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill)
{
    for (auto channel = 0; channel < bufferToFill.buffer->getNumChannels(); ++channel)
    {
        // Get a pointer to the start sample in the buffer for this audio output channel
        auto* buffer = bufferToFill.buffer->getWritePointer (channel, bufferToFill.startSample);

        // Fill the required number of samples with noise between -0.125 and +0.125
        for (auto sample = 0; sample < bufferToFill.numSamples; ++sample)
            buffer[sample] = random.nextFloat() * 0.25f - 0.125f;
    }
}

void MainComponent::releaseResources()
{
     Logger::getCurrentLogger()->writeToLog ("Releasing audio resources");
    // This will be called when the audio device stops, or when it is being
    // restarted due to a setting change.

    // For more details, see the help for AudioProcessor::releaseResources()
}

//==============================================================================
void MainComponent::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(Colours::lightsteelblue);
    //ugly checkerboard
//     g.fillCheckerBoard(getBounds().toFloat(), 20, 20, Colours::skyblue, Colours::black);
    g.setColour(Colours::white);

    g.setFont(40.0f);
    g.drawText ("Hello, World!", getLocalBounds(), Justification::centred, true);
   
    Image myFace = ImageFileFormat::loadFrom(BinaryData::wtfIcon_png, BinaryData::wtfIcon_pngSize);

    AffineTransform transform = AffineTransform::scale (0.4f);
    g.addTransform(transform);

    g.drawImageWithin(myFace, getWidth(), 0, getWidth()/2, getHeight() + getHeight()/2, RectanglePlacement(), false);
    
    // You can add your drawing code here!
}

void MainComponent::resized()
{
    // This is called when the MainContentComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
}
