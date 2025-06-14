#include "../Resources/ErrorEmitter.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <functional>

namespace Tarn
{
    ErrorEmitter::ErrorEmitter(OutputConfig config)
        : config(std::move(config)),
          formatter(this->config),
          outputStream(&std::cout) // default
    {
    }

    void ErrorEmitter::setSourceProvider(std::function<std::optional<std::string>(const std::string &)> provider)
    {
        sourceProvider = std::move(provider);
        formatter.setSourceProvider(sourceProvider);
    }

    void ErrorEmitter::emit(const Diagnostic &diag)
    {
        std::string hash = hashDiagnostic(diag);
        if (emittedHashSet.count(hash) > 0)
        {
            return; // Avoid duplicate emissions
        }
        emittedHashSet.insert(hash);

        if (diag.level == DiagnosticLevel::Error)
            ++errors;
        if (diag.level == DiagnosticLevel::Warning)
            ++warnings;

        std::string output = formatter.format(diag);
        writeOutput(output);
    }

    void ErrorEmitter::writeOutput(const std::string &rendered)
    {
        if (!config.outputToFile.empty())
        {
            std::ofstream outFile(config.outputToFile, std::ios::app);
            if (outFile.is_open())
            {
                outFile << rendered << "\n";
                outFile.close();
            }
            else
            {
                std::cerr << "Failed to write diagnostic to: " << config.outputToFile << "\n";
            }
        }
        else
        {
            (*outputStream) << rendered << std::endl;
        }
    }

    size_t ErrorEmitter::errorCount() const
    {
        return errors;
    }

    size_t ErrorEmitter::warningCount() const
    {
        return warnings;
    }

    void ErrorEmitter::clear()
    {
        emittedHashSet.clear();
        errors = 0;
        warnings = 0;
    }

    std::string ErrorEmitter::hashDiagnostic(const Diagnostic &diag) const
    {
        // Basic string hash: code + first span position
        std::ostringstream oss;
        oss << diag.code;
        if (!diag.labels.empty())
        {
            const auto &s = diag.labels.front().span.start;
            oss << s.line << ":" << s.column;
        }
        return oss.str();
    }
} // namespace Tarn
