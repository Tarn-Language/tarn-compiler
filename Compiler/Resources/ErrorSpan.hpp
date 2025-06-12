#pragma once

#include <string>

namespace Tarn
{
    struct ErrorSpan
    {
        std::string file;

        int startLine;
        int startColumn;
        int endLine;
        int endColumn;

        ErrorSpan(
            const std::string &file,

            int startLine,
            int startColumn,
            int endLine,
            int endColumn)
            : file(file),
              startLine(startLine),
              startColumn(startColumn),
              endLine(endLine),
              endColumn(endColumn)
        {
        }

        bool isSingleLine() const
        {
            return startLine == endLine;
        }

        std::string toString() const
        {
            return file + ":" + std::to_string(startLine) + ":" + std::to_string(startColumn);
        }
    };
} // namespace Tarn
