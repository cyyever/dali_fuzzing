/*!
 * \file bmp_test.cpp
 *
 */

#include <dali/image/bmp.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  try {
    if (Size <= 2) {
      return 0;
    }
    dali::DALIImageType image_type=static_cast<dali::DALIImageType>(Data[0]);
    dali::BmpImage img( Data+1,Size-1,image_type);
    img.Decode();
    img.PeekShape();
  } catch (...) {
  }
  return 0; // Non-zero return values are reserved for future use.
}
