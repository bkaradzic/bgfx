/*
---------------------------------------------------------------------------
Open Asset Import Library (assimp)
---------------------------------------------------------------------------

Copyright (c) 2006-2015, assimp team

All rights reserved.

Redistribution and use of this software in source and binary forms,
with or without modification, are permitted provided that the following
conditions are met:

* Redistributions of source code must retain the above
  copyright notice, this list of conditions and the
  following disclaimer.

* Redistributions in binary form must reproduce the above
  copyright notice, this list of conditions and the
  following disclaimer in the documentation and/or other
  materials provided with the distribution.

* Neither the name of the assimp team, nor the names of its
  contributors may be used to endorse or promote products
  derived from this software without specific prior
  written permission of the assimp team.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
---------------------------------------------------------------------------
*/

#include "assimp_view.h"

namespace AssimpView {

//-------------------------------------------------------------------------------
// Handle mouse input for the FPS input behaviour
//
// Movement in x and y axis is possible
//-------------------------------------------------------------------------------
void HandleMouseInputFPS( void )
    {
    POINT mousePos;
    GetCursorPos( &mousePos );
    ScreenToClient( GetDlgItem(g_hDlg,IDC_RT), &mousePos );

    g_mousePos.x = mousePos.x;
    g_mousePos.y = mousePos.y;

    D3DXMATRIX matRotation;

    if (g_bMousePressed)
        {
        int nXDiff = (g_mousePos.x - g_LastmousePos.x);
        int nYDiff = (g_mousePos.y - g_LastmousePos.y);

        if( 0 != nYDiff)
            {
            D3DXMatrixRotationAxis( &matRotation, (D3DXVECTOR3*)& g_sCamera.vRight, D3DXToRadian((float)nYDiff / 6.0f));
            D3DXVec3TransformCoord( (D3DXVECTOR3*)&g_sCamera.vLookAt, (D3DXVECTOR3*)& g_sCamera.vLookAt, &matRotation );
            D3DXVec3TransformCoord( (D3DXVECTOR3*)&g_sCamera.vUp, (D3DXVECTOR3*)&g_sCamera.vUp, &matRotation );
            }

        if( 0 != nXDiff )
            {
            D3DXVECTOR3 v(0,1,0);
            D3DXMatrixRotationAxis( &matRotation, (D3DXVECTOR3*)&g_sCamera.vUp, D3DXToRadian((float)nXDiff / 6.0f) );
            D3DXVec3TransformCoord( (D3DXVECTOR3*)&g_sCamera.vLookAt, (D3DXVECTOR3*)&g_sCamera.vLookAt, &matRotation );
            D3DXVec3TransformCoord( (D3DXVECTOR3*)&g_sCamera.vRight,(D3DXVECTOR3*) &g_sCamera.vRight, &matRotation );
            }
        }

    g_LastmousePos.x = g_mousePos.x;
    g_LastmousePos.y = g_mousePos.y;
    }


//-------------------------------------------------------------------------------
// Handle mouse input for the FPS input behaviour
//
// Movement in x and y axis is possible
//-------------------------------------------------------------------------------
void HandleMouseInputTextureView( void )
    {
    POINT mousePos;
    GetCursorPos( &mousePos );
    ScreenToClient( GetDlgItem(g_hDlg,IDC_RT), &mousePos );

    g_mousePos.x = mousePos.x;
    g_mousePos.y = mousePos.y;

    D3DXMATRIX matRotation;

    if (g_bMousePressed)
        {
        CDisplay::Instance().SetTextureViewOffsetX((float)(g_mousePos.x - g_LastmousePos.x));
        CDisplay::Instance().SetTextureViewOffsetY((float)(g_mousePos.y - g_LastmousePos.y));
        }

    g_LastmousePos.x = g_mousePos.x;
    g_LastmousePos.y = g_mousePos.y;
    }

//-------------------------------------------------------------------------------
// handle mouse input for the light rotation
//
// Axes: global x/y axis
//-------------------------------------------------------------------------------
void HandleMouseInputLightRotate( void )
    {
    POINT mousePos;
    GetCursorPos( &mousePos );
    ScreenToClient( GetDlgItem(g_hDlg,IDC_RT), &mousePos );

    g_mousePos.x = mousePos.x;
    g_mousePos.y = mousePos.y;

    if (g_bMousePressedR)
        {
        int nXDiff = -(g_mousePos.x - g_LastmousePos.x);
        int nYDiff = -(g_mousePos.y - g_LastmousePos.y);

        aiVector3D v = aiVector3D(1.0f,0.0f,0.0f);
        aiMatrix4x4 mTemp;
        D3DXMatrixRotationAxis( (D3DXMATRIX*) &mTemp, (D3DXVECTOR3*)&v, D3DXToRadian((float)nYDiff / 2.0f));
        D3DXVec3TransformCoord((D3DXVECTOR3*)&g_avLightDirs[0],
            (const D3DXVECTOR3*)&g_avLightDirs[0],(const D3DXMATRIX*)&mTemp);

        v = aiVector3D(0.0f,1.0f,0.0f);
        D3DXMatrixRotationAxis( (D3DXMATRIX*) &mTemp, (D3DXVECTOR3*)&v, D3DXToRadian((float)nXDiff / 2.0f));
        D3DXVec3TransformCoord((D3DXVECTOR3*)&g_avLightDirs[0],
            (const D3DXVECTOR3*)&g_avLightDirs[0],(const D3DXMATRIX*)&mTemp);
        }
    return;
    }


//-------------------------------------------------------------------------------
// Handle mouse input for movements of the skybox
//
// The skybox can be moved by holding both the left and the right mouse button
// pressed. Rotation is possible in x and y direction.
//-------------------------------------------------------------------------------
void HandleMouseInputSkyBox( void )
    {
    POINT mousePos;
    GetCursorPos( &mousePos );
    ScreenToClient( GetDlgItem(g_hDlg,IDC_RT), &mousePos );

    g_mousePos.x = mousePos.x;
    g_mousePos.y = mousePos.y;

    aiMatrix4x4 matRotation;

    if (g_bMousePressedBoth )
        {
        int nXDiff = -(g_mousePos.x - g_LastmousePos.x);
        int nYDiff = -(g_mousePos.y - g_LastmousePos.y);

        aiMatrix4x4 matWorld;

        if( 0 != nYDiff)
            {
            aiVector3D v = aiVector3D(1.0f,0.0f,0.0f);
            D3DXMatrixRotationAxis( (D3DXMATRIX*) &matWorld, (D3DXVECTOR3*)&v, D3DXToRadian((float)nYDiff / 2.0f));
            CBackgroundPainter::Instance().RotateSB(&matWorld);
            }

        if( 0 != nXDiff)
            {
            aiMatrix4x4 matWorldOld;
            if( 0 != nYDiff)
                {
                matWorldOld = matWorld;
                }

            aiVector3D v = aiVector3D(0.0f,1.0f,0.0f);
            D3DXMatrixRotationAxis( (D3DXMATRIX*)&matWorld, (D3DXVECTOR3*)&v, D3DXToRadian((float)nXDiff / 2.0f) );
            matWorld =  matWorldOld * matWorld;
            CBackgroundPainter::Instance().RotateSB(&matWorld);
            }
        }
    }

//-------------------------------------------------------------------------------
//-------------------------------------------------------------------------------
void HandleMouseInputLightIntensityAndColor( void )
    {
    POINT mousePos;
    GetCursorPos( &mousePos );
    ScreenToClient( GetDlgItem(g_hDlg,IDC_RT), &mousePos );

    g_mousePos.x = mousePos.x;
    g_mousePos.y = mousePos.y;

    if (g_bMousePressedM)
        {
        int nXDiff = -(g_mousePos.x - g_LastmousePos.x);
        int nYDiff = -(g_mousePos.y - g_LastmousePos.y);

        g_fLightIntensity -= (float)nXDiff / 400.0f;
        if ((nYDiff > 2 || nYDiff < -2) && (nXDiff < 20 && nXDiff > -20))
        {
            if (!g_bFPSView)
            {
                g_sCamera.vPos.z += nYDiff / 120.0f;
            }
            else
            {
                g_sCamera.vPos += (nYDiff / 120.0f) * g_sCamera.vLookAt.Normalize();
            }
        }
    }
    return;
    }

//-------------------------------------------------------------------------------
//-------------------------------------------------------------------------------
void HandleMouseInputLocal( void )
    {
    POINT mousePos;
    GetCursorPos( &mousePos );
    ScreenToClient( GetDlgItem(g_hDlg,IDC_RT), &mousePos );

    g_mousePos.x = mousePos.x;
    g_mousePos.y = mousePos.y;

    aiMatrix4x4 matRotation;

    if (g_bMousePressed)
        {
        int nXDiff = -(g_mousePos.x - g_LastmousePos.x);
        int nYDiff = -(g_mousePos.y - g_LastmousePos.y);

        aiMatrix4x4 matWorld;
        if (g_eClick != EClickPos_Outside)
            {
            if( 0 != nYDiff && g_eClick != EClickPos_CircleHor)
                {
                aiVector3D v = aiVector3D(1.0f,0.0f,0.0f);
                D3DXMatrixRotationAxis( (D3DXMATRIX*) &matWorld, (D3DXVECTOR3*)&v, D3DXToRadian((float)nYDiff / 2.0f));
                g_mWorldRotate = g_mWorldRotate * matWorld;
                }

            if( 0 != nXDiff && g_eClick != EClickPos_CircleVert)
                {
                aiVector3D v = aiVector3D(0.0f,1.0f,0.0f);
                D3DXMatrixRotationAxis( (D3DXMATRIX*)&matWorld, (D3DXVECTOR3*)&v, D3DXToRadian((float)nXDiff / 2.0f) );
                g_mWorldRotate = g_mWorldRotate * matWorld;
                }
            }
        else
            {
            if(0 != nYDiff || 0 != nXDiff)
                {
                // rotate around the z-axis
                RECT sRect;
                GetWindowRect(GetDlgItem(g_hDlg,IDC_RT),&sRect);
                sRect.right -= sRect.left;
                sRect.bottom -= sRect.top;

                int xPos = g_mousePos.x - sRect.right/2;
                int yPos = g_mousePos.y - sRect.bottom/2;
                float fXDist = (float)xPos;
                float fYDist = (float)yPos / sqrtf((float)(yPos * yPos + xPos * xPos));

                bool bSign1;
                if (fXDist < 0.0f)bSign1 = false;
                else bSign1 = true;
                float fAngle = asin(fYDist);

                xPos = g_LastmousePos.x - sRect.right/2;
                yPos = g_LastmousePos.y - sRect.bottom/2;

                fXDist = (float)xPos;
                fYDist = (float)yPos / sqrtf((float)(yPos * yPos + xPos * xPos));

                bool bSign2;
                if (fXDist < 0.0f)bSign2 = false;
                else bSign2 = true;
                float fAngle2 = asin(fYDist);
                fAngle -= fAngle2;

                if (bSign1 != bSign2)
                    {
                    g_bInvert = !g_bInvert;
                    }
                if (g_bInvert)fAngle *= -1.0f;

                aiVector3D v = aiVector3D(0.0f,0.0f,1.0f);
                D3DXMatrixRotationAxis( (D3DXMATRIX*)&matWorld, (D3DXVECTOR3*)&v, (float) (fAngle * 1.2) );
                g_mWorldRotate = g_mWorldRotate * matWorld;
                }
            }
        }

    g_LastmousePos.x = g_mousePos.x;
    g_LastmousePos.y = g_mousePos.y;
    }

//-------------------------------------------------------------------------------
//-------------------------------------------------------------------------------
void HandleKeyboardInputFPS( void )
    {
    unsigned char keys[256];
    GetKeyboardState( keys );

    aiVector3D tmpLook  = g_sCamera.vLookAt;
    aiVector3D tmpRight = g_sCamera.vRight;

    aiVector3D vOldPos = g_sCamera.vPos;

    // Up Arrow Key - View moves forward
    if( keys[VK_UP] & 0x80 )
        g_sCamera.vPos -= (tmpLook*-MOVE_SPEED)*g_fElpasedTime;

    // Down Arrow Key - View moves backward
    if( keys[VK_DOWN] & 0x80 )
        g_sCamera.vPos += (tmpLook*-MOVE_SPEED)*g_fElpasedTime;

    // Left Arrow Key - View side-steps or strafes to the left
    if( keys[VK_LEFT] & 0x80 )
        g_sCamera.vPos -= (tmpRight*MOVE_SPEED)*g_fElpasedTime;

    // Right Arrow Key - View side-steps or strafes to the right
    if( keys[VK_RIGHT] & 0x80 )
        g_sCamera.vPos += (tmpRight*MOVE_SPEED)*g_fElpasedTime;

    // Home Key - View elevates up
    if( keys[VK_HOME] & 0x80 )
        g_sCamera.vPos .y += MOVE_SPEED*g_fElpasedTime;

    // End Key - View elevates down
    if( keys[VK_END] & 0x80 )
        g_sCamera.vPos.y -= MOVE_SPEED*g_fElpasedTime;
    }


//-------------------------------------------------------------------------------
//-------------------------------------------------------------------------------
void HandleKeyboardInputTextureView( void )
    {
    unsigned char keys[256];
    GetKeyboardState( keys );

    // Up Arrow Key
    if( keys[VK_UP] & 0x80 )
        CDisplay::Instance().SetTextureViewOffsetY ( g_fElpasedTime * 150.0f );

    // Down Arrow Key
    if( keys[VK_DOWN] & 0x80 )
        CDisplay::Instance().SetTextureViewOffsetY ( -g_fElpasedTime * 150.0f );

    // Left Arrow Key
    if( keys[VK_LEFT] & 0x80 )
        CDisplay::Instance().SetTextureViewOffsetX ( g_fElpasedTime * 150.0f );

    // Right Arrow Key
    if( keys[VK_RIGHT] & 0x80 )
        CDisplay::Instance().SetTextureViewOffsetX ( -g_fElpasedTime * 150.0f );
    }
};