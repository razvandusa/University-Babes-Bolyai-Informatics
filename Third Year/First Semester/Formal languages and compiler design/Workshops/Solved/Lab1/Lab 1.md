## EBNF
| Simbol     | Inseamna                              |
| ---------- | ------------------------------------- |
| "text"     | terminal (apare exact asa in program) |
| nume       | neterminal (definit de o alta regula) |
| =          | "se defineste ca"                     |
| \|         | sau                                   |
| ( ... )    | grupare                               |
| { ... }    | repetat de 0, 1, 2, ... ori           |
| [ ... ]    | optional (0 sau 1 data)               |
| .          | sfarsit de regula                     |
| (* ... \*) | comentarii                            |
## 1. Specificarea minilimbajului de programare
```EBNF
program = "int" "main" "(" ")" "{" { declaratie } { instructiune } "}" .
```

```EBNF
declaratie = decl_variabile | decl_struct .
decl_variabile = tip identificator { "," identificator } ";" .
decl_struct = "struct" identificator "{" { tip identificator ";" } "}" ";" .
```

```EBNF
identificator = litera { litera | cifra } .
litera = "a" | "b" | ... | "z" | "A" | "B" | ... | "Z" .
cifra = "0" | "1" | ... | "9" .
constanta = intreg | real .
intreg = "0" | cifra_nenula { cifra } .
real = intreg "." cifra { cifra } .
cifra_nenula = "1" | "2" | ... | "9" .
```

```EBNF
expresie = termen { ("+" | "-") termen } .
termen = factor { ( "*" | "/" | "%" ) factor } .
factor = acces | constanta | "(" expresie ")" .
```

**2 tipuri de date simple si un tip de date definit de utilizator**
```EBNF
tip = "int" | "double" | "struct" identificator .
```

**instructiuni**
1. instructiune de atribuire
```EBNF
atribuire = acces "=" expresie ";" .
acces = identificator { "." identificator } .
```

2. instructiune de intrate/iesire
```EBNF
io = citire | scriere .
citire = "cin" ">>" acces ";" .
scriere = "cout" "<<" expresie ";" .
```

3. instructiune de selectie (conditionata)
```EBNF
selectie = "if" "(" conditie ")" instructiune [ "else" instructiune ] .

conditie = expresie op_rel expresie .

op_rel = "==" | "<" | ">" | "!=" | "<=" | ">=" .

bloc = "{" { instructiune } "}" .

instructiune = atribuire | io | selectie | bloc | ciclare .
```

4. instructiune de ciclare
```EBNF
ciclare = "while" "(" conditie ")" instructiune .
```

## 2. Textele sursa a 3 mini-programe
1. Calcul perimetru si aria cercului de o raza data
```cpp
int main() {
	struct Cerc {double raza; };
	struct Cerc c;
	double p, a;
	cin >> c.raza;
	p = 2 * 3.14 * c.raza;
	a = 3.14 * c.raza * c.raza;
	cout << p;
	cout << a;
}
```

2. CMMDC a doua numere naturale
```cpp
int main() {
	int a; int b; int c;
	cin >> a;
	cin >> b;
	while (b != 0) {
		r = a % b;
		a = b;
		b = r;
	}
	cout << a;
}
```

3. Suma a n numere citite de la tastatura
```cpp
int main () {
	int n;
	int i;
	int x;
	int s;
	cin >> n;
	s = 0;
	i = 0;
	while (i < n) {
		cin >> x;
		s = s + x;
		i = i + 1;
	}
	cout << s;
}
```

## 3. Texte sursa a doua programe care contin erori conform MLP-ului
1. Erori si in MLP si in C++
```cpp
int main() {
	int 2x; // atom care nu este identificator
	int a;
	a = 5 @ 3; // caracterul nu e operator valid
}
```

2. Erori doar in MLP
```cpp
int main() {
	int x_1; // _ nu apare in litera sau cifra, deci nu e un identificator in MLP, dar in C++ e valid
	x_1 = 0x1F; // constanta hexazecimala valida in C++, dar gramatica din MLP nu o permite
	cout << x_1;
}
```