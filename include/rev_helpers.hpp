#pragma once

#include <memory>
#include "rev/ConfigureTypes.h"
#include "rev/REVLibError.h"
#include "rev/SparkAbsoluteEncoder.h"
#include "rev/SparkLowLevel.h"
#include "rev/SparkMax.h"
#include "rev/SparkRelativeEncoder.h"
#include "units/voltage.h"

namespace rev_helpers {

namespace spark {

inline std::unique_ptr<rev::spark::SparkMax> create(int can_id, int motor_type) {
    return std::make_unique<rev::spark::SparkMax>(rev::spark::SparkMax(can_id, rev::spark::SparkLowLevel::MotorType{motor_type}));
}

inline void set(rev::spark::SparkMax& spark, double speed) {
    spark.Set(speed);
}

inline void set_voltage(rev::spark::SparkMax& spark, double voltage) {
    spark.SetVoltage(units::voltage::volt_t{voltage});
}

inline void disable(rev::spark::SparkMax& spark) {
    spark.Disable();
}

inline void stop(rev::spark::SparkMax& spark) {
    spark.StopMotor();
}

inline double get(rev::spark::SparkMax& spark) {
    return spark.Get();
}

inline rev::spark::SparkRelativeEncoder& get_encoder(rev::spark::SparkMax& spark) {
    return spark.GetEncoder();
}

inline rev::spark::SparkAbsoluteEncoder& get_absolute_encoder(rev::spark::SparkMax& spark) {
    return spark.GetAbsoluteEncoder();
}

inline double get_applied_output(rev::spark::SparkMax& spark) {
    return spark.GetAppliedOutput();
}

inline double get_bus_voltage(rev::spark::SparkMax& spark) {
    return spark.GetBusVoltage();
}

inline double get_output_current(rev::spark::SparkMax& spark) {
    return spark.GetOutputCurrent();
}

inline double get_motor_temperature(rev::spark::SparkMax& spark) {
    return spark.GetMotorTemperature();
}

inline double get_position(rev::spark::SparkRelativeEncoder& enc) {
    return enc.GetPosition();
}

inline double get_velocity(rev::spark::SparkRelativeEncoder& enc) {
    return enc.GetVelocity();
}

inline rev::REVLibError set_position(rev::spark::SparkRelativeEncoder& enc, double position) {
    return enc.SetPosition(position);
}

inline double absolute_get_position(rev::spark::SparkAbsoluteEncoder& enc) {
    return enc.GetPosition();
}

inline double absolute_get_velocity(rev::spark::SparkAbsoluteEncoder& enc) {
    return enc.GetVelocity();
}

struct SparkConfigWrapper;

void configure(rev::spark::SparkMax& motor, SparkConfigWrapper* config, rev::ResetMode reset, rev::PersistMode persist);

SparkConfigWrapper* config_create();
void config_delete(SparkConfigWrapper* config);
SparkConfigWrapper* config_neo();
SparkConfigWrapper* config_neo_2();
SparkConfigWrapper* config_neo_550();
SparkConfigWrapper* config_vortex();
SparkConfigWrapper* config_ctre_minion();
void apply_absolute_encoder(SparkConfigWrapper* wrapper, rev::spark::AbsoluteEncoderConfig& config);
void apply_analog_sensor(SparkConfigWrapper* wrapper, rev::spark::AnalogSensorConfig& config);
void apply_encoder(SparkConfigWrapper* wrapper, rev::spark::EncoderConfig& config);
void apply_closed_loop(SparkConfigWrapper* wrapper, rev::spark::ClosedLoopConfig& config);
void apply_inverted(SparkConfigWrapper* wrapper, bool inverted);
void apply_idle_mode(SparkConfigWrapper* wrapper, uint32_t mode);

}

}  // namespace rev_helpers
