/*!
 * \file jpg_test.cpp
 *
 */

#include <dali/image/jpeg2k.h>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  try {
    if (Size <= 3) {
      return 0;
    }
    dali::DALIImageType image_type =
        static_cast<dali::DALIImageType>(Data[0] % 5);

    std::vector<uint8_t> real_data;
    real_data.resize(Size - 1);
    memcpy(real_data.data(), Data + 1, Size - 1);
    real_data[0] = 0xFF;
    real_data[1] = 0xD8;
    dali::Jpeg2kImage img(real_data.data(), real_data.size(), image_type);
    img.Decode();
    img.PeekShape();
  } catch (...) {
  }
  return 0; // Non-zero return values are reserved for future use.
}
