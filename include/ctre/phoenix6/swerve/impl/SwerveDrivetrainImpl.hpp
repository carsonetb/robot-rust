/*
 * Copyright (C) Cross The Road Electronics.  All rights reserved.
 * License information can be found in CTRE_LICENSE.txt
 * For support and suggestions contact support@ctr-electronics.com or file
 * an issue tracker at https://github.com/CrossTheRoadElec/Phoenix-Releases
 */
#pragma once

#include "ctre/phoenix6/swerve/impl/SwerveModuleImpl.hpp"
#include "ctre/phoenix6/swerve/impl/SwerveDrivePoseEstimator.hpp"
#include "ctre/phoenix6/swerve/SwerveDrivetrainConstants.hpp"
#include "ctre/phoenix6/swerve/utility/LinearFilter.hpp"
#include "ctre/phoenix6/CANBus.hpp"

#include <atomic>
#include <thread>

namespace ctre {
namespace phoenix6 {
namespace swerve {
namespace impl {

/**
 * \brief Swerve Drive class utilizing CTR Electronics Phoenix 6 API.
 *
 * This class handles the kinematics and odometry (but not configuration)
 * of a swerve drive utilizing CTR Electronics devices. Users should
 * create a high-level SwerveDrivetrain instead of using this directly.
 */
class SwerveDrivetrainImpl {
public:
    /** \brief Performs swerve module updates in a separate thread to minimize latency. */
    class OdometryThread {
    protected:
        static constexpr int START_THREAD_PRIORITY = 1; // Testing shows 1 (minimum realtime) is sufficient for tighter
                                                        // odometry loops.
                                                        // If the odometry period is far away from the desired frequency,
                                                        // increasing this may help

        SwerveDrivetrainImpl *_drivetrain;

        std::thread _thread;
        std::mutex _threadMtx;
        std::atomic<bool> _isRunning = false;

        std::vector<BaseStatusSignal *> _allSignals;

        static constexpr int kLowPassTaps = 50;
        LinearFilter<units::second_t> _lowPass = LinearFilter<units::second_t>::MovingAverage(kLowPassTaps);
        bool _lastTimeValid = false;
        units::second_t _lastTime{};
        units::second_t _averageLoopTime{};

        std::atomic<int32_t> _successfulDaqs{};
        std::atomic<int32_t> _failedDaqs{};

        std::atomic<int> _threadPriorityToSet = START_THREAD_PRIORITY;
        int _lastThreadPriority = START_THREAD_PRIORITY;

    public:
        OdometryThread(SwerveDrivetrainImpl &drivetrain);
        ~OdometryThread()
        {
            Stop();
        }

        /**
         * \brief Starts the odometry thread.
         */
        void Start()
        {
            std::lock_guard<std::mutex> lock{_threadMtx};
            if (!_thread.joinable()) {
                _isRunning.store(true, std::memory_order_relaxed);
                _thread = std::thread{[this] { Run(); }};
            }
        }

        /**
         * \brief Stops the odometry thread.
         */
        void Stop()
        {
            std::lock_guard<std::mutex> lock{_threadMtx};
            if (_thread.joinable()) {
                _isRunning.store(false, std::memory_order_relaxed);
                _thread.join();
            }
        }

        /**
         * \brief Check if the odometry is currently valid.
         *
         * \returns True if odometry is valid
         */
        bool IsOdometryValid() const
        {
            return _successfulDaqs.load(std::memory_order_relaxed) > 2;
        }

        /**
         * \brief Sets the odometry thread priority to a real time priority under the specified priority level
         *
         * \param priority Priority level to set the odometry thread to.
         *                 This is a value between 0 and 99, with 99 indicating higher priority and 0 indicating lower priority.
         */
        void SetThreadPriority(int priority)
        {
            _threadPriorityToSet.store(priority, std::memory_order_relaxed);
        }

    protected:
        void Run();
    };

    /**
     * \brief Plain-Old-Data class holding the state of the swerve drivetrain.
     * This encapsulates most data that is relevant for telemetry or
     * decision-making from the Swerve Drive.
     */
    struct SwerveDriveState {
        /** \brief The current pose of the robot */
        Pose2d Pose;
        /** \brief The current robot-centric velocity */
        ChassisSpeeds Speeds;
        /** \brief The current module states */
        std::vector<SwerveModuleState> ModuleStates;
        /** \brief The target module states */
        std::vector<SwerveModuleState> ModuleTargets;
        /** \brief The current module positions */
        std::vector<SwerveModulePosition> ModulePositions;
        /** \brief The raw heading of the robot, unaffected by vision updates and odometry resets */
        Rotation2d RawHeading;
        /** \brief The timestamp of the state capture, in the timebase of utils#GetCurrentTime() */
        units::second_t Timestamp;
        /** \brief The measured odometry update period */
        units::second_t OdometryPeriod;
        /** \brief Number of successful data acquisitions */
        int32_t SuccessfulDaqs;
        /** \brief Number of failed data acquisitions */
        int32_t FailedDaqs;
    };

    /**
     * \brief Contains everything the control requests need to calculate the module state.
     */
    struct ControlParameters {
        /** \brief The kinematics object used for control */
        impl::SwerveDriveKinematics *kinematics;
        /** \brief The locations of the swerve modules */
        Translation2d const *moduleLocations;
        /** \brief The max speed of the robot at 12 V output */
        units::meters_per_second_t kMaxSpeed;

        /** \brief The forward direction from the operator perspective */
        Rotation2d operatorForwardDirection;
        /** \brief The current robot-centric chassis speeds */
        ChassisSpeeds currentChassisSpeed;
        /** \brief The current pose of the robot */
        Pose2d currentPose;
        /** \brief The timestamp of the current control apply, in the timebase of utils#GetCurrentTime() */
        units::second_t timestamp;
        /** \brief The update period of control apply */
        units::second_t updatePeriod;
    };

    using SwerveRequestFunc = std::function<ctre::phoenix::StatusCode(ControlParameters const &, std::vector<std::unique_ptr<SwerveModuleImpl>> const &)>;

private:
    friend class OdometryThread;

    CANBus _canbus;

    hardware::core::CorePigeon2 _pigeon2;
    StatusSignal<units::degree_t> _pigeonYaw;
    StatusSignal<units::degrees_per_second_t> _pigeonAngularVelocity;

    std::vector<std::unique_ptr<SwerveModuleImpl>> _modules;

    std::vector<Translation2d> _moduleLocations;
    std::vector<SwerveModulePosition> _modulePositions;
    std::vector<SwerveModuleState> _moduleStates;

    SwerveDriveKinematics _kinematics;
    SwerveDrivePoseEstimator _odometry;

    Rotation2d _operatorForwardDirection{};

    SwerveRequestFunc _requestToApply = [](auto&, auto&) { return ctre::phoenix::StatusCode::OK; };
    ControlParameters _requestParameters{};

    mutable std::recursive_mutex _stateLock;
    SwerveDriveState _cachedState{};
    std::function<void(SwerveDriveState const &)> _telemetryFunction{};

    bool _isOnCANFD;
    units::hertz_t _updateFrequency;

    std::unique_ptr<OdometryThread> _odometryThread;

public:
    /**
     * \brief Constructs a CTRE SwerveDrivetrainImpl using the specified constants.
     *
     * This constructs the underlying hardware devices, which can be accessed through
     * getters in the classes.
     *
     * \param drivetrainConstants Drivetrain-wide constants for the swerve drive
     * \param modules             Constants for each specific module
     */
    template <typename DriveMotorConfigsT, typename SteerMotorConfigsT, typename EncoderConfigsT>
    SwerveDrivetrainImpl(
        SwerveDrivetrainConstants const &drivetrainConstants,
        span<SwerveModuleConstants<DriveMotorConfigsT, SteerMotorConfigsT, EncoderConfigsT> const> modules
    ) :
        SwerveDrivetrainImpl{drivetrainConstants, 0_Hz, modules}
    {}

    /**
     * \brief Constructs a CTRE SwerveDrivetrainImpl using the specified constants.
     *
     * This constructs the underlying hardware devices, which can be accessed through
     * getters in the classes.
     *
     * \param drivetrainConstants        Drivetrain-wide constants for the swerve drive
     * \param odometryUpdateFrequency    The frequency to run the odometry loop. If
     *                                   unspecified or set to 0 Hz, this is 250 Hz on
     *                                   CAN FD, and 100 Hz on CAN 2.0.
     * \param modules                    Constants for each specific module
     */
    template <typename DriveMotorConfigsT, typename SteerMotorConfigsT, typename EncoderConfigsT>
    SwerveDrivetrainImpl(
        SwerveDrivetrainConstants const &drivetrainConstants,
        units::hertz_t odometryUpdateFrequency,
        span<SwerveModuleConstants<DriveMotorConfigsT, SteerMotorConfigsT, EncoderConfigsT> const> modules
    ) :
        SwerveDrivetrainImpl{drivetrainConstants, odometryUpdateFrequency, std::array{0.1, 0.1, 0.1}, std::array{0.9, 0.9, 0.9}, modules}
    {}

    /**
     * \brief Constructs a CTRE SwerveDrivetrainImpl using the specified constants.
     *
     * This constructs the underlying hardware devices, which can be accessed through
     * getters in the classes.
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
    template <typename DriveMotorConfigsT, typename SteerMotorConfigsT, typename EncoderConfigsT>
    SwerveDrivetrainImpl(
        SwerveDrivetrainConstants const &drivetrainConstants,
        units::hertz_t odometryUpdateFrequency,
        std::array<double, 3> const &odometryStandardDeviation,
        std::array<double, 3> const &visionStandardDeviation,
        span<SwerveModuleConstants<DriveMotorConfigsT, SteerMotorConfigsT, EncoderConfigsT> const> modules
    );

    /**
     * \brief Gets whether the drivetrain is on a CAN FD bus.
     * 
     * \returns true if on CAN FD
     */
    bool IsOnCANFD() const { return _isOnCANFD; }

    /**
     * \brief Gets the target odometry update frequency.
     * 
     * \returns Target odometry update frequency
     */
    units::hertz_t GetOdometryFrequency() const { return _updateFrequency; }

    /**
     * \brief Gets a reference to the odometry thread.
     *
     * \returns Odometry thread
     */
    OdometryThread &GetOdometryThread() { return *_odometryThread; }

    /**
     * \brief Check if the odometry is currently valid.
     *
     * \returns True if odometry is valid
     */
    bool IsOdometryValid() const
    {
        return _odometryThread->IsOdometryValid();
    }

    /**
     * \brief Gets a reference to the kinematics used for the drivetrain.
     * 
     * \returns Swerve kinematics
     */
    SwerveDriveKinematics const &GetKinematics() const { return _kinematics; }

    /**
     * \brief Applies the specified control function to this swerve drivetrain.
     *
     * \param request Request function to apply
     */
    void SetControl(SwerveRequestFunc &&request)
    {
        std::lock_guard<std::recursive_mutex> lock{_stateLock};
        if (request) {
            _requestToApply = std::move(request);
        } else {
            _requestToApply = [](auto&, auto&) { return ctre::phoenix::StatusCode::OK; };
        }
    }

    /**
     * \brief Immediately runs the provided temporary control function.
     *
     * This is used to accelerate non-native swerve requests and
     * can only be called from the odometry thread. Otherwise,
     * SetControl should be used instead.
     *
     * \param request Request function to invoke
     */
    ctre::phoenix::StatusCode RunTempRequest(SwerveRequestFunc &&request) const
    {
        std::lock_guard<std::recursive_mutex> lock{_stateLock};
        return request(_requestParameters, _modules);
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
        std::lock_guard<std::recursive_mutex> lock{_stateLock};
        return _cachedState;
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
    void RegisterTelemetry(std::function<void(SwerveDriveState const &)> telemetryFunction)
    {
        std::lock_guard<std::recursive_mutex> lock{_stateLock};
        _telemetryFunction = std::move(telemetryFunction);
    }

    /**
     * \brief Configures the neutral mode to use for all modules' drive motors.
     *
     * \param neutralMode The drive motor neutral mode
     * \returns Status code of the first failed config call, or OK if all succeeded
     */
    ctre::phoenix::StatusCode ConfigNeutralMode(signals::NeutralModeValue neutralMode)
    {
        ctre::phoenix::StatusCode retval = ctre::phoenix::StatusCode::OK;
        for (auto &module : _modules) {
            auto status = module->ConfigNeutralMode(neutralMode);
            if (retval.IsOK()) {
                retval = status;
            }
        }
        return retval;
    }

    /**
     * \brief Zero's this swerve drive's odometry entirely.
     *
     * This will zero the entire odometry, and place the robot at 0,0
     */
    void TareEverything()
    {
        std::lock_guard<std::recursive_mutex> lock{_stateLock};

        for (size_t i = 0; i < _modules.size(); ++i) {
            _modules[i]->ResetPosition();
            _modulePositions[i] = _modules[i]->GetPosition(true);
        }
        _odometry.ResetPosition({_pigeonYaw.GetValue()}, _modulePositions, Pose2d{});
        /* We need to update our cached pose immediately to prevent race conditions */
        _cachedState.Pose = _odometry.GetEstimatedPosition();
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
    void SeedFieldCentric()
    {
        ResetRotation(_operatorForwardDirection);
    }

    /**
     * \brief Resets the pose of the robot. The pose should be from the
     * requests#ForwardPerspectiveValue#BlueAlliance perspective.
     *
     * \param pose Pose to make the current pose
     */
    void ResetPose(Pose2d const &pose)
    {
        std::lock_guard<std::recursive_mutex> lock{_stateLock};

        _odometry.ResetPose(pose);
        /* We need to update our cached pose immediately to prevent race conditions */
        _cachedState.Pose = _odometry.GetEstimatedPosition();
    }

    /**
     * \brief Resets the translation of the robot pose without affecting rotation.
     * The translation should be from the requests#ForwardPerspectiveValue#BlueAlliance
     * perspective.
     *
     * \param translation Translation to make the current translation
     */
    void ResetTranslation(Translation2d const &translation)
    {
        std::lock_guard<std::recursive_mutex> lock{_stateLock};

        _odometry.ResetTranslation(translation);
        /* We need to update our cached pose immediately to prevent race conditions */
        _cachedState.Pose = _odometry.GetEstimatedPosition();
    }

    /**
     * \brief Resets the rotation of the robot pose without affecting translation.
     * The rotation should be from the requests#ForwardPerspectiveValue#BlueAlliance
     * perspective.
     *
     * \param rotation Rotation to make the current rotation
     */
    void ResetRotation(Rotation2d const &rotation)
    {
        std::lock_guard<std::recursive_mutex> lock{_stateLock};

        _odometry.ResetRotation(rotation);
        /* We need to update our cached pose immediately to prevent race conditions */
        _cachedState.Pose = _odometry.GetEstimatedPosition();
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
    void SetOperatorPerspectiveForward(Rotation2d fieldDirection)
    {
        std::lock_guard<std::recursive_mutex> lock{_stateLock};
        _operatorForwardDirection = fieldDirection;
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
        std::lock_guard<std::recursive_mutex> lock{_stateLock};
        return _operatorForwardDirection;
    }

    /**
     * \brief Adds a vision measurement to the Kalman Filter. This will correct the
     * odometry pose estimate while still accounting for measurement noise.
     *
     * This method can be called as infrequently as you want, as long as you are
     * calling impl#SwerveDrivePoseEstimator#Update every loop.
     *
     * To promote stability of the pose estimate and make it robust to bad vision
     * data, we recommend only adding vision measurements that are already within
     * one meter or so of the current pose estimate.
     *
     * \param visionRobotPose The pose of the robot as measured by the
     *                        vision camera.
     * \param timestamp       The timestamp of the vision measurement in
     *                        seconds. Note that if you don't use your
     *                        own time source by calling
     *                        impl#SwerveDrivePoseEstimator#UpdateWithTime,
     *                        then you must use a timestamp with an epoch
     *                        since system startup (i.e., the epoch of this
     *                        timestamp is the same epoch as utils#GetCurrentTime).
     *                        This means that you should use utils#GetCurrentTime
     *                        as your time source in this case.
     */
    void AddVisionMeasurement(Pose2d visionRobotPose, units::second_t timestamp)
    {
        std::lock_guard<std::recursive_mutex> lock{_stateLock};
        _odometry.AddVisionMeasurement(visionRobotPose, timestamp);
    }

    /**
     * \brief Adds a vision measurement to the Kalman Filter. This will correct the
     * odometry pose estimate while still accounting for measurement noise.
     *
     * This method can be called as infrequently as you want, as long as you are
     * calling impl#SwerveDrivePoseEstimator#Update every loop.
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
     *                                 seconds. Note that if you don't use your
     *                                 own time source by calling
     *                                 impl#SwerveDrivePoseEstimator#UpdateWithTime,
     *                                 then you must use a timestamp with an epoch
     *                                 since system startup (i.e., the epoch of this
     *                                 timestamp is the same epoch as utils#GetCurrentTime).
     *                                 This means that you should use utils#GetCurrentTime
     *                                 as your time source in this case.
     * \param visionMeasurementStdDevs Standard deviations of the vision pose
     *                                 measurement (x position in meters, y position
     *                                 in meters, and heading in radians). Increase
     *                                 these numbers to trust the vision pose
     *                                 measurement less.
     */
    void AddVisionMeasurement(
        Pose2d visionRobotPose,
        units::second_t timestamp,
        std::array<double, 3> const &visionMeasurementStdDevs)
    {
        std::lock_guard<std::recursive_mutex> lock{_stateLock};
        _odometry.AddVisionMeasurement(visionRobotPose, timestamp, visionMeasurementStdDevs);
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
    void SetVisionMeasurementStdDevs(std::array<double, 3> const &visionMeasurementStdDevs)
    {
        std::lock_guard<std::recursive_mutex> lock{_stateLock};
        _odometry.SetVisionMeasurementStdDevs(visionMeasurementStdDevs);
    }

    /**
     * \brief Sets the pose estimator's trust in robot odometry. This might be used
     * to change trust in odometry after an impact with the wall or traversing a bump.
     *
     * \param stateStdDevs Standard deviations of the pose estimate. Increase these
     *                     numbers to trust your state estimate less. This matrix is
     *                     in the form [x, y, theta]ᵀ, with units in meters and radians.
     */
    void SetStateStdDevs(std::array<double, 3> const &stateStdDevs)
    {
        std::lock_guard<std::recursive_mutex> lock{_stateLock};
        _odometry.SetStateStdDevs(stateStdDevs);
    }

    /**
     * \brief Return the pose at a given timestamp, if the buffer is not empty.
     *
     * \param timestamp The pose's timestamp. Note that if you don't use your
     *                  own time source by calling
     *                  impl#SwerveDrivePoseEstimator#UpdateWithTime,
     *                  then you must use a timestamp with an epoch
     *                  since system startup (i.e., the epoch of this
     *                  timestamp is the same epoch as utils#GetCurrentTime).
     *                  This means that you should use utils#GetCurrentTime
     *                  as your time source in this case.
     * \returns The pose at the given timestamp (or std::nullopt if the buffer is
     * empty).
     */
    std::optional<Pose2d> SamplePoseAt(units::second_t timestamp)
    {
        std::lock_guard<std::recursive_mutex> lock{_stateLock};
        return _odometry.SampleAt(timestamp);
    }

    /**
     * \brief Get a reference to the module at the specified index.
     * The index corresponds to the module described in the constructor.
     *
     * \param index Which module to get
     * \returns Reference to SwerveModuleImpl
     */
    SwerveModuleImpl &GetModule(size_t index) { return *_modules[index]; }
    /**
     * \brief Get a reference to the module at the specified index.
     * The index corresponds to the module described in the constructor.
     *
     * \param index Which module to get
     * \returns Reference to SwerveModuleImpl
     */
    SwerveModuleImpl const &GetModule(size_t index) const { return *_modules[index]; }
    /**
     * \brief Get a reference to the full array of modules.
     * The indexes correspond to the module described in the constructor.
     *
     * \returns Reference to the SwerveModuleImpl array
     */
    std::vector<std::unique_ptr<SwerveModuleImpl>> const &GetModules() const { return _modules; }

    /**
     * \brief Gets the locations of the swerve modules.
     * 
     * \returns Reference to the array of swerve module locations
     */
    std::vector<Translation2d> const &GetModuleLocations() const { return _moduleLocations; }

    /**
     * \brief Gets this drivetrain's Pigeon 2 reference.
     *
     * This should be used only to access signals and change configurations that the
     * swerve drivetrain does not configure itself.
     *
     * \returns This drivetrain's Pigeon 2 reference
     */
    hardware::core::CorePigeon2 &GetPigeon2() { return _pigeon2; }
};

}
}
}
}
