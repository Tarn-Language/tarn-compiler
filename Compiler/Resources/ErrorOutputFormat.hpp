#pragma once

#include <string>

namespace Tarn
{
    enum class OutputFormat
    {
        HumanReadable,
        PlainText,
        JSON,
        Silent,
        Verbose
    };

    struct OutputConfig
    {
        OutputFormat format = OutputFormat::HumanReadable;

        bool useColor = true;
        bool showSourceLine = true;
        bool showHelpLinks = true;
        bool emitFixSuggestions = true;

        std::string outputToFile = "";
    };
} // namespace Tarn
