Это репозиторий дев-мода для Карибской Легенды.<br>
[В мастерской](https://steamcommunity.com/sharedfiles/filedetails/?id=3494184551)

Представляет из себя набор функций, позволяющий использовать упрощённый код внутри файлов локализации.txt, конкретно для разруливания вопросов пола персонажей, падежей, склонений, числительных, обращений и прочего синтаксического стафа.

[Подробнее](https://github.com/seorgiy/dialogDSL/blob/master/HowTo.md)<br>
[Примеры](https://github.com/seorgiy/dialogDSL/blob/master/Examples.md)

Чтобы использовать в своём моде:
1. Подпишитесь на мод в мастерской.
2. Добавьте его в список необходимых продуктов в том моде, где вы хотите его использовать, чтобы игроки также подписались на него.
3. В своём моде, в файле диалога, где вы хотите использовать этот мод, добавьте в начало файла
#include "DialogDSL.c"
4. Теперь вы можете в этом диалоге вызывать функцию DLGO(text, context), внутри которой и происходит вся магия.

Например
```
>some_dialog.c
#include "dialogDSL.c"

void ProcessCommonDialogEvent(ref NPChar, aref Link, aref Diag) {
  ref PChar;
  PChar = GetMainCharacter();
  string NPC_Meeting;

  switch(Dialog.CurrentNode) {
    case "First time":
    Dialog.Text = DLGO(StringFromKey("key_1),"");
    Link.l1 = DLGO(StringFromKey("key_2),"");
    Link.l1.go = "meeting";
    break;
  }
}
```
