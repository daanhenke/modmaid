#include <modmaid.hh>

namespace modmaid
{
  void Initialize()
  {
    logging::Initialize();
    hooks::Initialize();
  }

  void Exit()
  {
    hooks::Exit();
    logging::Exit();
  }
}
