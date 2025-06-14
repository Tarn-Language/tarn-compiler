#pragma once

#include "./Resources/ErrorTypes.hpp"
#include <utility>

namespace Tarn
{
    class DiagnosticBuilder
    {
    private:
        Diagnostic diag;

    public:
        DiagnosticBuilder(std::string code, DiagnosticLevel level, std::string message);

        DiagnosticBuilder &primaryLabel(const Span &span, const std::string &message);
        DiagnosticBuilder &secondaryLabel(const Span &span, const std::string &message);
        DiagnosticBuilder &addNote(const std::string &note);
        DiagnosticBuilder &addFixIt(const Span &span, const std::string &replacement, std::optional<std::string> note = std::nullopt);
        DiagnosticBuilder &setHelpLink(const std::string &link);

        Diagnostic build() const;
    };
} // namespace Tarn
