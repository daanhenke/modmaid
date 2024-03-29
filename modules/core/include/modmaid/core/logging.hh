#pragma once

#define generate_logger_prototype(level) \
  void level(const char* format, ...)

namespace modmaid::log
{
  void Initialize();
  void Exit();

#ifdef OS_WINDOWS
  void InitializeWindowsConsoleHost();
  void ExitWindowsConsoleHost();
#endif

  enum class LogLevel
  {
    Trace,
    Debug,
    Message,
    Warning,
    Error,
    Critical,
    Panic
  };

  void Raw(LogLevel, const char* message);
  void Format(LogLevel, const char* format, ...);

  generate_logger_prototype(Trace);
  generate_logger_prototype(Debug);
  generate_logger_prototype(Message);
  generate_logger_prototype(Warning);
  generate_logger_prototype(Error);
  generate_logger_prototype(Critical);
  generate_logger_prototype(Panic);
}

