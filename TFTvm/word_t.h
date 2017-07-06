#pragma once
#include "TURING_MACHINE.h"

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

        byte_t& at(std::size_t pos);
        const byte_t& at(std::size_t pos)const;
        byte_t& operator[](std::size_t pos);
        const byte_t& operator[](std::size_t pos)const;

        void clear();

    private:
        std::unique_ptr<byte_t[]> bytes_; /*0...size_-1*/
        std::size_t size_;
    };
}
