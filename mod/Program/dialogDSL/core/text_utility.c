// Text stuff

// Lower and Upper register by keys "^" and "_" 
void DLG_ModifyRegister(string input, string key)
{
  int markPos = FindSubStr(input, key , 0);
  if (markPos < 0) return;

  string start   = "";
  string end     = "";
  string replace = strcut(input, markPos+1, markPos+2);
  if (key == "^") replace = ToUpper(replace);
  else replace = GetStrSmallRegister(replace);

  if (markPos > 0) start = strcut(input, 0, markPos-1);
  end = strcut(input, markPos+2, strlen(&input)-1);

  input = start + replace + end;
  DLG_ModifyRegister(&input, &key); // looking for the next replacement
}
