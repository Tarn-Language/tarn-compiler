#pragma once

#include <string>
#include <unordered_map>

namespace Tarn::Errors
{
    inline constexpr const char *TYPE_MISMATCH = "T1001";
    inline constexpr const char *MISSING_SEMICOLON = "T1002";
    inline constexpr const char *UNDECLARED_VARIABLE = "T1003";
    inline constexpr const char *EXPECTED_EXPRESSION = "T1004";
    inline constexpr const char *INTERNAL_COMPILER_ERROR = "T0000";
    inline constexpr const char *UNUSED_VARIABLE = "T2001";

    inline const std::unordered_map<std::string, std::string> DefaultMessages = {
        {TYPE_MISMATCH, "Type mismatch between expected and actual value"},
        {MISSING_SEMICOLON, "Expected `;` to terminate the statement"},
        {UNDECLARED_VARIABLE, "Use of undeclared variable"},
        {EXPECTED_EXPRESSION, "Expected an expression here"},
        {INTERNAL_COMPILER_ERROR, "An unexpected internal compiler error occurred"},
        {UNUSED_VARIABLE, "Variable is declared but never used"},
    };

    inline std::string getHelpLinkFor(const std::string &code)
    {
        return "https://tarn-language.com/errors/" + code;
    }
}