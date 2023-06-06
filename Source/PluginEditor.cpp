/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 6.1.6

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2020 - Raw Material Software Limited.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...
#include "Parameters.h"
//[/Headers]

#include "PluginEditor.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
PluginEditor::PluginEditor (StereoChorusAudioProcessor& p, AudioProcessorValueTreeState& vts)
    : AudioProcessorEditor (&p), processor (p), valueTreeState (vts)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    timeSlider.reset (new juce::Slider ("Delay Time (s)"));
    addAndMakeVisible (timeSlider.get());
    timeSlider->setRange (0, 10, 0);
    timeSlider->setSliderStyle (juce::Slider::RotaryVerticalDrag);
    timeSlider->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 80, 20);
    timeSlider->setColour (juce::Slider::textBoxOutlineColourId, juce::Colour (0x008e989b));

    timeSlider->setBounds (50, 48, 150, 120);

    dryWetSlider.reset (new juce::Slider ("Dry / Wet"));
    addAndMakeVisible (dryWetSlider.get());
    dryWetSlider->setRange (0, 10, 0);
    dryWetSlider->setSliderStyle (juce::Slider::RotaryVerticalDrag);
    dryWetSlider->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 80, 20);
    dryWetSlider->setColour (juce::Slider::textBoxOutlineColourId, juce::Colour (0x008e989b));

    dryWetSlider->setBounds (400, 240, 150, 120);

    amountSlider.reset (new juce::Slider ("Depth"));
    addAndMakeVisible (amountSlider.get());
    amountSlider->setRange (0, 10, 0);
    amountSlider->setSliderStyle (juce::Slider::RotaryVerticalDrag);
    amountSlider->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 80, 20);
    amountSlider->setColour (juce::Slider::textBoxOutlineColourId, juce::Colour (0x008e989b));

    wfSlider.reset (new juce::Slider ("WaveForm"));
    addAndMakeVisible (wfSlider.get());
    wfSlider->setRange (0, 10, 0);
    wfSlider->setSliderStyle (juce::Slider::RotaryVerticalDrag);
    wfSlider->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 80, 20);
    wfSlider->setColour (juce::Slider::textBoxOutlineColourId, juce::Colour (0x008e989b));

    wfSlider->setBounds (48, 240, 150, 120);

    rateSlider.reset (new juce::Slider ("Rate (Hz)"));
    addAndMakeVisible (rateSlider.get());
    rateSlider->setRange (0, 10, 0);
    rateSlider->setSliderStyle (juce::Slider::RotaryVerticalDrag);
    rateSlider->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 80, 20);
    rateSlider->setColour (juce::Slider::textBoxOutlineColourId, juce::Colour (0x008e989b));

    rateSlider->setBounds (400, 48, 150, 120);

    phaseSlider.reset (new juce::Slider ("Phase Delta"));
    addAndMakeVisible (phaseSlider.get());
    phaseSlider->setRange (0, 10, 0);
    phaseSlider->setSliderStyle (juce::Slider::RotaryVerticalDrag);
    phaseSlider->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 80, 20);
    phaseSlider->setColour (juce::Slider::textBoxOutlineColourId, juce::Colour (0x008e989b));

    phaseSlider->setBounds (224, 240, 150, 120);


    //[UserPreSize]
    timeAttachment.reset(new SliderAttachment(valueTreeState, NAME_DT, *timeSlider));
    dryWetAttachment.reset(new SliderAttachment(valueTreeState, NAME_DW, *dryWetSlider));
    rateAttachment.reset(new SliderAttachment(valueTreeState, NAME_FREQ, *rateSlider));
    amountAttachment.reset(new SliderAttachment(valueTreeState, NAME_AM, *amountSlider));
    wfAttachment.reset(new SliderAttachment(valueTreeState, NAME_WF, *wfSlider));
    phaseAttachment.reset(new SliderAttachment(valueTreeState, NAME_PD, *phaseSlider));

    this->setLookAndFeel(&tema); //tutti gli slider eriditano il LookAndFeel dall'editor
    temaWF.setNumTicks(4);
    wfSlider->setLookAndFeel(&temaWF);
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

PluginEditor::~PluginEditor()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    timeAttachment.reset();
    dryWetAttachment.reset();
    rateAttachment.reset();
    amountAttachment.reset();
    wfAttachment.reset();
    phaseAttachment.reset();

    this->setLookAndFeel(nullptr);
    //[/Destructor_pre]

    timeSlider = nullptr;
    dryWetSlider = nullptr;
    amountSlider = nullptr;
    wfSlider = nullptr;
    rateSlider = nullptr;
    phaseSlider = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void PluginEditor::paint (juce::Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (juce::Colour (0xff323e44));

    {
        int x = 0, y = 0, width = 600, height = 400;
        juce::Colour fillColour1 = juce::Colour (0xff25c18e), fillColour2 = juce::Colour (0xff20dd4e);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setGradientFill (juce::ColourGradient (fillColour1,
                                             280.0f - 0.0f + x,
                                             8.0f - 0.0f + y,
                                             fillColour2,
                                             264.0f - 0.0f + x,
                                             368.0f - 0.0f + y,
                                             false));
        g.fillRect (x, y, width, height);
    }

    {
        int x = 29, y = 21, width = 200, height = 30;
        juce::String text (TRANS("Delay Time (ms)"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 197, y = 21, width = 200, height = 30;
        juce::String text (TRANS("Depth"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 373, y = 221, width = 200, height = 30;
        juce::String text (TRANS("Dry / Wet"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 24, y = 217, width = 200, height = 30;
        juce::String text (TRANS("Waveform"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 373, y = 21, width = 200, height = 30;
        juce::String text (TRANS("Rate (Hz)"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 200, y = 217, width = 200, height = 30;
        juce::String text (TRANS("Phase Delta"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void PluginEditor::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    amountSlider->setBounds (299 - (150 / 2), 108 - (120 / 2), 150, 120);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="PluginEditor" componentName=""
                 parentClasses="public juce::AudioProcessorEditor" constructorParams="StereoChorusAudioProcessor&amp; p, AudioProcessorValueTreeState&amp; vts"
                 variableInitialisers="AudioProcessorEditor (&amp;p), processor (p), valueTreeState (vts)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="600" initialHeight="400">
  <BACKGROUND backgroundColour="ff323e44">
    <RECT pos="0 0 600 400" fill="linear: 280 8, 264 368, 0=ff25c18e, 1=ff20dd4e"
          hasStroke="0"/>
    <TEXT pos="29 21 200 30" fill="solid: ffffffff" hasStroke="0" text="Delay Time (ms)"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="0"
          italic="0" justification="36"/>
    <TEXT pos="197 21 200 30" fill="solid: ffffffff" hasStroke="0" text="Depth"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="0"
          italic="0" justification="36"/>
    <TEXT pos="373 221 200 30" fill="solid: ffffffff" hasStroke="0" text="Dry / Wet"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="0"
          italic="0" justification="36"/>
    <TEXT pos="24 217 200 30" fill="solid: ffffffff" hasStroke="0" text="Waveform"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="0"
          italic="0" justification="36"/>
    <TEXT pos="373 21 200 30" fill="solid: ffffffff" hasStroke="0" text="Rate (Hz)"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="0"
          italic="0" justification="36"/>
    <TEXT pos="200 217 200 30" fill="solid: ffffffff" hasStroke="0" text="Phase Delta"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="0"
          italic="0" justification="36"/>
  </BACKGROUND>
  <SLIDER name="Delay Time (s)" id="d382969186e66fd3" memberName="timeSlider"
          virtualName="" explicitFocusOrder="0" pos="50 48 150 120" textboxoutline="8e989b"
          min="0.0" max="10.0" int="0.0" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="0"/>
  <SLIDER name="Dry / Wet" id="40599856c19fc91b" memberName="dryWetSlider"
          virtualName="" explicitFocusOrder="0" pos="400 240 150 120" textboxoutline="8e989b"
          min="0.0" max="10.0" int="0.0" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="0"/>
  <SLIDER name="Depth" id="68a4a86b1787e2db" memberName="amountSlider"
          virtualName="" explicitFocusOrder="0" pos="299c 108c 150 120"
          textboxoutline="8e989b" min="0.0" max="10.0" int="0.0" style="RotaryVerticalDrag"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1.0" needsCallback="0"/>
  <SLIDER name="WaveForm" id="7c8c9374d9228c9b" memberName="wfSlider" virtualName=""
          explicitFocusOrder="0" pos="48 240 150 120" textboxoutline="8e989b"
          min="0.0" max="10.0" int="0.0" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="0"/>
  <SLIDER name="Rate (Hz)" id="24d73705a9130b99" memberName="rateSlider"
          virtualName="" explicitFocusOrder="0" pos="400 48 150 120" textboxoutline="8e989b"
          min="0.0" max="10.0" int="0.0" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="0"/>
  <SLIDER name="Phase Delta" id="e3158a6bf6fc5ce" memberName="phaseSlider"
          virtualName="" explicitFocusOrder="0" pos="224 240 150 120" textboxoutline="8e989b"
          min="0.0" max="10.0" int="0.0" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

