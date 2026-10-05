/*
 * Copyright (C) Cross The Road Electronics.  All rights reserved.
 * License information can be found in CTRE_LICENSE.txt
 * For support and suggestions contact support@ctr-electronics.com or file
 * an issue tracker at https://github.com/CrossTheRoadElec/Phoenix-Releases
 */
#pragma once

#include "ctre/phoenix6/swerve/impl/SwerveDrivetrainImpl.hpp"
#include "ctre/phoenix6/swerve/utility/PhoenixPIDController.hpp"

namespace ctre {
namespace phoenix6 {
namespace swerve {
namespace requests {

/**
 * \brief In field-centric control, the direction of "forward" is sometimes different
 * depending on perspective. This addresses which forward to use.
 */
enum class ForwardPerspectiveValue {
    /**
     * \brief "Forward" (positive X) is determined from the operator's perspective.
     * This is important for most teleop driven field-centric requests, where positive
     * X means to drive away from the operator.
     *
     * Important: Users must specify the OperatorPerspective in the SwerveDrivetrain object
     */
    OperatorPerspective = 0,
    /**
     * \brief "Forward" (positive X) is always from the perspective of the blue alliance (i.e.
     * towards the red alliance). This is important in situations such as path following where
     * positive X is always from the blue alliance perspective, regardless of where the operator
     * is physically located.
     */
    BlueAlliance = 1,
};

/**
 * \brief Container for all the Swerve Requests. Use this to find all applicable swerve
 * drive requests.
 *
 * This is also an interface common to all swerve drive control requests that
 * allow the request to calculate the state to apply to the modules.
 */
class SwerveRequest {
public:
    using ControlParameters = impl::SwerveDrivetrainImpl::ControlParameters;

    virtual ~SwerveRequest() = default;

    /**
     * \brief Applies this swerve request to the given modules.
     * This is typically called by the SwerveDrivetrain.
     *
     * \param parameters Parameters the control request needs to calculate the module state
     * \param modulesToApply Modules to which the control request is applied
     * \returns Status code of sending the request
     */
    virtual ctre::phoenix::StatusCode Apply(ControlParameters const &parameters, std::vector<std::unique_ptr<impl::SwerveModuleImpl>> const &modulesToApply) = 0;
};

/**
 * \brief Does nothing to the swerve module state. This is the default state of a newly
 * created swerve drive mechanism.
 */
class Idle : public SwerveRequest {
public:
    ctre::phoenix::StatusCode Apply(SwerveRequest::ControlParameters const &, std::vector<std::unique_ptr<impl::SwerveModuleImpl>> const &) override
    {
        return ctre::phoenix::StatusCode::OK;
    }
};

/**
 * \brief Sets the swerve drive module states to point inward on the
 * robot in an "X" fashion, creating a natural brake which will
 * oppose any motion.
 */
class SwerveDriveBrake : public SwerveRequest {
public:
    /**
     * \brief The type of control request to use for the drive motor.
     */
    impl::DriveRequestType DriveRequestType = impl::DriveRequestType::OpenLoopVoltage;
    /**
     * \brief The type of control request to use for the steer motor.
     */
    impl::SteerRequestType SteerRequestType = impl::SteerRequestType::Position;

    ctre::phoenix::StatusCode Apply(SwerveRequest::ControlParameters const &parameters, std::vector<std::unique_ptr<impl::SwerveModuleImpl>> const &modulesToApply) override
    {
        auto moduleRequest = impl::SwerveModuleImpl::ModuleRequest{}
            .WithDriveRequest(DriveRequestType)
            .WithSteerRequest(SteerRequestType)
            .WithUpdatePeriod(parameters.updatePeriod);
        for (size_t i = 0; i < modulesToApply.size(); ++i) {
            modulesToApply[i]->Apply(moduleRequest.WithState({0_mps, parameters.moduleLocations[i].Angle()}));
        }

        return ctre::phoenix::StatusCode::OK;
    }

    /**
     * \brief Modifies the DriveRequestType parameter and returns itself.
     *
     * The type of control request to use for the drive motor.
     *
     * \param newDriveRequestType Parameter to modify
     * \returns this object
     */
    SwerveDriveBrake &WithDriveRequestType(impl::DriveRequestType newDriveRequestType) &
    {
        this->DriveRequestType = std::move(newDriveRequestType);
        return *this;
    }
    /**
     * \brief Modifies the DriveRequestType parameter and returns itself.
     *
     * The type of control request to use for the drive motor.
     *
     * \param newDriveRequestType Parameter to modify
     * \returns this object
     */
    SwerveDriveBrake &&WithDriveRequestType(impl::DriveRequestType newDriveRequestType) &&
    {
        this->DriveRequestType = std::move(newDriveRequestType);
        return std::move(*this);
    }

    /**
     * \brief Modifies the SteerRequestType parameter and returns itself.
     *
     * The type of control request to use for the steer motor.
     *
     * \param newSteerRequestType Parameter to modify
     * \returns this object
     */
    SwerveDriveBrake &WithSteerRequestType(impl::SteerRequestType newSteerRequestType) &
    {
        this->SteerRequestType = std::move(newSteerRequestType);
        return *this;
    }
    /**
     * \brief Modifies the SteerRequestType parameter and returns itself.
     *
     * The type of control request to use for the steer motor.
     *
     * \param newSteerRequestType Parameter to modify
     * \returns this object
     */
    SwerveDriveBrake &&WithSteerRequestType(impl::SteerRequestType newSteerRequestType) &&
    {
        this->SteerRequestType = std::move(newSteerRequestType);
        return std::move(*this);
    }
};

/**
 * \brief Drives the swerve drivetrain in a field-centric manner.
 *
 * When users use this request, they specify the direction the robot should
 * travel oriented against the field, and the rate at which their robot should
 * rotate about the center of the robot.
 *
 * An example scenario is that the robot is oriented to the east, the
 * VelocityX is +5 m/s, VelocityY is 0 m/s, and RotationRate is 0.5 rad/s.
 * In this scenario, the robot would drive northward at 5 m/s and turn
 * counterclockwise at 0.5 rad/s.
 */
class FieldCentric : public SwerveRequest {
public:
    /**
     * \brief The velocity in the X direction. X is defined as forward according
     *  toWPILib convention, so this determines how fast to travel forward.
     */
    units::meters_per_second_t VelocityX = 0_mps;
    /**
     * \brief The velocity in the Y direction. Y is defined as to the left
     * according to WPILib convention, so this determines how fast to travel to
     * the left.
     */
    units::meters_per_second_t VelocityY = 0_mps;
    /**
     * \brief The angular rate to rotate at. Angular rate is defined as
     * counterclockwise positive, so this determines how fast to turn
     * counterclockwise.
     */
    units::radians_per_second_t RotationalRate = 0_rad_per_s;
    /**
     * \brief The allowable deadband of the request.
     */
    units::meters_per_second_t Deadband = 0_mps;
    /**
     * \brief The rotational deadband of the request.
     */
    units::radians_per_second_t RotationalDeadband = 0_rad_per_s;
    /**
     * \brief The center of rotation the robot should rotate around. This is
     * (0,0) by default, which will rotate around the center of the robot.
     */
    Translation2d CenterOfRotation{};

    /**
     * \brief The type of control request to use for the drive motor.
     */
    impl::DriveRequestType DriveRequestType = impl::DriveRequestType::OpenLoopVoltage;
    /**
     * \brief The type of control request to use for the steer motor.
     */
    impl::SteerRequestType SteerRequestType = impl::SteerRequestType::Position;
    /**
     * \brief Whether to desaturate wheel speeds before applying.
     * For more information, see the documentation of impl#SwerveDriveKinematics#DesaturateWheelSpeeds.
     */
    bool DesaturateWheelSpeeds = true;

    /**
     * \brief The perspective to use when determining which direction is forward.
     */
    ForwardPerspectiveValue ForwardPerspective = ForwardPerspectiveValue::OperatorPerspective;

    ctre::phoenix::StatusCode Apply(SwerveRequest::ControlParameters const &parameters, std::vector<std::unique_ptr<impl::SwerveModuleImpl>> const &modulesToApply) override
    {
        auto toApplyX = VelocityX;
        auto toApplyY = VelocityY;
        auto toApplyOmega = RotationalRate;

        if (ForwardPerspective == ForwardPerspectiveValue::OperatorPerspective) {
            /* If we're operator perspective, modify the X/Y translation by the angle */
            Translation2d tmp{toApplyX * 1_s, toApplyY * 1_s};
            tmp = tmp.RotateBy(parameters.operatorForwardDirection);
            toApplyX = tmp.X() / 1_s;
            toApplyY = tmp.Y() / 1_s;
        }

        if (units::math::hypot(toApplyX, toApplyY) < Deadband) {
            toApplyX = 0_mps;
            toApplyY = 0_mps;
        }
        if (units::math::abs(toApplyOmega) < RotationalDeadband) {
            toApplyOmega = 0_rad_per_s;
        }

        auto const speeds = ChassisSpeeds::Discretize(
            ChassisSpeeds::FromFieldRelativeSpeeds(
                {toApplyX, toApplyY, toApplyOmega}, parameters.currentPose.Rotation()
            ),
            parameters.updatePeriod
        );

        auto states = parameters.kinematics->ToSwerveModuleStates(speeds, CenterOfRotation);
        if (DesaturateWheelSpeeds && parameters.kMaxSpeed > 0_mps) {
            impl::SwerveDriveKinematics::DesaturateWheelSpeeds(&states, parameters.kMaxSpeed);
        }

        auto moduleRequest = impl::SwerveModuleImpl::ModuleRequest{}
            .WithDriveRequest(DriveRequestType)
            .WithSteerRequest(SteerRequestType)
            .WithUpdatePeriod(parameters.updatePeriod);
        for (size_t i = 0; i < modulesToApply.size(); ++i) {
            modulesToApply[i]->Apply(moduleRequest.WithState(states[i]));
        }

        return ctre::phoenix::StatusCode::OK;
    }

    /**
     * \brief Modifies the VelocityX parameter and returns itself.
     *
     * The velocity in the X direction. X is defined as forward according to
     * WPILib convention, so this determines how fast to travel forward.
     *
     * \param newVelocityX Parameter to modify
     * \returns this object
     */
    FieldCentric &WithVelocityX(units::meters_per_second_t newVelocityX) &
    {
        this->VelocityX = std::move(newVelocityX);
        return *this;
    }
    /**
     * \brief Modifies the VelocityX parameter and returns itself.
     *
     * The velocity in the X direction. X is defined as forward according to
     * WPILib convention, so this determines how fast to travel forward.
     *
     * \param newVelocityX Parameter to modify
     * \returns this object
     */
    FieldCentric &&WithVelocityX(units::meters_per_second_t newVelocityX) &&
    {
        this->VelocityX = std::move(newVelocityX);
        return std::move(*this);
    }

    /**
     * \brief Modifies the VelocityY parameter and returns itself.
     *
     * The velocity in the Y direction. Y is defined as to the left according
     * to WPILib convention, so this determines how fast to travel to the
     * left.
     *
     * \param newVelocityY Parameter to modify
     * \returns this object
     */
    FieldCentric &WithVelocityY(units::meters_per_second_t newVelocityY) &
    {
        this->VelocityY = std::move(newVelocityY);
        return *this;
    }
    /**
     * \brief Modifies the VelocityY parameter and returns itself.
     *
     * The velocity in the Y direction. Y is defined as to the left according
     * to WPILib convention, so this determines how fast to travel to the
     * left.
     *
     * \param newVelocityY Parameter to modify
     * \returns this object
     */
    FieldCentric &&WithVelocityY(units::meters_per_second_t newVelocityY) &&
    {
        this->VelocityY = std::move(newVelocityY);
        return std::move(*this);
    }

    /**
     * \brief Modifies the RotationalRate parameter and returns itself.
     *
     * The angular rate to rotate at. Angular rate is defined as counterclockwise
     * positive, so this determines how fast to turn counterclockwise.
     *
     * \param newRotationalRate Parameter to modify
     * \returns this object
     */
    FieldCentric &WithRotationalRate(units::radians_per_second_t newRotationalRate) &
    {
        this->RotationalRate = std::move(newRotationalRate);
        return *this;
    }
    /**
     * \brief Modifies the RotationalRate parameter and returns itself.
     *
     * The angular rate to rotate at. Angular rate is defined as counterclockwise
     * positive, so this determines how fast to turn counterclockwise.
     *
     * \param newRotationalRate Parameter to modify
     * \returns this object
     */
    FieldCentric &&WithRotationalRate(units::radians_per_second_t newRotationalRate) &&
    {
        this->RotationalRate = std::move(newRotationalRate);
        return std::move(*this);
    }

    /**
     * \brief Modifies the Deadband parameter and returns itself.
     *
     * The allowable deadband of the request.
     *
     * \param newDeadband Parameter to modify
     * \returns this object
     */
    FieldCentric &WithDeadband(units::meters_per_second_t newDeadband) &
    {
        this->Deadband = std::move(newDeadband);
        return *this;
    }
    /**
     * \brief Modifies the Deadband parameter and returns itself.
     *
     * The allowable deadband of the request.
     *
     * \param newDeadband Parameter to modify
     * \returns this object
     */
    FieldCentric &&WithDeadband(units::meters_per_second_t newDeadband) &&
    {
        this->Deadband = std::move(newDeadband);
        return std::move(*this);
    }

    /**
     * \brief Modifies the RotationalDeadband parameter and returns itself.
     *
     * The rotational deadband of the request.
     *
     * \param newRotationalDeadband Parameter to modify
     * \returns this object
     */
    FieldCentric &WithRotationalDeadband(units::radians_per_second_t newRotationalDeadband) &
    {
        this->RotationalDeadband = std::move(newRotationalDeadband);
        return *this;
    }
    /**
     * \brief Modifies the RotationalDeadband parameter and returns itself.
     *
     * The rotational deadband of the request.
     *
     * \param newRotationalDeadband Parameter to modify
     * \returns this object
     */
    FieldCentric &&WithRotationalDeadband(units::radians_per_second_t newRotationalDeadband) &&
    {
        this->RotationalDeadband = std::move(newRotationalDeadband);
        return std::move(*this);
    }

    /**
     * \brief Modifies the CenterOfRotation parameter and returns itself.
     *
     * The center of rotation the robot should rotate around. This is (0,0) by
     * default, which will rotate around the center of the robot.
     *
     * \param newCenterOfRotation Parameter to modify
     * \returns this object
     */
    FieldCentric &WithCenterOfRotation(Translation2d newCenterOfRotation) &
    {
        this->CenterOfRotation = std::move(newCenterOfRotation);
        return *this;
    }
    /**
     * \brief Modifies the CenterOfRotation parameter and returns itself.
     *
     * The center of rotation the robot should rotate around. This is (0,0) by
     * default, which will rotate around the center of the robot.
     *
     * \param newCenterOfRotation Parameter to modify
     * \returns this object
     */
    FieldCentric &&WithCenterOfRotation(Translation2d newCenterOfRotation) &&
    {
        this->CenterOfRotation = std::move(newCenterOfRotation);
        return std::move(*this);
    }

    /**
     * \brief Modifies the DriveRequestType parameter and returns itself.
     *
     * The type of control request to use for the drive motor.
     *
     * \param newDriveRequestType Parameter to modify
     * \returns this object
     */
    FieldCentric &WithDriveRequestType(impl::DriveRequestType newDriveRequestType) &
    {
        this->DriveRequestType = std::move(newDriveRequestType);
        return *this;
    }
    /**
     * \brief Modifies the DriveRequestType parameter and returns itself.
     *
     * The type of control request to use for the drive motor.
     *
     * \param newDriveRequestType Parameter to modify
     * \returns this object
     */
    FieldCentric &&WithDriveRequestType(impl::DriveRequestType newDriveRequestType) &&
    {
        this->DriveRequestType = std::move(newDriveRequestType);
        return std::move(*this);
    }

    /**
     * \brief Modifies the SteerRequestType parameter and returns itself.
     *
     * The type of control request to use for the steer motor.
     *
     * \param newSteerRequestType Parameter to modify
     * \returns this object
     */
    FieldCentric &WithSteerRequestType(impl::SteerRequestType newSteerRequestType) &
    {
        this->SteerRequestType = std::move(newSteerRequestType);
        return *this;
    }
    /**
     * \brief Modifies the SteerRequestType parameter and returns itself.
     *
     * The type of control request to use for the steer motor.
     *
     * \param newSteerRequestType Parameter to modify
     * \returns this object
     */
    FieldCentric &&WithSteerRequestType(impl::SteerRequestType newSteerRequestType) &&
    {
        this->SteerRequestType = std::move(newSteerRequestType);
        return std::move(*this);
    }

    /**
     * \brief Modifies the DesaturateWheelSpeeds parameter and returns itself.
     *
     * Whether to desaturate wheel speeds before applying. For more information, see
     * the documentation of impl#SwerveDriveKinematics#DesaturateWheelSpeeds.
     *
     * \param newDesaturateWheelSpeeds Parameter to modify
     * \returns this object
     */
    FieldCentric &WithDesaturateWheelSpeeds(bool newDesaturateWheelSpeeds) &
    {
        this->DesaturateWheelSpeeds = std::move(newDesaturateWheelSpeeds);
        return *this;
    }
    /**
     * \brief Modifies the DesaturateWheelSpeeds parameter and returns itself.
     *
     * Whether to desaturate wheel speeds before applying. For more information, see
     * the documentation of impl#SwerveDriveKinematics#DesaturateWheelSpeeds.
     *
     * \param newDesaturateWheelSpeeds Parameter to modify
     * \returns this object
     */
    FieldCentric &&WithDesaturateWheelSpeeds(bool newDesaturateWheelSpeeds) &&
    {
        this->DesaturateWheelSpeeds = std::move(newDesaturateWheelSpeeds);
        return std::move(*this);
    }

    /**
     * \brief Modifies the ForwardPerspective parameter and returns itself.
     *
     * The perspective to use when determining which direction is forward.
     *
     * \param newForwardPerspective Parameter to modify
     * \returns this object
     */
    FieldCentric &WithForwardPerspective(ForwardPerspectiveValue newForwardPerspective) &
    {
        this->ForwardPerspective = std::move(newForwardPerspective);
        return *this;
    }
    /**
     * \brief Modifies the ForwardPerspective parameter and returns itself.
     *
     * The perspective to use when determining which direction is forward.
     *
     * \param newForwardPerspective Parameter to modify
     * \returns this object
     */
    FieldCentric &&WithForwardPerspective(ForwardPerspectiveValue newForwardPerspective) &&
    {
        this->ForwardPerspective = std::move(newForwardPerspective);
        return std::move(*this);
    }
};

/**
 * \brief Drives the swerve drivetrain in a robot-centric manner.
 *
 * When users use this request, they specify the direction the robot should
 * travel oriented against the robot itself, and the rate at which their
 * robot should rotate about the center of the robot.
 *
 * An example scenario is that the robot is oriented to the east, the
 * VelocityX is +5 m/s, VelocityY is 0 m/s, and RotationRate is 0.5 rad/s.
 * In this scenario, the robot would drive eastward at 5 m/s and turn
 * counterclockwise at 0.5 rad/s.
 */
class RobotCentric : public SwerveRequest {
public:
    /**
     * \brief The velocity in the X direction. X is defined as forward according
     *  toWPILib convention, so this determines how fast to travel forward.
     */
    units::meters_per_second_t VelocityX = 0_mps;
    /**
     * \brief The velocity in the Y direction. Y is defined as to the left
     * according to WPILib convention, so this determines how fast to travel to
     * the left.
     */
    units::meters_per_second_t VelocityY = 0_mps;
    /**
     * \brief The angular rate to rotate at. Angular rate is defined as
     * counterclockwise positive, so this determines how fast to turn
     * counterclockwise.
     */
    units::radians_per_second_t RotationalRate = 0_rad_per_s;

    /**
     * \brief The allowable deadband of the request.
     */
    units::meters_per_second_t Deadband = 0_mps;
    /**
     * \brief The rotational deadband of the request.
     */
    units::radians_per_second_t RotationalDeadband = 0_rad_per_s;
    /**
     * \brief The center of rotation the robot should rotate around. This is
     * (0,0) by default, which will rotate around the center of the robot.
     */
    Translation2d CenterOfRotation{};

    /**
     * \brief The type of control request to use for the drive motor.
     */
    impl::DriveRequestType DriveRequestType = impl::DriveRequestType::OpenLoopVoltage;
    /**
     * \brief The type of control request to use for the steer motor.
     */
    impl::SteerRequestType SteerRequestType = impl::SteerRequestType::Position;
    /**
     * \brief Whether to desaturate wheel speeds before applying.
     * For more information, see the documentation of impl#SwerveDriveKinematics#DesaturateWheelSpeeds.
     */
    bool DesaturateWheelSpeeds = true;

    ctre::phoenix::StatusCode Apply(SwerveRequest::ControlParameters const &parameters, std::vector<std::unique_ptr<impl::SwerveModuleImpl>> const &modulesToApply) override
    {
        auto toApplyX = VelocityX;
        auto toApplyY = VelocityY;
        auto toApplyOmega = RotationalRate;
        if (units::math::hypot(toApplyX, toApplyY) < Deadband) {
            toApplyX = 0_mps;
            toApplyY = 0_mps;
        }
        if (units::math::abs(toApplyOmega) < RotationalDeadband) {
            toApplyOmega = 0_rad_per_s;
        }
        ChassisSpeeds const speeds{toApplyX, toApplyY, toApplyOmega};

        auto states = parameters.kinematics->ToSwerveModuleStates(speeds, CenterOfRotation);
        if (DesaturateWheelSpeeds && parameters.kMaxSpeed > 0_mps) {
            impl::SwerveDriveKinematics::DesaturateWheelSpeeds(&states, parameters.kMaxSpeed);
        }

        auto moduleRequest = impl::SwerveModuleImpl::ModuleRequest{}
            .WithDriveRequest(DriveRequestType)
            .WithSteerRequest(SteerRequestType)
            .WithUpdatePeriod(parameters.updatePeriod);
        for (size_t i = 0; i < modulesToApply.size(); ++i) {
            modulesToApply[i]->Apply(moduleRequest.WithState(states[i]));
        }

        return ctre::phoenix::StatusCode::OK;
    }

    /**
     * \brief Modifies the VelocityX parameter and returns itself.
     *
     * The velocity in the X direction. X is defined as forward according to
     * WPILib convention, so this determines how fast to travel forward.
     *
     * \param newVelocityX Parameter to modify
     * \returns this object
     */
    RobotCentric &WithVelocityX(units::meters_per_second_t newVelocityX) &
    {
        this->VelocityX = std::move(newVelocityX);
        return *this;
    }
    /**
     * \brief Modifies the VelocityX parameter and returns itself.
     *
     * The velocity in the X direction. X is defined as forward according to
     * WPILib convention, so this determines how fast to travel forward.
     *
     * \param newVelocityX Parameter to modify
     * \returns this object
     */
    RobotCentric &&WithVelocityX(units::meters_per_second_t newVelocityX) &&
    {
        this->VelocityX = std::move(newVelocityX);
        return std::move(*this);
    }

    /**
     * \brief Modifies the VelocityY parameter and returns itself.
     *
     * The velocity in the Y direction. Y is defined as to the left according
     * to WPILib convention, so this determines how fast to travel to the
     * left.
     *
     * \param newVelocityY Parameter to modify
     * \returns this object
     */
    RobotCentric &WithVelocityY(units::meters_per_second_t newVelocityY) &
    {
        this->VelocityY = std::move(newVelocityY);
        return *this;
    }
    /**
     * \brief Modifies the VelocityY parameter and returns itself.
     *
     * The velocity in the Y direction. Y is defined as to the left according
     * to WPILib convention, so this determines how fast to travel to the
     * left.
     *
     * \param newVelocityY Parameter to modify
     * \returns this object
     */
    RobotCentric &&WithVelocityY(units::meters_per_second_t newVelocityY) &&
    {
        this->VelocityY = std::move(newVelocityY);
        return std::move(*this);
    }

    /**
     * \brief Modifies the RotationalRate parameter and returns itself.
     *
     * The angular rate to rotate at. Angular rate is defined as counterclockwise
     * positive, so this determines how fast to turn counterclockwise.
     *
     * \param newRotationalRate Parameter to modify
     * \returns this object
     */
    RobotCentric &WithRotationalRate(units::radians_per_second_t newRotationalRate) &
    {
        this->RotationalRate = std::move(newRotationalRate);
        return *this;
    }
    /**
     * \brief Modifies the RotationalRate parameter and returns itself.
     *
     * The angular rate to rotate at. Angular rate is defined as counterclockwise
     * positive, so this determines how fast to turn counterclockwise.
     *
     * \param newRotationalRate Parameter to modify
     * \returns this object
     */
    RobotCentric &&WithRotationalRate(units::radians_per_second_t newRotationalRate) &&
    {
        this->RotationalRate = std::move(newRotationalRate);
        return std::move(*this);
    }

    /**
     * \brief Modifies the Deadband parameter and returns itself.
     *
     * The allowable deadband of the request.
     *
     * \param newDeadband Parameter to modify
     * \returns this object
     */
    RobotCentric &WithDeadband(units::meters_per_second_t newDeadband) &
    {
        this->Deadband = std::move(newDeadband);
        return *this;
    }
    /**
     * \brief Modifies the Deadband parameter and returns itself.
     *
     * The allowable deadband of the request.
     *
     * \param newDeadband Parameter to modify
     * \returns this object
     */
    RobotCentric &&WithDeadband(units::meters_per_second_t newDeadband) &&
    {
        this->Deadband = std::move(newDeadband);
        return std::move(*this);
    }

    /**
     * \brief Modifies the RotationalDeadband parameter and returns itself.
     *
     * The rotational deadband of the request.
     *
     * \param newRotationalDeadband Parameter to modify
     * \returns this object
     */
    RobotCentric &WithRotationalDeadband(units::radians_per_second_t newRotationalDeadband) &
    {
        this->RotationalDeadband = std::move(newRotationalDeadband);
        return *this;
    }
    /**
     * \brief Modifies the RotationalDeadband parameter and returns itself.
     *
     * The rotational deadband of the request.
     *
     * \param newRotationalDeadband Parameter to modify
     * \returns this object
     */
    RobotCentric &&WithRotationalDeadband(units::radians_per_second_t newRotationalDeadband) &&
    {
        this->RotationalDeadband = std::move(newRotationalDeadband);
        return std::move(*this);
    }

    /**
     * \brief Modifies the CenterOfRotation parameter and returns itself.
     *
     * The center of rotation the robot should rotate around. This is (0,0) by
     * default, which will rotate around the center of the robot.
     *
     * \param newCenterOfRotation Parameter to modify
     * \returns this object
     */
    RobotCentric &WithCenterOfRotation(Translation2d newCenterOfRotation) &
    {
        this->CenterOfRotation = std::move(newCenterOfRotation);
        return *this;
    }
    /**
     * \brief Modifies the CenterOfRotation parameter and returns itself.
     *
     * The center of rotation the robot should rotate around. This is (0,0) by
     * default, which will rotate around the center of the robot.
     *
     * \param newCenterOfRotation Parameter to modify
     * \returns this object
     */
    RobotCentric &&WithCenterOfRotation(Translation2d newCenterOfRotation) &&
    {
        this->CenterOfRotation = std::move(newCenterOfRotation);
        return std::move(*this);
    }

    /**
     * \brief Modifies the DriveRequestType parameter and returns itself.
     *
     * The type of control request to use for the drive motor.
     *
     * \param newDriveRequestType Parameter to modify
     * \returns this object
     */
    RobotCentric &WithDriveRequestType(impl::DriveRequestType newDriveRequestType) &
    {
        this->DriveRequestType = std::move(newDriveRequestType);
        return *this;
    }
    /**
     * \brief Modifies the DriveRequestType parameter and returns itself.
     *
     * The type of control request to use for the drive motor.
     *
     * \param newDriveRequestType Parameter to modify
     * \returns this object
     */
    RobotCentric &&WithDriveRequestType(impl::DriveRequestType newDriveRequestType) &&
    {
        this->DriveRequestType = std::move(newDriveRequestType);
        return std::move(*this);
    }

    /**
     * \brief Modifies the SteerRequestType parameter and returns itself.
     *
     * The type of control request to use for the steer motor.
     *
     * \param newSteerRequestType Parameter to modify
     * \returns this object
     */
    RobotCentric &WithSteerRequestType(impl::SteerRequestType newSteerRequestType) &
    {
        this->SteerRequestType = std::move(newSteerRequestType);
        return *this;
    }
    /**
     * \brief Modifies the SteerRequestType parameter and returns itself.
     *
     * The type of control request to use for the steer motor.
     *
     * \param newSteerRequestType Parameter to modify
     * \returns this object
     */
    RobotCentric &&WithSteerRequestType(impl::SteerRequestType newSteerRequestType) &&
    {
        this->SteerRequestType = std::move(newSteerRequestType);
        return std::move(*this);
    }

    /**
     * \brief Modifies the DesaturateWheelSpeeds parameter and returns itself.
     *
     * Whether to desaturate wheel speeds before applying. For more information, see
     * the documentation of impl#SwerveDriveKinematics#DesaturateWheelSpeeds.
     *
     * \param newDesaturateWheelSpeeds Parameter to modify
     * \returns this object
     */
    RobotCentric &WithDesaturateWheelSpeeds(bool newDesaturateWheelSpeeds) &
    {
        this->DesaturateWheelSpeeds = std::move(newDesaturateWheelSpeeds);
        return *this;
    }
    /**
     * \brief Modifies the DesaturateWheelSpeeds parameter and returns itself.
     *
     * Whether to desaturate wheel speeds before applying. For more information, see
     * the documentation of impl#SwerveDriveKinematics#DesaturateWheelSpeeds.
     *
     * \param newDesaturateWheelSpeeds Parameter to modify
     * \returns this object
     */
    RobotCentric &&WithDesaturateWheelSpeeds(bool newDesaturateWheelSpeeds) &&
    {
        this->DesaturateWheelSpeeds = std::move(newDesaturateWheelSpeeds);
        return std::move(*this);
    }
};

/**
 * \brief Sets the swerve drive modules to point to a specified direction.
 */
class PointWheelsAt : public SwerveRequest {
public:
    /**
     * \brief The direction to point the modules toward. This direction is still
     * optimized to what the module was previously at.
     */
    Rotation2d ModuleDirection{};
    /**
     * \brief The type of control request to use for the drive motor.
     */
    impl::DriveRequestType DriveRequestType = impl::DriveRequestType::OpenLoopVoltage;
    /**
     * \brief The type of control request to use for the steer motor.
     */
    impl::SteerRequestType SteerRequestType = impl::SteerRequestType::Position;

    ctre::phoenix::StatusCode Apply(SwerveRequest::ControlParameters const &parameters, std::vector<std::unique_ptr<impl::SwerveModuleImpl>> const &modulesToApply) override
    {
        auto moduleRequest = impl::SwerveModuleImpl::ModuleRequest{}
            .WithDriveRequest(DriveRequestType)
            .WithSteerRequest(SteerRequestType)
            .WithUpdatePeriod(parameters.updatePeriod);
        for (size_t i = 0; i < modulesToApply.size(); ++i) {
            modulesToApply[i]->Apply(moduleRequest.WithState({0_mps, ModuleDirection}));
        }

        return ctre::phoenix::StatusCode::OK;
    }

    /**
     * \brief Modifies the ModuleDirection parameter and returns itself.
     *
     * The direction to point the modules toward. This direction is still optimized
     * to what the module was previously at.
     *
     * \param newModuleDirection Parameter to modify
     * \returns this object
     */
    PointWheelsAt &WithModuleDirection(Rotation2d newModuleDirection) &
    {
        this->ModuleDirection = std::move(newModuleDirection);
        return *this;
    }
    /**
     * \brief Modifies the ModuleDirection parameter and returns itself.
     *
     * The direction to point the modules toward. This direction is still optimized
     * to what the module was previously at.
     *
     * \param newModuleDirection Parameter to modify
     * \returns this object
     */
    PointWheelsAt &&WithModuleDirection(Rotation2d newModuleDirection) &&
    {
        this->ModuleDirection = std::move(newModuleDirection);
        return std::move(*this);
    }

    /**
     * \brief Modifies the DriveRequestType parameter and returns itself.
     *
     * The type of control request to use for the drive motor.
     *
     * \param newDriveRequestType Parameter to modify
     * \returns this object
     */
    PointWheelsAt &WithDriveRequestType(impl::DriveRequestType newDriveRequestType) &
    {
        this->DriveRequestType = std::move(newDriveRequestType);
        return *this;
    }
    /**
     * \brief Modifies the DriveRequestType parameter and returns itself.
     *
     * The type of control request to use for the drive motor.
     *
     * \param newDriveRequestType Parameter to modify
     * \returns this object
     */
    PointWheelsAt &&WithDriveRequestType(impl::DriveRequestType newDriveRequestType) &&
    {
        this->DriveRequestType = std::move(newDriveRequestType);
        return std::move(*this);
    }

    /**
     * \brief Modifies the SteerRequestType parameter and returns itself.
     *
     * The type of control request to use for the steer motor.
     *
     * \param newSteerRequestType Parameter to modify
     * \returns this object
     */
    PointWheelsAt &WithSteerRequestType(impl::SteerRequestType newSteerRequestType) &
    {
        this->SteerRequestType = std::move(newSteerRequestType);
        return *this;
    }
    /**
     * \brief Modifies the SteerRequestType parameter and returns itself.
     *
     * The type of control request to use for the steer motor.
     *
     * \param newSteerRequestType Parameter to modify
     * \returns this object
     */
    PointWheelsAt &&WithSteerRequestType(impl::SteerRequestType newSteerRequestType) &&
    {
        this->SteerRequestType = std::move(newSteerRequestType);
        return std::move(*this);
    }
};

/**
 * \brief Accepts a generic robot-centric ChassisSpeeds to apply to the drivetrain.
 */
class ApplyRobotSpeeds : public SwerveRequest {
public:
    /**
     * \brief The robot-centric chassis speeds to apply to the drivetrain.
     */
    ChassisSpeeds Speeds{};
    /**
     * \brief Robot-centric wheel force feedforwards to apply in the
     * X direction. X is defined as forward according to WPILib
     * convention, so this determines the forward forces to apply.
     *
     * These forces should include friction applied to the ground.
     *
     * The order of the forces should match the order of the modules
     * returned from SwerveDrivetrain.
     */
    std::vector<units::newton_t> WheelForceFeedforwardsX;
    /**
     * \brief Robot-centric wheel force feedforwards to apply in the
     * Y direction. Y is defined as to the left according to WPILib
     * convention, so this determines the forces to apply to the left.
     *
     * These forces should include friction applied to the ground.
     *
     * The order of the forces should match the order of the modules
     * returned from SwerveDrivetrain.
     */
    std::vector<units::newton_t> WheelForceFeedforwardsY;
    /**
     * \brief The center of rotation to rotate around.
     */
    Translation2d CenterOfRotation{};
    /**
     * \brief The type of control request to use for the drive motor.
     */
    impl::DriveRequestType DriveRequestType = impl::DriveRequestType::OpenLoopVoltage;
    /**
     * \brief The type of control request to use for the steer motor.
     */
    impl::SteerRequestType SteerRequestType = impl::SteerRequestType::Position;
    /**
     * \brief Whether to desaturate wheel speeds before applying.
     * For more information, see the documentation of impl#SwerveDriveKinematics#DesaturateWheelSpeeds.
     */
    bool DesaturateWheelSpeeds = true;

    ctre::phoenix::StatusCode Apply(SwerveRequest::ControlParameters const &parameters, std::vector<std::unique_ptr<impl::SwerveModuleImpl>> const &modulesToApply) override
    {
        auto states = parameters.kinematics->ToSwerveModuleStates(Speeds, CenterOfRotation);
        if (DesaturateWheelSpeeds && parameters.kMaxSpeed > 0_mps) {
            impl::SwerveDriveKinematics::DesaturateWheelSpeeds(&states, parameters.kMaxSpeed);
        }

        auto moduleRequest = impl::SwerveModuleImpl::ModuleRequest{}
            .WithDriveRequest(DriveRequestType)
            .WithSteerRequest(SteerRequestType)
            .WithUpdatePeriod(parameters.updatePeriod);
        for (size_t i = 0; i < modulesToApply.size(); ++i) {
            if (i < WheelForceFeedforwardsX.size() && i < WheelForceFeedforwardsY.size()) {
                moduleRequest.WithWheelForceFeedforwardX(WheelForceFeedforwardsX[i])
                    .WithWheelForceFeedforwardY(WheelForceFeedforwardsY[i]);
            }
            modulesToApply[i]->Apply(moduleRequest.WithState(states[i]));
        }

        return ctre::phoenix::StatusCode::OK;
    }

    /**
     * \brief Modifies the Speeds parameter and returns itself.
     *
     * The robot-centric chassis speeds to apply to the drivetrain.
     *
     * \param newSpeeds Parameter to modify
     * \returns this object
     */
    ApplyRobotSpeeds &WithSpeeds(ChassisSpeeds newSpeeds) &
    {
        this->Speeds = std::move(newSpeeds);
        return *this;
    }
    /**
     * \brief Modifies the Speeds parameter and returns itself.
     *
     * The robot-centric chassis speeds to apply to the drivetrain.
     *
     * \param newSpeeds Parameter to modify
     * \returns this object
     */
    ApplyRobotSpeeds &&WithSpeeds(ChassisSpeeds newSpeeds) &&
    {
        this->Speeds = std::move(newSpeeds);
        return std::move(*this);
    }

    /**
     * \brief Modifies the WheelForceFeedforwardsX parameter and returns itself.
     *
     * Robot-centric wheel force feedforwards to apply in the
     * X direction. X is defined as forward according to WPILib
     * convention, so this determines the forward forces to apply.
     *
     * These forces should include friction applied to the ground.
     *
     * The order of the forces should match the order of the modules
     * returned from SwerveDrivetrain.
     *
     * \param newWheelForceFeedforwardsX Parameter to modify
     * \returns this object
     */
    ApplyRobotSpeeds &WithWheelForceFeedforwardsX(std::vector<units::newton_t> newWheelForceFeedforwardsX) &
    {
        this->WheelForceFeedforwardsX = std::move(newWheelForceFeedforwardsX);
        return *this;
    }
    /**
     * \brief Modifies the WheelForceFeedforwardsX parameter and returns itself.
     *
     * Robot-centric wheel force feedforwards to apply in the
     * X direction. X is defined as forward according to WPILib
     * convention, so this determines the forward forces to apply.
     *
     * These forces should include friction applied to the ground.
     *
     * The order of the forces should match the order of the modules
     * returned from SwerveDrivetrain.
     *
     * \param newWheelForceFeedforwardsX Parameter to modify
     * \returns this object
     */
    ApplyRobotSpeeds &&WithWheelForceFeedforwardsX(std::vector<units::newton_t> newWheelForceFeedforwardsX) &&
    {
        this->WheelForceFeedforwardsX = std::move(newWheelForceFeedforwardsX);
        return std::move(*this);
    }

    /**
     * \brief Modifies the WheelForceFeedforwardsY parameter and returns itself.
     *
     * Robot-centric wheel force feedforwards to apply in the
     * Y direction. Y is defined as to the left according to WPILib
     * convention, so this determines the forces to apply to the left.
     *
     * These forces should include friction applied to the ground.
     *
     * The order of the forces should match the order of the modules
     * returned from SwerveDrivetrain.
     *
     * \param newWheelForceFeedforwardsY Parameter to modify
     * \returns this object
     */
    ApplyRobotSpeeds &WithWheelForceFeedforwardsY(std::vector<units::newton_t> newWheelForceFeedforwardsY) &
    {
        this->WheelForceFeedforwardsY = std::move(newWheelForceFeedforwardsY);
        return *this;
    }
    /**
     * \brief Modifies the WheelForceFeedforwardsY parameter and returns itself.
     *
     * Robot-centric wheel force feedforwards to apply in the
     * Y direction. Y is defined as to the left according to WPILib
     * convention, so this determines the forces to apply to the left.
     *
     * These forces should include friction applied to the ground.
     *
     * The order of the forces should match the order of the modules
     * returned from SwerveDrivetrain.
     *
     * \param newWheelForceFeedforwardsY Parameter to modify
     * \returns this object
     */
    ApplyRobotSpeeds &&WithWheelForceFeedforwardsY(std::vector<units::newton_t> newWheelForceFeedforwardsY) &&
    {
        this->WheelForceFeedforwardsY = std::move(newWheelForceFeedforwardsY);
        return std::move(*this);
    }

    /**
     * \brief Modifies the CenterOfRotation parameter and returns itself.
     *
     * The center of rotation the robot should rotate around. This is (0,0) by
     * default, which will rotate around the center of the robot.
     *
     * \param newCenterOfRotation Parameter to modify
     * \return this object
     */
    ApplyRobotSpeeds &WithCenterOfRotation(Translation2d newCenterOfRotation) &
    {
        this->CenterOfRotation = std::move(newCenterOfRotation);
        return *this;
    }
    /**
     * \brief Modifies the CenterOfRotation parameter and returns itself.
     *
     * The center of rotation the robot should rotate around. This is (0,0) by
     * default, which will rotate around the center of the robot.
     *
     * \param newCenterOfRotation Parameter to modify
     * \return this object
     */
    ApplyRobotSpeeds &&WithCenterOfRotation(Translation2d newCenterOfRotation) &&
    {
        this->CenterOfRotation = std::move(newCenterOfRotation);
        return std::move(*this);
    }

    /**
     * \brief Modifies the DriveRequestType parameter and returns itself.
     *
     * The type of control request to use for the drive motor.
     *
     * \param newDriveRequestType Parameter to modify
     * \returns this object
     */
    ApplyRobotSpeeds &WithDriveRequestType(impl::DriveRequestType newDriveRequestType) &
    {
        this->DriveRequestType = std::move(newDriveRequestType);
        return *this;
    }
    /**
     * \brief Modifies the DriveRequestType parameter and returns itself.
     *
     * The type of control request to use for the drive motor.
     *
     * \param newDriveRequestType Parameter to modify
     * \returns this object
     */
    ApplyRobotSpeeds &&WithDriveRequestType(impl::DriveRequestType newDriveRequestType) &&
    {
        this->DriveRequestType = std::move(newDriveRequestType);
        return std::move(*this);
    }

    /**
     * \brief Modifies the SteerRequestType parameter and returns itself.
     *
     * The type of control request to use for the steer motor.
     *
     * \param newSteerRequestType Parameter to modify
     * \returns this object
     */
    ApplyRobotSpeeds &WithSteerRequestType(impl::SteerRequestType newSteerRequestType) &
    {
        this->SteerRequestType = std::move(newSteerRequestType);
        return *this;
    }
    /**
     * \brief Modifies the SteerRequestType parameter and returns itself.
     *
     * The type of control request to use for the steer motor.
     *
     * \param newSteerRequestType Parameter to modify
     * \returns this object
     */
    ApplyRobotSpeeds &&WithSteerRequestType(impl::SteerRequestType newSteerRequestType) &&
    {
        this->SteerRequestType = std::move(newSteerRequestType);
        return std::move(*this);
    }

    /**
     * \brief Modifies the DesaturateWheelSpeeds parameter and returns itself.
     *
     * Whether to desaturate wheel speeds before applying. For more information, see
     * the documentation of impl#SwerveDriveKinematics#DesaturateWheelSpeeds.
     *
     * \param newDesaturateWheelSpeeds Parameter to modify
     * \returns this object
     */
    ApplyRobotSpeeds &WithDesaturateWheelSpeeds(bool newDesaturateWheelSpeeds) &
    {
        this->DesaturateWheelSpeeds = std::move(newDesaturateWheelSpeeds);
        return *this;
    }
    /**
     * \brief Modifies the DesaturateWheelSpeeds parameter and returns itself.
     *
     * Whether to desaturate wheel speeds before applying. For more information, see
     * the documentation of impl#SwerveDriveKinematics#DesaturateWheelSpeeds.
     *
     * \param newDesaturateWheelSpeeds Parameter to modify
     * \returns this object
     */
    ApplyRobotSpeeds &&WithDesaturateWheelSpeeds(bool newDesaturateWheelSpeeds) &&
    {
        this->DesaturateWheelSpeeds = std::move(newDesaturateWheelSpeeds);
        return std::move(*this);
    }
};

/**
 * \brief Accepts a generic field-centric ChassisSpeeds to apply to the drivetrain.
 */
class ApplyFieldSpeeds : public SwerveRequest {
public:
    /**
     * \brief The field-centric chassis speeds to apply to the drivetrain.
     */
    ChassisSpeeds Speeds{};
    /**
     * \brief Field-centric wheel force feedforwards to apply in the
     * X direction. X is defined as forward according to WPILib
     * convention, so this determines the forward forces to apply.
     *
     * These forces should include friction applied to the ground.
     *
     * The order of the forces should match the order of the modules
     * returned from SwerveDrivetrain.
     */
    std::vector<units::newton_t> WheelForceFeedforwardsX;
    /**
     * \brief Field-centric wheel force feedforwards to apply in the
     * Y direction. Y is defined as to the left according to WPILib
     * convention, so this determines the forces to apply to the left.
     *
     * These forces should include friction applied to the ground.
     *
     * The order of the forces should match the order of the modules
     * returned from SwerveDrivetrain.
     */
    std::vector<units::newton_t> WheelForceFeedforwardsY;
    /**
     * \brief The center of rotation to rotate around.
     */
    Translation2d CenterOfRotation{};
    /**
     * \brief The type of control request to use for the drive motor.
     */
    impl::DriveRequestType DriveRequestType = impl::DriveRequestType::OpenLoopVoltage;
    /**
     * \brief The type of control request to use for the steer motor.
     */
    impl::SteerRequestType SteerRequestType = impl::SteerRequestType::Position;
    /**
     * \brief Whether to desaturate wheel speeds before applying.
     * For more information, see the documentation of impl#SwerveDriveKinematics#DesaturateWheelSpeeds.
     */
    bool DesaturateWheelSpeeds = true;

    /**
     * \brief The perspective to use when determining which direction is forward.
     */
    ForwardPerspectiveValue ForwardPerspective = ForwardPerspectiveValue::BlueAlliance;

    ctre::phoenix::StatusCode Apply(SwerveRequest::ControlParameters const &parameters, std::vector<std::unique_ptr<impl::SwerveModuleImpl>> const &modulesToApply) override
    {
        auto fieldSpeeds = Speeds;
        if (ForwardPerspective == ForwardPerspectiveValue::OperatorPerspective) {
            /* If we're operator perspective, modify the X/Y translation by the angle */
            Translation2d tmp{Speeds.vx * 1_s, Speeds.vy * 1_s};
            tmp = tmp.RotateBy(parameters.operatorForwardDirection);
            fieldSpeeds.vx = tmp.X() / 1_s;
            fieldSpeeds.vy = tmp.Y() / 1_s;
        }

        auto const robotSpeeds = ChassisSpeeds::Discretize(
            ChassisSpeeds::FromFieldRelativeSpeeds(
                fieldSpeeds, parameters.currentPose.Rotation()
            ),
            parameters.updatePeriod
        );

        auto states = parameters.kinematics->ToSwerveModuleStates(robotSpeeds, CenterOfRotation);
        if (DesaturateWheelSpeeds && parameters.kMaxSpeed > 0_mps) {
            impl::SwerveDriveKinematics::DesaturateWheelSpeeds(&states, parameters.kMaxSpeed);
        }

        auto moduleRequest = impl::SwerveModuleImpl::ModuleRequest{}
            .WithDriveRequest(DriveRequestType)
            .WithSteerRequest(SteerRequestType)
            .WithUpdatePeriod(parameters.updatePeriod);

        for (size_t i = 0; i < modulesToApply.size(); ++i) {
            if (i < WheelForceFeedforwardsX.size() && i < WheelForceFeedforwardsY.size()) {
                auto wheelForceFeedforwardX = WheelForceFeedforwardsX[i];
                auto wheelForceFeedforwardY = WheelForceFeedforwardsY[i];

                Translation2d tmp{wheelForceFeedforwardX * 1_m/1_N, wheelForceFeedforwardY * 1_m/1_N};
                if (ForwardPerspective == ForwardPerspectiveValue::OperatorPerspective) {
                    /* If we're operator perspective, modify the X/Y forces by the angle */
                    tmp = tmp.RotateBy(parameters.operatorForwardDirection);
                }
                /* Convert to robot-centric forces */
                tmp = tmp.RotateBy(-parameters.currentPose.Rotation());

                wheelForceFeedforwardX = tmp.X() * 1_N/1_m;
                wheelForceFeedforwardY = tmp.Y() * 1_N/1_m;

                moduleRequest.WithWheelForceFeedforwardX(wheelForceFeedforwardX)
                    .WithWheelForceFeedforwardY(wheelForceFeedforwardY);
            }

            modulesToApply[i]->Apply(moduleRequest.WithState(states[i]));
        }

        return ctre::phoenix::StatusCode::OK;
    }

    /**
     * \brief Modifies the Speeds parameter and returns itself.
     *
     * The field-centric chassis speeds to apply to the drivetrain.
     *
     * \param newSpeeds Parameter to modify
     * \returns this object
     */
    ApplyFieldSpeeds &WithSpeeds(ChassisSpeeds newSpeeds) &
    {
        this->Speeds = std::move(newSpeeds);
        return *this;
    }
    /**
     * \brief Modifies the Speeds parameter and returns itself.
     *
     * The field-centric chassis speeds to apply to the drivetrain.
     *
     * \param newSpeeds Parameter to modify
     * \returns this object
     */
    ApplyFieldSpeeds &&WithSpeeds(ChassisSpeeds newSpeeds) &&
    {
        this->Speeds = std::move(newSpeeds);
        return std::move(*this);
    }

    /**
     * \brief Modifies the WheelForceFeedforwardsX parameter and returns itself.
     *
     * Field-centric wheel force feedforwards to apply in the
     * X direction. X is defined as forward according to WPILib
     * convention, so this determines the forward forces to apply.
     *
     * These forces should include friction applied to the ground.
     *
     * The order of the forces should match the order of the modules
     * returned from SwerveDrivetrain.
     *
     * \param newWheelForceFeedforwardsX Parameter to modify
     * \returns this object
     */
    ApplyFieldSpeeds &WithWheelForceFeedforwardsX(std::vector<units::newton_t> newWheelForceFeedforwardsX) &
    {
        this->WheelForceFeedforwardsX = std::move(newWheelForceFeedforwardsX);
        return *this;
    }
    /**
     * \brief Modifies the WheelForceFeedforwardsX parameter and returns itself.
     *
     * Field-centric wheel force feedforwards to apply in the
     * X direction. X is defined as forward according to WPILib
     * convention, so this determines the forward forces to apply.
     *
     * These forces should include friction applied to the ground.
     *
     * The order of the forces should match the order of the modules
     * returned from SwerveDrivetrain.
     *
     * \param newWheelForceFeedforwardsX Parameter to modify
     * \returns this object
     */
    ApplyFieldSpeeds &&WithWheelForceFeedforwardsX(std::vector<units::newton_t> newWheelForceFeedforwardsX) &&
    {
        this->WheelForceFeedforwardsX = std::move(newWheelForceFeedforwardsX);
        return std::move(*this);
    }

    /**
     * \brief Modifies the WheelForceFeedforwardsY parameter and returns itself.
     *
     * Field-centric wheel force feedforwards to apply in the
     * Y direction. Y is defined as to the left according to WPILib
     * convention, so this determines the forces to apply to the left.
     *
     * These forces should include friction applied to the ground.
     *
     * The order of the forces should match the order of the modules
     * returned from SwerveDrivetrain.
     *
     * \param newWheelForceFeedforwardsY Parameter to modify
     * \returns this object
     */
    ApplyFieldSpeeds &WithWheelForceFeedforwardsY(std::vector<units::newton_t> newWheelForceFeedforwardsY) &
    {
        this->WheelForceFeedforwardsY = std::move(newWheelForceFeedforwardsY);
        return *this;
    }
    /**
     * \brief Modifies the WheelForceFeedforwardsY parameter and returns itself.
     *
     * Field-centric wheel force feedforwards to apply in the
     * Y direction. Y is defined as to the left according to WPILib
     * convention, so this determines the forces to apply to the left.
     *
     * These forces should include friction applied to the ground.
     *
     * The order of the forces should match the order of the modules
     * returned from SwerveDrivetrain.
     *
     * \param newWheelForceFeedforwardsY Parameter to modify
     * \returns this object
     */
    ApplyFieldSpeeds &&WithWheelForceFeedforwardsY(std::vector<units::newton_t> newWheelForceFeedforwardsY) &&
    {
        this->WheelForceFeedforwardsY = std::move(newWheelForceFeedforwardsY);
        return std::move(*this);
    }

    /**
     * \brief Modifies the CenterOfRotation parameter and returns itself.
     *
     * The center of rotation the robot should rotate around. This is (0,0) by
     * default, which will rotate around the center of the robot.
     *
     * \param newCenterOfRotation Parameter to modify
     * \return this object
     */
    ApplyFieldSpeeds &WithCenterOfRotation(Translation2d newCenterOfRotation) &
    {
        this->CenterOfRotation = std::move(newCenterOfRotation);
        return *this;
    }
    /**
     * \brief Modifies the CenterOfRotation parameter and returns itself.
     *
     * The center of rotation the robot should rotate around. This is (0,0) by
     * default, which will rotate around the center of the robot.
     *
     * \param newCenterOfRotation Parameter to modify
     * \return this object
     */
    ApplyFieldSpeeds &&WithCenterOfRotation(Translation2d newCenterOfRotation) &&
    {
        this->CenterOfRotation = std::move(newCenterOfRotation);
        return std::move(*this);
    }

    /**
     * \brief Modifies the DriveRequestType parameter and returns itself.
     *
     * The type of control request to use for the drive motor.
     *
     * \param newDriveRequestType Parameter to modify
     * \returns this object
     */
    ApplyFieldSpeeds &WithDriveRequestType(impl::DriveRequestType newDriveRequestType) &
    {
        this->DriveRequestType = std::move(newDriveRequestType);
        return *this;
    }
    /**
     * \brief Modifies the DriveRequestType parameter and returns itself.
     *
     * The type of control request to use for the drive motor.
     *
     * \param newDriveRequestType Parameter to modify
     * \returns this object
     */
    ApplyFieldSpeeds &&WithDriveRequestType(impl::DriveRequestType newDriveRequestType) &&
    {
        this->DriveRequestType = std::move(newDriveRequestType);
        return std::move(*this);
    }

    /**
     * \brief Modifies the SteerRequestType parameter and returns itself.
     *
     * The type of control request to use for the steer motor.
     *
     * \param newSteerRequestType Parameter to modify
     * \returns this object
     */
    ApplyFieldSpeeds &WithSteerRequestType(impl::SteerRequestType newSteerRequestType) &
    {
        this->SteerRequestType = std::move(newSteerRequestType);
        return *this;
    }
    /**
     * \brief Modifies the SteerRequestType parameter and returns itself.
     *
     * The type of control request to use for the steer motor.
     *
     * \param newSteerRequestType Parameter to modify
     * \returns this object
     */
    ApplyFieldSpeeds &&WithSteerRequestType(impl::SteerRequestType newSteerRequestType) &&
    {
        this->SteerRequestType = std::move(newSteerRequestType);
        return std::move(*this);
    }

    /**
     * \brief Modifies the DesaturateWheelSpeeds parameter and returns itself.
     *
     * Whether to desaturate wheel speeds before applying. For more information, see
     * the documentation of impl#SwerveDriveKinematics#DesaturateWheelSpeeds.
     *
     * \param newDesaturateWheelSpeeds Parameter to modify
     * \returns this object
     */
    ApplyFieldSpeeds &WithDesaturateWheelSpeeds(bool newDesaturateWheelSpeeds) &
    {
        this->DesaturateWheelSpeeds = std::move(newDesaturateWheelSpeeds);
        return *this;
    }
    /**
     * \brief Modifies the DesaturateWheelSpeeds parameter and returns itself.
     *
     * Whether to desaturate wheel speeds before applying. For more information, see
     * the documentation of impl#SwerveDriveKinematics#DesaturateWheelSpeeds.
     *
     * \param newDesaturateWheelSpeeds Parameter to modify
     * \returns this object
     */
    ApplyFieldSpeeds &&WithDesaturateWheelSpeeds(bool newDesaturateWheelSpeeds) &&
    {
        this->DesaturateWheelSpeeds = std::move(newDesaturateWheelSpeeds);
        return std::move(*this);
    }

    /**
     * \brief Modifies the ForwardPerspective parameter and returns itself.
     *
     * The perspective to use when determining which direction is forward.
     *
     * \param newForwardPerspective Parameter to modify
     * \returns this object
     */
    ApplyFieldSpeeds &WithForwardPerspective(ForwardPerspectiveValue newForwardPerspective) &
    {
        this->ForwardPerspective = std::move(newForwardPerspective);
        return *this;
    }
    /**
     * \brief Modifies the ForwardPerspective parameter and returns itself.
     *
     * The perspective to use when determining which direction is forward.
     *
     * \param newForwardPerspective Parameter to modify
     * \returns this object
     */
    ApplyFieldSpeeds &&WithForwardPerspective(ForwardPerspectiveValue newForwardPerspective) &&
    {
        this->ForwardPerspective = std::move(newForwardPerspective);
        return std::move(*this);
    }
};

/**
 * \brief Drives the swerve drivetrain in a field-centric manner, maintaining a
 * specified heading angle to ensure the robot is facing the desired direction
 *
 * When users use this request, they specify the direction the robot should
 * travel oriented against the field, and the direction the robot should be facing.
 *
 * An example scenario is that the robot is oriented to the east, the VelocityX
 * is +5 m/s, VelocityY is 0 m/s, and TargetDirection is 180 degrees.
 * In this scenario, the robot would drive northward at 5 m/s and turn clockwise
 * to a target of 180 degrees.
 *
 * This control request is especially useful for autonomous control, where the
 * robot should be facing a changing direction throughout the motion.
 */
class FieldCentricFacingAngle : public SwerveRequest {
public:
    /**
     * \brief The velocity in the X direction. X is defined as forward according
     * to WPILib convention, so this determines how fast to travel forward.
     */
    units::meters_per_second_t VelocityX = 0_mps;
    /**
     * \brief The velocity in the Y direction. Y is defined as to the left
     * according to WPILib convention, so this determines how fast to travel to
     * the left.
     */
    units::meters_per_second_t VelocityY = 0_mps;
    /**
     * \brief The desired direction to face.
     * 0 Degrees is defined as in the direction of the X axis.
     * As a result, a TargetDirection of 90 degrees will point along
     * the Y axis, or to the left.
     */
    Rotation2d TargetDirection{};
    /**
     * \brief The rotational rate feedforward to add to the output of the heading
     * controller, in radians per second. When using a motion profile for the
     * target direction, this can be set to the current velocity reference of
     * the profile.
     */
    units::radians_per_second_t TargetRateFeedforward = 0_rad_per_s;

    /**
     * \brief The allowable deadband of the request.
     */
    units::meters_per_second_t Deadband = 0_mps;
    /**
     * \brief The rotational deadband of the request.
     */
    units::radians_per_second_t RotationalDeadband = 0_rad_per_s;
    /**
     * \brief The maximum absolute rotational rate to allow.
     * Setting this to 0 results in no cap to rotational rate.
     */
    units::radians_per_second_t MaxAbsRotationalRate = 0_rad_per_s;
    /**
     * \brief The center of rotation the robot should rotate around. This is
     * (0,0) by default, which will rotate around the center of the robot.
     */
    Translation2d CenterOfRotation{};

    /**
     * \brief The type of control request to use for the drive motor.
     */
    impl::DriveRequestType DriveRequestType = impl::DriveRequestType::OpenLoopVoltage;
    /**
     * \brief The type of control request to use for the steer motor.
     */
    impl::SteerRequestType SteerRequestType = impl::SteerRequestType::Position;
    /**
     * \brief Whether to desaturate wheel speeds before applying.
     * For more information, see the documentation of impl#SwerveDriveKinematics#DesaturateWheelSpeeds.
     */
    bool DesaturateWheelSpeeds = true;

    /**
     * \brief The perspective to use when determining which direction is forward.
     */
    ForwardPerspectiveValue ForwardPerspective = ForwardPerspectiveValue::OperatorPerspective;

    /**
     * \brief The PID controller used to maintain the desired heading.
     * Users can specify the PID gains to change how aggressively to maintain
     * heading.
     *
     * This PID controller operates on heading radians and outputs a target
     * rotational rate in radians per second. Note that continuous input should
     * be enabled on the range [-pi, pi].
     */
    PhoenixPIDController HeadingController{0, 0, 0};

    FieldCentricFacingAngle()
    {
        HeadingController.EnableContinuousInput(-units::constants::detail::PI_VAL, units::constants::detail::PI_VAL);
    }

    ctre::phoenix::StatusCode Apply(SwerveRequest::ControlParameters const &parameters, std::vector<std::unique_ptr<impl::SwerveModuleImpl>> const &modulesToApply) override
    {
        Rotation2d angleToFace = TargetDirection;
        if (ForwardPerspective == ForwardPerspectiveValue::OperatorPerspective) {
            /* If we're operator perspective, rotate the direction we want to face by the angle */
            angleToFace = angleToFace.RotateBy(parameters.operatorForwardDirection);
        }

        units::radians_per_second_t toApplyOmega = TargetRateFeedforward +
            units::radians_per_second_t{HeadingController.Calculate(
                parameters.currentPose.Rotation().Radians().value(),
                angleToFace.Radians().value(),
                parameters.timestamp
            )};
        if (MaxAbsRotationalRate > 0_rad_per_s) {
            if (toApplyOmega > MaxAbsRotationalRate) {
                toApplyOmega = MaxAbsRotationalRate;
            } else if (toApplyOmega < -MaxAbsRotationalRate) {
                toApplyOmega = -MaxAbsRotationalRate;
            }
        }

        return FieldCentric{}
            .WithVelocityX(VelocityX)
            .WithVelocityY(VelocityY)
            .WithRotationalRate(toApplyOmega)
            .WithDeadband(Deadband)
            .WithRotationalDeadband(RotationalDeadband)
            .WithCenterOfRotation(CenterOfRotation)
            .WithDriveRequestType(DriveRequestType)
            .WithSteerRequestType(SteerRequestType)
            .WithDesaturateWheelSpeeds(DesaturateWheelSpeeds)
            .WithForwardPerspective(ForwardPerspective)
            .Apply(parameters, modulesToApply);
    }

    /**
     * \brief Modifies the PID gains of the HeadingController parameter and returns itself.
     *
     * Sets the proportional, integral, and differential coefficients used to maintain
     * the desired heading. Users can specify the PID gains to change how aggressively to
     * maintain heading.
     *
     * This PID controller operates on heading radians and outputs a target
     * rotational rate in radians per second.
     *
     * \param kP The proportional coefficient; must be >= 0
     * \param kI The integral coefficient; must be >= 0
     * \param kD The differential coefficient; must be >= 0
     * \returns this object
     */
    FieldCentricFacingAngle &WithHeadingPID(double kP, double kI, double kD)
    {
        this->HeadingController.SetPID(kP, kI, kD);
        return *this;
    }

    /**
     * \brief Modifies the VelocityX parameter and returns itself.
     *
     * The velocity in the X direction. X is defined as forward according to
     * WPILib convention, so this determines how fast to travel forward.
     *
     * \param newVelocityX Parameter to modify
     * \returns this object
     */
    FieldCentricFacingAngle &WithVelocityX(units::meters_per_second_t newVelocityX)
    {
        this->VelocityX = std::move(newVelocityX);
        return *this;
    }

    /**
     * \brief Modifies the VelocityY parameter and returns itself.
     *
     * The velocity in the Y direction. Y is defined as to the left according
     * to WPILib convention, so this determines how fast to travel to the
     * left.
     *
     * \param newVelocityY Parameter to modify
     * \returns this object
     */
    FieldCentricFacingAngle &WithVelocityY(units::meters_per_second_t newVelocityY)
    {
        this->VelocityY = std::move(newVelocityY);
        return *this;
    }

    /**
     * \brief Modifies the VelocityY parameter and returns itself.
     *
     * The desired direction to face. 0 Degrees is defined as in the direction of
     * the X axis. As a result, a TargetDirection of 90 degrees will point along
     * the Y axis, or to the left.
     *
     * \param newTargetDirection Parameter to modify
     * \returns this object
     */
    FieldCentricFacingAngle &WithTargetDirection(Rotation2d newTargetDirection)
    {
        this->TargetDirection = std::move(newTargetDirection);
        return *this;
    }

    /**
     * \brief Modifies the VelocityY parameter and returns itself.
     *
     * The rotational rate feedforward to add to the output of the heading
     * controller, in radians per second. When using a motion profile for the
     * target direction, this can be set to the current velocity reference of
     * the profile.
     *
     * \param newTargetRateFeedforward Parameter to modify
     * \returns this object
     */
    FieldCentricFacingAngle &WithTargetRateFeedforward(units::radians_per_second_t newTargetRateFeedforward)
    {
        this->TargetRateFeedforward = std::move(newTargetRateFeedforward);
        return *this;
    }

    /**
     * \brief Modifies the Deadband parameter and returns itself.
     *
     * The allowable deadband of the request.
     *
     * \param newDeadband Parameter to modify
     * \returns this object
     */
    FieldCentricFacingAngle &WithDeadband(units::meters_per_second_t newDeadband)
    {
        this->Deadband = std::move(newDeadband);
        return *this;
    }

    /**
     * \brief Modifies the RotationalDeadband parameter and returns itself.
     *
     * The rotational deadband of the request.
     *
     * \param newRotationalDeadband Parameter to modify
     * \returns this object
     */
    FieldCentricFacingAngle &WithRotationalDeadband(units::radians_per_second_t newRotationalDeadband)
    {
        this->RotationalDeadband = std::move(newRotationalDeadband);
        return *this;
    }

    /**
     * \brief Modifies the MaxAbsRotationalRate parameter and returns itself.
     *
     * The maximum absolute rotational rate to allow.
     * Setting this to 0 results in no cap to rotational rate.
     *
     * \param newMaxAbsRotationalRate Parameter to modify
     * \returns this object
     */
    FieldCentricFacingAngle &WithMaxAbsRotationalRate(units::radians_per_second_t newMaxAbsRotationalRate)
    {
        this->MaxAbsRotationalRate = std::move(newMaxAbsRotationalRate);
        return *this;
    }

    /**
     * \brief Modifies the CenterOfRotation parameter and returns itself.
     *
     * The center of rotation the robot should rotate around. This is (0,0) by
     * default, which will rotate around the center of the robot.
     *
     * \param newCenterOfRotation Parameter to modify
     * \returns this object
     */
    FieldCentricFacingAngle &WithCenterOfRotation(Translation2d newCenterOfRotation)
    {
        this->CenterOfRotation = std::move(newCenterOfRotation);
        return *this;
    }

    /**
     * \brief Modifies the DriveRequestType parameter and returns itself.
     *
     * The type of control request to use for the drive motor.
     *
     * \param newDriveRequestType Parameter to modify
     * \returns this object
     */
    FieldCentricFacingAngle &WithDriveRequestType(impl::DriveRequestType newDriveRequestType)
    {
        this->DriveRequestType = std::move(newDriveRequestType);
        return *this;
    }

    /**
     * \brief Modifies the SteerRequestType parameter and returns itself.
     *
     * The type of control request to use for the steer motor.
     *
     * \param newSteerRequestType Parameter to modify
     * \returns this object
     */
    FieldCentricFacingAngle &WithSteerRequestType(impl::SteerRequestType newSteerRequestType)
    {
        this->SteerRequestType = std::move(newSteerRequestType);
        return *this;
    }

    /**
     * \brief Modifies the DesaturateWheelSpeeds parameter and returns itself.
     *
     * Whether to desaturate wheel speeds before applying. For more information, see
     * the documentation of impl#SwerveDriveKinematics#DesaturateWheelSpeeds.
     *
     * \param newDesaturateWheelSpeeds Parameter to modify
     * \returns this object
     */
    FieldCentricFacingAngle &WithDesaturateWheelSpeeds(bool newDesaturateWheelSpeeds)
    {
        this->DesaturateWheelSpeeds = std::move(newDesaturateWheelSpeeds);
        return *this;
    }

    /**
     * \brief Modifies the ForwardPerspective parameter and returns itself.
     *
     * The perspective to use when determining which direction is forward.
     *
     * \param newForwardPerspective Parameter to modify
     * \returns this object
     */
    FieldCentricFacingAngle &WithForwardPerspective(ForwardPerspectiveValue newForwardPerspective)
    {
        this->ForwardPerspective = std::move(newForwardPerspective);
        return *this;
    }
};

/**
 * \brief Drives the swerve drivetrain in a robot-centric manner, maintaining a
 * specified heading angle to ensure the robot is facing the desired direction
 *
 * When users use this request, they specify the direction the robot should
 * travel oriented against the robot itself, and the direction the robot should
 * be facing relative to the field.
 *
 * An example scenario is that the robot is oriented to the east, the VelocityX
 * is +5 m/s, VelocityY is 0 m/s, and TargetDirection is 180 degrees.
 * In this scenario, the robot would drive forward at 5 m/s and turn clockwise
 * to a target of 180 degrees.
 *
 * This control request is especially useful for vision control, where the
 * robot should be facing a vision target throughout the motion.
 */
class RobotCentricFacingAngle : public SwerveRequest {
public:
    /**
     * \brief The velocity in the X direction. X is defined as forward according
     * to WPILib convention, so this determines how fast to travel forward.
     */
    units::meters_per_second_t VelocityX = 0_mps;
    /**
     * \brief The velocity in the Y direction. Y is defined as to the left
     * according to WPILib convention, so this determines how fast to travel to
     * the left.
     */
    units::meters_per_second_t VelocityY = 0_mps;
    /**
     * \brief The desired direction to face.
     * 0 Degrees is defined as in the direction of the X axis.
     * As a result, a TargetDirection of 90 degrees will point along
     * the Y axis, or to the left.
     */
    Rotation2d TargetDirection{};
    /**
     * \brief The rotational rate feedforward to add to the output of the heading
     * controller, in radians per second. When using a motion profile for the
     * target direction, this can be set to the current velocity reference of
     * the profile.
     */
    units::radians_per_second_t TargetRateFeedforward = 0_rad_per_s;

    /**
     * \brief The allowable deadband of the request.
     */
    units::meters_per_second_t Deadband = 0_mps;
    /**
     * \brief The rotational deadband of the request.
     */
    units::radians_per_second_t RotationalDeadband = 0_rad_per_s;
    /**
     * \brief The maximum absolute rotational rate to allow.
     * Setting this to 0 results in no cap to rotational rate.
     */
    units::radians_per_second_t MaxAbsRotationalRate = 0_rad_per_s;
    /**
     * \brief The center of rotation the robot should rotate around. This is
     * (0,0) by default, which will rotate around the center of the robot.
     */
    Translation2d CenterOfRotation{};

    /**
     * \brief The type of control request to use for the drive motor.
     */
    impl::DriveRequestType DriveRequestType = impl::DriveRequestType::OpenLoopVoltage;
    /**
     * \brief The type of control request to use for the steer motor.
     */
    impl::SteerRequestType SteerRequestType = impl::SteerRequestType::Position;
    /**
     * \brief Whether to desaturate wheel speeds before applying.
     * For more information, see the documentation of impl#SwerveDriveKinematics#DesaturateWheelSpeeds.
     */
    bool DesaturateWheelSpeeds = true;

    /**
     * \brief The perspective to use when determining which direction is forward
     * for the target heading.
     */
    ForwardPerspectiveValue ForwardPerspective = ForwardPerspectiveValue::OperatorPerspective;

    /**
     * \brief The PID controller used to maintain the desired heading.
     * Users can specify the PID gains to change how aggressively to maintain
     * heading.
     *
     * This PID controller operates on heading radians and outputs a target
     * rotational rate in radians per second. Note that continuous input should
     * be enabled on the range [-pi, pi].
     */
    PhoenixPIDController HeadingController{0, 0, 0};

    RobotCentricFacingAngle()
    {
        HeadingController.EnableContinuousInput(-units::constants::detail::PI_VAL, units::constants::detail::PI_VAL);
    }

    ctre::phoenix::StatusCode Apply(SwerveRequest::ControlParameters const &parameters, std::vector<std::unique_ptr<impl::SwerveModuleImpl>> const &modulesToApply) override
    {
        Rotation2d angleToFace = TargetDirection;
        if (ForwardPerspective == ForwardPerspectiveValue::OperatorPerspective) {
            /* If we're operator perspective, rotate the direction we want to face by the angle */
            angleToFace = angleToFace.RotateBy(parameters.operatorForwardDirection);
        }

        units::radians_per_second_t toApplyOmega = TargetRateFeedforward +
            units::radians_per_second_t{HeadingController.Calculate(
                parameters.currentPose.Rotation().Radians().value(),
                angleToFace.Radians().value(),
                parameters.timestamp
            )};
        if (MaxAbsRotationalRate > 0_rad_per_s) {
            if (toApplyOmega > MaxAbsRotationalRate) {
                toApplyOmega = MaxAbsRotationalRate;
            } else if (toApplyOmega < -MaxAbsRotationalRate) {
                toApplyOmega = -MaxAbsRotationalRate;
            }
        }

        return RobotCentric{}
            .WithVelocityX(VelocityX)
            .WithVelocityY(VelocityY)
            .WithRotationalRate(toApplyOmega)
            .WithDeadband(Deadband)
            .WithRotationalDeadband(RotationalDeadband)
            .WithCenterOfRotation(CenterOfRotation)
            .WithDriveRequestType(DriveRequestType)
            .WithSteerRequestType(SteerRequestType)
            .WithDesaturateWheelSpeeds(DesaturateWheelSpeeds)
            .Apply(parameters, modulesToApply);
    }

    /**
     * \brief Modifies the PID gains of the HeadingController parameter and returns itself.
     *
     * Sets the proportional, integral, and differential coefficients used to maintain
     * the desired heading. Users can specify the PID gains to change how aggressively to
     * maintain heading.
     *
     * This PID controller operates on heading radians and outputs a target
     * rotational rate in radians per second.
     *
     * \param kP The proportional coefficient; must be >= 0
     * \param kI The integral coefficient; must be >= 0
     * \param kD The differential coefficient; must be >= 0
     * \returns this object
     */
    RobotCentricFacingAngle &WithHeadingPID(double kP, double kI, double kD)
    {
        this->HeadingController.SetPID(kP, kI, kD);
        return *this;
    }

    /**
     * \brief Modifies the VelocityX parameter and returns itself.
     *
     * The velocity in the X direction. X is defined as forward according to
     * WPILib convention, so this determines how fast to travel forward.
     *
     * \param newVelocityX Parameter to modify
     * \returns this object
     */
    RobotCentricFacingAngle &WithVelocityX(units::meters_per_second_t newVelocityX)
    {
        this->VelocityX = std::move(newVelocityX);
        return *this;
    }

    /**
     * \brief Modifies the VelocityY parameter and returns itself.
     *
     * The velocity in the Y direction. Y is defined as to the left according
     * to WPILib convention, so this determines how fast to travel to the
     * left.
     *
     * \param newVelocityY Parameter to modify
     * \returns this object
     */
    RobotCentricFacingAngle &WithVelocityY(units::meters_per_second_t newVelocityY)
    {
        this->VelocityY = std::move(newVelocityY);
        return *this;
    }

    /**
     * \brief Modifies the VelocityY parameter and returns itself.
     *
     * The desired direction to face. 0 Degrees is defined as in the direction of
     * the X axis. As a result, a TargetDirection of 90 degrees will point along
     * the Y axis, or to the left.
     *
     * \param newTargetDirection Parameter to modify
     * \returns this object
     */
    RobotCentricFacingAngle &WithTargetDirection(Rotation2d newTargetDirection)
    {
        this->TargetDirection = std::move(newTargetDirection);
        return *this;
    }

    /**
     * \brief Modifies the VelocityY parameter and returns itself.
     *
     * The rotational rate feedforward to add to the output of the heading
     * controller, in radians per second. When using a motion profile for the
     * target direction, this can be set to the current velocity reference of
     * the profile.
     *
     * \param newTargetRateFeedforward Parameter to modify
     * \returns this object
     */
    RobotCentricFacingAngle &WithTargetRateFeedforward(units::radians_per_second_t newTargetRateFeedforward)
    {
        this->TargetRateFeedforward = std::move(newTargetRateFeedforward);
        return *this;
    }

    /**
     * \brief Modifies the Deadband parameter and returns itself.
     *
     * The allowable deadband of the request.
     *
     * \param newDeadband Parameter to modify
     * \returns this object
     */
    RobotCentricFacingAngle &WithDeadband(units::meters_per_second_t newDeadband)
    {
        this->Deadband = std::move(newDeadband);
        return *this;
    }

    /**
     * \brief Modifies the RotationalDeadband parameter and returns itself.
     *
     * The rotational deadband of the request.
     *
     * \param newRotationalDeadband Parameter to modify
     * \returns this object
     */
    RobotCentricFacingAngle &WithRotationalDeadband(units::radians_per_second_t newRotationalDeadband)
    {
        this->RotationalDeadband = std::move(newRotationalDeadband);
        return *this;
    }

    /**
     * \brief Modifies the MaxAbsRotationalRate parameter and returns itself.
     *
     * The maximum absolute rotational rate to allow.
     * Setting this to 0 results in no cap to rotational rate.
     *
     * \param newMaxAbsRotationalRate Parameter to modify
     * \returns this object
     */
    RobotCentricFacingAngle &WithMaxAbsRotationalRate(units::radians_per_second_t newMaxAbsRotationalRate)
    {
        this->MaxAbsRotationalRate = std::move(newMaxAbsRotationalRate);
        return *this;
    }

    /**
     * \brief Modifies the CenterOfRotation parameter and returns itself.
     *
     * The center of rotation the robot should rotate around. This is (0,0) by
     * default, which will rotate around the center of the robot.
     *
     * \param newCenterOfRotation Parameter to modify
     * \returns this object
     */
    RobotCentricFacingAngle &WithCenterOfRotation(Translation2d newCenterOfRotation)
    {
        this->CenterOfRotation = std::move(newCenterOfRotation);
        return *this;
    }

    /**
     * \brief Modifies the DriveRequestType parameter and returns itself.
     *
     * The type of control request to use for the drive motor.
     *
     * \param newDriveRequestType Parameter to modify
     * \returns this object
     */
    RobotCentricFacingAngle &WithDriveRequestType(impl::DriveRequestType newDriveRequestType)
    {
        this->DriveRequestType = std::move(newDriveRequestType);
        return *this;
    }

    /**
     * \brief Modifies the SteerRequestType parameter and returns itself.
     *
     * The type of control request to use for the steer motor.
     *
     * \param newSteerRequestType Parameter to modify
     * \returns this object
     */
    RobotCentricFacingAngle &WithSteerRequestType(impl::SteerRequestType newSteerRequestType)
    {
        this->SteerRequestType = std::move(newSteerRequestType);
        return *this;
    }

    /**
     * \brief Modifies the DesaturateWheelSpeeds parameter and returns itself.
     *
     * Whether to desaturate wheel speeds before applying. For more information, see
     * the documentation of impl#SwerveDriveKinematics#DesaturateWheelSpeeds.
     *
     * \param newDesaturateWheelSpeeds Parameter to modify
     * \returns this object
     */
    RobotCentricFacingAngle &WithDesaturateWheelSpeeds(bool newDesaturateWheelSpeeds)
    {
        this->DesaturateWheelSpeeds = std::move(newDesaturateWheelSpeeds);
        return *this;
    }

    /**
     * \brief Modifies the ForwardPerspective parameter and returns itself.
     *
     * The perspective to use when determining which direction is forward
     * for the target heading.
     *
     * \param newForwardPerspective Parameter to modify
     * \returns this object
     */
    RobotCentricFacingAngle &WithForwardPerspective(ForwardPerspectiveValue newForwardPerspective)
    {
        this->ForwardPerspective = std::move(newForwardPerspective);
        return *this;
    }
};

/**
 * \brief SysId-specific SwerveRequest to characterize the translational
 * characteristics of a swerve drivetrain.
 */
class SysIdSwerveTranslation : public SwerveRequest {
public:
    /**
     * \brief Voltage to apply to drive wheels.
     */
    units::volt_t VoltsToApply = 0_V;

    ctre::phoenix::StatusCode Apply(SwerveRequest::ControlParameters const &parameters, std::vector<std::unique_ptr<impl::SwerveModuleImpl>> const &modulesToApply) override
    {
        for (size_t i = 0; i < modulesToApply.size(); ++i) {
            switch (modulesToApply[i]->GetSteerClosedLoopOutputType()) {
                case ClosedLoopOutputType::Voltage:
                    modulesToApply[i]->Apply(
                        controls::VoltageOut{VoltsToApply},
                        controls::PositionVoltage{0_tr}
                    );
                    break;
                case ClosedLoopOutputType::TorqueCurrentFOC:
                    modulesToApply[i]->Apply(
                        controls::VoltageOut{VoltsToApply},
                        controls::PositionTorqueCurrentFOC{0_tr}
                    );
                    break;
            }
        }
        return ctre::phoenix::StatusCode::OK;
    }

    /**
     * \brief Sets the voltage to apply to drive wheels.
     *
     * \param volts Voltage to apply
     * \returns this request
     */
    SysIdSwerveTranslation &WithVolts(units::volt_t volts) &
    {
        this->VoltsToApply = volts;
        return *this;
    }
    /**
     * \brief Sets the voltage to apply to drive wheels.
     *
     * \param volts Voltage to apply
     * \returns this request
     */
    SysIdSwerveTranslation &&WithVolts(units::volt_t volts) &&
    {
        this->VoltsToApply = volts;
        return std::move(*this);
    }
};

/**
 * \brief SysId-specific SwerveRequest to characterize the rotational
 * characteristics of a swerve drivetrain. This is useful to
 * characterize the heading controller for FieldCentricFacingAngle.
 *
 * The RotationalRate of this swerve request should be logged.
 * When importing the log to SysId, set the "voltage" to
 * RotationalRate, "position" to the Pigeon 2 Yaw, and "velocity"
 * to the Pigeon 2 AngularVelocityZWorld. Note that the position
 * and velocity will both need to be scaled by pi/180.
 *
 * Alternatively, the MotorVoltage of one of the drive motors can
 * be loaded into the SysId "voltage" field, which can be useful
 * when determining the MOI of the robot.
 */
class SysIdSwerveRotation : public SwerveRequest {
public:
    /**
     * \brief The angular rate to rotate at, in radians per second.
     */
    units::radians_per_second_t RotationalRate = 0_rad_per_s;

    ctre::phoenix::StatusCode Apply(SwerveRequest::ControlParameters const &parameters, std::vector<std::unique_ptr<impl::SwerveModuleImpl>> const &modulesToApply) override
    {
        for (size_t i = 0; i < modulesToApply.size(); ++i) {
            auto const speed = RotationalRate * (parameters.moduleLocations[i].Norm() / 1_rad);
            auto const driveVoltage = speed / parameters.kMaxSpeed * 12_V;

            auto const angle = parameters.moduleLocations[i].Angle() + Rotation2d{90_deg};

            switch (modulesToApply[i]->GetSteerClosedLoopOutputType()) {
                case ClosedLoopOutputType::Voltage:
                    modulesToApply[i]->Apply(
                        controls::VoltageOut{driveVoltage},
                        controls::PositionVoltage{angle.Radians()}
                    );
                    break;
                case ClosedLoopOutputType::TorqueCurrentFOC:
                    modulesToApply[i]->Apply(
                        controls::VoltageOut{driveVoltage},
                        controls::PositionTorqueCurrentFOC{angle.Radians()}
                    );
                    break;
            }
        }
        return ctre::phoenix::StatusCode::OK;
    }

    /**
     * \brief Update the angular rate to rotate at, in radians per second.
     *
     * \param rotationalRate Angular rate to rotate at
     * \returns this request
     */
    SysIdSwerveRotation &WithRotationalRate(units::radians_per_second_t rotationalRate) &
    {
        this->RotationalRate = rotationalRate;
        return *this;
    }
    /**
     * \brief Update the angular rate to rotate at, in radians per second.
     *
     * \param rotationalRate Angular rate to rotate at
     * \returns this request
     */
    SysIdSwerveRotation &&WithRotationalRate(units::radians_per_second_t rotationalRate) &&
    {
        this->RotationalRate = rotationalRate;
        return std::move(*this);
    }
};

/**
 * \brief SysId-specific SwerveRequest to characterize the steer module
 * characteristics of a swerve drivetrain.
 */
class SysIdSwerveSteerGains : public SwerveRequest {
public:
    /**
     * \brief Voltage to apply to drive wheels.
     */
    units::volt_t VoltsToApply = 0_V;

    ctre::phoenix::StatusCode Apply(SwerveRequest::ControlParameters const &parameters, std::vector<std::unique_ptr<impl::SwerveModuleImpl>> const &modulesToApply) override
    {
        for (size_t i = 0; i < modulesToApply.size(); ++i) {
            modulesToApply[i]->Apply(controls::CoastOut{}, controls::VoltageOut{VoltsToApply});
        }
        return ctre::phoenix::StatusCode::OK;
    }

    /**
     * \brief Update the voltage to apply to the drive wheels.
     *
     * \param volts Voltage to apply
     * \returns this request
     */
    SysIdSwerveSteerGains &WithVolts(units::volt_t volts) &
    {
        this->VoltsToApply = volts;
        return *this;
    }
    /**
     * \brief Update the voltage to apply to the drive wheels.
     *
     * \param volts Voltage to apply
     * \returns this request
     */
    SysIdSwerveSteerGains &&WithVolts(units::volt_t volts) &&
    {
        this->VoltsToApply = volts;
        return std::move(*this);
    }
};

}
}
}
}
