#pragma once

#include "./ErrorTypes.hpp"
#include "./ErrorRegistry.hpp"
#include "./ErrorBuilder.hpp"
#include "./ErrorEmitter.hpp"
#include "./ErrorSpan.hpp"

namespace Tarn::ErrorLogic
{
    extern ErrorEmitter *GlobalEmitter;

    void reportTypeMismatch(
        const Span &span,
        const std::string &expectedType,
        const std::string &foundType);

    void reportUndeclaredVariable(
        const Span &span,
        const std::string &variableName);
    void reportMissingSemicolon(
        const Span &span);

    void reportInternalCompilerError(
        const Span &span,
        const std::string &context);

    void reportUnusedVariable(
        const Span &span,
        const std::string &name);
} // namespace Tarn::ErrorLogic
