/*
  ==============================================================================

    SynthSound.h
    Created: 19 Jul 2018 9:29:50am
    Author:  Levi

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

class SynthSound : public SynthesiserSound
{
public:
	bool appliesToNote(int /*midi note pressed*/) {
		return true;
	}
	bool appliesToChannel(int /*The Channel*/) {
		return true;
	}
};