#pragma once
#include "TURING_MACHINE.h"

#include <algorithm>
#include <iostream>
#include <limits>
#include <memory>


/*
 * This type is an unsigned integral type with used-defined internal byte-width.
 * Note: this type assumes unsigned operations.
 */
namespace TURING_MACHINE {
    class word_t
    {
    public:
        /* Constructors and Destructor */

        word_t();
        /*
         * Contruct a word with argument size.
         * This should not be used as constructing a word with the argument value.
         */
        explicit word_t(std::size_t size);
        word_t(const word_t &object);
        word_t(word_t &&object);

        ~word_t();


        /* Assignment Operators */
        word_t& operator= (const word_t & rhs);
        word_t& operator= (word_t &&rhs);


        /* Comparison Operators */
        bool operator ==(const word_t &rhs) const;


        /* Arithmetic Operators */
        word_t operator-()const;
        word_t operator+()const;
        word_t& operator-=(const word_t& rhs);
        word_t& operator+=(const word_t& rhs);
        word_t operator~()const;


        /* Increment Decrement Operators */
        word_t& operator++(); // pre-increment: ++a
        word_t& operator--(); // pre-decrement: --a
        word_t operator++(int); // post-increment: a++
        word_t operator--(int); // post-decrement: a--


        /* Property */
        std::size_t size()const;
        bool equalsZero()const;


        /* Access the Value */
        /*
         * Return an unsigned value as the template argument type.
         * T needs to have bitwise operator << and |.
         */
        template <typename T>
        T getValue()const;

        /*
         * Set the word value from the argument value.
         * T needs to have bitwise operator >> and &.
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
    /* Arithmetic Operators */
    word_t operator-(word_t lhs, const word_t& rhs);
    word_t operator+(word_t lhs, const word_t& rhs);


    /* Stream Output Operator */
    std::ostream& operator<<(std::ostream& os, const word_t& word);


    //-------------------------------------------------------------------------
    template<typename T>
    T word_t::getValue() const
    {
        T t = static_cast <T>(0);
        int offset = std::numeric_limits<byte_t>::digits;

        for (std::size_t i = 0; i < size_; i++) {
            t = t << offset;
            t = t | static_cast<T>(bytes_[size_ - 1 - i]);
        }
        return t;
    }

    template<typename T>
    word_t & word_t::setValue(T t)
    {
        T max = static_cast<T>(std::numeric_limits<byte_t>::max());
        int offset = std::numeric_limits<byte_t>::digits;

        std::for_each(bytes_.get(), bytes_.get() + size_,
            [&t, offset, max](byte_t& byte) {
            byte = static_cast<byte_t>(t & max);
            t = t >> offset;
        });
        return *this;
    }
}
