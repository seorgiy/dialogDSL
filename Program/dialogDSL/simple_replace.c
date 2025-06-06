// What keys are we looking for
void DLG_ReplaceSimpleKeys(string input)
{
  DLG_Replace(&input, "$playerSir");  // → Sir, Ledy for pchar sex
  DLG_Replace(&input, "$playerName"); // → Sharlie, Diego, Helen (pchar name)
  DLG_Replace(&input, "$name");       // → Robert, Carl, James (NPCname)
  DLG_Replace(&input, "$sir");        // → Sir, Ledy for NPC sex
  DLG_Replace(&input, "$hello");      // → Greetings!
  DLG_Replace(&input, "$bye");        // → Good bye!
  DLG_Replace(&input, "$swear");      // → God damn it!
}

// Looking for a specific key
void DLG_Replace(string input, string key)
{
  int iPos = FindSubStr(input, key, 0);
  if (iPos == -1) return;
  int lastIdx = iPos + strlen(&key);

  string start = "";
  string end = "";
  if (iPos > 0) start = strcut(input, 0, iPos-1);
  if (lastIdx < strlen(&input)) end = strcut(input, lastIdx, strlen(&input)-1);

  input = start + DLG_GetReplace(&key) + end;
}

// Replacing the key with a value
string DLG_GetReplace(string key)
{
  switch(key)
  {
    case "$playerSir":  return GetAddress_FormToNPC(&pchar);        break;
    case "$sir":        return GetAddress_FormToNPC(&CharacterRef); break;
    case "$playerName": return pchar.name;                          break;
    case "$name":       return CharacterRef.name;                   break;
    case "$swear":      return RandSwear();                         break;
    case "$bye":        return Goodbye();                           break;
    case "$hello":      return TimeGreeting();                      break;
  }

  return "missing replacement";
}
