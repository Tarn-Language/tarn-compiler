#pragma once

#include "./ErrorTypes.hpp"
#include <string>
#include <vector>
#include <optional>

namespace Tarn
{
    enum class DiagnosticLevel
    {
        Error,
        Warning,
        Note,
        Help
    };

    struct Label
    {
        Span span;
        std::string message;
        bool isPrimary;
    };

    struct FixItHint
    {
        Span span;
        std::string replacementText;

        std::optional<std::string> note;
    };

    struct Diagnostic
    {
        std::string code;
        std::string message;
        DiagnosticLevel level;

        std::vector<Label> labels;
        std::vector<std::string> notes;
        std::vector<FixItHint> fixIts;

        std::optional<std::string> helpLink;
        std::optional<std::string> sourceLine;
    };
} // namespace Tarn
