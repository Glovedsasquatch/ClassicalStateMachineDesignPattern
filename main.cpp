#include "src/ModuleProgressReport.h"

int main(int argc, char** argv) {
    ModuleProgressReport progress_report;

    progress_report.progress_module(
        WriteExam,
        Register,
        WriteExam,
        Prepare,
        Prepare,
        WriteExam,
        ResultFail,
        Prepare,
        WriteExam,
        ResultPass,
        Prepare,
        ResultFail
    );

    return EXIT_SUCCESS;
}
