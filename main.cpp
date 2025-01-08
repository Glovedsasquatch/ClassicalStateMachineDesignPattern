#include "src/ModuleProgressReport.h"
#include "src/Config/Config.h"

int main(int argc, char** argv) {
    const Config config("classic_sm_config.json");
    ModuleProgressReport progress_report(config);

    progress_report.begin_module_activity();

    return EXIT_SUCCESS;
}
