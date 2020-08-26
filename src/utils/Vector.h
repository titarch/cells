#ifndef CELLS_VECTOR_H
#define CELLS_VECTOR_H


#include <cmath>
#include <ostream>
#include <array>
#include <execution>
#include "yaml-cpp/yaml.h"

template<typename T, size_t D>
class Vector {
public:
    using Ts = std::array<T, D>;
    using iterator = typename Ts::iterator;
    using const_iterator = typename Ts::const_iterator;

    Vector() : pts_{} {}

    Vector(Ts const& pts) : pts_(pts) {}

    [[nodiscard]] T sqrMagnitude() const {
        return std::inner_product(this->cbegin(), this->cend(), this->cbegin(), 0.0);
    }

    [[nodiscard]] T magnitude() const {
        return std::sqrt(sqrMagnitude());
    }

    [[nodiscard]] Vector normalized() const {
        Vector copy(*this);
        copy /= magnitude();
        return copy;
    }

    void clamp(T min, T max) {
        std::transform(begin(), end(), begin(), [min, max](T v) { return std::clamp(v, min, max); });
    }

    T& operator[](size_t idx) {
        return pts_[idx];
    }

    T operator[](size_t idx) const {
        return pts_[idx];
    }

    T x() const {
        return pts_[0];
    }

    T y() const {
        return pts_[1];
    }

    iterator begin() { return pts_.begin(); }

    iterator end() { return pts_.end(); }

    const_iterator begin() const { return pts_.begin(); }

    const_iterator end() const { return pts_.end(); }

    const_iterator cbegin() const { return pts_.cbegin(); }

    const_iterator cend() const { return pts_.cend(); }

    Vector& operator+=(Vector const& rhs) {
        std::transform(begin(), end(), rhs.cbegin(), begin(), std::plus<T>());
        return *this;
    }

    Vector operator-() const {
        Vector copy;
        std::transform(cbegin(), cend(), copy.begin(), std::negate<T>());
        return copy;
    }

    Vector& operator-=(Vector const& rhs) {
        std::transform(begin(), end(), rhs.cbegin(), begin(), std::minus<T>());
        return *this;
    }

    Vector& operator*=(T k) {
        std::transform(begin(), end(), pts_.begin(), [&k](T const& e) { return e * k; });
        return *this;
    }

    Vector& operator/=(T k) {
        std::transform(pts_.begin(), pts_.end(), pts_.begin(), [&k](T const& e) { return e / k; });
        return *this;
    }

    Vector& operator%=(Vector const& rhs) {
        std::transform(begin(), end(), rhs.cbegin(), begin(), std::multiplies<T>());
        return *this;
    }

    Vector& operator^=(Vector const& rhs) {
        (void) rhs;
        throw "Cross product not implemented for dimension " + std::to_string(D);
        return *this;
    }

    operator sf::Vector2f() const {
        throw "sf::Vector2f conversion not implemented for dim other than 2";
    }

    static Vector fill(T val) {
        Vector v{};
        std::fill(v.begin(), v.end(), val);
        return v;
    }

    static Vector one() {
        return fill(1);
    }

    static Vector random() {
        Vector v{};
        std::generate(v.begin(), v.end(), []() -> T { return (T) std::rand() / (T) RAND_MAX; });
        return v;
    }

    static Vector signed_random() {
        return random() * (T) 2 - one();
    }

    friend std::ostream& operator<<(std::ostream& os, Vector const& v) {
        os << "( ";
        for (const T& e: v)
            os << e << ' ';
        return os << ")";
    }

    friend YAML::Emitter& operator<<(YAML::Emitter& out, Vector const& v) {
        out << YAML::Flow << YAML::BeginSeq;
        for (const T& e: v)
            out << e;
        return out << YAML::EndSeq;
    }

private:
    Ts pts_;
};

template<typename T, size_t D>
inline Vector<T, D> operator+(Vector<T, D> lhs, Vector<T, D> const& rhs) {
    lhs += rhs;
    return lhs;
}

template<typename T, size_t D>
inline Vector<T, D> operator-(Vector<T, D> lhs, Vector<T, D> const& rhs) {
    lhs -= rhs;
    return lhs;
}

template<typename T, size_t D>
inline T operator*(Vector<T, D> const& lhs, Vector<T, D> const& rhs) {
    return std::inner_product(lhs.cbegin(), lhs.cend(), rhs.cbegin(), 0.0);
}

template<typename T, size_t D>
inline Vector<T, D> operator*(Vector<T, D> lhs, T rhs) {
    lhs *= rhs;
    return lhs;
}

template<typename T, size_t D>
inline Vector<T, D> operator*(T lhs, Vector<T, D> rhs) {
    rhs *= lhs;
    return rhs;
}

template<typename T, size_t D>
inline Vector<T, D> operator/(Vector<T, D> lhs, T rhs) {
    lhs /= rhs;
    return lhs;
}

template<typename T, size_t D>
inline Vector<T, D> operator%(Vector<T, D> lhs, Vector<T, D> const& rhs) {
    lhs %= rhs;
    return lhs;
}

template<typename T, size_t D>
inline Vector<T, D> operator^(Vector<T, D> lhs, Vector<T, D> const& rhs) {
    lhs ^= rhs;
    return lhs;
}

using Vec2f = Vector<float, 2>;
using Vec2z = Vector<size_t, 2>;

template<>
inline Vec2f::operator sf::Vector2f() const {
    return {x(), y()};
}

#endif //CELLS_VECTOR_H
