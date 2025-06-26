extern void DLG_DynamicDialogEvent();

// Run file with dialog
void DLG_RunDynamicDialog(string dialogFile)
{
  LoadSegment(dialogFile);
  DLG_DynamicDialogEvent();
  UnloadSegment(dialogFile);
}

// Prepend new link before the existent Exit-link
void DLG_AddDynamicLink(ref dlg, string text, string goText)
{
  aref links;
  makearef(links, dlg.links);
  int linksNum = GetAttributesNum(&links);

  for (int i=0; i < linksNum; i++)
  {
    aref link = GetAttributeN(&links, i);
    if (link.go != "exit") continue;

    DLG_ReplaceLink(&links, &link, &text, &goText);
    break;
  }
}

// Switch exit-link and new link values, assuming the exit-link is the last one
void DLG_ReplaceLink(ref links, ref link, string text, string goText)
{
  string linkName = GetAttributeName(&link);
  string linkValue = GetAttributeValue(&link);
  string nextLinkName = "l" + (sti(strright(linkName, strlen(linkName)-1)) + 1);
  links.(linkName) = strcut(linkValue, 0, 1) + " " + text;
  links.(linkName).go = goText;
  links.(nextLinkName) = (sti(strcut(linkValue, 0, 1)) + 1) + strright(linkValue, strlen(linkValue)-1);
  links.(nextLinkName).go = "exit";
}

// Add new link to the dialog, with correct index
void DLG_AddLink(ref links, string text, string goText)
{
  int linksNum = GetAttributesNum(&links) + 1;
  string linkName = "l" + linksNum;
  links.(linkName) = linksNum + ". " + text;
  links.(linkName).go = goText;
}

/**
========================================================================================================
=========== All the others functions here is for while-loop dialog mode, check the examples ============
========================================================================================================
**/

// GoTo specific node if some condition is true
bool DLG_GoToIf(bool check, string nextNode, ref dlg)
{
  if (check) DLG_GoTo(nextNode, &dlg);
  return check;
}

// GoTo specific node if some condition is true, with node specified
bool DLG_GoToIfReason(string reason, ref dlg)
{
  if (reason == "") return false;
  return DLG_GoToIf(reason != "", DLG_ChangeTargetNode(dlg.currentNode, reason), &dlg);
}

// Merging current node before "_" with reason like dialog_1 → dialog_reason
string DLG_ChangeTargetNode(string branch, string targetNode)
{
  string newBranch = FindStringBeforeChar(branch, "_");
  if (newBranch == "") newBranch = branch;
  return newBranch + "_" + targetNode;
}

void DLG_GoTo(string node, ref dlg)
{
  dlg.currentNode = node;
  dlg.NextNode = node;
}
