#include "plugin.h"
#include "OneDimTwoDim.h"
#include <cedar/processing/ElementDeclaration.h>

void pluginDeclaration(cedar::aux::PluginDeclarationListPtr plugin)
{
    cedar::proc::ElementDeclarationPtr summation_decl
    (
        new cedar::proc::ElementDeclarationTemplate <OneDimTwoDim>("Utilities")
    );
    plugin->add(summation_decl);
}
