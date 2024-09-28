# Array of input and output file names
$inputFiles = @("input_demo.txt", "input_easy1.txt", "input_easy2.txt", "input_medium1.txt", "input_medium2.txt")
$outputFiles = @("output_demo.txt", "output_easy1.txt", "output_easy2.txt", "output_medium1.txt", "output_medium2.txt")

# Compile the sequential and parallel programs
gcc -o conv_sequential conv_sequential.c
gcc -fopenmp -o conv_parallel conv_parallel.c

# Iterate over each input file
for ($i = 0; $i -lt $inputFiles.Count; $i++) {
    Write-Host "Running tests for input: $($inputFiles[$i])"

    # Run the sequential program and measure its time
    Write-Host "Running conv_sequential..."
    $seqStopwatch = [System.Diagnostics.Stopwatch]::StartNew()
    Get-Content $inputFiles[$i] | .\conv_sequential.exe > seq_output.txt
    $seqStopwatch.Stop()
    $seqTime = $seqStopwatch.Elapsed.TotalSeconds

    # Run the parallel program and measure its time
    Write-Host "Running conv_parallel..."
    $parStopwatch = [System.Diagnostics.Stopwatch]::StartNew()
    Get-Content $inputFiles[$i] | .\conv_parallel.exe > par_output.txt
    $parStopwatch.Stop()
    $parTime = $parStopwatch.Elapsed.TotalSeconds

    # Compare the outputs
    Write-Host "Comparing outputs..."
    $seqOutput = Get-Content seq_output.txt
    $parOutput = Get-Content par_output.txt
    $expectedOutput = Get-Content $outputFiles[$i]

    $seqDiff = Compare-Object $seqOutput $expectedOutput -ExcludeDifferent
    $parDiff = Compare-Object $parOutput $expectedOutput -ExcludeDifferent

    if ($seqDiff.Count -eq 0) {
        Write-Host "Test $($inputFiles[$i]) passed for conv_sequential!"
    } else {
        Write-Host "Test $($inputFiles[$i]) failed for conv_sequential!"
    }

    if ($parDiff.Count -eq 0) {
        Write-Host "Test $($inputFiles[$i]) passed for conv_parallel!"
    } else {
        Write-Host "Test $($inputFiles[$i]) failed for conv_parallel!"
    }

    # Calculate and show speedup
    if ($parTime -gt 0) {
        $speedup = $seqTime / $parTime
        Write-Host "Speedup for input $($inputFiles[$i]): $speedup times"
    } else {
        Write-Host "Parallel execution time is zero, cannot calculate speedup."
    }

    # Show the time comparison
    Write-Host "Time taken by conv_sequential: $seqTime seconds"
    Write-Host "Time taken by conv_parallel: $parTime seconds"
    Write-Host "-----------------------------------"
}
