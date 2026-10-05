/*
 * Copyright (C) Cross The Road Electronics.  All rights reserved.
 * License information can be found in CTRE_LICENSE.txt
 * For support and suggestions contact support@ctr-electronics.com or file
 * an issue tracker at https://github.com/CrossTheRoadElec/Phoenix-Releases
 */
#pragma once

#include "ctre/phoenix6/core/CorePigeon2.hpp"
#include "ctre/phoenix6/swerve/impl/SwerveDriveKinematics.hpp"
#include "ctre/phoenix6/swerve/SwerveModule.hpp"
#include <frc/simulation/DCMotorSim.h>
#include <frc/system/plant/LinearSystemId.h>

namespace ctre {
namespace phoenix6 {
namespace swerve {

/**
 * \brief Simplified swerve drive simulation class.
 *
 * This class assumes that the swerve drive is perfect, meaning
 * that there is no scrub and the wheels do not slip.
 *
 * In addition, it assumes the inertia of the robot is governed only
 * by the inertia of the steer module and the individual drive wheels.
 * Robot-wide inertia is not accounted for, and neither is translational
 * vs rotational inertia of the robot.
 *
 * These assumptions provide a simplified example that can demonstrate the
 * behavior of a swerve drive in simulation. Users are encouraged to
 * expand this model for their own use.
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
class SimSwerveDrivetrain {
protected:
    class SimSwerveModule {
    public:
        /** \brief Reference to motor simulation for drive motor */
        frc::sim::DCMotorSim DriveMotor;
        /** \brief Reference to motor simulation for the steer motor */
        frc::sim::DCMotorSim SteerMotor;
        /** \brief Reference to steer gearing for updating encoder */
        units::scalar_t DriveGearing;
        /** \brief Reference to steer gearing for updating encoder */
        units::scalar_t SteerGearing;
        /** \brief Voltage necessary for the drive motor to overcome friction */
        units::volt_t DriveFrictionVoltage;
        /** \brief Voltage necessary for the steer motor to overcome friction */
        units::volt_t SteerFrictionVoltage;
        /** \brief Whether the drive motor is inverted */
        bool DriveMotorInverted;
        /** \brief Whether the steer motor is inverted */
        bool SteerMotorInverted;
        /** \brief Whether the azimuth encoder is inverted */
        bool EncoderInverted;
        /** \brief The type of encoder to use for the azimuth */
        SteerFeedbackType EncoderType;

        SimSwerveModule(
            units::scalar_t driveGearing, units::kilogram_square_meter_t driveInertia,
            units::volt_t driveFrictionVoltage, bool driveMotorInverted,
            DriveMotorArrangement driveMotorType,
            units::scalar_t steerGearing, units::kilogram_square_meter_t steerInertia,
            units::volt_t steerFrictionVoltage, bool steerMotorInverted,
            SteerMotorArrangement steerMotorType,
            bool encoderInverted,
            SteerFeedbackType encoderType
        ) :
            DriveMotor{frc::LinearSystemId::DCMotorSystem(GetDriveMotorGearbox(driveMotorType), driveInertia, driveGearing), GetDriveMotorGearbox(driveMotorType)},
            SteerMotor{frc::LinearSystemId::DCMotorSystem(GetSteerMotorGearbox(steerMotorType), steerInertia, steerGearing), GetSteerMotorGearbox(steerMotorType)},
            DriveGearing{driveGearing},
            SteerGearing{steerGearing},
            DriveFrictionVoltage{driveFrictionVoltage},
            SteerFrictionVoltage{steerFrictionVoltage},
            DriveMotorInverted{driveMotorInverted},
            SteerMotorInverted{steerMotorInverted},
            EncoderInverted{encoderInverted},
            EncoderType{encoderType}
        {}

        static frc::DCMotor GetDriveMotorGearbox(DriveMotorArrangement driveMotorType)
        {
            switch (driveMotorType) {
                case DriveMotorArrangement::TalonFX_Integrated:
                default:
                    return frc::DCMotor::KrakenX60FOC(1);
                case DriveMotorArrangement::TalonFXS_NEO_JST:
                    return frc::DCMotor::NEO(1);
                case DriveMotorArrangement::TalonFXS_VORTEX_JST:
                    return frc::DCMotor::NeoVortex(1);
            }
        }

        static frc::DCMotor GetSteerMotorGearbox(SteerMotorArrangement steerMotorType)
        {
            switch (steerMotorType) {
                case SteerMotorArrangement::TalonFX_Integrated:
                default:
                    return frc::DCMotor::KrakenX60FOC(1);
                case SteerMotorArrangement::TalonFXS_Minion_JST:
                    return frc::DCMotor{12_V, 3.1_Nm, 202_A, 4_A, 774_rad_per_s, 1};
                case SteerMotorArrangement::TalonFXS_NEO_JST:
                    return frc::DCMotor::NEO(1);
                case SteerMotorArrangement::TalonFXS_VORTEX_JST:
                    return frc::DCMotor::NeoVortex(1);
                case SteerMotorArrangement::TalonFXS_NEO550_JST:
                    return frc::DCMotor::NEO550(1);
                case SteerMotorArrangement::TalonFXS_Brushed_AB:
                case SteerMotorArrangement::TalonFXS_Brushed_AC:
                case SteerMotorArrangement::TalonFXS_Brushed_BC:
                    return frc::DCMotor::CIM(1);
            }
        }
    };

    sim::Pigeon2SimState &_pigeonSim;
    std::vector<SimSwerveModule> _modules;

    impl::SwerveDriveKinematics _kinem;
    Rotation2d _lastAngle{};

public:
    template <
        typename... ModuleConstants,
        typename = std::enable_if_t<std::conjunction_v<
            std::is_same<
                ModuleConstants,
                SwerveModuleConstants<typename DriveMotorT::Configuration, typename SteerMotorT::Configuration, typename EncoderT::Configuration>
            >...
        >>
    >
    SimSwerveDrivetrain(
        std::vector<Translation2d> wheelLocations,
        sim::Pigeon2SimState &pigeonSim,
        ModuleConstants const &... moduleConstants
    ) :
        _pigeonSim{pigeonSim},
        _modules{
            SimSwerveModule{
                moduleConstants.DriveMotorGearRatio,
                moduleConstants.DriveInertia,
                moduleConstants.DriveFrictionVoltage,
                moduleConstants.DriveMotorInverted,
                moduleConstants.DriveMotorType,
                moduleConstants.SteerMotorGearRatio,
                moduleConstants.SteerInertia,
                moduleConstants.SteerFrictionVoltage,
                moduleConstants.SteerMotorInverted,
                moduleConstants.SteerMotorType,
                moduleConstants.EncoderInverted,
                moduleConstants.FeedbackSource
            }...
        },
        _kinem{std::move(wheelLocations)}
    {}

    void Update(
        units::second_t dt,
        units::volt_t supplyVoltage,
        std::vector<std::unique_ptr<SwerveModule<DriveMotorT, SteerMotorT, EncoderT>>> const &modulesToApply
    ) {
        if (modulesToApply.size() != _modules.size()) return;

        std::vector<SwerveModuleState> states(modulesToApply.size());
        /* update our sim devices */
        for (size_t i = 0; i < modulesToApply.size(); ++i) {
            auto &driveMotor = modulesToApply[i]->GetDriveMotor().GetSimState();
            auto &steerMotor = modulesToApply[i]->GetSteerMotor().GetSimState();
            auto &encoder = modulesToApply[i]->GetEncoder().GetSimState();

            if constexpr (std::is_same_v<hardware::TalonFXS, DriveMotorT>) {
                driveMotor.MotorOrientation = _modules[i].DriveMotorInverted ? sim::ChassisReference::Clockwise_Positive : sim::ChassisReference::CounterClockwise_Positive;
            } else {
                driveMotor.Orientation = _modules[i].DriveMotorInverted ? sim::ChassisReference::Clockwise_Positive : sim::ChassisReference::CounterClockwise_Positive;
            }

            if constexpr (std::is_same_v<hardware::TalonFXS, SteerMotorT>) {
                steerMotor.MotorOrientation = _modules[i].SteerMotorInverted ? sim::ChassisReference::Clockwise_Positive : sim::ChassisReference::CounterClockwise_Positive;
                steerMotor.ExtSensorOrientation = _modules[i].SteerMotorInverted != _modules[i].EncoderInverted ? sim::ChassisReference::Clockwise_Positive : sim::ChassisReference::CounterClockwise_Positive;
            } else {
                steerMotor.Orientation = _modules[i].SteerMotorInverted ? sim::ChassisReference::Clockwise_Positive : sim::ChassisReference::CounterClockwise_Positive;
            }

            if constexpr (std::is_same_v<hardware::CANcoder, EncoderT>) {
                encoder.Orientation = _modules[i].EncoderInverted ? sim::ChassisReference::Clockwise_Positive : sim::ChassisReference::CounterClockwise_Positive;
            }

            driveMotor.SetSupplyVoltage(supplyVoltage);
            steerMotor.SetSupplyVoltage(supplyVoltage);
            encoder.SetSupplyVoltage(supplyVoltage);

            _modules[i].DriveMotor.SetInputVoltage(AddFriction(driveMotor.GetMotorVoltage(), _modules[i].DriveFrictionVoltage));
            _modules[i].SteerMotor.SetInputVoltage(AddFriction(steerMotor.GetMotorVoltage(), _modules[i].SteerFrictionVoltage));

            _modules[i].DriveMotor.Update(dt);
            _modules[i].SteerMotor.Update(dt);

            driveMotor.SetRawRotorPosition(_modules[i].DriveMotor.GetAngularPosition() * _modules[i].DriveGearing);
            driveMotor.SetRotorVelocity(_modules[i].DriveMotor.GetAngularVelocity() * _modules[i].DriveGearing);

            steerMotor.SetRawRotorPosition(_modules[i].SteerMotor.GetAngularPosition() * _modules[i].SteerGearing);
            steerMotor.SetRotorVelocity(_modules[i].SteerMotor.GetAngularVelocity() * _modules[i].SteerGearing);
            if constexpr (std::is_same_v<hardware::TalonFXS, SteerMotorT>) {
                /* azimuth encoders see the mechanism, so don't account for the steer gearing */
                steerMotor.SetPulseWidthPosition(_modules[i].SteerMotor.GetAngularPosition());
                steerMotor.SetPulseWidthVelocity(_modules[i].SteerMotor.GetAngularVelocity());
            }

            if constexpr (std::is_same_v<hardware::CANcoder, EncoderT>) {
                /* azimuth encoders see the mechanism, so don't account for the steer gearing */
                encoder.SetRawPosition(_modules[i].SteerMotor.GetAngularPosition());
                encoder.SetVelocity(_modules[i].SteerMotor.GetAngularVelocity());
            } else if constexpr (std::is_same_v<hardware::CANdi, EncoderT>) {
                switch (_modules[i].EncoderType) {
                    case SteerFeedbackType::FusedCANdiPWM1:
                    case SteerFeedbackType::SyncCANdiPWM1:
                    case SteerFeedbackType::RemoteCANdiPWM1:
                        encoder.Pwm1Orientation = _modules[i].EncoderInverted ? sim::ChassisReference::Clockwise_Positive : sim::ChassisReference::CounterClockwise_Positive;

                        /* azimuth encoders see the mechanism, so don't account for the steer gearing */
                        encoder.SetPwm1Connected(true);
                        encoder.SetPwm1Position(_modules[i].SteerMotor.GetAngularPosition());
                        encoder.SetPwm1Velocity(_modules[i].SteerMotor.GetAngularVelocity());
                        break;

                    case SteerFeedbackType::FusedCANdiPWM2:
                    case SteerFeedbackType::SyncCANdiPWM2:
                    case SteerFeedbackType::RemoteCANdiPWM2:
                        encoder.Pwm2Orientation = _modules[i].EncoderInverted ? sim::ChassisReference::Clockwise_Positive : sim::ChassisReference::CounterClockwise_Positive;

                        /* azimuth encoders see the mechanism, so don't account for the steer gearing */
                        encoder.SetPwm2Connected(true);
                        encoder.SetPwm2Position(_modules[i].SteerMotor.GetAngularPosition());
                        encoder.SetPwm2Velocity(_modules[i].SteerMotor.GetAngularVelocity());
                        break;

                    default:
                        break;
                }
            }

            states[i] = modulesToApply[i]->GetCurrentState();
        }

        auto const angularVel = _kinem.ToChassisSpeeds(states).omega;
        _lastAngle = _lastAngle + Rotation2d{angularVel * dt};
        _pigeonSim.SetRawYaw(_lastAngle.Degrees());
        _pigeonSim.SetAngularVelocityZ(angularVel);
    }

protected:
    /**
     * \brief Applies the effects of friction to dampen the motor voltage.
     *
     * \param motorVoltage Voltage output by the motor
     * \param frictionVoltage Voltage required to overcome friction
     * \returns Friction-dampened motor voltage
     */
    static units::volt_t AddFriction(units::volt_t motorVoltage, units::volt_t frictionVoltage)
    {
        if (units::math::abs(motorVoltage) < frictionVoltage) {
            motorVoltage = 0_V;
        } else if (motorVoltage > 0_V) {
            motorVoltage -= frictionVoltage;
        } else {
            motorVoltage += frictionVoltage;
        }
        return motorVoltage;
    }
};

}
}
}
