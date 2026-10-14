/*
 * Copyright (C) Cross The Road Electronics.  All rights reserved.
 * License information can be found in CTRE_LICENSE.txt
 * For support and suggestions contact support@ctr-electronics.com or file
 * an issue tracker at https://github.com/CrossTheRoadElec/Phoenix-Releases
 */
#pragma once

#include "ctre/phoenix6/swerve/utility/Kinematics.hpp"
#include "units/angular_acceleration.h"
#include "units/force.h"
#include "units/moment_of_inertia.h"
#include "units/torque.h"
#include <vector>

namespace ctre {
namespace phoenix6 {
namespace swerve {

/**
 * Calculates wheel force feedforwards for a SwerveDrivetrain.
 * Wheel force feedforwards can be used to improve accuracy of path
 * following in regions of acceleration.
 *
 * Many path planning libraries (such as PathPlanner and Choreo) already
 * provide per-module force feedforwards, which should be preferred over
 * this class.
 */
class WheelForceCalculator {
public:
    /** \brief Wheel force feedforwards to apply to a swerve drivetrain. */
    struct Feedforwards {
        /** \brief The X component of the forces in Newtons. */
        std::vector<units::newton_t> x;
        /** \brief The Y component of the forces in Newtons. */
        std::vector<units::newton_t> y;

        /**
         * \brief Constructs a new set of wheel force feedforwards.
         *
         * \param numModules The number of swerve modules
         */
        Feedforwards(size_t numModules) :
            x(numModules),
            y(numModules)
        {}
    };

private:
    std::vector<Translation2d> moduleLocations;
    units::kilogram_t mass;
    units::kilogram_square_meter_t moi;

public:
    /**
     * \brief Constructs a new wheel force feedforward calculator for the given
     * drivetrain characteristics.
     *
     * \param moduleLocations The drivetrain swerve module locations
     * \param mass The mass of the robot
     * \param moi The moment of inertia of the robot
     */
    WheelForceCalculator(
        std::vector<Translation2d> moduleLocations,
        units::kilogram_t mass,
        units::kilogram_square_meter_t moi
    ) :
        moduleLocations{std::move(moduleLocations)},
        mass{mass},
        moi{moi}
    {}

    /**
     * \brief Calculates wheel force feedforwards for the desired robot acceleration.
     * This can be used with either robot-centric or field-centric accelerations;
     * the returned force feedforwards will match in being robot-/field-centric.
     *
     * \param ax Acceleration in the X direction (forward) in m/s^2
     * \param ay Acceleration in the Y direction (left) in m/s^2
     * \param alpha Angular acceleration in rad/s^2
     * \param centerOfRotation Center of rotation
     * \returns Wheel force feedforwards to apply
     */
    Feedforwards Calculate(
        units::meters_per_second_squared_t ax,
        units::meters_per_second_squared_t ay,
        units::radians_per_second_squared_t alpha,
        Translation2d const &centerOfRotation = {}
    ) const {
        units::newton_t const fx = ax * mass;
        units::newton_t const fy = ay * mass;
        units::newton_meter_t const tau = alpha * moi / 1_rad;

        Feedforwards feedforwards{moduleLocations.size()};
        for (size_t i = 0; i < moduleLocations.size(); ++i) {
            Translation2d const r = moduleLocations[i] - centerOfRotation;

            Translation2d const f_tau{tau / r.Norm() * 1_m/1_N, r.Angle() + Rotation2d{90_deg}};
            feedforwards.x[i] = (fx + f_tau.X() * 1_N/1_m) / moduleLocations.size();
            feedforwards.y[i] = (fy + f_tau.Y() * 1_N/1_m) / moduleLocations.size();
        }

        return feedforwards;
    }

    /**
     * \brief Calculates wheel force feedforwards for the desired change in speeds.
     * This can be used with either robot-centric or field-centric speeds; the
     * returned force feedforwards will match in being robot-/field-centric.
     *
     * \param dt The change in time between the path setpoints
     * \param prev The previous ChassisSpeeds setpoint of the path
     * \param current The new ChassisSpeeds setpoint of the path
     * \param centerOfRotation Center of rotation
     * \returns Wheel force feedforwards to apply
     */
    Feedforwards Calculate(
        units::second_t dt,
        ChassisSpeeds const &prev,
        ChassisSpeeds const &current,
        Translation2d const &centerOfRotation = {}
    ) const {
        auto const ax = (current.vx - prev.vx) / dt;
        auto const ay = (current.vy - prev.vy) / dt;
        auto const alpha = (current.omega - prev.omega) / dt;
        return Calculate(ax, ay, alpha, centerOfRotation);
    }
};

}
}
}
