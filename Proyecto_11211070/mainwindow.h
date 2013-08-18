#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QLabel>
#include <QStatusBar>
#include <QFileDialog>
#include <QInputDialog>
#include <QDialog>
#include <QFormLayout>
#include <QLineEdit>
#include <QComboBox>
#include <QSpinBox>
#include <QCheckBox>
#include <QPushButton>

#include "adtfile.h"
#include "field.h"
#include "adtrecordfile.h"

#include <iostream>
#include <string>
using namespace std;

/* Constants */
const QString PROGRAM_NAME = "Edilson Fernando Gonzalez";
const QString EXTENSION = ".edb";
const QString TEMP_FILE = "temp_file" + EXTENSION;

class MainWindow : public QMainWindow
{
    Q_OBJECT

    /* Files */
    ADTRecordFile current_open_file;

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
    QAction* cross_tables;

    /* Indexes menu actions */
    QAction* create_simple_index;
    QAction* create_Btree_index;
    QAction* reindex;

    /* Utilities menu actions */
    QAction* export_xml;
    QAction* import_xml;
    QAction* export_json;
    QAction* import_json;


    /* Field Dialog */
    QDialog* field_dialog;
    QLineEdit* le_name;
    QComboBox* cbox_datatype;
    QSpinBox* sp_length;
    QSpinBox* sp_decimal_places;
    QCheckBox* chbox_key;

    /* Status bar */
    QLabel* lbl_status_bar;

    /* init methods */
    void init_components();
    void init_actions();
    void init_field_dialog();
    void initialStatus();
    void enabledComponents();
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

    /* Create Field Dialog */
    void desactivateDecimalPlaces();
    void saveField();
};

#endif // MAINWINDOW_H
