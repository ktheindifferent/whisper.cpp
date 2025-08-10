# Test Infrastructure Documentation - whisper.cpp

## Overview
This document describes the testing infrastructure and requirements for the whisper.cpp project, including test execution procedures, requirements, and areas needing test coverage.

## Current Test Infrastructure

### 1. Integration Tests (`tests/run-tests.sh`)
- **Purpose**: End-to-end testing of whisper models against real audio files
- **Requirements**:
  - Built `whisper-cli` executable
  - Downloaded whisper models
  - FFmpeg for audio conversion
  - wget for downloading test audio files
- **Coverage**: Tests English and multilingual transcription
- **Validation**: Uses git diff to compare output against reference transcriptions

### 2. Test Files
- **Reference Files**:
  - `en-0-ref.txt`, `en-1-ref.txt`, `en-2-ref.txt` - English transcription references
  - `es-0-ref.txt` - Spanish transcription reference
- **Test Data Sources**: Audio files from Wikipedia Commons and OpenAI

### 3. LibriSpeech Testing
- **Location**: `tests/librispeech/`
- **Purpose**: Evaluate model performance on LibriSpeech dataset
- **Components**:
  - Python evaluation scripts
  - Text normalizers for comparison
  - Makefile for automation

### 4. JavaScript Tests
- **File**: `tests/test-whisper.js`
- **Purpose**: Test JavaScript bindings and WebAssembly builds

### 5. C API Test
- **File**: `tests/test-c.c`
- **Purpose**: Minimal C API validation

## Build Requirements

### Prerequisites
1. **Build Tools**:
   - CMake (3.10+)
   - C++ compiler (GCC, Clang, MSVC)
   - Make

2. **Runtime Dependencies**:
   - FFmpeg (for audio conversion)
   - wget (for downloading test files)
   - Python 3.x (for evaluation scripts)

3. **Optional**:
   - CUDA toolkit (for GPU testing)
   - Vulkan SDK (for Vulkan backend)
   - Metal framework (macOS)

## Test Execution Procedure

### Step 1: Build the Project
```bash
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . --config Release
```

### Step 2: Download Models
```bash
# Download a specific model
bash ./models/download-ggml-model.sh tiny.en
```

### Step 3: Run Integration Tests
```bash
# Run tests with specific model
./tests/run-tests.sh tiny.en [threads]
```

### Step 4: Run Specific Component Tests
```bash
# Test JavaScript bindings
node tests/test-whisper.js

# Test C API
gcc tests/test-c.c -o test-c && ./test-c
```

## Areas Requiring Test Coverage

### 1. Core Functionality
- [ ] Memory allocation/deallocation patterns
- [ ] Thread safety in multi-threaded scenarios
- [ ] Model loading and initialization
- [ ] Audio preprocessing pipeline
- [ ] Token generation and decoding

### 2. Optimization Paths
- [ ] SIMD implementations (AVX, NEON, VSX)
- [ ] GPU acceleration (CUDA, Vulkan, Metal)
- [ ] Quantization accuracy
- [ ] Mixed precision computation

### 3. Platform-Specific
- [ ] iOS build and execution
- [ ] Android NDK compatibility
- [ ] WebAssembly functionality
- [ ] Windows MSVC/MinGW builds

### 4. Language Bindings
- [ ] Java binding functionality
- [ ] Ruby binding tests
- [ ] Go binding validation
- [ ] Python integration (if applicable)

### 5. Edge Cases
- [ ] Very short audio files (<1 second)
- [ ] Very long audio files (>1 hour)
- [ ] Noisy audio handling
- [ ] Multiple speaker scenarios
- [ ] Different audio formats and sample rates

## Identified Issues from Code Analysis

### TODO/FIXME Items Found
1. **Memory Optimizations** (`src/whisper.cpp`):
   - Line 5849, 6120: Avoid memory allocations in critical paths
   - Line 7367: Allocating memory on every function call

2. **Platform Optimizations** (`src/whisper.cpp`):
   - Line 295: Check if other platforms benefit from optimizations
   - Line 296: CUDA handling of views needs fixing

3. **Performance** (`src/whisper.cpp`):
   - Line 5010: Optimization needed
   - Line 5754: Avoid recomputing unchanged prompts

4. **Correctness** (`src/whisper.cpp`):
   - Line 6360: Timestamp offset correctness
   - Line 7296: Manual clip/transpose efficiency

5. **GGML Library** (`ggml/src/ggml.c`):
   - Multiple TODO items for backward propagation
   - Non-F32 return type implementations needed
   - Tensor operation validations

## Recommended Test Development

### Priority 1: Unit Tests
Create unit tests for:
- Audio preprocessing functions
- Token encoding/decoding
- Model parameter loading
- Memory management utilities

### Priority 2: Performance Tests
Develop benchmarks for:
- Inference speed across different models
- Memory usage patterns
- GPU vs CPU performance comparison
- Quantization impact on accuracy

### Priority 3: Regression Tests
Establish tests for:
- Recent bug fixes
- Platform-specific issues
- Edge case handling
- API compatibility

## Test Automation Recommendations

1. **CI/CD Integration**:
   - Automated builds for multiple platforms
   - Run integration tests on PR submissions
   - Performance regression detection
   - Code coverage reporting

2. **Test Data Management**:
   - Centralized test audio repository
   - Version control for reference transcriptions
   - Automated test data generation

3. **Reporting**:
   - Test execution dashboards
   - Performance trend tracking
   - Failure analysis tools
   - Coverage metrics

## Next Steps

1. Install build dependencies (CMake)
2. Create unit test framework
3. Expand integration test coverage
4. Implement performance benchmarks
5. Set up CI/CD pipeline
6. Document test procedures

---
*Last Updated: 2025-08-10*
*Branch: terragon/maintain-docs-testing-features*