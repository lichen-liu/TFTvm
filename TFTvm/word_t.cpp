#include "word_t.h"
#include "TURING_MACHINE.h"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <iomanip>
#include <iterator>
#include <limits>


namespace {
    using namespace TURING_MACHINE;

    void byteFullAdder(byte_t a, byte_t b, byte_t cin, byte_t& s, byte_t& cout)
    {
        using u_t = unsigned int;
        static constexpr u_t MAX = static_cast<u_t>(std::numeric_limits<byte_t>::max()); // make this const a function scope static variable

        u_t byteSum = static_cast<u_t>(a) + static_cast<u_t>(b) + static_cast<u_t>(cin);
        u_t carryOut = byteSum / (MAX + 1);
        assert(carryOut <= MAX); // carryOut should never overflow the byte_t

        cout = static_cast<byte_t>(carryOut);
        s = static_cast<byte_t>(byteSum % (MAX + 1));
    }
}

namespace TURING_MACHINE {
    word_t::word_t() :word_t(std::size_t(0))
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

    word_t word_t::operator-() const
    {
        word_t obj = operator~();
        ++obj;
        return obj;
    }

    word_t word_t::operator+() const
    {
        return *this;
    }

    word_t & word_t::operator-=(const word_t & rhs)
    {
        operator+=(-rhs);
        return *this;
    }

    word_t & word_t::operator+=(const word_t & rhs)
    {
        std::size_t len = std::min(size_, rhs.size_);

        byte_t cout = 0;
        byte_t cin = 0;
        byte_t s = 0;

        for (std::size_t i = 0; i < len; i++) {
            cin = cout;
            byteFullAdder(bytes_[i], rhs.bytes_[i], cin, s, cout);
            bytes_[i] = s;
        }

        // while we have not yet reached the MSB of this->bytes_
        // propagate the carry
        for (std::size_t i = len; i < size_; i++) {
            cin = cout;
            if (cin == 0)
                break;
            byteFullAdder(bytes_[i], 0, cin, s, cout);
            bytes_[i] = s;
        }

        return *this;
    }

    word_t word_t::operator~() const
    {
        word_t other(*this);
        std::for_each(other.bytes_.get(), other.bytes_.get() + other.size_,
            [](byte_t &byte) {
            byte = ~byte;
        });
        return other;
    }

    word_t & word_t::operator++()
    {
        byte_t cout = 1;
        byte_t cin = 0;
        byte_t s = 0;

        for (std::size_t i = 0; i < size_; ++i) {
            cin = cout;
            if (cin == 0)
                break;
            byteFullAdder(bytes_[i], 0, cin, s, cout);
            bytes_[i] = s;
        }

        return *this;
    }

    word_t & word_t::operator--()
    {
        byte_t cout = std::numeric_limits<byte_t>::max();
        byte_t cin = 0;
        byte_t s = 0;

        for (std::size_t i = 0; i < size_; ++i) {
            cin = cout;
            if (cin == 0)
                break;
            byteFullAdder(bytes_[i], 0, cin, s, cout);
            if (cin == std::numeric_limits<byte_t>::max())
                cout--;
            bytes_[i] = s;
        }

        return *this;
    }

    word_t word_t::operator++(int)
    {
        word_t obj;
        operator++();
        return obj;
    }

    word_t word_t::operator--(int)
    {
        word_t obj;
        operator--();
        return obj;
    }

    std::size_t word_t::size() const
    {
        return size_;
    }

    bool word_t::equalsZero() const
    {
        return std::all_of(bytes_.get(), bytes_.get() + size_,
            [](byte_t byte) ->bool {
            return (byte == 0); });
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

    word_t operator-(word_t lhs, const word_t & rhs)
    {
        lhs -= rhs;
        return lhs;
    }

    word_t operator+(word_t lhs, const word_t & rhs)
    {
        lhs += rhs;
        return lhs;
    }

    std::ostream& operator<<(std::ostream& os, const word_t& word) {
        std::ios_base::fmtflags f(os.flags());// save the os flags

        os << "0x";
        std::size_t n = word.size();
        for (std::size_t i = 0; i < n; i++) {
            os << std::hex << std::nouppercase << std::setfill('0') << std::setw(2) << ((unsigned int)word[n - 1 - i]);
        }

        os.flags(f); // reset os flags
        return os;
    }
}