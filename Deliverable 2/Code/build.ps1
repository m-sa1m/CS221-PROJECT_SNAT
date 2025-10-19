# PowerShell Script to compile and run a multi-file C++ project

# Step 1: Define file names
$sourceFiles = "main.cpp", "algorithm.cpp", "structure.cpp"
$outputFile = "program.exe"

# Step 2: Remove old executable if it exists
if (Test-Path $outputFile) {
    Remove-Item $outputFile
    Write-Host "Old executable removed." -ForegroundColor Yellow
}

# Step 3: Compile the C++ files
Write-Host "Compiling project..." -ForegroundColor Cyan
g++ -std=c++17 -Wall -O2 $sourceFiles -o $outputFile

# Step 4: Check if compilation succeeded
if ($LASTEXITCODE -eq 0) {
    Write-Host "✅ Compilation successful!" -ForegroundColor Green
    Write-Host "Running program..." -ForegroundColor Cyan
    ./program.exe
} else {
    Write-Host "❌ Compilation failed!" -ForegroundColor Red
}

# Set-ExecutionPolicy -Scope Process -ExecutionPolicy Bypass
#.\build.ps1
