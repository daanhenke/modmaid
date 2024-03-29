#pragma once

#include <cstdint>
#include <cstdlib>

#define maid_ptr_from_offset(type, base, offset) \
  reinterpret_cast<type*>( \
    reinterpret_cast<std::uintptr_t>(base) + offset \
  )

#define maid_define_property_getter(type, name, index) \
  inline type Get ## name() \
  { \
    return *maid_ptr_from_offset(type, this, index); \
  }

#define maid_define_property_setter(type, name, index) \
  inline void Set ## name(type value) \
  { \
    *maid_ptr_from_offset(type, this, index) = value; \
  }

#define maid_define_property_getter_and_setter(type, name, index) \
  maid_define_property_getter(type, name, index); \
  maid_define_property_setter(type, name, index);

#define maid_define_property_pointer(type, name, index) \
  inline type* name ## Ptr() \
  { \
    return maid_ptr_from_offset(type, this, offset) \
  }

#define maid_define_virtual_method(returnType, name, index, prototype_args, ...) \
  inline returnType name prototype_args \
  { \
    return GetVirtualMethod<decltype(this), returnType>(this, index, __VA_ARGS__); \
  }

template <typename TThisType, typename TReturnType, typename... TArgs>
using TVirtualMethod = TReturnType(*)(TThisType this_, TArgs...);

template <typename TThisType, typename TReturnType, typename... TArgs>
inline TReturnType GetVirtualMethod(TThisType this_, std::size_t index, TArgs... args)
{
  auto vtable = *reinterpret_cast<void***>(this_);
  auto method = reinterpret_cast<TVirtualMethod<TThisType, TReturnType, TArgs...>>(
    vtable[index]
  );

  return method(this_, args...);
}
