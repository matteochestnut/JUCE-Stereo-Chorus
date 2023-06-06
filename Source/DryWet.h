#pragma once
#include <JuceHeader.h>
#include "Parameters.h"

class DryWet
{
public:
	DryWet() {}
	~DryWet() {}

	void prepareToPlay(double sr, int maxNumSamples);

	void releaseResources();

	void setDry(const AudioBuffer<float>& buffer);

	void merge(AudioBuffer<float>& buffer);

	void setMix(const float newValue);

private:

	AudioBuffer<float> dry;

	SmoothedValue<float, ValueSmoothingTypes::Linear> dryLevel;
	SmoothedValue<float, ValueSmoothingTypes::Linear> wetLevel;

	float mix = 0.5;
	
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DryWet)
};

