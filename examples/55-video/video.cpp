#include "common.h"
#include "bgfx_utils.h"
#include "imgui/imgui.h"
#include "entry/dialog.h"
#include "video_player.h"
#include "movie_audio.h"

#include <bx/filepath.h>
#include <bx/math.h>
#include <iconfontheaders/icons_font_awesome.h>

namespace
{

class ExampleVideo : public entry::AppI
{
public:
	ExampleVideo(const char* _name, const char* _description, const char* _url)
		: entry::AppI(_name, _description, _url)
	{
	}

	void init(int32_t _argc, const char* const* _argv, uint32_t _width, uint32_t _height) override
	{
		Args args(_argc, _argv);
		m_width = _width;
		m_height = _height;

		bgfx::Init init;
		init.type = args.m_type;
		init.vendorId = args.m_pciId;
		init.videoDecode = true;
		init.debug = true;
		init.swapChain.nwh = entry::getNativeWindowHandle(entry::kDefaultWindowHandle);
		init.swapChain.ndt = entry::getNativeDisplayHandle();
		init.platformData.type = entry::getNativeWindowHandleType();
		init.swapChain.width = m_width;
		init.swapChain.height = m_height;
		init.reset = m_reset;
		bgfx::init(init);
		bgfx::setViewClear(0, BGFX_CLEAR_COLOR, 0x101010ff);
		imguiCreate();
	}

	int shutdown() override
	{
		m_audio.close();
		m_player.close();
		imguiDestroy();
		bgfx::shutdown();
		return 0;
	}

	void openMovie()
	{
		m_audio.close();
		m_audioError = false;
		m_openError = !m_player.open(m_path.getCPtr() );
		if (!m_openError)
		{
			m_audioError = !m_audio.open(m_path.getCPtr() );
		}
	}

	void play()
	{
		if (m_player.isOpen() )
		{
			if (m_audio.finished() )
			{
				m_player.seekTo(0);
				m_audioError = !m_audio.seek(0);
			}
			if (m_player.isPaused() )
			{
				m_player.togglePause();
			}
			m_audio.setPaused(false);
		}
		else if (!m_path.isEmpty() )
		{
			openMovie();
		}
	}

	bool update() override
	{
		if (entry::processEvents(m_width, m_height, m_debug, m_reset, &m_mouseState) )
		{
			return false;
		}

		imguiBeginFrame(m_mouseState.m_mx, m_mouseState.m_my
			, (m_mouseState.m_buttons[entry::MouseButton::Left] ? IMGUI_MBUT_LEFT : 0)
			| (m_mouseState.m_buttons[entry::MouseButton::Right] ? IMGUI_MBUT_RIGHT : 0)
			| (m_mouseState.m_buttons[entry::MouseButton::Middle] ? IMGUI_MBUT_MIDDLE : 0)
			, m_mouseState.m_mz, uint16_t(m_width), uint16_t(m_height)
			);

		showExampleDialog(this);

		ImGui::SetNextWindowPos(ImVec2(10.0f, 200.0f), ImGuiCond_FirstUseEver);
		ImGui::SetNextWindowSize(ImVec2(float(m_width) - 20.0f, float(m_height) - 210.0f), ImGuiCond_FirstUseEver);
		ImGui::Begin("Movie player");

		const bool supported = 0 != (bgfx::getCaps()->supported & BGFX_CAPS_VIDEO_DECODE);
		ImGui::Text("Renderer: %s", bgfx::getRendererName(bgfx::getRendererType() ) );
		ImGui::BeginDisabled(!supported);
		if (ImGui::Button(ICON_FA_FOLDER_OPEN " Open") )
		{
			const bool resume = m_player.isActive();
			if (resume)
			{
				m_player.togglePause();
				m_audio.setPaused(true);
			}
			bx::FilePath selected = m_path;
			if (openFileSelectionDialog(selected, FileSelectionDialogType::Open, "Open movie"
				, "Movies | *.mp4;*.m4v;*.mov | All Files | *") )
			{
				m_path = selected;
				openMovie();
			}
			else if (resume)
			{
				m_player.togglePause();
				m_audio.setPaused(false);
			}
		}
		ImGui::SameLine();
		ImGui::BeginDisabled(m_path.isEmpty() );
		if (ImGui::Button(ICON_FA_PLAY " Play") )
		{
			play();
		}
		ImGui::SameLine();
		ImGui::BeginDisabled(!m_player.isOpen() );
		if (ImGui::Button(ICON_FA_PAUSE " Pause") )
		{
			if (!m_player.isPaused() )
			{
				m_player.togglePause();
			}
			m_audio.setPaused(true);
		}
		ImGui::SameLine();
		if (ImGui::Button(ICON_FA_STOP " Stop") )
		{
			m_audio.close();
			m_player.close();
		}
		ImGui::EndDisabled();
		ImGui::EndDisabled();
		ImGui::EndDisabled();

		if (!supported)
		{
			ImGui::TextWrapped("Native video decoding is unavailable on this renderer/device.");
		}
		if (!m_path.isEmpty() )
		{
			ImGui::TextWrapped("%s", m_path.getCPtr() );
		}
		if (m_openError)
		{
			ImGui::TextWrapped("Cannot open movie: unsupported container, codec, or GPU decoding capabilities.");
		}
		if (m_audioError)
		{
			ImGui::TextWrapped("Audio unavailable: no supported audio stream or audio output device.");
		}
		if (m_player.isOpen() )
		{
			float position = float(double(m_player.playbackTimeUs() ) / 1000000.0);
			const float duration = float(double(m_player.durationUs() ) / 1000000.0);
			ImGui::SetNextItemWidth(-1.0f);
			if (ImGui::SliderFloat("##position", &position, 0.0f, duration, "%.2f s") )
			{
				m_player.seekTo(uint64_t(double(position) * 1000000.0) );
				if (m_audio.isOpen() )
				{
					m_audioError = !m_audio.seek(uint64_t(double(position) * 1000000.0) );
				}
			}
			ImGui::Text("%ux%u  %.2f / %.2f s  %s", m_player.width(), m_player.height()
				, position, duration, m_player.isPaused() ? "Paused" : "Playing"
				);
			if (m_audio.isOpen() )
			{
				if (!m_audio.tick() )
				{
					m_audio.close();
					m_audioError = true;
				}
			}
			if (m_audio.isOpen() )
			{
				m_player.tick(int64_t(bx::min(m_audio.positionUs(), m_player.durationUs() ) ) );
				if (m_audio.finished() && !m_player.isPaused() )
				{
					m_player.togglePause();
					m_audio.setPaused(true);
				}
			}
			else
			{
				m_player.tick();
			}
			const ImVec2 available = ImGui::GetContentRegionAvail();
			if (available.x > 0.0f && available.y > 0.0f)
			{
				const float scale = bx::min(available.x / float(m_player.width() ), available.y / float(m_player.height() ) );
				const ImVec2 size(float(m_player.width() ) * scale, float(m_player.height() ) * scale);
				ImGui::SetCursorPosX(ImGui::GetCursorPosX() + (available.x - size.x) * 0.5f);
				ImGui::Image(m_player.texture(), size);
			}
		}

		ImGui::End();
		imguiEndFrame();
		bgfx::setViewRect(0, 0, 0, uint16_t(m_width), uint16_t(m_height) );
		bgfx::touch(0);
		bgfx::frame();
		return true;
	}

private:
	entry::MouseState m_mouseState;
	uint32_t m_width = 0;
	uint32_t m_height = 0;
	uint32_t m_debug = BGFX_DEBUG_NONE;
	uint32_t m_reset = BGFX_RESET_VSYNC;
	bx::FilePath m_path;
	VideoPlayer m_player;
	MovieAudio m_audio;
	bool m_openError = false;
	bool m_audioError = false;
};

} // namespace

ENTRY_IMPLEMENT_MAIN(ExampleVideo, "55-video", "Native video decoding.", "");