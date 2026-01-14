#define AppName GetEnv('APP_NAME')
#define AppVersion GetEnv('APP_VERSION')
#define SourceDir GetEnv('SOURCE_DIR')
#define OutputDir GetEnv('OUTPUT_DIR')

[Setup]
AppId={{5A0E047D-0B1D-4A4F-9D9A-3B7C4B3AF7D1}
AppName={#AppName}
AppVersion={#AppVersion}
AppPublisher=Henry++
DefaultDirName={autopf}\{#AppName}
DisableProgramGroupPage=yes
OutputDir={#OutputDir}
OutputBaseFilename={#AppName}-{#AppVersion}-setup
Compression=lzma2
SolidCompression=yes
ArchitecturesAllowed=x64
ArchitecturesInstallIn64BitMode=x64
PrivilegesRequired=admin

[Files]
Source: "{#SourceDir}\*"; DestDir: "{app}"; Flags: recursesubdirs createallsubdirs ignoreversion

[Icons]
Name: "{autoprograms}\{#AppName}"; Filename: "{app}\simplewall.exe"

[Run]
Filename: "{app}\simplewall.exe"; Description: "Launch {#AppName}"; Flags: nowait postinstall skipifsilent
