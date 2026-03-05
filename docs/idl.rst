IDL — Interface Definition Language
====================================

bgfx uses a custom Interface Definition Language (IDL) to define its entire public API in a single
source-of-truth file: ``scripts/bgfx.idl``. From this file, code generators produce the C99 API,
C++ API, language bindings, and documentation — ensuring that all representations stay in sync.

For additional background and motivation, see the blog post:
`IDL — Interface Definition Language <https://bkaradzic.github.io/posts/idl/>`__.

Purpose
-------

The IDL serves several goals:

- **Single source of truth** — The API (types, functions, flags, enums, structs, handles) is
  declared once in ``bgfx.idl``. All generated outputs derive from this file.
- **Multi-language bindings** — Code generators read the IDL and produce bindings for C99, C#, D,
  Zig, Beef, C3, and potentially other languages.
- **Documentation generation** — The ``docs-rst.lua`` generator produces reStructuredText API
  reference documentation from the IDL.
- **Consistency** — Changes to the API only need to be made in one place. The code generators
  ensure that all bindings and documentation are updated automatically.

File overview
-------------

All IDL-related files live under ``scripts/``:

``bgfx.idl``
    The IDL source file. Contains all type definitions, function declarations, flag/enum
    definitions, struct layouts, handle types, documentation comments, and the section hierarchy
    for the generated docs.

``idl.lua``
    The IDL parser/runtime. Sets up the Lua environment that ``bgfx.idl`` executes in. Provides
    the DSL keywords (``typedef``, ``enum``, ``flag``, ``struct``, ``handle``, ``func``,
    ``funcptr``, ``section``, ``version``, etc.) as Lua metatable-driven constructors.

``codegen.lua``
    Shared code generation utilities. Reads the parsed IDL, resolves types, converts between
    naming conventions (CamelCase ↔ underscore_case), and provides template expansion for
    function signatures.

``bgfx-codegen.lua``
    The main code generator. Reads the IDL via ``codegen.lua`` and produces the C99 header,
    C++ header, C99-to-C++ bridge implementation, and the internal function ID tables.

``bindings-*.lua``
    Per-language binding generators (``bindings-cs.lua``, ``bindings-d.lua``, ``bindings-zig.lua``,
    ``bindings-bf.lua``, ``bindings-c3.lua``). Each reads the IDL and outputs the API in the
    target language's syntax and conventions.

``docs-rst.lua``
    Generates reStructuredText API reference documentation (``docs/bgfx.rst``) from the IDL.

Running the code generators
----------------------------

The code generators are invoked via the makefile at the repository root:

.. code-block:: bash

    make idl

This runs the Lua scripts that regenerate all C/C++ headers, language bindings, and documentation
from ``scripts/bgfx.idl``.

IDL syntax reference
---------------------

The IDL file is valid Lua, executed in a special environment that provides the DSL keywords.
Comments prefixed with ``---`` become documentation comments attached to the next declaration.

version
~~~~~~~

Declares the API version number:

.. code-block:: lua

    version(140)

typedef
~~~~~~~

Declares a type alias. These map IDL type names to their C/C++ equivalents:

.. code-block:: lua

    typedef "uint32_t"
    typedef "ViewId"
    typedef "CallbackI" { cname = "callback_interface" }

The optional table provides attributes. ``cname`` overrides the C binding name.

handle
~~~~~~

Declares an opaque handle type. Handles are type-safe 16-bit integers used to reference GPU
resources:

.. code-block:: lua

    handle "TextureHandle"
    handle "VertexBufferHandle"

enum
~~~~

Declares an enumeration. Each member can have a ``---`` documentation comment:

.. code-block:: lua

    enum.TextureFormat { comment = "Texture formats:", section = "Textures" }
        .BC1       --- DXT1 R5G6B5A1.
        .BC2       --- DXT3 R5G6B5A4.
        .Unknown   --- Compressed formats above.
        ()

The ``()`` sentinel marks the end of the enum (generates a ``Count`` member). The ``section``
attribute controls where this type appears in the generated documentation hierarchy.

flag
~~~~

Declares a bitfield flag type. Similar to ``enum``, but members represent individual bits:

.. code-block:: lua

    flag.StateWrite { bits = 64, base = 1, section = "State Flags", label = "Write" }
        .R     --- Enable R write.
        .G     --- Enable G write.
        .B     --- Enable B write.
        .A     --- Enable alpha write.
        .Z (39) --- Enable depth write.
        .Rgb  { "R",   "G", "B" }  --- Enable RGB write.
        .Mask { "Rgb", "A", "Z" }  --- Write all channels mask.

Attributes:

- ``bits`` — Total bit width (32 or 64).
- ``shift`` — Bit offset where this flag group starts.
- ``range`` — Number of bits in this group.
- ``base`` — Starting value for auto-numbering.
- ``section`` — Documentation section.
- ``label`` — Display label for documentation grouping.

A member with a number in parentheses (e.g. ``.Z (39)``) sets an explicit bit position. Members
with a table of names (e.g. ``.Rgb { "R", "G", "B" }``) define combined masks.

struct
~~~~~~

Declares a data structure with typed fields:

.. code-block:: lua

    struct.Init { ctor, section = "Initialization and Shutdown" }
        .type             "RendererType::Enum" --- Select rendering backend.
        .vendorId         "uint16_t"           --- Vendor PCI ID. See: `BGFX_PCI_ID_*`.
        .deviceId         "uint16_t"           --- Device ID.
        .capabilities     "uint64_t"           --- Capabilities initialization mask.
        .debug            "bool"               --- Enable device for debugging.
        .profile          "bool"               --- Enable device for profiling.

Attributes:

- ``ctor`` — Generate a constructor with default values.
- ``namespace`` — Nest this struct inside another (e.g. ``namespace = "Caps"`` produces
  ``Caps::Limits``).
- ``section`` — Documentation section.

func
~~~~

Declares a function. The first string is the return type, followed by named parameters:

.. code-block:: lua

    --- Advance to next frame.
    func.frame { section = "Frame" }
        "uint32_t"                      --- Current frame number.
        .flags "uint8_t"                --- Frame flags.
         { default = "BGFX_FRAME_NONE" }

Attributes:

- ``section`` — Documentation section.
- ``const`` — Mark as a const method (for class member functions).
- ``conly`` — Only emit in the C99 API, not in C++.
- ``cpponly`` — Only emit in the C++ API, not in C99.
- ``cppinline`` — Provide an inline C++ implementation string.

Parameters can have:

- ``{ default = "value" }`` — Default argument value.
- ``{ out }`` — Output parameter.
- ``{ inout }`` — Input/output parameter.

funcptr
~~~~~~~

Declares a function pointer type:

.. code-block:: lua

    funcptr.ReleaseFn
        "void"
        .ptr      "void*" --- Pointer to allocated data.
        .userData "void*" --- User defined data if needed.

section
~~~~~~~

Declares a documentation section for organizing the generated API reference. Sections form a
hierarchy based on their level (0 = top-level heading, 1 = chapter, 2+ = subsections):

.. code-block:: lua

    section("API Reference", 0)
    section("General", 1)
    section("Initialization and Shutdown", 2)

Types and functions reference their section via the ``section`` attribute. The documentation
generator (``docs-rst.lua``) uses the section tree to organize the output.

Documentation comments
~~~~~~~~~~~~~~~~~~~~~~~

Lines starting with ``---`` before a declaration become documentation comments. These are emitted
as Doxygen-style comments in the C/C++ headers and as descriptions in the generated docs:

.. code-block:: lua

    --- Render frame.
    ---
    --- @attention `bgfx::renderFrame` is a blocking call.
    ---
    --- @warning This call should only be used on platforms that don't
    ---   allow creating a separate rendering thread.
    ---
    func.renderFrame { section = "Platform specific" }
        "RenderFrame::Enum"
        .msecs "int32_t"
        { default = -1 }

Supported Doxygen tags in comments: ``@attention``, ``@warning``, ``@remarks``, ``@param``,
``@returns``.

Adding a new API function
--------------------------

To add a new function to the bgfx API:

1. Add the function declaration in ``scripts/bgfx.idl`` with the appropriate ``section`` attribute
   and ``---`` documentation comments.
2. Run ``make idl`` to regenerate all headers, bindings, and documentation.
3. Implement the function in ``src/bgfx.cpp`` (and the renderer backends if needed).
4. Verify the generated output in ``include/bgfx/bgfx.h``, ``include/bgfx/c99/bgfx.h``, and the
   binding files under ``bindings/``.
