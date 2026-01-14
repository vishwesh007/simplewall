[CmdletBinding()]
param(
    [ValidateSet('Release','Debug')]
    [string]$Configuration = 'Release',

    [ValidateSet('x64','x86','ARM64')]
    [string[]]$Platforms = @('x64'),

    [switch]$Clean,
    [switch]$Package,
    [switch]$Installer
)

Set-StrictMode -Version Latest
$ErrorActionPreference = 'Stop'

$repoRoot = (Resolve-Path (Join-Path $PSScriptRoot '..')).Path
$versionInfo = & (Join-Path $PSScriptRoot 'get-version.ps1')
$appName = $versionInfo.AppName
$appVersion = $versionInfo.Version

function Find-VsDevCmd {
    $candidates = @(
        "${env:ProgramFiles(x86)}\Microsoft Visual Studio\2022\BuildTools\Common7\Tools\VsDevCmd.bat",
        "${env:ProgramFiles}\\Microsoft Visual Studio\\2022\\BuildTools\\Common7\\Tools\\VsDevCmd.bat",
        "${env:ProgramFiles(x86)}\Microsoft Visual Studio\2022\Community\Common7\Tools\VsDevCmd.bat",
        "${env:ProgramFiles}\\Microsoft Visual Studio\\2022\\Community\\Common7\\Tools\\VsDevCmd.bat",
        "${env:ProgramFiles(x86)}\Microsoft Visual Studio\2026\Community\Common7\Tools\VsDevCmd.bat",
        "${env:ProgramFiles}\\Microsoft Visual Studio\\2026\\Community\\Common7\\Tools\\VsDevCmd.bat"
    )

    foreach ($p in $candidates) {
        if (Test-Path -LiteralPath $p) { return $p }
    }

    return $null
}

function Invoke-MSBuildInDevEnv {
    param(
        [Parameter(Mandatory=$true)][string]$MsBuildArgs
    )

    $vsDevCmd = Find-VsDevCmd
    if (-not $vsDevCmd) {
        throw "Visual Studio Build Tools not found. Install 'Visual Studio BuildTools 2022' with the 'Desktop development with C++' (VCTools) workload, then re-run."
    }

    $cmd = "`"$vsDevCmd`" -no_logo -arch=amd64 -host_arch=amd64 && msbuild $MsBuildArgs"
    Write-Host "[build] $cmd"

    Push-Location $repoRoot
    try {
        cmd.exe /c $cmd
        if ($LASTEXITCODE -ne 0) {
            throw "MSBuild failed with exit code $LASTEXITCODE"
        }
    } finally {
        Pop-Location
    }
}

$solution = Join-Path $repoRoot 'simplewall.sln'
if (-not (Test-Path -LiteralPath $solution)) {
    throw "Missing solution file: $solution"
}

    $kitsRoot = "${env:ProgramFiles(x86)}\Windows Kits\10\"
    $sdkLibRoot = Join-Path $kitsRoot 'Lib'
    if (-not (Test-Path -LiteralPath $sdkLibRoot)) {
        throw "Windows SDK not found at: $sdkLibRoot"
    }

    # Let MSBuild/VS pick the best matching SDK. We only verify presence.
    $sdkMsBuildProps = ""

# Restore packages (CppWinRT via packages.config)
Invoke-MSBuildInDevEnv ("/t:Restore /m $sdkMsBuildProps `"$solution`"")

foreach ($platform in $Platforms) {
    $slnPlatform = switch ($platform) {
        'x64' { 'x64' }
        'x86' { 'x86' }   # maps to Win32 inside the solution
        'ARM64' { 'ARM64' }
    }

    if ($Clean) {
        Invoke-MSBuildInDevEnv ("/t:Clean /m $sdkMsBuildProps /p:Configuration=$Configuration /p:Platform=$slnPlatform `"$solution`"")
    }

    Invoke-MSBuildInDevEnv ("/t:Build /m $sdkMsBuildProps /p:Configuration=$Configuration /p:Platform=$slnPlatform `"$solution`"")
}

if ($Package -or $Installer) {
    $distRoot = Join-Path $repoRoot 'dist'
    New-Item -ItemType Directory -Force -Path $distRoot | Out-Null

    $resourceRoot = Join-Path $repoRoot 'bin'
    $resourceItems = @('History.txt','License.txt','Readme.txt','simplewall.lng','profile_internal.sp','profile_internal.xml','i18n')

    foreach ($platform in $Platforms) {
        $archFolder = switch ($platform) {
            'x64' { '64' }
            'x86' { '32' }
            'ARM64' { 'arm64' }
        }

        $builtExe = Join-Path $repoRoot ("bin\\$archFolder\\simplewall.exe")
        if (-not (Test-Path -LiteralPath $builtExe)) {
            throw "Build output missing: $builtExe"
        }

        $packageName = "$appName-$appVersion-portable-$platform"
        $stageDir = Join-Path $distRoot $packageName

        if (Test-Path $stageDir) { Remove-Item -Recurse -Force $stageDir }
        New-Item -ItemType Directory -Force -Path $stageDir | Out-Null

        Copy-Item -LiteralPath $builtExe -Destination (Join-Path $stageDir 'simplewall.exe') -Force

        foreach ($item in $resourceItems) {
            $src = Join-Path $resourceRoot $item
            if (Test-Path -LiteralPath $src) {
                Copy-Item -LiteralPath $src -Destination $stageDir -Recurse -Force
            }
        }

        $zipPath = Join-Path $distRoot "$packageName.zip"
        if (Test-Path $zipPath) { Remove-Item -Force $zipPath }
        Compress-Archive -Path (Join-Path $stageDir '*') -DestinationPath $zipPath

        Write-Host "[package] $zipPath"

        if ($Installer -and $platform -eq 'x64') {
            $iscc = @(
                "${env:ProgramFiles(x86)}\Inno Setup 6\ISCC.exe",
                "${env:ProgramFiles}\\Inno Setup 6\\ISCC.exe",
                "${env:LOCALAPPDATA}\Programs\Inno Setup 6\ISCC.exe"
            ) | Where-Object { Test-Path -LiteralPath $_ } | Select-Object -First 1

            if (-not $iscc) {
                throw "Inno Setup not found (ISCC.exe). Install Inno Setup 6, then re-run with -Installer."
            }

            $issPath = Join-Path $repoRoot 'installer\\simplewall.iss'
            if (-not (Test-Path -LiteralPath $issPath)) {
                throw "Missing installer script: $issPath"
            }

            $env:APP_NAME = $appName
            $env:APP_VERSION = $appVersion
            $env:SOURCE_DIR = $stageDir
            $env:OUTPUT_DIR = $distRoot

            & $iscc $issPath
            if ($LASTEXITCODE -ne 0) {
                throw "ISCC failed with exit code $LASTEXITCODE"
            }
        }
    }
}

Write-Host "Done. Version: $appVersion"
