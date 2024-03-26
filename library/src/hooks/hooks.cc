#include <maid/hooks.hh>
#include <maid/logging.hh>

#include <map>

namespace modmaid::hooks
{
  using HookDescriptor = struct
  {
  };

  std::map<Hook_t, HookDescriptor> GetMap()
  {
    static std::map<Hook_t, HookDescriptor> map;
    return map;
  }

  void Exit()
  {
    for (auto& hook : GetMap())
    {
      logging::Trace("Hook removed!");
    }
  }
}
