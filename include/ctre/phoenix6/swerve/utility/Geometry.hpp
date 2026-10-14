/*
 * Copyright (C) Cross The Road Electronics.  All rights reserved.
 * License information can be found in CTRE_LICENSE.txt
 * For support and suggestions contact support@ctr-electronics.com or file
 * an issue tracker at https://github.com/CrossTheRoadElec/Phoenix-Releases
 */
#pragma once

#include <units/angle.h>
#include <units/length.h>
#include <units/math.h>

namespace ctre {
namespace phoenix6 {
namespace swerve {

/**
 * \brief Linearly interpolates between two values.
 *
 * \param startValue The start value.
 * \param endValue The end value.
 * \param t The fraction for interpolation.
 *
 * \returns The interpolated value.
 */
template <typename T>
static constexpr T Lerp(T const &startValue, T const &endValue, double t)
{
    return startValue + (endValue - startValue) * t;
}

/**
 * \brief A rotation in a 2D coordinate frame represented by a point on the unit circle
 * (cosine and sine).
 *
 * The angle is continuous, that is if a Rotation2d is constructed with 361
 * degrees, it will return 361 degrees. This allows algorithms that wouldn't
 * want to see a discontinuity in the rotations as it sweeps past from 360 to 0
 * on the second time around.
 */
class Rotation2d {
    units::radian_t m_value = 0_rad;
    double m_cos = 1.0;
    double m_sin = 0.0;

public:
    /**
     * \brief Constructs a Rotation2d with a default angle of 0 degrees.
     */
    constexpr Rotation2d() = default;

    /**
     * \brief Constructs a Rotation2d with the given angle.
     *
     * \param value The value of the angle.
     */
#if __cpp_concepts >= 201907L
    Rotation2d(units::angle_unit auto value)
#else
    Rotation2d(units::radian_t value)
#endif
        : m_value{value},
        m_cos{units::math::cos(value)},
        m_sin{units::math::sin(value)}
    {}

    /**
     * \brief Constructs a Rotation2d with the given x and y (cosine and sine)
     * components. The x and y don't have to be normalized.
     *
     * \param x The x component or cosine of the rotation.
     * \param y The y component or sine of the rotation.
     */
    Rotation2d(double x, double y);

    /**
     * \brief Returns the radian value of the rotation.
     *
     * \returns The radian value of the rotation.
     */
    constexpr units::radian_t Radians() const { return m_value; }
    /**
     * \brief Returns the degree value of the rotation.
     *
     * \returns The degree value of the rotation.
     */
    constexpr units::degree_t Degrees() const { return m_value; }
    /**
     * \brief Returns the rotation value of the rotation.
     *
     * \returns The rotation value of the rotation.
     */
    constexpr units::turn_t Rotations() const { return m_value; }

    /**
     * \brief Returns the cosine of the rotation.
     *
     * \returns The cosine of the rotation.
     */
    constexpr double Cos() const { return m_cos; }
    /**
     * \brief Returns the sine of the rotation.
     *
     * \returns The sine of the rotation.
     */
    constexpr double Sin() const { return m_sin; }
    /**
     * \brief Returns the tangent of the rotation.
     *
     * \returns The tangent of the rotation.
     */
    constexpr double Tan() const { return m_sin / m_cos; }

    /**
     * \brief Adds the new rotation to the current rotation using a rotation matrix.
     *
     * <pre>
     * [cos_new]   [other.cos, -other.sin][cos]
     * [sin_new] = [other.sin,  other.cos][sin]
     * value_new = std::atan2(sin_new, cos_new)
     * </pre>
     *
     * \param other The rotation to rotate by.
     *
     * \returns The new rotated Rotation2d.
     */
    Rotation2d RotateBy(Rotation2d const &other) const
    {
        return {
            Cos() * other.Cos() - Sin() * other.Sin(),
            Cos() * other.Sin() + Sin() * other.Cos()
        };
    }

    Rotation2d operator-() const { return Rotation2d{-m_value}; }
    Rotation2d operator+(Rotation2d const &other) const { return RotateBy(other); }
    Rotation2d operator-(Rotation2d const &other) const { return *this + (-other); }
    Rotation2d operator*(double scalar) const { return Rotation2d{m_value * scalar}; }
    Rotation2d operator/(double scalar) const { return *this * (1.0 / scalar); }

    bool operator==(Rotation2d const &other) const
    {
        return hypot(m_cos - other.m_cos, m_sin - other.m_sin) < 1E-9;
    }
};

/**
 * \brief Represents a translation in 2D space.
 * This object can be used to represent a point or a vector.
 *
 * This assumes that you are using conventional mathematical axes.
 * When the robot is at the origin facing in the positive X direction, forward
 * is positive X and left is positive Y.
 */
class Translation2d {
    units::meter_t x = 0_m;
    units::meter_t y = 0_m;

public:
    /**
     * \brief Constructs a Translation2d with X and Y components equal to zero.
     */
    constexpr Translation2d() = default;

    /**
     * \brief Constructs a Translation2d with the X and Y components equal to the
     * provided values.
     *
     * \param x The x component of the translation.
     * \param y The y component of the translation.
     */
    constexpr Translation2d(units::meter_t x, units::meter_t y) :
        x{x}, y{y}
    {}

    /**
     * \brief Constructs a Translation2d with the provided distance and angle. This is
     * essentially converting from polar coordinates to Cartesian coordinates.
     *
     * \param distance The distance from the origin to the end of the translation.
     * \param angle The angle between the x-axis and the translation vector.
     */
    constexpr Translation2d(units::meter_t distance, Rotation2d const &angle) :
        x{distance * angle.Cos()},
        y{distance * angle.Sin()}
    {}

    /**
     * \brief Returns the X component of the translation.
     *
     * \returns The X component of the translation.
     */
    constexpr units::meter_t X() const { return x; }
    /**
     * \brief Returns the Y component of the translation.
     *
     * \returns The Y component of the translation.
     */
    constexpr units::meter_t Y() const { return y; }

    /**
     * \brief Returns the norm, or distance from the origin to the translation.
     *
     * \returns The norm of the translation.
     */
    units::meter_t Norm() const
    {
        return units::math::hypot(x, y);
    }

    /**
     * \brief Returns the angle this translation forms with the positive X axis.
     *
     * \returns The angle of the translation
     */
    Rotation2d Angle() const
    {
        return Rotation2d{x.value(), y.value()};
    }

    units::meter_t Distance(Translation2d const &other) const
    {
        return units::math::hypot(other.x - x, other.y - y);
    }

    /**
     * \brief Applies a rotation to the translation in 2D space.
     *
     * This multiplies the translation vector by a counterclockwise rotation
     * matrix of the given angle.
     *
     * <pre>
     * [x_new]   [other.cos, -other.sin][x]
     * [y_new] = [other.sin,  other.cos][y]
     * </pre>
     *
     * For example, rotating a Translation2d of &lt;2, 0&gt; by 90 degrees will
     * return a Translation2d of &lt;0, 2&gt;.
     *
     * \param other The rotation to rotate the translation by.
     *
     * \returns The new rotated translation.
     */
    constexpr Translation2d RotateBy(Rotation2d const &angle) const
    {
        return {
            x * angle.Cos() - y * angle.Sin(),
            x * angle.Sin() + y * angle.Cos()
        };
    }

    /**
     * \brief Rotates this translation around another translation in 2D space.
     *
     * <pre>
     * [x_new]   [rot.cos, -rot.sin][x - other.x]   [other.x]
     * [y_new] = [rot.sin,  rot.cos][y - other.y] + [other.y]
     * </pre>
     *
     * \param other The other translation to rotate around.
     * \param rot The rotation to rotate the translation by.
     * \returns The new rotated translation.
     */
    constexpr Translation2d RotateAround(Translation2d const &other, Rotation2d const &angle) const
    {
        return {
            (x - other.x) * angle.Cos() - (y - other.y) * angle.Sin() + other.x,
            (x - other.x) * angle.Sin() + (y - other.y) * angle.Cos() + other.y
        };
    }

    constexpr Translation2d operator-() const { return {-x, -y}; }
    constexpr Translation2d operator+(Translation2d const &other) const
    {
        return {x + other.x, y + other.y};
    }
    constexpr Translation2d operator-(Translation2d const &other) const
    {
        return *this + -other;
    }
    constexpr Translation2d operator*(double scalar) const
    {
        return {scalar * x, scalar * y};
    }
    constexpr Translation2d operator/(double scalar) const
    {
        return *this * (1.0 / scalar);
    }

    bool operator==(Translation2d const &other) const
    {
        return units::math::abs(x - other.x) < 1E-9_m &&
               units::math::abs(y - other.y) < 1E-9_m;
    }
};

class Pose2d;

/**
 * \brief Represents a transformation for a Pose2d in the pose's frame.
 */
class Transform2d {
    Translation2d translation;
    Rotation2d rotation;

public:
    /**
     * \brief Constructs the identity transform -- maps an initial pose to itself.
     */
    constexpr Transform2d() = default;

    /**
     * \brief Constructs a transform with the given translation and rotation components.
     *
     * \param translation Translational component of the transform.
     * \param rotation Rotational component of the transform.
     */
    constexpr Transform2d(Translation2d translation, Rotation2d rotation) :
        translation{std::move(translation)},
        rotation{std::move(rotation)}
    {}

    /**
     * \brief Constructs a transform with x and y translations instead of a separate
     * Translation2d.
     *
     * \param x The x component of the translational component of the transform.
     * \param y The y component of the translational component of the transform.
     * \param rotation The rotational component of the transform.
     */
    constexpr Transform2d(units::meter_t x, units::meter_t y, Rotation2d rotation)
        : translation{x, y}, rotation{std::move(rotation)} {}

    /**
     * \brief Constructs the transform that maps the initial pose to the final pose.
     *
     * \param initial The initial pose for the transformation.
     * \param final The final pose for the transformation.
     */
    Transform2d(Pose2d const &initial, Pose2d const &final);

    /**
     * \brief Returns the translation component of the transformation.
     *
     * \returns Reference to the translational component of the transform.
     */
    constexpr Translation2d const &Translation() const { return translation; }
    /**
     * \brief Returns the X component of the transformation's translation.
     *
     * \returns The x component of the transformation's translation.
     */
    constexpr units::meter_t X() const { return translation.X(); }
    /**
     * \brief Returns the Y component of the transformation's translation.
     *
     * \returns The y component of the transformation's translation.
     */
    constexpr units::meter_t Y() const { return translation.Y(); }
    /**
     * \brief Returns the rotational component of the transformation.
     *
     * \returns Reference to the rotational component of the transform.
     */
    constexpr Rotation2d const &Rotation() const { return rotation; }

    /**
     * \brief Invert the transformation. This is useful for undoing a transformation.
     *
     * \returns The inverted transformation.
     */
    Transform2d Inverse() const
    {
        return Transform2d{-translation.RotateBy(-rotation), -rotation};
    }

    Transform2d operator+(Transform2d const &other) const;
    Transform2d operator*(double scalar) const
    {
        return {translation * scalar, rotation * scalar};
    }
    Transform2d operator/(double scalar) const
    {
        return *this * (1.0 / scalar);
    }

    bool operator==(Transform2d const &) const = default;
};

/**
 * \brief A change in distance along a 2D arc since the last pose update. We can use
 * ideas from differential calculus to create new Pose2ds from a Twist2d and
 * vice versa.
 *
 * A Twist can be used to represent a difference between two poses.
 */
struct Twist2d {
    /**
     * \brief Linear "dx" component
     */
    units::meter_t dx = 0_m;
    /**
     * \brief Linear "dy" component
     */
    units::meter_t dy = 0_m;
    /**
     * \brief Angular "dtheta" component
     */
    units::radian_t dtheta = 0_rad;

    constexpr Twist2d operator*(double factor) const
    {
        return {dx * factor, dy * factor, dtheta * factor};
    }

    bool operator==(Twist2d const &other) const
    {
        return units::math::abs(dx - other.dx) < 1E-9_m &&
               units::math::abs(dy - other.dy) < 1E-9_m &&
               units::math::abs(dtheta - other.dtheta) < 1E-9_rad;
    }
};

/**
 * \brief Represents a 2D pose containing translational and rotational elements.
 */
class Pose2d {
    Translation2d translation;
    Rotation2d rotation;

public:
    /**
     * \brief Constructs a pose at the origin facing toward the positive X axis.
     */
    constexpr Pose2d() = default;

    /**
     * \brief Constructs a pose with the specified translation and rotation.
     *
     * \param translation The translational component of the pose.
     * \param rotation The rotational component of the pose.
     */
    constexpr Pose2d(Translation2d translation, Rotation2d rotation) :
        translation{std::move(translation)},
        rotation{std::move(rotation)}
    {}

    /**
     * \brief Constructs a pose with x and y translations instead of a separate
     * Translation2d.
     *
     * \param x The x component of the translational component of the pose.
     * \param y The y component of the translational component of the pose.
     * \param rotation The rotational component of the pose.
     */
    constexpr Pose2d(units::meter_t x, units::meter_t y, Rotation2d rotation) :
        Pose2d{{x, y}, std::move(rotation)}
    {}

    /**
     * \brief Returns the underlying translation.
     *
     * \returns Reference to the translational component of the pose.
     */
    constexpr Translation2d const &Translation() const { return translation; }
    /**
     * \brief Returns the X component of the pose's translation.
     *
     * \returns The x component of the pose's translation.
     */
    constexpr units::meter_t X() const { return translation.X(); }
    /**
     * \brief Returns the Y component of the pose's translation.
     *
     * \returns The y component of the pose's translation.
     */
    constexpr units::meter_t Y() const { return translation.Y(); }
    /**
     * \brief Returns the underlying rotation.
     *
     * \returns Reference to the rotational component of the pose.
     */
    constexpr Rotation2d const &Rotation() const { return rotation; }

    /**
     * \brief Rotates the pose around the origin and returns the new pose.
     *
     * \param other The rotation to transform the pose by.
     *
     * \returns The rotated pose.
     */
    Pose2d RotateBy(Rotation2d const &angle) const
    {
        return {translation.RotateBy(angle), rotation.RotateBy(angle)};
    }

    /**
     * \brief Transforms the pose by the given transformation and returns the new pose.
     *
     * <pre>
     * [x_new]    [cos, -sin, 0][transform.x]
     * [y_new] += [sin,  cos, 0][transform.y]
     * [t_new]    [  0,    0, 1][transform.t]
     * </pre>
     *
     * \param other The transform to transform the pose by.
     *
     * \returns The transformed pose.
     */
    Pose2d TransformBy(Transform2d const &other) const
    {
        return {translation + (other.Translation().RotateBy(rotation)), other.Rotation() + rotation};
    }

    /**
     * \brief Returns the current pose relative to the given pose.
     *
     * This function can often be used for trajectory tracking or pose
     * stabilization algorithms to get the error between the reference and the
     * current pose.
     *
     * \param other The pose that is the origin of the new coordinate frame that
     * the current pose will be converted into.
     *
     * \returns The current pose relative to the new origin pose.
     */
    Pose2d RelativeTo(Pose2d const &other) const
    {
        Transform2d const transform{other, *this};
        return {transform.Translation(), transform.Rotation()};
    }

    /**
     * \brief Obtain a new Pose2d from a (constant curvature) velocity.
     *
     * See https://file.tavsys.net/control/controls-engineering-in-frc.pdf section
     * 10.2 "Pose exponential" for a derivation.
     *
     * The twist is a change in pose in the robot's coordinate frame since the
     * previous pose update. When the user runs exp() on the previous known
     * field-relative pose with the argument being the twist, the user will
     * receive the new field-relative pose.
     *
     * "Exp" represents the pose exponential, which is solving a differential
     * equation moving the pose forward in time.
     *
     * \param twist The change in pose in the robot's coordinate frame since the
     * previous pose update. For example, if a non-holonomic robot moves forward
     * 0.01 meters and changes angle by 0.5 degrees since the previous pose
     * update, the twist would be Twist2d{0.01_m, 0_m, 0.5_deg}.
     *
     * \returns The new pose of the robot.
     */
    Pose2d Exp(Twist2d const &twist) const;

    /**
     * \brief Returns a Twist2d that maps this pose to the end pose. If c is the output
     * of a.Log(b), then a.Exp(c) would yield b.
     *
     * \param end The end pose for the transformation.
     *
     * \returns The twist that maps this to end.
     */
    Twist2d Log(Pose2d const &end) const;

    Pose2d operator+(Transform2d const &other) const
    {
        return TransformBy(other);
    }
    Transform2d operator-(Pose2d const &other) const
    {
        auto const pose = RelativeTo(other);
        return Transform2d{pose.translation, pose.rotation};
    }
    Pose2d operator*(double scalar) const
    {
        return {translation * scalar, rotation * scalar};
    }
    Pose2d operator/(double scalar) const
    {
        return *this * (1.0 / scalar);
    }

    bool operator==(Pose2d const &) const = default;
};

}
}
}
