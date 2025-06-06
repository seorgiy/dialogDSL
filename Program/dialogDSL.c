// DSL for localizations files

#include "dialogDSL\simple_replace.c"
#include "dialogDSL\functions_replace.c"

// Main function to use from dialog files
string DLGO(string input, ref context)
{
  DLG_ReplaceSimpleKeys(&input);                 // replace all the simple keys like $key
  input = DLG_RunAllFunctions(&input, &context); // run all the functions like $func(args)
  input = DLG_ModifyRegister(&input, "^");       // correcting upper letters like ^letter
  input = DLG_ModifyRegister(&input, "_");       // correcting lower letters like _letter

  return "" + input;
}

string DLG_ModifyRegister(string input, string key)
{
  int markPos = FindSubStr(input, key , 0);
  if (markPos < 0) return "" + input;

  string start   = "";
  string end     = "";
  string replace = strcut(input, markPos+1, markPos+2);
  if (key == "^") replace = ToUpper(replace);
  else replace = GetStrSmallRegister(replace);

  if (markPos > 0) start = strcut(input, 0, markPos-1);
  end = strcut(input, markPos+2, strlen(&input)-1);

  return DLG_ModifyRegister(start + replace + end, &key); // looking for the next replacement
}
