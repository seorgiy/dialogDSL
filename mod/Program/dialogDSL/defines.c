// List for all DSL $handlers to use
// Define all the new ones here

// Predefined DSL-functions
// Access global variables: pchar, CharacterRef + context object
string DLG_RunKnownFunction(string functionName, ref context, ref args, int argsCount)
{
  ref NPC = &CharacterRef; // just for consistensy

  switch (functionName)
  {
    case "manWoman":        return GetSexPhrase(DLG_A(&args, 0), DLG_A(&args, 1));                   break;
    case "npcManWoman":     return NPCharSexPhrase(&NPC, DLG_A(&args, 0), DLG_A(&args, 1));          break;
    case "ctxManWoman":     return NPCharSexPhrase(&context, DLG_A(&args, 0), DLG_A(&args, 1));      break;
    case "days":            return FindRussianDaysString(sti(DLG_A(&args, 0)));                      break;
    case "dublon":          return FindRussianDublonString(sti(DLG_A(&args, 0)));                    break;
    case "qty":             return FindRussianQtyString(sti(DLG_A(&args, 0)));                       break;
    case "month":           return FindRussianMonthString(sti(DLG_A(&args, 0)));                     break;
    case "people":          return FindRussianPeoplesString(sti(DLG_A(&args, 0))), DLG_A(&args, 1);  break;
    case "slaves":          return FindRussianSlavesString(sti(DLG_A(&args, 0))), DLG_A(&args, 1);   break;
    case "sailors":         return FindRussianSailorString(sti(DLG_A(&args, 0))), DLG_A(&args, 1);   break;
    case "rand":            return DLG_RandArgument(&args, argsCount);                               break;
    case "attr":            return DLG_A(&args, 0);                                                  break;
    case "ShipClass":       return DLG_ShipClass(&args, &pchar);                                     break;
    case "npcShipClass":    return DLG_ShipClass(&args, &NPC);                                       break;
    case "goodBad":         return DLG_GoodBad(&args, &pchar);                                       break;
    case "npcGoodBad":      return DLG_GoodBad(&args, &NPC);                                         break;
    case "key":             return xiStr(DLG_A(&args, 0));                                           break;
    case "link":            return DLG_Link(&args, &context);                                        break;
    case "shipManWoman":    return DLG_ShipManWoman(&args, &pchar);                                  break;
    case "npcShipManWoman": return DLG_ShipManWoman(&args, &NPC);                                    break;
    case "ctxShipManWoman": return DLG_ShipManWoman(&args, &context);                                break;
    case "workType":        return GetWorkTypeOfMan(&NPC, DLG_A(&args, 0));                          break;
    case "hasAttr":         return DLG_IfHasAttribute(&args, &pchar);                                break;
    case "npcHasAttr":      return DLG_IfHasAttribute(&args, &NPC);                                  break;
    case "ctxHasAttr":      return DLG_IfHasAttribute(&args, &context);                              break;
    break;
  }

  return "";
}

// Predefined DSL-shortcuts replaces
// If you wants to add new shortcut – add here and to function DLG_ReplaceSimpleKeys as well
string DLG_RunReplace(string key)
{
  switch(key)
  {
    case "$sir":     return GetAddress_FormToNPC(&pchar);        break; // → Sir, Ledy for pchar sex
    case "$npcSir":  return GetAddress_FormToNPC(&CharacterRef); break; // → Sir, Ledy for NPC sex
    case "$name":    return pchar.name;                          break; // → Sharlie, Diego, Helen (pchar name)
    case "$npcName": return CharacterRef.name;                   break; // → Robert, Carl, James (npcName)
    case "$swear":   return RandSwear();                         break; // → God damn it!
    case "$bye":     return Goodbye();                           break; // → Good bye!
    case "$hello":   return TimeGreeting();                      break; // → Greetings!
    case "$city":    return GetCityName(CharacterRef.city);      break; // → VIllemstad
  }

  return "Error: missing replacement for " + key;
}

// Predefined DSL-shortcuts keys
void DLG_ReplaceSimpleKeys(string input)
{
  DLG_Replace(&input, "$sir");
  DLG_Replace(&input, "$npcSir");
  DLG_Replace(&input, "$name");
  DLG_Replace(&input, "$npcName");
  DLG_Replace(&input, "$swear");
  DLG_Replace(&input, "$bye");
  DLG_Replace(&input, "$hello");
  DLG_Replace(&input, "$city");
}
