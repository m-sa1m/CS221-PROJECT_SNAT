# ============================================
# SNAT Build Script - Deliverable 3
# Secure Network Assessment Tool
# ============================================

Write-Host "`n╔════════════════════════════════════════╗" -ForegroundColor Cyan
Write-Host "║   SNAT Compilation Script v3.0        ║" -ForegroundColor Cyan
Write-Host "║   Deliverable 3 - Final Build         ║" -ForegroundColor Cyan
Write-Host "╚════════════════════════════════════════╝`n" -ForegroundColor Cyan

# Define source files
$sourceFiles = @(
    "main.cpp",
    "structure.cpp",
    "algorithm.cpp",
    "menu.cpp",
    "input.cpp",
    "fileio.cpp"
)

$outputFile = "snat.exe"

# Step 1: Display source files
Write-Host "📁 Source Files:" -ForegroundColor Green
foreach ($file in $sourceFiles) {
    if (Test-Path $file) {
        Write-Host "   ✓ $file" -ForegroundColor White
    } else {
        Write-Host "   ✗ $file (MISSING)" -ForegroundColor Red
        Write-Host "`n❌ ERROR: Missing source file!" -ForegroundColor Red
        exit 1
    }
}

# Step 2: Remove old executable
if (Test-Path $outputFile) {
    Remove-Item $outputFile
    Write-Host "`n🗑️  Removed old executable" -ForegroundColor Yellow
}

# Step 3: Compile
Write-Host "`n⚙️  Compiling with g++..." -ForegroundColor Cyan
Write-Host "   Flags: -std=c++17 -Wall -Wextra -O2`n" -ForegroundColor Gray

$compileCommand = "g++ -std=c++17 -Wall -Wextra -O2 " + ($sourceFiles -join " ") + " -o $outputFile"
Invoke-Expression $compileCommand

# Step 4: Check compilation result
if ($LASTEXITCODE -eq 0) {
    Write-Host "`n╔════════════════════════════════════════╗" -ForegroundColor Green
    Write-Host "║   ✅ COMPILATION SUCCESSFUL!          ║" -ForegroundColor Green
    Write-Host "╚════════════════════════════════════════╝`n" -ForegroundColor Green
    
    # Display file size
    $fileSize = (Get-Item $outputFile).Length / 1KB
    Write-Host "📦 Executable size: $($fileSize.ToString('0.00')) KB`n" -ForegroundColor White
    
    # Ask to run
    Write-Host "🚀 Run the program? (y/n): " -ForegroundColor Cyan -NoNewline
    $response = Read-Host
    
    if ($response -eq "y" -or $response -eq "Y") {
        Write-Host "`n╔════════════════════════════════════════╗" -ForegroundColor Cyan
        Write-Host "║          Starting SNAT...             ║" -ForegroundColor Cyan
        Write-Host "╚════════════════════════════════════════╝`n" -ForegroundColor Cyan
        
        & ".\$outputFile"
        
        Write-Host "`n╔════════════════════════════════════════╗" -ForegroundColor Cyan
        Write-Host "║       Program Terminated               ║" -ForegroundColor Cyan
        Write-Host "╚════════════════════════════════════════╝`n" -ForegroundColor Cyan
    } else {
        Write-Host "`n✓ Build complete. Run with: .\$outputFile`n" -ForegroundColor Green
    }
    
} else {
    Write-Host "`n╔════════════════════════════════════════╗" -ForegroundColor Red
    Write-Host "║   ❌ COMPILATION FAILED!              ║" -ForegroundColor Red
    Write-Host "╚════════════════════════════════════════╝`n" -ForegroundColor Red
    Write-Host "Please check the error messages above.`n" -ForegroundColor Yellow
    exit 1
}

# cd 
# Set-ExecutionPolicy -Scope Process -ExecutionPolicy Bypass
#.\build.ps1
