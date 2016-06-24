#ifndef SOFTC_STRING_PRIVATE_H_CPP
#define SOFTC_STRING_PRIVATE_H_CPP

struct _softc_string_s
{
  _softc_string_s(){}
  explicit _softc_string_s(const char *str)
    :str(str)
  {}
  explicit _softc_string_s(_softc_string_s &&other) noexcept
    :str(std::move(other.str))
  {}
  _softc_string_s& operator=(_softc_string_s &&other)
  {
    str = std::move(other.str);
    return *this;
  }
  std::string str;
};

#endif
