; ----------------------------------------------------------------------------
; Inno Setup 5.x setup script for Windows
; This script will create an installer for the binary Windows distribution
; ----------------------------------------------------------------------------

[Setup]
AppName=OpenCTM
AppVerName=OpenCTM 1.0.3
VersionInfoVersion=1.0.3.0
AppPublisher=Marcus Geelnard
AppPublisherURL=http://openctm.sourceforge.net/
AppSupportURL=http://openctm.sourceforge.net/
AppUpdatesURL=http://openctm.sourceforge.net/
DefaultDirName={pf}\OpenCTM 1.0.3
DefaultGroupName=OpenCTM 1.0.3
LicenseFile=LICENSE.txt
OutputDir=.
OutputBaseFilename=OpenCTM-1.0.3-setup
Compression=lzma
SolidCompression=yes
ChangesAssociations=yes
ChangesEnvironment=yes


[Tasks]
Name: associatectm; Description: "&Associate OpenCTM (.ctm) files with the OpenCTM viewer"; GroupDescription: "Associate files:"
Name: associatestl; Description: "&Associate Stereolithography (.stl) files with the OpenCTM viewer"; GroupDescription: "Associate files:"
Name: associateply; Description: "&Associate Stanford PLY (.ply) files with the OpenCTM viewer"; GroupDescription: "Associate files:"
Name: associate3ds; Description: "&Associate 3DStudio (.3ds) files with the OpenCTM viewer"; GroupDescription: "Associate files:"
Name: associatedae; Description: "&Associate COLLADA (.dae) files with the OpenCTM viewer"; GroupDescription: "Associate files:"
Name: associateobj; Description: "&Associate Wavefront (.obj) files with the OpenCTM viewer"; GroupDescription: "Associate files:"
Name: associatelwo; Description: "&Associate LightWave (.lwo) files with the OpenCTM viewer"; GroupDescription: "Associate files:"
Name: associateoff; Description: "&Associate Geomview OFF (.off) files with the OpenCTM viewer"; GroupDescription: "Associate files:"
Name: modifypath; Description: "&Add application directory to your system path"; GroupDescription: "Modify system paths:"

[Files]
Source: "lib\openctm.dll"; DestDir: "{app}\bin"
Source: "tools\freeglut.dll"; DestDir: "{app}\bin"
Source: "tools\ctmconv.exe"; DestDir: "{app}\bin"
Source: "tools\ctmviewer.exe"; DestDir: "{app}\bin"
Source: "doc\APIReference\*"; DestDir: "{app}\Documentation\APIReference"
Source: "doc\DevelopersManual.pdf"; DestDir: "{app}\Documentation"
Source: "doc\FormatSpecification.pdf"; DestDir: "{app}\Documentation"
Source: "doc\ctmconv.html"; DestDir: "{app}\Documentation"
Source: "doc\ctmviewer.html"; DestDir: "{app}\Documentation"
Source: "README.txt"; DestDir: "{app}\Documentation"; Flags: isreadme
Source: "LICENSE.txt"; DestDir: "{app}\Documentation"
Source: "lib\openctm.h"; DestDir: "{app}\Developer files"
Source: "lib\openctmpp.h"; DestDir: "{app}\Developer files"
Source: "lib\openctm.lib"; DestDir: "{app}\Developer files"
Source: "bindings\delphi\OpenCTM.pas"; DestDir: "{app}\Developer files"
Source: "bindings\python\openctm.py"; DestDir: "{app}\Developer files"
Source: "bindings\python\ctminfo.py"; DestDir: "{app}\Developer files"
Source: "plugins\blender\*"; DestDir: "{app}\Plugins\Blender"
Source: "plugins\maya\*"; DestDir: "{app}\Plugins\Maya"

[Icons]
Name: "{group}\3D Viewer"; Filename: "{app}\bin\ctmviewer.exe"; WorkingDir: "{app}\bin"
Name: "{group}\Browse the OpenCTM folder"; Filename: "{app}"
Name: "{group}\Documentation\Developers Manual"; Filename: "{app}\Documentation\DevelopersManual.pdf"
Name: "{group}\Documentation\API Reference"; Filename: "{app}\Documentation\APIReference\index.html"
Name: "{group}\Documentation\Format Specification"; Filename: "{app}\Documentation\FormatSpecification.pdf"
Name: "{group}\Documentation\3D Viewer Manual (ctmviewer)"; Filename: "{app}\Documentation\ctmviewer.html"
Name: "{group}\Documentation\File Converter Manual (ctmconv)"; Filename: "{app}\Documentation\ctmconv.html"
Name: "{group}\Documentation\License"; Filename: "{app}\Documentation\LICENSE.txt"
Name: "{group}\Documentation\README"; Filename: "{app}\Documentation\README.txt"
Name: "{group}\{cm:UninstallProgram,OpenCTM}"; Filename: "{uninstallexe}"

[Registry]
Root: HKCR; Subkey: ".ctm"; ValueType: string; ValueName: ""; ValueData: "OpenCTM_file"; Flags: uninsdeletevalue; Tasks: associatectm
Root: HKCR; Subkey: "OpenCTM_file"; ValueType: string; ValueName: ""; ValueData: "OpenCTM 3D mesh file"; Flags: uninsdeletekey; Tasks: associatectm
Root: HKCR; Subkey: "OpenCTM_file\DefaultIcon"; ValueType: string; ValueName: ""; ValueData: "{app}\bin\ctmviewer.exe,0"; Tasks: associatectm
Root: HKCR; Subkey: "OpenCTM_file\shell\open\command"; ValueType: string; ValueName: ""; ValueData: """{app}\bin\ctmviewer.exe"" ""%1"""; Tasks: associatectm

Root: HKCR; Subkey: ".ply"; ValueType: string; ValueName: ""; ValueData: "PLY_file"; Flags: uninsdeletevalue; Tasks: associateply
Root: HKCR; Subkey: "PLY_file"; ValueType: string; ValueName: ""; ValueData: "Stanford PLY file"; Flags: uninsdeletekey; Tasks: associateply
Root: HKCR; Subkey: "PLY_file\DefaultIcon"; ValueType: string; ValueName: ""; ValueData: "{app}\bin\ctmviewer.exe,0"; Tasks: associateply
Root: HKCR; Subkey: "PLY_file\shell\open\command"; ValueType: string; ValueName: ""; ValueData: """{app}\bin\ctmviewer.exe"" ""%1"""; Tasks: associateply

Root: HKCR; Subkey: ".stl"; ValueType: string; ValueName: ""; ValueData: "STL_file"; Flags: uninsdeletevalue; Tasks: associatestl
Root: HKCR; Subkey: "STL_file"; ValueType: string; ValueName: ""; ValueData: "Stereolithography 3D mesh file"; Flags: uninsdeletekey; Tasks: associatestl
Root: HKCR; Subkey: "STL_file\DefaultIcon"; ValueType: string; ValueName: ""; ValueData: "{app}\bin\ctmviewer.exe,0"; Tasks: associatestl
Root: HKCR; Subkey: "STL_file\shell\open\command"; ValueType: string; ValueName: ""; ValueData: """{app}\bin\ctmviewer.exe"" ""%1"""; Tasks: associatestl

Root: HKCR; Subkey: ".3ds"; ValueType: string; ValueName: ""; ValueData: "3DS_file"; Flags: uninsdeletevalue; Tasks: associate3ds
Root: HKCR; Subkey: "3DS_file"; ValueType: string; ValueName: ""; ValueData: "3DStudio file"; Flags: uninsdeletekey; Tasks: associate3ds
Root: HKCR; Subkey: "3DS_file\DefaultIcon"; ValueType: string; ValueName: ""; ValueData: "{app}\bin\ctmviewer.exe,0"; Tasks: associate3ds
Root: HKCR; Subkey: "3DS_file\shell\open\command"; ValueType: string; ValueName: ""; ValueData: """{app}\bin\ctmviewer.exe"" ""%1"""; Tasks: associate3ds

Root: HKCR; Subkey: ".dae"; ValueType: string; ValueName: ""; ValueData: "DAE_file"; Flags: uninsdeletevalue; Tasks: associatedae
Root: HKCR; Subkey: "DAE_file"; ValueType: string; ValueName: ""; ValueData: "COLLADA file"; Flags: uninsdeletekey; Tasks: associatedae
Root: HKCR; Subkey: "DAE_file\DefaultIcon"; ValueType: string; ValueName: ""; ValueData: "{app}\bin\ctmviewer.exe,0"; Tasks: associatedae
Root: HKCR; Subkey: "DAE_file\shell\open\command"; ValueType: string; ValueName: ""; ValueData: """{app}\bin\ctmviewer.exe"" ""%1"""; Tasks: associatedae

Root: HKCR; Subkey: ".obj"; ValueType: string; ValueName: ""; ValueData: "OBJ_file"; Flags: uninsdeletevalue; Tasks: associateobj
Root: HKCR; Subkey: "OBJ_file"; ValueType: string; ValueName: ""; ValueData: "Wavefront OBJ file"; Flags: uninsdeletekey; Tasks: associateobj
Root: HKCR; Subkey: "OBJ_file\DefaultIcon"; ValueType: string; ValueName: ""; ValueData: "{app}\bin\ctmviewer.exe,0"; Tasks: associateobj
Root: HKCR; Subkey: "OBJ_file\shell\open\command"; ValueType: string; ValueName: ""; ValueData: """{app}\bin\ctmviewer.exe"" ""%1"""; Tasks: associateobj

Root: HKCR; Subkey: ".lwo"; ValueType: string; ValueName: ""; ValueData: "LWO_file"; Flags: uninsdeletevalue; Tasks: associatelwo
Root: HKCR; Subkey: "LWO_file"; ValueType: string; ValueName: ""; ValueData: "LightWave object file"; Flags: uninsdeletekey; Tasks: associatelwo
Root: HKCR; Subkey: "LWO_file\DefaultIcon"; ValueType: string; ValueName: ""; ValueData: "{app}\bin\ctmviewer.exe,0"; Tasks: associatelwo
Root: HKCR; Subkey: "LWO_file\shell\open\command"; ValueType: string; ValueName: ""; ValueData: """{app}\bin\ctmviewer.exe"" ""%1"""; Tasks: associatelwo

Root: HKCR; Subkey: ".off"; ValueType: string; ValueName: ""; ValueData: "OFF_file"; Flags: uninsdeletevalue; Tasks: associateoff
Root: HKCR; Subkey: "OFF_file"; ValueType: string; ValueName: ""; ValueData: "Geomview object file"; Flags: uninsdeletekey; Tasks: associateoff
Root: HKCR; Subkey: "OFF_file\DefaultIcon"; ValueType: string; ValueName: ""; ValueData: "{app}\bin\ctmviewer.exe,0"; Tasks: associateoff
Root: HKCR; Subkey: "OFF_file\shell\open\command"; ValueType: string; ValueName: ""; ValueData: """{app}\bin\ctmviewer.exe"" ""%1"""; Tasks: associateoff

[Code]

// ----------------------------------------------------------------------------
// ModPath script, by Jared Breland
// Homepage: http://www.legroom.net/software
// ----------------------------------------------------------------------------

function ModPathDir(): TArrayOfString;
var
	Dir:	TArrayOfString;
begin
	setArrayLength(Dir, 1)
	Dir[0] := ExpandConstant('{app}\bin');
	Result := Dir;
end;

procedure ModPath();
var
	oldpath:	String;
	newpath:	String;
	pathArr:	TArrayOfString;
	aExecFile:	String;
	aExecArr:	TArrayOfString;
	i, d:		Integer;
	pathdir:	TArrayOfString;
begin

	// Get array of new directories and act on each individually
	pathdir := ModPathDir();
	for d := 0 to GetArrayLength(pathdir)-1 do begin

		// Modify WinNT path
		if UsingWinNT() = true then begin

			// Get current path, split into an array
			RegQueryStringValue(HKEY_LOCAL_MACHINE, 'SYSTEM\CurrentControlSet\Control\Session Manager\Environment', 'Path', oldpath);
			oldpath := oldpath + ';';
			i := 0;
			while (Pos(';', oldpath) > 0) do begin
				SetArrayLength(pathArr, i+1);
				pathArr[i] := Copy(oldpath, 0, Pos(';', oldpath)-1);
				oldpath := Copy(oldpath, Pos(';', oldpath)+1, Length(oldpath));
				i := i + 1;

				// Check if current directory matches app dir
				if pathdir[d] = pathArr[i-1] then begin
					// if uninstalling, remove dir from path
					if IsUninstaller() = true then begin
						continue;
					// if installing, abort because dir was already in path
					end else begin
						abort;
					end;
				end;

				// Add current directory to new path
				if i = 1 then begin
					newpath := pathArr[i-1];
				end else begin
					newpath := newpath + ';' + pathArr[i-1];
				end;
			end;

			// Append app dir to path if not already included
			if IsUninstaller() = false then
				newpath := newpath + ';' + pathdir[d];

			// Write new path
			RegWriteStringValue(HKEY_LOCAL_MACHINE, 'SYSTEM\CurrentControlSet\Control\Session Manager\Environment', 'Path', newpath);

		// Modify Win9x path
		end else begin

			// Convert to shortened dirname
			pathdir[d] := GetShortName(pathdir[d]);

			// If autoexec.bat exists, check if app dir already exists in path
			aExecFile := 'C:\AUTOEXEC.BAT';
			if FileExists(aExecFile) then begin
				LoadStringsFromFile(aExecFile, aExecArr);
				for i := 0 to GetArrayLength(aExecArr)-1 do begin
					if IsUninstaller() = false then begin
						// If app dir already exists while installing, abort add
						if (Pos(pathdir[d], aExecArr[i]) > 0) then
							abort;
					end else begin
						// If app dir exists and = what we originally set, then delete at uninstall
						if aExecArr[i] = 'SET PATH=%PATH%;' + pathdir[d] then
							aExecArr[i] := '';
					end;
				end;
			end;

			// If app dir not found, or autoexec.bat didn't exist, then (create and) append to current path
			if IsUninstaller() = false then begin
				SaveStringToFile(aExecFile, #13#10 + 'SET PATH=%PATH%;' + pathdir[d], True);

			// If uninstalling, write the full autoexec out
			end else begin
				SaveStringsToFile(aExecFile, aExecArr, False);
			end;
		end;

		// Write file to flag modifypath was selected
		//   Workaround since IsTaskSelected() cannot be called at uninstall and AppName and AppId cannot be "read" in Code section
		if IsUninstaller() = false then
			SaveStringToFile(ExpandConstant('{app}') + '\uninsTasks.txt', WizardSelectedTasks(False), False);
	end;
end;

procedure CurStepChanged(CurStep: TSetupStep);
begin
	if CurStep = ssPostInstall then
		if IsTaskSelected('modifypath') then
			ModPath();
end;

procedure CurUninstallStepChanged(CurUninstallStep: TUninstallStep);
var
	appdir:			String;
	selectedTasks:	String;
begin
	appdir := ExpandConstant('{app}')
	if CurUninstallStep = usUninstall then begin
		if LoadStringFromFile(appdir + '\uninsTasks.txt', selectedTasks) then
			if Pos('modifypath', selectedTasks) > 0 then
				ModPath();
		DeleteFile(appdir + '\uninsTasks.txt')
	end;
end;

function NeedRestart(): Boolean;
begin
	if IsTaskSelected('modifypath') and not UsingWinNT() then begin
		Result := True;
	end else begin
		Result := False;
	end;
end;

