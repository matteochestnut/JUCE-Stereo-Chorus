#include "DryWet.h"

void DryWet::prepareToPlay(double sr, int maxNumSamples)
{
	dry.setSize(2, maxNumSamples);
	dryLevel.reset(sr, DW_SMOOTHING_TIME);
	wetLevel.reset(sr, DW_SMOOTHING_TIME);
	setMix(mix);
}

void DryWet::releaseResources()
{
	dry.setSize(0, 0);
}

void DryWet::setDry(const AudioBuffer<float>& buffer)
{
	for (int ch = buffer.getNumChannels(); --ch >= 0; )
		dry.copyFrom(ch, 0, buffer, ch, 0, buffer.getNumSamples());
}

void DryWet::merge(AudioBuffer<float>& buffer)
{
	auto numSamples = buffer.getNumSamples();
	wetLevel.applyGain(buffer, numSamples);
	dryLevel.applyGain(dry, numSamples);

	for (int ch = buffer.getNumChannels(); --ch >= 0; )
		buffer.addFrom(ch, 0, dry, ch, 0, numSamples);
}

void DryWet::setMix(const float newValue)
{
	mix = newValue;
	// constant power implementation of dry/wet knob
	dryLevel.setTargetValue(sqrt(1 - mix));
	wetLevel.setTargetValue(sqrt(mix));
}
