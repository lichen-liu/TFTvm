#pragma once
#include "TURING_MACHINE.h"

#include <algorithm>
#include <iostream>
#include <limits>
#include <memory>


namespace TURING_MACHINE {
    class word_t
    {
    public:
        word_t();
        word_t(std::size_t size);
        word_t(const word_t &object);
        word_t(word_t &&object);

        ~word_t();

        word_t& operator= (const word_t & rhs);
        word_t& operator= (word_t &&rhs);


        bool operator ==(const word_t &rhs) const;

        std::size_t size()const;

        /*
         * Return an unsigned value as the template argument type.
         * T needs to be an unsigned integral type.
         */
        template <typename T>
        T getValue()const;

        /*
         * Set the word value from the argument value.
         * The argument type is expected to be of unsigned integral type.
         */
        template <typename T>
        word_t& setValue(T t);


        byte_t& at(std::size_t pos);
        const byte_t& at(std::size_t pos)const;
        byte_t& operator[](std::size_t pos);
        const byte_t& operator[](std::size_t pos)const;

        void clear();

    private:
        std::unique_ptr<byte_t[]> bytes_; /*0...size_-1*/
        std::size_t size_;
    };

    std::ostream& operator<<(std::ostream& os, const word_t& word);

    template<typename T>
    T word_t::getValue() const
    {
        T t = static_cast <T>(0);
        T offset = static_cast<T>(std::numeric_limits<byte_t>::max() + 1);
        for (std::size_t i = 0; i < size_; i++) {
            t = (offset) * (t);
            t = t + static_cast<T>(bytes_[size_ - 1 - i]);
        }
        return t;
    }

    template<typename T>
    word_t & word_t::setValue(T t)
    {
        T offset = static_cast<T>(std::numeric_limits<byte_t>::max() + 1);
        std::for_each(bytes_.get(), bytes_.get() + size_,
            [&t, offset](byte_t& byte) {
            byte = static_cast<byte_t>(t % offset);
            t = t / offset;
        });
        return *this;
    }
}
