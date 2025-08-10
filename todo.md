# TODO List - whisper.cpp

## Immediate Tasks

### Testing & Quality Assurance
- [ ] Run complete test suite with `tests/run-tests.sh`
- [ ] Validate all example applications build correctly
- [ ] Test model download and conversion scripts
- [ ] Verify WebAssembly builds are functional
- [ ] Test GPU acceleration paths (CUDA, Vulkan, Metal)
- [ ] Validate quantization functionality
- [ ] Check memory leak detection in debug builds

### Code Improvements
- [ ] Review recent CUDA optimizations for correctness
- [ ] Investigate SYCL reorder optimization issues
- [ ] Validate split-mode row functionality for MMQ
- [ ] Check partial offload assertions in CUDA code
- [ ] Review deprecated WHISPER_CCACHE option removal impact

### Documentation
- [ ] Update build instructions for recent CMake changes
- [ ] Document new HEAPU8 export in stream.wasm
- [ ] Add examples for new features
- [ ] Update API documentation if needed
- [ ] Create migration guide for deprecated features

### Platform-Specific
- [ ] Test iOS build with latest changes
- [ ] Validate Android build process
- [ ] Check WebAssembly worker.js generation
- [ ] Test Docker container builds
- [ ] Verify Windows MSVC and MinGW builds

## Future Enhancements

### Performance
- [ ] Profile and optimize hot paths
- [ ] Investigate further SIMD optimizations
- [ ] Explore additional quantization schemes
- [ ] Optimize memory bandwidth usage
- [ ] Implement batch processing improvements

### Features
- [ ] Extended language model support
- [ ] Improved streaming capabilities
- [ ] Enhanced voice activity detection
- [ ] Better noise handling
- [ ] Multi-speaker diarization support

### Infrastructure
- [ ] Automated performance regression testing
- [ ] Continuous integration improvements
- [ ] Cross-platform testing matrix expansion
- [ ] Benchmark suite enhancements
- [ ] Code coverage reporting

### Bindings & Integration
- [ ] Update language bindings for new features
- [ ] Improve Python integration examples
- [ ] Add Swift package manager support
- [ ] Create NuGet package for .NET
- [ ] Enhance REST API functionality

## Bug Fixes & Issues
- [ ] Review and address open GitHub issues
- [ ] Fix any reported memory leaks
- [ ] Resolve platform-specific build issues
- [ ] Address quantization accuracy concerns
- [ ] Fix streaming latency issues

## Research & Development
- [ ] Investigate new model architectures
- [ ] Explore dynamic quantization
- [ ] Research pruning techniques
- [ ] Evaluate knowledge distillation
- [ ] Study hardware-specific optimizations

## Community & Documentation
- [ ] Create comprehensive tutorials
- [ ] Develop best practices guide
- [ ] Build example gallery
- [ ] Improve troubleshooting documentation
- [ ] Create performance tuning guide

---
*Last Updated: 2025-08-10*
*Branch: terragon/maintain-docs-testing-features*