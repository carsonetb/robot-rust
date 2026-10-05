/*
 * Copyright (C) Cross The Road Electronics.  All rights reserved.
 * License information can be found in CTRE_LICENSE.txt
 * For support and suggestions contact support@ctr-electronics.com or file
 * an issue tracker at https://github.com/CrossTheRoadElec/Phoenix-Releases
 */
#pragma once

#include "ctre/phoenix6/swerve/impl/SwerveDrivetrainImpl.hpp"
#include "ctre/phoenix6/swerve/SimSwerveDrivetrain.hpp"
#include "ctre/phoenix6/swerve/SwerveModule.hpp"
#include "ctre/phoenix6/swerve/SwerveRequest.hpp"
#include "ctre/phoenix6/Pigeon2.hpp"

namespace ctre {
namespace phoenix6 {
namespace swerve {

/**
 * \brief Swerve Drive class utilizing CTR Electronics Phoenix 6 API.
 *
 * This class handles the kinematics, configuration, and odometry of a
 * swerve drive utilizing CTR Electronics devices. We recommend using
 * the Swerve Project Generator in Tuner X to create a template project
 * that demonstrates how to use this class.
 *
 * This class performs pose estimation internally using a separate odometry
 * thread. Vision measurements can be added using AddVisionMeasurement.
 * Other odometry APIs such as ResetPose are also available. The resulting
 * pose estimate can be retrieved along with module states and other
 * information using GetState. Additionally, the odometry thread synchronously
 * provides all new state updates to a telemetry function registered with
 * RegisterTelemetry.
 *
 * This class will construct the hardware devices internally, so the user
 * only specifies the constants (IDs, PID gains, gear ratios, etc).
 * Getters for these hardware devices are available.
 *
 * If using the generator, the order in which modules are constructed is
 * Front Left, Front Right, Back Left, Back Right. This means if you need
 * the Back Left module, call \c GetModule(2); to get the third (0-indexed)
 * module.
 */
template <
    typename DriveMotorT,
    typename SteerMotorT,
    typename EncoderT,
    typename = std::enable_if_t<std::is_base_of_v<hardware::traits::CommonTalon, DriveMotorT>>,
    typename = std::enable_if_t<std::is_base_of_v<hardware::traits::CommonTalon, SteerMotorT>>,
    typename = std::enable_if_t<std::disjunction_v<
        std::is_same<hardware::CANcoder, EncoderT>,
        std::is_same<hardware::CANdi, EncoderT>,
        std::is_same<hardware::TalonFXS, EncoderT>
    >>
>
class SwerveDrivetrain {
public:
    /** \brief Performs swerve module updates in a separate thread to minimize latency. */
    using OdometryThread = impl::SwerveDrivetrainImpl::OdometryThread;

    /**
     * \brief Plain-Old-Data class holding the state of the swerve drivetrain.
     * This encapsulates most data that is relevant for telemetry or
     * decision-making from the Swerve Drive.
     */
    using SwerveDriveState = impl::SwerveDrivetrainImpl::SwerveDriveState;

protected:
    /** \brief Number of times to attempt config applies. */
    static constexpr int kNumConfigAttempts = 2;

    /** \brief The underlying drivetrain instance. */
    impl::SwerveDrivetrainImpl _drivetrain;

private:
    std::vector<std::unique_ptr<SwerveModule<DriveMotorT, SteerMotorT, EncoderT>>> _modules;

    hardware::Pigeon2 _pigeon2;
    SimSwerveDrivetrain<DriveMotorT, SteerMotorT, EncoderT> _simDrive;

public:
    /**
     * \brief Constructs a CTRE SwerveDrivetrain using the specified constants.
     *
     * This constructs the underlying hardware devices, so users should not construct
     * the devices themselves. If they need the devices, they can access them
     * through getters in the classes.
     *
     * \param drivetrainConstants Drivetrain-wide constants for the swerve drive
     * \param modules             Constants for each specific module
     */
    template <
        typename... ModuleConstants,
        typename = std::enable_if_t<std::conjunction_v<
            std::is_same<
                ModuleConstants,
                SwerveModuleConstants<typename DriveMotorT::Configuration, typename SteerMotorT::Configuration, typename EncoderT::Configuration>
            >...
        >>
    >
    SwerveDrivetrain(SwerveDrivetrainConstants const &drivetrainConstants, ModuleConstants const &... modules) :
        SwerveDrivetrain{drivetrainConstants, 0_Hz, modules...}
    {}

    /**
     * \brief Constructs a CTRE SwerveDrivetrain using the specified constants.
     *
     * This constructs the underlying hardware devices, so users should not construct
     * the devices themselves. If they need the devices, they can access them
     * through getters in the classes.
     *
     * \param drivetrainConstants        Drivetrain-wide constants for the swerve drive
     * \param odometryUpdateFrequency    The frequency to run the odometry loop. If
     *                                   unspecified or set to 0 Hz, this is 250 Hz on
     *                                   CAN FD, and 100 Hz on CAN 2.0.
     * \param modules                    Constants for each specific module
     */
    template <
        typename... ModuleConstants,
        typename = std::enable_if_t<std::conjunction_v<
            std::is_same<
                ModuleConstants,
                SwerveModuleConstants<typename DriveMotorT::Configuration, typename SteerMotorT::Configuration, typename EncoderT::Configuration>
            >...
        >>
    >
    SwerveDrivetrain(
        SwerveDrivetrainConstants const &drivetrainConstants,
        units::hertz_t odometryUpdateFrequency,
        ModuleConstants const &... modules
    ) :
        SwerveDrivetrain{drivetrainConstants, odometryUpdateFrequency, std::array{0.1, 0.1, 0.1}, std::array{0.9, 0.9, 0.9}, modules...}
    {}

    /**
     * \brief Constructs a CTRE SwerveDrivetrain using the specified constants.
     *
     * This constructs the underlying hardware devices, so users should not construct
     * the devices themselves. If they need the devices, they can access them
     * through getters in the classes.
     *
     * \param drivetrainConstants        Drivetrain-wide constants for the swerve drive
     * \param odometryUpdateFrequency    The frequency to run the odometry loop. If
     *                                   unspecified or set to 0 Hz, this is 250 Hz on
     *                                   CAN FD, and 100 Hz on CAN 2.0.
     * \param odometryStandardDeviation  The standard deviation for odometry calculation
     *                                   in the form [x, y, theta]ᵀ, with units in meters
     *                                   and radians
     * \param visionStandardDeviation    The standard deviation for vision calculation
     *                                   in the form [x, y, theta]ᵀ, with units in meters
     *                                   and radians
     * \param modules                    Constants for each specific module
     */
    template <
        typename... ModuleConstants,
        typename = std::enable_if_t<std::conjunction_v<
            std::is_same<
                ModuleConstants,
                SwerveModuleConstants<typename DriveMotorT::Configuration, typename SteerMotorT::Configuration, typename EncoderT::Configuration>
            >...
        >>
    >
    SwerveDrivetrain(
        SwerveDrivetrainConstants const &drivetrainConstants,
        units::hertz_t odometryUpdateFrequency,
        std::array<double, 3> const &odometryStandardDeviation,
        std::array<double, 3> const &visionStandardDeviation,
        ModuleConstants const &... modules
    ) :
        _drivetrain{
            drivetrainConstants, odometryUpdateFrequency,
            odometryStandardDeviation, visionStandardDeviation,
            span<SwerveModuleConstants<typename DriveMotorT::Configuration, typename SteerMotorT::Configuration, typename EncoderT::Configuration> const>{
                std::array{modules...}
            }
        },
        _modules{CreateModuleArray(drivetrainConstants.CANBusName, modules...)},
        _pigeon2{drivetrainConstants.Pigeon2Id, std::string{drivetrainConstants.CANBusName}},
        _simDrive{_drivetrain.GetModuleLocations(), _pigeon2.GetSimState(), modules...}
    {
        if (drivetrainConstants.Pigeon2Configs) {
            ctre::phoenix::StatusCode retval{};
            for (int i = 0; i < kNumConfigAttempts; ++i) {
                retval = GetPigeon2().GetConfigurator().Apply(*drivetrainConstants.Pigeon2Configs);
                if (retval.IsOK()) break;
            }
            if (!retval.IsOK()) {
                printf("Pigeon2 ID %d failed config with error: %s\n", GetPigeon2().GetDeviceID(), retval.GetName());
            }
        }
        /* do not start thread until after applying Pigeon 2 configs */
        GetOdometryThread().Start();
    }

    virtual ~SwerveDrivetrain() = default;

private:
    template <typename... ModuleConstants>
    std::vector<std::unique_ptr<SwerveModule<DriveMotorT, SteerMotorT, EncoderT>>> CreateModuleArray(
        std::string_view canbusName,
        ModuleConstants const &... constants
    ) {
        std::vector<std::unique_ptr<SwerveModule<DriveMotorT, SteerMotorT, EncoderT>>> modules;
        modules.reserve(sizeof...(ModuleConstants));

        [&]<size_t... Idxs>(std::index_sequence<Idxs...>) {
            (modules.emplace_back(std::make_unique<SwerveModule<DriveMotorT, SteerMotorT, EncoderT>>(constants, canbusName, _drivetrain.GetModule(Idxs))), ...);
        }(std::index_sequence_for<ModuleConstants...>{});

        return modules;
    }

public:
    /**
     * \brief Updates all the simulation state variables for this
     * drivetrain class. User provides the update variables for the simulation.
     *
     * \param dt time since last update call
     * \param supplyVoltage voltage as seen at the motor controllers
     */
    virtual void UpdateSimState(units::second_t dt, units::volt_t supplyVoltage)
    {
        _simDrive.Update(dt, supplyVoltage, _modules);
    }

    /**
     * \brief Gets whether the drivetrain is on a CAN FD bus.
     * 
     * \returns true if on CAN FD
     */
    bool IsOnCANFD() const
    {
        return _drivetrain.IsOnCANFD();
    }

    /**
     * \brief Gets the target odometry update frequency.
     * 
     * \returns Target odometry update frequency
     */
    units::hertz_t GetOdometryFrequency() const
    {
        return _drivetrain.GetOdometryFrequency();
    }

    /**
     * \brief Gets a reference to the odometry thread.
     *
     * \returns Odometry thread
     */
    OdometryThread &GetOdometryThread()
    {
        return _drivetrain.GetOdometryThread();
    }

    /**
     * \brief Check if the odometry is currently valid.
     *
     * \returns True if odometry is valid
     */
    virtual bool IsOdometryValid() const
    {
        return _drivetrain.IsOdometryValid();
    }

    /**
     * \brief Gets a reference to the kinematics used for the drivetrain.
     * 
     * \returns Swerve kinematics
     */
    impl::SwerveDriveKinematics const &GetKinematics() const
    {
        return _drivetrain.GetKinematics();
    }

    /**
     * \brief Applies the specified control request to this swerve drivetrain.
     *
     * This captures the swerve request by reference, so it must live for
     * at least as long as the drivetrain. This can be done by storing the
     * request as a member variable of your drivetrain subsystem or robot.
     *
     * \param request Request to apply
     */
    template <
        typename Request,
        typename = std::enable_if_t<std::is_base_of_v<requests::SwerveRequest, Request>>,
        typename = std::enable_if_t<!std::is_const_v<Request>>
    >
    void SetControl(Request &request)
    {
        _drivetrain.SetControl(
            [&request](auto const &params, auto const &modules) mutable {
                return request.Apply(params, modules);
            }
        );
    }

    /**
     * \brief Applies the specified control request to this swerve drivetrain.
     *
     * \param request Request to apply
     */
    template <
        typename Request,
        typename = std::enable_if_t<std::is_base_of_v<requests::SwerveRequest, Request>>,
        typename = std::enable_if_t<!std::is_const_v<Request>>
    >
    void SetControl(Request &&request)
    {
        _drivetrain.SetControl(
            [request=std::move(request)](auto const &params, auto const &modules) mutable {
                return request.Apply(params, modules);
            }
        );
    }

    /**
     * \brief Gets the current state of the swerve drivetrain.
     * This includes information such as the pose estimate,
     * module states, and chassis speeds.
     *
     * \returns Current state of the drivetrain
     */
    SwerveDriveState GetState() const
    {
        return _drivetrain.GetState();
    }

    /**
     * \brief Register the specified lambda to be executed whenever the SwerveDriveState
     * is updated in the odometry thread.
     *
     * It is imperative that this function is cheap, as it will be executed synchronously
     * with the odometry call; if this takes a long time, it may negatively impact the
     * odometry of this stack.
     *
     * This can also be used for logging data if the function performs logging instead of telemetry.
     * Additionally, the SwerveDriveState object can be cloned and stored for later processing.
     *
     * \param telemetryFunction Function to call for telemetry or logging
     */
    virtual void RegisterTelemetry(std::function<void(SwerveDriveState const &)> telemetryFunction)
    {
        _drivetrain.RegisterTelemetry(std::move(telemetryFunction));
    }

    /**
     * \brief Configures the neutral mode to use for all modules' drive motors.
     *
     * \param neutralMode The drive motor neutral mode
     * \returns Status code of the first failed config call, or OK if all succeeded
     */
    virtual ctre::phoenix::StatusCode ConfigNeutralMode(signals::NeutralModeValue neutralMode)
    {
        return _drivetrain.ConfigNeutralMode(neutralMode);
    }

    /**
     * \brief Zero's this swerve drive's odometry entirely.
     *
     * This will zero the entire odometry, and place the robot at 0,0
     */
    virtual void TareEverything()
    {
        _drivetrain.TareEverything();
    }

    /**
     * \brief Resets the rotation of the robot pose to 0 from the
     * requests#ForwardPerspectiveValue#OperatorPerspective perspective.
     * This makes the current orientation of the robot X forward for
     * field-centric maneuvers.
     *
     * This is equivalent to calling ResetRotation with the operator
     * perspective rotation.
     */
    virtual void SeedFieldCentric()
    {
        _drivetrain.SeedFieldCentric();
    }

    /**
     * \brief Resets the pose of the robot. The pose should be from the
     * requests#ForwardPerspectiveValue#BlueAlliance perspective.
     *
     * \param pose Pose to make the current pose
     */
    virtual void ResetPose(Pose2d const &pose)
    {
        _drivetrain.ResetPose(pose);
    }

    /**
     * \brief Resets the translation of the robot pose without affecting rotation.
     * The translation should be from the requests#ForwardPerspectiveValue#BlueAlliance
     * perspective.
     *
     * \param translation Translation to make the current translation
     */
    virtual void ResetTranslation(Translation2d const &translation)
    {
        _drivetrain.ResetTranslation(translation);
    }

    /**
     * \brief Resets the rotation of the robot pose without affecting translation.
     * The rotation should be from the requests#ForwardPerspectiveValue#BlueAlliance
     * perspective.
     *
     * \param rotation Rotation to make the current rotation
     */
    virtual void ResetRotation(Rotation2d const &rotation)
    {
        _drivetrain.ResetRotation(rotation);
    }

    /**
     * \brief Takes the requests#ForwardPerspectiveValue#BlueAlliance perpective
     * direction and treats it as the forward direction for
     * requests#ForwardPerspectiveValue#OperatorPerspective.
     *
     * If the operator is in the Blue Alliance Station, this should be 0 degrees.
     * If the operator is in the Red Alliance Station, this should be 180 degrees.
     *
     * This does not change the robot pose, which is in the
     * requests#ForwardPerspectiveValue#BlueAlliance perspective.
     * As a result, the robot pose may need to be reset using ResetPose.
     *
     * \param fieldDirection Heading indicating which direction is forward from
     *                       the requests#ForwardPerspectiveValue#BlueAlliance perspective
     */
    virtual void SetOperatorPerspectiveForward(Rotation2d fieldDirection)
    {
        _drivetrain.SetOperatorPerspectiveForward(fieldDirection);
    }

    /**
     * \brief Returns the requests#ForwardPerspectiveValue#BlueAlliance perpective
     * direction that is treated as the forward direction for
     * requests#ForwardPerspectiveValue#OperatorPerspective.
     *
     * If the operator is in the Blue Alliance Station, this should be 0 degrees.
     * If the operator is in the Red Alliance Station, this should be 180 degrees.
     *
     * \returns Heading indicating which direction is forward from
     *          the requests#ForwardPerspectiveValue#BlueAlliance perspective
     */
    Rotation2d GetOperatorForwardDirection() const
    {
        return _drivetrain.GetOperatorForwardDirection();
    }

    /**
     * \brief Adds a vision measurement to the Kalman Filter. This will correct the
     * odometry pose estimate while still accounting for measurement noise.
     *
     * This method can be called as infrequently as you want
     *
     * To promote stability of the pose estimate and make it robust to bad vision
     * data, we recommend only adding vision measurements that are already within
     * one meter or so of the current pose estimate.
     *
     * \param visionRobotPose The pose of the robot as measured by the
     *                        vision camera.
     * \param timestamp       The timestamp of the vision measurement in
     *                        seconds. Note that you must use a timestamp with an
     *                        epoch since system startup (i.e., the epoch of this
     *                        timestamp is the same epoch as utils#GetCurrentTime).
     *                        This means that you should use utils#GetCurrentTime
     *                        as your time source in this case.
     *                        An FPGA timestamp can be converted to the correct
     *                        timebase using utils#FPGAToCurrentTime.
     */
    virtual void AddVisionMeasurement(Pose2d visionRobotPose, units::second_t timestamp)
    {
        _drivetrain.AddVisionMeasurement(std::move(visionRobotPose), timestamp);
    }

    /**
     * \brief Adds a vision measurement to the Kalman Filter. This will correct the
     * odometry pose estimate while still accounting for measurement noise.
     *
     * This method can be called as infrequently as you want.
     *
     * To promote stability of the pose estimate and make it robust to bad vision
     * data, we recommend only adding vision measurements that are already within
     * one meter or so of the current pose estimate.
     *
     * Note that the vision measurement standard deviations passed into this method
     * will continue to apply to future measurements until a subsequent call to
     * #SetVisionMeasurementStdDevs or this method.
     *
     * \param visionRobotPose          The pose of the robot as measured by the
     *                                 vision camera.
     * \param timestamp                The timestamp of the vision measurement in
     *                                 seconds. Note that you must use a timestamp with an
     *                                 epoch since system startup (i.e., the epoch of this
     *                                 timestamp is the same epoch as utils#GetCurrentTime).
     *                                 This means that you should use utils#GetCurrentTime
     *                                 as your time source in this case.
     *                                 An FPGA timestamp can be converted to the correct
     *                                 timebase using utils#FPGAToCurrentTime.
     * \param visionMeasurementStdDevs Standard deviations of the vision pose
     *                                 measurement (x position in meters, y position
     *                                 in meters, and heading in radians). Increase
     *                                 these numbers to trust the vision pose
     *                                 measurement less.
     */
    virtual void AddVisionMeasurement(
        Pose2d visionRobotPose,
        units::second_t timestamp,
        std::array<double, 3> visionMeasurementStdDevs)
    {
        _drivetrain.AddVisionMeasurement(std::move(visionRobotPose), timestamp, visionMeasurementStdDevs);
    }

    /**
     * \brief Sets the pose estimator's trust of global measurements. This might be used to
     * change trust in vision measurements after the autonomous period, or to change
     * trust as distance to a vision target increases.
     *
     * \param visionMeasurementStdDevs Standard deviations of the vision
     *                                 measurements. Increase these
     *                                 numbers to trust global measurements from
     *                                 vision less. This matrix is in the form [x,
     *                                 y, theta]ᵀ, with units in meters and radians.
     */
    virtual void SetVisionMeasurementStdDevs(std::array<double, 3> visionMeasurementStdDevs)
    {
        _drivetrain.SetVisionMeasurementStdDevs(visionMeasurementStdDevs);
    }

    /**
     * \brief Sets the pose estimator's trust in robot odometry. This might be used
     * to change trust in odometry after an impact with the wall or traversing a bump.
     *
     * \param stateStdDevs Standard deviations of the pose estimate. Increase these
     *                     numbers to trust your state estimate less. This matrix is
     *                     in the form [x, y, theta]ᵀ, with units in meters and radians.
     */
    virtual void SetStateStdDevs(std::array<double, 3> const &stateStdDevs)
    {
        _drivetrain.SetStateStdDevs(stateStdDevs);
    }

    /**
     * \brief Return the pose at a given timestamp, if the buffer is not empty.
     *
     * \param timestamp The pose's timestamp. Note that you must use a timestamp
     *                  with an epoch since system startup (i.e., the epoch of
     *                  this timestamp is the same epoch as utils#GetCurrentTime).
     *                  This means that you should use utils#GetCurrentTime
     *                  as your time source in this case.
     *                  An FPGA timestamp can be converted to the correct
     *                  timebase using utils#FPGAToCurrentTime.
     * \returns The pose at the given timestamp (or std::nullopt if the buffer is
     *          empty).
     */
    virtual std::optional<Pose2d> SamplePoseAt(units::second_t timestamp)
    {
        return _drivetrain.SamplePoseAt(timestamp);
    }

    /**
     * \brief Get a reference to the module at the specified index.
     * The index corresponds to the module described in the constructor.
     *
     * \param index Which module to get
     * \returns Reference to SwerveModule
     */
    SwerveModule<DriveMotorT, SteerMotorT, EncoderT> &GetModule(size_t index)
    {
        return *_modules.at(index);
    }
    /**
     * \brief Get a reference to the module at the specified index.
     * The index corresponds to the module described in the constructor.
     *
     * \param index Which module to get
     * \returns Reference to SwerveModule
     */
    SwerveModule<DriveMotorT, SteerMotorT, EncoderT> const &GetModule(size_t index) const
    {
        return *_modules.at(index);
    }
    /**
     * \brief Get a reference to the full array of modules.
     * The indexes correspond to the module described in the constructor.
     *
     * \returns Reference to the SwerveModule array
     */
    std::vector<std::unique_ptr<SwerveModule<DriveMotorT, SteerMotorT, EncoderT>>> const &GetModules() const
    {
        return _modules;
    }

    /**
     * \brief Gets the locations of the swerve modules.
     * 
     * \returns Reference to the array of swerve module locations
     */
    std::vector<Translation2d> const &GetModuleLocations() const { return _drivetrain.GetModuleLocations(); }

    /**
     * \brief Gets the current orientation of the robot as a frc#Rotation3d from
     * the Pigeon 2 quaternion values.
     *
     * \returns The robot orientation as a frc#Rotation3d
     */
    frc::Rotation3d GetRotation3d() const
    {
        return _pigeon2.GetRotation3d();
    }

    /**
     * \brief Gets this drivetrain's Pigeon 2 reference.
     *
     * This should be used only to access signals and change configurations that the
     * swerve drivetrain does not configure itself.
     *
     * \returns This drivetrain's Pigeon 2 reference
     */
    hardware::Pigeon2 &GetPigeon2()
    {
        return _pigeon2;
    }
};

}
}
}
