/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <sstream>

using namespace std;

//==============================================================================
NewProjectAudioProcessorEditor::NewProjectAudioProcessorEditor (NewProjectAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (600, 400);

	// Make visible the dials
	addAndMakeVisible(Attack_Slider);
	Attack_Slider.setRange(0, 2000);
	Attack_Slider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
	Attack_Slider.setTextBoxStyle(Slider::TextBoxBelow, true, Attack_Slider.getWidth(), 20);
	Attack_Slider.setTextBoxIsEditable(true);
	Attack_Slider.setTextValueSuffix(" ms");
	Attack_Slider.setValue(50);
	Attack_Slider.addListener(this);

	addAndMakeVisible(Decay_Slider);
	Decay_Slider.setRange(0, 2000);
	Decay_Slider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
	Decay_Slider.setTextBoxStyle(Slider::TextBoxBelow, true, Decay_Slider.getWidth(), 20);
	Decay_Slider.setTextBoxIsEditable(true);
	Decay_Slider.setTextValueSuffix(" ms");
	Decay_Slider.setValue(1000);
	Decay_Slider.addListener(this);

	addAndMakeVisible(Sustain_Slider);
	Sustain_Slider.setRange(0, 1);
	Sustain_Slider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
	Sustain_Slider.setTextBoxStyle(Slider::TextBoxBelow, true, Sustain_Slider.getWidth(), 20);
	Sustain_Slider.setTextBoxIsEditable(true);
	Sustain_Slider.setValue(0.7);
	Sustain_Slider.addListener(this);

	addAndMakeVisible(Release_Slider);
	Release_Slider.setRange(0, 2000);
	Release_Slider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
	Release_Slider.setTextBoxStyle(Slider::TextBoxBelow, true, Release_Slider.getWidth(), 20);
	Release_Slider.setTextBoxIsEditable(true);
	Release_Slider.setTextValueSuffix(" ms");
	Release_Slider.setValue(50);
	Release_Slider.addListener(this);
}

NewProjectAudioProcessorEditor::~NewProjectAudioProcessorEditor()
{
}

//==============================================================================
void NewProjectAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
   g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setColour (Colours::white);
    g.setFont (30.0f);
    g.drawFittedText ("Attack", 0, 200, 150, 30, Justification::centred, 1);
	g.drawFittedText("Decay", 150, 200, 150, 30, Justification::centred, 1);
	g.drawFittedText("Sustain", 300, 200, 150, 30, Justification::centred, 1);
	g.drawFittedText("Release", 450, 200, 150, 30, Justification::centred, 1);

	int width = this->getWidth();
	int height = this->getHeight()/2 + this->getHeight() / 3;
	int x = 0;
	int lastX = 0;
	int lastY = 0.93 * sin(x + 0.2*sin(2 * x) + 0.08*sin(1.48*x) + 0.03*sin(2.96*x)) + 0.05*sin(2.01 * x) + 0.2*sin(2.01*1.498*x);;

	for (int i = 0; i < width; i += 5) {
		x = i*(width / TWOPI);
		double y = 0.93 * sin(x + 0.2*sin(2 * x) + 0.08*sin(1.48*x) + 0.03*sin(2.96*x)) + 0.05*sin(2.01 * x) + 0.2*sin(2.01*1.498*x);
		y *= 50;
		g.setColour(Colours::azure);
		g.drawLine(lastX, lastY, i, 300 + y, 2);
		lastX = i;
		lastY = 300 + y;
	}
}

void NewProjectAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
	const int border = 20;
	const int dial_width = getWidth()/4;
	Attack_Slider.setBounds(0, 0, dial_width, dial_width);
	Decay_Slider.setBounds((getWidth() / 4), 0, dial_width, dial_width);
	Sustain_Slider.setBounds((getWidth() / 4) * 2, 0, dial_width, dial_width);
	Release_Slider.setBounds((getWidth() / 4) * 3, 0, dial_width, dial_width);
}

void NewProjectAudioProcessorEditor::buttonClicked(Button* btn){

}

void NewProjectAudioProcessorEditor::sliderValueChanged(Slider* sld) {
	if (sld == &Attack_Slider) {
		processor.p_attack = Attack_Slider.getValue();
	}else if (sld == &Decay_Slider) {
		processor.p_decay = Decay_Slider.getValue();
	}else if (sld == &Sustain_Slider) {
		processor.p_sustain = Sustain_Slider.getValue();
	}else if (sld == &Release_Slider) {
		processor.p_release = Release_Slider.getValue();
	}
}
