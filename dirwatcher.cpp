#include "dirwatcher.h"
#include <iostream>

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


DirWatcher::DirWatcher(const QString &root, QObject* parent):
    QObject(parent), m_root(root), m_rbSize{10}
{

    m_watcher.addPath(root);

    QObject::connect(&m_watcher, SIGNAL(directoryChanged(const QString&)),
                                        this, SLOT(hDirChanged(const QString&)));


    QObject::connect(&m_watcher, SIGNAL(fileChanged(const QString&)),
                                        this, SLOT(hFileChanged(const QString&)));


}

DirWatcher::~DirWatcher()
{

}


void DirWatcher::hDirChanged(const QString &path)
{
    QDirIterator it(m_root.path());
    while (it.hasNext()) {
        QString d = it.next();
        if (d.at(0) == '.' || d.at(d.size()-1) == '.') {
        } else {
            if (!m_directories.contains(d)){
                m_directories << d;
                m_lastKey = d;
            }
        }

    }

#if 0 //delete directories when count reaches...
    if (m_directories.count() > DirWatcher::sMaxCount) {
        QSetIterator<QString> setit(m_directories);
        while (setit.hasNext()) {
            QString toDel = setit.next();
            if (toDel != m_lastKey) {
                QDir rem (toDel);
                rem.removeRecursively();
            }
        }
        m_directories.clear();
        m_directories << m_lastKey;
    }
#endif
    std::cout << "##############################################\r\n";
    QSetIterator<QString> setit(m_directories);
    while (setit.hasNext()) {
        QString d = setit.next();
        if (d.contains(".tlf")) {
            m_watcher.addPath(d);
        }
        std::cout << d.toStdString() << std::endl;
    }
}


void DirWatcher::hFileChanged(const QString& file)
{
    static size_t cnt = 0;
    QFile f{file};
    if (f.open(QFile::ReadOnly)) {
        quint64 s = f.size();
        s /= 4;
        f.seek(f.size()-s);
        while (!f.atEnd()) {
            QByteArray data = f.readLine();
            m_ringBuffer[cnt++ % m_rbSize]=data;
        }
    }

    std::cout << "----------------- B E G I N ----------------------\r\n";
    for(auto i : m_ringBuffer) {
        std::cout << "~~~~~~\r\n";
        std::cout << i.toStdString().c_str() << "\r\n";
    }
}
