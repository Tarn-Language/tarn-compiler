#pragma once

#include <string>
#include <optional>
#include <tuple>

namespace Tarn
{
    struct Position
    {
        size_t line;
        size_t column;

        bool operator==(const Position &other) const
        {
            return line == other.line && column == other.column;
        }

        bool operator<(const Position &other) const
        {
            return std::tie(line, column) < std::tie(other.line, other.column);
        }
    };

    struct Span
    {
        std::string fileName;
        Position start;
        Position end;

        bool contains(const Position &pos) const;
        bool overlaps(const Span &other) const;
        Span mergeWith(const Span &other) const;

        std::string toString() const;
    };
} // namespace Tarn
