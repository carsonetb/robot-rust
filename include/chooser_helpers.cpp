#include "chooser_helpers.hpp"
#include <frc/smartdashboard/SendableChooser.h>
#include <frc/smartdashboard/SmartDashboard.h>

namespace chooser {

struct ChooserHandle {
    frc::SendableChooser<std::string> chooser;
};

ChooserHandle* chooser_create() {
    return new ChooserHandle();
}

void chooser_destroy(ChooserHandle *chooser) {
    delete chooser;
}

void chooser_set_default(ChooserHandle *chooser, const std::string name) {
    chooser->chooser.SetDefaultOption(name, name);
}

void chooser_add_option(ChooserHandle *chooser, const std::string name) {
    chooser->chooser.AddOption(name, name);
}

void chooser_publish(ChooserHandle *chooser, const std::string name) {
    frc::SmartDashboard::PutData(name, &chooser->chooser);
}

std::string chooser_get_selected(ChooserHandle *chooser) {
    return chooser->chooser.GetSelected();
}

}
