[CmdletBinding()]
param()

$vsDevCmdCandidates = @(
    "${env:ProgramFiles(x86)}\Microsoft Visual Studio\2022\BuildTools\Common7\Tools\VsDevCmd.bat",
    "${env:ProgramFiles}\Microsoft Visual Studio\2022\BuildTools\Common7\Tools\VsDevCmd.bat",
    "${env:ProgramFiles(x86)}\Microsoft Visual Studio\2022\Community\Common7\Tools\VsDevCmd.bat",
    "${env:ProgramFiles}\Microsoft Visual Studio\2022\Community\Common7\Tools\VsDevCmd.bat"
)

$innoSetupCandidates = @(
    "${env:ProgramFiles(x86)}\Inno Setup 6\ISCC.exe",
    "${env:ProgramFiles}\Inno Setup 6\ISCC.exe",
    "${env:LOCALAPPDATA}\Programs\Inno Setup 6\ISCC.exe"
)

$sdkLibRoot = Join-Path ${env:ProgramFiles(x86)} "Windows Kits\10\Lib"
$sdkVersion = if (Test-Path $sdkLibRoot) { Get-ChildItem $sdkLibRoot -Directory | Sort-Object Name -Descending | Select-Object -First 1 } else { $null }

$results = [ordered]@{}
$results['VsDevCmd'] = $vsDevCmdCandidates | Where-Object { Test-Path $_ } | Select-Object -First 1
$results['WinSdk'] = if ($sdkVersion) { $sdkVersion.FullName } else { $null }
$results['InnoSetup'] = $innoSetupCandidates | Where-Object { Test-Path $_ } | Select-Object -First 1
$pythonCmd = Get-Command python -ErrorAction SilentlyContinue
$results['Python'] = if ($pythonCmd) { $pythonCmd.Source } else { $null }

[pscustomobject]$results
