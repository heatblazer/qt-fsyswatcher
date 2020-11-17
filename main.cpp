#include <QCoreApplication>
#include "dirwatcher.h"

namespace
{

    void split(const char* str, const char* delim, std::vector<std::string>& out)
    {
        const char* begin = str;
        const char* it = strstr(str, delim);
        if (it != NULL)
        {
            std::string data{begin, it};
            out.push_back(data);
            it++;
            split(it, delim, out);
        } else {
            std::string data{str};
            out.push_back(data);
        }
    }
}




int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
#if 0
    QFile fp{"Config.ini"};
    if (fp.open(QFile::ReadOnly)) {
        QByteArray b = fp.readAll();
        std::vector<std::string> out;
        split(b.toStdString().c_str(), ":", out);
        for(auto it : out) {
            printf("[%s]\r\n", it.c_str());
        }
    }
#endif
    DirWatcher dw(argv[1]);
    return a.exec();
}
