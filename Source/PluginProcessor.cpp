#include "PluginProcessor.h"
#include "Parameters.h"
#include "PluginEditor.h"

//==============================================================================
StereoChorusAudioProcessor::StereoChorusAudioProcessor()
    : parameters(*this, nullptr, "StereoChorusParameters", {
            std::make_unique<AudioParameterFloat>(NAME_DW, "Dry/Wet", 0.0f, 1.0f, DEFAULT_DW),
            std::make_unique<AudioParameterFloat>(NAME_DT, "Delay time (s)", NormalisableRange<float>(MIN_DELAY_TIME, MAX_DELAY_TIME, 0.001f, 0.7f), DEFAULT_DT),
            std::make_unique<AudioParameterFloat>(NAME_FREQ, "Rate (Hz)", NormalisableRange<float>(0.1f, 5.0f, 0.01f, 0.3f), DEFAULT_FREQ),
            std::make_unique<AudioParameterChoice>(NAME_WF, "Waveform", StringArray{ "Sin", "Tri", "Saw up", "Saw down"}, DEFAULT_WF),
            std::make_unique<AudioParameterFloat>(NAME_AM, "Mod amount (s)", NormalisableRange<float>(0.004f, MAX_DELAY_TIME / 2.0f, 0.001f), DEFAULT_AM),
            std::make_unique<AudioParameterFloat>(NAME_PD, "Phase Delta", 0.0f, 1.0f, DEFAULT_PD)
        })
{
    parameters.addParameterListener(NAME_DW, this);
    mix.setMix(DEFAULT_DW);

    parameters.addParameterListener(NAME_DT, this);

    parameters.addParameterListener(NAME_FREQ, this);
    parameters.addParameterListener(NAME_WF, this);
    parameters.addParameterListener(NAME_PD, this);
    LFO.setFrequency(DEFAULT_FREQ);
    LFO.setWaveform(DEFAULT_WF);
    LFO.setPhaseDelta(DEFAULT_PD);

    parameters.addParameterListener(NAME_AM, this);
    delayTimeParam.setAmount(DEFAULT_AM);
    delayTimeParam.setParametro(DEFAULT_DT);
}

StereoChorusAudioProcessor::~StereoChorusAudioProcessor()
{
}

//==============================================================================
void StereoChorusAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    mix.prepareToPlay(sampleRate, samplesPerBlock);
    delay.prepareToPlay(sampleRate, samplesPerBlock);
    LFO.prepareToPlay(sampleRate);
    delayTimeParam.prepareToPlay(sampleRate);

    timeModBuffer.setSize(2, samplesPerBlock);
}

void StereoChorusAudioProcessor::releaseResources()
{
    mix.releaseResources();
    delay.releaseResources();
    timeModBuffer.setSize(0, 0);
}

void StereoChorusAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    const auto numSamples = buffer.getNumSamples();

    auto totalNumInputChannels  = getTotalNumInputChannels();

    LFO.getNextAudioBlock(timeModBuffer, numSamples);

    delayTimeParam.processBlock(timeModBuffer, numSamples);

    mix.setDry(buffer);

    delay.processBlock(buffer, timeModBuffer);

    mix.merge(buffer);
}

void StereoChorusAudioProcessor::parameterChanged(const String& paramID, float newvalue)
{
    if (paramID == NAME_DW)
    {
        mix.setMix(newvalue);
    }

    if (paramID == NAME_FREQ)
    {
        LFO.setFrequency(newvalue);
    }

    if (paramID == NAME_WF)
    {
        LFO.setWaveform(newvalue);
    }

    if (paramID == NAME_PD)
    {
        LFO.setPhaseDelta(newvalue);
    }

    if (paramID == NAME_DT)
    {
        delayTimeParam.setParametro(newvalue);
    }

    if (paramID == NAME_AM)
    {
        delayTimeParam.setAmount(newvalue);
    }
}

//==============================================================================
juce::AudioProcessorEditor* StereoChorusAudioProcessor::createEditor()
{
    return new PluginEditor(*this, parameters);
}

//==============================================================================
void StereoChorusAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    auto state = parameters.copyState();
    std::unique_ptr<XmlElement> xml(state.createXml());
    copyXmlToBinary(*xml, destData);
}

void StereoChorusAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    std::unique_ptr<XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));
    if (xmlState.get() != nullptr)
        if (xmlState->hasTagName(parameters.state.getType()))
            parameters.replaceState(ValueTree::fromXml(*xmlState));
}

//==============================================================================
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new StereoChorusAudioProcessor();
}
