#include "Resources/ErrorEmitter.hpp"
#include "Resources/ErrorLogic.hpp"
#include "Resources/ErrorBuilder.hpp"
#include "Resources/ErrorOutputFormat.hpp"
#include "Resources/ErrorRegistry.hpp"
#include "Resources/ErrorSpan.hpp"
#include <fstream>
#include <iostream>
#include <sstream>

using namespace Tarn;

std::optional<std::string> readFile(const std::string &path)
{
    std::ifstream in(path);
    if (!in.is_open())
        return std::nullopt;

    return std::string((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
}

int main()
{
    OutputConfig config;
    config.format = OutputFormat::HumanReadable;
    config.useColor = true;

    ErrorEmitter emitter(config);
    emitter.setSourceProvider([](const std::string &filename) -> std::optional<std::string>
                              {
                                  return readFile("Tests/" + filename); // Assuming test source is in Tests/
                              });
    Tarn::Span span = {
        "test.tarn",
        {3, 10},
        {3, 17}};

    Diagnostic diag = DiagnosticBuilder(
                          Errors::TYPE_MISMATCH,
                          DiagnosticLevel::Error,
                          Errors::DefaultMessages.at(Errors::TYPE_MISMATCH))
                          .primaryLabel(span, "expected `Int`, found `String`")
                          .addNote("Tarn is strictly typed — no implicit conversions allowed")
                          .addFixIt(span, "42", "Replace string literal with integer")
                          .build();

    emitter.emit(diag);

    std::cout << "Emitted errors: " << emitter.errorCount() << std::endl;
    return 0;
}