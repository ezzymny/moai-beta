//
//  MemoryAudioSource.h
//  Part of UNTZ
//
//  Created by Robert Dalton Jr. (bob@retronyms.com) on 06/01/2011.
//  Copyright 2011 Retronyms. All rights reserved.
//

#ifndef MEMORYAUDIOSOURCE_H_
#define MEMORYAUDIOSOURCE_H_

#include "Untz.h"
#include "BufferedAudioSource.h"

class MemoryAudioSource : public BufferedAudioSource
{
public:
	MemoryAudioSource(UNTZ::SoundInfo& info, float* interleavedData, bool ownsData);
//	MemoryAudioSource(UInt32 sampleRate, UInt32 numChannels, UInt32 numFrames, Int16 *interleavedData);
    ~MemoryAudioSource() {};
    
    // AudioSource
	double getSampleRate();
	double getLength();
	UInt32 getNumChannels();
	UInt32 getBitsPerSample();
        
private:
	UNTZ::SoundInfo mInfo;
};

#endif