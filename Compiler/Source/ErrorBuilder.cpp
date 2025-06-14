#include "../Resources/ErrorBuilder.hpp";
#include "../Resources/ErrorRegistry.hpp";

namespace Tarn
{
    DiagnosticBuilder::DiagnosticBuilder(std::string code, DiagnosticLevel level, std::string message)
    {
        diag.code = std::move(code);
        diag.level = level;
        diag.message = std::move(message);

        diag.helpLink = Errors::getHelpLinkFor(diag.code);
    }

    DiagnosticBuilder &DiagnosticBuilder::primaryLabel(const Span &span, const std::string &message)
    {
        diag.labels.push_back(Label{span, message, true});
        return *this;
    }

    DiagnosticBuilder &DiagnosticBuilder::secondaryLabel(const Span &span, const std::string &message)
    {
        diag.labels.push_back(Label{span, message, false});
        return *this;
    }

    DiagnosticBuilder &DiagnosticBuilder::addNote(const std::string &note)
    {
        diag.notes.push_back(note);
        return *this;
    }

    DiagnosticBuilder &DiagnosticBuilder::addFixIt(const Span &span, const std::string &replacement, std::optional<std::string> note)
    {
        diag.fixIts.push_back(FixItHint{span, replacement, note});
        return *this;
    }

    DiagnosticBuilder &DiagnosticBuilder::setHelpLink(const std::string &link)
    {
        diag.helpLink = link;
        return *this;
    }

    Diagnostic DiagnosticBuilder::build() const
    {
        return diag;
    }
} // namespace Tarn
