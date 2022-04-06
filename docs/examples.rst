Examples
========

Most of the examples require shader/texture/mesh data to be loaded. When
running examples your current directory should be examples/runtime.

::

    <bgfx_path>/examples/runtime $ ../../.build/<config>/bin/example-00-helloworldDebug

`00-helloworld <https://github.com/bkaradzic/bgfx/blob/master/examples/00-helloworld>`__
----------------------------------------------------------------------------------------

Initialization and debug text.

.. figure:: https://github.com/bkaradzic/bgfx/raw/master/examples/00-helloworld/screenshot.png
   :alt: example-00-helloworld

`01-cubes <https://github.com/bkaradzic/bgfx/blob/master/examples/01-cubes/cubes.cpp>`__
----------------------------------------------------------------------------------------

Rendering simple static mesh.

.. figure:: https://github.com/bkaradzic/bgfx/raw/master/examples/01-cubes/screenshot.png
   :alt: example-01-cubes

`02-metaballs <https://github.com/bkaradzic/bgfx/blob/master/examples/02-metaballs>`__
--------------------------------------------------------------------------------------

Rendering with transient buffers and embedding shaders.

.. raw:: html

    <div class="emscripten">
      <progress value="0" max="100" id="progress" hidden=1></progress>
    </div>

    <div class="spinner" id='spinner'></div>
    <div class="emscripten" id="status">Downloading...</div>
    <div class="emscripten_border">
      <canvas class="emscripten" id="canvas" oncontextmenu="event.preventDefault()"></canvas>
    </div>

    <script type='text/javascript'>
      var statusElement   = document.getElementById('status');
      var progressElement = document.getElementById('progress');
      var spinnerElement  = document.getElementById('spinner');

      var Module = {
        preRun: [],
        postRun: [],
        print: (function() {
          var element = document.getElementById('output');
          if (element) element.value = ''; // clear browser cache
          return function(text) {
            if (arguments.length > 1) text = Array.prototype.slice.call(arguments).join(' ');
            // These replacements are necessary if you render to raw HTML
            //text = text.replace(/&/g, "&amp;");
            //text = text.replace(/</g, "&lt;");
            //text = text.replace(/>/g, "&gt;");
            //text = text.replace('\n', '<br>', 'g');
            console.log(text);
            if (element) {
              element.value += text + "\n";
              element.scrollTop = element.scrollHeight; // focus on bottom
            }
          };
        })(),
        printErr: function(text) {
          if (arguments.length > 1) text = Array.prototype.slice.call(arguments).join(' ');
          if (0) { // XXX disabled for safety typeof dump == 'function') {
            dump(text + '\n'); // fast, straight to the real console
          } else {
            console.error(text);
          }
        },
        canvas: (function() {
          var canvas = document.getElementById('canvas');

          // As a default initial behavior, pop up an alert when webgl context is lost. To make your
          // application robust, you may want to override this behavior before shipping!
          // See http://www.khronos.org/registry/webgl/specs/latest/1.0/#5.15.2
          canvas.addEventListener("webglcontextlost", function(e) { alert('WebGL context lost. You will need to reload the page.'); e.preventDefault(); }, false);

          return canvas;
        })(),
        setStatus: function(text) {
          if (!Module.setStatus.last) Module.setStatus.last = { time: Date.now(), text: '' };
          if (text === Module.setStatus.text) return;
          var m = text.match(/([^(]+)\((\d+(\.\d+)?)\/(\d+)\)/);
          var now = Date.now();
          if (m && now - Date.now() < 30) return; // if this is a progress update, skip it if too soon
          if (m) {
            text = m[1];
            progressElement.value = parseInt(m[2])*100;
            progressElement.max = parseInt(m[4])*100;
            progressElement.hidden = false;
            spinnerElement.hidden = false;
          } else {
            progressElement.value = null;
            progressElement.max = null;
            progressElement.hidden = true;
            if (!text) spinnerElement.style.display = 'none';
          }
          statusElement.innerHTML = text;
        },
        totalDependencies: 0,
        monitorRunDependencies: function(left) {
          this.totalDependencies = Math.max(this.totalDependencies, left);
          Module.setStatus(left ? 'Preparing... (' + (this.totalDependencies-left) + '/' + this.totalDependencies + ')' : 'All downloads complete.');
        }
      };
      Module.setStatus('Downloading...');
      window.onerror = function(event) {
        // TODO: do not warn on ok events like simulating an infinite loop or exitStatus
        Module.setStatus('Exception thrown, see JavaScript console');
        spinnerElement.style.display = 'none';
        Module.setStatus = function(text) {
          if (text) Module.printErr('[post-exception status] ' + text);
        };
      };
    </script>
    <script async type="text/javascript" src="example-02-metaballsRelease.bc.js"></script>

`03-raymarch <https://github.com/bkaradzic/bgfx/blob/master/examples/03-raymarch>`__
------------------------------------------------------------------------------------

Updating shader uniforms.

.. figure:: https://github.com/bkaradzic/bgfx/raw/master/examples/03-raymarch/screenshot.png
   :alt: example-03-raymarch

`04-mesh <https://github.com/bkaradzic/bgfx/blob/master/examples/04-mesh>`__
----------------------------------------------------------------------------

Loading meshes.

.. figure:: https://github.com/bkaradzic/bgfx/raw/master/examples/04-mesh/screenshot.png
   :alt: example-04-mesh

`05-instancing <https://github.com/bkaradzic/bgfx/blob/master/examples/05-instancing>`__
----------------------------------------------------------------------------------------

Geometry instancing.

.. figure:: https://github.com/bkaradzic/bgfx/raw/master/examples/05-instancing/screenshot.png
   :alt: example-05-instancing

`06-bump <https://github.com/bkaradzic/bgfx/blob/master/examples/06-bump>`__
----------------------------------------------------------------------------

Loading textures.

.. figure:: https://github.com/bkaradzic/bgfx/raw/master/examples/06-bump/screenshot.png
   :alt: example-06-bump

`07-callback <https://github.com/bkaradzic/bgfx/blob/master/examples/07-callback>`__
------------------------------------------------------------------------------------

Implementing application specific callbacks for taking screen shots,
caching OpenGL binary shaders, and video capture.

`08-update <https://github.com/bkaradzic/bgfx/blob/master/examples/08-update>`__
--------------------------------------------------------------------------------

Updating textures.

`09-hdr <https://github.com/bkaradzic/bgfx/tree/master/examples/09-hdr>`__
--------------------------------------------------------------------------

Using multiple views with frame buffers, and view order remapping.

.. figure:: https://github.com/bkaradzic/bgfx/raw/master/examples/09-hdr/screenshot.png
   :alt: example-09-hdr

`10-font <https://github.com/bkaradzic/bgfx/tree/master/examples/10-font>`__
----------------------------------------------------------------------------

Use the font system to display text and styled text.

.. figure:: https://github.com/bkaradzic/bgfx/raw/master/examples/10-font/screenshot.png
   :alt: example-10-font

`11-fontsdf <https://github.com/bkaradzic/bgfx/tree/master/examples/11-fontsdf>`__
----------------------------------------------------------------------------------

Use a single distance field font to render text of various size.

.. figure:: https://github.com/bkaradzic/bgfx/raw/master/examples/11-fontsdf/screenshot.png
   :alt: example-11-fontsdf

`12-lod <https://github.com/bkaradzic/bgfx/tree/master/examples/12-lod>`__
--------------------------------------------------------------------------

Mesh LOD transitions.

.. figure:: https://github.com/bkaradzic/bgfx/raw/master/examples/12-lod/screenshot.png
   :alt: example-12-lod

`13-stencil <https://github.com/bkaradzic/bgfx/tree/master/examples/13-stencil>`__
----------------------------------------------------------------------------------

Stencil reflections and shadows.

.. figure:: https://github.com/bkaradzic/bgfx/raw/master/examples/13-stencil/screenshot.png
   :alt: example-13-stencil

`14-shadowvolumes <https://github.com/bkaradzic/bgfx/tree/master/examples/14-shadowvolumes>`__
----------------------------------------------------------------------------------------------

Shadow volumes.

.. figure:: https://github.com/bkaradzic/bgfx/raw/master/examples/14-shadowvolumes/screenshot.png
   :alt: example-14-shadowvolumes

`15-shadowmaps-simple <https://github.com/bkaradzic/bgfx/tree/master/examples/15-shadowmaps-simple>`__
------------------------------------------------------------------------------------------------------

.. figure:: https://github.com/bkaradzic/bgfx/raw/master/examples/15-shadowmaps-simple/screenshot.png
   :alt: example-15-shadowmaps-simple

`16-shadowmaps <https://github.com/bkaradzic/bgfx/tree/master/examples/16-shadowmaps>`__
----------------------------------------------------------------------------------------

.. figure:: https://github.com/bkaradzic/bgfx/raw/master/examples/16-shadowmaps/screenshot.png
   :alt: example-16-shadowmaps

`17-drawstress <https://github.com/bkaradzic/bgfx/blob/master/examples/17-drawstress>`__
----------------------------------------------------------------------------------------

60Hz
^^^^

Draw stress is CPU stress test to show what is the maximimum number of
draw calls while maintaining 60Hz frame rate. bgfx currently has default
limit of 64K draw calls per frame. You can increase this limit by
changing ``BGFX_CONFIG_MAX_DRAW_CALLS``.

+-----------------+----------------+--------------+------------------------+-------+----------+
| CPU             | Renderer       | GPU          | Arch/Compiler/OS       | Dim   | Calls    |
+=================+================+==============+========================+=======+==========+
| i7-4770K 4.2    | GL2.1          | 2xGTX780     | x64/VS2013/Win 8.1     | 51    | 132651   |
+-----------------+----------------+--------------+------------------------+-------+----------+
| i7-4770K 4.2    | DX11           | 2xGTX780     | x64/VS2013/Win 8.1     | 50    | 125000   |
+-----------------+----------------+--------------+------------------------+-------+----------+
| i7-4790K 4.0    | GL2.1          | GTX970       | x64/VS2015/Win 10      | 47    | 103823   |
+-----------------+----------------+--------------+------------------------+-------+----------+
| i7-4790K 4.0    | DX11           | GTX970       | x64/VS2015/Win 10      | 45    | 91125    |
+-----------------+----------------+--------------+------------------------+-------+----------+
| i7-4790K 4.0    | DX9            | GTX970       | x64/VS2013/Win 10      | 40    | 64000    |
+-----------------+----------------+--------------+------------------------+-------+----------+
| i5-3570 3.8     | NV 331.49      | GTX560Ti     | x64/GCC/Linux          | 40    | 64000+   |
+-----------------+----------------+--------------+------------------------+-------+----------+
| i7-920 2.66     | GL2.1          | GTX650Ti     | x64/VS2008/Win 7       | 38    | 54872    |
+-----------------+----------------+--------------+------------------------+-------+----------+
| i7-920 2.66     | GL2.1          | GTX650Ti     | x86/VS2008/Win 7       | 38    | 54872    |
+-----------------+----------------+--------------+------------------------+-------+----------+
| i7-6700K 4.0    | GL2.1          | Skylake GT2  | x64/GCC/Win 10         | 38    | 54872    |
+-----------------+----------------+--------------+------------------------+-------+----------+
| i7-4790K 4.0    | DX11           | R7 240       | x64/VS2015/Win 10      | 36    | 46656    |
+-----------------+----------------+--------------+------------------------+-------+----------+
| i7-920 2.66     | NV 331.113     | GTX650Ti     | x64/GCC/Linux          | 34    | 39304    |
+-----------------+----------------+--------------+------------------------+-------+----------+
| i7-6700K 4.0    | DX11           | Skylake GT2  | x64/GCC/Win 10         | 34    | 39304    |
+-----------------+----------------+--------------+------------------------+-------+----------+
| i7-4790K 4.0    | DX9            | R7 240       | x64/VS2015/Win 10      | 32    | 32768    |
+-----------------+----------------+--------------+------------------------+-------+----------+
| i7-920 2.66     | DX9            | GTX650Ti     | x64/GCC/Win 7          | 32    | 32768    |
+-----------------+----------------+--------------+------------------------+-------+----------+
| i7-920 2.66     | DX9            | GTX650Ti     | x64/VS2008/Win 7       | 32    | 32768    |
+-----------------+----------------+--------------+------------------------+-------+----------+
| i7-920 2.66     | DX9            | GTX650Ti     | x86/GCC/Win 7          | 30    | 27000    |
+-----------------+----------------+--------------+------------------------+-------+----------+
| i7-920 2.66     | DX9            | GTX650Ti     | x86/VS2008/Win 7       | 30    | 27000    |
+-----------------+----------------+--------------+------------------------+-------+----------+
| i5-6200U 2.3    | DX11           | Intel 520    | x64/GCC/Win 10         | 30    | 27000    |
+-----------------+----------------+--------------+------------------------+-------+----------+
| i5-4250U 1.3    | GL2.1          | HD5000       | x64/Clang/OSX 10.9     | 28    | 21852    |
+-----------------+----------------+--------------+------------------------+-------+----------+
| Q8200 2.33      | NV 319.32      | GTX260       | x64/GCC/Linux          | 27    | 19683    |
+-----------------+----------------+--------------+------------------------+-------+----------+
| i7-6700K 4.0    | GL2.1          | Skylake GT2  | x64/GCC/Linux          | 27    | 19683    |
+-----------------+----------------+--------------+------------------------+-------+----------+
| i7-2600K 3.4    | DX9            | AMD6800      | x64/VS2012/Win 7       | 27    | 19683    |
+-----------------+----------------+--------------+------------------------+-------+----------+
| i7-2600K 3.4    | GL2.1          | AMD6800      | x64/VS2012/Win 7       | 26    | 17576    |
+-----------------+----------------+--------------+------------------------+-------+----------+
| i7-4770R 3.2    | Mesa 10.5.9    | HD5200       | x64/GCC/Linux          | 26    | 17576    |
+-----------------+----------------+--------------+------------------------+-------+----------+
| i5-6200U 2.3    | GL             | Intel 520    | x64/GCC/Win 10         | 26    | 17576    |
+-----------------+----------------+--------------+------------------------+-------+----------+
| i7-920 2.66     | DX9-Wine       | GTX650Ti     | x64/GCC/Linux          | 24    | 13824    |
+-----------------+----------------+--------------+------------------------+-------+----------+
| i5-6200U 2.3    | Mesa 10.5.9    | Intel 520    | x64/GCC/Linux          | 23    | 12167    |
+-----------------+----------------+--------------+------------------------+-------+----------+
| i7-4750HQ 2.0   | Mesa 10.0.1    | HD5200       | x64/GCC/Linux          | 22    | 10648    |
+-----------------+----------------+--------------+------------------------+-------+----------+
| i7-4750HQ 2.0   | Mesa 10.1.3    | HD5200       | x64/GCC/Linux          | 21    | 9261     |
+-----------------+----------------+--------------+------------------------+-------+----------+
| i7-920 2.66     | ES2-ANGLE      | GTX650Ti     | x86/VS2008/Win 7       | 21    | 9261     |
+-----------------+----------------+--------------+------------------------+-------+----------+
| Q8200 2.33      | Gallium 0.4    | AMD5770      | x64/GCC/Linux          | 21    | 9261     |
+-----------------+----------------+--------------+------------------------+-------+----------+
| i5-4250U 1.3    | ES2            | HD5000       | JIT/Clang/PNaCl 31     | 21    | 9261     |
+-----------------+----------------+--------------+------------------------+-------+----------+
| i5-4250U 1.3    | ES2            | HD5000       | x86/GCC/NaCl 31        | 20    | 8000     |
+-----------------+----------------+--------------+------------------------+-------+----------+
| Q8200 2.33      | Gallium 0.4    | GTX260       | x64/GCC/Linux          | 19    | 6859     |
+-----------------+----------------+--------------+------------------------+-------+----------+
| i5-2450M 2.5    | Mesa 10.2.0    | HD3000       | x64/GCC/Linux          | 19    | 6859     |
+-----------------+----------------+--------------+------------------------+-------+----------+
| i7-920 2.66     | ES2-PowerVR    | GTX650Ti     | x86/VS2008/Win 7       | 18    | 5832     |
+-----------------+----------------+--------------+------------------------+-------+----------+
| i7-920 2.66     | FF27-GL        | GTX650Ti     | JIT/Clang/W7-asm.js    | 17    | 4913     |
+-----------------+----------------+--------------+------------------------+-------+----------+
| i7-6700K 4.0    | DX9            | Skylake GT2  | x64/GCC/Win 10         | 16    | 4096     |
+-----------------+----------------+--------------+------------------------+-------+----------+
| i7-4750HQ 2.0   | Mesa 8.0.5     | LLVMPIPE     | x64/GCC/Linux          | 16    | 4096     |
+-----------------+----------------+--------------+------------------------+-------+----------+
| i5-6200U 2.3    | DX9            | Intel 520    | x64/GCC/Win 10         | 16    | 4096     |
+-----------------+----------------+--------------+------------------------+-------+----------+
| i7-920 2.66     | ES2-Qualcomm   | GTX650Ti     | x86/VS2008/Win 7       | 15    | 3375     |
+-----------------+----------------+--------------+------------------------+-------+----------+
| i7-920 2.66     | ES2            | GTX650Ti     | x64/GCC/NaCl 31        | 15    | 3375     |
+-----------------+----------------+--------------+------------------------+-------+----------+
| i7-920 2.66     | ES2            | GTX650Ti     | JIT/Clang/PNaCl 31     | 15    | 3375     |
+-----------------+----------------+--------------+------------------------+-------+----------+
| Q8200 2.33      | NV 319.32      | GTX260       | x64/GCC/NaCl 31        | 15    | 3375     |
+-----------------+----------------+--------------+------------------------+-------+----------+
| Q8200 2.33      | NV 319.32      | GTX260       | x64/GCC/PNaCl 31       | 15    | 3375     |
+-----------------+----------------+--------------+------------------------+-------+----------+
| '12 Nexus 7     | ES2            | Tegra3       | ARM/GCC/Android        | 15    | 3375     |
+-----------------+----------------+--------------+------------------------+-------+----------+
| i5-4250U 1.3    | ES2-FF27       | HD5000       | JIT/Clang/OSX-asm.js   | 15    | 3375     |
+-----------------+----------------+--------------+------------------------+-------+----------+
| i5-4250U 1.3    | Chrome33       | HD5000       | JIT/Clang/OSX-asm.js   | 15    | 3375     |
+-----------------+----------------+--------------+------------------------+-------+----------+
| iPad mini 2     | ES2            | PVR G6430    | ARM64/Clang/iOS7       | 15    | 3375     |
+-----------------+----------------+--------------+------------------------+-------+----------+
| i7-920 2.66     | Chrome33       | GTX650Ti     | JIT/Clang/W7-asm.js    | 14    | 2744     |
+-----------------+----------------+--------------+------------------------+-------+----------+
| i7-920 2.66     | FF27-ANGLE     | GTX650Ti     | JIT/Clang/W7-asm.js    | 14    | 2744     |
+-----------------+----------------+--------------+------------------------+-------+----------+
| '13 Nexus 10    | ES2            | Mali T604    | ARM/GCC/Android        | 13    | 2197     |
+-----------------+----------------+--------------+------------------------+-------+----------+
| iPhone 5        | ES2            | PVR SGX543   | ARM/Clang/iOS7         | 13    | 2197     |
+-----------------+----------------+--------------+------------------------+-------+----------+
| '13 Nexus 7     | ES2            | S4 Pro       | ARM/GCC/Android        | 12    | 1728     |
+-----------------+----------------+--------------+------------------------+-------+----------+
| iPad 2          | ES2            | PVR SGX543   | ARM/Clang/iOS6         | 12    | 1728     |
+-----------------+----------------+--------------+------------------------+-------+----------+
| AMD A4-5000     | Gallium 0.4    | HD8330/Kabini| x64/GCC/Linux          | 12    | 1728     |
+-----------------+----------------+--------------+------------------------+-------+----------+
| Xperia Z        | ES2            | Adreno320    | ARM/GCC/Android        | 11    | 1331     |
+-----------------+----------------+--------------+------------------------+-------+----------+
| iPod 4          | ES2            | PVR SGX535   | ARM/Clang/iOS6         | 7     | 343      |
+-----------------+----------------+--------------+------------------------+-------+----------+
| i7-920 2.66     | ES2-Mali       | GTX650Ti     | x86/VS2008/Windows7    | 6     | 216      |
+-----------------+----------------+--------------+------------------------+-------+----------+
| Creator CI20    | ES2            | PVR SGX540   | MIPS/GCC/Debian8       | 7     | 343      |
+-----------------+----------------+--------------+------------------------+-------+----------+
| i5-6200U 2.3    | ES2            | SwiftShader  | x64/GCC/Linux          | 6     | 216      |
+-----------------+----------------+--------------+------------------------+-------+----------+
| RaspberryPi     | ES2            | VC IV        | ARM/GCC/Raspbian       | 6     | 216      |
+-----------------+----------------+--------------+------------------------+-------+----------+

To test browsers in 60Hz mode following changes were made:

-  Firefox 27 about:config adjustments: ``webgl.prefer-native-gl true``
   (on Windows), and ``layout.frame_rate 500``.
-  Chrome 33 command line option: ``--disable-gpu-vsync``.

30Hz (test for browsers)
^^^^^^^^^^^^^^^^^^^^^^^^

By default browsers are using vsync, and don't have option to turn it
off programatically.

+----------------+------------+------------+--------------------------+-------+----------+
| CPU            | Renderer   | GPU        | Arch/Compiler/OS         | Dim   | Calls    |
+================+============+============+==========================+=======+==========+
| i7-920 2.66    | GL2.1      | GTX650Ti   | x64/VS2008/Win7          | 38    | 64000+   |
+----------------+------------+------------+--------------------------+-------+----------+
| i5-4250U 1.3   | GL2.1      | HD5000     | x64/Clang/OSX 10.9       | 36    | 46656    |
+----------------+------------+------------+--------------------------+-------+----------+
| i5-4250U 1.3   | Chrome34   | HD5000     | JIT/Clang/OSX-PNaCl 31   | 28    | 21952    |
+----------------+------------+------------+--------------------------+-------+----------+
| i5-4250U 1.3   | Chrome33   | HD5000     | JIT/Clang/OSX-PNaCl 31   | 27    | 19683    |
+----------------+------------+------------+--------------------------+-------+----------+
| i5-4250U 1.3   | FF28       | HD5000     | JIT/Clang/OSX-asm.js     | 25    | 15625    |
+----------------+------------+------------+--------------------------+-------+----------+
| i5-4250U 1.3   | FF36       | HD5000     | JIT/Clang/OSX-asm.js     | 25    | 15625    |
+----------------+------------+------------+--------------------------+-------+----------+
| i5-4250U 1.3   | Chrome41   | HD5000     | x64/GCC/OSX-NaCl 41      | 24    | 13824    |
+----------------+------------+------------+--------------------------+-------+----------+
| i5-4250U 1.3   | FF37       | HD5000     | JIT/Clang/OSX-asm.js     | 23    | 12167    |
+----------------+------------+------------+--------------------------+-------+----------+
| i5-4250U 1.3   | FF27       | HD5000     | JIT/Clang/OSX-asm.js     | 20    | 8000     |
+----------------+------------+------------+--------------------------+-------+----------+
| i7-920 2.66    | Chrome33   | GTX650Ti   | JIT/Clang/W7-PNaCl 31    | 20    | 8000     |
+----------------+------------+------------+--------------------------+-------+----------+
| i7-920 2.66    | Chrome34   | GTX650Ti   | JIT/Clang/W7-asm.js      | 18    | 5832     |
+----------------+------------+------------+--------------------------+-------+----------+
| i7-920 2.66    | Chrome33   | GTX650Ti   | JIT/Clang/W7-asm.js      | 18    | 5832     |
+----------------+------------+------------+--------------------------+-------+----------+
| i7-920 2.66    | FF28       | GTX650Ti   | JIT/Clang/W7-asm.js      | 18    | 5832     |
+----------------+------------+------------+--------------------------+-------+----------+
| i7-920 2.66    | FF27       | GTX650Ti   | JIT/Clang/W7-asm.js      | 18    | 5832     |
+----------------+------------+------------+--------------------------+-------+----------+
| i5-4250U 1.3   | Safari7    | HD5000     | JIT/Clang/OSX-asm.js     | 15    | 3375     |
+----------------+------------+------------+--------------------------+-------+----------+

`18-ibl <https://github.com/bkaradzic/bgfx/tree/master/examples/18-ibl>`__
--------------------------------------------------------------------------

Image-based lighting.

.. figure:: https://github.com/bkaradzic/bgfx/raw/master/examples/18-ibl/screenshot.png
   :alt: example-18-ibl

`19-oit <https://github.com/bkaradzic/bgfx/tree/master/examples/19-oit>`__
--------------------------------------------------------------------------

Weighted, Blended Order-Independent Transparency

.. figure:: https://github.com/bkaradzic/bgfx/raw/master/examples/19-oit/screenshot.png
   :alt: example-19-oit

`20-nanovg <https://github.com/bkaradzic/bgfx/tree/master/examples/20-nanovg>`__
--------------------------------------------------------------------------------

NanoVG is small antialiased vector graphics rendering library.

.. figure:: https://github.com/bkaradzic/bgfx/raw/master/examples/20-nanovg/screenshot.png
   :alt: example-20-nanovg

`21-deferred <https://github.com/bkaradzic/bgfx/tree/master/examples/21-deferred>`__
------------------------------------------------------------------------------------

MRT rendering and deferred shading.

.. figure:: https://github.com/bkaradzic/bgfx/raw/master/examples/21-deferred/screenshot.png
   :alt: example-21-deferred

`22-windows <https://github.com/bkaradzic/bgfx/tree/master/examples/22-windows>`__
----------------------------------------------------------------------------------

Rendering into multiple windows.

`23-vectordisplay <https://github.com/bkaradzic/bgfx/tree/master/examples/23-vectordisplay>`__
----------------------------------------------------------------------------------------------

Rendering lines as oldschool vectors.

.. figure:: https://github.com/bkaradzic/bgfx/raw/master/examples/23-vectordisplay/screenshot.png
   :alt: example-23-vectordisplay

`24-nbody <https://github.com/bkaradzic/bgfx/tree/master/examples/24-nbody>`__
------------------------------------------------------------------------------

N-body simulation with compute shaders using buffers.

.. figure:: https://github.com/bkaradzic/bgfx/raw/master/examples/24-nbody/screenshot.png
   :alt: example-24-nbody

`25-c99 <https://github.com/bkaradzic/bgfx/tree/master/examples/25-c99>`__
--------------------------------------------------------------------------

Initialization and debug text with C99 API.

`26-occlusion <https://github.com/bkaradzic/bgfx/tree/master/examples/26-occlusion>`__
--------------------------------------------------------------------------------------

Using occlusion query for conditional rendering.

.. figure:: https://github.com/bkaradzic/bgfx/raw/master/examples/26-occlusion/screenshot.png
   :alt: example-26-occlusion

`27-terrain <https://github.com/bkaradzic/bgfx/tree/master/examples/27-terrain>`__
----------------------------------------------------------------------------------

Terrain painting example.

.. figure:: https://github.com/bkaradzic/bgfx/raw/master/examples/27-terrain/screenshot.png
   :alt: example-27-terrain

`28-wireframe <https://github.com/bkaradzic/bgfx/tree/master/examples/28-wireframe>`__
--------------------------------------------------------------------------------------

Drawing wireframe mesh.

.. figure:: https://github.com/bkaradzic/bgfx/raw/master/examples/28-wireframe/screenshot.png
   :alt: example-28-wireframe

`29-debugdraw <https://github.com/bkaradzic/bgfx/tree/master/examples/29-debugdraw>`__
--------------------------------------------------------------------------------------

Debug draw.

.. figure:: https://github.com/bkaradzic/bgfx/raw/master/examples/29-debugdraw/screenshot.png
   :alt: example-29-debugdraw

`30-picking <https://github.com/bkaradzic/bgfx/tree/master/examples/30-picking>`__
--------------------------------------------------------------------------------------

Mouse picking via GPU readback.

.. figure:: https://github.com/bkaradzic/bgfx/raw/master/examples/30-picking/screenshot.png
   :alt: example-30-picking

`31-rsm <https://github.com/bkaradzic/bgfx/tree/master/examples/31-rsm>`__
--------------------------------------------------------------------------------------

Global Illumination with Reflective Shadow Map.

.. figure:: https://github.com/bkaradzic/bgfx/raw/master/examples/31-rsm/screenshot.png
   :alt: example-31-rsm

`32-particles <https://github.com/bkaradzic/bgfx/tree/master/examples/32-particles>`__
--------------------------------------------------------------------------------------

Particles.

.. figure:: https://github.com/bkaradzic/bgfx/raw/master/examples/32-particles/screenshot.png
   :alt: example-32-particles

`33-pom <https://github.com/bkaradzic/bgfx/tree/master/examples/33-pom>`__
--------------------------------------------------------------------------

Parallax occlusion mapping.

Reference(s):
 - `Exploring bump mapping with WebGL <http://apoorvaj.io/exploring-bump-mapping-with-webgl.html>`__

.. figure:: https://github.com/bkaradzic/bgfx/raw/master/examples/33-pom/screenshot.png
   :alt: example-33-pom

`34-mvs <https://github.com/bkaradzic/bgfx/tree/master/examples/34-mvs>`__
--------------------------------------------------------------------------

Multiple vertex streams.

.. figure:: https://github.com/bkaradzic/bgfx/raw/master/examples/34-mvs/screenshot.png
   :alt: example-34-mvs

`35-dynamic <https://github.com/bkaradzic/bgfx/tree/master/examples/35-dynamic>`__
----------------------------------------------------------------------------------

Dynamic buffers update.

.. figure:: https://github.com/bkaradzic/bgfx/raw/master/examples/35-dynamic/screenshot.png
   :alt: example-35-dynamic

`36-sky <https://github.com/bkaradzic/bgfx/tree/master/examples/36-sky>`__
--------------------------------------------------------------------------

Perez dynamic sky model.

.. figure:: https://github.com/bkaradzic/bgfx/raw/master/examples/36-sky/screenshot.png
   :alt: example-36-sky

`37-gpudrivenrendering <https://github.com/bkaradzic/bgfx/tree/master/examples/37-gpudrivenrendering>`__
--------------------------------------------------------------------------------------------------------

GPU-Driven Rendering.

Reference(s):
 - `Experiments in GPU-based occlusion culling <https://interplayoflight.wordpress.com/2017/11/15/experiments-in-gpu-based-occlusion-culling/>`__,
 - `Experiments in GPU-based occlusion culling part 2: MultiDrawIndirect and mesh lodding <https://interplayoflight.wordpress.com/2018/01/15/experiments-in-gpu-based-occlusion-culling-part-2-multidrawindirect-and-mesh-lodding/>`__,
 - `Porting GPU driven occlusion culling to bgfx <https://interplayoflight.wordpress.com/2018/03/05/porting-gpu-driven-occlusion-culling-to-bgfx/>`__.

.. figure:: https://github.com/bkaradzic/bgfx/raw/master/examples/37-gpudrivenrendering/screenshot.png
   :alt: example-37-gpudrivenrendering

`38-bloom <https://github.com/bkaradzic/bgfx/tree/master/examples/38-bloom>`__
------------------------------------------------------------------------------

Bloom.

Reference(s):
 - `Next Generation Post Processing in Call of Duty: Advanced Warfare <http://www.iryoku.com/next-generation-post-processing-in-call-of-duty-advanced-warfare>`__.

.. figure:: https://github.com/bkaradzic/bgfx/raw/master/examples/38-bloom/screenshot.png
   :alt: example-38-bloom

`39-assao <https://github.com/bkaradzic/bgfx/tree/master/examples/39-assao>`__
------------------------------------------------------------------------------

Adaptive Screen Space Ambient Occlusion.

Reference(s):
 - `Adaptive Screen Space Ambient Occlusion <https://software.intel.com/en-us/articles/adaptive-screen-space-ambient-occlusion>`__.

.. figure:: https://github.com/bkaradzic/bgfx/raw/master/examples/39-assao/screenshot.png
   :alt: example-39-assao

`40-svt <https://github.com/bkaradzic/bgfx/tree/master/examples/40-svt>`__
--------------------------------------------------------------------------

Sparse Virtual Textures.

.. figure:: https://github.com/bkaradzic/bgfx/raw/master/examples/40-svt/screenshot.png
   :alt: example-40-svt

`41-tess <https://github.com/bkaradzic/bgfx/tree/master/examples/41-tess>`__
----------------------------------------------------------------------------

Adaptive GPU Tessellation with Compute Shaders

Reference(s):
  - `Adaptive GPU Tessellation with Compute Shaders by Jad Khoury, Jonathan Dupuy, and Christophe Riccio <http://onrendering.com/data/papers/isubd/isubd.pdf>`__.

.. figure:: https://github.com/bkaradzic/bgfx/raw/master/examples/41-tess/screenshot.png
   :alt: example-41-tess

`42-bunnylod <https://github.com/bkaradzic/bgfx/tree/master/examples/42-bunnylod>`__
------------------------------------------------------------------------------------

Simple Polygon Reduction

Reference(s):
 - `Simple Polygon Reduction <https://web.archive.org/web/20020114194131/http://www.melax.com/polychop/>`__.
 - `A Simple, Fast,and Effective Polygon Reduction Algorithm <https://web.archive.org/web/20031204035320/http://www.melax.com/polychop/gdmag.pdf>`__.

.. figure:: https://github.com/bkaradzic/bgfx/raw/master/examples/42-bunnylod/screenshot.png
   :alt: example-42-bunnylod

`43-denoise <https://github.com/bkaradzic/bgfx/tree/master/examples/43-denoise>`__
----------------------------------------------------------------------------------

Denoise

Reference(s):
 - `Spatiotemporal Variance-Guided Filtering: Real-Time Reconstruction for Path-Traced Global Illumination. <https://web.archive.org/web/20170720213354/https://research.nvidia.com/sites/default/files/pubs/2017-07_Spatiotemporal-Variance-Guided-Filtering%3A/svgf_preprint.pdf>`__.
 - `Streaming G-Buffer Compression for Multi-Sample Anti-Aliasing <https://web.archive.org/web/20200807211002/https://software.intel.com/content/www/us/en/develop/articles/streaming-g-buffer-compression-for-multi-sample-anti-aliasing.html>`__.
 - `Edge-Avoiding À-Trous Wavelet Transform for fast Global Illumination Filtering <https://web.archive.org/web/20130412085423/https://www.uni-ulm.de/fileadmin/website_uni_ulm/iui.inst.100/institut/Papers/atrousGIfilter.pdf>`__.

.. figure:: https://github.com/bkaradzic/bgfx/raw/master/examples/43-denoise/screenshot.png
   :alt: example-43-denoise

`44-sss <https://github.com/bkaradzic/bgfx/tree/master/examples/44-sss>`__
--------------------------------------------------------------------------

Screen-Space Shadows

.. figure:: https://github.com/bkaradzic/bgfx/raw/master/examples/44-sss/screenshot.png
   :alt: example-44-sss

`45-bokeh <https://github.com/bkaradzic/bgfx/tree/master/examples/45-bokeh>`__
------------------------------------------------------------------------------

Bokeh Depth of Field

Reference(s):
 - `Bokeh depth of field in a single pass <https://web.archive.org/web/20201215123940/https://blog.tuxedolabs.com/2018/05/04/bokeh-depth-of-field-in-single-pass.html>`__.

.. figure:: https://github.com/bkaradzic/bgfx/raw/master/examples/45-bokeh/screenshot.png
   :alt: example-45-bokeh

`46-fsr <https://github.com/bkaradzic/bgfx/tree/master/examples/46-fsr>`__
------------------------------------------------------------------------------

AMD FidelityFX Super Resolution - high-quality solution for producing high resolution frames
from lower resolution inputs.

.. figure:: https://github.com/bkaradzic/bgfx/raw/master/examples/46-fsr/screenshot.png
   :alt: example-46-fsr
