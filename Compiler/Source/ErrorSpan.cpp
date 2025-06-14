#include "../Resources/ErrorSpan.hpp";
#include <sstream>

namespace Tarn
{
    bool Span::contains(const Position &pos) const
    {
        return (start < pos || start == pos) && (pos < end);
    }

    bool Span::overlaps(const Span &other) const
    {
        return !(other.end < start || end < other.start);
    }

    Span Span::mergeWith(const Span &other) const
    {
        Position newStart = (start < other.start) ? start : other.start;
        Position newEnd = (end < other.end) ? other.end : end;
        return {fileName, newStart, newEnd};
    }

    std::string Span::toString() const
    {
        std::ostringstream oss;
        oss << fileName << ":" << start.line << ":" << start.column;
        return oss.str();
    }
} // namespace Tarn
