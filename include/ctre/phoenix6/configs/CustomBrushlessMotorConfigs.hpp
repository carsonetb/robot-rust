/*
 * Copyright (C) Cross The Road Electronics.  All rights reserved.
 * License information can be found in CTRE_LICENSE.txt
 * For support and suggestions contact support@ctr-electronics.com or file
 * an issue tracker at https://github.com/CrossTheRoadElec/Phoenix-Releases
 */
#pragma once

#include "ctre/phoenix6/configs/Configuration.hpp"
#include "ctre/unit/motor_constants.h"

namespace ctre {
namespace phoenix6 {


namespace configs {

/**
 * \brief Configs related to using a custom brushless motor that is
 *        not formally supported by Talon FXS.
 * 
 * \details Configs are only used when Motor Arrangement is set to
 *          Custom Brushless Motor.  Note this feature will only work
 *          device is not FRC-Locked.
 *          
 *          Users are responsible for ensuring that these configs are
 *          accurate to the motor. CTR Electronics is not responsible
 *          for damage caused by an incorrect custom motor
 *          configuration.
 */
class CustomBrushlessMotorConfigs : public ParentConfiguration {
public:
    constexpr CustomBrushlessMotorConfigs() = default;

    /**
     * \brief Kv constant of the connected custom brushless motor. This
     * can usually be determined by consulting the motor manufacturer data
     * sheet.
     * 
     * - Minimum Value: 0
     * - Maximum Value: 2047
     * - Default Value: 500
     * - Units: RPM/V
     */
    ctre::unit::rpm_per_volt_t MotorKv = 500_rpm / 1_V;
    /**
     * \brief Number of pole pairs in the connected custom brushless motor
     * (number of poles divided by 2). This can usually be determined by
     * consulting the motor manufacturer data sheet.
     * 
     * \details For example, if motor has ten poles, then specify five
     * pole pairs.
     * 
     * - Minimum Value: 1
     * - Maximum Value: 8
     * - Default Value: 1
     * - Units: 
     */
    int PolePairCount = 1;
    /**
     * \brief Expected Hall Value when motor controller applies A+ and B-.
     * 
     * \details Hall Values are little endian [CBA].  For example, if
     * halls report: HA=0, HB=0, HC=1, then the Hall Value is 4.
     * 
     * - Minimum Value: 0
     * - Maximum Value: 6
     * - Default Value: 0
     * - Units: 
     */
    int HallDuringAB = 0;
    /**
     * \brief Expected Hall Value when motor controller applies A+ and C-.
     * 
     * \details Hall Values are little endian [CBA].  For example, if
     * halls report: HA=0, HB=0, HC=1, then the Hall Value is 4.
     * 
     * - Minimum Value: 0
     * - Maximum Value: 6
     * - Default Value: 0
     * - Units: 
     */
    int HallDuringAC = 0;
    /**
     * \brief Optional configuration to correct clockwise versus
     * counter-clockwise rotor spin.
     * 
     * \details Depending on the mechanical design of the motor, rotor may
     * spin clockwise during positive output when Inverted is set to
     * counterclockwise.  This configuration can be toggled so that the
     * rest of the API is canonically true.
     * 
     * - Default Value: False
     */
    bool HallCCWSelect = false;
    /**
     * \brief Determines expected Hall direction for rotor velocity
     * signage.
     * 
     * \details If RotorVelocity is signed opposite of applied voltage,
     * flip this configuration.
     * 
     * - Default Value: False
     */
    bool HallDirection = false;
    
    /**
     * \brief Modifies this configuration's MotorKv parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Kv constant of the connected custom brushless motor. This can
     * usually be determined by consulting the motor manufacturer data
     * sheet.
     * 
     * - Minimum Value: 0
     * - Maximum Value: 2047
     * - Default Value: 500
     * - Units: RPM/V
     *
     * \param newMotorKv Parameter to modify
     * \returns Itself
     */
    constexpr CustomBrushlessMotorConfigs &WithMotorKv(ctre::unit::rpm_per_volt_t newMotorKv)
    {
        MotorKv = std::move(newMotorKv);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's PolePairCount parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Number of pole pairs in the connected custom brushless motor
     * (number of poles divided by 2). This can usually be determined by
     * consulting the motor manufacturer data sheet.
     * 
     * \details For example, if motor has ten poles, then specify five
     * pole pairs.
     * 
     * - Minimum Value: 1
     * - Maximum Value: 8
     * - Default Value: 1
     * - Units: 
     *
     * \param newPolePairCount Parameter to modify
     * \returns Itself
     */
    constexpr CustomBrushlessMotorConfigs &WithPolePairCount(int newPolePairCount)
    {
        PolePairCount = std::move(newPolePairCount);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's HallDuringAB parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Expected Hall Value when motor controller applies A+ and B-.
     * 
     * \details Hall Values are little endian [CBA].  For example, if
     * halls report: HA=0, HB=0, HC=1, then the Hall Value is 4.
     * 
     * - Minimum Value: 0
     * - Maximum Value: 6
     * - Default Value: 0
     * - Units: 
     *
     * \param newHallDuringAB Parameter to modify
     * \returns Itself
     */
    constexpr CustomBrushlessMotorConfigs &WithHallDuringAB(int newHallDuringAB)
    {
        HallDuringAB = std::move(newHallDuringAB);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's HallDuringAC parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Expected Hall Value when motor controller applies A+ and C-.
     * 
     * \details Hall Values are little endian [CBA].  For example, if
     * halls report: HA=0, HB=0, HC=1, then the Hall Value is 4.
     * 
     * - Minimum Value: 0
     * - Maximum Value: 6
     * - Default Value: 0
     * - Units: 
     *
     * \param newHallDuringAC Parameter to modify
     * \returns Itself
     */
    constexpr CustomBrushlessMotorConfigs &WithHallDuringAC(int newHallDuringAC)
    {
        HallDuringAC = std::move(newHallDuringAC);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's HallCCWSelect parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Optional configuration to correct clockwise versus
     * counter-clockwise rotor spin.
     * 
     * \details Depending on the mechanical design of the motor, rotor may
     * spin clockwise during positive output when Inverted is set to
     * counterclockwise.  This configuration can be toggled so that the
     * rest of the API is canonically true.
     * 
     * - Default Value: False
     *
     * \param newHallCCWSelect Parameter to modify
     * \returns Itself
     */
    constexpr CustomBrushlessMotorConfigs &WithHallCCWSelect(bool newHallCCWSelect)
    {
        HallCCWSelect = std::move(newHallCCWSelect);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's HallDirection parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Determines expected Hall direction for rotor velocity signage.
     * 
     * \details If RotorVelocity is signed opposite of applied voltage,
     * flip this configuration.
     * 
     * - Default Value: False
     *
     * \param newHallDirection Parameter to modify
     * \returns Itself
     */
    constexpr CustomBrushlessMotorConfigs &WithHallDirection(bool newHallDirection)
    {
        HallDirection = std::move(newHallDirection);
        return *this;
    }

    

    std::string ToString() const override;

    std::string Serialize() const final;
    ctre::phoenix::StatusCode Deserialize(std::string const &to_deserialize) final;
};

}
}
}
