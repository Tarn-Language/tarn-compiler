#pragma once

#include "./ErrorTypes.hpp"
#include "./ErrorOutputFormat.hpp"
#include "./ErrorFormatter.hpp"

#include <vector>
#include <functional>
#include <unordered_set>
#include <ostream>

namespace Tarn
{
    class ErrorEmitter
    {
    public:
        ErrorEmitter(OutputConfig config = {});

        void emit(const Diagnostic &diag);
        void setSourceProvider(std::function<std::optional<std::string>(const std::string &)> provider);

        size_t errorCount() const;
        size_t warningCount() const;

        void clear();

    private:
        OutputConfig config;
        DiagnosticFormatter formatter;
        std::function<std::optional<std::string>(const std::string &)> sourceProvider;

        std::ostream *outputStream;
        std::unordered_set<std::string> emittedHashSet;

        size_t errors = 0;
        size_t warnings = 0;

        std::string hashDiagnostic(const Diagnostic &diag) const;
        void writeOutput(const std::string &rendered);
    };
} // namespace Tarn
