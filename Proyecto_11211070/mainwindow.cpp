#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    init_components();
}

MainWindow::~MainWindow()
{
}

void MainWindow::init_components() {
    init_actions();
    init_field_dialog();
    init_change_field_dialog();

    /* File menu */
    QMenu* file_menu = menuBar()->addMenu("File");
    file_menu->addAction(this->new_file);
    file_menu->addAction(this->open_file);
    file_menu->addAction(this->save_file);
    file_menu->addAction(this->print_file);
    file_menu->addAction(this->close_file);
    file_menu->addAction(this->quit_program);

    /* Field menu */
    QMenu* field_menu = menuBar()->addMenu("Fields");
    field_menu->addAction(this->create_field);
    field_menu->addAction(this->change_field);
    field_menu->addAction(this->list_fields);

    /* Record menu */
    QMenu* record_menu = menuBar()->addMenu("Records");
    record_menu->addAction(this->insert_record);
    record_menu->addAction(this->search_record);
    record_menu->addAction(this->delete_record);
    record_menu->addAction(this->list_records);
    record_menu->addAction(this->cross_tables);

    /* Indexes menu */
    QMenu* indexes_menu = menuBar()->addMenu("Indexes");
    indexes_menu->addAction(this->create_simple_index);
    indexes_menu->addAction(this->create_Btree_index);
    indexes_menu->addAction(this->reindex);

    /* Utilities menu */
    QMenu* utilities_menu = menuBar()->addMenu("Utilities");
    utilities_menu->addAction(this->export_xml);
    utilities_menu->addAction(this->import_xml);
    utilities_menu->addAction(this->export_json);
    utilities_menu->addAction(this->import_json);

    /* Status bar */
    QLabel* main_status_bar = new QLabel();
    this->lbl_status_bar = main_status_bar;
    main_status_bar->setAlignment(Qt::AlignHCenter);
    main_status_bar->setMinimumSize(main_status_bar->sizeHint());
    this->statusBar()->addWidget(main_status_bar);

    /* Main table */
    this->main_table = new QTableWidget(this);
    this->setCentralWidget(main_table);

    initialStatus();
    this->setMinimumSize(500, 500);
    this->setWindowTitle(PROGRAM_NAME);
}

void MainWindow::init_actions() {
    /* File menu actions */
    this->new_file = new QAction("New File", this);
    this->new_file->setShortcut(Qt::CTRL + Qt::Key_N);
    this->new_file->setStatusTip("Create a new database");
    this->new_file->setToolTip("Create a new database");
    this->new_file->setCheckable(false);
    connect(this->new_file, SIGNAL(triggered()), this, SLOT(newFile()));

    this->open_file = new QAction("Open File", this);
    this->open_file->setShortcut(Qt::CTRL + Qt::Key_O);
    this->open_file->setStatusTip("Open an exist database");
    this->open_file->setToolTip("Open an exist database");
    this->open_file->setCheckable(false);
    connect(this->open_file, SIGNAL(triggered()), this, SLOT(openFile()));

    this->save_file = new QAction("Save File", this);
    this->save_file->setShortcut(Qt::CTRL + Qt::Key_S);
    this->save_file->setStatusTip("Save changes in the current database");
    this->save_file->setToolTip("Save changes in the current database");
    this->save_file->setCheckable(false);
    connect(this->save_file, SIGNAL(triggered()), this, SLOT(saveFile()));

    this->print_file = new QAction("Print File", this);
    this->print_file->setShortcut(Qt::CTRL + Qt::Key_P);
    this->print_file->setStatusTip("Print the content of file");
    this->print_file->setToolTip("Print the content of file");
    this->print_file->setCheckable(false);
    connect(this->print_file, SIGNAL(triggered()), this, SLOT(printFile()));

    this->close_file = new QAction("Close File", this);
    this->close_file->setShortcut(Qt::CTRL + Qt::Key_C);
    this->close_file->setStatusTip("Close the current database");
    this->close_file->setToolTip("Close the current database");
    this->close_file->setCheckable(false);
    connect(this->close_file, SIGNAL(triggered()), this, SLOT(closeFile()));

    this->quit_program = new QAction("Quit", this);
    this->quit_program->setShortcut(Qt::ALT + Qt::Key_F4);
    this->quit_program->setStatusTip("Exit program");
    this->quit_program->setToolTip("Exit program");
    this->quit_program->setCheckable(false);
    connect(this->quit_program, SIGNAL(triggered()), this, SLOT(close()));

    /* Field menu actions */
    this->create_field = new QAction("Create", this);
    this->create_field->setStatusTip("Create a new field");
    this->create_field->setToolTip("Create a new field");
    this->create_field->setCheckable(false);
    connect(this->create_field, SIGNAL(triggered()), this, SLOT(createField()));

    this->change_field = new QAction("Change", this);
    this->change_field->setStatusTip("Change a exist field");
    this->change_field->setToolTip("Change a exist field");
    this->change_field->setCheckable(false);
    connect(this->change_field, SIGNAL(triggered()), this, SLOT(changeField()));

    this->list_fields = new QAction("List", this);
    this->list_fields->setStatusTip("List all fields");
    this->list_fields->setToolTip("List all fields");
    this->list_fields->setCheckable(false);
    connect(this->list_fields, SIGNAL(triggered()), this, SLOT(listFields()));

    /* Record menu actions */
    this->insert_record = new QAction("Insert", this);
    this->insert_record->setStatusTip("Insert a new record");
    this->insert_record->setToolTip("Insert a new record");
    this->insert_record->setCheckable(false);
    connect(this->insert_record, SIGNAL(triggered()), this, SLOT(insertRecord()));

    this->search_record = new QAction("Search", this);
    this->search_record->setStatusTip("Search a record");
    this->search_record->setToolTip("Search a record");
    this->search_record->setCheckable(false);
    connect(this->search_record, SIGNAL(triggered()), this, SLOT(searchRecord()));

    this->delete_record = new QAction("Delete", this);
    this->delete_record->setStatusTip("Delete a record");
    this->delete_record->setToolTip("Delete a record");
    this->delete_record->setCheckable(false);
    connect(this->delete_record, SIGNAL(triggered()), this, SLOT(deleteRecord()));

    this->list_records = new QAction("List", this);
    this->list_records->setStatusTip("List all records");
    this->list_records->setToolTip("Search all records");
    this->list_records->setCheckable(false);
    connect(this->list_records, SIGNAL(triggered()), this, SLOT(listRecods()));

    this->cross_tables = new QAction("Cross", this);
    this->cross_tables->setStatusTip("Cross tables");
    this->cross_tables->setToolTip("Cross tables");
    this->cross_tables->setCheckable(false);

    /* Indexes menu */
    this->create_simple_index = new QAction("Create Simple Index", this);
    this->create_simple_index->setStatusTip("Create Simple Index");
    this->create_simple_index->setToolTip("Create Simple Index");
    this->create_simple_index->setCheckable(false);

    this->create_Btree_index = new QAction("Create B Tree Index", this);
    this->create_Btree_index->setStatusTip("Create B Tree Index");
    this->create_Btree_index->setToolTip("Create B Tree Index");
    this->create_Btree_index->setCheckable(false);

    this->reindex = new QAction("Reindex", this);
    this->reindex->setStatusTip("Reindex");
    this->reindex->setToolTip("Reindex");
    this->reindex->setCheckable(false);

    /* Utilities menu */
    this->export_xml = new QAction("Export to XML", this);
    this->export_xml->setStatusTip("Export current database intro XML file");
    this->export_xml->setToolTip("Export current database intro XML file");
    this->export_xml->setCheckable(false);

    this->import_xml = new QAction("Import to XML", this);
    this->import_xml->setStatusTip("Import data intro XML file");
    this->import_xml->setToolTip("Import data intro XML file");
    this->import_xml->setCheckable(false);

    this->export_json = new QAction("Export to JSON", this);
    this->export_json->setStatusTip("Export current database intro JSON file");
    this->export_json->setToolTip("Export current database intro JSON file");
    this->export_json->setCheckable(false);

    this->import_json = new QAction("Import to JSON", this);
    this->import_json->setStatusTip("Import data intro JSON file");
    this->import_json->setToolTip("Import data intro JSON file");
    this->import_json->setCheckable(false);
}
void MainWindow::init_field_dialog() {
    this->field_dialog = new QDialog(this);
    QFormLayout* layout = new QFormLayout(this->field_dialog);

    this->le_name = new QLineEdit(this->field_dialog);
    this->le_name->setMaxLength(30);
    QRegExp exp("[A-Za-z][A-Za-z0-9]*");
    this->le_name->setValidator(new QRegExpValidator(exp, this->field_dialog));
    layout->addRow(new QLabel("Name"), this->le_name);

    QStringList cbox_options;
    cbox_options << "Integer" << "Real" << "String";
    this->cbox_datatype = new QComboBox(this->field_dialog);
    this->cbox_datatype->addItems(cbox_options);
    connect(this->cbox_datatype, SIGNAL(currentIndexChanged(QString)), this, SLOT(desactivateDecimalPlaces()));
    layout->addRow(new QLabel("Data Type"), this->cbox_datatype);

    this->sp_length = new QSpinBox(this->field_dialog);
    this->sp_length->setMinimum(1);
    this->sp_length->setMaximum(255);
    layout->addRow(new QLabel("Length"), this->sp_length);

    this->sp_decimal_places = new QSpinBox(this->field_dialog);
    this->sp_decimal_places->setMinimum(0);
    this->sp_decimal_places->setMaximum(255);
    this->sp_decimal_places->setEnabled(false);
    layout->addRow(new QLabel("Decimal Places"), this->sp_decimal_places);

    this->chbox_key = new QCheckBox(this->field_dialog);
    layout->addRow(new QLabel("Key"), this->chbox_key);

    QPushButton* btn_cancel = new QPushButton("Cancel", this->field_dialog);
    connect(btn_cancel, SIGNAL(clicked()), this->field_dialog, SLOT(close()));
    QPushButton* btn_save_field = new QPushButton("Save", this->field_dialog);
    connect(btn_save_field, SIGNAL(clicked()), this, SLOT(saveField()));
    layout->addWidget(btn_save_field);
    layout->addWidget(btn_cancel);



    this->field_dialog->setLayout(layout);

    this->field_dialog->setWindowTitle("Create a new field");
    this->field_dialog->setModal(true);
    this->field_dialog->setWindowFlags((windowFlags() | Qt::CustomizeWindowHint)
                                       & ~Qt::WindowMaximizeButtonHint
                                       & ~Qt::WindowContextHelpButtonHint
                                       & ~Qt::WindowMinimizeButtonHint);

}

void MainWindow::init_change_field_dialog() {
    this->change_field_dialog = new QDialog(this, (windowFlags() | Qt::CustomizeWindowHint)
                                            & ~Qt::WindowMaximizeButtonHint
                                            & ~Qt::WindowContextHelpButtonHint
                                            & ~Qt::WindowMinimizeButtonHint);
    QVBoxLayout* layout = new QVBoxLayout(this->change_field_dialog);

    this->cbox_fields = new QComboBox(this->change_field_dialog);
    layout->addWidget(this->cbox_fields);

    this->le_new_field_name = new QLineEdit(this->change_field_dialog);
    this->le_new_field_name->setMaxLength(30);
    QRegExp exp("[A-Za-z][A-Za-z0-9]*");
    this->le_new_field_name->setValidator(new QRegExpValidator(exp, this->change_field_dialog));
    layout->addWidget(this->le_new_field_name);
    this->change_field_dialog->setLayout(layout);
    QPushButton* btn_change = new QPushButton("Change" ,this->change_field_dialog);
    connect(btn_change, SIGNAL(clicked()), this, SLOT(updateFields()));
}

void MainWindow::desactivateDecimalPlaces() {
    if (this->cbox_datatype->currentText() != "Real") {
        this->sp_decimal_places->setEnabled(false);
    } else {
        this->sp_decimal_places->setEnabled(true);
    }
}

void MainWindow::initialStatus() {
    this->save_file->setEnabled(false);
    this->print_file->setEnabled(false);
    this->close_file->setEnabled(false);
    this->create_field->setEnabled(false);
    this->change_field->setEnabled(false);
    this->list_fields->setEnabled(false);
    this->insert_record->setEnabled(false);
    this->search_record->setEnabled(false);
    this->delete_record->setEnabled(false);
    this->list_records->setEnabled(false);
    this->cross_tables->setEnabled(false);
    this->create_simple_index->setEnabled(false);
    this->create_Btree_index->setEnabled(false);
    this->reindex->setEnabled(false);
    this->export_xml->setEnabled(false);
    this->import_xml->setEnabled(false);
    this->export_json->setEnabled(false);
    this->import_json->setEnabled(false);
}

void MainWindow::enabledComponents() {
    this->save_file->setEnabled(true);
    this->print_file->setEnabled(true);
    this->close_file->setEnabled(true);
    this->create_field->setEnabled(true);
    this->change_field->setEnabled(true);
    this->list_fields->setEnabled(true);
    this->insert_record->setEnabled(true);
    this->search_record->setEnabled(true);
    this->delete_record->setEnabled(true);
    this->list_records->setEnabled(true);
    this->cross_tables->setEnabled(true);
    this->create_simple_index->setEnabled(true);
    this->create_Btree_index->setEnabled(true);
    this->reindex->setEnabled(true);
    this->export_xml->setEnabled(true);
    this->import_xml->setEnabled(true);
    this->export_json->setEnabled(true);
    this->import_json->setEnabled(true);
}

void MainWindow::newFile() {
    if (this->current_open_file.open()) {
        this->current_open_file.close();
    }

    QString folder = QFileDialog::getExistingDirectory(this, "New File", "");
    if (!folder.isEmpty()) {
        bool ok;
        QString file_name = QInputDialog::getText(this, "File name", "File Name: ", QLineEdit::Normal,"", &ok);
        if (ok && !file_name.isEmpty()) {
            QString path = folder + "/" + file_name + EXTENSION;
            if (!this->current_open_file.open(path.toStdString())) {
                this->current_open_file.open(path.toStdString(), ios::out);
                this->current_open_file.write("%", 1);
                this->current_open_file.flush();
                this->current_open_file.close();
                if(this->current_open_file.open(path.toStdString())) {
                    QMessageBox::information(this, "Successful", "Database created successfully");
                    enabledComponents();
                }
            }
        }
    }
}

void MainWindow::openFile() {
    if (this->current_open_file.open()) {
        this->current_open_file.close();
    }

    QString file_name = QFileDialog::getOpenFileName(this, "Open File", "", "Databases (*" + EXTENSION + ")");

    if (this->current_open_file.open(file_name.toStdString())) {
        this->lbl_status_bar->setText("Opened sucessfully");
        enabledComponents();
    } else {
        this->lbl_status_bar->setText("");
    }
}

void MainWindow::saveFile() {
    if(this->current_open_file.flush()) {
        this->lbl_status_bar->setText("Saved successfully");
    } else {
        this->lbl_status_bar->setText("");
    }

}

void MainWindow::printFile() {

}

void MainWindow::closeFile() {
    if (this->current_open_file.close()) {
        this->lbl_status_bar->setText("Closed successfully");
        initialStatus();
    } else {
        this->lbl_status_bar->setText("");
    }
}

void MainWindow::createField() {
    this->field_dialog->exec();
}

void MainWindow::saveField() {
    if (this->le_name->text().isEmpty() || (this->sp_decimal_places->isEnabled() && this->sp_decimal_places->value() >= this->sp_length->value())) {
        QMessageBox::warning(this->field_dialog, "Error", "Check field values");
    } else {
        Field* neo;

        if (this->cbox_datatype->currentText() == "Integer") {
            neo = new Field(
                        this->le_name->text().toStdString(),
                        INT_DT,
                        this->sp_length->value(),
                        255,
                        this->chbox_key->checkState()
                        );
            this->current_open_file.createField(*neo);
            this->lbl_status_bar->setText("Success");
        } else if (this->cbox_datatype->currentText() == "String") {
            neo = new Field(
                        this->le_name->text().toStdString(),
                        STRING_DT,
                        this->sp_length->value(),
                        255,
                        this->chbox_key->checkState()
                        );
            this->current_open_file.createField(*neo);
            this->lbl_status_bar->setText("Success");
        } else {
            neo = new Field(
                        this->le_name->text().toStdString(),
                        REAL_DT,
                        this->sp_length->value(),
                        this->sp_decimal_places->value(),
                        this->chbox_key->checkState()
                        );
            this->current_open_file.createField(*neo);
            this->lbl_status_bar->setText("Success");
        }

        this->le_name->setText("");
        this->sp_length->setValue(1);
        this->sp_decimal_places->setValue(0);
    }
}

void MainWindow::changeField() {
    this->cbox_fields->clear();


    this->change_field_dialog->exec();
}

void MainWindow::updateFields() {

}

void MainWindow::listFields() {
   this->clearMainTable();

    this->current_open_file.readFileStructure();
    vector<Field> fields = this->current_open_file.listFields();
    this->main_table->setColumnCount(5);
    QStringList headers;
    headers << "Name" << "Data Type" << "Length" << "Decimal Places" << "Key";
    this->main_table->setHorizontalHeaderLabels(headers);
    this->main_table->setRowCount(fields.size());

    for (int i = 0; i < fields.size(); i++) {
        stringstream ss;
        string value;
        QString value2;
        Field* curr = &fields[i];
        ss << curr->getName();
        ss >> value;
        value2 = QString::fromStdString(value);
        this->main_table->setItem(i, 0, new QTableWidgetItem(value2));

        if (curr->getDatatype() == INT_DT) {
            value2 = "INTEGER";
        } else if (curr->getDatatype() == STRING_DT) {
            value2 = "STRING";
        } else {
            value2 = "REAL";
        }
        this->main_table->setItem(i, 1, new QTableWidgetItem(value2));

        value2 = QString::number((int) curr->getLength());
        this->main_table->setItem(i, 2, new QTableWidgetItem(value2));

        if (curr->getDatatype() != REAL_DT) {
            value2 = "0";
        } else {
            value2 = QString::number((int) curr->getDecimalPlaces());
        }
        this->main_table->setItem(i, 3, new QTableWidgetItem(value2));

        if (curr->isKey()) {
            value2 = "Yes";
        } else {
            value2 = "No";
        }
        this->main_table->setItem(i, 4, new QTableWidgetItem(value2));
    }
}

void MainWindow::clearMainTable() {
    if (!this->main_table) {
        return;
    }

    while(this->main_table->rowCount() > 0) {
        this->main_table->removeRow(0);
    }

    while (this->main_table->columnCount() > 0) {
        this->main_table->removeColumn(0);
    }
}

void MainWindow::insertRecord() {

}

void MainWindow::searchRecord() {

}

void MainWindow::deleteRecord() {

}

void MainWindow::listRecods() {

}
