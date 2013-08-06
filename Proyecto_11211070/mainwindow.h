#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QVBoxLayout>

/* Constants */
const QString PROGRAM_NAME = "Edilson Fernando Gonzalez";
const QString EXTENSION = ".edb";

class MainWindow : public QMainWindow
{
    Q_OBJECT

    /* File menu actions */
    QAction* new_file;
    QAction* open_file;
    QAction* save_file;
    QAction* print_file;
    QAction* close_file;
    QAction* quit_program;

    /* Field menu actions */
    QAction* create_field;
    QAction* change_field;
    QAction* list_fields;

    /* Record menu actions */
    QAction* insert_record;
    QAction* search_record;
    QAction* delete_record;
    QAction* list_records;

    /* Indexes menu actions */
    QAction* create_simple_index;
    QAction* create_Btree_index;
    QAction* reindex;

    /* Utilities menu actions */
    QAction* export_xml;
    QAction* import_xml;

    /* init methods */
    void init_components();
    void init_actions();
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
};

#endif // MAINWINDOW_H
