#pragma once

#include "./ErrorTypes.hpp"
#include "./ErrorOutputFormat.hpp"
#include "./ErrorSpan.hpp"

#include <string>
#include <functional>

namespace Tarn
{
    class DiagnosticFormatter
    {
    public:
        DiagnosticFormatter(OutputConfig config);

        void setSourceProvider(std::function<std::optional<std::string>(const std::string &)> provider);
        std::string format(const Diagnostic &diag) const;
        std::string formatAsJson(const Diagnostic &diag) const;

    private:
        OutputConfig config;
        std::function<std::optional<std::string>(const std::string &)> sourceProvider;

        std::string renderHumanReadable(const Diagnostic &diag) const;
        std::string renderPlainText(const Diagnostic &diag) const;
        std::string getLevelPrefix(DiagnosticLevel level) const;
        std::string applyColor(const std::string &text, DiagnosticLevel level) const;
        std::string underlineSpan(const Span &span, const std::string &sourceLine, const std::string &message, bool isPrimary) const;
    };
} // namespace Tarn
