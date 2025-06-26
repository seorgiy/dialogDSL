// There we injecting dynamic dialogs on the fly
#include "dialogDSL\dynamic_dialog\utility.c"

#event_handler("DialogEvent", "DLG_DialogContinue");
#event_handler(EVENT_DIALOG_START, "DLG_DialogStart");

void DLG_DialogStart()
{
  PostEvent("DLG_DialogStart", 0);
}

void DLG_DialogContinue()
{
  PostEvent("DLG_DialogContinue", 0);
}
