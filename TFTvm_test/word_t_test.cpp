#include "stdafx.h"
#include "CppUnitTest.h"

#include <limits>

#include "word_t.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace TFTvm_test
{
    using namespace TURING_MACHINE;

    TEST_CLASS(word_t_test)
    {
    public:

        TEST_METHOD(setValue)
        {
            word_t w1(static_cast<std::size_t>(4));
            w1.setValue(static_cast<uint32_t>(std::numeric_limits<uint32_t>::max()));
            Assert::AreEqual(static_cast<byte_t>(0xFF), w1[0]);
            Assert::AreEqual(static_cast<byte_t>(0xFF), w1[1]);
            Assert::AreEqual(static_cast<byte_t>(0xFF), w1[2]);
            Assert::AreEqual(static_cast<byte_t>(0xFF), w1[3]);

            word_t w2(static_cast<std::size_t>(4));
            w2.setValue(static_cast<uint32_t>(0));
            Assert::AreEqual(static_cast<byte_t>(0x0), w2[0]);
            Assert::AreEqual(static_cast<byte_t>(0x0), w2[1]);
            Assert::AreEqual(static_cast<byte_t>(0x0), w2[2]);
            Assert::AreEqual(static_cast<byte_t>(0x0), w2[3]);

            word_t w3(static_cast<std::size_t>(4));
            w3.setValue(static_cast<uint32_t>(8456588));
            Assert::AreEqual(static_cast<byte_t>(0x8C), w3[0]);
            Assert::AreEqual(static_cast<byte_t>(0x09), w3[1]);
            Assert::AreEqual(static_cast<byte_t>(0x81), w3[2]);
            Assert::AreEqual(static_cast<byte_t>(0x00), w3[3]);

            word_t w4(static_cast<std::size_t>(4));
            w4.setValue(static_cast<uint32_t>(465326546));
            Assert::AreEqual(static_cast<byte_t>(0xD2), w4[0]);
            Assert::AreEqual(static_cast<byte_t>(0x51), w4[1]);
            Assert::AreEqual(static_cast<byte_t>(0xBC), w4[2]);
            Assert::AreEqual(static_cast<byte_t>(0x1B), w4[3]);

            word_t w5(static_cast<std::size_t>(4));
            w5.setValue(static_cast<uint32_t>(0xDEADBEEF));
            Assert::AreEqual(static_cast<byte_t>(0xEF), w5[0]);
            Assert::AreEqual(static_cast<byte_t>(0xBE), w5[1]);
            Assert::AreEqual(static_cast<byte_t>(0xAD), w5[2]);
            Assert::AreEqual(static_cast<byte_t>(0xDE), w5[3]);

            word_t w6(static_cast<std::size_t>(4));
            w6.setValue(static_cast<int32_t>(-8838384));
            Assert::AreEqual(static_cast<byte_t>(0x10), w6[0]);
            Assert::AreEqual(static_cast<byte_t>(0x23), w6[1]);
            Assert::AreEqual(static_cast<byte_t>(0x79), w6[2]);
            Assert::AreEqual(static_cast<byte_t>(0xFF), w6[3]);

            word_t w7(static_cast<std::size_t>(4));
            w7.setValue(static_cast<int32_t>(-1));
            Assert::AreEqual(static_cast<byte_t>(0xFF), w7[0]);
            Assert::AreEqual(static_cast<byte_t>(0xFF), w7[1]);
            Assert::AreEqual(static_cast<byte_t>(0xFF), w7[2]);
            Assert::AreEqual(static_cast<byte_t>(0xFF), w7[3]);

            word_t w8(static_cast<std::size_t>(4));
            w8.setValue(static_cast<int32_t>(std::numeric_limits<int32_t>::max()));
            Assert::AreEqual(static_cast<byte_t>(0xFF), w8[0]);
            Assert::AreEqual(static_cast<byte_t>(0xFF), w8[1]);
            Assert::AreEqual(static_cast<byte_t>(0xFF), w8[2]);
            Assert::AreEqual(static_cast<byte_t>(0x7F), w8[3]);

            word_t w9(static_cast<std::size_t>(4));
            w9.setValue(static_cast<int32_t>(std::numeric_limits<int32_t>::lowest()));
            Assert::AreEqual(static_cast<byte_t>(0x00), w9[0]);
            Assert::AreEqual(static_cast<byte_t>(0x00), w9[1]);
            Assert::AreEqual(static_cast<byte_t>(0x00), w9[2]);
            Assert::AreEqual(static_cast<byte_t>(0x80), w9[3]);

            word_t w10(static_cast<std::size_t>(2));
            w10.setValue(static_cast<uint32_t>(0xDEADBEEF));
            Assert::AreEqual(static_cast<byte_t>(0xEF), w10[0]);
            Assert::AreEqual(static_cast<byte_t>(0xBE), w10[1]);
        }
    };
}