Remotery
--------

A realtime CPU/GPU profiler hosted in a single C file with a viewer that runs in a web browser.

![screenshot](screenshot.png?raw=true)

Supported features:

* Lightweight instrumentation of multiple threads running on the CPU.
* Web viewer that runs in Chrome, Firefox and Safari. Custom WebSockets server
  transmits sample data to the browser on a latent thread.
* Profiles itself and shows how it's performing in the viewer.
* Can optionally sample CUDA/D3D11/OpenGL GPU activity.
* Console output for logging text.
* Console input for sending commands to your game.


Compiling
---------

* Windows (MSVC) - add lib/Remotery.c and lib/Remotery.h to your program. Set include
  directories to add Remotery/lib path. The required library ws2_32.lib should be picked
  up through the use of the #pragma comment(lib, "ws2_32.lib") directive in Remotery.c.

* Mac OS X (XCode) - simply add lib/Remotery.c and lib/Remotery.h to your program.

* Linux (GCC) - add the source in lib folder. Compilation of the code requires -pthreads for
  library linkage. For example to compile the same run: cc lib/Remotery.c sample/sample.c
  -I lib -pthread -lm

You can define some extra macros to modify what features are compiled into Remotery:

    Macro               Default     Description

    RMT_ENABLED         1           Disable this to not include any bits of Remotery in your build
    RMT_USE_TINYCRT     0           Used by the Celtoys TinyCRT library (not released yet)
    RMT_USE_CUDA        0           Assuming CUDA headers/libs are setup, allow CUDA profiling
    RMT_USE_D3D11       0           Assuming Direct3D 11 headers/libs are setup, allow D3D11 GPU profiling
    RMT_USE_OPENGL      0           Allow OpenGL GPU profiling (standalone except you must link to OpenGL which you already do if you use it)


Basic Use
---------

See the sample directory for further examples. A quick example:

    int main()
    {
        // Create the main instance of Remotery.
        // You need only do this once per program.
        Remotery* rmt;
        rmt_CreateGlobalInstance(&rmt);

        // Explicit begin/end for C
        {
            rmt_BeginCPUSample(LogText);
            rmt_LogText("Time me, please!");
            rmt_EndCPUSample();
        }

        // Scoped begin/end for C++
        {
            rmt_ScopedCPUSample(LogText);
            rmt_LogText("Time me, too!");
        }

        // Destroy the main instance of Remotery.
        rmt_DestroyGlobalInstance(rmt);
    }


Running the Viewer
------------------

Double-click or launch `vis/index.html` from the browser.


Sampling CUDA GPU activity
--------------------------

Remotery allows for profiling multiple threads of CUDA execution using different asynchronous streams
that must all share the same context. After initialising both Remotery and CUDA you need to bind the
two together using the call:

    rmtCUDABind bind;
    bind.context = m_Context;
    bind.CtxSetCurrent = &cuCtxSetCurrent;
    bind.CtxGetCurrent = &cuCtxGetCurrent;
    bind.EventCreate = &cuEventCreate;
    bind.EventDestroy = &cuEventDestroy;
    bind.EventRecord = &cuEventRecord;
    bind.EventQuery = &cuEventQuery;
    bind.EventElapsedTime = &cuEventElapsedTime;
    rmt_BindCUDA(&bind);

Explicitly pointing to the CUDA interface allows Remotery to be included anywhere in your project without
need for you to link with the required CUDA libraries. After the bind completes you can safely sample any
CUDA activity:

    CUstream stream;

    // Explicit begin/end for C
    {
        rmt_BeginCUDASample(UnscopedSample, stream);
        // ... CUDA code ...
        rmt_EndCUDASample(stream);
    }

    // Scoped begin/end for C++
    {
        rmt_ScopedCUDASample(ScopedSample, stream);
        // ... CUDA code ...
    }

Remotery supports only one context for all threads and will use cuCtxGetCurrent and cuCtxSetCurrent to
ensure the current thread has the context you specify in rmtCUDABind.context.


Sampling Direct3D 11 GPU activity
---------------------------------

Remotery allows sampling of GPU activity on your main D3D11 context. After initialising Remotery, you need
to bind it to D3D11 with a single call from the thread that owns the device context:

    // Parameters are ID3D11Device* and ID3D11DeviceContext*
    rmt_BindD3D11(d3d11_device, d3d11_context);

Sampling is then a simple case of:

    // Explicit begin/end for C
    {
        rmt_BeginD3D11Sample(UnscopedSample);
        // ... D3D code ...
        rmt_EndD3D11Sample();
    }

    // Scoped begin/end for C++
    {
        rmt_ScopedD3D11Sample(ScopedSample);
        // ... D3D code ...
    }

Support for multiple contexts can be added pretty easily if there is demand for the feature. When you shutdown
your D3D11 device and context, ensure you notify Remotery before shutting down Remotery itself:

    rmt_UnbindD3D11();


Sampling OpenGL GPU activity
----------------------------

Remotery allows sampling of GPU activity on your main OpenGL context. After initialising Remotery, you need
to bind it to OpenGL with the single call:

    rmt_BindOpenGL();

Sampling is then a simple case of:

    // Explicit begin/end for C
    {
        rmt_BeginOpenGLSample(UnscopedSample);
        // ... OpenGL code ...
        rmt_EndOpenGLSample();
    }

    // Scoped begin/end for C++
    {
        rmt_ScopedOpenGLSample(ScopedSample);
        // ... OpenGL code ...
    }

Support for multiple contexts can be added pretty easily if there is demand for the feature. When you shutdown
your OpenGL device and context, ensure you notify Remotery before shutting down Remotery itself:

    rmt_UnbindOpenGL();


Applying Configuration Settings
-------------------------------

Before creating your Remotery instance, you can configure its behaviour by retrieving its settings object:

    rmtSettings* settings = rmt_Settings();

Some important settings are:

    // Redirect any Remotery allocations to your own malloc/free, with an additional context pointer
    // that gets passed to your callbacks.
    settings->malloc;
    settings->free;
    settings->mm_context;

    // Specify an input handler that receives text input from the Remotery console, with an additional
    // context pointer that gets passed to your callback.
    settings->input_handler;
    settings->input_handler_context;
