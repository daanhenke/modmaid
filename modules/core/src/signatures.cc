#include <modmaid/core/signatures.hh>
#include <modmaid/core/memory.hh>

namespace modmaid::signature
{
    class ParsedSignature
    {
    public:
        explicit ParsedSignature(const char* pattern)
        {
            Source = TrimPattern(pattern);
            Size = Source.length() / 2;

            Bytes = new unsigned char[Size];
            Masks = new bool[Size];

            auto index = 0;
            auto it = Source.begin();
            while (it != Source.end())
            {
                // Supports both ? and ?? for masked bytes, but current implementation parses "? ?" as a single ??
                if (*it == '?')
                {
                    ++it;
                    if (*it == '?')
                    {
                        ++it;
                    }

                    Bytes[index] = 0;
                    Masks[index++] = true;
                }
                else if (IsHexNibble(*it))
                {
                    const auto topNibble = ParseHexNibble(*it);
                    ++it;
                    const auto bottomNibble = ParseHexNibble(*it);
                    ++it;

                    Bytes[index] = (topNibble << 4) | bottomNibble;
                    Masks[index++] = false;
                }
                else
                {
                    // TODO: PANIC
                    ++it;
                }
            }
        }

        ~ParsedSignature()
        {
            delete[] Bytes;
            delete[] Masks;
        }

        unsigned char* Bytes;
        bool* Masks;

        std::string Source;
        std::size_t Size;

    private:
        static std::string TrimPattern(const char* pattern)
        {
            auto result = std::string(pattern);
            std::erase_if(result, std::isspace);
            return result;
        }

        static unsigned char ParseHexNibble(char chr)
        {
            if (chr >= '0' && chr <= '9') return chr - '0';
            if (chr >= 'A' && chr <= 'F') return chr - 'A' + 10;
            if (chr >= 'a' && chr <= 'f') return chr - 'a' + 10;
            return 0;
        }

        static bool IsHexNibble(char chr)
        {
            if (chr >= '0' && chr <= '9') return true;
            if (chr >= 'A' && chr <= 'F') return true;
            if (chr >= 'a' && chr <= 'f') return true;
            return false;
        }
    };

    void* FindInRange(void* base, std::size_t size, const char* pattern)
    {
        auto parsed = ParsedSignature(pattern);

        auto charBase = reinterpret_cast<unsigned char*>(base);
        for (auto curr = charBase; curr < charBase + (size - parsed.Size); curr++)
        {
            auto matches = true;
            for (auto sigIndex = 0; sigIndex < parsed.Size; sigIndex++)
            {
                if (parsed.Masks[sigIndex])
                {
                    continue;
                }

                if (parsed.Bytes[sigIndex] == curr[sigIndex])
                {
                    continue;
                }

                matches = false;
                break;
            }

            if (matches)
            {
                return curr;
            }
        }

        return nullptr;
    }

    void* FindInModule(const char* moduleName, const char* pattern)
    {
        auto base = memory::GetExecutableBase(moduleName);
        auto size = memory::GetExecutableSize(base);
        return FindInRange(
            base,
            size,
            pattern
        );
    }
}