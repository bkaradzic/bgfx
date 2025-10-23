// https://github.com/CedricGuillemet/ImGuizmo
// v1.91.3 WIP
//
// The MIT License(MIT)
//
// Copyright(c) 2021 Cedric Guillemet
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
// -------------------------------------------------------------------------------------------
// History :
// 2019/11/03 View gizmo
// 2016/09/11 Behind camera culling. Scaling Delta matrix not multiplied by source matrix scales. local/world rotation and translation fixed. Display message is incorrect (X: ... Y:...) in local mode.
// 2016/09/09 Hatched negative axis. Snapping. Documentation update.
// 2016/09/04 Axis switch and translation plan autohiding. Scale transform stability improved
// 2016/09/01 Mogwai changed to Manipulate. Draw debug cube. Fixed inverted scale. Mixing scale and translation/rotation gives bad results.
// 2016/08/31 First version
//
// -------------------------------------------------------------------------------------------
// Future (no order):
//
// - Multi view
// - display rotation/translation/scale infos in local/world space and not only local
// - finish local/world matrix application
// - OPERATION as bitmask
//
// -------------------------------------------------------------------------------------------
// Example
#if 0
void EditTransform(const Camera& camera, matrix_t& matrix)
{
   static ImGuizmo::OPERATION mCurrentGizmoOperation(ImGuizmo::ROTATE);
   static ImGuizmo::MODE mCurrentGizmoMode(ImGuizmo::WORLD);
   if (ImGui::IsKeyPressed(90))
      mCurrentGizmoOperation = ImGuizmo::TRANSLATE;
   if (ImGui::IsKeyPressed(69))
      mCurrentGizmoOperation = ImGuizmo::ROTATE;
   if (ImGui::IsKeyPressed(82)) // r Key
      mCurrentGizmoOperation = ImGuizmo::SCALE;
   if (ImGui::RadioButton("Translate", mCurrentGizmoOperation == ImGuizmo::TRANSLATE))
      mCurrentGizmoOperation = ImGuizmo::TRANSLATE;
   ImGui::SameLine();
   if (ImGui::RadioButton("Rotate", mCurrentGizmoOperation == ImGuizmo::ROTATE))
      mCurrentGizmoOperation = ImGuizmo::ROTATE;
   ImGui::SameLine();
   if (ImGui::RadioButton("Scale", mCurrentGizmoOperation == ImGuizmo::SCALE))
      mCurrentGizmoOperation = ImGuizmo::SCALE;
   float matrixTranslation[3], matrixRotation[3], matrixScale[3];
   ImGuizmo::DecomposeMatrixToComponents(matrix.m16, matrixTranslation, matrixRotation, matrixScale);
   ImGui::InputFloat3("Tr", matrixTranslation, 3);
   ImGui::InputFloat3("Rt", matrixRotation, 3);
   ImGui::InputFloat3("Sc", matrixScale, 3);
   ImGuizmo::RecomposeMatrixFromComponents(matrixTranslation, matrixRotation, matrixScale, matrix.m16);

   if (mCurrentGizmoOperation != ImGuizmo::SCALE)
   {
      if (ImGui::RadioButton("Local", mCurrentGizmoMode == ImGuizmo::LOCAL))
         mCurrentGizmoMode = ImGuizmo::LOCAL;
      ImGui::SameLine();
      if (ImGui::RadioButton("World", mCurrentGizmoMode == ImGuizmo::WORLD))
         mCurrentGizmoMode = ImGuizmo::WORLD;
   }
   static bool useSnap(false);
   if (ImGui::IsKeyPressed(83))
      useSnap = !useSnap;
   ImGui::Checkbox("", &useSnap);
   ImGui::SameLine();
   vec_t snap;
   switch (mCurrentGizmoOperation)
   {
   case ImGuizmo::TRANSLATE:
      snap = config.mSnapTranslation;
      ImGui::InputFloat3("Snap", &snap.x);
      break;
   case ImGuizmo::ROTATE:
      snap = config.mSnapRotation;
      ImGui::InputFloat("Angle Snap", &snap.x);
      break;
   case ImGuizmo::SCALE:
      snap = config.mSnapScale;
      ImGui::InputFloat("Scale Snap", &snap.x);
      break;
   }
   ImGuiIO& io = ImGui::GetIO();
   ImGuizmo::SetRect(0, 0, io.DisplaySize.x, io.DisplaySize.y);
   ImGuizmo::Manipulate(camera.mView.m16, camera.mProjection.m16, mCurrentGizmoOperation, mCurrentGizmoMode, matrix.m16, NULL, useSnap ? &snap.x : NULL);
}
#endif
#pragma once

#ifdef USE_IMGUI_API
#include "imconfig.h"
#endif
#ifndef IMGUI_API
#define IMGUI_API
#endif

#ifndef IMGUIZMO_NAMESPACE
#define IMGUIZMO_NAMESPACE ImGuizmo
#endif

struct ImGuiWindow;

namespace IMGUIZMO_NAMESPACE
{
   // call inside your own window and before Manipulate() in order to draw gizmo to that window.
   // Or pass a specific ImDrawList to draw to (e.g. ImGui::GetForegroundDrawList()).
   IMGUI_API void SetDrawlist(ImDrawList* drawlist = nullptr);

   // call BeginFrame right after ImGui_XXXX_NewFrame();
   IMGUI_API void BeginFrame();

   // this is necessary because when imguizmo is compiled into a dll, and imgui into another
   // globals are not shared between them.
   // More details at https://stackoverflow.com/questions/19373061/what-happens-to-global-and-static-variables-in-a-shared-library-when-it-is-dynam
   // expose method to set imgui context
   IMGUI_API void SetImGuiContext(ImGuiContext* ctx);

   // return true if mouse cursor is over any gizmo control (axis, plan or screen component)
   IMGUI_API bool IsOver();

   // return true if mouse IsOver or if the gizmo is in moving state
   IMGUI_API bool IsUsing();

   // return true if the view gizmo is in moving state
   IMGUI_API bool IsUsingViewManipulate();
   // only check if your mouse is over the view manipulator - no matter whether it's active or not
   IMGUI_API bool IsViewManipulateHovered();

   // return true if any gizmo is in moving state
   IMGUI_API bool IsUsingAny();

   // enable/disable the gizmo. Stay in the state until next call to Enable.
   // gizmo is rendered with gray half transparent color when disabled
   IMGUI_API void Enable(bool enable);

   // helper functions for manualy editing translation/rotation/scale with an input float
   // translation, rotation and scale float points to 3 floats each
   // Angles are in degrees (more suitable for human editing)
   // example:
   // float matrixTranslation[3], matrixRotation[3], matrixScale[3];
   // ImGuizmo::DecomposeMatrixToComponents(gizmoMatrix.m16, matrixTranslation, matrixRotation, matrixScale);
   // ImGui::InputFloat3("Tr", matrixTranslation, 3);
   // ImGui::InputFloat3("Rt", matrixRotation, 3);
   // ImGui::InputFloat3("Sc", matrixScale, 3);
   // ImGuizmo::RecomposeMatrixFromComponents(matrixTranslation, matrixRotation, matrixScale, gizmoMatrix.m16);
   //
   // These functions have some numerical stability issues for now. Use with caution.
   IMGUI_API void DecomposeMatrixToComponents(const float* matrix, float* translation, float* rotation, float* scale);
   IMGUI_API void RecomposeMatrixFromComponents(const float* translation, const float* rotation, const float* scale, float* matrix);

   IMGUI_API void SetRect(float x, float y, float width, float height);
   // default is false
   IMGUI_API void SetOrthographic(bool isOrthographic);

   // Render a cube with face color corresponding to face normal. Usefull for debug/tests
   IMGUI_API void DrawCubes(const float* view, const float* projection, const float* matrices, int matrixCount);
   IMGUI_API void DrawGrid(const float* view, const float* projection, const float* matrix, const float gridSize);

   // call it when you want a gizmo
   // Needs view and projection matrices.
   // matrix parameter is the source matrix (where will be gizmo be drawn) and might be transformed by the function. Return deltaMatrix is optional
   // translation is applied in world space
   enum OPERATION
   {
      TRANSLATE_X      = (1u << 0),
      TRANSLATE_Y      = (1u << 1),
      TRANSLATE_Z      = (1u << 2),
      ROTATE_X         = (1u << 3),
      ROTATE_Y         = (1u << 4),
      ROTATE_Z         = (1u << 5),
      ROTATE_SCREEN    = (1u << 6),
      SCALE_X          = (1u << 7),
      SCALE_Y          = (1u << 8),
      SCALE_Z          = (1u << 9),
      BOUNDS           = (1u << 10),
      SCALE_XU         = (1u << 11),
      SCALE_YU         = (1u << 12),
      SCALE_ZU         = (1u << 13),

      TRANSLATE = TRANSLATE_X | TRANSLATE_Y | TRANSLATE_Z,
      ROTATE = ROTATE_X | ROTATE_Y | ROTATE_Z | ROTATE_SCREEN,
      SCALE = SCALE_X | SCALE_Y | SCALE_Z,
      SCALEU = SCALE_XU | SCALE_YU | SCALE_ZU, // universal
      UNIVERSAL = TRANSLATE | ROTATE | SCALEU
   };

   inline OPERATION operator|(OPERATION lhs, OPERATION rhs)
   {
     return static_cast<OPERATION>(static_cast<int>(lhs) | static_cast<int>(rhs));
   }

   enum MODE
   {
      LOCAL,
      WORLD
   };

   IMGUI_API bool Manipulate(const float* view, const float* projection, OPERATION operation, MODE mode, float* matrix, float* deltaMatrix = NULL, const float* snap = NULL, const float* localBounds = NULL, const float* boundsSnap = NULL);
   //
   // Please note that this cubeview is patented by Autodesk : https://patents.google.com/patent/US7782319B2/en
   // It seems to be a defensive patent in the US. I don't think it will bring troubles using it as
   // other software are using the same mechanics. But just in case, you are now warned!
   //
   IMGUI_API void ViewManipulate(float* view, float length, ImVec2 position, ImVec2 size, ImU32 backgroundColor);

   // use this version if you did not call Manipulate before and you are just using ViewManipulate
   IMGUI_API void ViewManipulate(float* view, const float* projection, OPERATION operation, MODE mode, float* matrix, float length, ImVec2 position, ImVec2 size, ImU32 backgroundColor);

   IMGUI_API void SetAlternativeWindow(ImGuiWindow* window);

   [[deprecated("Use PushID/PopID instead.")]]
   IMGUI_API void SetID(int id);

	// ID stack/scopes
	// Read the FAQ (docs/FAQ.md or http://dearimgui.org/faq) for more details about how ID are handled in dear imgui.
	// - Those questions are answered and impacted by understanding of the ID stack system:
	//   - "Q: Why is my widget not reacting when I click on it?"
	//   - "Q: How can I have widgets with an empty label?"
	//   - "Q: How can I have multiple widgets with the same label?"
	// - Short version: ID are hashes of the entire ID stack. If you are creating widgets in a loop you most likely
	//   want to push a unique identifier (e.g. object pointer, loop index) to uniquely differentiate them.
	// - You can also use the "Label##foobar" syntax within widget label to distinguish them from each others.
	// - In this header file we use the "label"/"name" terminology to denote a string that will be displayed + used as an ID,
	//   whereas "str_id" denote a string that is only used as an ID and not normally displayed.
	IMGUI_API void          PushID(const char* str_id);                                     // push string into the ID stack (will hash string).
	IMGUI_API void          PushID(const char* str_id_begin, const char* str_id_end);       // push string into the ID stack (will hash string).
	IMGUI_API void          PushID(const void* ptr_id);                                     // push pointer into the ID stack (will hash pointer).
	IMGUI_API void          PushID(int int_id);                                             // push integer into the ID stack (will hash integer).
	IMGUI_API void          PopID();                                                        // pop from the ID stack.
	IMGUI_API ImGuiID       GetID(const char* str_id);                                      // calculate unique ID (hash of whole ID stack + given parameter). e.g. if you want to query into ImGuiStorage yourself
	IMGUI_API ImGuiID       GetID(const char* str_id_begin, const char* str_id_end);
	IMGUI_API ImGuiID       GetID(const void* ptr_id);

   // return true if the cursor is over the operation's gizmo
   IMGUI_API bool IsOver(OPERATION op);
   IMGUI_API void SetGizmoSizeClipSpace(float value);

   // Allow axis to flip
   // When true (default), the guizmo axis flip for better visibility
   // When false, they always stay along the positive world/local axis
   IMGUI_API void AllowAxisFlip(bool value);

   // Configure the limit where axis are hidden
   IMGUI_API void SetAxisLimit(float value);
   // Set an axis mask to permanently hide a given axis (true -> hidden, false -> shown)
   IMGUI_API void SetAxisMask(bool x, bool y, bool z);
   // Configure the limit where planes are hiden
   IMGUI_API void SetPlaneLimit(float value);
   // from a x,y,z point in space and using Manipulation view/projection matrix, check if mouse is in pixel radius distance of that projected point
   IMGUI_API bool IsOver(float* position, float pixelRadius);

   enum COLOR
   {
      DIRECTION_X,      // directionColor[0]
      DIRECTION_Y,      // directionColor[1]
      DIRECTION_Z,      // directionColor[2]
      PLANE_X,          // planeColor[0]
      PLANE_Y,          // planeColor[1]
      PLANE_Z,          // planeColor[2]
      SELECTION,        // selectionColor
      INACTIVE,         // inactiveColor
      TRANSLATION_LINE, // translationLineColor
      SCALE_LINE,
      ROTATION_USING_BORDER,
      ROTATION_USING_FILL,
      HATCHED_AXIS_LINES,
      TEXT,
      TEXT_SHADOW,
      COUNT
   };

   struct Style
   {
      IMGUI_API Style();

      float TranslationLineThickness;   // Thickness of lines for translation gizmo
      float TranslationLineArrowSize;   // Size of arrow at the end of lines for translation gizmo
      float RotationLineThickness;      // Thickness of lines for rotation gizmo
      float RotationOuterLineThickness; // Thickness of line surrounding the rotation gizmo
      float ScaleLineThickness;         // Thickness of lines for scale gizmo
      float ScaleLineCircleSize;        // Size of circle at the end of lines for scale gizmo
      float HatchedAxisLineThickness;   // Thickness of hatched axis lines
      float CenterCircleSize;           // Size of circle at the center of the translate/scale gizmo

      ImVec4 Colors[COLOR::COUNT];
   };

   IMGUI_API Style& GetStyle();
}
