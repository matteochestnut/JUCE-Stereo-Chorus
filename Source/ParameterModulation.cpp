#include "ParameterModulation.h"

void ParameterModulation::prepareToPlay(double sr)
{
	parametro.reset(sr, PM_SMOOTHING_TIME);
	amount.reset(sr, PM_SMOOTHING_TIME);
}

void ParameterModulation::setParametro(float newValue)
{
	parametro.setTargetValue(newValue);
}

void ParameterModulation::setAmount(float newValue)
{
	amount.setTargetValue(newValue);
}

void ParameterModulation::processBlock(AudioBuffer<float>& buffer, const int numSamples)
{
	auto modArray = buffer.getArrayOfWritePointers();
	auto numCh = buffer.getNumChannels();

	// scaling the modulating signal between 0 and 1
	for (int ch = 0; ch < numCh; ++ch)
	{
		FloatVectorOperations::add(modArray[ch], 1.0, numSamples);
		FloatVectorOperations::multiply(modArray[ch], 0.5f, numSamples);
	}

	// modulation dependent on the amount
	amount.applyGain(buffer, numSamples);

    // sum the modulating signal to the delay time from 'parametro'
	if (parametro.isSmoothing())
		for (int smp = 0; smp < numSamples; ++smp)
		{
			const auto param = parametro.getNextValue();

			for (int ch = 0; ch < numCh; ++ch)
				modArray[ch][smp] += param;
		}
	else
		for (int ch = 0; ch < numCh; ++ch)
			FloatVectorOperations::add(modArray[ch], parametro.getCurrentValue(), numSamples);

	// check if i'm in the maximum delay time range
	for (int ch = 0; ch < numCh; ++ch)
		FloatVectorOperations::min(modArray[ch], modArray[ch], MAX_DELAY_TIME + MAX_DELAY_TIME * 0.5f, numSamples);


}
