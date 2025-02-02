/*##########################################################################################

	PAX SAPIENTICA Library 💀🌿🌏

	[Planning]		2023 As Project
	[Production]	2023 As Project
	[Contact Us]	wanotaitei@gmail.com			https://github.com/AsPJT/PAX_SAPIENTICA
	[License]		Distributed under the CC0 1.0.	https://creativecommons.org/publicdomain/zero/1.0/

##########################################################################################*/

#ifndef PAX_SAPIENTICA_TYPE_VECTOR2_HPP
#define PAX_SAPIENTICA_TYPE_VECTOR2_HPP

/*##########################################################################################

##########################################################################################*/

#include <cmath>
#include <iostream>

namespace paxs {
    
    /// @brief 2D Vector class.
    template<typename T>
    class Vector2 {
    public:
        constexpr explicit Vector2() noexcept = default;
        constexpr explicit Vector2(T x, T y) noexcept : x(x), y(y) {}

        T x;
        T y;

        constexpr static Vector2<T> zero() noexcept { return Vector2<T>(0, 0); }

        constexpr Vector2<T> operator-() const noexcept {
            return Vector2<T>(-x, -y);
        }

        constexpr Vector2<T> operator+(const Vector2<T>& v) const noexcept {
            return Vector2<T>(x + v.x, y + v.y);
        }
        constexpr Vector2<T>& operator+=(const Vector2<T>& v) noexcept {
            x += v.x;
            y += v.y;
            return *this;
        }
        constexpr Vector2<T> operator-(const Vector2<T>& v) const noexcept {
            return Vector2<T>(x - v.x, y - v.y);
        }
        constexpr Vector2<T>& operator-=(const Vector2<T>& v) noexcept {
            x -= v.x;
            y -= v.y;
            return *this;
        }
        constexpr Vector2<T> operator*(const Vector2<T>& v) const noexcept {
            return Vector2<T>(x * v.x, y * v.y);
        }
        constexpr Vector2<T> operator*(const int& t) const noexcept {
            return Vector2<T>(x * t, y * t);
        }
        constexpr Vector2<T>& operator*=(const int& t) noexcept {
            x *= t;
            y *= t;
            return *this;
        }
        constexpr Vector2<T> operator*(const double& t) const noexcept {
            return Vector2<T>(x * T(t), y * T(t));
        }
        constexpr Vector2<T>& operator*=(const double& t) noexcept {
            x *= t;
            y *= t;
            return *this;
        }
        constexpr Vector2<T> operator/(const Vector2<T>& v) const noexcept {
            return Vector2<T>(x / v.x, y / v.y);
        }
        constexpr Vector2<T> operator/(const int& t) const noexcept {
            return Vector2<T>(x / t, y / t);
        }
        constexpr Vector2<T>& operator/=(const int& t) noexcept {
            x /= t;
            y /= t;
            return *this;
        }
        constexpr Vector2<T> operator/(const double& t) const noexcept {
            return Vector2<T>(x / t, y / t);
        }
        constexpr Vector2<T>& operator/=(const double& t) noexcept {
            x /= t;
            y /= t;
            return *this;
        }
        constexpr bool operator==(const Vector2<T>& v) const noexcept {
            return v.x == x && v.y == y;
        }
        constexpr bool operator!=(const Vector2<T>& v) const noexcept {
            return v.x != x || v.y != y;
        }
        constexpr bool operator<(const Vector2<T>& v) const noexcept {
            if (x == v.x) {
                return y < v.y;
            }
            return x < v.x;
        }
        constexpr bool operator>(const Vector2<T>& v) const noexcept {
            if (x == v.x) {
                return y > v.y;
            }
            return x > v.x;
        }
        constexpr bool operator<=(const Vector2<T>& v) const noexcept {
            if (x == v.x) {
                return y <= v.y;
            }
            return x <= v.x;
        }
        constexpr bool operator>=(const Vector2<T>& v) const noexcept {
            if (x == v.x) {
                return y >= v.y;
            }
            return x >= v.x;
        }

        /// @brief Get the length of the vector
        /// @brief べクトルの長さを取得。
        double length() const noexcept {
            return std::sqrt(x * x + y * y);
        }

        /// @brief  Get the distance between two vectors
        /// @brief  二つのベクトルの距離を取得。
        double distance(const Vector2<T>& v) const noexcept {
            return std::sqrt((x - v.x) * (x - v.x) + (y - v.y) * (y - v.y));
        }
        friend std::ostream& operator<<(std::ostream& os, const Vector2<T>& v) noexcept {
            os << "(" << v.x << ", " << v.y << ")";
            return os;
        }
    };
}

#endif // !PAX_SAPIENTICA_TYPE_VECTOR2_HPP