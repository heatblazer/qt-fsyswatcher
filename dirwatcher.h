#ifndef DIRWATCHER_H
#define DIRWATCHER_H
#include <QObject>
#include <QFileSystemWatcher>
#include <QDir>
#include <QSet>
#include <QDirIterator>


class DirWatcher : public QObject
{
    Q_OBJECT
public:
    static const int sMaxCount = 5;

    explicit DirWatcher(const QString& root, QObject* parent = nullptr);
    virtual ~DirWatcher();

private slots:

    void hDirChanged(const QString&);

    void hFileChanged(const QString&);

private:
    QFileSystemWatcher m_watcher;
    QDir m_root;
    QSet<QString> m_directories;
    QString m_lastKey;

};

#endif // DIRWATCHER_H
