/*
 * Copyright (C) Cross The Road Electronics.  All rights reserved.
 * License information can be found in CTRE_LICENSE.txt
 * For support and suggestions contact support@ctr-electronics.com or file
 * an issue tracker at https://github.com/CrossTheRoadElec/Phoenix-Releases
 */
#pragma once

#include "ctre/phoenix6/swerve/impl/SwerveDriveKinematics.hpp"
#include "ctre/phoenix6/swerve/utility/TimeInterpolatableBuffer.hpp"
#include "ctre/phoenix6/Utils.hpp"
#include <array>
#include <map>

namespace ctre {
namespace phoenix6 {
namespace swerve {
namespace impl {

/**
 * \brief Class for swerve drive odometry. Odometry allows you to track the robot's
 * position on the field over a course of a match using readings from your
 * swerve drive encoders and swerve azimuth encoders.
 *
 * Teams can use odometry during the autonomous period for complex tasks like
 * path following. Furthermore, odometry can be used for latency compensation
 * when using computer-vision systems.
 */
class SwerveDriveOdometry {
public:
    using WheelSpeeds = std::vector<SwerveModuleState>;
    using WheelPositions = std::vector<SwerveModulePosition>;

private:
    SwerveDriveKinematics const &m_kinematics;
    Pose2d m_pose;

    WheelPositions m_previousWheelPositions;
    Rotation2d m_previousAngle;
    Rotation2d m_gyroOffset;

public:
    /**
     * \brief Constructs a SwerveDriveOdometry object.
     *
     * \param kinematics The swerve drive kinematics for your drivetrain.
     * \param gyroAngle The angle reported by the gyroscope.
     * \param modulePositions The wheel positions reported by each module.
     * \param initialPose The starting position of the robot on the field.
     */
    SwerveDriveOdometry(SwerveDriveKinematics const &kinematics, Rotation2d const &gyroAngle, WheelPositions modulePositions, Pose2d initialPose = Pose2d{}) :
        m_kinematics{kinematics},
        m_pose{std::move(initialPose)},
        m_previousWheelPositions{std::move(modulePositions)},
        m_previousAngle{m_pose.Rotation()},
        m_gyroOffset{m_pose.Rotation() - gyroAngle}
    {}

    /**
     * \brief Resets the robot's position on the field.
     *
     * The gyroscope angle does not need to be reset here on the user's robot
     * code. The library automatically takes care of offsetting the gyro angle.
     *
     * \param gyroAngle The angle reported by the gyroscope.
     * \param wheelPositions The current distances measured by each wheel.
     * \param pose The position on the field that your robot is at.
     */
    void ResetPosition(Rotation2d const &gyroAngle, WheelPositions wheelPositions, Pose2d const &pose)
    {
        m_pose = pose;
        m_previousAngle = m_pose.Rotation();
        m_gyroOffset = m_pose.Rotation() - gyroAngle;
        m_previousWheelPositions = std::move(wheelPositions);
    }

    /**
     * \brief Resets the pose.
     *
     * \param pose The pose to reset to.
     */
    void ResetPose(Pose2d const &pose)
    {
        m_gyroOffset = m_gyroOffset + (pose.Rotation() - m_pose.Rotation());
        m_pose = pose;
        m_previousAngle = pose.Rotation();
    }

    /**
     * \brief Resets the translation of the pose.
     *
     * \param translation The translation to reset to.
     */
    void ResetTranslation(Translation2d const &translation)
    {
        m_pose = Pose2d{translation, m_pose.Rotation()};
    }

    /**
     * \brief Resets the rotation of the pose.
     *
     * \param rotation The rotation to reset to.
     */
    void ResetRotation(Rotation2d const &rotation)
    {
        m_gyroOffset = m_gyroOffset + (rotation - m_pose.Rotation());
        m_pose = Pose2d{m_pose.Translation(), rotation};
        m_previousAngle = rotation;
    }

    /**
     * \brief Returns the position of the robot on the field.
     *
     * \returns The pose of the robot.
     */
    Pose2d const &Pose() const { return m_pose; }

    /**
     * \brief Updates the robot's position on the field using forward kinematics and
     * integration of the pose over time. This method takes in an angle parameter
     * which is used instead of the angular rate that is calculated from forward
     * kinematics, in addition to the current distance measurement at each wheel.
     *
     * \param gyroAngle The angle reported by the gyroscope.
     * \param wheelPositions The current distances measured by each wheel.
     *
     * \returns The new pose of the robot.
     */
    Pose2d const &Update(Rotation2d const &gyroAngle, WheelPositions wheelPositions);
};

/**
 * \brief This class wraps Swerve Drive Odometry to fuse latency-compensated
 * vision measurements with swerve drive encoder distance measurements. It is
 * intended to be a drop-in for SwerveDriveOdometry.
 *
 * Update() should be called every robot loop.
 *
 * AddVisionMeasurement() can be called as infrequently as you want; if you
 * never call it, then this class will behave as regular encoder odometry.
 */
class SwerveDrivePoseEstimator {
public:
    using WheelSpeeds = std::vector<SwerveModuleState>;
    using WheelPositions = std::vector<SwerveModulePosition>;

private:
    struct VisionUpdate {
        /** \brief The vision-compensated pose estimate */
        Pose2d visionPose;

        /** \brief The pose estimated based solely on odometry */
        Pose2d odometryPose;

        /**
         * \brief Returns the vision-compensated version of the pose. Specifically, changes
         * the pose from being relative to this record's odometry pose to being
         * relative to this record's vision pose.
         *
         * \param pose The pose to compensate.
         * \returns The compensated pose.
         */
        Pose2d Compensate(const Pose2d& pose) const
        {
            auto const delta = pose - odometryPose;
            return visionPose + delta;
        }
    };

    static constexpr units::second_t kBufferDuration = 1.5_s;

    SwerveDriveOdometry m_odometry;
    std::array<double, 3> m_q{};
    std::array<double, 3> m_r{};

    struct VisionMatrices;
    std::unique_ptr<VisionMatrices> m_matrices;

    /* Maps timestamps to odometry-only pose estimates */
    TimeInterpolatableBuffer<Pose2d> m_odometryPoseBuffer{kBufferDuration};
    /*
     * Maps timestamps to vision updates
     * Always contains one entry before the oldest entry in m_odometryPoseBuffer,
     * unless there have been no vision measurements after the last reset
     */
    std::map<units::second_t, VisionUpdate> m_visionUpdates;

    Pose2d m_poseEstimate;

    /**
     * \brief Removes stale vision updates that won't affect sampling.
     */
    void CleanUpVisionUpdates();

    /**
     * \brief Updates the vision matrices to account for changes in standard deviations.
     */
    void UpdateVisionMatrices();

public:
    /**
     * \brief Constructs a SwerveDrivePoseEstimator with default standard deviations
     * for the model and vision measurements.
     *
     * The default standard deviations of the model states are
     * 0.1 meters for x, 0.1 meters for y, and 0.1 radians for heading.
     * The default standard deviations of the vision measurements are
     * 0.9 meters for x, 0.9 meters for y, and 0.9 radians for heading.
     *
     * \param kinematics A correctly-configured kinematics object for your
     *     drivetrain.
     * \param gyroAngle The current gyro angle.
     * \param modulePositions The current distance and rotation measurements of
     *     the swerve modules.
     * \param initialPose The starting pose estimate.
     */
    SwerveDrivePoseEstimator(SwerveDriveKinematics const &kinematics, Rotation2d const &gyroAngle,
            WheelPositions modulePositions, Pose2d initialPose) :
        SwerveDrivePoseEstimator{kinematics, gyroAngle, std::move(modulePositions), std::move(initialPose),
            {0.1, 0.1, 0.1}, {0.9, 0.9, 0.9}}
    {}

    /**
     * \brief Constructs a SwerveDrivePoseEstimator.
     *
     * \param kinematics A correctly-configured kinematics object for your
     *     drivetrain.
     * \param gyroAngle The current gyro angle.
     * \param modulePositions The current distance and rotation measurements of
     *     the swerve modules.
     * \param initialPose The starting pose estimate.
     * \param stateStdDevs Standard deviations of the pose estimate (x position in
     *     meters, y position in meters, and heading in radians). Increase these
     *     numbers to trust your state estimate less.
     * \param visionMeasurementStdDevs Standard deviations of the vision pose
     *     measurement (x position in meters, y position in meters, and heading in
     *     radians). Increase these numbers to trust the vision pose measurement
     *     less.
     */
    SwerveDrivePoseEstimator(SwerveDriveKinematics const &kinematics, Rotation2d const &gyroAngle,
            WheelPositions modulePositions, Pose2d initialPose,
            std::array<double, 3> const &stateStdDevs, std::array<double, 3> const &visionMeasurementStdDevs);

    ~SwerveDrivePoseEstimator();

    /**
     * \brief Sets the pose estimator's trust in robot odometry. This might be used
     * to change trust in odometry after an impact with the wall or traversing a bump.
     *
     * \param stateStdDevs Standard deviations of the pose estimate (x position in
     *     meters, y position in meters, and heading in radians). Increase these
     *     numbers to trust your state estimate less.
     */
    void SetStateStdDevs(std::array<double, 3> const &stateStdDevs)
    {
        for (size_t i = 0; i < m_q.size(); ++i) {
            m_q[i] = stateStdDevs[i] * stateStdDevs[i];
        }
        UpdateVisionMatrices();
    }

    /**
     * \brief Sets the pose estimator's trust in vision measurements. This might be used
     * to change trust in vision measurements after the autonomous period, or to
     * change trust as distance to a vision target increases.
     *
     * \param visionMeasurementStdDevs Standard deviations of the vision pose
     *     measurement (x position in meters, y position in meters, and heading in
     *     radians). Increase these numbers to trust the vision pose measurement
     *     less.
     */
    void SetVisionMeasurementStdDevs(std::array<double, 3> const &visionMeasurementStdDevs)
    {
        for (size_t i = 0; i < m_r.size(); ++i) {
            m_r[i] = visionMeasurementStdDevs[i] * visionMeasurementStdDevs[i];
        }
        UpdateVisionMatrices();
    }

    /**
     * \brief Resets the robot's position on the field.
     *
     * The gyroscope angle does not need to be reset in the user's robot code.
     * The library automatically takes care of offsetting the gyro angle.
     *
     * \param gyroAngle The current gyro angle.
     * \param wheelPositions The distances traveled by the encoders.
     * \param pose The estimated pose of the robot on the field.
     */
    void ResetPosition(Rotation2d const &gyroAngle, WheelPositions wheelPositions, Pose2d const &pose)
    {
        m_odometry.ResetPosition(gyroAngle, std::move(wheelPositions), pose);
        m_odometryPoseBuffer.Clear();
        m_visionUpdates.clear();
        m_poseEstimate = m_odometry.Pose();
    }

    /**
     * \brief Resets the robot's pose.
     *
     * \param pose The pose to reset to.
     */
    void ResetPose(Pose2d const &pose)
    {
        m_odometry.ResetPose(pose);
        m_odometryPoseBuffer.Clear();
        m_visionUpdates.clear();
        m_poseEstimate = m_odometry.Pose();
    }

    /**
     * \brief Resets the robot's translation.
     *
     * \param translation The pose to translation to.
     */
    void ResetTranslation(Translation2d const &translation)
    {
        m_odometry.ResetTranslation(translation);
        m_odometryPoseBuffer.Clear();
        m_visionUpdates.clear();
        m_poseEstimate = m_odometry.Pose();
    }

    /**
     * \brief Resets the robot's rotation.
     *
     * \param rotation The rotation to reset to.
     */
    void ResetRotation(Rotation2d const &rotation)
    {
        m_odometry.ResetRotation(rotation);
        m_odometryPoseBuffer.Clear();
        m_visionUpdates.clear();
        m_poseEstimate = m_odometry.Pose();
    }

    /**
     * \brief Gets the estimated robot pose.
     *
     * \returns The estimated robot pose in meters.
     */
    Pose2d GetEstimatedPosition() const
    {
        return m_poseEstimate;
    }

    /**
     * \brief Return the pose at a given timestamp, if the buffer is not empty.
     *
     * \param timestamp The pose's timestamp.
     * \returns The pose at the given timestamp (or std::nullopt if the buffer is
     * empty).
     */
    std::optional<Pose2d> SampleAt(units::second_t timestamp) const;

    /**
     * \brief Adds a vision measurement to the Kalman Filter. This will correct
     * the odometry pose estimate while still accounting for measurement noise.
     *
     * This method can be called as infrequently as you want, as long as you are
     * calling Update() every loop.
     *
     * To promote stability of the pose estimate and make it robust to bad vision
     * data, we recommend only adding vision measurements that are already within
     * one meter or so of the current pose estimate.
     *
     * \param visionRobotPose The pose of the robot as measured by the vision
     *     camera.
     * \param timestamp The timestamp of the vision measurement in seconds. Note
     *     that if you don't use your own time source by calling UpdateWithTime(),
     *     then you must use a timestamp with an epoch since system startup (i.e.,
     *     the epoch of this timestamp is the same epoch as utils#GetCurrentTime().
     *     This means that you should use utils#GetCurrentTime() as your time source
     *     in this case.
     */
    void AddVisionMeasurement(Pose2d const &visionRobotPose, units::second_t timestamp);

    /**
     * \brief Adds a vision measurement to the Kalman Filter. This will correct
     * the odometry pose estimate while still accounting for measurement noise.
     *
     * This method can be called as infrequently as you want, as long as you are
     * calling Update() every loop.
     *
     * To promote stability of the pose estimate and make it robust to bad vision
     * data, we recommend only adding vision measurements that are already within
     * one meter or so of the current pose estimate.
     *
     * Note that the vision measurement standard deviations passed into this
     * method will continue to apply to future measurements until a subsequent
     * call to SetVisionMeasurementStdDevs() or this method.
     *
     * \param visionRobotPose The pose of the robot as measured by the vision
     *     camera.
     * \param timestamp The timestamp of the vision measurement in seconds. Note
     *     that if you don't use your own time source by calling UpdateWithTime(),
     *     then you must use a timestamp with an epoch since system startup (i.e.,
     *     the epoch of this timestamp is the same epoch as utils#GetCurrentTime().
     *     This means that you should use utils#GetCurrentTime() as your time source
     *     in this case.
     * \param visionMeasurementStdDevs Standard deviations of the vision pose
     *     measurement (x position in meters, y position in meters, and heading in
     *     radians). Increase these numbers to trust the vision pose measurement
     *     less.
     */
    void AddVisionMeasurement(Pose2d const &visionRobotPose, units::second_t timestamp,
            std::array<double, 3> const &visionMeasurementStdDevs)
    {
        SetVisionMeasurementStdDevs(visionMeasurementStdDevs);
        AddVisionMeasurement(visionRobotPose, timestamp);
    }

    /**
     * \brief Updates the pose estimator with wheel encoder and gyro information.
     * This should be called every loop.
     *
     * \param gyroAngle      The current gyro angle.
     * \param wheelPositions The distances traveled by the encoders.
     *
     * \returns The estimated pose of the robot in meters.
     */
    Pose2d Update(Rotation2d const &gyroAngle, WheelPositions const &wheelPositions)
    {
        return UpdateWithTime(utils::GetCurrentTime(), gyroAngle, wheelPositions);
    }

    /**
     * \brief Updates the pose estimator with wheel encoder and gyro information. This
     * should be called every loop.
     *
     * \param currentTime   The time at which this method was called.
     * \param gyroAngle     The current gyro angle.
     * \param wheelPositions The distances traveled by the encoders.
     *
     * \returns The estimated pose of the robot in meters.
     */
    Pose2d UpdateWithTime(units::second_t currentTime, Rotation2d const &gyroAngle, WheelPositions const &wheelPositions)
    {
        auto odometryEstimate = m_odometry.Update(gyroAngle, wheelPositions);

        m_odometryPoseBuffer.AddSample(currentTime, odometryEstimate);

        if (m_visionUpdates.empty()) {
            m_poseEstimate = std::move(odometryEstimate);
        } else {
            auto const visionUpdate = m_visionUpdates.rbegin()->second;
            m_poseEstimate = visionUpdate.Compensate(odometryEstimate);
        }

        return GetEstimatedPosition();
    }
};

}
}
}
}
