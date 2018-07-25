/*
  ==============================================================================

    SynthVoice.h
    Created: 19 Jul 2018 9:30:20am
    Author:  Levi

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "SynthSound.h"
#include "WavetableOscillator.h"
#include "maximilian.h"

class SynthVoice : public SynthesiserVoice {
public:
	double attack;
	double decay;
	double sustain;
	double release;

	bool canPlaySound(SynthesiserSound* sound) {
		return dynamic_cast<SynthSound*>(sound) != nullptr;
	}
	/*==================================================*/

	void startNote(int midiNoteNumber, float velocity, SynthesiserSound* sound, int currentPitchWheelPosition) {
		env1.trigger = 1;
		frequency = MidiMessage::getMidiNoteInHertz(midiNoteNumber);
		voice_count += 1;
		level = velocity;
	}

	void stopNote(float velocity, bool allowTailOff) {
		env1.trigger = 0;
		voice_count -= 1;
		allowTailOff = true;
		if (velocity == 0) {
			clearCurrentNote();
		}
	}

	void pitchWheelMoved(int controllerNumber, int newControllerValue) {

	}

	void controllerMoved(int controllerNumber, int newControllerValue) {

	}

	void renderNextBlock(AudioBuffer<float> &outputBuffer, int startSample, int numSamples) {
		env1.setAttack(attack);
		env1.setDecay(decay);
		env1.setSustain(sustain);
		env1.setRelease(release);
		for (auto sample = 0; sample < numSamples; sample++) {
			double wave = osc1.custom(frequency);
			double sound = env1.adsr(wave, env1.trigger) * level * 0.1;
			double default_filter = filt_velocity.lores(sound, 200 + (4500*level), 1);
			for (auto channel = 0; channel < outputBuffer.getNumChannels(); channel++) {

				outputBuffer.addSample(channel, startSample, default_filter);
			}
			startSample++;
		}
	}

	void pitchWheelMoved(int newPitchWheelValue) {
	
	}
private:
	double frequency;
	double level;
	maxiOsc osc1;
	maxiEnv env1;
	maxiFilter filt_velocity;

	int voice_count = 0;
};