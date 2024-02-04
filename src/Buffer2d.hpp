#pragma once
#include <vector>

namespace cpp_renderer
{
    template <typename T>
    class Buffer2d
    {
    public:
        const T &operator()(size_t x, size_t y) const
        {
            return data_[y * width_ + x];
        }

        T &operator()(size_t x, size_t y)
        {
            return data_[y * width_ + x];
        }

        void clear(size_t width, size_t height, T value = T())
        {
            data_.resize(0);
            data_.resize(width * height);
            width_ = width;
            height_ = height;
            if (value != T())
            {
                std::fill(data_.begin(), data_.end(), value);
            }
        }
        void clear()
        {
            clear(width_, height_);
        }

    private:
        std::vector<T> data_;
        size_t width_;
        size_t height_;
    };
}