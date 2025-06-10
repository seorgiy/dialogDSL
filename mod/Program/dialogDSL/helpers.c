// Additional localization functions

// Localized ship class with cases like "corvette, Корвет, Корвета, Корвету"
string DLG_ShipClass(ref args, ref chr)
{
  string end = "";
  if (CheckAttribute(&args, "var0")) end = DLG_A(&args, 0);
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

// Localized prhase for the male/female ship class name
string DLG_ShipManWoman(ref args, ref chr)
{
  int nShipType = GetCharacterShipType(&chr);
  ref rBaseShip = GetRealShip(nShipType);
  return GetShipSexWord(rBaseShip.BaseName, DLG_A(&args, 0), DLG_A(&args, 1));
}

// Return another localized key with the same context
string DLG_Link(ref args, ref context)
{
  return DLGO(StringFromKey(DLG_A(&args, 0)), &context);
}

string DLG_IfHasAttribute(ref args, ref context)
{
  if (CheckAttribute(&context, DLG_A(&args, 0))) return DLG_A(&args, 1);
  return DLG_A(&args, 2);
}
