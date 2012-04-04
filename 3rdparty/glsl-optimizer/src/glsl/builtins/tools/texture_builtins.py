#!/usr/bin/python

import sys
import StringIO

# Bitfield constants for the 'variant' argument to generate_sigs
Proj = 1
Offset = 2
Single = 4

def vec_type(g, size):
    if size == 1:
        if g == "i":
            return "int"
        elif g == "u":
            return "uint"
        return "float"
    return g + "vec" + str(size)

# Get the sampler dimension - i.e. sampler3D gives 3
def get_sampler_dim(sampler_type):
    if sampler_type[0].isdigit():
        sampler_dim = int(sampler_type[0])
    elif sampler_type.startswith("Cube"):
        sampler_dim = 3
    else:
        assert False ("coord_dim: invalid sampler_type: " + sampler_type)
    return sampler_dim

# Get the coordinate dimension for a given sampler type.
# Array samplers also get +1 here since the layer is really an extra coordinate
def get_coord_dim(sampler_type):
    coord_dim = get_sampler_dim(sampler_type)
    if sampler_type.find("Array") != -1:
        coord_dim += 1
    return coord_dim

# Get the number of extra vector components (i.e. shadow comparitor)
def get_extra_dim(sampler_type, use_proj, unused_fields):
    extra_dim = unused_fields
    if sampler_type.find("Shadow") != -1:
        extra_dim += 1
    if use_proj:
        extra_dim += 1
    return extra_dim

def generate_sigs(g, tex_inst, sampler_type, variant = 0, unused_fields = 0):
    coord_dim = get_coord_dim(sampler_type)
    extra_dim = get_extra_dim(sampler_type, variant & Proj, unused_fields)
    offset_dim = get_sampler_dim(sampler_type)

    if variant & Single:
        return_type = "float"
    else:
        return_type = g + "vec4"

    # Print parameters
    print "   (signature", return_type
    print "     (parameters"
    print "       (declare (in) " + g + "sampler" + sampler_type + " sampler)"
    print "       (declare (in) " + vec_type("i" if tex_inst == "txf" else "", coord_dim + extra_dim) + " P)",
    if tex_inst == "txl":
        print "\n       (declare (in) float lod)",
    elif tex_inst == "txf":
        print "\n       (declare (in) int lod)",
    elif tex_inst == "txd":
        grad_type = vec_type("", coord_dim)
        print "\n       (declare (in) " + grad_type + " dPdx)",
        print "\n       (declare (in) " + grad_type + " dPdy)",

    if variant & Offset:
        print "\n       (declare (const_in) " + vec_type("i", offset_dim) + " offset)",
    if tex_inst == "txb":
        print "\n       (declare (in) float bias)",

    print ")\n     ((return (" + tex_inst, return_type, "(var_ref sampler)",

    # Coordinate
    if extra_dim > 0:
        print "(swiz " + "xyzw"[:coord_dim] + " (var_ref P))",
    else:
        print "(var_ref P)",

    if variant & Offset:
        print "(var_ref offset)",
    else:
        print "0",

    if tex_inst != "txf":
        # Projective divisor
        if variant & Proj:
            print "(swiz " + "xyzw"[coord_dim + extra_dim-1] + " (var_ref P))",
        else:
            print "1",

        # Shadow comparitor
        if sampler_type == "2DArrayShadow": # a special case:
            print "(swiz w (var_ref P))",   # ...array layer is z; shadow is w
        elif sampler_type.endswith("Shadow"):
            print "(swiz z (var_ref P))",
        else:
            print "()",

    # Bias/explicit LOD/gradient:
    if tex_inst == "txb":
        print "(var_ref bias)",
    elif tex_inst == "txl" or tex_inst == "txf":
        print "(var_ref lod)",
    elif tex_inst == "txd":
        print "((var_ref dPdx) (var_ref dPdy))",
    print "))))\n"

def generate_fiu_sigs(tex_inst, sampler_type, variant = 0, unused_fields = 0):
    generate_sigs("",  tex_inst, sampler_type, variant, unused_fields)
    generate_sigs("i", tex_inst, sampler_type, variant, unused_fields)
    generate_sigs("u", tex_inst, sampler_type, variant, unused_fields)

def start_function(name):
    sys.stdout = StringIO.StringIO()
    print "((function " + name

def end_function(fs, name):
    print "))"
    fs[name] = sys.stdout.getvalue();
    sys.stdout.close()

# Generate all the functions and store them in the supplied dictionary.
# This is better than writing them to actual files since they should never be
# edited; it'd also be easy to confuse them with the many hand-generated files.
#
# Takes a dictionary as an argument.
def generate_texture_functions(fs):
    start_function("texture")
    generate_fiu_sigs("tex", "1D")
    generate_fiu_sigs("tex", "2D")
    generate_fiu_sigs("tex", "3D")
    generate_fiu_sigs("tex", "Cube")
    generate_fiu_sigs("tex", "1DArray")
    generate_fiu_sigs("tex", "2DArray")
    generate_sigs("", "tex", "1DShadow", Single, 1);
    generate_sigs("", "tex", "2DShadow", Single);
    generate_sigs("", "tex", "CubeShadow", Single);
    generate_sigs("", "tex", "1DArrayShadow", Single);
    generate_sigs("", "tex", "2DArrayShadow", Single);

    generate_fiu_sigs("txb", "1D")
    generate_fiu_sigs("txb", "2D")
    generate_fiu_sigs("txb", "3D")
    generate_fiu_sigs("txb", "Cube")
    generate_fiu_sigs("txb", "1DArray")
    generate_fiu_sigs("txb", "2DArray")
    generate_sigs("", "txb", "1DShadow", Single, 1);
    generate_sigs("", "txb", "2DShadow", Single);
    generate_sigs("", "txb", "CubeShadow", Single);
    generate_sigs("", "txb", "1DArrayShadow", Single);
    generate_sigs("", "txb", "2DArrayShadow", Single);
    end_function(fs, "texture")

    start_function("textureProj")
    generate_fiu_sigs("tex", "1D", Proj)
    generate_fiu_sigs("tex", "1D", Proj, 2)
    generate_fiu_sigs("tex", "2D", Proj)
    generate_fiu_sigs("tex", "2D", Proj, 1)
    generate_fiu_sigs("tex", "3D", Proj)
    generate_sigs("", "tex", "1DShadow", Proj | Single, 1);
    generate_sigs("", "tex", "2DShadow", Proj | Single);

    generate_fiu_sigs("txb", "1D", Proj)
    generate_fiu_sigs("txb", "1D", Proj, 2)
    generate_fiu_sigs("txb", "2D", Proj)
    generate_fiu_sigs("txb", "2D", Proj, 1)
    generate_fiu_sigs("txb", "3D", Proj)
    generate_sigs("", "txb", "1DShadow", Proj | Single, 1);
    generate_sigs("", "txb", "2DShadow", Proj | Single);
    end_function(fs, "textureProj")

    start_function("textureLod")
    generate_fiu_sigs("txl", "1D")
    generate_fiu_sigs("txl", "2D")
    generate_fiu_sigs("txl", "3D")
    generate_fiu_sigs("txl", "Cube")
    generate_fiu_sigs("txl", "1DArray")
    generate_fiu_sigs("txl", "2DArray")
    generate_sigs("", "txl", "1DShadow", Single, 1);
    generate_sigs("", "txl", "2DShadow", Single);
    generate_sigs("", "txl", "1DArrayShadow", Single);
    end_function(fs, "textureLod")

    start_function("textureLodOffset")
    generate_fiu_sigs("txl", "1D", Offset)
    generate_fiu_sigs("txl", "2D", Offset)
    generate_fiu_sigs("txl", "3D", Offset)
    generate_fiu_sigs("txl", "1DArray", Offset)
    generate_fiu_sigs("txl", "2DArray", Offset)
    generate_sigs("", "txl", "1DShadow", Offset | Single, 1);
    generate_sigs("", "txl", "2DShadow", Offset | Single);
    generate_sigs("", "txl", "1DArrayShadow", Offset | Single);
    end_function(fs, "textureLodOffset")

    start_function("textureOffset")
    generate_fiu_sigs("tex", "1D", Offset)
    generate_fiu_sigs("tex", "2D", Offset)
    generate_fiu_sigs("tex", "3D", Offset)
    generate_fiu_sigs("tex", "1DArray", Offset)
    generate_fiu_sigs("tex", "2DArray", Offset)
    generate_sigs("", "tex", "1DShadow", Offset | Single, 1);
    generate_sigs("", "tex", "2DShadow", Offset | Single);
    generate_sigs("", "tex", "1DArrayShadow", Offset | Single);

    generate_fiu_sigs("txb", "1D", Offset)
    generate_fiu_sigs("txb", "2D", Offset)
    generate_fiu_sigs("txb", "3D", Offset)
    generate_fiu_sigs("txb", "1DArray", Offset)
    generate_fiu_sigs("txb", "2DArray", Offset)
    generate_sigs("", "txb", "1DShadow", Offset | Single, 1);
    generate_sigs("", "txb", "2DShadow", Offset | Single);
    generate_sigs("", "txb", "1DArrayShadow", Offset | Single);
    end_function(fs, "textureOffset")

    start_function("texelFetch")
    generate_fiu_sigs("txf", "1D")
    generate_fiu_sigs("txf", "2D")
    generate_fiu_sigs("txf", "3D")
    generate_fiu_sigs("txf", "1DArray")
    generate_fiu_sigs("txf", "2DArray")
    end_function(fs, "texelFetch")

    start_function("texelFetchOffset")
    generate_fiu_sigs("txf", "1D", Offset)
    generate_fiu_sigs("txf", "2D", Offset)
    generate_fiu_sigs("txf", "3D", Offset)
    generate_fiu_sigs("txf", "1DArray", Offset)
    generate_fiu_sigs("txf", "2DArray", Offset)
    end_function(fs, "texelFetchOffset")

    start_function("textureProjOffset")
    generate_fiu_sigs("tex", "1D", Proj | Offset)
    generate_fiu_sigs("tex", "1D", Proj | Offset, 2)
    generate_fiu_sigs("tex", "2D", Proj | Offset)
    generate_fiu_sigs("tex", "2D", Proj | Offset, 1)
    generate_fiu_sigs("tex", "3D", Proj | Offset)
    generate_sigs("", "tex", "1DShadow", Proj | Offset | Single, 1);
    generate_sigs("", "tex", "2DShadow", Proj | Offset | Single);

    generate_fiu_sigs("txb", "1D", Proj | Offset)
    generate_fiu_sigs("txb", "1D", Proj | Offset, 2)
    generate_fiu_sigs("txb", "2D", Proj | Offset)
    generate_fiu_sigs("txb", "2D", Proj | Offset, 1)
    generate_fiu_sigs("txb", "3D", Proj | Offset)
    generate_sigs("", "txb", "1DShadow", Proj | Offset | Single, 1);
    generate_sigs("", "txb", "2DShadow", Proj | Offset | Single);
    end_function(fs, "textureProjOffset")

    start_function("textureProjLod")
    generate_fiu_sigs("txl", "1D", Proj)
    generate_fiu_sigs("txl", "1D", Proj, 2)
    generate_fiu_sigs("txl", "2D", Proj)
    generate_fiu_sigs("txl", "2D", Proj, 1)
    generate_fiu_sigs("txl", "3D", Proj)
    generate_sigs("", "txl", "1DShadow", Proj | Single, 1);
    generate_sigs("", "txl", "2DShadow", Proj | Single);
    end_function(fs, "textureProjLod")

    start_function("textureProjLodOffset")
    generate_fiu_sigs("txl", "1D", Proj | Offset)
    generate_fiu_sigs("txl", "1D", Proj | Offset, 2)
    generate_fiu_sigs("txl", "2D", Proj | Offset)
    generate_fiu_sigs("txl", "2D", Proj | Offset, 1)
    generate_fiu_sigs("txl", "3D", Proj | Offset)
    generate_sigs("", "txl", "1DShadow", Proj | Offset | Single, 1);
    generate_sigs("", "txl", "2DShadow", Proj | Offset | Single);
    end_function(fs, "textureProjLodOffset")

    start_function("textureGrad")
    generate_fiu_sigs("txd", "1D")
    generate_fiu_sigs("txd", "2D")
    generate_fiu_sigs("txd", "3D")
    generate_fiu_sigs("txd", "Cube")
    generate_fiu_sigs("txd", "1DArray")
    generate_fiu_sigs("txd", "2DArray")
    generate_sigs("", "txd", "1DShadow", Single, 1);
    generate_sigs("", "txd", "2DShadow", Single);
    generate_sigs("", "txd", "CubeShadow", Single);
    generate_sigs("", "txd", "1DArrayShadow", Single);
    generate_sigs("", "txd", "2DArrayShadow", Single);
    end_function(fs, "textureGrad")

    start_function("textureGradOffset")
    generate_fiu_sigs("txd", "1D", Offset)
    generate_fiu_sigs("txd", "2D", Offset)
    generate_fiu_sigs("txd", "3D", Offset)
    generate_fiu_sigs("txd", "Cube", Offset)
    generate_fiu_sigs("txd", "1DArray", Offset)
    generate_fiu_sigs("txd", "2DArray", Offset)
    generate_sigs("", "txd", "1DShadow", Offset | Single, 1);
    generate_sigs("", "txd", "2DShadow", Offset | Single);
    generate_sigs("", "txd", "1DArrayShadow", Offset | Single);
    generate_sigs("", "txd", "2DArrayShadow", Offset | Single);
    end_function(fs, "textureGradOffset")

    start_function("textureProjGrad")
    generate_fiu_sigs("txd", "1D", Proj)
    generate_fiu_sigs("txd", "1D", Proj, 2)
    generate_fiu_sigs("txd", "2D", Proj)
    generate_fiu_sigs("txd", "2D", Proj, 1)
    generate_fiu_sigs("txd", "3D", Proj)
    generate_sigs("", "txd", "1DShadow", Proj | Single, 1);
    generate_sigs("", "txd", "2DShadow", Proj | Single);
    end_function(fs, "textureProjGrad")

    start_function("textureProjGradOffset")
    generate_fiu_sigs("txd", "1D", Proj | Offset)
    generate_fiu_sigs("txd", "1D", Proj | Offset, 2)
    generate_fiu_sigs("txd", "2D", Proj | Offset)
    generate_fiu_sigs("txd", "2D", Proj | Offset, 1)
    generate_fiu_sigs("txd", "3D", Proj | Offset)
    generate_sigs("", "txd", "1DShadow", Proj | Offset | Single, 1);
    generate_sigs("", "txd", "2DShadow", Proj | Offset | Single);
    end_function(fs, "textureProjGradOffset")


    # ARB_texture_rectangle extension
    start_function("texture2DRect")
    generate_sigs("", "tex", "2DRect")
    end_function(fs, "texture2DRect")

    start_function("texture2DRectProj")
    generate_sigs("", "tex", "2DRect", Proj)
    generate_sigs("", "tex", "2DRect", Proj, 1)
    end_function(fs, "texture2DRectProj")

    start_function("shadow2DRect")
    generate_sigs("", "tex", "2DRectShadow")
    end_function(fs, "shadow2DRect")

    start_function("shadow2DRectProj")
    generate_sigs("", "tex", "2DRectShadow", Proj)
    end_function(fs, "shadow2DRectProj")

    # EXT_texture_array extension
    start_function("texture1DArray")
    generate_sigs("", "tex", "1DArray")
    generate_sigs("", "txb", "1DArray")
    end_function(fs, "texture1DArray")

    start_function("texture1DArrayLod")
    generate_sigs("", "txl", "1DArray")
    end_function(fs, "texture1DArrayLod")

    start_function("texture2DArray")
    generate_sigs("", "tex", "2DArray")
    generate_sigs("", "txb", "2DArray")
    end_function(fs, "texture2DArray")

    start_function("texture2DArrayLod")
    generate_sigs("", "txl", "2DArray")
    end_function(fs, "texture2DArrayLod")

    start_function("shadow1DArray")
    generate_sigs("", "tex", "1DArrayShadow")
    generate_sigs("", "txb", "1DArrayShadow")
    end_function(fs, "shadow1DArray")

    start_function("shadow1DArrayLod")
    generate_sigs("", "txl", "1DArrayShadow")
    end_function(fs, "shadow1DArrayLod")

    start_function("shadow2DArray")
    generate_sigs("", "tex", "2DArrayShadow")
    end_function(fs, "shadow2DArray")

    # ARB_shader_texture_lod extension
    start_function("texture1DGradARB")
    generate_fiu_sigs("txd", "1D")
    end_function(fs, "texture1DGradARB")

    start_function("texture2DGradARB")
    generate_fiu_sigs("txd", "2D")
    end_function(fs, "texture2DGradARB")
    
    start_function("texture2DGradEXT")
    generate_fiu_sigs("txd", "2D")
    end_function(fs, "texture2DGradEXT")

    start_function("texture3DGradARB")
    generate_fiu_sigs("txd", "3D")
    end_function(fs, "texture3DGradARB")

    start_function("textureCubeGradARB")
    generate_fiu_sigs("txd", "Cube")
    end_function(fs, "textureCubeGradARB")
    
    start_function("textureCubeGradEXT")
    generate_fiu_sigs("txd", "Cube")
    end_function(fs, "textureCubeGradEXT")

    start_function("texture1DProjGradARB")
    generate_fiu_sigs("txd", "1D", True)
    generate_fiu_sigs("txd", "1D", True, 2)
    end_function(fs, "texture1DProjGradARB")

    start_function("texture2DProjGradARB")
    generate_fiu_sigs("txd", "2D", True)
    generate_fiu_sigs("txd", "2D", True, 1)
    end_function(fs, "texture2DProjGradARB")
    
    start_function("texture2DProjGradEXT")
    generate_fiu_sigs("txd", "2D", True)
    generate_fiu_sigs("txd", "2D", True, 1)
    end_function(fs, "texture2DProjGradEXT")

    start_function("texture3DProjGradARB")
    generate_fiu_sigs("txd", "3D", True)
    end_function(fs, "texture3DProjGradARB")

    start_function("shadow1DGradARB")
    generate_sigs("", "txd", "1DShadow", False, 1)
    end_function(fs, "shadow1DGradARB")

    start_function("shadow1DProjGradARB")
    generate_sigs("", "txd", "1DShadow", True, 1)
    end_function(fs, "shadow1DProjGradARB")

    start_function("shadow2DGradARB")
    generate_sigs("", "txd", "2DShadow", False)
    end_function(fs, "shadow2DGradARB")

    start_function("shadow2DProjGradARB")
    generate_sigs("", "txd", "2DShadow", True)
    end_function(fs, "shadow2DProjGradARB")

    start_function("texture2DRectGradARB")
    generate_sigs("", "txd", "2DRect")
    end_function(fs, "texture2DRectGradARB")

    start_function("texture2DRectProjGradARB")
    generate_sigs("", "txd", "2DRect", True)
    generate_sigs("", "txd", "2DRect", True, 1)
    end_function(fs, "texture2DRectProjGradARB")

    start_function("shadow2DRectGradARB")
    generate_sigs("", "txd", "2DRectShadow", False)
    end_function(fs, "shadow2DRectGradARB")

    start_function("shadow2DRectProjGradARB")
    generate_sigs("", "txd", "2DRectShadow", True)
    end_function(fs, "shadow2DRectProjGradARB")

    # Deprecated (110/120 style) functions with silly names:
    start_function("texture1D")
    generate_sigs("", "tex", "1D")
    generate_sigs("", "txb", "1D")
    end_function(fs, "texture1D")

    start_function("texture1DLod")
    generate_sigs("", "txl", "1D")
    end_function(fs, "texture1DLod")
    
    start_function("texture1DProj")
    generate_sigs("", "tex", "1D", Proj)
    generate_sigs("", "tex", "1D", Proj, 2)
    generate_sigs("", "txb", "1D", Proj)
    generate_sigs("", "txb", "1D", Proj, 2)
    end_function(fs, "texture1DProj")

    start_function("texture1DProjLod")
    generate_sigs("", "txl", "1D", Proj)
    generate_sigs("", "txl", "1D", Proj, 2)
    end_function(fs, "texture1DProjLod")
    
    start_function("texture2D")
    generate_sigs("", "tex", "2D")
    generate_sigs("", "txb", "2D")
    end_function(fs, "texture2D")

    start_function("texture2DLod")
    generate_sigs("", "txl", "2D")
    end_function(fs, "texture2DLod")
    
    start_function("texture2DLodEXT")
    generate_sigs("", "txl", "2D")
    end_function(fs, "texture2DLodEXT")

    start_function("texture2DProj")
    generate_sigs("", "tex", "2D", Proj)
    generate_sigs("", "tex", "2D", Proj, 1)
    generate_sigs("", "txb", "2D", Proj)
    generate_sigs("", "txb", "2D", Proj, 1)
    end_function(fs, "texture2DProj")

    start_function("texture2DProjLod")
    generate_sigs("", "txl", "2D", Proj)
    generate_sigs("", "txl", "2D", Proj, 1)
    end_function(fs, "texture2DProjLod")
    
    start_function("texture2DProjLodEXT")
    generate_sigs("", "txl", "2D", Proj)
    generate_sigs("", "txl", "2D", Proj, 1)
    end_function(fs, "texture2DProjLodEXT")

    start_function("texture3D")
    generate_sigs("", "tex", "3D")
    generate_sigs("", "txb", "3D")
    end_function(fs, "texture3D")

    start_function("texture3DLod")
    generate_sigs("", "txl", "3D")
    end_function(fs, "texture3DLod")

    start_function("texture3DProj")
    generate_sigs("", "tex", "3D", Proj)
    generate_sigs("", "txb", "3D", Proj)
    end_function(fs, "texture3DProj")

    start_function("texture3DProjLod")
    generate_sigs("", "txl", "3D", Proj)
    end_function(fs, "texture3DProjLod")

    start_function("textureCube")
    generate_sigs("", "tex", "Cube")
    generate_sigs("", "txb", "Cube")
    end_function(fs, "textureCube")

    start_function("textureCubeLod")
    generate_sigs("", "txl", "Cube")
    end_function(fs, "textureCubeLod")
    
    start_function("textureCubeLodEXT")
    generate_sigs("", "txl", "Cube")
    end_function(fs, "textureCubeLodEXT")

    start_function("shadow1D")
    generate_sigs("", "tex", "1DShadow", False, 1)
    generate_sigs("", "txb", "1DShadow", False, 1)
    end_function(fs, "shadow1D")

    start_function("shadow1DLod")
    generate_sigs("", "txl", "1DShadow", False, 1)
    end_function(fs, "shadow1DLod")

    start_function("shadow1DProj")
    generate_sigs("", "tex", "1DShadow", Proj, 1)
    generate_sigs("", "txb", "1DShadow", Proj, 1)
    end_function(fs, "shadow1DProj")

    start_function("shadow1DProjLod")
    generate_sigs("", "txl", "1DShadow", Proj, 1)
    end_function(fs, "shadow1DProjLod")

    start_function("shadow2D")
    generate_sigs("", "tex", "2DShadow")
    generate_sigs("", "txb", "2DShadow")
    end_function(fs, "shadow2D")

    start_function("shadow2DLod")
    generate_sigs("", "txl", "2DShadow")
    end_function(fs, "shadow2DLod")

    start_function("shadow2DProj")
    generate_sigs("", "tex", "2DShadow", Proj)
    generate_sigs("", "txb", "2DShadow", Proj)
    end_function(fs, "shadow2DProj")

    start_function("shadow2DProjLod")
    generate_sigs("", "txl", "2DShadow", Proj)
    end_function(fs, "shadow2DProjLod")

    sys.stdout = sys.__stdout__
    return fs

# If you actually run this script, it'll print out all the functions.
if __name__ == "__main__":
    fs = {}
    generate_texture_functions(fs);
    for k, v in fs.iteritems():
        print v
