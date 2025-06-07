// Iternal helpers

string DLG_RandArgument(ref args, int argsCount)
{
  return GetAttributeValue(GetAttributeN(&args, rand(argsCount-1)));
}

// Just safety calls
string DLG_GetObjectAttributeSafe(ref obj, string attribute)
{
  if (CheckAttribute(&obj, attribute)) return obj.(attribute);
  trace("Error: missing argument " + attribute);
  return ("Error: missing argument " + attribute);
}

// Just safety calls
string DLG_A(ref args, int index)
{
  string argName = "arg" + index;
  return DLG_GetObjectAttributeSafe(&args, &argName);
}

void DLG_ReplaceAllMatches(string input, string key, string replace, int curPos)
{
  int markPos = FindSubStr(&input, key, curPos);
  if (markPos < 0) return;

  string start   = "";
  string end     = "";
  if (markPos > 0) start = strcut(input, 0, markPos-1);
  end = strcut(input, markPos+2, strlen(&input)-1);

  input = start + replace + end;
  DLG_ReplaceAllMatches(input, &key, &replace, markPos); // looking for the next replacement
}

void DLG_EscapeAllChars(string input)
{
  DLG_ReplaceAllMatches(&input, "\(", "{{", 0);
  DLG_ReplaceAllMatches(&input, "\)", "}}", 0);
}

void DLG_UnescapeAllChars(string input)
{
  DLG_ReplaceAllMatches(&input, "{{", "(", 0);
  DLG_ReplaceAllMatches(&input, "}}", ")", 0);
}
