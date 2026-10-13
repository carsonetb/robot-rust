#include "rev_helpers.hpp"
#include "rev/ConfigureTypes.h"
#include "rev/config/AbsoluteEncoderConfig.h"
#include "rev/config/AnalogSensorConfig.h"
#include "rev/config/ClosedLoopConfig.h"
#include "rev/config/EncoderConfig.h"
#include "rev/config/SparkBaseConfig.h"

namespace rev_helpers {

namespace spark {

struct SparkConfigWrapper {
    rev::spark::SparkBaseConfig config;

    public:

        SparkConfigWrapper() = default;
        SparkConfigWrapper(rev::spark::SparkBaseConfig config): config{config} {}
};

void configure(rev::spark::SparkMax &motor, SparkConfigWrapper *config, rev::ResetMode reset, rev::PersistMode persist) {
    motor.Configure(config->config, reset, persist);
}

SparkConfigWrapper* config_create() {
    return new SparkConfigWrapper();
}

void config_delete(SparkConfigWrapper *config) {
    delete config;
}

SparkConfigWrapper* config_neo() {
    return new SparkConfigWrapper(rev::spark::SparkBaseConfig::Presets::REV_NEO());
}

SparkConfigWrapper* config_neo_2() {
    return new SparkConfigWrapper(rev::spark::SparkBaseConfig::Presets::REV_NEO_2());
}

SparkConfigWrapper* config_neo_550() {
    return new SparkConfigWrapper(rev::spark::SparkBaseConfig::Presets::REV_NEO_550());
}

SparkConfigWrapper* config_vortex() {
    return new SparkConfigWrapper(rev::spark::SparkBaseConfig::Presets::REV_Vortex());
}

SparkConfigWrapper* config_ctre_minion() {
    return new SparkConfigWrapper(rev::spark::SparkBaseConfig::Presets::CTRE_Minion());
}

void apply_absolute_encoder(SparkConfigWrapper* wrapper, rev::spark::AbsoluteEncoderConfig& config) {
    wrapper->config.Apply(config);
}

void apply_analog_sensor(SparkConfigWrapper* wrapper, rev::spark::AnalogSensorConfig& config) {
    wrapper->config.Apply(config);
}

void apply_encoder(SparkConfigWrapper* wrapper, rev::spark::EncoderConfig& config) {
    wrapper->config.Apply(config);
}

void apply_closed_loop(SparkConfigWrapper* wrapper, rev::spark::ClosedLoopConfig& config) {
    wrapper->config.Apply(config);
}

}

}  // namespace rev_helpers
