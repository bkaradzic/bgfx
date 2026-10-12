# 55-video

Native GPU video decoding with the standard bgfx renderer selector and an
ImGui movie player: Open, Play, Pause, Stop, and a seek slider. Stop releases
the decoder and audio stream; Play opens the selected movie again. The video
keeps its aspect ratio. Audio-backed playback pauses at the end, and Play
restarts it. Video-only playback loops, matching the existing texturev player.

The example reuses `tools/texturev/video_player.cpp` and L-SMASH. Supported
input is MP4-family containers (including M4V/MOV) with H.264 or HEVC video,
subject to the selected renderer/device's native codec capabilities. The file
dialog also permits selecting any filename; this does not add support for
other container formats. There is no software video decoder fallback.
Unsupported input or unavailable native decoding is reported in the player.

On Windows 10 or later, Media Foundation decodes only the selected audio
stream, and XAudio2 plays a bounded queue of PCM buffers. Its playback clock
drives video presentation. Pause, Stop, and seeking affect both streams.
Audio support depends on the installed Media Foundation codecs and output
device; unavailable audio is reported without disabling video. Other
platforms currently use video-only playback.

## Build On Windows

From the bgfx directory, with bx and bimg checked out alongside bgfx:

```powershell
..\bx\tools\bin\windows\genie.exe --with-examples vs2022
```

Open `.build/projects/vs2022/bgfx.sln` in Visual Studio and build
`example-55-video` with the Debug/x64 configuration. This also builds the
shared L-SMASH library. The example is also registered in
`--with-combined-examples` builds and can coexist with `--with-tools`.

## Run

From `examples/runtime`:

```powershell
..\..\.build\win64_vs2022\bin\example-55-videoDebug.exe --d3d11
```

Use `--d3d12` or `--vk` to start with another renderer, or use the standard
Renderer dropdown. Renderer selection restarts the example. Debug-layer
diagnostics are enabled to help investigate native decoding errors; the
example does not repair or bypass decoder-backend faults.