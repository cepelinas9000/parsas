#include "ParsasApp.h"
#include "Moose.h"
#include "AppFactory.h"
#include "ModulesApp.h"

template<>
InputParameters validParams<ParsasApp>()
{
  InputParameters params = validParams<MooseApp>();

  params.set<bool>("use_legacy_uo_initialization") = false;
  params.set<bool>("use_legacy_uo_aux_computation") = false;
  return params;
}

ParsasApp::ParsasApp(const std::string & name, InputParameters parameters) :
    MooseApp(name, parameters)
{
  srand(processor_id());

  Moose::registerObjects(_factory);
  ModulesApp::registerObjects(_factory);
  ParsasApp::registerObjects(_factory);

  Moose::associateSyntax(_syntax, _action_factory);
  ModulesApp::associateSyntax(_syntax, _action_factory);
  ParsasApp::associateSyntax(_syntax, _action_factory);
}

ParsasApp::~ParsasApp()
{
}

// External entry point for dynamic application loading
extern "C" void ParsasApp__registerApps() { ParsasApp::registerApps(); }
void
ParsasApp::registerApps()
{
  registerApp(ParsasApp);
}

// External entry point for dynamic object registration
extern "C" void ParsasApp__registerObjects(Factory & factory) { ParsasApp::registerObjects(factory); }
void
ParsasApp::registerObjects(Factory & factory)
{
}

// External entry point for dynamic syntax association
extern "C" void ParsasApp__associateSyntax(Syntax & syntax, ActionFactory & action_factory) { ParsasApp::associateSyntax(syntax, action_factory); }
void
ParsasApp::associateSyntax(Syntax & syntax, ActionFactory & action_factory)
{
}
