/* Copyright (c) 2005 - 2012 G-Truc Creation (www.g-truc.net)
 * Copyright © 2012 Intel Corporation
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#version 120
mat2 inverse(mat2 m)
{
   mat2 adj;
   adj[0][0] = m[1][1];
   adj[0][1] = -m[0][1];
   adj[1][0] = -m[1][0];
   adj[1][1] = m[0][0];
   float det = m[0][0] * m[1][1] - m[1][0] * m[0][1];
   return adj / det;
}

mat3 inverse(mat3 m)
{
   mat3 adj;
   adj[0][0] = + (m[1][1] * m[2][2] - m[2][1] * m[1][2]);
   adj[1][0] = - (m[1][0] * m[2][2] - m[2][0] * m[1][2]);
   adj[2][0] = + (m[1][0] * m[2][1] - m[2][0] * m[1][1]);
   adj[0][1] = - (m[0][1] * m[2][2] - m[2][1] * m[0][2]);
   adj[1][1] = + (m[0][0] * m[2][2] - m[2][0] * m[0][2]);
   adj[2][1] = - (m[0][0] * m[2][1] - m[2][0] * m[0][1]);
   adj[0][2] = + (m[0][1] * m[1][2] - m[1][1] * m[0][2]);
   adj[1][2] = - (m[0][0] * m[1][2] - m[1][0] * m[0][2]);
   adj[2][2] = + (m[0][0] * m[1][1] - m[1][0] * m[0][1]);

   float det = (+ m[0][0] * (m[1][1] * m[2][2] - m[1][2] * m[2][1])
		- m[0][1] * (m[1][0] * m[2][2] - m[1][2] * m[2][0])
		+ m[0][2] * (m[1][0] * m[2][1] - m[1][1] * m[2][0]));

   return adj / det;
}

mat4 inverse(mat4 m)
{
   float SubFactor00 = m[2][2] * m[3][3] - m[3][2] * m[2][3];
   float SubFactor01 = m[2][1] * m[3][3] - m[3][1] * m[2][3];
   float SubFactor02 = m[2][1] * m[3][2] - m[3][1] * m[2][2];
   float SubFactor03 = m[2][0] * m[3][3] - m[3][0] * m[2][3];
   float SubFactor04 = m[2][0] * m[3][2] - m[3][0] * m[2][2];
   float SubFactor05 = m[2][0] * m[3][1] - m[3][0] * m[2][1];
   float SubFactor06 = m[1][2] * m[3][3] - m[3][2] * m[1][3];
   float SubFactor07 = m[1][1] * m[3][3] - m[3][1] * m[1][3];
   float SubFactor08 = m[1][1] * m[3][2] - m[3][1] * m[1][2];
   float SubFactor09 = m[1][0] * m[3][3] - m[3][0] * m[1][3];
   float SubFactor10 = m[1][0] * m[3][2] - m[3][0] * m[1][2];
   float SubFactor11 = m[1][1] * m[3][3] - m[3][1] * m[1][3];
   float SubFactor12 = m[1][0] * m[3][1] - m[3][0] * m[1][1];
   float SubFactor13 = m[1][2] * m[2][3] - m[2][2] * m[1][3];
   float SubFactor14 = m[1][1] * m[2][3] - m[2][1] * m[1][3];
   float SubFactor15 = m[1][1] * m[2][2] - m[2][1] * m[1][2];
   float SubFactor16 = m[1][0] * m[2][3] - m[2][0] * m[1][3];
   float SubFactor17 = m[1][0] * m[2][2] - m[2][0] * m[1][2];
   float SubFactor18 = m[1][0] * m[2][1] - m[2][0] * m[1][1];

   mat4 adj;

   adj[0][0] = + (m[1][1] * SubFactor00 - m[1][2] * SubFactor01 + m[1][3] * SubFactor02);
   adj[1][0] = - (m[1][0] * SubFactor00 - m[1][2] * SubFactor03 + m[1][3] * SubFactor04);
   adj[2][0] = + (m[1][0] * SubFactor01 - m[1][1] * SubFactor03 + m[1][3] * SubFactor05);
   adj[3][0] = - (m[1][0] * SubFactor02 - m[1][1] * SubFactor04 + m[1][2] * SubFactor05);

   adj[0][1] = - (m[0][1] * SubFactor00 - m[0][2] * SubFactor01 + m[0][3] * SubFactor02);
   adj[1][1] = + (m[0][0] * SubFactor00 - m[0][2] * SubFactor03 + m[0][3] * SubFactor04);
   adj[2][1] = - (m[0][0] * SubFactor01 - m[0][1] * SubFactor03 + m[0][3] * SubFactor05);
   adj[3][1] = + (m[0][0] * SubFactor02 - m[0][1] * SubFactor04 + m[0][2] * SubFactor05);

   adj[0][2] = + (m[0][1] * SubFactor06 - m[0][2] * SubFactor07 + m[0][3] * SubFactor08);
   adj[1][2] = - (m[0][0] * SubFactor06 - m[0][2] * SubFactor09 + m[0][3] * SubFactor10);
   adj[2][2] = + (m[0][0] * SubFactor11 - m[0][1] * SubFactor09 + m[0][3] * SubFactor12);
   adj[3][2] = - (m[0][0] * SubFactor08 - m[0][1] * SubFactor10 + m[0][2] * SubFactor12);

   adj[0][3] = - (m[0][1] * SubFactor13 - m[0][2] * SubFactor14 + m[0][3] * SubFactor15);
   adj[1][3] = + (m[0][0] * SubFactor13 - m[0][2] * SubFactor16 + m[0][3] * SubFactor17);
   adj[2][3] = - (m[0][0] * SubFactor14 - m[0][1] * SubFactor16 + m[0][3] * SubFactor18);
   adj[3][3] = + (m[0][0] * SubFactor15 - m[0][1] * SubFactor17 + m[0][2] * SubFactor18);

   float det = (+ m[0][0] * adj[0][0]
		+ m[0][1] * adj[1][0]
		+ m[0][2] * adj[2][0]
		+ m[0][3] * adj[3][0]);

   return adj / det;
}

