/*
 * Copyright (C) Cross The Road Electronics.  All rights reserved.
 * License information can be found in CTRE_LICENSE.txt
 * For support and suggestions contact support@ctr-electronics.com or file
 * an issue tracker at https://github.com/CrossTheRoadElec/Phoenix-Releases
 */
#pragma once

#include <units/angle.h>

#include <algorithm>
#include <optional>
#include <sstream>
#include <stdint.h>

#if __has_include(<frc/util/Color8Bit.h>)
#include <frc/util/Color8Bit.h>
#endif

namespace ctre {
namespace phoenix6 {
namespace signals {

/**
 * Represents an RGBW color that can be applied to an LED.
 */
class RGBWColor {
public:
    /**
     * \brief The red component of the color, within [0, 255].
     */
    uint8_t Red{};
    /**
     * \brief The green component of the color, within [0, 255].
     */
    uint8_t Green{};
    /**
     * \brief The blue component of the color, within [0, 255].
     */
    uint8_t Blue{};
    /**
     * \brief The white component of the color, within [0, 255].
     * Note that not all LED strips support the white component.
     */
    uint8_t White{};

    /**
     * \brief Creates a new RGBW color where all components are off.
     */
    constexpr RGBWColor() = default;

    /**
     * \brief Creates a new RGBW color from the given 8-bit components.
     *
     * \param red The red component of the color, within [0, 255].
     * \param green The green component of the color, within [0, 255].
     * \param blue The blue component of the color, within [0, 255].
     * \param white The white component of the color, within [0, 255].
     *              Note that not all LED strips support the white component.
     */
    constexpr RGBWColor(uint8_t red, uint8_t green, uint8_t blue, uint8_t white = 0) :
        Red{red},
        Green{green},
        Blue{blue},
        White{white}
    {}

#if __has_include(<frc/util/Color8Bit.h>)
    /**
     * \brief Creates a new RGBW color from a WPILib color.
     * The white component will be left 0.
     *
     * \param color The WPILib color
     */
    constexpr RGBWColor(frc::Color8Bit const &color) :
        Red{(uint8_t)color.red},
        Green{(uint8_t)color.green},
        Blue{(uint8_t)color.blue},
        White{0}
    {}

    constexpr operator frc::Color8Bit() const
    {
        return frc::Color8Bit{Red, Green, Blue};
    }
    constexpr operator frc::Color() const
    {
        return frc::Color8Bit{*this};
    }
#endif

    /**
     * \brief Creates a new RGBW color from the given hex string.
     *
     * \param hex The color hex in the form "#RRGGBBWW" or "#RRGGBB".
     * \returns The color if the hex is valid, otherwise std::nullopt
     */
    static constexpr std::optional<RGBWColor> FromHex(std::string_view hex)
    {
        /* hex string is either 7 (RGB) or 9 (RGBW) characters and starts with # */
        if ((hex.size() != 7 && hex.size() != 9) || hex[0] != '#') {
            return std::nullopt;
        }

        /* {r, g, b, w} */
        uint8_t colors[4]{};
        for (size_t i = 1; i < hex.size(); i += 2) {
            int8_t const upper = HexToNibble(hex[i]);
            int8_t const lower = HexToNibble(hex[i + 1]);
            if (upper < 0 || lower < 0) {
                return std::nullopt;
            }
            colors[(i - 1) / 2] = (upper << 4) | lower;
        }

        return RGBWColor{colors[0], colors[1], colors[2], colors[3]};
    }

    /**
     * \brief Creates a new RGBW color from the given HSV color.
     *
     * \param h The hue as an angle from [0, 360) deg, where 0 is red.
     * \param s The saturation as a scalar from [0, 1].
     * \param v The value as a scalar from [0, 1].
     * \returns The corresponding RGB color; the white component will be 0.
     */
    static constexpr RGBWColor FromHSV(units::degree_t h, double s, double v)
    {
        /* wrap h to [0, 360) and clamp s and v */
        if (h < 0_deg || h >= 360_deg) {
            h += ((h < 0_deg) - (int)units::turn_t{h}.value()) * 1_tr;
        }
        s = std::clamp(s, 0.0, 1.0);
        v = std::clamp(v, 0.0, 1.0);

        /* range between highest and lowest RGB components */
        double const chroma = s * v;
        /* 6 regions of hue */
        double const hue_region = h / 60_deg;

        /* the highest RGB component */
        double const maxf = v;
        /* the lowest RGB component */
        double const minf = maxf - chroma;

        /* offset from max/min for the middle RGB component */
        double const Xoffset = chroma * (hue_region - (int)hue_region);
        /* the middle RGB component; even regions from min, odd from max */
        double const Xf = ((int)hue_region & 1)
            ? maxf - Xoffset
            : minf + Xoffset;

        /* all scalars within [0, 1], scale to [0, 255] */
        uint8_t const max = (uint8_t)(maxf * 255 + 0.5);
        uint8_t const min = (uint8_t)(minf * 255 + 0.5);
        uint8_t const X = (uint8_t)(Xf * 255 + 0.5);

        switch ((int)hue_region) {
            default:
            case 0:
                return RGBWColor{max, X, min};
            case 1:
                return RGBWColor{X, max, min};
            case 2:
                return RGBWColor{min, max, X};
            case 3:
                return RGBWColor{min, X, max};
            case 4:
                return RGBWColor{X, min, max};
            case 5:
                return RGBWColor{max, min, X};
        }
    }

    /**
     * \brief Scales down the components of this color
     * by the given brightness.
     *
     * \param brightness The scalar to apply from [0, 1].
     * \returns New color scaled by the given brightness
     */
    constexpr RGBWColor operator*(double brightness) const
    {
        brightness = std::clamp(brightness, 0.0, 1.0);
        return RGBWColor{
            (uint8_t)(0.5 + Red * brightness),
            (uint8_t)(0.5 + Green * brightness),
            (uint8_t)(0.5 + Blue * brightness),
            (uint8_t)(0.5 + White * brightness)
        };
    }

    constexpr bool operator==(RGBWColor const &other) const
    {
        return Red == other.Red &&
            Green == other.Green &&
            Blue == other.Blue &&
            White == other.White;
    }
    constexpr bool operator!=(RGBWColor const &other) const
    {
        return !(*this == other);
    }

    friend std::ostream &operator<<(std::ostream &os, const RGBWColor &color)
    {
        os << "RGBW(" << (int)color.Red << ", " << (int)color.Green << ", " << (int)color.Blue << ", " << (int)color.White << ")";
        return os;
    }
    /**
     * \brief Returns this RGBW color as a string.
     * \returns A string in the format "RGBW(Red, Green, Blue, White)"
     */
    std::string ToString() const
    {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    /**
     * \brief Returns this RGBW color as a hex string.
     * \returns A hex string in the format "#RRGGBBWW"
     */
    std::string HexString() const
    {
        std::string hex = "#00000000";
        hex[1] = NibbleToHex((Red >> 4) & 0xF);
        hex[2] = NibbleToHex(Red & 0xF);
        hex[3] = NibbleToHex((Green >> 4) & 0xF);
        hex[4] = NibbleToHex(Green & 0xF);
        hex[5] = NibbleToHex((Blue >> 4) & 0xF);
        hex[6] = NibbleToHex(Blue & 0xF);
        hex[7] = NibbleToHex((White >> 4) & 0xF);
        hex[8] = NibbleToHex(White & 0xF);
        return hex;
    }

private:
    static constexpr int8_t HexToNibble(char hex)
    {
        if ('A' <= hex && hex <= 'F') {
            return hex - 'A' + 10;
        } else if ('a' <= hex && hex <= 'f') {
            return hex - 'a' + 10;
        } else if ('0' <= hex && hex <= '9') {
            return hex - '0';
        } else {
            /* invalid */
            return -1;
        }
    }
    static constexpr char NibbleToHex(uint8_t nibble)
    {
        if (nibble < 10) {
            return nibble + '0';
        } else {
            return nibble - 10 + 'A';
        }
    }
};

}
}
}
