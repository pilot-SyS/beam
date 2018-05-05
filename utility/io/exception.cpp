#include "exception.h"
#include <stdio.h>

namespace beam { namespace io {

const char* error_str(ErrorCode errorCode) {
    switch (errorCode) {
        case EC_OK: return "0";
        case EC_WRITE_BUFFER_OVERFLOW: return "EC_WRITE_BUFFER_OVERFLOW";
#define XX(code, _) case EC_ ## code: return "EC_" # code;
    UV_ERRNO_MAP(XX)
#undef XX
        default: return "UNKNOWN";
    }
}

const char* error_descr(beam::io::ErrorCode errorCode) {
    switch (errorCode) {
        case EC_OK: return "OK";
        case EC_WRITE_BUFFER_OVERFLOW: return "stream write buffer overflow";
#define XX(code, descr) case EC_ ## code: return descr;
    UV_ERRNO_MAP(XX)
#undef XX
        default: return "unknown io error";
    }
}

std::string format_io_error(const char* _function, const char* _file, int _line, ErrorCode _code) {
    char buf[4096];
#ifdef SHOW_CODE_LOCATION
    snprintf(buf, 4096, "io::Exception from %s (%s:%d): code=%d (%s : %s)", _function, _file, _line, _code, error_str(_code), error_descr(_code));
#else
    snprintf(buf, 4096, "io::Exception: code=%d (%s : %s)", _code, error_str(_code), error_descr(_code));
#endif
    return std::string(buf);
}

}} //namespaces