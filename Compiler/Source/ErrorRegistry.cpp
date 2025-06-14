#include "../Resources/ErrorRegistry.hpp"

namespace Tarn::Errors
{
    std::string getHelpLinkFor(const std::string &code)
    {
        return "https://tarn-language.com/errors" + code;
    }
} // namespace Tarn::Errors
