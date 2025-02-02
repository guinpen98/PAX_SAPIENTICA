﻿/*##########################################################################################

	PAX SAPIENTICA Library 💀🌿🌏

	[Planning]		2023 As Project
	[Production]	2023 As Project
	[Contact Us]	wanotaitei@gmail.com			https://github.com/AsPJT/PAX_SAPIENTICA
	[License]		Distributed under the CC0 1.0.	https://creativecommons.org/publicdomain/zero/1.0/

##########################################################################################*/

#ifndef PAX_SAPIENTICA_SIMULATION_OBJECT_HPP
#define PAX_SAPIENTICA_SIMULATION_OBJECT_HPP

/*##########################################################################################

##########################################################################################*/

#include <PAX_SAPIENTICA/Type/Vector2.hpp>
#include <PAX_SAPIENTICA/Simulation/ConvertToMercatorCoordinate.hpp>

namespace paxs {

    /// @brief Class that represents an object.
    /// @brief オブジェクトを表すクラス
    /// @tparam T Type of the object's position. 座標の型
    template <typename T>
    class Object {
    public:
        using Vector2 = paxs::Vector2<T>;

        constexpr explicit Object(const std::string& id, const std::string& name, const Vector2& position) noexcept : id(id), name(name), position(position) {}

        /// @brief Get the object's id. オブジェクトのIDを取得
        std::string getId() const noexcept { return id; }

        /// @brief Get the coordinate x. オブジェクトの座標xを取得
        constexpr T getX() const noexcept { return position.x; }

        /// @brief Get the coordinate y. オブジェクトの座標yを取得
        constexpr T getY() const noexcept { return position.y; }

        /// @brief Get the coordinate. オブジェクトの座標を取得
        constexpr Vector2 getPosition() const noexcept { return position; }

        /// @brief Set the coordinate x. オブジェクトの座標xをセット
        constexpr void setX(const T& x) noexcept { position.x = x; }

        /// @brief Set the coordinate y. オブジェクトの座標yをセット
        constexpr void setY(const T& y) noexcept { position.y = y; }

        /// @brief Set the coordinate. オブジェクトの座標をセット
        constexpr void setPosition(const Vector2& pos) noexcept { position = pos; }

        /// @brief Get the mercator coordinate from the XYZTile coordinate.
        /// @brief 座標をメルカトル座標で取得
        constexpr paxs::Vector2<double> getLocation(const paxs::Vector2<int>& start_position, const int z) const noexcept {
            return convertToMercatorCoordinate(start_position, position, z);
        }

        constexpr bool operator==(const paxs::Object<T>& a) const noexcept {
            return a.position == position && a.id == id && a.name == name;
        }

    protected:
        std::string id; // オブジェクトのID
        std::string name; // オブジェクトの名前
        Vector2 position; // オブジェクトの座標
    };
}

#endif // !PAX_SAPIENTICA_SIMULATION_OBJECT_HPP