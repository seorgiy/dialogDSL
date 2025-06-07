// Functions
// $func(args) → result

// Looking for the functions call in the input
void DLG_RunAllFunctions(string input, ref context)
{
  int startFuncIdx = FindSubStr(input, "$" , 0);
  int endFuncIdx   = FindSubStr(input, ")" , 0);
  int startArgsIdx = FindSubStr(input, "(" , 0);
  if (startFuncIdx < 0 || endFuncIdx < 0 || startArgsIdx < 0) return; // all replacements are made

  int startPos;
  int endPos;
  int length = strlen(&input);
  DLG_FindNestedFunction(input, length, &startPos, &endPos);

  string start   = "";
  string end     = "";
  if (startPos < 0) return "" + input; // no inner function found

  string innerFunction = strcut(input, startPos, endPos);

  if (startPos > 0) start = strcut(input, 0, startPos-1);
  if (endPos+1 < length) end = strcut(input, endPos+1, length-1);

  input = start + DLG_RunFunction(innerFunction, &context) + end;
  DLG_RunAllFunctions(&input, &context)
}

// Looking for another $func inside the brackets like $func($func(args)) → $func(args)
void DLG_FindNestedFunction(string input, int length, int start, int end)
{
  int braceRPos = -1;
  int braceLPos = -1;
  int signPos = -1;
  string symbol;

  for(int i=length-1; i>=0; i--)
  {
    symbol = strcut(input, i, i);
    if (symbol == "(") braceLPos = i;
    if (symbol == ")") braceRPos = i;
    if (braceLPos == -1 || symbol != "$") continue;

    signPos = i;
    break;
  }

  start = signPos;
  end = braceRPos;
}

// Running specific function by predefined list with custom function corner case
string DLG_RunFunction(string input, ref context)
{
  int startArgsIdx = FindSubStr(input, "(" , 0);
  string functionName = strcut(input, 1, startArgsIdx-1);
  object args;
  string sArguments = "";
  if (startArgsIdx+2 != strlen(&input)) sArguments = strcut(input, startArgsIdx+1, strlen(&input)-2);
  if (sArguments != "") DLG_ParseArguments(&sArguments, &args, &context);

  int argsCount = GetAttributesNum(&args);

  string result = "";
  result = DLG_RunKnownFunction(functionName, &context, &args, argsCount);
  if (result != "") return result;

  return DLG_RunCustomFunction(functionName, &args, argsCount);
}

// Looking for up to 10 arguments
void DLG_ParseArguments(string sArguments, ref result, ref context)
{
  for (int i=0; i < 9; i++)
  {
    if (DLG_GetNextArgument(&result, "arg" + i, &sArguments, &context)) return;
  }
}

// Return the next argument from (arg|arg) string or return false if no arguments left
bool DLG_GetNextArgument(ref result, string argName, string input, ref context)
{
  int iPos = findsubstr(input, "|", 0);

  if (iPos < 0) result.(argName) = DLG_ApplyContextToArgument(input, &context);
  else if (iPos < 1) result.(argName) = "";
  else if (iPos == 1) result.(argName) = DLG_ApplyContextToArgument(GetSymbol(&input, 0), &context);
  else result.(argName) = DLG_ApplyContextToArgument(strcut(input, 0, iPos-1), &context);
  if (iPos < 0) return true;

  input = strcut(input, iPos+1, strlen(&input)-1);
  return false;
}

// If the argument starts with $objectName we take it's attribute by name without the "$objectName" part
// $player.sex → calls .sex for pchar
// $player.ship.name → calls .ship.name for pchar
// $context.location.name → calls .location.name for the context object passed to the DLGO function
string DLG_ApplyContextToArgument(string argument, ref context)
{
  int argLen = strlen(&argument);

  if (argLen > 6 && strcut(argument, 0, 6) == "$player")  return DLG_GetObjectAttributeSafe(&pchar, strright(argument, argLen-8));
  if (argLen > 4 && strcut(argument, 0, 4) == "$npc")     return DLG_GetObjectAttributeSafe(&CharacterRef, strright(argument, argLen-6));
  if (argLen > 8 && strcut(argument, 0, 7) == "$context") return DLG_GetObjectAttributeSafe(&context, strright(argument, argLen-9));

  return "" + argument;
}

// Custom functions
// Up to 10 arguments, string type only
// Don't use without arguments!
string DLG_RunCustomFunction(string fnc, ref ar, int argsCount)
{
  switch (argsCount)
  {
    case 0:  return "Error: empty arguments is no allowed here"; break;
    case 1:  return call fnc(ar.arg0); break;
    case 2:  return call fnc(ar.arg0, ar.arg1); break;
    case 3:  return call fnc(ar.arg0, ar.arg1, ar.arg2); break;
    case 4:  return call fnc(ar.arg0, ar.arg1, ar.arg2, ar.arg3); break;
    case 5:  return call fnc(ar.arg0, ar.arg1, ar.arg2, ar.arg3, ar.arg4); break;
    case 6:  return call fnc(ar.arg0, ar.arg1, ar.arg2, ar.arg3, ar.arg4, ar.arg5); break;
    case 7:  return call fnc(ar.arg0, ar.arg1, ar.arg2, ar.arg3, ar.arg4, ar.arg5, ar.arg6); break;
    case 8:  return call fnc(ar.arg0, ar.arg1, ar.arg2, ar.arg3, ar.arg4, ar.arg5, ar.arg6, ar.arg7); break;
    case 9:  return call fnc(ar.arg0, ar.arg1, ar.arg2, ar.arg3, ar.arg4, ar.arg5, ar.arg6, ar.arg7, ar.arg8); break;
    case 10: return call fnc(ar.arg0, ar.arg1, ar.arg2, ar.arg3, ar.arg4, ar.arg5, ar.arg6, ar.arg7, ar.arg8, ar.arg9); break;
  }

  return "Error: to much arguments";
}
