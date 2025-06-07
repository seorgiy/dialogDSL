// Additional localizing functions

// Localized ship class with cases like "corvette, Корвет, Корвета, Корвету"
string DLG_ShipClass(ref args, ref chr)
{
  string end = "";
  if (CheckAttribute(&args, "arg0")) end = DLG_A(&args, 0);
  return xiStr(GetShipTypeName(&chr) + end);
}

// Return phrase based on char's nobility
string DLG_GoodBad(ref args, ref chr)
{
  int nobility = makeint(chr.reputation.nobility);
  if (nobility > 70) return DLG_A(&args, 0);
  if (nobility > 30) return DLG_A(&args, 1);
  return DLG_A(&args, 2);
}
