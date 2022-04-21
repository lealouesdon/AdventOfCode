#include <string>
#include <ratio>
#include <ostream>
#include <iostream>
#include <algorithm>

// Length is in cm
template <class Period = std::ratio<1>>
class Length
{

public:
    Length() : value(0) {}
    explicit Length(long double v) : value(v) {}

    template <typename R>
    Length<Period>& operator=(const Length<R>& l)
    {
        value = l.value * R::num;
        return *this;
    }

    template <typename R>
    Length<Period>& operator+=(const Length<R>& l)
    {
        value += l.value * R::num;
        return *this;
    }

    long double value;
};

auto operator""_cm(long double n)
{
    return Length<>(n);
}

auto operator""_m(long double n)
{
    return Length<std::hecto>(n);
}

template <typename Period>
std::ostream &operator<<(std::ostream &os, const Length<Period> &l)
{
    long double val = l.value * Period::num;
    if (val < 100) {
        os << val << " cm";
    } else if (val < 100000) {
        os << val / 100 << " m";
    } else {
        os << std::fixed << val / 100000 << " km";
    }
    return os;
}

template <typename Period>
std::istream &operator>>(std::istream &is, Length<Period> &l)
{
    int val;
    is >> val;
    l.value = val * Period::num;
    return is;
}

template <class R = std::ratio<1>>
struct Present
{
    struct Length<R> length;
    struct Length<R> width;
    struct Length<R> height;

    Present() {}
    Present(Length<R> l, Length<R> w, Length<R> h) : length(l), width(w), height(h){ }

    Length<R> wrapping_paper_calculator()
    {
        auto length_surface = length.value * width.value;
        auto height_surface = width.value * height.value;
        auto width_surface = height.value * length.value;

        return Length<R>(2 * length_surface + 2 * height_surface + 2 * width_surface + std::min({length_surface, height_surface, width_surface}));
    }
};

template <typename R>
std::ostream &operator<<(std::ostream &os, const Present<R> &p)
{
    os << "Present(" << p.height << " x " << p.width << " x " << p.length << ")";
    return os;
}
