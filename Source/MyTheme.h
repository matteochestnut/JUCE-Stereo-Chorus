#pragma once
#include <JuceHeader.h>

#define BORDER_WIDTH 1.5f
#define SCALE_TO_KNOB_RATIO 0.85f

class MyLookAndFeel : public LookAndFeel_V4
{
public:
	MyLookAndFeel() {}

	void drawRotarySlider(Graphics& g,
		int x, int y, int width, int height,
		float sliderPosProportional, float rotaryStartAngle, float rotaryEndAngle,
		Slider& slider) override
	{
		const auto raggio = jmin(width, height) * 0.5f * SCALE_TO_KNOB_RATIO - BORDER_WIDTH * 0.5f;
		const auto centroX = x + width * 0.5f;
		const auto centroY = y + height * 0.5f;
		const auto topX = centroX - raggio;
		const auto topY = centroY - raggio;
		const auto diametro = raggio * 2;

		//const Colour brightColour = Colour(0xff2b2d31);
		//const Colour darkColour = Colour(0xff0d0d11);
		const Colour brightColour = Colour(214, 214, 214);
		const Colour darkColour = Colour(191, 191, 191);

		// knob body
		g.setGradientFill(ColourGradient(brightColour, topX, topY, darkColour.brighter(0.05), topX, topY * diametro, false));
		g.fillEllipse(topX, topY, diametro, diametro);

		// knob edge
		g.setGradientFill(ColourGradient(brightColour.brighter(0.9), topX, topY, darkColour.darker(0.9), topX, topY + diametro, false));
		g.drawEllipse(topX, topY, diametro, diametro, BORDER_WIDTH);

		// creating the "pointer" to the knob
		Path p;
		const auto pointerLunghezza = raggio * 0.33f;
		const auto pointerSpessore = 2.0f;
		p.addRectangle(-pointerSpessore * 0.5f, -raggio, pointerSpessore, pointerLunghezza);

		const auto angle = jmap(sliderPosProportional, rotaryStartAngle, rotaryEndAngle);
		p.applyTransform(AffineTransform::rotation(angle).translated(centroX, centroY)); //ruota il "puntatore" partendo dal centro della knob
		g.setGradientFill(ColourGradient(Colours::grey, topX, topY, Colours::grey.darker(0.2f), topX, topY + diametro, false));
		g.fillPath(p);

		// ticks
		Path punto, scala;
		auto tickSpessore = 2.0f;
		punto.addEllipse(-tickSpessore * 0.5f, -raggio / SCALE_TO_KNOB_RATIO, tickSpessore, tickSpessore);
		g.setColour(Colours::whitesmoke);

		for (int i = 0; i < numTicks; ++i)
		{
			scala = punto;
			auto normValue = pow((float)i / (numTicks - 1), (float)slider.getSkewFactor());
			float angle = jmap(normValue, rotaryStartAngle, rotaryEndAngle);
			scala.applyTransform(AffineTransform::rotation(angle).translated(centroX, centroY));
			g.fillPath(scala);
		}

	}

	void setNumTicks(int newValue)
	{
		numTicks = newValue;
	}

private:

	int numTicks = 21;
};
