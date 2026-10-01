#include <string_view>
namespace ErrorOpengl {

// Error Code
enum Error {
  Success = 0,
  windowInitFailed,
  gLoadFailed,
};

constexpr std::string_view toString(ErrorOpengl::Error errorCode)
{
    switch(errorCode)
    {
        case ErrorOpengl::Error::Success: return "Success.";
        case ErrorOpengl::Error::windowInitFailed: return "Window Init Failed.";
        case ErrorOpengl::Error::gLoadFailed: return "Gload Init Failed.";
        default: return "Unknown Error.";
    }
}

}
