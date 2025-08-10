# Project Description - whisper.cpp

## Summary
whisper.cpp is a high-performance C/C++ implementation of OpenAI's Whisper automatic speech recognition (ASR) model, designed for efficient inference without dependencies.

## Current Work Session
- **Date**: 2025-08-10
- **Branch**: terragon/maintain-docs-testing-features
- **Main Branch**: master

## Recent Activities
1. Documentation maintenance and organization
2. Test coverage assessment
3. Project structure analysis
4. Created comprehensive project documentation:
   - `overview.md` - High-level architecture and technical overview
   - `todo.md` - Detailed task list for ongoing and future work
   - `test_infrastructure.md` - Testing requirements and procedures
5. Developed unit test suite:
   - `tests/test-whisper-api.c` - Unit tests for core API functions
6. Identified areas requiring attention:
   - Found 30+ TODO/FIXME items in codebase
   - Memory optimization opportunities
   - Platform-specific improvements needed
   - CUDA view handling issues

## Key Features
- Plain C/C++ implementation without dependencies
- Optimized for various architectures (ARM NEON, x86 AVX, POWER VSX)
- Multiple platform support (macOS, iOS, Android, Linux, Windows, WebAssembly)
- GPU acceleration support (NVIDIA, Vulkan, Metal, Core ML)
- Zero memory allocations at runtime
- Mixed F16/F32 precision and integer quantization support

## Project Structure
- **Core Implementation**: `src/whisper.cpp` and `include/whisper.h`
- **Machine Learning Library**: Based on ggml
- **Bindings**: Available for Java, JavaScript, Ruby, Go
- **Examples**: Multiple platform-specific implementations
- **Tests**: Basic test suite with reference files

## Build System
- CMake-based build configuration
- Platform-specific build scripts
- Docker support available

## Testing Infrastructure
- Test runner script: `tests/run-tests.sh`
- Reference test files for English and Spanish
- LibriSpeech evaluation framework
- JavaScript test implementation

## Areas Requiring Attention
- Expand test coverage for new functionality
- Complete any partially implemented features
- Maintain consistent documentation across all modules
- Regular testing and validation of different build configurations