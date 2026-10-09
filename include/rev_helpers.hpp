#pragma once

#include <memory>

namespace rev_helpers {

struct NeoHandle;

NeoHandle* neo_create(int can_id);
void neo_set(NeoHandle* motor, double speed);
void neo_set_voltage(NeoHandle* motor, double voltage);
void neo_destroy(NeoHandle* motor);

}  // namespace rev_helpers
