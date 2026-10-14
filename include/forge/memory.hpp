#pragma once
#include <cstddef>
#include <new>
#include <memory>
#include <utility>
#include <stdexcept>

namespace forge {
class Arena {
    std::byte* memory_;
    std::size_t capacity_;
    std::size_t used_ = 0;
public:
    explicit Arena(std::size_t bytes) : memory_(static_cast<std::byte*>(::operator new(bytes))), capacity_(bytes) {}
    Arena(const Arena&) = delete;
    Arena& operator=(const Arena&) = delete;
    ~Arena() { ::operator delete(memory_); }
    template<class T, class... Args> T* make(Args&&... args) {
        void* place = memory_ + used_;
        std::size_t space = capacity_ - used_;
        if (!std::align(alignof(T), sizeof(T), place, space)) throw std::bad_alloc{};
        auto* object = ::new (place) T(std::forward<Args>(args)...);
        used_ = static_cast<std::byte*>(place) - memory_ + sizeof(T);
        return object;
    }
    std::size_t bytes_used() const noexcept { return used_; }
};
template<class T> class Unique {
    T* ptr_ = nullptr;
public:
    explicit Unique(T* p = nullptr) noexcept : ptr_(p) {}
    Unique(const Unique&) = delete;
    Unique& operator=(const Unique&) = delete;
    Unique(Unique&& other) noexcept : ptr_(std::exchange(other.ptr_, nullptr)) {}
    Unique& operator=(Unique&& other) noexcept { if (this != &other) { delete ptr_; ptr_ = std::exchange(other.ptr_, nullptr); } return *this; }
    ~Unique() { delete ptr_; }
    T* get() const noexcept { return ptr_; }
    T& operator*() const { return *ptr_; }
    T* operator->() const noexcept { return ptr_; }
};
}
