## cupsnode
CUPS (Common Unix Printing System) native bindings for node.js
### Description
The library provides native bindings for the CUPS Programming API. The library uses CUPS 1.4 since upper versions are not supported in OS X 10.6 (Snow Leopard).

### Implemented Functions
Currently only few basic functions are implemented, however the following set is pretty enough for basic printing and job management purposes.
  * `cupsGetDests` 
  * `cupsGetDefault`
  * `cupsGetJobs`
  * `cupsPrintFile`
  * `cupsCancelJob`

### License
The MIT License (MIT)

Copyright (c) 2014 Alexey Taktarov, molefrog@gmail.com

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
