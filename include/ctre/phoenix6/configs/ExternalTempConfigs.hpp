/*
 * Copyright (C) Cross The Road Electronics.  All rights reserved.
 * License information can be found in CTRE_LICENSE.txt
 * For support and suggestions contact support@ctr-electronics.com or file
 * an issue tracker at https://github.com/CrossTheRoadElec/Phoenix-Releases
 */
#pragma once

#include "ctre/phoenix6/configs/Configuration.hpp"
#include "ctre/phoenix6/signals/SpnEnums.hpp"
#include <units/impedance.h>
#include <units/temperature.h>

namespace ctre {
namespace phoenix6 {


namespace configs {

/**
 * \brief Configs related to using an independent thermister for
 *        automatically disabling a motor when a threshold has been
 *        reached.
 * 
 * \details Configs are only used when Motor Arrangement is set to
 *          Custom Brushless Motor or Brushed.  Note this feature will
 *          only work device is not FRC-Locked.
 *          
 *          Users are responsible for ensuring that these configs are
 *          accurate to the motor. CTR Electronics is not responsible
 *          for damage caused by an incorrect custom motor
 *          configuration.
 */
class ExternalTempConfigs : public ParentConfiguration {
public:
    constexpr ExternalTempConfigs() = default;

    /**
     * \brief Threshold for thermal faulting a custom motor.
     * 
     * \details The motor controller will fault if the connected motor
     * thermistor exceeds this value.
     * 
     * - Minimum Value: 0
     * - Maximum Value: 150
     * - Default Value: 0
     * - Units: ℃
     */
    units::temperature::celsius_t ThermistorMaxTemperature = 0_degC;
    /**
     * \brief Beta K value for the connected NTC thermistor. This can
     * usually be determined by consulting the motor manufacturer data
     * sheet.
     * 
     * - Minimum Value: 0
     * - Maximum Value: 8000
     * - Default Value: 0
     * - Units: K
     */
    units::temperature::kelvin_t ThermistorBeta = 0_K;
    /**
     * \brief The thermistor resistance for the connected NTC thermistor
     * as measured at 25'C. This can usually be determined by consulting
     * the motor manufacturer data sheet.
     * 
     * - Minimum Value: 0
     * - Maximum Value: 400
     * - Default Value: 0
     * - Units: kOhm
     */
    units::impedance::kiloohm_t ThermistorR0 = 0_kOhm;
    /**
     * \brief Whether a temperature sensor should be required for motor
     * control. This configuration is ignored in FRC environments and
     * defaults to Required.
     * 
     */
    signals::TempSensorRequiredValue TempSensorRequired = signals::TempSensorRequiredValue::Required;
    
    /**
     * \brief Modifies this configuration's ThermistorMaxTemperature parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Threshold for thermal faulting a custom motor.
     * 
     * \details The motor controller will fault if the connected motor
     * thermistor exceeds this value.
     * 
     * - Minimum Value: 0
     * - Maximum Value: 150
     * - Default Value: 0
     * - Units: ℃
     *
     * \param newThermistorMaxTemperature Parameter to modify
     * \returns Itself
     */
    constexpr ExternalTempConfigs &WithThermistorMaxTemperature(units::temperature::celsius_t newThermistorMaxTemperature)
    {
        ThermistorMaxTemperature = std::move(newThermistorMaxTemperature);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's ThermistorBeta parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Beta K value for the connected NTC thermistor. This can usually be
     * determined by consulting the motor manufacturer data sheet.
     * 
     * - Minimum Value: 0
     * - Maximum Value: 8000
     * - Default Value: 0
     * - Units: K
     *
     * \param newThermistorBeta Parameter to modify
     * \returns Itself
     */
    constexpr ExternalTempConfigs &WithThermistorBeta(units::temperature::kelvin_t newThermistorBeta)
    {
        ThermistorBeta = std::move(newThermistorBeta);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's ThermistorR0 parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * The thermistor resistance for the connected NTC thermistor as
     * measured at 25'C. This can usually be determined by consulting the
     * motor manufacturer data sheet.
     * 
     * - Minimum Value: 0
     * - Maximum Value: 400
     * - Default Value: 0
     * - Units: kOhm
     *
     * \param newThermistorR0 Parameter to modify
     * \returns Itself
     */
    constexpr ExternalTempConfigs &WithThermistorR0(units::impedance::kiloohm_t newThermistorR0)
    {
        ThermistorR0 = std::move(newThermistorR0);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's TempSensorRequired parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Whether a temperature sensor should be required for motor control.
     * This configuration is ignored in FRC environments and defaults to
     * Required.
     * 
     *
     * \param newTempSensorRequired Parameter to modify
     * \returns Itself
     */
    constexpr ExternalTempConfigs &WithTempSensorRequired(signals::TempSensorRequiredValue newTempSensorRequired)
    {
        TempSensorRequired = std::move(newTempSensorRequired);
        return *this;
    }

    

    std::string ToString() const override;

    std::string Serialize() const final;
    ctre::phoenix::StatusCode Deserialize(std::string const &to_deserialize) final;
};

}
}
}
