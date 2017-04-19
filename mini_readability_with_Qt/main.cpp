#include <QApplication>
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <set>
#include <locale.h>

#include <QFile>
#include <QTextStream>
// include project files
#include "make_full_html_file.h"
#include "dialog.h"


int main(int argc, char *argv[])
{
    setlocale(LC_CTYPE, "Russian");
    QApplication a(argc, argv);
    Dialog w;
    w.show();
    return a.exec();
}
