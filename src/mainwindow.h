#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QVector>
#include <character.h>
#include <clas.h>
#include <species.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT
// =========================================================================
public:
// =========================================================================
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
// =========================================================================
private slots:
// =========================================================================
    void saveAction_triggered(int numChar);
    void saveAsAction_triggered(int numCHar);
    void addAction_triggered(bool opened);
// =========================================================================
    void closeTab(int numTab);
// =========================================================================
private:
// =========================================================================
    QString saveToJson(int numChar);
    void namingWidget(QWidget *widget, const QString &name, unsigned short num);
// =========================================================================
};
#endif // MAINWINDOW_H
