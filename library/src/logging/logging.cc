#include <maid/logging.hh>

#include <cstdarg>
#include <cstdio>

#define generate_logger_impl(level) \
  generate_logger_prototype(level) \
  { \
    va_list args; \
    \
    va_start(args, format); \
    auto bufferSize = std::vsnprintf(nullptr, 0, format, args) + 1; \
    va_end(args); \
    \
    auto buffer = new char[bufferSize]; \
    \
    va_start(args, format); \
    std::vsnprintf(buffer, bufferSize, format, args); \
    va_end(args); \
    \
    LogRaw(LogLevel::level, buffer); \
    \
    delete[] buffer; \
  }


namespace modmaid::logging
{
  const char* LevelPrefix(LogLevel level)
  {
    switch (level)
    {
    case LogLevel::Panic: return "PANIC";
    case LogLevel::Critical: return " CRIT";
    case LogLevel::Error: return "ERROR";
    case LogLevel::Warning: return " WARN";
    case LogLevel::Message: return " MESG";
    case LogLevel::Debug: return "DEBUG";
    case LogLevel::Trace: return "TRACE";
    default: return "UNKWN";
    }
  }

  void LogRaw(LogLevel level, const char* message)
  {
    std::printf("[%s]: %s\n", LevelPrefix(level), message);
  }

  void LogFormat(LogLevel level, const char* format, ...)
  {
    va_list args;

    va_start(args, format);
    auto bufferSize = std::vsnprintf(nullptr, 0, format, args) + 1;
    va_end(args);

    auto buffer = new char[bufferSize];

    va_start(args, format);
    std::vsnprintf(buffer, bufferSize, format, args);
    va_end(args);

    LogRaw(level, buffer);

    delete[] buffer;
  }

  generate_logger_impl(Trace);
  generate_logger_impl(Debug);
  generate_logger_impl(Message);
  generate_logger_impl(Warning);
  generate_logger_impl(Error);
  generate_logger_impl(Critical);
  generate_logger_impl(Panic);
}
