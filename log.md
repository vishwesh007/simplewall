# Log

## 2026-01-14

### Build Fixes - ULONG_PTR Type Widening

The build was failing with C4244 warnings (treated as errors due to `/WX` flag) caused by narrowing conversions from `ULONG_PTR` to `ULONG`. The root cause was that `_r_str_gethash` and `_app_listview_getitemcontext` return `ULONG_PTR` values (64-bit on x64), but various hash parameters/variables were declared as `ULONG` (32-bit).

**Files modified to fix type mismatches:**

1. **src/profile.h & src/profile.c:**
   - `_app_getappitem` - parameter `app_hash` changed from `ULONG` to `ULONG_PTR`
   - `_app_getruleconfigitem` - parameter `app_hash` changed from `ULONG` to `ULONG_PTR`
   - `_app_getlogitem` - parameter `log_hash` changed from `ULONG` to `ULONG_PTR`
   - `_app_freeapplication` - parameter `app_hash` changed from `ULONG` to `ULONG_PTR`
   - `_app_isappfound` - parameter `app_hash` changed from `ULONG` to `ULONG_PTR`
   - `_app_issystemhash` - parameter `app_hash` changed from `ULONG` to `ULONG_PTR`
   - `_app_ruleremoveapp` - parameter `app_hash` changed from `ULONG` to `ULONG_PTR`

2. **src/network.h & src/network.c:**
   - `_app_network_getitem` - parameter `network_hash` changed from `ULONG` to `ULONG_PTR`
   - `_app_network_getappitem` - parameter `app_hash` changed from `ULONG` to `ULONG_PTR`
   - `_app_network_gethash` - return type and local `hash_code` changed from `ULONG` to `ULONG_PTR`
   - `_app_network_isitemfound` - parameter changed from `ULONG` to `ULONG_PTR`
   - `_app_network_removeitem` - parameter `network_hash` changed from `ULONG` to `ULONG_PTR`

3. **src/listview.h & src/listview.c:**
   - `_app_listview_addnetworkitem` - parameter `network_hash` changed from `ULONG` to `ULONG_PTR`

4. **src/wfp.h & src/wfp.c:**
   - `_wfp_createrulefilter` - parameter `app_hash` changed from `ULONG` to `ULONG_PTR`

5. **src/messages.c:**
   - Removed `(ULONG)` casts from `_app_listview_getitemcontext` calls at lines 2387, 2574, 2912

6. **src/helper.c:**
   - Initialized `PR_STRING string = NULL` in `_app_getfilehashinfo` to fix C4703 "potentially uninitialized local pointer" error at line 1103

**Why these changes were needed:**
- On 64-bit systems, `ULONG_PTR` is 64 bits while `ULONG` is 32 bits
- The routine library's `_r_str_gethash` returns `ULONG_PTR` for hash values
- Storing 64-bit hash values in 32-bit variables causes data loss warnings
- The `/WX` compiler flag treats warnings as errors, breaking the build

**How to reproduce the fix yourself:**
1. Search for all function declarations using `ULONG app_hash` or similar hash parameters
2. Change them to `ULONG_PTR app_hash` in both headers (.h) and implementations (.c)
3. Update local variables storing hash values to use `ULONG_PTR`
4. Remove any explicit `(ULONG)` casts that truncate `ULONG_PTR` values

### Portable Package Creation

Created portable distribution package at:
- Folder: `%USERPROFILE%\Desktop\simplewall-3.8.7-portable`
- ZIP: `%USERPROFILE%\Desktop\simplewall-3.8.7-bin.zip`

**Contents of the portable package:**
- `simplewall.exe` - Main application (1.0 MB)
- `portable.dat` - Marker file for portable mode
- `simplewall.lng` - Language strings
- `profile_internal.sp` - Internal profile (signed)
- `profile_internal.xml` - Internal profile (XML)
- `i18n/` - Localization files (27 languages)
- `History.txt`, `License.txt`, `Readme.txt` - Documentation

**How to create the package manually:**
```powershell
$version = "3.8.7"
$outDir = "$env:USERPROFILE\Desktop\simplewall-$version-portable"
New-Item -ItemType Directory -Force -Path $outDir
Copy-Item "bin\64\simplewall.exe" $outDir
Copy-Item "bin\*.txt" $outDir
Copy-Item "bin\*.lng" $outDir
Copy-Item "bin\*.sp" $outDir
Copy-Item "bin\*.xml" $outDir
Copy-Item -Recurse "bin\i18n" $outDir
New-Item -ItemType File -Path "$outDir\portable.dat" -Value "#PORTABLE#"
Compress-Archive -Path "$outDir\*" -DestinationPath "$env:USERPROFILE\Desktop\simplewall-$version-bin.zip"
```

---

- Added `scripts/check-deps.ps1` to probe VS dev command, Windows SDK, Inno Setup, and Python paths before builds. Run it with `pwsh -NoProfile -ExecutionPolicy Bypass -File .\scripts\check-deps.ps1 | Format-List *` to verify prerequisites.
- Initial inline dependency checks failed because PowerShell parsing of `$env:ProgramFiles(x86)` broke inside one-liners; fixed by bracing env vars inside the script and rerunning.
- Installed Inno Setup 6 via winget so the installer build can run: `winget install --id JRSoftware.InnoSetup --exact --accept-package-agreements --accept-source-agreements`.
- Extended the dependency probe to detect per-user Inno Setup installs (`%LOCALAPPDATA%\Programs\Inno Setup 6\ISCC.exe`) and confirmed current prerequisites: VSDevCmd present, Windows SDK 10.0.26100.0 present, Inno Setup detected, Python 3.12 available.

### Installer Creation & Installation

Created Windows installer using Inno Setup:
- Installer: `%USERPROFILE%\Desktop\simplewall-3.8.7-setup.exe`
- Installed to: `C:\Program Files\simplewall`

**How to create the installer manually:**
```powershell
# Set environment variables for Inno Setup
$env:APP_NAME = "simplewall"
$env:APP_VERSION = "3.8.7"
$env:SOURCE_DIR = "C:\Users\vishw\Desktop\simplewall-3.8.7-portable"
$env:OUTPUT_DIR = "$env:USERPROFILE\Desktop"

# Run Inno Setup compiler
& "$env:LOCALAPPDATA\Programs\Inno Setup 6\ISCC.exe" "installer\simplewall.iss"
```

**Silent installation (for automation):**
```powershell
Start-Process -FilePath "simplewall-3.8.7-setup.exe" -ArgumentList "/VERYSILENT", "/SUPPRESSMSGBOXES", "/NORESTART" -Wait -Verb RunAs
```

### CI/CD Setup - Upstream Sync & Build Automation

Created GitHub Actions workflows to automate:
1. **Syncing with upstream** (`henrypp/simplewall`)
2. **Building releases**

**Files created:**
- `.github/workflows/sync-upstream.yml` - Automatically checks for upstream changes daily and creates PRs
- `.github/workflows/build.yml` - Builds the project on push and can create releases
- `scripts/sync-upstream.ps1` - Manual sync script for local development

**Why CI/CD was set up:**
- The upstream `henrypp/simplewall` repository receives regular updates
- Without automation, you'd need to manually fetch and merge changes
- The workflow automatically detects new commits and creates pull requests for review
- Build workflow ensures code compiles after merging upstream changes

**How the upstream sync works:**
1. GitHub Actions runs daily at 6 AM UTC (or manually triggered)
2. Fetches the latest `upstream/master` branch
3. Compares with your fork's master branch
4. If changes exist, creates a PR with the new commits
5. You review the PR, resolve any conflicts, and merge

**How to manually sync with upstream:**
```powershell
# Option 1: Use the sync script
.\scripts\sync-upstream.ps1 -AutoMerge

# Option 2: Manual git commands
git remote add upstream https://github.com/henrypp/simplewall.git
git fetch upstream
git merge upstream/master
```

**How to trigger a release:**
- Include `[release]` in your commit message, OR
- Manually trigger the workflow from GitHub Actions tab with `create_release: true`

### Repository Configuration

Added upstream remote for tracking the main fork:
```
origin    https://github.com/vishwesh007/simplewall.git (your fork)
upstream  https://github.com/henrypp/simplewall.git (main repository)
```

