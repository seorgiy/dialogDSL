// DSL for localizations files

#include "dialogDSL\core\utility.c"           // iternal helpers
#include "dialogDSL\core\text_utility.c"      // lower/uper register
#include "dialogDSL\core\simple_replace.c"    // replace $shortcut$
#include "dialogDSL\core\functions_replace.c" // replace $func(args)
#include "dialogDSL\defines.c"                // DSL-functions and shorcuts defines here
#include "dialogDSL\helpers.c"                // helpers for localization stuff

// Main function to use from dialog files
string DLGO(string input, ref context)
{
  DLG_EscapeAllChars(&input);            // escape all system chars like \( and \) to {{}}
  DLG_ReplaceSimpleKeys(&input);         // replace all the simple shortcuts like $shortcut
  DLG_RunAllFunctions(&input, &context); // replace all the functions like $func(args)
  DLG_ModifyRegister(&input, "^", 0);    // correcting upper letters like ^letter
  DLG_ModifyRegister(&input, "_", 0);    // correcting lower letters like _letter
  DLG_UnescapeAllChars(&input);          // return all system chars back from {{}} to ()
  return "" + input;
}
