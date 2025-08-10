// Unit tests for whisper.cpp API functions
// This file provides basic unit tests for the core whisper API

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "../include/whisper.h"

// Test result tracking
static int tests_run = 0;
static int tests_passed = 0;
static int tests_failed = 0;

#define TEST_START(name) \
    do { \
        tests_run++; \
        printf("Running test: %s ... ", name); \
        fflush(stdout); \
    } while(0)

#define TEST_PASS() \
    do { \
        tests_passed++; \
        printf("PASSED\n"); \
    } while(0)

#define TEST_FAIL(msg) \
    do { \
        tests_failed++; \
        printf("FAILED: %s\n", msg); \
    } while(0)

#define ASSERT_TRUE(cond, msg) \
    do { \
        if (!(cond)) { \
            TEST_FAIL(msg); \
            return; \
        } \
    } while(0)

#define ASSERT_FALSE(cond, msg) \
    do { \
        if (cond) { \
            TEST_FAIL(msg); \
            return; \
        } \
    } while(0)

#define ASSERT_NOT_NULL(ptr, msg) \
    do { \
        if ((ptr) == NULL) { \
            TEST_FAIL(msg); \
            return; \
        } \
    } while(0)

#define ASSERT_NULL(ptr, msg) \
    do { \
        if ((ptr) != NULL) { \
            TEST_FAIL(msg); \
            return; \
        } \
    } while(0)

// Test functions

void test_context_params_init() {
    TEST_START("whisper_context_default_params");
    
    struct whisper_context_params params = whisper_context_default_params();
    
    // Check default values
    ASSERT_TRUE(params.use_gpu, "GPU should be enabled by default");
    ASSERT_TRUE(params.flash_attn, "Flash attention should be enabled by default");
    
    TEST_PASS();
}

void test_sampling_strategies() {
    TEST_START("whisper_sampling_strategy");
    
    // Test greedy strategy
    int greedy = whisper_sampling_strategy_from_str("greedy");
    ASSERT_TRUE(greedy == WHISPER_SAMPLING_GREEDY, "Greedy strategy should be recognized");
    
    // Test beam search strategy  
    int beam_search = whisper_sampling_strategy_from_str("beam_search");
    ASSERT_TRUE(beam_search == WHISPER_SAMPLING_BEAM_SEARCH, "Beam search strategy should be recognized");
    
    // Test invalid strategy
    int invalid = whisper_sampling_strategy_from_str("invalid_strategy");
    ASSERT_TRUE(invalid == -1, "Invalid strategy should return -1");
    
    TEST_PASS();
}

void test_full_default_params() {
    TEST_START("whisper_full_default_params");
    
    struct whisper_full_params params_greedy = whisper_full_default_params(WHISPER_SAMPLING_GREEDY);
    ASSERT_TRUE(params_greedy.strategy == WHISPER_SAMPLING_GREEDY, "Strategy should be greedy");
    ASSERT_TRUE(params_greedy.n_threads > 0, "Thread count should be positive");
    ASSERT_FALSE(params_greedy.translate, "Translation should be disabled by default");
    ASSERT_TRUE(params_greedy.print_progress, "Progress printing should be enabled by default");
    
    struct whisper_full_params params_beam = whisper_full_default_params(WHISPER_SAMPLING_BEAM_SEARCH);
    ASSERT_TRUE(params_beam.strategy == WHISPER_SAMPLING_BEAM_SEARCH, "Strategy should be beam search");
    ASSERT_TRUE(params_beam.beam_search.beam_size == 5, "Default beam size should be 5");
    
    TEST_PASS();
}

void test_lang_functions() {
    TEST_START("whisper_lang_functions");
    
    // Test language count
    int max_lang_id = whisper_lang_max_id();
    ASSERT_TRUE(max_lang_id > 0, "Should have at least one language");
    
    // Test English language ID
    int en_id = whisper_lang_id("en");
    ASSERT_TRUE(en_id >= 0, "English should be a valid language");
    
    // Test getting language string from ID
    const char* en_str = whisper_lang_str(en_id);
    ASSERT_NOT_NULL(en_str, "Language string should not be null");
    ASSERT_TRUE(strcmp(en_str, "en") == 0, "Language string should be 'en'");
    
    // Test invalid language
    int invalid_id = whisper_lang_id("invalid_lang");
    ASSERT_TRUE(invalid_id == -1, "Invalid language should return -1");
    
    // Test translate token
    int translate_id = whisper_token_translate();
    ASSERT_TRUE(translate_id > 0, "Translate token should be positive");
    
    // Test transcribe token
    int transcribe_id = whisper_token_transcribe();
    ASSERT_TRUE(transcribe_id > 0, "Transcribe token should be positive");
    ASSERT_TRUE(transcribe_id != translate_id, "Transcribe and translate tokens should be different");
    
    TEST_PASS();
}

void test_special_tokens() {
    TEST_START("whisper_special_tokens");
    
    // Test special token IDs
    int eot = whisper_token_eot();
    int sot = whisper_token_sot();
    int solm = whisper_token_solm();
    int prev = whisper_token_prev();
    int nosp = whisper_token_nosp();
    int not_token = whisper_token_not();
    int beg = whisper_token_beg();
    
    // All special tokens should have unique positive IDs
    ASSERT_TRUE(eot > 0, "EOT token should be positive");
    ASSERT_TRUE(sot > 0, "SOT token should be positive");
    ASSERT_TRUE(solm > 0, "SOLM token should be positive");
    ASSERT_TRUE(prev > 0, "PREV token should be positive");
    ASSERT_TRUE(nosp > 0, "NOSP token should be positive");
    ASSERT_TRUE(not_token > 0, "NOT token should be positive");
    ASSERT_TRUE(beg > 0, "BEG token should be positive");
    
    // Check they are all different
    ASSERT_TRUE(eot != sot, "EOT and SOT should be different");
    ASSERT_TRUE(eot != solm, "EOT and SOLM should be different");
    ASSERT_TRUE(sot != solm, "SOT and SOLM should be different");
    
    TEST_PASS();
}

void test_print_timings() {
    TEST_START("whisper_print_timings");
    
    // This test just ensures the function doesn't crash with NULL context
    // In a real test environment, we'd have a valid context
    whisper_print_timings(NULL);
    
    TEST_PASS();
}

void test_log_callback() {
    TEST_START("whisper_log_set");
    
    // Test setting log callback to NULL (disable logging)
    whisper_log_set(NULL, NULL);
    
    // This mainly tests that the function exists and doesn't crash
    TEST_PASS();
}

void test_null_context_safety() {
    TEST_START("null_context_safety");
    
    // Test that functions handle NULL context gracefully
    whisper_free(NULL);
    whisper_free_state(NULL);
    whisper_free_params(NULL);
    whisper_free_context_params(NULL);
    
    // Test functions that should return safe values with NULL
    int n_len = whisper_n_len(NULL);
    ASSERT_TRUE(n_len == 0, "n_len should be 0 for NULL context");
    
    int n_vocab = whisper_n_vocab(NULL);
    ASSERT_TRUE(n_vocab == 0, "n_vocab should be 0 for NULL context");
    
    int n_text_ctx = whisper_n_text_ctx(NULL);
    ASSERT_TRUE(n_text_ctx == 0, "n_text_ctx should be 0 for NULL context");
    
    int n_audio_ctx = whisper_n_audio_ctx(NULL);
    ASSERT_TRUE(n_audio_ctx == 0, "n_audio_ctx should be 0 for NULL context");
    
    int is_multilingual = whisper_is_multilingual(NULL);
    ASSERT_TRUE(is_multilingual == 0, "is_multilingual should be 0 for NULL context");
    
    TEST_PASS();
}

void test_pcm_to_mel_params() {
    TEST_START("whisper_pcm_to_mel_params");
    
    // Test with NULL context and state (should handle gracefully)
    int result = whisper_pcm_to_mel(NULL, NULL, 0, 0, 0);
    ASSERT_TRUE(result != 0, "Should return error for NULL context");
    
    result = whisper_pcm_to_mel_with_state(NULL, NULL, NULL, 0, 0, 0);
    ASSERT_TRUE(result != 0, "Should return error for NULL state");
    
    TEST_PASS();
}

void test_model_type_string() {
    TEST_START("whisper_model_type_readable");
    
    // Test that function returns a string for NULL context
    const char* type_str = whisper_model_type_readable(NULL);
    ASSERT_NOT_NULL(type_str, "Should return a string even for NULL context");
    
    TEST_PASS();
}

// Main test runner
int main(int argc, char** argv) {
    printf("=== Whisper API Unit Tests ===\n\n");
    
    // Run all tests
    test_context_params_init();
    test_sampling_strategies();
    test_full_default_params();
    test_lang_functions();
    test_special_tokens();
    test_print_timings();
    test_log_callback();
    test_null_context_safety();
    test_pcm_to_mel_params();
    test_model_type_string();
    
    // Print summary
    printf("\n=== Test Summary ===\n");
    printf("Tests run:    %d\n", tests_run);
    printf("Tests passed: %d\n", tests_passed);
    printf("Tests failed: %d\n", tests_failed);
    
    if (tests_failed == 0) {
        printf("\nAll tests PASSED!\n");
        return 0;
    } else {
        printf("\nSome tests FAILED!\n");
        return 1;
    }
}