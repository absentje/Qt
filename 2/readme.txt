Приложение с использованием текстовой строки, кнопок, переключателей, флажков.
Поля:
QLabel("FirstName: "), QLineEdit;
QLabel("LastName: "), QLineEdit;
QGroupBox("&Sex"), содержащее в себе QRadioButton("&Male"), QRadioButton("&Female");
QCheckBox("O&ne"), QCheckBox("T&wo"), QCheckBox("Th&ree");
QPushButton("&Update"), QPushButton("&Exit"):
первая кнопка задает параметры в виджетах по умолчанию
вторая кнопка закрывает приложение(главный виджет)