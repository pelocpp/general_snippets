# `decltype` und `std::declval`

## `decltype`

Der in C ++ 11 eingef�hrte `decltype`-Operator gibt, grob gesagt, den Typ eines Ausdrucks oder einer Entit�t wieder.
Es ist nicht von der Hand zu weisen, dass der `decltype`-Operator Gemeinsamkeiten mit dem
`typeof`-Operator hat. Vermutlich auf Grund vorhandener, inkompatibler Erweiterungen
dieses Namens in vielen Compilern wurde stattdessen `decltype` gew�hlt.

`decltype` gibt einen Typ zur�ck. Es kann grunds�tzlich �berall dort eingesetzt werden, wo ein Typ ben�tigt wird:

```cpp
// decltype may modify type deduction, e.g. in generic lamdas
// (decltype (t + u), decltype (t) or decltype (u) are valid)
template <typename T, typename U>
auto add(const T& t, const U& u) -> decltype (t + u) 
{ 
    return t + u;
}
```

In diesem Beispiel wird `decltype` zusammen mit dem so genannten *trailing return type*, zu deutsch etwa
*nachgereichter R�ckgabetyp* demonstriert.

Weitere Beispiele:

```cpp
// demonstrating decltype with entities / instances of types:
std::vector<int> vec;

// decltype(vec) yields std::vector<int>,
// so the next line is equivalent to 'std::vector<int> v2;'
decltype(vec) vec2;

// foo returns the type of f, in this case float,
// so this is equivalent to float foo(int b);
float f;
auto foo(int b) -> decltype(f);
```

und

```cpp
// demonstrating decltype with expressions:

// decltype(foo()) yields the type of whatever foo() returns,
// in this case, float:
float foo();
decltype(foo()) b;

//decltype yields void, so this is the same as void bar();
std::vector<int> vec;
auto bar() -> decltype(vec.push_back(int{})); 
```

## `std::declval`

In manchen Situationen stehen Objekte nicht zur Verf�gung,
die wir an einen Ausdruck �bergeben wollen, um diesen mit `decltype` auszuwerten.
M�glicherweise lassen sich derartige Objekte �berhaupt nicht erstellen,
z.B. weil ihre Klassen nur private oder gesch�tzte Konstruktoren haben.

Betrachten wir das Beispiel einer Funktion `f`. `decltype(f(11))` besagt 
"Welchen Typ bekomme ich, wenn ich `f` mit `11` aufrufe?".
Was wir eigentlich meinen, ist "Welchen Typ bekomme ich, wenn ich `f` mit einem `int` aufrufe?".
Im Fall von `int` k�nnten wir nur ein standardm��ig initialisiertes `int` verwenden.
Der Standardkonstruktor ist jedoch nicht immer verf�gbar.

F�r solche F�lle ist `std::declval` konzipiert.
Es ist eine Funktionsschablinbe, die eine *r*-Value-Referenz auf alles zur�ckgibt,
was an sie �bergeben wird. 
Auf diese Weise m�ssen nicht eine Funktion k�nstlich deklarieren,
um etwas zu haben, das wir in unserem `decltype`-Argument verwenden k�nnen:

```cpp
decltype(f(std::declval<int>()))
```

Dies ist besonders praktisch,
wenn man sich in einem Template-Kontext befindet und der Wert, den man erhalten m�chte,
von einem Template-Parameter abh�ngt. Siehe zum Beispiel:

```cpp
template<typename T, typename U>
using sum_t = decltype(std::declval<T>() + std::declval<U>());
```

Dies ist zu lesen in der Form: "`sum_t` ist der Typ, den ich bekomme, wenn ich zu *einem U* *ein T* hinzuf�ge."

## Literaturhinweise:

Die Anregungen zu diesem Code-Snippet finden sich unter anderem unter

[Modern C++ Features](https://arne-mertz.de/2017/01/decltype-declval/)<br>(abgerufen am 23.05.2020).

---

[Zur�ck](../../Readme.md)

---