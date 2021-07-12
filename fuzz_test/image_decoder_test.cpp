/*!
 * \file image_decoder_test.cpp
 */

#include <dali/image/png.h>
#include <fstream>

#include <dali/fuzzing/dali_harness.h>
#include <dali/operators.h>
#include <dali/pipeline/init.h>
#include <dali/pipeline/operator/op_spec.h>

static bool init_flag = false;
static void init() {
  if (init_flag) {
    return;
  }
  // Init DALI
  dali::InitOperatorsLib();
  dali::DALIInit(dali::OpSpec("CPUAllocator"),
                 dali::OpSpec("PinnedCPUAllocator"),
                 dali::OpSpec("GPUAllocator"));
  init_flag = true;
}

namespace dali {
namespace testing {

const std::string &dali_extra_path() {
  static std::string tmp = "";
  return tmp;
}

} // namespace testing
} // namespace dali

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  if (Size != 0) {
    return 0;
  }
  init();

  std::ios_base::sync_with_stdio(false);
  auto startTime = std::chrono::high_resolution_clock::now();
  std::string file_name = "/tmp/dali_fuzz_image_decoder_test";
  {
    auto myfile = std::fstream(file_name, std::ios::out | std::ios::binary);
    myfile.write((const char *)(Data), Size);
  }
  dali::DecoderHarness harness{file_name};
  harness.Run();

  return 0; // Non-zero return values are reserved for future use.
}
