param(
    [string]$AppHeaderPath = (Join-Path $PSScriptRoot "..\src\app.h")
)

$AppHeaderPath = (Resolve-Path $AppHeaderPath).Path
$content = Get-Content -LiteralPath $AppHeaderPath -Raw

$versionMatch = [regex]::Match($content, '#define\s+APP_VERSION\s+L"(?<v>[0-9]+(\.[0-9]+)*)"')
if (-not $versionMatch.Success) {
    throw "Failed to parse APP_VERSION from $AppHeaderPath"
}

$nameMatch = [regex]::Match($content, '#define\s+APP_NAME\s+L"(?<n>[^\"]+)"')
$appName = if ($nameMatch.Success) { $nameMatch.Groups['n'].Value } else { "simplewall" }

[pscustomobject]@{
    AppName  = $appName
    Version  = $versionMatch.Groups['v'].Value
}
