// https://github.com/CedricGuillemet/ImGuizmo
// v 1.04 WIP
//
// The MIT License(MIT)
// 
// Copyright(c) 2016 Cedric Guillemet
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

namespace ImGuizmo
{
	// call BeginFrame right after ImGui_XXXX_NewFrame();
	void BeginFrame();

	// return true if mouse cursor is over any gizmo control (axis, plan or screen component)
	bool IsOver();

	// return true if mouse IsOver or if the gizmo is in moving state
	bool IsUsing();

	// enable/disable the gizmo. Stay in the state until next call to Enable.
	// gizmo is rendered with gray half transparent color when disabled
	void Enable(bool enable);

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
	void DecomposeMatrixToComponents(const float *matrix, float *translation, float *rotation, float *scale);
	void RecomposeMatrixFromComponents(const float *translation, const float *rotation, const float *scale, float *matrix);

	void SetRect(float x, float y, float width, float height);

	// Render a cube with face color corresponding to face normal. Usefull for debug/tests
	void DrawCube(const float *view, const float *projection, float *matrix);

	// call it when you want a gizmo
	// Needs view and projection matrices. 
	// matrix parameter is the source matrix (where will be gizmo be drawn) and might be transformed by the function. Return deltaMatrix is optional
	// translation is applied in world space
	enum OPERATION
	{
		TRANSLATE,
		ROTATE,
		SCALE,
	};

	enum MODE
	{
		LOCAL,
		WORLD
	};

	void Manipulate(const float *view, const float *projection, OPERATION operation, MODE mode, float *matrix, float *deltaMatrix = 0, float *snap = 0, float *localBounds = NULL, float *boundsSnap = NULL);
};
