#pragma once
#include <JuceHeader.h>
#include "DryWet.h"
#include "Delay.h"
#include "Oscillator.h"
#include "ParameterModulation.h"

class StereoChorusAudioProcessor  : public juce::AudioProcessor, public AudioProcessorValueTreeState::Listener
{
public:
    //==============================================================================
    StereoChorusAudioProcessor();
    ~StereoChorusAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

    //bool isBusesLayoutSupported (const BusesLayout& layouts) const override;

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    void parameterChanged(const String& paramID, float newvalue) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override { return true; };

    //==============================================================================
    const juce::String getName() const override { return JucePlugin_Name; };

    bool acceptsMidi() const override   { return false; };
    bool producesMidi() const override  { return false; };
    bool isMidiEffect() const override  { return false; };
    double getTailLengthSeconds() const override { return 0.0; };

    //==============================================================================
    int getNumPrograms() override    { return 1; };
    int getCurrentProgram() override { return 0; };
    void setCurrentProgram (int index) override {};
    const juce::String getProgramName(int index) override { return {}; };
    void changeProgramName (int index, const juce::String& newName) override {};

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

private:

    AudioProcessorValueTreeState parameters;

    DryWet mix;
    Delay delay;
    Oscillator LFO;
    ParameterModulation delayTimeParam;

    AudioBuffer<float> timeModBuffer;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (StereoChorusAudioProcessor)
};
