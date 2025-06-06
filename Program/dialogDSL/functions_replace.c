// Looking for the functions call in the input
string DLG_RunAllFunctions(string input, ref context)
{
  int startFuncIdx = FindSubStr(input, "$" , 0);
  int endFuncIdx   = FindSubStr(input, ")" , 0);
  if (startFuncIdx < 0 || endFuncIdx < 0) return "" + input; // all replacements are made

  string end     = "";
  string start   = "";
  string replace = strcut(input, startFuncIdx+1, endFuncIdx-1);

  if (startFuncIdx > 1)               start = strcut(input, 0, startFuncIdx-1);
  if (strlen(&input) - endFuncIdx > 2) end  = strcut(input, endFuncIdx+1, strlen(&input)-1);

  replace = DLG_RunFunction(replace, &context);
  return DLG_RunAllFunctions(start + replace + end, &context); // looking for the next replacement
}

// Running specific function by known list
string DLG_RunFunction(string input, ref context)
{
  int startArgsIdx = FindSubStr(input, "(" , 0);
  string functionName = strcut(input, 0, startArgsIdx-1);
  object args;
  string sArguments = "";
  if (startArgsIdx+2 != strlen(&input)) sArguments = strcut(input, startArgsIdx+1, strlen(&input)-1);
  if (sArguments != "") DLG_ParseArguments(&sArguments, &args, &context);
  int argsCount = GetAttributesNum(&args);

  switch (functionName)
  {
    case "manWoman":    return GetSexPhrase(args.arg0, args.arg1); break;
    case "NpcManWoman": return NPCharSexPhrase(CharacterRef, args.arg0, args.arg1); break;
    case "days":        return FindRussianDaysString(sti(args.arg0)); break;
    case "dublon":      return FindRussianDublonString(sti(args.arg0)); break;
    case "qty":         return FindRussianQtyString(sti(args.arg0)); break;
    case "month":       return FindRussianMonthString(sti(args.arg0)); break;
    case "people":      return FindRussianPeoplesString(sti(args.arg0), args.arg1); break;
    case "slaves":      return FindRussianSlavesString(sti(args.arg0), args.arg1); break;
    case "sailors":     return FindRussianSailorString(sti(args.arg0), args.arg1); break;
    case "rand":        return DLG_RandArgument(&args, argsCount); break;
    case "goodbad":
      int nobility = makeint(pchar.reputation.nobility);
      if (nobility > 70) return (args.arg0);
      if (nobility > 30) return (args.arg1);
      return (args.arg2);
    break;
  }

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

  if (argLen > 6 && strcut(argument, 0, 6) == "$player")  return DLG_GetObjectAttribute(&pchar, strright(argument, argLen-8));
  if (argLen > 4 && strcut(argument, 0, 4) == "$npc")     return DLG_GetObjectAttribute(&CharacterRef, strright(argument, argLen-6));
  if (argLen > 8 && strcut(argument, 0, 8) == "$context") return DLG_GetObjectAttribute(&context, strright(argument, argLen-10));

  return "" + argument;
}

string DLG_GetObjectAttribute(ref context, string attribute)
{
  if (CheckAttribute(&context, attribute)) return context.(attribute);
  return "";
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

string DLG_RandArgument(ref variants, int variantsCount)
{
  return GetAttributeValue(GetAttributeN(variants, rand(variantsCount-1)));
}
