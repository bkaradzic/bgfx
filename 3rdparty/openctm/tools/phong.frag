//-----------------------------------------------------------------------------
// Product:     OpenCTM tools
// File:        phong.frag
// Description: GLSL per-pixel phong shader - fragment shader
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

uniform bool uUseTexture;
uniform sampler2D uTex;

varying vec3 vNormal;
varying vec3 vPos;
varying vec4 vColor;

void main()
{
	vec3 n = normalize(vNormal);

	//  Calculate vertex color (vertex color * texture color)
	vec4 color = vColor;
	if(uUseTexture)
		color *= texture2D(uTex, gl_TexCoord[0].st);

	// Ambient term
//	vec4 ambient = color * gl_LightSource[0].ambient;
	vec4 ambient = color * gl_LightModel.ambient;

	// Diffuse term
	vec3 lightDir = normalize(gl_LightSource[0].position.xyz - vPos);
	float NdotL = abs(dot(n, lightDir));
	vec4 diffuse = color * gl_LightSource[0].diffuse * NdotL;

	// Specular term
	vec3 rVector = normalize(2.0 * n * dot(n, lightDir) - lightDir);
	vec3 viewVector = normalize(-vPos);
	float RdotV = dot(rVector, viewVector);
	vec4 specular = vec4(0.0);
	if(RdotV > 0.0)
		specular = vec4(0.4, 0.4, 0.4, 1.0) * gl_LightSource[0].specular * pow(RdotV, 20.0);

	gl_FragColor = ambient + diffuse + specular;
}
