#pragma once

#include <string>

namespace chooser {

struct ChooserHandle;

ChooserHandle* chooser_create();
void chooser_destroy(ChooserHandle* chooser);

void chooser_set_default(ChooserHandle* chooser, const std::string name);
void chooser_add_option(ChooserHandle* chooser, const std::string name);
void chooser_publish(ChooserHandle* chooser, const std::string dashboard_key);

std::string chooser_get_selected(ChooserHandle* chooser);

}  // chooser
