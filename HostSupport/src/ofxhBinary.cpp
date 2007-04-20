/*
Software License :

Copyright (c) 2007, The Foundry Visionmongers Ltd. All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice,
this list of conditions and the following disclaimer.
* Redistributions in binary form must reproduce the above copyright notice,
this list of conditions and the following disclaimer in the documentation
and/or other materials provided with the distribution.
* Neither the name The Foundry Visionmongers Ltd, nor the names of its 
contributors may be used to endorse or promote products derived from this
software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "ofxhBinary.h"

namespace OFX {

  // actually open the binary.
  void Binary::load() {
#if defined (UNIX)
    _dlHandle = dlopen(_binaryPath.c_str(), RTLD_NOW);
#else
    _dlHandle = LoadLibrary(_binaryPath.c_str());
#endif
    if (_dlHandle == 0) {
      _invalid = true;
    }
  }

  /// close the binary
  void Binary::unload() {
    if (_dlHandle != 0) {
#if defined (UNIX)
      dlclose(_dlHandle);
#elif defined (WINDOWS)
      FreeLibrary(_dlHandle);
#endif
      _dlHandle = 0;
    }
  }

  /// look up a symbol in the binary file and return it as a pointer.
  /// returns null pointer if not found, or if the library is not loaded.
  void *Binary::findSymbol(const std::string &symbol) {
    if (_dlHandle != 0) {
#if defined(UNIX)
      return dlsym(_dlHandle, symbol.c_str());
#elif defined (WINDOWS)
      return GetProcAddress(_dlHandle, symbol.c_str());
#endif
    } else {
      return 0;
    }
  }
}