#include "stdafx.h"
#include "CppUnitTest.h"

#include <string>
#include <vector>

#include "mif_parser.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace TFTvm_test
{
    using namespace PARSER;

    TEST_CLASS(MIFParser_test)
    {
    public:

        TEST_METHOD(processComment)
        {
            std::vector<std::string> mif =
            { "notcomment",
                "--comment",
                "notcomment--comment",
                "notcomment--comment--comment",
                "---comment",
                "----comment",
                "-notcomment",
                "-0-0-0-0-0",
                "- -notcomment",
                "",
                "---",
                "--",
                "-",
                "%comment%",
                "%comment",
                "comment%notcomment",
                "notcomment%",
                "comment%notcomment",
                "%",
                "comment",
                "comment",
                "%notcomment",
                "notcomment%%notcomment",
                "notcomment%%%comment%%%notcomment",
                "%",
                "",
                "",
                "comment",
                "%",
                "notcomment",
                "notcomment--%comment",
                "notcomment%comment%",
                "%--comment%notcomment%comment%notcomment",
                "--comment%comment%notcomment",
                "notcomment",
                "notcomment-%comment%-comment",
                "notcomment--%comment%-comment",
                "notcomment-%comment%--comment",
                "notcomment-%comment%-a-comment",
                "notcomment-%comment%-a--comment",
                "%%--comment"
            };

            std::vector<std::string> expectedResult =
            { "notcomment",
                "",
                "notcomment",
                "notcomment",
                "",
                "",
                "-notcomment",
                "-0-0-0-0-0",
                "- -notcomment",
                "",
                "",
                "",
                "-",
                "",
                "",
                "notcomment",
                "notcomment",
                "notcomment",
                "",
                "",
                "",
                "notcomment",
                "notcommentnotcomment",
                "notcommentnotcomment",
                "",
                "",
                "",
                "",
                "",
                "notcomment",
                "notcomment",
                "notcomment",
                "notcommentnotcomment",
                "",
                "notcomment",
                "notcomment",
                "notcomment",
                "notcomment",
                "notcomment",
                "notcomment",
                ""
            };

            std::vector<std::string> result;
            MIFParser::processComment(mif, result);

            Assert::IsTrue(expectedResult == result);
        }
    };
}