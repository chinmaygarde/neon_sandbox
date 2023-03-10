#pragma once

#include "geom.h"
#include "macros.h"

namespace ns {

class Texture {
 public:
  Texture() = default;

  ~Texture() { std::free(allocation_); }

  size_t GetBytesPerPixel() const { return sizeof(Color); }

  Color& operator[](const UPoint& pos) {
    auto* colors = reinterpret_cast<Color*>(allocation_);
    const auto index = size_.x * pos.y + pos.x;
    return colors[index];
  }

  const Color* At(const UPoint& pos = {}) const {
    auto* colors = reinterpret_cast<Color*>(allocation_);
    const auto index = size_.x * pos.y + pos.x;
    return colors + index;
  }

  const Color* GetAllocation() const { return At(); }

  bool Resize(UPoint size) {
    if (size_ == size) {
      return true;
    }
    const auto new_allocation_size = size.x * size.y * GetBytesPerPixel();
    auto new_allocation = std::realloc(allocation_, new_allocation_size);
    if (new_allocation == nullptr) {
      return false;
    }
    allocation_ = reinterpret_cast<uint8_t*>(new_allocation);
    size_ = size;
    return true;
  }

  const UPoint& GetSize() const { return size_; }

  void Clear(Color color);

  void ToGrayscale();

 private:
  uint8_t* allocation_ = nullptr;
  UPoint size_ = {};

  NS_DISALLOW_COPY_AND_ASSIGN(Texture);
};

void SetHaveNeon(bool have_neon);

}  // namespace ns
