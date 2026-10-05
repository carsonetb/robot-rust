/*
 * Copyright (C) Cross The Road Electronics.  All rights reserved.
 * License information can be found in CTRE_LICENSE.txt
 * For support and suggestions contact support@ctr-electronics.com or file
 * an issue tracker at https://github.com/CrossTheRoadElec/Phoenix-Releases
 */
#pragma once

#include "ctre/phoenix6/swerve/utility/Kinematics.hpp"
#include <units/angular_velocity.h>
#include <units/velocity.h>
#include <memory>
#include <vector>

namespace ctre {
namespace phoenix6 {
namespace swerve {
namespace impl {

/**
 * \brief Class that converts a chassis velocity (dx, dy, and dtheta components)
 * into individual module states (speed and angle).
 *
 * The inverse kinematics (converting from a desired chassis velocity to
 * individual module states) uses the relative locations of the modules with
 * respect to the center of rotation. The center of rotation for inverse
 * kinematics is also variable. This means that you can set your set your center
 * of rotation in a corner of the robot to perform special evasion maneuvers.
 *
 * Forward kinematics (converting an array of module states into the overall
 * chassis motion) is performs the exact opposite of what inverse kinematics
 * does. Since this is an overdetermined system (more equations than variables),
 * we use a least-squares approximation.
 *
 * The inverse kinematics: [moduleStates] = [moduleLocations] * [chassisSpeeds]
 * We take the Moore-Penrose pseudoinverse of [moduleLocations] and then
 * multiply by [moduleStates] to get our chassis speeds.
 *
 * Forward kinematics is also used for odometry -- determining the position of
 * the robot on the field using encoders and a gyro.
 */
class SwerveDriveKinematics {
    size_t m_numModules;
    std::vector<Translation2d> m_moduleLocations;

    struct KinematicsMatrices;
    std::unique_ptr<KinematicsMatrices> m_matrices;

    std::vector<Rotation2d> m_lastModuleHeading;
    Translation2d m_lastCOR{};

public:
    using WheelSpeeds = std::vector<SwerveModuleState>;
    using WheelPositions = std::vector<SwerveModulePosition>;

    /**
     * \brief Constructs a swerve drive kinematics object. This takes in a variable
     * number of module locations as Translation2ds. The order in which you pass
     * in the module locations is the same order that you will receive the module
     * states when performing inverse kinematics. It is also expected that you
     * pass in the module states in the same order when calling the forward
     * kinematics methods.
     *
     * \param moduleLocations The locations of the modules relative to the
     *                        physical center of the robot.
     */
    SwerveDriveKinematics(std::vector<Translation2d> moduleLocations);

    SwerveDriveKinematics(SwerveDriveKinematics const &);
    SwerveDriveKinematics(SwerveDriveKinematics &&);
    ~SwerveDriveKinematics();

    SwerveDriveKinematics &operator=(SwerveDriveKinematics const &);
    SwerveDriveKinematics &operator=(SwerveDriveKinematics &&);

    /**
     * \brief Reset the internal swerve module headings.
     *
     * \param moduleHeadings The swerve module headings. The order of the module
     * headings should be same as passed into the constructor of this class.
     */
    void ResetHeadings(std::vector<Rotation2d> const &moduleHeadings)
    {
        for (size_t i = 0; i < m_numModules && i < moduleHeadings.size(); ++i) {
            m_lastModuleHeading[i] = moduleHeadings[i];
        }
    }

    /**
     * \brief Performs inverse kinematics to return the module states from a desired
     * chassis velocity. This method is often used to convert joystick values into
     * module speeds and angles.
     *
     * This function also supports variable centers of rotation. During normal
     * operations, the center of rotation is usually the same as the physical
     * center of the robot; therefore, the argument is defaulted to that use case.
     * However, if you wish to change the center of rotation for evasive
     * maneuvers, vision alignment, or for any other use case, you can do so.
     *
     * In the case that the desired chassis speeds are zero (i.e. the robot will
     * be stationary), the previously calculated module angle will be maintained.
     *
     * \param chassisSpeeds The desired chassis speed.
     * \param centerOfRotation The center of rotation. For example, if you set the
     * center of rotation at one corner of the robot and provide a chassis speed
     * that only has a dtheta component, the robot will rotate around that corner.
     *
     * \returns A vector containing the module states. Use caution because these
     * module states are not normalized. Sometimes, a user input may cause one of
     * the module speeds to go above the attainable max velocity. Use the
     * DesaturateWheelSpeeds(WheelSpeeds*, units::meters_per_second_t) function to
     * rectify this issue.
     */
    WheelSpeeds ToSwerveModuleStates(ChassisSpeeds const &chassisSpeeds, Translation2d const &centerOfRotation = Translation2d{});

    /**
     * \brief Performs forward kinematics to return the resulting chassis state from the
     * given module states. This method is often used for odometry -- determining
     * the robot's position on the field using data from the real-world speed and
     * angle of each module on the robot.
     *
     * \param moduleStates The state of the modules as a std::vector of type
     * SwerveModuleState as measured from respective encoders and gyros. The
     * order of the swerve module states should be same as passed into the
     * constructor of this class.
     *
     * \returns The resulting chassis speed.
     */
    ChassisSpeeds ToChassisSpeeds(WheelSpeeds const &moduleStates) const;

    /**
     * \brief Performs forward kinematics to return the resulting Twist2d from the
     * given module position deltas. This method is often used for odometry --
     * determining the robot's position on the field using data from the
     * real-world position delta and angle of each module on the robot.
     *
     * \param moduleDeltas The latest change in position of the modules (as a
     * SwerveModulePosition type) as measured from respective encoders and gyros.
     * The order of the swerve module states should be same as passed into the
     * constructor of this class.
     *
     * \returns The resulting Twist2d.
     */
    Twist2d ToTwist2d(WheelPositions const &moduleDeltas) const;

    /**
     * \brief Performs forward kinematics to return the resulting Twist2d from the given
     * change in wheel positions. This method is often used for odometry --
     * determining the robot's position on the field using changes in the distance
     * driven by each wheel on the robot.
     *
     * \param start The starting distances driven by the wheels.
     * \param end The ending distances driven by the wheels.
     *
     * \returns The resulting Twist2d in the robot's movement.
     */
    Twist2d ToTwist2d(WheelPositions const &start, WheelPositions const &end) const
    {
        WheelPositions result(m_numModules);
        for (size_t i = 0; i < m_numModules && i < std::min(start.size(), end.size()); ++i) {
            result[i] = {end[i].distance - start[i].distance, end[i].angle};
        }
        return ToTwist2d(result);
    }

    /**
     * \brief Performs interpolation between two values.
     *
     * \param start The value to start at.
     * \param end The value to end at.
     * \param t How far between the two values to interpolate. This should be
     * bounded to [0, 1].
     * \returns The interpolated value.
     */
    WheelPositions Interpolate(WheelPositions const &start, WheelPositions const &end, double t) const
    {
        WheelPositions result(m_numModules);
        for (size_t i = 0; i < m_numModules && i < std::min(start.size(), end.size()); ++i) {
            result[i] = start[i].Interpolate(end[i], t);
        }
        return result;
    }

    /**
     * \brief Renormalizes the wheel speeds if any individual speed is above the
     * specified maximum.
     *
     * Sometimes, after inverse kinematics, the requested speed
     * from one or more modules may be above the max attainable speed for the
     * driving motor on that module. To fix this issue, one can reduce all the
     * wheel speeds to make sure that all requested module speeds are at-or-below
     * the absolute threshold, while maintaining the ratio of speeds between
     * modules.
     *
     * \param moduleStates Reference to vector of module states. The vector will be
     * mutated with the normalized speeds!
     * \param attainableMaxSpeed The absolute max speed that a module can reach.
     */
    static void DesaturateWheelSpeeds(WheelSpeeds *moduleStates, units::meters_per_second_t attainableMaxSpeed);
};

}
}
}
}