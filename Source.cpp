#include <iostream>
#include "Header.h"
#include <string>
#include <fstream>
#include "String.h"
#include <Windows.h>
#include <vector>
#include <regex>
#include <map>
using namespace std;

struct List {
	int data;
	List* next;
};

struct info_guests {
	string name;
	int year;
	string Address;
	string target_come;
};

struct Hash_map {
	string num_passport;
	info_guests data;
	bool busy = false;
	Hash_map* next = NULL;
};

struct Elem {
	string num_passport;
	string num_number;
	int number;
	string date_input;
	string date_output;
};

struct Linear_List {
	Elem info;
	Linear_List* next;
};

struct Node {
	string number;
	int num_number;
	int count_place;
	int count_room;
	bool sanuzel;
	string equipment;

	bool operator ==(Node& b) {
		if (this->count_place == b.count_place && this->count_room == b.count_room &&
			this->equipment == b.equipment && this->number == b.number && (this->sanuzel == b.sanuzel)) {
			return true;
		}
		return false;
	}

	bool operator !=(Node& b) {
		return !(*this == b);
	}
};

struct Tree {
	Node info_nomer;
	int height;
	Tree* Left;
	Tree* Right;
};

string equip(int num) {
	switch (num)
	{
	case(1):
		return "Холодильник";
	case(2):
		return "Телевизор";
	case(3):
		return "Кондиционер";
	case(4):
		return "Мини-бар";
	case(5):
		return "Приставка";
	}
}

int equip_1(string s) {
	if (s == "Холодильник") return 1;
	else if (s == "Телевизор") return 2;
	else if (s == "Кондиционер") return 3;
	else if (s == "Мини-бар") return 4;
	else return 5;
}

int equip_to_num(string s) {
	std::string delimiter = " ";
	int num = 0;
	size_t pos = 0;
	std::string token;
	while ((pos = s.find(delimiter)) != std::string::npos) {
		num = num * 10;
		token = s.substr(0, pos);
		s.erase(0, pos + delimiter.length());
		num += equip_1(token);
	}
	int m = 0;
	while (num)
	{
		m = m * 10 + num % 10;
		num /= 10;
	}
	return m;
}

int height(Tree* a) {
	if (a) { return a->height; }
	else return 0;
}

int BF(Tree* a)
{
	return height(a->Right) - height(a->Left);
}

void OverHeight(Tree* a)
{
	int hleft = height(a->Left);
	int hright = height(a->Right);
	a->height = (hleft > hright ? hleft : hright) + 1;
}

bool find_elem(Tree* a, int element, int* lr) {
	*lr += 1;
	if (a->Left == NULL && a->Right == NULL) {
		if (a->info_nomer.num_number == element) {
			return true;
		}
		else {
			return false;
		}
	}
	else if (a->Left == NULL && a->Right != NULL) {
		if (a->info_nomer.num_number == element) {
			return true;
		}
		else {
			return find_elem(a->Right, element, lr);
		}
	}
	else if (a->Right == NULL && a->Left != NULL) {
		if (a->info_nomer.num_number == element) {
			return true;
		}
		else {
			return find_elem(a->Left, element, lr);
		}
	}
	else {
		if (a->info_nomer.num_number == element) {
			return true;
		}
		else {
			if (element > a->info_nomer.num_number) {
				return find_elem(a->Right, element, lr);
			}
			else {
				return find_elem(a->Left, element, lr);
			}
		}
	}
}

Tree* RightRotation(Tree* x) {
	Tree* y = x->Left;
	x->Left = y->Right;
	y->Right = x;
	OverHeight(x);
	OverHeight(y);
	return y;
}


Tree* LeftRotation(Tree* y) {
	Tree* x = y->Right;
	y->Right = x->Left;
	x->Left = y;
	OverHeight(y);
	OverHeight(x);
	return x;
}


Tree* Balance(Tree* x)
{
	OverHeight(x);
	if (BF(x) == 2)
	{
		if (BF(x->Right) < 0) x->Right = RightRotation(x->Right);
		return LeftRotation(x);
	}
	if (BF(x) == -2)
	{
		if (BF(x->Left) > 0) x->Left = LeftRotation(x->Left);
		return RightRotation(x);
	}
	return x;
}

Tree* add(Tree* a, Node element) {
	if (!a) {
		a = new Tree;
		a->info_nomer = element;
		a->Left = NULL;
		a->Right = NULL;
		a->height = 1;
		return a;
	}
	if (element.num_number < a->info_nomer.num_number) {
		a->Left = add(a->Left, element);
	}
	else {
		a->Right = add(a->Right, element);
	}
	return Balance(a);
}

Tree* SearchMin(Tree* x)
{
	if (x->Left) return SearchMin(x->Left);
	else return x;
}
Tree* DeleteMin(Tree* x)
{
	if (x->Left == 0) return x->Right;
	x->Left = DeleteMin(x->Left);
	return Balance(x);
}


Tree* Delete(Tree* x, int k)
{
	if (!x) return 0;
	if (k < x->info_nomer.num_number) x->Left = Delete(x->Left, k);
	else if (k > x->info_nomer.num_number) x->Right = Delete(x->Right, k);
	else
	{
		Tree* y = x->Left;
		Tree* z = x->Right;
		delete x;
		if (!z) return y;
		Tree* min = SearchMin(z);
		min->Right = DeleteMin(z);
		min->Left = y;
		return Balance(min);
	}
	return Balance(x);
}


int check(string s, int left = INT_MIN, int right = INT_MAX) {
	int n;
	while (true) {
		cin >> n;
		if (left != INT_MIN && right != INT_MAX) {
			if (cin.fail() || cin.rdbuf()->in_avail() > 1 || n > right || n < left) {
				cout << s << " в отрезке от " << left << " до " << right << "." << endl;
				cin.clear();
				cin.ignore(INT_FAST16_MAX, '\n');
			}
			else {
				break;
			}
		}
		else if (left == INT_MIN && right != INT_MAX) {
			if (cin.fail() || cin.rdbuf()->in_avail() > 1 || n > right) {
				cout << s << " меньшее либо равное " << right << "." << endl;
				cin.clear();
				cin.ignore(INT_FAST16_MAX, '\n');
			}
			else {
				break;
			}
		}
		else if (left != INT_MIN && right == INT_MAX) {
			if (cin.fail() || cin.rdbuf()->in_avail() > 1 || n < left) {
				cout << s << " большее либо равное " << left << "." << endl;
				cin.clear();
				cin.ignore(INT_FAST16_MAX, '\n');
			}
			else {
				break;
			}
		}
		else {
			if (cin.fail() || cin.rdbuf()->in_avail() > 1) {
				cout << s << "." << endl;
				cin.clear();
				cin.ignore(INT_FAST16_MAX, '\n');
			}
			else {
				break;
			}
		}
	}
	return n;
}


int hash_func(string c, int size_hash) {
	int sum = 0;
	for (int i = 0; i < c.length(); i++) {
		sum += (int)c[i] * (int)c[i];
	}
	return sum % size_hash;
}

void InsertElem(Hash_map* h, Hash_map el, int index) {
	if (!(h[index]).busy) {
		h[index] = el;
	}
	else {
		Hash_map* temp = &h[index];
		while (temp->next && temp->next->busy) {
			temp = temp -> next;
		}
		if (!temp-> next) {
			temp->next = new Hash_map;
			temp->next->busy = el.busy;
			temp->next->data = el.data;
			temp->next->num_passport = el.num_passport;
			temp->next->next = NULL;
		}
		else {
			temp->next->busy = el.busy;
			temp->next->data = el.data;
			temp->next->num_passport = el.num_passport;
			temp->next->next = NULL;
		}
	}
}

string check_passport() {
	string num_pass;
	while (true) {
		cin >> num_pass;
		if (cin.fail() || cin.rdbuf()->in_avail() > 1) {
			cin.clear();
			cin.ignore(INT_FAST16_MAX, '\n');
			cout << "Повторите ввод: " << endl;
			continue;
		}
		regex num_passport("[1-9][0-9]{3}-[1-9][0-9]{5}");
		if (regex_match(num_pass, num_passport)) {
			break;
		}
		else {
			cout << "Неправильно введен номер паспорта. Повторите ввод: " << endl;
			cin.clear();
			cin.ignore(INT_FAST16_MAX, '\n');
		}
	}
	cin.clear();
	cin.ignore(INT_FAST16_MAX, '\n');
	return num_pass;
}

void add_new_pos(Hash_map* h, int size_hash) {
	string num_pass;
	string name_pos;
	int year = 0;
	string Address;
	string target_come;
	while (true) {
		cout << "Введите номер паспорта постояльца в формате NNNN-NNNNNN, где N - цифра от 0 до 9: " << endl;
		num_pass = check_passport();
		int temp_index = hash_func(num_pass, size_hash);
		auto temp = &h[temp_index];
		bool flag = true;
		while (temp) {
			if (temp->num_passport == num_pass) {
				flag = false;
				break;
			}
			temp = temp->next;
		}
		if (flag) {
			break;
		}
		else {
			cout << "Постоялец с таким номером паспорта уже зарегистрирован!!! " << endl;
		}
	}
	cout << "Введите имя постояльца в формате Фамилия И.О.: " << endl;
	while (true) {
		getline(cin, name_pos);
		regex name_post("[А-Я][а-я]* [А-Я]\.[А-Я]\.");
		if (regex_match(name_pos, name_post)) {
			break;
		}
		else {
			cout << "Неправильно введены фамилия и инициалы постояльца. Повторите ввод: " << endl;
		}
	}
	cout << "Введите год рождения постояльца: " << endl;
	year = check("Неверно. Введите число ", 1900, 2100);
	cout << "Выберете домашнюю страну постояльца: " << endl;
	cout << "1. Россия" << endl;
	cout << "2. Сербия" << endl;
	cout << "3. Казахстан" << endl;
	cout << "4. Турция" << endl;
	cout << "5. Республика Беларусь" << endl;
	cout << "6. Киргистан" << endl;
	cout << "7. Узбекистан" << endl;
	int num = check("Неверно. Введите число ", 1, 7);
	switch (num)
	{
	case(1):
		Address = "Россия";
		break;
	case(2):
		Address = "Сербия";
		break;
	case(3):
		Address = "Казахстан";
		break;
	case(4):
		Address = "Турция";
		break;
	case(5):
		Address = "Республика Беларусь";
		break;
	case(6):
		Address = "Киргистан";
		break;
	case(7):
		Address = "Узбекистан";
		break;
	}
	cout << "Выберете цель прибытия постояльца: " << endl;
	cout << "1. Путешествие" << endl;
	cout << "2. Отдых" << endl;
	cout << "3. Работа" << endl;
	num = check("Неверно. Введите число ", 1, 3);
	switch (num)
	{
	case(1):
		target_come = "Путешествие";
		break;
	case(2):
		target_come = "Отдых";
		break;
	case(3):
		target_come = "Работа";
		break;
	}
	Hash_map el;
	el.num_passport = num_pass;
	el.data.name = name_pos;
	el.data.year = year;
	el.data.Address = Address;
	el.busy = true;
	el.data.target_come = target_come;
	el.next = NULL;
	int index = hash_func(el.num_passport, size_hash);
	InsertElem(h, el, index);
}

void zap_hash_map(Hash_map* h, int size_hash) {
	ifstream file;
	file.open("Hash_map.txt");
	if (file.is_open()) {
		while (!file.eof()) {
			char c[1000];
			file.getline(c, 1000);
			//string splitting_str = c;
			Hash_map el;
			el.num_passport = strtok(c, " ");
			el.data.name = strtok(NULL, " ");
			el.data.name += ' ';
			el.data.name += strtok(NULL, " ");
			el.data.year = atoi(strtok(NULL, " "));
			el.data.Address = strtok(NULL, " ");
			el.busy = true;
			el.data.target_come = strtok(NULL, " ");
			el.next = NULL;
			int index = hash_func(el.num_passport, size_hash);
			InsertElem(h, el, index);
		}
	} 
	else
	{
		cout << "Файл не открыт!" << endl;
	}
	file.close();
	//return h;
}

void Output_hasp_map(Hash_map* h, int size_hash) {
	for (int i = 0; i < size_hash; i++) {
		Hash_map* temp = &h[i];
		while (temp) {
			if (temp->busy) {
				cout << temp->num_passport << ' ' << temp->data.name << endl;
				temp = temp->next;
			}
			else {
				break;
			}
		}
	}
}

Tree* zap_tree(Tree* a) {
	ifstream file;
	file.open("Tree.txt");
	if (file.is_open()) {
		while (!file.eof()) {
			char c[1000];
			file.getline(c, 1000);
			Node el;
			el.number = strtok(c, " ");
			el.num_number = atoi(strtok(NULL, " "));
			el.count_place = atoi(strtok(NULL, " "));
			el.count_room = atoi(strtok(NULL, " "));
			el.sanuzel = atoi(strtok(NULL, " ")) == 1 ? true : false;
			int num = atoi(strtok(NULL, " "));
			while (num) {
				el.equipment += equip(num % 10);
				el.equipment += ' ';
				num /= 10;
			}
			a = add(a, el);
		}
	}
	else
	{
		cout << "Файл не открыт!" << endl;
	}
	file.close();
	return a;
}

void Output_tree(Tree* a) {
	if (a == NULL) {
		return;
	}
	cout << "Информация о номере: " << a->info_nomer.number << endl;
	cout << "Количество комнат: " << a->info_nomer.count_room << '\n'
		<< "Количество мест: " << a->info_nomer.count_place << '\n'
		<< "Наличие санузла: " << (a->info_nomer.sanuzel ? "Есть\n" : "Нет\n")
		<< "Оборудование номера: " << a->info_nomer.equipment << endl;
	Output_tree(a->Left);
	Output_tree(a->Right);
}

int len_list(Linear_List* l) {
	Linear_List* temp = l;
	int lenght = 0;
	while (temp) {
		lenght += 1;
		temp = temp->next;
	}
	return lenght;
}

Linear_List* insert(Linear_List* l, int num, Elem el) {
	auto temp = l;
	if (num == 0) {
		while (temp->info.num_passport != "") {
			temp = temp->next;
		}
		temp->info = el;
		return l;
	}
	for (int i = 1; i < num; i++) {
		temp = temp->next;
	}
	while (temp->next->info.num_passport != "") {
		temp = temp->next;
	}
	temp->next->info = el;
	return l;
}

Linear_List* sort(Linear_List* l) {
	int len = len_list(l);
	Linear_List* B = new Linear_List;
	Linear_List* temp = B;
	for (int i = len - 1; i > 0; --i) {
		temp->next = new Linear_List;
		temp = temp->next;
	}
	temp->next = NULL;
	auto i_el = l;
	while(i_el){
		int count = 0;
		temp = l;
		while (temp) {
			if (temp->info.number < i_el->info.number) {
				count++;
			}
			temp = temp->next;
		}
		B = insert(B, count, i_el->info);
		i_el = i_el->next;
	}
	return B;
}


Linear_List* add_list(Linear_List* l, Elem el) {
	Linear_List* new_el = new Linear_List;
	new_el->info = el;
	new_el->next = NULL;
	if (l == NULL) {
		l = new_el;
		return l;
	}
	Linear_List* temp = l;
	while (temp->next) {
		temp = temp->next;
	}
	temp->next = new_el;
	return l;
}

Linear_List* zap_list(Linear_List* l) {
	ifstream file;
	file.open("List.txt");
	if (file.is_open()) {
		while (!file.eof()) {
			char c[1000];
			file.getline(c, 1000);
			Elem el;
			el.num_passport = strtok(c, " ");
			el.num_number = strtok(NULL, " ");
			el.number = atoi(strtok(NULL, " "));
			el.date_input = strtok(NULL, " ");
			el.date_output = strtok(NULL, " ");
			l = add_list(l, el);
		}
	}
	else
	{
		cout << "Файл не открыт!" << endl;
	}
	file.close();
	return l;
}

void Output_List(Linear_List* l) {
	Linear_List* temp = l;
	int i = 1;
	while (temp) {
		cout << "Посетитель " << i << endl;
		cout << "Номер " << temp->info.num_number << '\n'
			<< "Номер паспорта: " << temp->info.num_passport << '\n'
			<< "Дата въезда: " << temp->info.date_input << '\n'
			<< "Дата выезда: " << temp->info.date_output << endl;
		temp = temp->next;
		i++;
	}
}


void all_node(Tree* a, vector <Node>* b) {
	if (a == NULL) {
		return;
	}
	Node el;
	el.num_number = a->info_nomer.num_number;
	el.number = a->info_nomer.number;
	el.count_place = a->info_nomer.count_place;
	el.count_room = a->info_nomer.count_room;
	el.equipment = a->info_nomer.equipment;
	el.sanuzel = a->info_nomer.sanuzel;
	b->push_back(el);
	all_node(a->Left, b);
	all_node(a->Right, b);
}


void input_in_file_tree(Tree* a){
	ofstream f;
	f.open("Tree.txt");
	vector <Node> b;
	all_node(a, &b);
	for (auto i : b) {
		char sanuzel = i.sanuzel ? '1' : '0';
		string c;
		if (i != b[b.size() - 1]) {
			c = i.number + ' ' + to_string(i.num_number) + ' '
				+ to_string(i.count_place) + ' '
				+ to_string(i.count_room) + ' ' + sanuzel + ' ' + to_string(equip_to_num(i.equipment)) + '\n';
		}
		else {
			c = i.number + ' ' + to_string(i.num_number) + ' '
				+ to_string(i.count_place) + ' '
				+ to_string(i.count_room) + ' ' + sanuzel + ' ' + to_string(equip_to_num(i.equipment));
		}
		f << c;
	}
	f.close();
}

void input_in_file_list(Linear_List* l) {
	ofstream f;
	f.open("List.txt");
	auto temp = l;
	string c;
	while (temp) {
		auto el = temp->info;
		if (temp->next) {
			c = el.num_passport + ' ' + el.num_number + ' '
				+ to_string(el.number) + ' ' + el.date_input + ' ' 
				+ el.date_output + '\n';
		}
		else {
			c = el.num_passport + ' ' + el.num_number + ' '
				+ to_string(el.number) + ' ' + el.date_input + ' ' 
				+ el.date_output;
		}
		f << c;
		temp = temp->next;
	}
	f.close();
}


void input_in_file_hash(Hash_map* h, int size) {
	ofstream f;
	f.open("Hash_map.txt");
	string c;
	vector <string> a;
	for (int i = 0; i < size; i++) {
		Hash_map* temp = &h[i];
		while (temp) {
			if (temp->busy) {
				c = temp->num_passport + ' ' + temp->data.name + ' ' + to_string(temp->data.year) + ' ' +
					temp->data.Address + ' ' + temp->data.target_come + '\n';
				a.push_back(c);
			}
			temp = temp->next;
		}
	}
	a[a.size() - 1].erase(c.size() - 1);
	for (auto i : a) {
		f << i;
	}
	f.close();
}


int print_menu() {
	cout << "Главное меню." << endl;
	cout << "1. Регистрация нового постояльца." << endl;
	cout << "2. Удаление данных о постояльце." << endl;
	cout << "3. Просмотр всех зарегистрированных постояльцев." << endl;
	cout << "4. Очистка данных о постояльцах." << endl;
	cout << "5. Поиск постояльца по номеру паспорта." << endl;
	cout << "6. Поиск постояльца по ФИО." << endl;
	cout << "7. Добавление нового гостиничного номера." << endl;
	cout << "8. Удаление сведений о гостиничном номере." << endl;
	cout << "9. Просмотр всех имеющихся гостиничных номеров." << endl;
	cout << "10. Очистка данных о гостиничных номерах." << endl;
	cout << "11. Поиск гостиничного номера по номеру." << endl;
	cout << "12. Поиск гостиничного номера по фрагментам <Оборудования>." << endl;
	cout << "13. Регистрация вселения постояльца." << endl;
	cout << "14. Регистрация выселения постояльца." << endl;
	cout << "15. Выход из главного меню." << endl;
	cout << "Введите пункт меню: " << endl;
	int num = check("Неверно. Выберите пункт меню ", 1, 15);
	return num;
}

void del_el_hash_map(Hash_map* h, Linear_List* l, int size, string num_passport) {
	auto temp = l;
	while (temp) {
		if (temp->info.num_passport == num_passport) {
			cout << "Этот постоялец в данный момент находится в гостинице, поэтому нельзя удалять данные о нем!!!" << endl;
			return;
		}
		temp = temp->next;
	}
	auto t = &h[hash_func(num_passport, size)];
	if (t->num_passport == num_passport) {
		t->busy = false;
		if (t->next) {
			h[hash_func(num_passport, size)] = *t->next;
			delete t;
		}
		return;
	}
	while (t->next) {
		if (t->next->num_passport == num_passport) {
			if (t->next->next) {
				auto t2 = t->next;
				t->next = t->next->next;
				delete t2;
			}
			else {
				delete t->next;
				t->next = NULL;
				return;
			}
		}
		else {
			t = t->next;
		}
	}
}

void del_pos(Hash_map* h, Linear_List* l, int size) {
	cout << "Введите номер паспорта постояльца, которого вы хотите удалить. " << endl;
	string num_passport = check_passport();
	del_el_hash_map(h, l, size, num_passport);
}


void clear_hash_map(Hash_map* h, Linear_List* l, int size) {
	for (int i = 0; i < size; i++) {
		auto temp = &h[i];
		while (temp) {
			if (temp->busy) {
				del_el_hash_map(h, l, size, temp->num_passport);
			}
			temp = temp->next;
		}
	}
}

void find_pos_passport(Hash_map* h, int size) {
	cout << "Введите номер паспорта постояльца в формате NNNN-NNNNNN, где N - цифра от 0 до 9: " << endl;
	string num_pass = check_passport();
	int temp_index = hash_func(num_pass, size);
	auto temp = &h[temp_index];
	while (temp) {
		if (temp->num_passport == num_pass) {
			cout << "Информация о постояльце: " << endl;
			cout << temp->num_passport << ' ' << temp->data.name << ' '
				<< temp->data.Address << ' ' << temp->data.target_come << endl;
			return;
		}
		temp = temp->next;
	}
	cout << "Постояльца с таким номером паспорта нет!!!" << endl;
}

void find_pos_name(Hash_map* h, int size) {
	cout << "Введите имя постояльца в формате Фамилия И.О.: " << endl;
	string name_pos;
	cin.clear();
	cin.ignore(INT_FAST16_MAX, '\n');
	while (true) {
		getline(cin, name_pos);
		regex name_post("[А-Я][а-я]* [А-Я]\.[А-Я]\.");
		if (regex_match(name_pos, name_post)) {
			break;
		}
		else {
			cout << "Неправильно введены фамилия и инициалы постояльца. Повторите ввод: " << endl;
		}
	}
	for (int i = 0; i < size; i++) {
		auto temp = &h[i];
		while (temp) {
			if (temp->data.name == name_pos) {
				cout << "Информация о постояльце: " << endl;
				cout << temp->num_passport << ' ' << temp->data.name << ' '
					<< temp->data.Address << ' ' << temp->data.target_come << endl;
				return;
			}
			temp = temp->next;
		}
	}
	cout << "Постояльца с таким ФИО нет в гостинице!!!" << endl;
}


Tree* add_new_nomer(Tree* a) {
	Node elem;
	cout << "Выберите цифру, соответствующую типу номера: " << endl;
	cout << "1. Люкс\n2. Полулюкс\n3. Одноместный\n4. Многоместный" << endl;
	int num = check("Неверно. Введите число ", 1, 4);
	switch (num)
	{
	case(1):
		elem.number = "Л";
		break;
	case(2):
		elem.number = "П";
		break;
	case(3):
		elem.number = "О";
		break;
	case(4):
		elem.number = "М";
		break;
	}
	while (true) {
		string number;
		cout << "Введите номер номера в формате NNN, где N - цифра от 0 до 9: " << endl;
		cin >> number;
		regex number_nim("[0-9]{3}");
		if (regex_match(number, number_nim) && number != "000") {
			if (find_elem(a, stoi(number), &num)) {
				cout << "Такой номер уже есть. Повторите ввод: " << endl;
				continue;
			}
			elem.number += number;
			elem.num_number = stoi(number);
			break;
		}
		else {
			cout << "Неправильно введен номер номера. Повторите ввод: " << endl;
			cin.clear();
			cin.ignore(INT_FAST16_MAX, '\n');
		}
	}
	cout << "Введите число мест в номере от 1 до 5" << endl;
	elem.count_place = check("Неверно. Введите число ", 1, 5);
	cout << "Введите число комнат в номере от 1 до 4" << endl;
	elem.count_room = check("Неверно. Введите число ", 1, 4);
	cout << "Введите 1, если в номере есть санузел, и 0, если нет: " << endl;
	num = check("Неверно. Введите число ", 0, 1);
	elem.sanuzel = num == 1? true : false;
	elem.equipment = "";
	cout << "Введите 1, если в номере есть приставка, и 0, если нет: " << endl;
	num = check("Неверно. Введите число ", 0, 1);
	elem.equipment += num == 1 ? "Приставка " : "";
	cout << "Введите 1, если в номере есть мини-бар, и 0, если нет: " << endl;
	num = check("Неверно. Введите число", 0, 1);
	elem.equipment += num == 1 ? "Мини-бар " : "";
	cout << "Введите 1, если в номере есть кондиционер, и 0, если нет: " << endl;
	num = check("Неверно. Введите число ", 0, 1);
	elem.equipment += num == 1 ? "Кондиционер " : "";
	cout << "Введите 1, если в номере есть телевизор, и 0, если нет: " << endl;
	num = check("Неверно. Введите число ", 0, 1);
	elem.equipment += num == 1 ? "Телевизор " : "";
	cout << "Введите 1, если в номере есть холодильник, и 0, если нет: " << endl;
	num = check("Неверно. Введите число ", 0, 1);
	elem.equipment += num == 1 ? "Холодильник " : "";
	a = add(a, elem);
	return a;
}


Tree* del_nomer(Tree* a, Linear_List* l) {
	cout << "Введите номер, который хотите удалить в формате числа от 1 до 999: " << endl;
	int num_number = check("Неверно. Введите число", 1, 999);
	int num = 0;
	if (find_elem(a, num_number, &num)) {
		auto temp = l;
		while (temp) {
			if (temp->info.number == num_number) {
				cout << "Этот номер нельзя удалять, т.к. в нем сейчас заселен человек." << endl;
				return a;
			}
			temp = temp->next;
		}
		Delete(a, num_number);
	}
	else {
		cout << "Такого номера нет в гостинице!!!" << endl;
	}
	return a;
}


bool nomer_in_list(int k, Linear_List* l) {
	auto temp = l;
	while (temp) {
		if (temp->info.number == k) return true;
		temp = temp->next;
	}
	return false;
}


Tree* clear_tree(Tree* a, Linear_List* l) {
	if (a == NULL) {
		return NULL;
	}
	if (nomer_in_list(a->info_nomer.num_number, l)) {
		a -> Left = clear_tree(a->Left, l);
		a -> Right = clear_tree(a->Right, l);
		return a;
	}
	else {
		a = Delete(a, a->info_nomer.num_number);
	}
}

Node* search_in_tree(Tree* a, int number) {
	if (a == NULL) {
		return NULL;
	}
	if (a->info_nomer.num_number == number) {
		return &a->info_nomer;
	}
	else if (a->info_nomer.num_number > number) {
		search_in_tree(a->Left, number);
	}
	else {
		search_in_tree(a->Right, number);
	}
}

void find_num(Tree* a, Linear_List* l, Hash_map* h, int size) {
	cout << "Введите номер гостиничного номера, который вы хотите найти в формате числа от 1 до 999: " << endl;
	int num = check("Неверно. Введите число", 1, 999);
	Node* x = search_in_tree(a, num);
	if (x == NULL) {
		cout << "Такого номера нет в гостинице!!!" << endl;
		return;
	}
	cout << "Информация о номере: " << x->number << endl;
	cout << "Количество комнат: " << x->count_room << '\n'
		<< "Количество мест: " << x->count_place << '\n'
		<< "Наличие санузла: " << (x->sanuzel ? "Есть\n" : "Нет\n")
		<< "Оборудование номера: " << x->equipment << endl;
	auto temp = l;
	bool flag = false;
	while (temp) {
		if (temp->info.number == num) {
			if (!flag) {
				cout << "Информация о постояльцах в номере " << temp->info.num_number << ":" << endl;
			}
			flag = true;
			cout << temp->info.num_passport << ' ' << h[hash_func(temp->info.num_passport, size)].data.name << endl;
		}
		temp = temp->next;
	}
	if (!flag) {
		cout << "В этом номере сейчас никто не живет!!!" << endl;
	}
}

Linear_List* input_pos(Linear_List* l, Tree* a, Hash_map* h, int size){
	cout << "Введите номер гостиничного номера, в который вы хотите заселить постояльца в формате числа от 1 до 999: " << endl;
	int num = check("Неверно. Введите число", 1, 999);
	Node* x = search_in_tree(a, num);
	if (x == NULL) {
		cout << "Такого номера нет в гостинице!!!" << endl;
		return l;
	}
	auto temp = l;
	int count = 0;
	string num_number;
	while (temp) {
		if (temp->info.number == num) {
			while (temp && temp->info.number == num) {
				num_number = temp->info.num_number;
				count++;
				temp = temp->next;
			}
			break;
		}
		temp = temp->next;
	}
	if (count < x->count_place) {
		Elem el;
		cout << "Введите номер паспорта постояльца в формате NNNN-NNNNNN, где N - цифра от 0 до 9: " << endl;
		string num_passport = check_passport();
		auto t = &h[hash_func(num_passport, size)];
		bool flag = false;
		while (t) {
			if (t->num_passport == num_passport) {
				flag = true; 
				break;
			}
			t = t->next;
		}
		if (!flag) {
			cout << "Такого постояльца нет. Сначала нужно его зарегистрировать!!!" << endl;
			return l;
		}
		auto x = l;
		while (x) {
			if (x->info.num_passport == num_passport) {
				cout << "Такой постоялец у нас уже заселен в номер " << x->info.num_number << "!!!" << endl;
				return l;
			}
			x = x->next;
		}
		el.num_passport = num_passport;

		cout << "Введите дату въезда в формате D.M.Y, где D - день, M - месяц, Y-год: " << endl;
		string date_in;
		regex date_1("[0-9][1-9]\.[0-1][1-9]\.[2][0][2][0-9]");
		while (true) {
			cin >> date_in;
			int day = stoi(date_in.substr(0, 2));
			int month = stoi(date_in.substr(3, 5));
			int year = stoi(date_in.substr(6, date_in.size()));
			if (regex_match(date_in, date_1) && 
				((day <= 30 && (month == 4 || month == 6 || month == 9 || month == 11)) ||
				(day <= 28 && month == 2 && (year % 4 != 0 || year % 100 == 0)) || 
				(day <= 29 && month == 2 && ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)) ||
				(day <= 31 && (month == 1 || month == 3 || month == 5 || month == 7 || 
					month == 8 || month == 10 || month == 12)))) {
				break;
			}
			else {
				cout << "Неверно введена дата. Повторите ввод: " << endl;
			}
		}
		el.date_input = date_in;
		cout << "Введите дату выезда в формате D.M.Y, где D - день, M - месяц, Y-год: " << endl;
		string date_out;
		regex date("[0-9][1-9]\.[0-1][1-9]\.[2][0][2][0-9]");
		while (true) {
			cin >> date_out;
			int day = stoi(date_out.substr(0, 2));
			int month = stoi(date_out.substr(3, 5));
			int year = stoi(date_out.substr(6, date_out.size()));
			if (regex_match(date_out, date) &&
				((day <= 30 && (month == 4 || month == 6 || month == 9 || month == 11)) ||
					(day <= 28 && month == 2 && (year % 4 != 0 || year % 100 == 0)) ||
					(day <= 29 && month == 2 && ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)) ||
					(day <= 31 && (month == 1 || month == 3 || month == 5 || month == 7 ||
						month == 8 || month == 10 || month == 12)))) {
				break;
			}
			else {
				cout << "Неверно введена дата. Повторите ввод: " << endl;
			}
		}
		el.date_output = date_out;
		el.number = num;
		el.num_number = num_number;
		l = add_list(l, el);
		l = sort(l);
	}
	else {
		cout << "В этом номере нет свободных мест!!!" << endl;
	}
	return l;
}


void eviction(Linear_List* l) {
	if (l == NULL) {
		return;
	}
	cout << "Введите номер паспорта постояльца, которого нужно выселить: " << endl;
	string num_passport = check_passport();
	auto temp = l;
	if (temp->info.num_passport == num_passport) {
		l = l->next;
		delete temp;
		return;
	}
	while (temp->next) {
		if (temp->next->info.num_passport == num_passport) {
			if (temp->next->next == NULL) {
				delete temp->next;
				temp->next = NULL;
			}
			else {
				auto t = temp->next;
				temp->next = temp->next->next;
				delete t;
			}
			return;
		}
		temp = temp->next;
	}
	cout << "Постоялец с таким номером паспорта никуда не заселен!!!" << endl;
}


bool search(string txt, string pat)
{
	std::map<char, int> a;
	for (int i = txt.size() - 1; i >= 0; --i) {
		auto it = a.find(txt[i]);
		if (it == a.cend()) {
			a[txt[i]] = txt.size() - 1 - i;
		}
		else {
			continue;
		}
	}
	a['*'] = txt.size();
	int i = txt.size() - 1; 
	bool flag = false;
	while(i < pat.size()) {
		flag = true;
		for (int j = i; j > (i - txt.size() + 1); --j) {
			if (txt[j - i + txt.size() - 1] != pat[j]) {
				auto it = a.find(pat[j]);
				if (it == a.cend()) {
					i += a['*'];
					flag = false;
					break;
				}
				else {
					flag = false;
					i += a[pat[j]];
					break;
				}
			}
		}
		if (flag) {
			break;
		}
	}
	return flag;
}



void sertain_obor(Tree* a, string obor) {
	if (a == NULL) {
		return;
	}
	if (search(obor, a->info_nomer.equipment)) {
		cout << "Информация о номере: " << a->info_nomer.number << endl;
		cout << "Количество комнат: " << a->info_nomer.count_room << '\n'
			<< "Количество мест: " << a->info_nomer.count_place << '\n'
			<< "Наличие санузла: " << (a->info_nomer.sanuzel ? "Есть\n" : "Нет\n")
			<< "Оборудование номера: " << a->info_nomer.equipment << endl;
	}
	sertain_obor(a->Left, obor);
	sertain_obor(a->Right, obor);
}


void find_oborudovanie(Tree* a) {
	string equipment = "";
	cout << "Введите 1, если в номере есть приставка, и 0, если нет: " << endl;
	int num = check("Неверно. Введите число ", 0, 1);
	equipment += num == 1 ? "Приставка " : "";
	cout << "Введите 1, если в номере есть мини-бар, и 0, если нет: " << endl;
	num = check("Неверно. Введите число", 0, 1);
	equipment += num == 1 ? "Мини-бар " : "";
	cout << "Введите 1, если в номере есть кондиционер, и 0, если нет: " << endl;
	num = check("Неверно. Введите число ", 0, 1);
	equipment += num == 1 ? "Кондиционер " : "";
	cout << "Введите 1, если в номере есть телевизор, и 0, если нет: " << endl;
	num = check("Неверно. Введите число ", 0, 1);
	equipment += num == 1 ? "Телевизор " : "";
	cout << "Введите 1, если в номере есть холодильник, и 0, если нет: " << endl;
	num = check("Неверно. Введите число ", 0, 1);
	equipment += num == 1 ? "Холодильник " : "";
	sertain_obor(a, equipment);
}

void check_hash_map(Hash_map* h, int size) {
	string pass_1 = "4901-135716";
	string pass_2 = "9401-135716";
	cout << h[hash_func(pass_1, size)].data.name << '\n' << 
		h[hash_func(pass_2, size)].next->data.name << endl;
}

/*Регистрация постояльцев в гостинице
Открытое хеширование
Сортировка подсчетом
Список линейный однонаправленный
Метод обхода дерева прямой
Алгоритм поиска слова в тексте Боуера и Мура*/

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int size_hash = 500;
	Hash_map* h = new Hash_map[size_hash];
	Tree* a = NULL;
	Linear_List* l = NULL;
	a = zap_tree(a);
	l = zap_list(l);
	l = sort(l);
	zap_hash_map(h, size_hash);
	//check_hash_map(h, size_hash);
	while (true) {
		int punkt_menu = print_menu();
		switch (punkt_menu) 
		{
		case(1):
			add_new_pos(h, size_hash);
			break;
		case(2):
			del_pos(h, l, size_hash);
			break;
		case(3):
			Output_hasp_map(h, size_hash);
			break;
		case(4):
			clear_hash_map(h, l, size_hash);
			break;
		case(5):
			find_pos_passport(h, size_hash);
			break;
		case(6):
			find_pos_name(h, size_hash);
			break;
		case(7):
			a = add_new_nomer(a);
			break;
		case(8):
			a = del_nomer(a, l);
			break;
		case(9):
			Output_tree(a);
			break;
		case(10):
			a = clear_tree(a, l);
			break;
		case(11):
			find_num(a, l, h, size_hash);
			break;
		case(12):
			find_oborudovanie(a);
			break;
		case(13):
			l = input_pos(l, a, h, size_hash);
			break;
		case(14):
			eviction(l);
			break;
		}
		if (punkt_menu == 15) {
			break;
		}
	}
	input_in_file_list(l);
	input_in_file_tree(a);
	input_in_file_hash(h, size_hash);
	return 0;
}
