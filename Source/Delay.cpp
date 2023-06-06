#include "Delay.h"

void Delay::prepareToPlay(double sampleRate, int maxNumSamples)
{
	sr = sampleRate;
	memorySize = roundToInt((MAX_DELAY_TIME + (MAX_DELAY_TIME * 0.5f)) * sr) + maxNumSamples;
    // 4th parameter of setSize clearExtraSpace = true prevent noise burst when loading the plugin in a DAW
	delayMemory.setSize(2, memorySize, false, true);
}

void Delay::releaseResources()
{
	delayMemory.setSize(0, 0);
	memorySize = 0;
}

void Delay::processBlock(AudioBuffer<float>& buffer, AudioBuffer<float>& timeModBuffer)
{
	scrittura(buffer);
	lettura(buffer, timeModBuffer);
	avanzaIndiceScrittura(buffer.getNumSamples());
}

void Delay::scrittura(const AudioBuffer<float>& buffer)
{
	const auto numInputSamples = buffer.getNumSamples();
	const auto numChannels = buffer.getNumChannels();

	for (int ch = 0; ch < numChannels; ++ch)
	{
		if (indiceScrittura + numInputSamples <= memorySize)
			delayMemory.copyFrom(ch, indiceScrittura, buffer, ch, 0, numInputSamples);
		else
		{
			const int fittingSamples = memorySize - indiceScrittura;
			const int remainingSamples = numInputSamples - fittingSamples;

			delayMemory.copyFrom(ch, indiceScrittura, buffer, ch, 0, fittingSamples);
			delayMemory.copyFrom(ch, 0, buffer, ch, fittingSamples, remainingSamples);
		}
	}
}

void Delay::lettura(AudioBuffer<float>& buffer, AudioBuffer<float>& timeModBuffer)
{
	const auto numOutputSamples = buffer.getNumSamples();
	const auto numChannels = buffer.getNumChannels();
	const auto numModChannels = timeModBuffer.getNumChannels();

	auto outputArray = buffer.getArrayOfWritePointers();
	auto delayArray = delayMemory.getArrayOfWritePointers();
	auto modArray = timeModBuffer.getArrayOfReadPointers();

	for (int smp = 0; smp < numOutputSamples; ++smp)
	{
		for (int ch = 0; ch < numChannels; ++ch)
		{
			auto dt = modArray[jmin(ch, numModChannels - 1)][smp];

			auto actualWriteIndex = (indiceScrittura + smp) % memorySize;
			auto actualReadIndex = memorySize + actualWriteIndex - (dt * sr);

			auto integerPart = (int)actualReadIndex;
			auto fractionalPart = actualReadIndex - integerPart;

			auto A = (integerPart + memorySize) % memorySize;
			auto B = (A + 1) % memorySize;

			// linear interpolation
			auto sampleValue = delayArray[ch][A] * (1.0 - fractionalPart) + delayArray[ch][B] * fractionalPart;

			outputArray[ch][smp] = sampleValue;
		}
	}
}

void Delay::avanzaIndiceScrittura(int salto)
{
	indiceScrittura += salto;
	indiceScrittura %= memorySize;
}
