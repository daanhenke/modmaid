#include <maid/init.hh>

#include <maid/logging.hh>
#include <maid/hooks.hh>

namespace modmaid
{
  InitComponent gFlagsForExit;

  void InitializeModMaid(InitComponent flags)
  {
    gFlagsForExit = 0;

    if (flags & init::Logging)
    {
      logging::Initialize();
      gFlagsForExit |= init::Logging;

      if (flags & init::WindowsConsoleHost)
      {
        logging::InitializeWindowsConsoleHost();
        gFlagsForExit |= init::WindowsConsoleHost;
      }
    }

    if (flags & init::Hooks)
    {
      hooks::Initialize();
      gFlagsForExit |= init::Hooks;
    }
  }

  void ExitModMaid()
  {
    if (gFlagsForExit & init::Hooks)
    {
      hooks::Exit();
    }

    if (gFlagsForExit & init::Logging)
    {
      if (gFlagsForExit & init::WindowsConsoleHost)
      {
        logging::ExitWindowsConsoleHost();
      }

      logging::Exit();
    }

    gFlagsForExit = 0;
  }
}
