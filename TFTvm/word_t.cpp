#include "word_t.h"
#include "TURING_MACHINE.h"

#include <algorithm>
#include <cassert>
#include <iterator>


namespace TURING_MACHINE {
    word_t::word_t() :word_t(0)
    {
    }

    word_t::word_t(std::size_t size) :
        bytes_(new byte_t[size]),
        size_(size)
    {
        clear();
    }

    word_t::word_t(const word_t &object) :
        bytes_(new byte_t[object.size_]),
        size_(object.size_)
    {
        std::copy(object.bytes_.get(), object.bytes_.get() + object.size_,
            stdext::checked_array_iterator<byte_t*>(bytes_.get(), size_));
    }

    word_t::word_t(word_t && object) :
        bytes_(std::move(object.bytes_)),
        size_(object.size_)
    {
        object.size_ = 0;
    }

    word_t::~word_t()
    {
    }

    word_t& word_t::operator=(const word_t & rhs)
    {
        if (this == &rhs) // self assignment
            return *this;

        if (size_ != rhs.size_) // need to re-allocate
        {
            size_ = rhs.size_;
            bytes_.reset(new byte_t[size_]);
        }

        std::copy(rhs.bytes_.get(), rhs.bytes_.get() + rhs.size_,
            stdext::checked_array_iterator<byte_t*>(bytes_.get(), size_));

        return *this;
    }

    word_t& word_t::operator=(word_t && rhs)
    {
        if (this == &rhs) // self assignment
            return *this;

        size_ = rhs.size_;
        rhs.size_ = 0;
        bytes_ = std::move(rhs.bytes_);

        return *this;
    }

    bool word_t::operator==(const word_t & rhs) const
    {
        if (this == &rhs) // self comparison
            return true;

        return std::equal(bytes_.get(), bytes_.get() + size_,
            rhs.bytes_.get(), rhs.bytes_.get() + rhs.size_);
    }

    std::size_t word_t::size() const
    {
        return size_;
    }

    byte_t & word_t::at(std::size_t pos)
    {
        assert(pos < size_);
        return bytes_[pos];
    }

    const byte_t & word_t::at(std::size_t pos) const
    {
        assert(pos < size_);
        return bytes_[pos];
    }

    byte_t & word_t::operator[](std::size_t pos)
    {
        assert(pos < size_);
        return bytes_[pos];
    }

    const byte_t & word_t::operator[](std::size_t pos) const
    {
        assert(pos < size_);
        return bytes_[pos];
    }

    void word_t::clear()
    {
        std::for_each(bytes_.get(), bytes_.get() + size_, [](byte_t &ele) {ele = 0; });
    }
}