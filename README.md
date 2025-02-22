# Лабораторная работа №13
Дата выдачи: 2024-04-27. 
Срок выполнения работы: 2024-05-15.

## Параллелизация вычислений и стандартные алгоритмы языка Си++

### Ответвление
Необходимо создать ответвление (fork) моего репозитория Lab-13 (название
оставить без изменения, а видимость поставить приватной). Назничить меня в
новом репозитории соавтором с правами администратора. Вики, Задачи а также
Проекты отключить.

В локальной копии создавать ветки (branch) по необходимости.

### Этап разработки
Используя механизм шаблонов языка Си++ разработать класс (либо набор классов) 
для представления ИНС типа многослойный песептрон. Обязательными параметрами 
шаблона должны являться тип данных, используемый для хранения значения ФН 
и функция активации. 

Реализовать функционал необходимый для корректной работы сети, 
задействовать параллелизацию вычислений (см. например 
[https://www.modernescpp.com/index.php/asynchronous-function-calls/](https://www.modernescpp.com/index.php/asynchronous-function-calls/)
).
Также реализовать механизм загрузки весовых коэффициентов из файла.

В основной функции, размещенной в файле `main.cpp`, продемонстрировать 
применение разработанного класса и его методов.

Ключи компиляции `-std=c++11` `-Wall` `-Werror` `-pedantic` `-lpthread`. 

#### Этап тестирования
Для проверки корректности разработанных классов построить сеть с одним 
скрытым слоем в следующей конфигурации. 
1. Размерности:
  - входа `784`;
  - скрытого слоя `200`;
  - выхода `10`.
2. Функции активации:
  - скрытого слоя  `tansig`;
  - выхода `purelin`.
3. Весовые коэффициенты (формат `double`):
  - `net_train_bias1.bin` смещения скрытого слоя;
  - `net_train_weight1.bin` коэффициенты скрытого слоя (двумерный массив `200*784`);
  - `net_train_bias2.bin` смещения выходного слоя;
  - `net_train_weight2.bin` весовые коэффициенты для выходного слоя (двумерный массив `10*200`);

На первых `6000` элементах обучающего набора базы [MNIST](http://yann.lecun.com/exdb/mnist/) 
cеть выдает 77% верных ответов. Выходные значения кодируются по следующей схеме:
  - `0` = `{0,0,0,0,0,0,0,0,0,1}`;
  - `1` = `{1,0,0,0,0,0,0,0,0,0}`;
  - `2` = `{0,1,0,0,0,0,0,0,0,0}`;
  - `3` = `{0,0,1,0,0,0,0,0,0,0}`;
  - `4` = `{0,0,0,1,0,0,0,0,0,0}`;
  - `5` = `{0,0,0,0,1,0,0,0,0,0}`;
  - `6` = `{0,0,0,0,0,1,0,0,0,0}`;
  - `7` = `{0,0,0,0,0,0,1,0,0,0}`;
  - `8` = `{0,0,0,0,0,0,0,1,0,0}`;
  - `9` = `{0,0,0,0,0,0,0,0,1,0}`.

Дополнительная информация:
  * [tansig](http://matlab.izmiran.ru/help/toolbox/nnet/tansig.html)
  * [purelin](http://matlab.izmiran.ru/help/toolbox/nnet/purelin.html)
  * Nelson H. F. Beebe *Using C and C++ with Fortran*: [www.math.utah.edu](https://www.math.utah.edu/software/c-with-fortran.html)

### Этап обсуждения
По итогу выполнения работы создать запрос на слияние (pull request) 
и назначить рецензентами обоих ассистентов.

По результатам рецензирования получить минимум один комментарий, 
в случае необходимости внести исправления.

