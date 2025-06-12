#pragma once

#include <string>

namespace Tarn
{
    enum class ErrorKind
    {
        Syntax,
        Type,
        Semantic,
        Lifetime,
        Trait,
        Internal,
        Generation,
        Io
    };

    enum class ErrorSeverity
    {
        Error,
        Warning,
        Note,
        Help
    };

    inline std::string to_string(ErrorKind kind)
    {
        switch (kind)
        {
        case ErrorKind::Syntax:
            return "Syntax";
        case ErrorKind::Type:
            return "Type";
        case ErrorKind::Semantic:
            return "Semantic";
        case ErrorKind::Lifetime:
            return "Lifetime";
        case ErrorKind::Trait:
            return "Trait";
        case ErrorKind::Internal:
            return "Internal";
        case ErrorKind::Generation:
            return "Codegen";
        case ErrorKind::Io:
            return "Io";
        default:
            return "Unknown";
        }
    }

    inline std::string to_string(ErrorSeverity severity)
    {
        switch (severity)
        {
        case ErrorSeverity::Error:
            return "error";
        case ErrorSeverity::Warning:
            return "warning";
        case ErrorSeverity::Note:
            return "note";
        case ErrorSeverity::Help:
            return "help";
        default:
            return "unknown";
        }
    } // namespace Tarn