//-----------------------------------------------------------------------------
// Product:     OpenCTM tools
// File:        phong.vert
// Description: GLSL per-pixel phong shader - vertex shader
//-----------------------------------------------------------------------------
// Copyright (c) 2009-2010 Marcus Geelnard
//
// This software is provided 'as-is', without any express or implied
// warranty. In no event will the authors be held liable for any damages
// arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
//
//     1. The origin of this software must not be misrepresented; you must not
//     claim that you wrote the original software. If you use this software
//     in a product, an acknowledgment in the product documentation would be
//     appreciated but is not required.
//
//     2. Altered source versions must be plainly marked as such, and must not
//     be misrepresented as being the original software.
//
//     3. This notice may not be removed or altered from any source
//     distribution.
//-----------------------------------------------------------------------------

varying vec3 vNormal;
varying vec3 vPos;
varying vec4 vColor;

void main()
{
	// Vertex normal
	vNormal = normalize(gl_NormalMatrix * gl_Normal);

	// Vertex position in eye coordinates
	vPos = vec3(gl_ModelViewMatrix * gl_Vertex);

	// Vertex color (used for the ambient and diffuse terms)
	vColor = gl_Color;

	// Texture coordinate
	gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;

	// Vertex position in screen coordinates
	gl_Position = ftransform();
}
