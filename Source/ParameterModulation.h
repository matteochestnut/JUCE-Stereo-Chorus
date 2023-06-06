#pragma once
#include <JuceHeader.h>
#include "Parameters.h"

class ParameterModulation
{
public:
	ParameterModulation() {}
	~ParameterModulation() {}

	void prepareToPlay(double sr);

	void setParametro(float newValue);

	void setAmount(float newValue);

	void processBlock(AudioBuffer<float>& buffer, const int numSamples);

private:

	SmoothedValue<float, ValueSmoothingTypes::Linear> amount;
	SmoothedValue<float, ValueSmoothingTypes::Linear> parametro;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ParameterModulation)
};