#include <vector>
#include "Flags.h"
#include "Enums.h"

namespace vg
{
    /// @brief Get components of the format
    /// @param format Format
    /// @return Flag set of components present in format
    Flags<FormatComponent> GetComponents(Format format);

    /// @brief Get resolutions of all components
    /// @param format Format
    /// @return Array of bit resolutions, in order of format components, if component is compressed then corresponding resolution is -1
    std::vector<int> GetFormatComponentsResolutions(Format format);

    /// @brief Get bit resolution of specified component
    /// @param format Format
    /// @param component Component
    /// @return Bit resolution of corresponding format, or 0 if component is not present
    int GetFormatComponentResolutions(Format format, FormatComponent component);

    /// @brief Get total format bit resolution
    /// @param format Format
    /// @return Total format bit resolution, or -1 if any component are compressed
    int GetFormatResolutions(Format format);

    bool IsFormatUnsigned(Format format);

    bool IsFormatIntegral(Format format);
}