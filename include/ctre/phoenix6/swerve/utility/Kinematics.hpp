/*
 * Copyright (C) Cross The Road Electronics.  All rights reserved.
 * License information can be found in CTRE_LICENSE.txt
 * For support and suggestions contact support@ctr-electronics.com or file
 * an issue tracker at https://github.com/CrossTheRoadElec/Phoenix-Releases
 */
#pragma once

#include "ctre/phoenix6/swerve/utility/Geometry.hpp"
#include <units/angular_velocity.h>
#include <units/velocity.h>

namespace ctre {
namespace phoenix6 {
namespace swerve {

/**
 * \brief Represents the state of one swerve module.
 */
struct SwerveModuleState {
    /**
     * \brief Speed of the wheel of the module.
     */
    units::meters_per_second_t speed = 0_mps;
    /**
     * \brief Angle of the module.
     */
    Rotation2d angle = 0_rad;

    /**
     * \brief Minimize the change in heading the desired swerve module state would
     * require by potentially reversing the direction the wheel spins. If this is
     * used with the PIDController class's continuous input functionality, the
     * furthest a wheel will ever rotate is 90 degrees.
     *
     * \param currentAngle The current module angle.
     */
    void Optimize(Rotation2d const &currentAngle)
    {
        auto const delta = angle - currentAngle;
        if (units::math::abs(delta.Degrees()) > 90_deg) {
            speed *= -1;
            angle = angle + Rotation2d{180_deg};
        }
    }

    /**
     * \brief Scales speed by cosine of angle error. This scales down movement
     * perpendicular to the desired direction of travel that can occur when
     * modules change directions. This results in smoother driving.
     *
     * \param currentAngle The current module angle.
     */
    void CosineScale(Rotation2d const &currentAngle)
    {
        speed *= (angle - currentAngle).Cos();
    }

    bool operator==(SwerveModuleState const &other) const
    {
        return units::math::abs(speed - other.speed) < 1E-9_mps &&
               angle == other.angle;
    }
};

/**
 * \brief Represents the position of one swerve module.
 */
struct SwerveModulePosition {
    /**
     * \brief Distance the wheel of a module has traveled
     */
    units::meter_t distance = 0_m;
    /**
     * \brief Angle of the module.
     */
    Rotation2d angle;

    SwerveModulePosition Interpolate(SwerveModulePosition const &endValue, double t) const
    {
        return {Lerp(distance, endValue.distance, t), Lerp(angle, endValue.angle, t)};
    }

    bool operator==(SwerveModulePosition const &other) const
    {
        return units::math::abs(distance - other.distance) < 1E-9_m &&
               angle == other.angle;
    }
};

/**
 * \brief Represents the speed of a robot chassis. Although this struct contains
 * similar members compared to a Twist2d, they do NOT represent the same thing.
 * Whereas a Twist2d represents a change in pose w.r.t to the robot frame of
 * reference, a ChassisSpeeds struct represents a robot's velocity.
 *
 * A strictly non-holonomic drivetrain, such as a differential drive, should
 * never have a dy component because it can never move sideways. Holonomic
 * drivetrains such as swerve and mecanum will often have all three components.
 */
struct ChassisSpeeds {
    /**
     * \brief Velocity along the x-axis. (Fwd is +)
     */
    units::meters_per_second_t vx = 0_mps;
    /**
     * \brief Velocity along the y-axis. (Left is +)
     */
    units::meters_per_second_t vy = 0_mps;
    /**
     * \brief Represents the angular velocity of the robot frame. (CCW is +)
     */
    units::radians_per_second_t omega = 0_rad_per_s;

    /**
     * \brief Creates a Twist2d from ChassisSpeeds.
     *
     * \param dt The duration of the timestep.
     *
     * \returns Twist2d.
     */
    constexpr Twist2d ToTwist2d(units::second_t dt) const
    {
        return {vx * dt, vy * dt, omega * dt};
    }

    /**
     * \brief Disretizes a continuous-time chassis speed.
     *
     * This function converts a continuous-time chassis speed into a discrete-time
     * one such that when the discrete-time chassis speed is applied for one
     * timestep, the robot moves as if the velocity components are independent
     * (i.e., the robot moves v_x * dt along the x-axis, v_y * dt along the
     * y-axis, and omega * dt around the z-axis).
     *
     * This is useful for compensating for translational skew when translating and
     * rotating a swerve drivetrain.
     *
     * \param continuousSpeeds The continuous speeds.
     * \param dt The duration of the timestep the speeds should be applied for.
     *
     * \returns Discretized ChassisSpeeds.
     */
    static ChassisSpeeds Discretize(ChassisSpeeds const &continuousSpeeds, units::second_t dt)
    {
        Pose2d const desiredDeltaPose{continuousSpeeds.vx * dt, continuousSpeeds.vy * dt, continuousSpeeds.omega * dt};
        auto const twist = Pose2d{}.Log(desiredDeltaPose);
        return {twist.dx / dt, twist.dy / dt, twist.dtheta / dt};
    }

    /**
     * \brief Converts a user provided field-relative ChassisSpeeds object into a
     * robot-relative ChassisSpeeds object.
     *
     * \param fieldRelativeSpeeds The ChassisSpeeds object representing the speeds
     *    in the field frame of reference. Positive x is away from your alliance
     *    wall. Positive y is to your left when standing behind the alliance wall.
     * \param robotAngle The angle of the robot as measured by a gyroscope. The
     *    robot's angle is considered to be zero when it is facing directly away
     *    from your alliance station wall. Remember that this should be CCW
     *    positive.
     * \returns ChassisSpeeds object representing the speeds in the robot's frame
     *    of reference.
     */
    static ChassisSpeeds FromFieldRelativeSpeeds(ChassisSpeeds const &fieldRelativeSpeeds, Rotation2d const &robotAngle)
    {
        auto const rotated = Translation2d{fieldRelativeSpeeds.vx * 1_s, fieldRelativeSpeeds.vy * 1_s}
            .RotateBy(-robotAngle);
        return {rotated.X() / 1_s, rotated.Y() / 1_s, fieldRelativeSpeeds.omega};
    }

    /**
     * \brief Converts a user provided robot-relative ChassisSpeeds object into a
     * field-relative ChassisSpeeds object.
     *
     * \param robotRelativeSpeeds The ChassisSpeeds object representing the speeds
     *    in the robot frame of reference. Positive x is the towards robot's
     * front. Positive y is towards the robot's left.
     * \param robotAngle The angle of the robot as measured by a gyroscope. The
     *    robot's angle is considered to be zero when it is facing directly away
     *    from your alliance station wall. Remember that this should be CCW
     *    positive.
     * \returns ChassisSpeeds object representing the speeds in the field's frame
     *    of reference.
     */
    static ChassisSpeeds FromRobotRelativeSpeeds(ChassisSpeeds const &robotRelativeSpeeds, Rotation2d const &robotAngle)
    {
        auto const rotated = Translation2d{robotRelativeSpeeds.vx * 1_s, robotRelativeSpeeds.vy * 1_s}
            .RotateBy(robotAngle);
        return {rotated.X() / 1_s, rotated.Y() / 1_s, robotRelativeSpeeds.omega};
    }

    constexpr ChassisSpeeds operator-() const { return {-vx, -vy, -omega}; }
    constexpr ChassisSpeeds operator+(ChassisSpeeds const &other) const
    {
        return {vx + other.vx, vy + other.vy, omega + other.omega};
    }
    constexpr ChassisSpeeds operator-(ChassisSpeeds const &other) const
    {
        return *this + -other;
    }
    constexpr ChassisSpeeds operator*(double scalar) const
    {
        return {scalar * vx, scalar * vy, scalar * omega};
    }
    constexpr ChassisSpeeds operator/(double scalar) const
    {
        return *this * (1.0 / scalar);
    }

    constexpr bool operator==(ChassisSpeeds const &) const = default;
};

}
}
}
