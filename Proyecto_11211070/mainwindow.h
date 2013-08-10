#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QVBoxLayout>
#include <QMessageBox>

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
    QAction* export_json;
    QAction* import_json;

    /* init methods */
    void init_components();
    void init_actions();
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    /* File menu slots */
    void newFile();
    void openFile();
    void saveFile();
    void printFile();
    void closeFile();

    /* Field menu slots */
    void createField();
    void changeField();
    void listFields();

    /* Record menu slots */
    void insertRecord();
    void searchRecord();
    void deleteRecord();
    void listRecods();
};

#endif // MAINWINDOW_H
