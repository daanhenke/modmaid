#include <modmaid.hh>

using namespace modmaid;

void LogMemoryHelpers()
{
  // Logging and some memory helpers!
  logging::Trace("Hello %s", "world!");
  logging::Message("IsValidPointer(nullptr) = %d", memory::IsValidPointer(nullptr));
  logging::Message("IsValidPointer(\"hi\") = %d", memory::IsValidPointer("hi"));
  logging::Message("IsValidCodePointer(\"hi\") = %d", memory::IsValidCodePointer("hi"));
  logging::Message("IsValidPointer(&modmaid::Initialize) = %d",
                   memory::IsValidCodePointer(reinterpret_cast<void*>(&Initialize)));
}

void TestReprotect()
{
  // SomeString is in the .rodata section
  const char* SomeString = "Not modified";

  // Reprotect it so it's writeable
  auto oldProtection = memory::ReprotectMemory(SomeString, 12, memory::MemoryProtection::ReadWrite);

  // Overwrite it
  auto mutablePointerIntoConstString = const_cast<char*>(SomeString);
  memory::CopyMemory("VERY", mutablePointerIntoConstString, 4);

  // Restore old protection
  memory::ReprotectMemory(SomeString, 12, oldProtection);

  // Print result
  logging::Message("Modified string: %s", SomeString);
}

namespace VTableStuff
{
  // Interface with pure virtual method
  class IInterface
  {
  public:
    virtual void Test(const char* arg) = 0;
  };

  // Implementation that we will be overriding
  class CImpl : public IInterface
  {
  public:
    void Test(const char* arg) override
    {
      logging::Message("Original implementation: %s", arg);
    }
  };
}

// Test_Original will be used to house a pointer to the original method
void (*Test_Original)(void* thiz, const char* argument);

// Test_Hook is the method that will override the original inside the vtable
void Test_Hook(void* thiz, const char* argument)
{
  logging::Message("Captured argument: %s", argument);
  Test_Original(thiz, "Hey!");
}

void TestVTableHook()
{
  // Create an instance
  VTableStuff::IInterface* iface = new VTableStuff::CImpl();

  // Apply the hook
  auto hook = hooks::RegisterVTableHook(iface, 0, &Test_Original, Test_Hook);

  // Test
  iface->Test("Capturable argument!");
}

size_t (*StringLength_Original)(const char* str) = nullptr;
size_t StringLength_Hook(const char* str)
{
  return StringLength_Original(str) + 25;
}

void TestTrampolineHook()
{
  hooks::RegisterTrampolineHook(strlen, reinterpret_cast<void**>(&StringLength_Original), StringLength_Hook);
  logging::Warning("Calling hooked strlen: %d", strlen("hi"));
}

void OnLoad()
{
  modmaid::Initialize();

  LogMemoryHelpers();
  TestReprotect();
  TestVTableHook();
  TestTrampolineHook();
}

void OnUnload()
{
  modmaid::Exit();
}

modmaid::Entrypoint gEntrypoint(OnLoad, OnUnload);
