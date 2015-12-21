/*
Copyright 2007 nVidia, Inc.
Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. 

You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0 

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, 
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. 

See the License for the specific language governing permissions and limitations under the License.
*/
#pragma once
#ifndef _ZOH_BITS_H
#define _ZOH_BITS_H

// read/write a bitstream

#include "nvcore/Debug.h"

namespace ZOH {

class Bits
{
public:

	Bits(char *data, int maxdatabits) { nvAssert (data && maxdatabits > 0); bptr = bend = 0; bits = data; maxbits = maxdatabits; readonly = 0;}
	Bits(const char *data, int availdatabits) { nvAssert (data && availdatabits > 0); bptr = 0; bend = availdatabits; cbits = data; maxbits = availdatabits; readonly = 1;}

	void write(int value, int nbits) {
		nvAssert (nbits >= 0 && nbits < 32);
		nvAssert (sizeof(int)>= 4);
		for (int i=0; i<nbits; ++i)
			writeone(value>>i);
	}
	int read(int nbits) { 
		nvAssert (nbits >= 0 && nbits < 32);
		nvAssert (sizeof(int)>= 4);
		int out = 0;
		for (int i=0; i<nbits; ++i)
			out |= readone() << i;
		return out;
	}
	int getptr() { return bptr; }
	void setptr(int ptr) { nvAssert (ptr >= 0 && ptr < maxbits); bptr = ptr; }
	int getsize() { return bend; }

private:
	int	bptr;		// next bit to read
	int bend;		// last written bit + 1
	char *bits;		// ptr to user bit stream
	const char *cbits;	// ptr to const user bit stream
	int maxbits;	// max size of user bit stream
	char readonly;	// 1 if this is a read-only stream

	int readone() {
		nvAssert (bptr < bend);
		if (bptr >= bend) return 0;
		int bit = (readonly ? cbits[bptr>>3] : bits[bptr>>3]) & (1 << (bptr & 7));
		++bptr;
		return bit != 0;
	}
	void writeone(int bit) {
		nvAssert (!readonly); // "Writing a read-only bit stream"
		nvAssert (bptr < maxbits);
		if (bptr >= maxbits) return;
		if (bit&1)
			bits[bptr>>3] |= 1 << (bptr & 7);
		else
			bits[bptr>>3] &= ~(1 << (bptr & 7));
		if (bptr++ >= bend) bend = bptr;
	}
};

}

#endif
