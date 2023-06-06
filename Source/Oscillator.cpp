#include "Oscillator.h"

void Oscillator::prepareToPlay(double sr)
{
	samplePeriod = 1.0 / sr;
	frequency.reset(sr, GLIDE_TIME);
}

void Oscillator::setFrequency(float newValue)
{
	frequency.setTargetValue(newValue);
}

void Oscillator::setWaveform(float newValue)
{
	waveform = roundToInt(newValue);
}

void Oscillator::setPhaseDelta(float newValue)
{
	phaseDelta = newValue;
}

void Oscillator::getNextAudioBlock(AudioBuffer<float>& buffer, const int numSamples)
{
	const int numCh = buffer.getNumChannels();
	auto outputArray = buffer.getArrayOfWritePointers();

	for (int smp = 0; smp < numSamples; ++smp)
	{
		outputArray[0][smp] = getNextAudioSample(0);
		outputArray[1][smp] = getNextAudioSample(phaseDelta);

		phaseIncrement = frequency.getNextValue() * samplePeriod;
		currentPhase += phaseIncrement;
		currentPhase -= static_cast<int>(currentPhase);
	}
}

float Oscillator::getNextAudioSample(const float delta)
{
	auto sampleValue = 0.0f;
	float phase = fmod(currentPhase + delta, 1);

	switch (waveform)
	{
	case 0:
		sampleValue = sin(MathConstants<float>::twoPi * phase);
		break;
	case 1:
		sampleValue = 4.0f * abs(phase - 0.5f) - 1.0f;
		break;
	case 2:
		sampleValue = 2.0f * phase - 1.0f;
		break;
	case 3:
		sampleValue = -2.0f * phase - 1.0f;
		break;
	default:
		break;
	}

	return sampleValue;
}
