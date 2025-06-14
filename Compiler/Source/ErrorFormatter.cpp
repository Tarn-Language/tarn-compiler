#include "../Resources/ErrorFormatter.hpp";
#include "../Resources/json.hpp";
#include <sstream>
#include <iomanip>

namespace Tarn
{
    DiagnosticFormatter::DiagnosticFormatter(OutputConfig config)
        : config(std::move(config)) {}

    std::string DiagnosticFormatter::format(const Diagnostic &diag) const
    {
        switch (config.format)
        {
        case OutputFormat::HumanReadable:
            return renderHumanReadable(diag);
        case OutputFormat::PlainText:
            return renderPlainText(diag);
        case OutputFormat::JSON:
            return formatAsJson(diag);
        case OutputFormat::Silent:
            return "";
        case OutputFormat::Verbose:
            return renderHumanReadable(diag) + "\n[VERBOSE MODE ENABLED]";
        default:
            return renderPlainText(diag);
        }
    }

    std::string DiagnosticFormatter::formatAsJson(const Diagnostic &diag) const
    {
        nlohmann::json j;
        j["code"] = diag.code;
        j["level"] = getLevelPrefix(diag.level);
        j["message"] = diag.message;

        for (const auto &label : diag.labels)
        {
            j["labels"].push_back({{"file", label.span.fileName},
                                   {"start", {label.span.start.line, label.span.start.column}},
                                   {"end", {label.span.end.line, label.span.end.column}},
                                   {"message", label.message},
                                   {"primary", label.isPrimary}});
        }

        for (const auto &note : diag.notes)
            j["notes"].push_back(note);

        for (const auto &fix : diag.fixIts)
        {
            j["fix_its"].push_back({{"replacement", fix.replacementText},
                                    {"file", fix.span.fileName},
                                    {"start", {fix.span.start.line, fix.span.start.column}},
                                    {"end", {fix.span.end.line, fix.span.end.column}},
                                    {"note", fix.note.value_or("")}});
        }

        if (diag.helpLink)
            j["help_link"] = *diag.helpLink;

        return j.dump(4);
    }

    std::string DiagnosticFormatter::getLevelPrefix(DiagnosticLevel level) const
    {
        switch (level)
        {
        case DiagnosticLevel::Error:
            return "error";
        case DiagnosticLevel::Warning:
            return "warning";
        case DiagnosticLevel::Note:
            return "note";
        case DiagnosticLevel::Help:
            return "help";
        }
        return "unknown";
    }

    std::string DiagnosticFormatter::applyColor(const std::string &text, DiagnosticLevel level) const
    {
        if (!config.useColor)
            return text;

        const char *red = "\033[31m";
        const char *yellow = "\033[33m";
        const char *blue = "\033[34m";
        const char *green = "\033[32m";
        const char *reset = "\033[0m";

        switch (level)
        {
        case DiagnosticLevel::Error:
            return red + text + reset;
        case DiagnosticLevel::Warning:
            return yellow + text + reset;
        case DiagnosticLevel::Note:
            return blue + text + reset;
        case DiagnosticLevel::Help:
            return green + text + reset;
        }
        return text;
    }

    std::string DiagnosticFormatter::renderHumanReadable(const Diagnostic &diag) const
    {
        std::ostringstream out;

        auto prefix = getLevelPrefix(diag.level);
        auto levelStr = applyColor(prefix + "[" + diag.code + "]", diag.level);
        out << levelStr << ": " << diag.message << "\n";

        for (const auto &label : diag.labels)
        {
            out << "  --> " << label.span.toString() << "\n";

            if (sourceProvider && config.showSourceLine)
            {
                auto src = sourceProvider(label.span.fileName);
                if (src)
                {
                    std::istringstream iss(*src);
                    std::string line;
                    size_t lineNum = 0;
                    while (std::getline(iss, line))
                    {
                        ++lineNum;
                        if (lineNum == label.span.start.line)
                        {
                            out << "   |\n";
                            out << std::setw(3) << lineNum << " | " << line << "\n";
                            out << "   | " << underlineSpan(label.span, line, label.message, label.isPrimary) << "\n";
                            break;
                        }
                    }
                }
            }
        }

        for (const auto &note : diag.notes)
            out << "  = note: " << note << "\n";

        if (config.emitFixSuggestions && !diag.fixIts.empty())
        {
            for (const auto &fix : diag.fixIts)
            {
                out << "  = fix: replace with `" << fix.replacementText << "`\n";
                if (fix.note)
                    out << "    - note: " << *fix.note << "\n";
            }
        }

        if (config.showHelpLinks && diag.helpLink)
            out << "  = help: see " << *diag.helpLink << "\n";

        return out.str();
    }

    std::string DiagnosticFormatter::renderPlainText(const Diagnostic &diag) const
    {
        std::ostringstream out;
        out << getLevelPrefix(diag.level) << "[" << diag.code << "]: " << diag.message << "\n";

        for (const auto &label : diag.labels)
        {
            out << " -> " << label.span.toString() << ": " << label.message << "\n";
        }

        for (const auto &note : diag.notes)
            out << " = note: " << note << "\n";

        if (diag.helpLink)
            out << " = help: " << *diag.helpLink << "\n";

        return out.str();
    }

    std::string DiagnosticFormatter::underlineSpan(const Span &span, const std::string &line, const std::string &message, bool isPrimary) const
    {
        std::string underline;
        for (size_t i = 1; i < span.start.column; ++i)
            underline += " ";
        size_t len = span.end.column > span.start.column ? span.end.column - span.start.column : 1;
        underline += std::string(len, isPrimary ? '^' : '-');
        underline += " " + message;
        return underline;
    }
} // namespace Tarn
