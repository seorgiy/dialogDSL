Это репозиторий дев-мода для Карибской Легенды.<br>
[В мастерской](https://steamcommunity.com/sharedfiles/filedetails/?id=3494184551)

Представляет из себя набор функций, позволяющий использовать упрощённый код внутри файлов локализации.txt, конкретно для разруливания вопросов пола персонажей, падежей, склонений, числительных, обращений и прочего синтаксического стафа.

[Подробнее](https://github.com/seorgiy/dialogDSL/blob/master/HowTo.md)<br>
[Примеры](https://github.com/seorgiy/dialogDSL/blob/master/Examples.md)<br>
[Полный список волшебных ключей](https://github.com/seorgiy/dialogDSL/blob/master/mod/Program/dialogDSL/defines.c)<br>

### Как использовать
1. Подпишитесь на мод в мастерской.
2. Добавьте его в список необходимых продуктов в том моде, где вы хотите его использовать, чтобы игроки также подписались на него.
3. В своём моде, в файле диалога, где вы хотите использовать этот мод, добавьте в начало файла
```
#include "DialogDSL.c"
```
4. Теперь вы можете в этом диалоге вызывать функцию DLGO(text, context), внутри которой и происходит вся магия.

Hello world
```
>some_dialog.c
#include "DialogDSL.c"

void ProcessCommonDialogEvent(ref NPChar, aref Link, aref Diag) {
  switch(Dialog.CurrentNode) {
    case "First time":
      Dialog.Text = DLGO($hello, $name, ""); // пример сырого использования, так делать не стоит
      Link.l1 = DLGO(StringFromKey("key_2),""); // а вот так стоит
      Link.l1.go = "meeting";
      Link.l2 = DLGO(XI_ConvertString("somekey"),""); // и так тоже можно
      Link.l2.go = "farewell";
    break;
  }
}
```

Не подключайте библиотеку в общих файлах игры, это вызовет конфликт с любым другим модом, где используется DLGO, из-за повторного объявления функций. Поэтому лучше подключать конкретно в файл диалога, который подгружается/выгружается по необходимости. Бонус: таким же образом работают файлы интерфейсов, поэтому подключать можно и туда тоже.

### Для продвинутых парней

Подключаем вариант с обработчиком всего диалога в целом
```
>some_dialog.c
#include "DialogDSL.c"
#include "DialogDSL\core\events.c" // Здесь добавлятся обработчик события

void ProcessCommonDialogEvent(ref NPChar, aref Link, aref Diag) {
  switch(Dialog.CurrentNode) {
    // здесь сам диалог
  }

  Event("DLGO_ALL", "i", &NullCharacter); // В конец докидываем событие и готово, можно передать здесь какой-нибудь контекст при желании, например, квест
}
```

Такой способ, впрочем, не запрещает точечное использование DLGO внутри диалога, если нужно передать особый контекст.
