#include "html_parser.h"
#include <cstdio>

HtmlParser::HtmlParser(string nameOfFile) {
    string a;
    std::ifstream in(nameOfFile);
    while (getline(in, a)) {
        fullHtmlFile += a;
        fullHtmlFile += '\n';
    }
    in.close();
    for (int i = 0; i < 50; i++) {
        fullHtmlFile += "</File> ";
    }

    // To not call the copy constructor
    file = shared_ptr<Tag>(new Tag(fullHtmlFile, 0, string("File"), string("File"), nullptr));
    fileName = string(nameOfFile, 0, nameOfFile.size() - 14);
    fileName += ".txt";
}

string HtmlParser::getNameOfFile() const {
    return fileName;
}

string HtmlParser::getTags(set<string>& tags) {
    string readyLine;
    file->getTags(readyLine, tags);
    return readyLine;
}

string HtmlParser::getTagsFromFile(string nameOfFile) {
    std::ifstream in(nameOfFile);
    if (!in.is_open()) {
        throw std::exception("Could not open file\n");
    }
    string a;
    set<string> tags;
    while (in >> a) {
        tags.insert(a);
    }
    return getTags(tags);
}

string HtmlParser::getClearText() {
    set<string> tags;
    tags.insert(string("title"));
    tags.insert(string("p"));
    string fullLine = getTags(tags);
    string readyLine;
    removeTagP(fullLine);
    convertLink(fullLine);
    deleteCharacterEntity(readyLine);
    makeReadyLine(fullLine, readyLine);
    makeLineBreaks(readyLine);
    return readyLine;
}
string HtmlParser::getClTextWithoutLineBreaks() {
    set<string> tags;
    tags.insert(string("title"));
    tags.insert(string("p"));
    string fullLine = getTags(tags);
    string readyLine;
    removeTagP(fullLine);
    convertLink(fullLine);
    deleteCharacterEntity(fullLine);
    makeReadyLine(fullLine, readyLine);
    return readyLine;
}

void HtmlParser::deleteRaquo(string& readyLine) {
    int POS_FIND = (int)readyLine.find("&raquo;");
    while (POS_FIND >= 0) {
        readyLine[POS_FIND] = '"';
        const int COUNT_SYMBOLS = 6;
        readyLine[POS_FIND + 1] = '<';
        readyLine[POS_FIND + COUNT_SYMBOLS] = '"';
        POS_FIND = (int)readyLine.find("&raquo;");
    }
}

void HtmlParser::deleteLaquo(string& readyLine) {
    int POS_FIND = (int)readyLine.find("&laquo;");
    while (POS_FIND >= 0) {
        readyLine[POS_FIND] = '"';
        const int COUNT_SYMBOLS = 6;
        readyLine[POS_FIND + 1] = '<';
        readyLine[POS_FIND + COUNT_SYMBOLS] = '"';
        POS_FIND = (int)readyLine.find("&laquo;");
    }
}

void HtmlParser::deleteMdash(string& readyLine) {
    int POS_FIND = (int)readyLine.find("&mdash;");
    while (POS_FIND >= 0) {
        readyLine[POS_FIND] = '"';
        const int COUNT_SYMBOLS = 6;
        readyLine[POS_FIND + 1] = '<';
        readyLine[POS_FIND + COUNT_SYMBOLS] = '"';
        POS_FIND = (int)readyLine.find("&mdash;");
    }
}

void HtmlParser::deleteNdash(string& readyLine) {
    int POS_FIND = (int)readyLine.find("&ndash;");
    while (POS_FIND >= 0) {
        readyLine[POS_FIND] = '"';
        const int COUNT_SYMBOLS = 6;
        readyLine[POS_FIND + 1] = '<';
        readyLine[POS_FIND + COUNT_SYMBOLS] = '"';
        POS_FIND = (int)readyLine.find("&ndash;");
    }
}

void HtmlParser::removeTagP(string& fullLine) {
    int x = (int)fullLine.find("<p>");
    while (x >= 0) {
        fullLine.insert(x, "\n\n");
        x += 2;
        string a(&fullLine[x + 1]);
        if ((int)a.find("<p>") >= 0)
            x += (int)a.find("<p>") + 1;
        else
            x = -1;
    }
}

void HtmlParser::convertLink(string& fullLine) {
    int x = (int)fullLine.find("href=\"");
    while (x >= 0) {
        fullLine[x + 4] = '>';
        fullLine[x + 5] = '[';
        string a(&fullLine[x]);
        const int POS_SYMBOL = (int)a.find('"');
        if (POS_SYMBOL > 0) {
            fullLine[x + POS_SYMBOL] = ']';
            fullLine[x + POS_SYMBOL + 1] = '<';
        }
        x = (int)fullLine.find("href=\"");
    }
}

void HtmlParser::makeReadyLine(string& fullLine, string& readyLine) {
    bool id = 1;
    for (int i = 0, size = (int)fullLine.size(); i < size; i++) {
        if (fullLine[i] == '<') {
            id = false;
            continue;
        }
        if (fullLine[i] == '>') {
            id = true;
            continue;
        }
        if (id) {
            readyLine += fullLine[i];
        }
    }
}

void HtmlParser::makeLineBreaks(string& readyLine) {
    int x = (int)readyLine.find(' ');
    while (x >= 0) {
        string a(readyLine);
        a.erase(x);
        if (a.size() - a.rfind('\n') > 80)
            readyLine[x] = '\n';
        x++;
        string b(&readyLine[x]);
        const int POS_FIND = (int)b.find(' ');
        if (POS_FIND >= 0)
            x += POS_FIND;
        else
            x = -1;
    }
}

void HtmlParser::deleteCharacterEntity(string& readyLine) {
    deleteRaquo(readyLine);
    deleteLaquo(readyLine);
    deleteMdash(readyLine);
    deleteNdash(readyLine);
}
