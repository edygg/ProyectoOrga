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
#include <QTableWidget>
#include <QTextDocument>
#include <QPrinter>

#include "adtfile.h"
#include "field.h"
#include "adtrecordfile.h"
#include "object.h"

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
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
    QAction* compact_file;
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


    /* Create Field Dialog */
    QDialog* field_dialog;
    QLineEdit* le_name;
    QComboBox* cbox_datatype;
    QSpinBox* sp_length;
    QSpinBox* sp_decimal_places;
    QCheckBox* chbox_key;

    /* Change Fields Dialog */
    QDialog* change_field_dialog;
    QComboBox* cbox_fields;
    QLineEdit* le_new_field_name;

    /* Input Record Dialog */
    QDialog* input_record_dialog;
    QLabel* lbl_message;
    QLineEdit* le_input_data;
    QPushButton* btn_accept;
    QString str_input_data;

    /* Status bar */
    QLabel* lbl_status_bar;

    /* Main Table */
    QTableWidget* main_table;

    /* init methods */
    void init_components();
    void init_actions();
    void init_field_dialog();
    void init_change_field_dialog();
    void init_input_record_dialog();
    void initialStatus();
    void enabledComponents();
    void clearMainTable();
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
    void listRecords();
    void compactFile();

    /* Indexes menu slots */
    void createSimpleIndex();

    /* Create Field Dialog */
    void desactivateDecimalPlaces();
    void saveField();

    /* Change Field Dialog */
    void updateFields();

    /* Input Record Dialog */
    void recieveInput();
};

#endif // MAINWINDOW_H
