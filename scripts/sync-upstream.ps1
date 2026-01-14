<# 
.SYNOPSIS
    Syncs local repository with upstream henrypp/simplewall

.DESCRIPTION
    This script fetches the latest changes from the upstream repository
    and helps merge them into your local fork.

.EXAMPLE
    .\scripts\sync-upstream.ps1
    
.EXAMPLE
    .\scripts\sync-upstream.ps1 -AutoMerge
#>

param(
    [switch]$AutoMerge = $false,
    [switch]$DryRun = $false
)

$ErrorActionPreference = "Stop"

Write-Host "=== Upstream Sync Script ===" -ForegroundColor Cyan

# Check if upstream remote exists
$remotes = git remote -v
if ($remotes -notmatch "upstream") {
    Write-Host "Adding upstream remote..." -ForegroundColor Yellow
    git remote add upstream https://github.com/henrypp/simplewall.git
}

# Fetch upstream
Write-Host "`nFetching upstream changes..." -ForegroundColor Yellow
git fetch upstream

# Get current branch
$currentBranch = git branch --show-current
Write-Host "Current branch: $currentBranch" -ForegroundColor Green

# Check for differences
$localHead = git rev-parse HEAD
$upstreamHead = git rev-parse upstream/master

if ($localHead -eq $upstreamHead) {
    Write-Host "`nAlready up to date with upstream!" -ForegroundColor Green
    exit 0
}

# Show what's new
Write-Host "`nNew commits from upstream:" -ForegroundColor Cyan
git log --oneline HEAD..upstream/master | Select-Object -First 20

$commitCount = (git rev-list --count HEAD..upstream/master)
Write-Host "`nTotal new commits: $commitCount" -ForegroundColor Yellow

if ($DryRun) {
    Write-Host "`n[Dry Run] Would merge $commitCount commits from upstream" -ForegroundColor Magenta
    exit 0
}

if ($AutoMerge) {
    Write-Host "`nAuto-merging upstream changes..." -ForegroundColor Yellow
    
    # Create backup branch
    $backupBranch = "backup-$(Get-Date -Format 'yyyyMMdd-HHmmss')"
    git branch $backupBranch
    Write-Host "Created backup branch: $backupBranch" -ForegroundColor Green
    
    # Attempt merge
    try {
        git merge upstream/master -m "Merge upstream changes from henrypp/simplewall"
        Write-Host "`nMerge successful!" -ForegroundColor Green
    }
    catch {
        Write-Host "`nMerge conflicts detected!" -ForegroundColor Red
        Write-Host "Please resolve conflicts manually, then run:" -ForegroundColor Yellow
        Write-Host "  git add ." -ForegroundColor White
        Write-Host "  git commit" -ForegroundColor White
        Write-Host "`nTo abort the merge:" -ForegroundColor Yellow
        Write-Host "  git merge --abort" -ForegroundColor White
        exit 1
    }
}
else {
    Write-Host "`nTo merge upstream changes, run:" -ForegroundColor Yellow
    Write-Host "  git merge upstream/master" -ForegroundColor White
    Write-Host "`nOr use -AutoMerge flag:" -ForegroundColor Yellow
    Write-Host "  .\scripts\sync-upstream.ps1 -AutoMerge" -ForegroundColor White
}
