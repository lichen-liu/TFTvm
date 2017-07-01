#pragma once
#include <memory>
#include <vector>


namespace MACHINE {
    template <typename WORD>
    class Memory
    {
    public:
        /*
         * Little Endian only makes sense when isByteAddressable==true.
         * If WORD is not a multiple of 1-byte, I don't know whether it works.
         */
        Memory(WORD memorySizeInWords, bool isByteAddressable = true, bool isLittleEndian = true) :m_impl(new IMPL) {
            m_impl->wordSizeInBytes = sizeof(WORD);
            m_impl->memorySizeInWords = memorySizeInWords;
            m_impl->memorySizeInBytes = (m_impl->wordSizeInBytes) * (m_impl->memorySizeInWords);
            m_impl->isByteAddressable = isByteAddressable;
            m_impl->isLittleEndian = isLittleEndian;
            m_impl->word_array.resize(m_impl->memorySizeInWords, static_cast < WORD> 0);
        }

        virtual ~Memory() {}

    private:

        typedef struct {
            std::size_t wordSizeInBytes;
            WORD memorySizeInWords;
            WORD memorySizeInBytes;
            bool isByteAddressable;
            bool isLittleEndian;

            std::vector<WORD> word_array;
        }IMPL;

        std::unique_ptr<IMPL> m_impl;
    };
}
