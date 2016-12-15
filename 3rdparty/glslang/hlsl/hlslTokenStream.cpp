//
//Copyright (C) 2016 Google, Inc.
//
//All rights reserved.
//
//Redistribution and use in source and binary forms, with or without
//modification, are permitted provided that the following conditions
//are met:
//
//    Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//
//    Redistributions in binary form must reproduce the above
//    copyright notice, this list of conditions and the following
//    disclaimer in the documentation and/or other materials provided
//    with the distribution.
//
//    Neither the name of Google, Inc., nor the names of its
//    contributors may be used to endorse or promote products derived
//    from this software without specific prior written permission.
//
//THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
//"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
//LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
//FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
//COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
//INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
//BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
//LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
//CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
//LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
//ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
//POSSIBILITY OF SUCH DAMAGE.
//

#include "hlslTokenStream.h"

namespace glslang {

void HlslTokenStream::pushPreToken(const HlslToken& tok)
{
    assert(preTokenStackSize < tokenBufferSize);
    preTokenStack[preTokenStackSize++] = tok;
}

HlslToken HlslTokenStream::popPreToken()
{
    assert(preTokenStackSize > 0);

    return preTokenStack[--preTokenStackSize];
}

void HlslTokenStream::pushTokenBuffer(const HlslToken& tok)
{
    tokenBuffer[tokenBufferPos] = tok;
    tokenBufferPos = (tokenBufferPos+1) % tokenBufferSize;
}

HlslToken HlslTokenStream::popTokenBuffer()
{
    // Back up
    tokenBufferPos = (tokenBufferPos+tokenBufferSize-1) % tokenBufferSize;

    return tokenBuffer[tokenBufferPos];
}

// Load 'token' with the next token in the stream of tokens.
void HlslTokenStream::advanceToken()
{
    pushTokenBuffer(token);
    if (preTokenStackSize > 0)
        token = popPreToken();
    else
        scanner.tokenize(token);
}

void HlslTokenStream::recedeToken()
{
    pushPreToken(token);
    token = popTokenBuffer();
}

// Return the current token class.
EHlslTokenClass HlslTokenStream::peek() const
{
    return token.tokenClass;
}

// Return true, without advancing to the next token, if the current token is
// the expected (passed in) token class.
bool HlslTokenStream::peekTokenClass(EHlslTokenClass tokenClass) const
{
    return peek() == tokenClass;
}

// Return true and advance to the next token if the current token is the
// expected (passed in) token class.
bool HlslTokenStream::acceptTokenClass(EHlslTokenClass tokenClass)
{
    if (peekTokenClass(tokenClass)) {
        advanceToken();
        return true;
    }

    return false;
}

} // end namespace glslang
