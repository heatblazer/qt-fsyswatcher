#include "dirwatcher.h"
#include <iostream>

DirWatcher::DirWatcher(const QString &root, QObject* parent):
    QObject(parent), m_root(root)
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
    std::cout << "##############################################\r\n";
    QSetIterator<QString> setit(m_directories);
    while (setit.hasNext()) {
        QString d = setit.next();
        std::cout << d.toStdString() << std::endl;
    }
}


void DirWatcher::hFileChanged(const QString& file)
{
#if 0
    for (auto dir : m_root.entryList()) {
        std::cout << dir.toStdString() << std::endl;
    }
#endif
}
